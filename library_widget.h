#ifndef LIBRARY_WIDGET_H
#define LIBRARY_WIDGET_H

#include <QMainWindow>
#include <QTreeView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

#include <QSplitter>

#include <io.h>
#include <string>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <direct.h>
#include <typeinfo>
//#include <windows.h>

#include "scigui/sci_ui_display_tab_widget.h"
#include "scigui/sci_file_model.h"
#include "scigui/sci_ui_file.h"
#include "scigui/sci_ui_lib_buffer.h"
#include "scigui/sci_ui_file_tree_view.h"

#include "scisl/sci_sl_lib.h"

#include "scirecommend/sci_r_converter.h"
#include "scirecommend/multi_input_dialog.h"

namespace Ui {
class library_widget;
}

class library_widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit library_widget(QWidget *parent = nullptr);
    ~library_widget();

private:
    Ui::library_widget *ui;

    //上方菜单栏
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *recentlyAccessedFileMenu;
    QMenu *editMenu;
    QMenu *webMenu;
    QMenu *sciManagerMenu;
    MultiInputDialog *mdialog;

    //图书馆左侧树状文件窗口
    scigui::sci_ui_file_tree_view *_tree_view;
    scigui::sci_file_model *model;

    //图书馆右侧细节窗口
    scigui::sci_ui_display_tab_widget *_tab_widget;
    //分裂器
    QSplitter * splitter;
    //最近文档
    scigui::sci_ui_lib_buffer _library_buffer;
    scisl::sci_sl_lib _lib;

private:
    void set_up_menu_bar();
    void set_up_tree_view();
    void set_up_tab_widget();
    void set_up_layout();

public slots:
    void load_lib(QString path);

    void newLibrary();
    void openLibrary();
    void parseDocument();
    void onlineImportDocument();
    void localImportDocument();
    void exportDocument();
    void save();
    void edit();
    void undo();
    void redo();
    void _delete();
    void search();
    void filter();
    void selectAll();
    void newWebDatabase();
    void openWebDatabase();
    void aboutSciManager();
    void instruction();
    void searchLine();

};

#endif // LIBRARY_WIDGET_H
