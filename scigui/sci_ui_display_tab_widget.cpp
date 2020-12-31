#include "sci_ui_display_tab_widget.h"

#include <QDebug>

namespace scigui {

sci_ui_display_tab_widget::sci_ui_display_tab_widget(QWidget *parent) :
    QTabWidget(parent)
{
    this->setTabsClosable(true);
    connect(this,SIGNAL(tabCloseRequested(int)),this,SLOT(close_page(int)));
}

sci_ui_display_tab_widget::~sci_ui_display_tab_widget()
{

}

void sci_ui_display_tab_widget::close_page(int index){
    QWidget* widget = this->widget(index);

    if(widget){
        //this->removeTab(index);
        qDebug()<<"close_page"<<index;
        this->removeTab(index);
        delete widget;
    }
}

void sci_ui_display_tab_widget::add_page(QWidget* widget,QString title){
    this->addTab(widget,title);
}

}


