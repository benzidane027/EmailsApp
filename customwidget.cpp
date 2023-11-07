#include "customwidget.h"

mQLable::mQLable(QWidget *parent) : QLabel(parent)
{
    setText("singup");
    setStyleSheet(
        "border-bottom-width: 1px;\
        border-bottom-style: solid;\
        border-radius: 0px;\
        border-bottom-color:#0074d9;\
        color: #0074d9; \
        ");
}

mQWidgetMessage::mQWidgetMessage(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("border-bottom:1.5px solid rgba(127,127,127,0.3)");
    setMinimumHeight(80);
    setMaximumHeight(100);

    //setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    //setLayout(new QVBoxLayout(parent));
    //setGeometry(QRect(0, 0, 10, 10));
    //resize(QSize(10,10));
}
