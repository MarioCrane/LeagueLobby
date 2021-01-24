#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QWidget>
#include <QPointer>

class QLineEdit;
class QPlainTextEdit;

class HelpWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HelpWidget(QWidget *parent = nullptr);

    void showHelp(const QString &url, const QString &json);

signals:

private:
    QPointer<QLineEdit> m_urlEdit;
    QPointer<QPlainTextEdit> m_jsonEdit;
};

#endif // HELPWIDGET_H
