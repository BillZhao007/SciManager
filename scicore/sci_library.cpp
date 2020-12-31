#include "sci_library.h"

namespace scicore {

sci_library::sci_library(){

}

void sci_library::set_root(sci_file *root){
    this->_root = root;
}


sci_file* sci_library::get_root(){
    return this->_root;
}


void _search_on_name(std::string name, sci_file *root, std::vector<sci_file*>* list){
    if(root->get_name().find(name)!=std::string::npos){
        list->push_back(root);
    }
    for(int i =0; i < root->child_count(); i++){
        _search_on_name(name,root->get_child(i),list);
    }
}

std::vector<sci_file*> sci_library::search_on_name(std::string name, sci_file *root){
    std::vector<sci_file*> list;
    _search_on_name(name,root,&list);
    return list;
}

long long sci_library::total_file(sci_file* root){
    int count = 1;
    for(int i = 0; i<root->child_count(); i++){
        count+=total_file(root->get_child(i));
    }
    return count;
}

}
