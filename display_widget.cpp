#include "display_widget.h"
#include "ui_display_widget.h"

display_widget::display_widget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::display_widget)
{
    ui->setupUi(this);

    this->setTabsClosable(true);
    connect(this,SIGNAL(tabCloseRequested(int)),this,SLOT(close_page(int)));
}

display_widget::~display_widget()
{
    delete ui;
}

void display_widget::close_page(int index){
    QWidget* widget = this->widget(index);

    if(widget){
        //this->removeTab(index);
        delete widget;
        this->removeTab(index);
    }
}
