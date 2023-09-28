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
