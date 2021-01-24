#ifndef STYLESHEET_H
#define STYLESHEET_H

#include <QString>

const QString WidgetStyleSheet = R"(
QWidget {
background-color: #FFFFFF;
}
)";

const QString ButtonStyleSheet = R"(
QPushButton {
min-width: 80px;
min-height: 30px;
max-height: 30px;

background: qlineargradient(x1: 0, x2: 1,
stop: 0 rgb(100, 140, 222), stop: 1.0 rgb(100, 100, 222));
color: #FFFFFF;
border: none;
border-radius: 3px;
}
QPushButton#btn_select {
min-width: 25px;
max-width: 25px;
min-height: 25px;
max-height: 25px;

background: qlineargradient(x1: 0, x2: 1,
stop: 0 rgb(100, 140, 222), stop: 1.0 rgb(100, 100, 222));
color: #FFFFFF;
border: none;
border-radius: 3px;
}
QPushButton:hover {
background: qlineargradient(x1: 0, x2: 1,
stop: 0 rgb(120, 160, 242), stop: 1.0 rgb(120, 120, 242));
}
QPushButton:hover#btn_select {
background: qlineargradient(x1: 0, x2: 1,
stop: 0 rgb(120, 160, 242), stop: 1.0 rgb(120, 120, 242));
}
QPushButton:pressed {
background: qlineargradient(x1: 0, x2: 1,
stop: 0 rgb(80, 120, 202), stop: 1.0 rgb(80, 80, 202));
}
QPushButton:pressed#btn_select {
background: qlineargradient(x1: 0, x2: 1,
stop: 0 rgb(80, 120, 202), stop: 1.0 rgb(80, 80, 202));
}
)";

const QString HelpStyleSheet = R"(
QPushButton {
min-width: 25px;
max-width: 25px;
min-height: 25px;
max-height: 25px;

image: url(:/resources/images/help.png);
background: qlineargradient(x1: 0, x2: 1,
stop: 0 rgb(100, 140, 222), stop: 1.0 rgb(100, 100, 222));
color: #FFFFFF;
border: none;
border-radius: 3px;
}
QPushButton:hover {
background: qlineargradient(x1: 0, x2: 1,
stop: 0 rgb(120, 160, 242), stop: 1.0 rgb(120, 120, 242));
}
QPushButton:pressed {
background: qlineargradient(x1: 0, x2: 1,
stop: 0 rgb(80, 120, 202), stop: 1.0 rgb(80, 80, 202));
}
)";

const QString RefreshStyleSheet = R"(
QPushButton {
min-width: 25px;
max-width: 25px;
min-height: 25px;
max-height: 25px;

image: url(:/resources/images/refresh.png);
background: qlineargradient(x1: 0, x2: 1,
stop: 0 rgb(100, 140, 222), stop: 1.0 rgb(100, 100, 222));
color: #FFFFFF;
border: none;
border-radius: 3px;
}
QPushButton:hover {
background: qlineargradient(x1: 0, x2: 1,
stop: 0 rgb(120, 160, 242), stop: 1.0 rgb(120, 120, 242));
}
QPushButton:pressed {
background: qlineargradient(x1: 0, x2: 1,
stop: 0 rgb(80, 120, 202), stop: 1.0 rgb(80, 80, 202));
}
)";

const QString LineEditStyleSheet = R"(
QLineEdit {
min-height: 25px;
max-height: 25px;

background-color: #FFFFFF;
color: #000000;
border: none;
border-radius: 3px;
padding: 2px;
}
)";

const QString ToolTipStyleSheet = R"(
QToolTip {
border: 1px solid rgb(118, 118, 118);
background-color: #ffffff;
color: #484848;
font-size: 12px;
}
)";

#endif // STYLESHEET_H
