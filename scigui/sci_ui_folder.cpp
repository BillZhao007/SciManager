#include "sci_ui_folder.h"

namespace scigui {

sci_ui_folder::sci_ui_folder(std::string name, sci_file_model* model, scicore::sci_file* parent):sci_ui_file(model)
{
    this->_folder=new scicore::sci_folder(name,parent);
    _icon = QIcon(":/gfx/icon/file_icon/Folder_Attempt.png");
}

sci_ui_folder::sci_ui_folder(scicore::sci_folder* folder, sci_file_model* model):sci_ui_file(model){
    this->_folder = folder;
    _icon = QIcon(":/gfx/icon/file_icon/Folder_Attempt.png");
}

QMenu* sci_ui_folder::context_menu(QWidget* parent) {
    QMenu *qMenu = new QMenu(parent);

    QAction* exampleAction = new QAction("&Example");
    connect(exampleAction, SIGNAL(triggered()), this, SLOT(example()));

    QAction* addTreeItemAction = new QAction("&AddItem");
    connect(addTreeItemAction, SIGNAL(triggered()), this, SLOT(openAddItemWindow()));

    qMenu->addAction(exampleAction);
    qMenu->addAction(addTreeItemAction);

    return qMenu;
}

QWidget * sci_ui_folder::edit_widget(QWidget *parent) {
    //sci_ui_file* file = _ui_model_item->data(Qt::UserRole+1).value<sci_ui_file*>();
    sci_ui_folder_edit_widget* edit_widget = new sci_ui_folder_edit_widget(_folder,parent);
//    return edit_widget;
    return NULL;
}

QIcon * sci_ui_folder::file_icon(){
    return &this->_icon;
}



}
