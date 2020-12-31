#include "sci_ui_local_search_result_dialog.h"
#include "ui_sci_ui_local_search_result_dialog.h"

sci_ui_local_search_result_dialog::sci_ui_local_search_result_dialog(std::vector<scicore::sci_file*> list, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sci_ui_local_search_result_dialog)
{
    ui->setupUi(this);
    _list = list;
    _model = new QStandardItemModel;
    ui->listView_search_result->setModel(_model);
    ui->listView_search_result->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for( int i = 0; i < _list.size(); i++){
        std::string text;
        scicore::sci_file* file_ptr = _list[i];
        while(file_ptr->get_parent()){
            text ="\\" + file_ptr->get_name() + text;
            file_ptr = file_ptr->get_parent();
        }
        _model->appendRow(new QStandardItem(tr(text.c_str())));

    }
}

sci_ui_local_search_result_dialog::~sci_ui_local_search_result_dialog()
{
    delete ui;
}

void sci_ui_local_search_result_dialog::on_listView_search_result_doubleClicked(const QModelIndex &index)
{
    scicore::sci_file* file_ptr = _list[index.row()];
    emit file_selected(file_ptr);
}
