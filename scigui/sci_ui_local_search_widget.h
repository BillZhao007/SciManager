#ifndef SCI_UI_LOCAL_SEARCH_WIDGET_H
#define SCI_UI_LOCAL_SEARCH_WIDGET_H

#include <QWidget>

#include "sci_file_model.h"

namespace Ui {
class sci_ui_local_search_widget;
}

namespace scigui {

class sci_ui_local_search_widget : public QWidget
{
    Q_OBJECT

public:
    explicit sci_ui_local_search_widget(sci_file_model* model, QWidget *parent = nullptr);
    ~sci_ui_local_search_widget();

private slots:
    void on_pushButton_local_search_clicked();

    void on_file_selected(scicore::sci_file*);
signals:
    void file_selected(scicore::sci_file*);
private:
    Ui::sci_ui_local_search_widget *ui;
    sci_file_model* _model;
};


}

#endif // SCI_UI_LOCAL_SEARCH_WIDGET_H
