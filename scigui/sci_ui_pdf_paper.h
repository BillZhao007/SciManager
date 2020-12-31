#ifndef SCI_UI_PDF_PAPER_H
#define SCI_UI_PDF_PAPER_H

#include "scicore/sci_pdf_paper.h"

#include "sci_ui_file.h"


namespace scigui {

class sci_ui_pdf_paper :public sci_ui_file
{
public:
    /**
     * @brief 默认构造函数，将在内部创建一个新的sci_folder ！不安全，析构时不删除内存
     * @param name:folder名称
     * @param parent:父文件指针
     */
    sci_ui_pdf_paper(std::string name = "untitled",sci_file_model* model = NULL, scicore::sci_file* parent = NULL);

    /**
     * @brief 构造函数
     * @param folder
     */
    sci_ui_pdf_paper(scicore::sci_pdf_paper* file, sci_file_model* model = NULL);

    /**
     * @brief ui_file的重载函数，控制folder项右键菜单的样式
     * @param parent：父窗口
     * @return
     */
    QMenu* context_menu(QWidget* parent) override;

    QWidget * edit_widget(QWidget *parent) override;

    QIcon * file_icon() override;

protected:
    QIcon _icon;

    scicore::sci_pdf_paper* _file;
};

}


#endif // SCI_UI_PDF_PAPER_H
