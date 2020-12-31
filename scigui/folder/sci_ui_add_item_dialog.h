#ifndef SCI_UI_ADD_ITEM_DIALOG_H
#define SCI_UI_ADD_ITEM_DIALOG_H

#include "../scicore/sci_folder.h"
#include <QDialog>


namespace Ui {
class sci_ui_add_item_dialog;
}


namespace scigui {

/**
 * @brief 为图书馆添加项目的窗口，目前啥也没有（有个文件名输入框；
 */
class sci_ui_add_item_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit sci_ui_add_item_dialog(QWidget *parent = nullptr);
    ~sci_ui_add_item_dialog();

signals:
    /**
     * @brief 发送新建的文件项目
     * @param item
     */
    void emit_item( scicore::sci_file* item);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::sci_ui_add_item_dialog *ui;
};

}


#endif // SCI_UI_ADD_ITEM_DIALOG_H
