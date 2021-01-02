#include "empty_detail_widget.h"
#include "ui_empty_detail_widget.h"

empty_detail_widget::empty_detail_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::empty_detail_widget)
{
    ui->setupUi(this);
}

empty_detail_widget::~empty_detail_widget()
{
    delete ui;
}
