#include "helpwidget.h"

#include <QLineEdit>
#include <QPlainTextEdit>
#include <QVBoxLayout>

HelpWidget::HelpWidget(QWidget *parent)
    : QWidget(parent)
    , m_urlEdit(new QLineEdit(this))
    , m_jsonEdit(new QPlainTextEdit(this))
{
    m_urlEdit->setReadOnly(true);
    m_jsonEdit->setReadOnly(true);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_urlEdit);
    mainLayout->addWidget(m_jsonEdit);
    this->setLayout(mainLayout);
    this->hide();
}

void HelpWidget::showHelp(const QString &url, const QString &json)
{
    m_urlEdit->setText(url);
    m_jsonEdit->setPlainText(json);
    this->show();
}
