#ifndef SCI_FILE_VISITOR_ADAPTOR_H
#define SCI_FILE_VISITOR_ADAPTOR_H


#include "../scicore/sci_file_visitor.h"
#include "sci_ui_folder.h"
#include "sci_ui_pdf_paper.h"

namespace scigui{

/**
 * @brief 用作file系统visitor的适配器层，当增加file的子类并且需要ui显示时，需在本类中增加对应visit函数的重载，函数参数为对应子类（同时在file的visitor中也要增加visit函数的重载
 */
class sci_file_visitor_adaptor:public scicore::sci_file_visitor{
public:
    sci_file_visitor_adaptor();

    void visit(scicore::sci_folder *file) override;

    void visit(scicore::sci_pdf_file *file) override;

    void visit(scicore::sci_pdf_paper *file) override;

    sci_ui_file* operator()(scicore::sci_file* file);

    sci_ui_file* operator()(scicore::sci_file* file,sci_file_model* model);

private:
    sci_ui_file* _ui_file;
};

/**
 * @brief 伪函数，用于获得file的对应ui_file指针
 */
static sci_file_visitor_adaptor ui_of_file;

}



#endif // SCI_FILE_VISITOR_ADAPTOR_H
