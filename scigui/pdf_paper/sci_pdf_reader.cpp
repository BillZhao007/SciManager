#include "sci_pdf_reader.h"
#include "ui_sci_pdf_reader.h"

sci_pdf_reader::sci_pdf_reader(QString path,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sci_pdf_widget)
{
    ui->setupUi(this);

    ui->pdf_canvas->load(path);

    suit_page();

    connect(ui->pdf_canvas,SIGNAL(page_size_changed(double)),this,SLOT(set_display_ratio(double)));

    connect(ui->pdf_canvas,SIGNAL(page_size_changed(double)),this,SLOT(set_scroll_bar()));

    connect(ui->pdf_canvas,SIGNAL(canvas_size_changed()),this,SLOT(set_scroll_bar()));

}


sci_pdf_reader::~sci_pdf_reader()
{
    delete ui;
}

void sci_pdf_reader::set_display_ratio(double ratio){
    qDebug()<<"set line edit display ratio "<<ratio;
    ui->lineEdit_scale_ratio->setText(QString::number(ratio, 'f', 2));
}

void sci_pdf_reader::suit_page(){
    ui->pdf_canvas->suit_page_to_canvas();
}

void sci_pdf_reader::set_scroll_bar(){
    ui->verticalScrollBar->setMaximum(ui->pdf_canvas->get_total_height());
    ui->verticalScrollBar->setPageStep(ui->pdf_canvas->get_page_step());
    ui->verticalScrollBar->setValue(ui->pdf_canvas->get_total_y());
}

void sci_pdf_reader::on_verticalScrollBar_valueChanged(int value)
{
    ui->pdf_canvas->set_y_value(value);
    ui->pdf_canvas->paint();
}


void sci_pdf_reader::on_lineEdit_scale_ratio_returnPressed()
{
    double ratio = ui->lineEdit_scale_ratio->text().toFloat();
    qDebug()<<"ss"<<ratio;
    if(ratio<0.2){
        ratio = 0.2;
        ui->lineEdit_scale_ratio->setText(QString::number(ratio,'f',2));
    }
    if(ratio>3.0){
        ratio = 3.0;
        ui->lineEdit_scale_ratio->setText(QString::number(ratio,'f',2));
    }

    ui->pdf_canvas->scale_page(ratio);
    ui->pdf_canvas->paint();
}

void sci_pdf_reader::on_pushButton_enlarge_pdf_clicked()
{
    double ratio = ui->lineEdit_scale_ratio->text().toFloat();
    ratio+=0.2;

    ui->lineEdit_scale_ratio->setText(QString::number(ratio, 'f', 2));
    emit ui->lineEdit_scale_ratio->returnPressed();
}

void sci_pdf_reader::on_pushButton_shrink_pdf_clicked()
{
    double ratio = ui->lineEdit_scale_ratio->text().toFloat();
    ratio-=0.2;

    ui->lineEdit_scale_ratio->setText(QString::number(ratio, 'f', 2));
    emit ui->lineEdit_scale_ratio->returnPressed();
}

