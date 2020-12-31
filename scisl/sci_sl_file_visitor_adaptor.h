#ifndef SCI_SL_FILE_VISITOR_ADAPTOR_H
#define SCI_SL_FILE_VISITOR_ADAPTOR_H

#include <QMap>

#include "scicore/sci_file_visitor.h"
#include "sci_sl_file.h"


namespace scisl {

class sci_sl_file_visitor_adaptor:public scicore::sci_file_visitor
{
public:
    sci_sl_file_visitor_adaptor();

    void visit(scicore::sci_folder *file) override;

    void visit(scicore::sci_pdf_file *file) override;

    void visit(scicore::sci_pdf_paper *file) override;

    sci_sl_file* get_sl_file(scicore::sci_file* file);


    static sci_sl_file_visitor_adaptor* get_instance();
    /**
     * @brief 伪函数，用于获得file的对应ui_file指针
     */
    //static  sl_of_file;

private:
    QMap<scicore::sci_file*,sci_sl_file*> sl_map;

    sci_sl_file* _file;
    static sci_sl_file_visitor_adaptor* sl_of_file;
    //scisl::sci_sl_file* _file;
};




}




#endif // SCI_SL_FILE_VISITOR_ADAPTOR_H
