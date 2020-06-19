#ifndef PROCESSINFO_H
#define PROCESSINFO_H

/**
* @projectName   LeagueLobby
* @brief         根据进程名获取进程所在路径
* @author        Mario
* @date          2020-06-19
*/

#include <windows.h>
#include <tchar.h>
#include <Psapi.h>
#include <tlhelp32.h>
#include <QString>
#include <QStringList>

static bool DosPathToNtPath(LPTSTR pszDosPath, LPTSTR pszNtPath)
{
    wchar_t            szDriveStr[500];
    wchar_t            szDrive[3];
    wchar_t            szDevName[100];
    INT                iDevName;
    INT                i;

    //检查参数
    if (!pszDosPath || !pszNtPath)
        return false;

    //获取本地磁盘所有盘符,以'\0'分隔,所以下面+4
    if (GetLogicalDriveStrings(sizeof(szDriveStr), szDriveStr))
    {
        for (i = 0; szDriveStr[i]; i += 4)
        {
            if (!lstrcmpi(&(szDriveStr[i]), _T("A:\\")) || !lstrcmpi(&(szDriveStr[i]), _T("B:\\")))
                continue;    //从C盘开始

            //盘符
            szDrive[0] = szDriveStr[i];
            szDrive[1] = szDriveStr[i + 1];
            szDrive[2] = '\0';
            if (!QueryDosDevice(szDrive, szDevName, 100))//查询 Dos 设备名(盘符由NT查询DOS)
                return false;

            iDevName = lstrlen(szDevName);
            if (_tcsnicmp(pszDosPath, szDevName, iDevName) == 0)//是否为此盘
            {
                lstrcpy(pszNtPath, szDrive);//复制驱动器
                lstrcat(pszNtPath, pszDosPath + iDevName);//复制路径

                return true;
            }
        }
    }

    lstrcpy(pszNtPath, pszDosPath);

    return false;
}

//获取进程完整路径
static bool GetProcessFullPath(const DWORD &dwPID, wchar_t *pszFullPath)
{
    wchar_t       szImagePath[MAX_PATH];
    //wchar_t       pszFullPath[MAX_PATH];
    HANDLE        hProcess;
    if (!pszFullPath)
        return false;

    pszFullPath[0] = '\0';

    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, 0, dwPID);    //由线程ID获得线程信息
    if (!hProcess)
        return false;

    if (!GetProcessImageFileName(hProcess, szImagePath, MAX_PATH))    //得到线程完整DOS路径
    {
        CloseHandle(hProcess);
        return false;
    }
    if (!DosPathToNtPath(szImagePath, pszFullPath))    //DOS路径转NT路径
    {
        CloseHandle(hProcess);
        return false;
    }

    CloseHandle(hProcess);

    //printf(("%5d  %ls \r\n"), dwPID, pszFullPath);
    fflush(stdout);
    return true;
}

//获取进程完整路径
static QStringList GetProcessFullPaths(const QString &name)
{
    QStringList list;
    setlocale(LC_ALL, "chs");    //不设置解析中文字符时可能会出问题
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);    //得到系统所有线程快照
    if (INVALID_HANDLE_VALUE == hSnapshot)
    {
        return list;
    }
    PROCESSENTRY32 pe;
    memset(&pe, 0, sizeof(PROCESSENTRY32));
    pe.dwSize = sizeof(PROCESSENTRY32);

    wchar_t wcName[50];
    int end = name.toWCharArray(wcName);
    wcName[end] = 0;

    BOOL fOk;
    wchar_t path[MAX_PATH];
    QString strPath;
    for (fOk = Process32First(hSnapshot, &pe); fOk; fOk = Process32Next(hSnapshot, &pe))    //遍历
    {
        if (wcscmp(wcName, pe.szExeFile) == 0) {
            GetProcessFullPath(pe.th32ProcessID, path);
            //printf(("%ls \r\n"), path);
            strPath = QString::fromWCharArray(path);
            if (list.indexOf(strPath) == -1) {
                list.append(strPath);
            }
        }
    }
    return list;
}

#endif // PROCESSINFO_H
