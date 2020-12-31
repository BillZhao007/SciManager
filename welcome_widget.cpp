#include "welcome_widget.h"
#include "ui_welcome_widget.h"

welcome_widget::welcome_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::welcome_widget)
{
    ui->setupUi(this);
    this->show();
}

welcome_widget::~welcome_widget() {
    delete ui;
}

welcome_thread::welcome_thread(QObject *parent) : QThread(parent)
{
    this->start();
}

welcome_thread::~welcome_thread() {
    this->terminate();
}

void welcome_thread::run() {
    sleep(2);
    emit finish();
}
