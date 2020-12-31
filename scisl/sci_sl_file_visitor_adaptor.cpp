#include "sci_sl_file_visitor_adaptor.h"

#include "sci_sl_folder.h"
#include "sci_sl_pdf_paper.h"

namespace scisl {

sci_sl_file_visitor_adaptor::sci_sl_file_visitor_adaptor()
{

}

void sci_sl_file_visitor_adaptor::visit(scicore::sci_folder *file){
    _file = new sci_sl_folder(file);
}

void sci_sl_file_visitor_adaptor::visit(scicore::sci_pdf_file *file){
    //_file = file;
}

void sci_sl_file_visitor_adaptor::visit(scicore::sci_pdf_paper *file){
    _file = new sci_sl_pdf_paper(file);
}

sci_sl_file* sci_sl_file_visitor_adaptor::get_sl_file(scicore::sci_file *file){
    //如果已经有了储存文件，就直接返回指针
    qDebug()<<"map size:"<<sl_map.size();
    if(sl_map.contains(file)){
        return sl_map[file];
    }
    //否则创建储存文件
    file->accept_file_visitor(this);
    sl_map[file] = _file;

    return _file;
}

sci_sl_file_visitor_adaptor* sci_sl_file_visitor_adaptor::sl_of_file = NULL;

sci_sl_file_visitor_adaptor* sci_sl_file_visitor_adaptor::get_instance(){
    if(sl_of_file==NULL){
        sl_of_file = new sci_sl_file_visitor_adaptor;
    }
    return sl_of_file;

}

}

