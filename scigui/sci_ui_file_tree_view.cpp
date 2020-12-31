#include "sci_ui_file_tree_view.h"

#include <QMouseEvent>
#include "sci_file_visitor_adaptor.h"
#include "sci_ui_file.h"

namespace scigui {

sci_ui_file_tree_view::sci_ui_file_tree_view(QWidget* parent):QTreeView(parent)
{
    setHeaderHidden(true);        //设置隐藏表头
    QFont treeFont;
    treeFont.setPointSize(14);
    setFont(treeFont);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(detail_widget_requested(QModelIndex)));

    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),this,SLOT(show_customed_menu(const QPoint &)));
}

void sci_ui_file_tree_view::mousePressEvent(QMouseEvent *event){
    QModelIndex index = this->indexAt(event->pos());
    if (index.row() == -1)
    {
        setCurrentIndex(index);
    }
    else
    {
        QTreeView::mousePressEvent(event);
    }
}

void sci_ui_file_tree_view::set_model(sci_file_model *model){
    QTreeView::setModel(model);
    this->_model = model;
}

void sci_ui_file_tree_view::detail_widget_requested(QModelIndex index){
    scicore::sci_file* file = _model->file_from_index(index);
    if(file){
        scigui::sci_ui_file* ui_file = scigui::ui_of_file(file, _model);
        //右边打开编辑窗口
        QWidget* edit_widget = ui_file->edit_widget(this);
        if(!edit_widget) return;
        emit request_show_widget(edit_widget,QString::fromStdString(file->get_name()));
    }
}

void sci_ui_file_tree_view::show_customed_menu(const QPoint & pos){
    QModelIndex index = this->indexAt(pos);

    scicore::sci_file* file = _model->file_from_index(index);
    if(file){
        scigui::sci_ui_file* ui_file = scigui::ui_of_file(file, _model);
        QMenu* menu=ui_file->context_menu(this);
        menu->exec(QCursor::pos());
    }
}

void sci_ui_file_tree_view::select_file(scicore::sci_file* file){
    QModelIndex index = _model->index_of(file);
    this->setCurrentIndex(index);
}

}

