#include "sci_file.h"

#include "QDebug"
namespace scicore {

sci_file::sci_file(std::string name,sci_file* parent):
    _name(name)// , QObject(parent)
{
    _parent = parent;
}

sci_file::~sci_file(){

}

char sci_file::type(){
    return 0;
}

std::string sci_file::get_name(){
    return _name;
}

bool sci_file::set_name(std::string name){
    this->_name = name;
}

sci_file* sci_file::get_child(int index){
    return NULL;
}

int sci_file::child_count(){
    return 0;
}

sci_file* sci_file::get_parent(){
    return _parent;
}

void sci_file::set_parent(sci_file* parent){
    this->_parent = parent;
}

int sci_file::match_child(sci_file *file){
    return -1;
}

bool sci_file::insert_file(sci_file* file,int index){
    return false;
}

sci_file* sci_file::remove_file(int index){
    return NULL;
}

void sci_file::delete_file(int index){
    sci_file* file = remove_file(index);
    if(!file){
        return;
    }

    for(int i = 0; i < file->child_count(); i++){
        file->delete_file(i);
    }
    delete file;
}

void sci_file::delete_self(){

    sci_file* parent = this->get_parent();
    if(parent)
        parent->delete_file(parent->match_child(this));
    else{
        qDebug()<<"self_destroy";
        for(int i = 0; i < child_count(); i++){
            delete_file(i);
        }
        //delete this;
    }
}

bool sci_file::add_file(sci_file *file){
    insert_file(file,child_count());
}

}
