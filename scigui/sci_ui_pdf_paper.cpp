#include "sci_ui_pdf_paper.h"

#include "pdf_paper/sci_pdf_paper_widget.h"

namespace scigui {

sci_ui_pdf_paper::sci_ui_pdf_paper(std::string name, sci_file_model* model, scicore::sci_file* parent):sci_ui_file(model)
{
    this->_file=new scicore::sci_pdf_paper(name,parent);
    _icon = QIcon(":/gfx/icon/file_icon/pdf.png");
}

sci_ui_pdf_paper::sci_ui_pdf_paper(scicore::sci_pdf_paper* file, sci_file_model* model):sci_ui_file(model){
    this->_file = file;
    _icon = QIcon(":/gfx/icon/file_icon/pdf.png");
}

QMenu* sci_ui_pdf_paper::context_menu(QWidget* parent) {
    QMenu *qMenu = new QMenu(parent);

    QAction* exampleAction = new QAction("&Example");
    //connect(exampleAction, SIGNAL(triggered()), this, SLOT(example()));

    qMenu->addAction(exampleAction);

    return qMenu;
}

QWidget * sci_ui_pdf_paper::edit_widget(QWidget *parent) {
    sci_pdf_paper_widget* widget = new sci_pdf_paper_widget(this->_file,parent);
    return widget;
    //sci_ui_file* file = _ui_model_item->data(Qt::UserRole+1).value<sci_ui_file*>();
    //sci_ui_folder_edit_widget* edit_widget = new sci_ui_folder_edit_widget(_folder,parent);
    //return edit_widget;

}

QIcon * sci_ui_pdf_paper::file_icon(){
    return &this->_icon;
}


}

