#ifndef SCI_UI_LIB_BUFFER_H
#define SCI_UI_LIB_BUFFER_H

#include <QMenu>
#include <QSignalMapper>

#include "scisl/sci_sl_lib_buffer.h"



namespace scigui {

/**
 * @brief 继承于sl_lib_buffer,用于保存图书馆路径列表，并且控制与其相关的ui设置
 */
class sci_ui_lib_buffer: public QObject, public scisl::sci_sl_lib_buffer
{
    Q_OBJECT
public:
    explicit sci_ui_lib_buffer();
    /**
     * @brief 构造函数，将储存路径设为path
     * @param path
     */
    explicit sci_ui_lib_buffer(QString path);

    /**
     * @brief 获取当前情况下的菜单
     * @return
     */
    QMenu* get_lib_menu();

    /**
     * @brief 获取一个显示所有图书馆文件的表单
     * @param parent
     * @return
     */
    QDialog* get_lib_list(QWidget* parent);

public slots:

    /**
     * @brief 手动刷新菜单
     */
    void set_lib_menu();

    /**
     * @brief 直接显示一个显示所有图书馆文件的表单
     */
    void show_total_widget();
    /**
     * @brief 清空整个菜单
     */
    void clear_menu();

    /**
     * @brief 向储存中添加图书馆路径
     * @param path：路径
     * @param index：添加位置，如果为负数，则为从后往前计数
     * @return 是否成功
     */
    bool add_library(std::string path, int index = -1);

    /**
     * @brief 选中某个菜单，将发送library_selected(QString)信号
     */
    void select_library(int);
    /**
     * @brief 删除某个菜单，TODO
     */
    void delete_library(int);

signals:
    void library_selected(QString path);

private:
    QMenu* _menu;
    QSignalMapper* _mapper;
};

}



#endif // SCI_UI_LIB_BUFFER_H
