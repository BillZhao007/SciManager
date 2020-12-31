#ifndef SCI_UI_FOLDER_EDIT_WIDGET_H
#define SCI_UI_FOLDER_EDIT_WIDGET_H

#include <QWidget>
#include "../scicore/sci_file.h"

namespace Ui {
class sci_ui_folder_edit_widget;
}

namespace scigui {
/**
 * @brief 文件夹详细窗口，目前啥也没有
 */
class sci_ui_folder_edit_widget : public QWidget
{
    Q_OBJECT

public:
    explicit sci_ui_folder_edit_widget(QWidget *parent = nullptr);
    explicit sci_ui_folder_edit_widget(scicore::sci_file* file,QWidget *parent = nullptr);
    ~sci_ui_folder_edit_widget();

private:
    Ui::sci_ui_folder_edit_widget *ui;
};


}


#endif // SCI_UI_FOLDER_EDIT_WIDGET_H
