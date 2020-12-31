#include "sci_ui_local_search_widget.h"
#include "ui_sci_ui_local_search_widget.h"

#include <vector>
#include "sci_ui_local_search_result_dialog.h"

namespace scigui {

sci_ui_local_search_widget::sci_ui_local_search_widget(sci_file_model* model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sci_ui_local_search_widget)
{
    ui->setupUi(this);
    _model = model;
}

sci_ui_local_search_widget::~sci_ui_local_search_widget()
{
    delete ui;
}

void sci_ui_local_search_widget::on_pushButton_local_search_clicked()
{
    std::vector<scicore::sci_file*> search_list = _model->search_on_name(ui->lineEdit_local_search->text().toStdString(),_model->get_root());
    sci_ui_local_search_result_dialog* dialog = new sci_ui_local_search_result_dialog(search_list,this);
    connect(dialog,SIGNAL(file_selected(scicore::sci_file*)),this,SLOT(on_file_selected(scicore::sci_file*)) );
    dialog->exec();

}

void sci_ui_local_search_widget::on_file_selected(scicore::sci_file* file){
    emit file_selected(file);
}

}

