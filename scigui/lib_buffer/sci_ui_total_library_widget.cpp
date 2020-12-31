#include "sci_ui_total_library_widget.h"
#include "ui_sci_ui_total_library_widget.h"

#include <QMessageBox>

sci_ui_total_library_widget::sci_ui_total_library_widget(scisl::sci_sl_lib_buffer *buffer, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sci_ui_total_library_widget)
{
    ui->setupUi(this);
    _model = new QStandardItemModel(this);
    ui->listView->setModel(_model);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    _buffer = buffer;
    for(int i=0; i<buffer->get_library_count(); i++){
        _model->appendRow(new QStandardItem(QString::fromStdString(buffer->get_library_path(i))));
    }

}

sci_ui_total_library_widget::~sci_ui_total_library_widget()
{
    delete ui;
}

void sci_ui_total_library_widget::on_listView_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    QString lib_name = index.data().toString();
    if(QMessageBox::question(this,"选择图书馆","确认选择图书馆："+lib_name+" ?",
                             QMessageBox::Yes |
                             QMessageBox::No,
                             QMessageBox::Yes)==
                             QMessageBox::Yes)
    {
        emit library_selected(row);
        this->close();
    }

}

void sci_ui_total_library_widget::on_pushButton_accept_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    on_listView_doubleClicked(index);
}

void sci_ui_total_library_widget::on_pushButton_cancel_clicked()
{
    this->close();
}
