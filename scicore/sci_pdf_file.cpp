#include "sci_pdf_file.h"
#include "sci_file_visitor.h"

namespace scicore {

sci_pdf_file::sci_pdf_file(std::string name, sci_file* parent):sci_file(name,parent)
{

}

sci_pdf_file::sci_pdf_file(std::string name,std::string path, sci_file* parent):sci_file(name,parent),_path(path){

}

std::string sci_pdf_file::write(){
    return "pdf";
}

void sci_pdf_file::read(std::string data){

}

void sci_pdf_file::accept_file_visitor(sci_file_visitor* visitor){
    visitor->visit(this);
}

std::string sci_pdf_file::get_path(){
    return _path;
}

void sci_pdf_file::set_path(std::string path){
    _path = path;
}
}

