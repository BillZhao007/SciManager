#include "sci_file_visitor_adaptor.h"
namespace scigui {
sci_file_visitor_adaptor::sci_file_visitor_adaptor()
{
    this->_ui_file = NULL;
}

void sci_file_visitor_adaptor::visit(scicore::sci_folder *file) {
    this->_ui_file = new sci_ui_folder(file);
}

void sci_file_visitor_adaptor::visit(scicore::sci_pdf_file *file) {
    //this->_ui_file = new sci_ui_folder(file);
}

void sci_file_visitor_adaptor::visit(scicore::sci_pdf_paper *file) {
    this->_ui_file = new sci_ui_pdf_paper(file);
}

sci_ui_file* sci_file_visitor_adaptor::operator()(scicore::sci_file* file){
    file->accept_file_visitor(this);
    return _ui_file;
}

sci_ui_file* sci_file_visitor_adaptor::operator()(scicore::sci_file* file,sci_file_model* model){
    file->accept_file_visitor(this);
    _ui_file->set_model(model);
    return _ui_file;
}

}

