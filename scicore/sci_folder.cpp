#include "sci_folder.h"
#include "sci_file_visitor.h"

namespace scicore{
sci_folder::sci_folder(std::string name, sci_file* parent):sci_file(name,parent)
{

}

sci_folder::~sci_folder()
{

}

void sci_folder::read(std::string data){

}

std::string sci_folder::write(){
    return std::string("folder");
}

bool sci_folder::add_file(sci_file *file){
    if(!file){
        return false;
    }
    file->set_parent(this);
    this->_file_list.push_back(file);
    return true;
}

bool sci_folder::insert_file(sci_file *file, int index) {
    if(index>_file_list.size()||index<0){
        return false;
    }
    file->set_parent(this);
    this->_file_list.insert(_file_list.begin()+index,file);
    return true;
}

sci_file* sci_folder::remove_file(int index){
    if(index<0||index>=this->_file_list.size()){
        return NULL;
    }

    std::vector<sci_file*>::iterator iter = this->_file_list.begin()+index;
    sci_file* tmp = *iter;
    this->_file_list.erase(iter);
    tmp->set_parent(NULL);
    return tmp;
}
/*
bool sci_folder::delete_file(int index){
    if(index<0||index>=this->_file_list.size()){
        return false;
    }

    std::vector<sci_file*>::iterator iter = this->_file_list.begin()+index;
    sci_file* tmp = *iter;
    this->_file_list.erase(iter);
    //慎用
    delete tmp;

    return true;
}*/

int sci_folder::match_child(sci_file *file){
    int i = 0;
    for(std::vector<sci_file*>::iterator iter = this->_file_list.begin();iter!=this->_file_list.end(); iter++){
        if(*iter == file){
            return i;
        }
        i++;
    }
    return -1;
}

bool sci_folder::replace_file(int from,int to){
    if(from<0||from>=this->_file_list.size()){
        return false;
    }

    if(to<0||to>=this->_file_list.size()){
        return false;
    }

    sci_file* tmp = this->_file_list[from];
    this->_file_list[from] = this->_file_list[to];
    this->_file_list[to] = tmp;
    return true;
}

int sci_folder::child_count() {
    return this->_file_list.size();
}

sci_file* sci_folder::get_child(int index){
    if(index>=child_count()||index<0){
        return NULL;
    }
    return this->_file_list[index];
}

void sci_folder::accept_file_visitor(sci_file_visitor *visitor) {
    visitor->visit(this);
}

}
