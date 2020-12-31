#ifndef SCI_UI_FOLDER_H
#define SCI_UI_FOLDER_H

#include "../scicore/sci_folder.h"

#include "folder/sci_ui_add_item_dialog.h"
#include "folder/sci_ui_folder_edit_widget.h"
#include "sci_ui_file.h"



namespace scigui{

class sci_ui_folder:public sci_ui_file
{
    Q_OBJECT
public:
    /**
     * @brief 默认构造函数，将在内部创建一个新的sci_folder ！不安全，析构时不删除内存
     * @param name:folder名称
     * @param parent:父文件指针
     */
    sci_ui_folder(std::string name = "untitled",sci_file_model* model = NULL, scicore::sci_file* parent = NULL);

    /**
     * @brief 构造函数
     * @param folder
     */
    sci_ui_folder(scicore::sci_folder* folder, sci_file_model* model = NULL);

    /**
     * @brief ui_file的重载函数，控制folder项右键菜单的样式
     * @param parent：父窗口
     * @return
     */
    QMenu* context_menu(QWidget* parent) override;

    QWidget * edit_widget(QWidget *parent) override;

    QIcon * file_icon() override;
public slots:
    void example(){
        qDebug()<<"this is a QMenu Action example"<<endl;
    }
    void openAddItemWindow(){
        sci_ui_add_item_dialog* dialog = new sci_ui_add_item_dialog;
        dialog->show();
        connect(dialog,SIGNAL(emit_item(scicore::sci_file*)),this,SLOT(addItem(scicore::sci_file*)));
    }

    void addItem(scicore::sci_file* file){
        //TODO
        //这里默认是添加文件夹，后续需要补充
        this->_model->insert_file(_folder->child_count(),file,_folder);

    }

private:
    QIcon _icon;

    scicore::sci_folder* _folder;
};


}


#endif // SCI_UI_FOLDER_H
