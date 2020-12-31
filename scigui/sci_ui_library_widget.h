#ifndef SCI_UI_LIBRARY_WIDGET_H
#define SCI_UI_LIBRARY_WIDGET_H

#include <QMainWindow>

#include <QTreeView>

#include "sci_file_model.h"
#include "sci_ui_folder.h"

namespace Ui {
class sci_ui_library_widget;
}

namespace scigui {

/**
 * @brief 图书馆主界面
 */
class sci_ui_library_widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit sci_ui_library_widget(QString filename,QWidget *parent = nullptr);
    ~sci_ui_library_widget();

private slots:
    /**
     * @brief 双击左侧树状窗口中条目时，弹出右侧详细窗口
     * @param index
     */
    void on_treeView_library_file_tree_doubleClicked(const QModelIndex &index);
    /**
     * @brief 暂时没用
     * @param index
     */
    void on_treeView_library_file_tree_clicked(const QModelIndex &index);

    /**
     * @brief 右键单击左侧树状窗口中条目时，弹出小菜单
     * @param pos
     */
    void on_treeView_library_file_tree_customContextMenuRequested(const QPoint &pos);

    void closeEvent( QCloseEvent * event )override;
protected:
    void mousePressEvent(QMouseEvent * event);

private:
    Ui::sci_ui_library_widget *ui;

    QTreeView *treeView_library_file_tree;
    sci_file_model* model;//创建模型

    QString _filename;

};

}


#endif // SCI_UI_LIBRARY_WIDGET_H
