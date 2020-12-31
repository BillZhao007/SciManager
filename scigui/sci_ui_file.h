#ifndef SCI_UI_FILE_H
#define SCI_UI_FILE_H


#include <QDebug>
#include <QVariant>
#include <QMenu>
#include <QIcon>

#include "sci_file_model.h"

namespace scigui {

class sci_file_visitor_adaptor;

/**
 * @brief 文件的ui表示类，控制用户界面中文件的互动
 */

class sci_ui_file:public QObject
{
    Q_OBJECT
public:
    sci_ui_file(sci_file_model* model = NULL);
    //sci_ui_file(sci_file* item):_ui_m(item){};
    /**
     * @brief 纯虚函数，所有需要在ui界面中显示的文件类都需重载此函数，用于指定在树状列表中右键该文件弹出的菜单样式
     * @param 父对象
     * @return
     */
    virtual QMenu* context_menu(QWidget* parent)=0;

    /**
     * @brief 纯虚函数，所有需要在ui界面中显示的文件类都需重载此函数，用于指定在树状列表中左键双击该文件时，右侧详细信息窗口的样式
     * @param 父对象
     * @return
     */
    virtual QWidget* edit_widget(QWidget* parent)=0;

    /**
     * @brief 纯虚函数，所有需要在ui界面中显示的文件类都需重载此函数，用于指定在左侧文件树中的文件图标
     * @return
     */
    virtual QIcon * file_icon()=0;

    virtual void set_model(sci_file_model* model);
protected:
    sci_file_model* _model;
};

}


#endif // SCI_UI_FILE_H
