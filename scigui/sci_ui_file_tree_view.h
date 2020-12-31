#ifndef SCI_UI_FILE_TREE_VIEW_H
#define SCI_UI_FILE_TREE_VIEW_H

#include <QTreeView>
#include "sci_file_model.h"

namespace scigui {

class sci_ui_file_tree_view : public QTreeView
{
    Q_OBJECT
public:
    sci_ui_file_tree_view(QWidget* parent = NULL);

    void mousePressEvent(QMouseEvent *event) override;

    void set_model(sci_file_model *model);

public slots:
    void detail_widget_requested(QModelIndex);

    void show_customed_menu(const QPoint &);

    void select_file(scicore::sci_file*);
signals:
    void request_show_widget(QWidget* widget, QString title);

private:
    sci_file_model* _model;
};

}



#endif // SCI_UI_FILE_TREE_VIEW_H
