#ifndef SCI_UI_LOCAL_SEARCH_RESULT_DIALOG_H
#define SCI_UI_LOCAL_SEARCH_RESULT_DIALOG_H

#include <QDialog>
#include <QList>
#include <QStandardItemModel>
#include <vector>
#include "sci_file_model.h"

namespace Ui {
class sci_ui_local_search_result_dialog;
}

class sci_ui_local_search_result_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit sci_ui_local_search_result_dialog(std::vector<scicore::sci_file*> list, QWidget *parent = nullptr);
    ~sci_ui_local_search_result_dialog();

private slots:
    void on_listView_search_result_doubleClicked(const QModelIndex &index);

signals:
    void file_selected(scicore::sci_file*);
private:
    Ui::sci_ui_local_search_result_dialog *ui;
    std::vector<scicore::sci_file*> _list;

    QStandardItemModel* _model;
};

#endif // SCI_UI_LOCAL_SEARCH_RESULT_DIALOG_H
