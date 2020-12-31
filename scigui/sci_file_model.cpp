#include "sci_file_model.h"

#include "sci_file_visitor_adaptor.h"

namespace scigui {

sci_file_model::sci_file_model(QObject *parent):QAbstractItemModel(parent)
{
    _root = NULL;

    stack_size = 3;
    stack_ptr = 0;
}

sci_file_model::~sci_file_model()
{
    _root->delete_self();
    delete _root;
}


scicore::sci_file* sci_file_model::file_from_index(const QModelIndex &index) const{

    if (index.isValid()) {
        scicore::sci_file* file = static_cast<scicore::sci_file *>(index.internalPointer());
        if(file)
            return file;
    }

    return _root;

}

QModelIndex sci_file_model::index_of(scicore::sci_file* file){
    if(file){
        scicore::sci_file* parent = file->get_parent();
        if(parent){
            int row = file->get_parent()->match_child(file);
            return createIndex(row,0,file);
        }
    }
    return QModelIndex();
}


QModelIndex sci_file_model::index(int row, int column, const QModelIndex &parent) const{
    if (parent.isValid() && column != 0)
        return QModelIndex();
    scicore::sci_file *parent_file = file_from_index(parent);
    //qDebug()<<"ss";
    if(!parent_file){
        return QModelIndex();
    }
    scicore::sci_file *child_file = parent_file->get_child(row);

    if (child_file)
        return createIndex(row, column, child_file);
    return QModelIndex();

}



QModelIndex sci_file_model::parent(const QModelIndex &child) const{
    if(!child.isValid()){
        return QModelIndex();
    }
    scicore::sci_file *node = file_from_index(child);
    if (!node)
        return QModelIndex();
    scicore::sci_file *parentNode = node->get_parent();
    if (!parentNode)
        return QModelIndex();
    scicore::sci_file *grandparentNode = parentNode->get_parent();
    if (!grandparentNode)
        return QModelIndex();

    int row = grandparentNode->match_child(parentNode);
    return createIndex(row, 0, parentNode);
}

int sci_file_model::rowCount(const QModelIndex &parent) const{

    scicore::sci_file *parent_file = file_from_index(parent);
    if (!parent_file)
        return 0;
    return parent_file->child_count();
}

int sci_file_model::columnCount(const QModelIndex &parent) const{
    return 1;
}

QVariant sci_file_model::data(const QModelIndex &index, int role) const{
    if (!index.isValid()) {
        return QVariant();
    }

    switch (role) {
    case Qt::TextAlignmentRole:{
        return int(Qt::AlignLeft | Qt::AlignVCenter);
        break;
    }

    case Qt::DisplayRole:{

        scicore::sci_file* node = file_from_index(index);

        return QString::fromStdString(node->get_name());
        break;
    }

    case Qt::DecorationRole:{
        scicore::sci_file* node = file_from_index(index);

        return QVariant(*(ui_of_file(node)->file_icon()));
    }

    default:{
        return QVariant();
    }
    }

    return QVariant();
}

QVariant sci_file_model::headerData(int section, Qt::Orientation orientation, int role) const{
    //返回 section列处的列名
    if(role == Qt::DisplayRole && section == 0 && orientation == Qt::Horizontal)
        return QVariant("file name");
    return QVariant();
}

Qt::ItemFlags sci_file_model::flags(const QModelIndex &index) const{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if (index.column()==0) {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

bool sci_file_model::setData(const QModelIndex &index, const QVariant &value, int role){
    if(!index.isValid())
        return false;

    if(index.column()>0)
        return false;

    if(role == Qt::DisplayRole){
        scicore::sci_file* node = file_from_index(index);
        node->set_name( value.toString().toStdString() );
        emit dataChanged(index,index,{Qt::DisplayRole, Qt::EditRole});
        return true;
    }

    return false;
}

void sci_file_model::clear(){
    if(_root){
        _root->delete_self();
        delete _root;
        _root = NULL;
    }
    emit layoutChanged();

}

void sci_file_model::set_root(scicore::sci_file *root){
    //clear();
    this->_root = root;
    qDebug()<<"Model Root Set!";
    //emit dataChanged(index_of(root),index_of(root),{Qt::DisplayRole, Qt::EditRole});
    emit layoutChanged();
}

bool sci_file_model::insert_file(int row, scicore::sci_file* file, scicore::sci_file *parent,bool into_stack) {
    if(!parent){
        return false;
    }
    if(!file){
        return false;
    }
    emit layoutAboutToBeChanged();
    parent->insert_file(file,row);
    if(into_stack){
        _push(row,file,parent,INSERT);
    }
    emit layoutChanged();

    return true;
}

bool sci_file_model::insert_file(int row, scicore::sci_file* file, const QModelIndex &parent) {

    scicore::sci_file* parent_file = file_from_index(parent);

    return insert_file(row,file,parent_file);
}

scicore::sci_file* sci_file_model::remove_file(int row,const QModelIndex &parent){
    scicore::sci_file* parent_file = file_from_index(parent);

    scicore::sci_file* file = remove_file(row,parent_file);

    return file;
}
scicore::sci_file* sci_file_model::remove_file(int row, scicore::sci_file *parent, bool into_stack){
    if(!parent){
        return NULL;
    }
    if(parent->child_count()<=row||0>row){
        return NULL;
    }


    emit layoutAboutToBeChanged();
    scicore::sci_file* file = parent->remove_file(row);
    if(into_stack){
       _push(row,file,parent,REMOVE);
    }

    emit layoutChanged();

    return file;
}

bool sci_file_model::add_file(scicore::sci_file* file, scicore::sci_file* parent){
    return insert_file(parent->child_count(),file,parent);
}

void sci_file_model::_push(int row, scicore::sci_file *file, scicore::sci_file *parent, file_operation operation){
    if(stack_ptr<_file_stack.size()){
        //如果已经undo过，那么就把undo之后的记录全删了
        for(int i = stack_ptr; i <_file_stack.size() ; i++){
            _file_stack.removeAt(i);
        }

    }


    if(_file_stack.size()>=stack_size){
        _file_stack.pop_front();
        _parent_stack.pop_front();
        _row_stack.pop_front();
        _operation_stack.pop_front();
        stack_ptr--;
    }

    _file_stack.push_back(file);
    _parent_stack.push_back(parent);
    _row_stack.push_back(row);
    _operation_stack.push_back(operation);
    stack_ptr++;
}

void sci_file_model::undo(){
    if(stack_ptr<=0){
        return;
    }
    stack_ptr--;
    scicore::sci_file* file= *(_file_stack.begin()+stack_ptr);
    scicore::sci_file* parent= *(_parent_stack.begin()+stack_ptr);
    int row = *(_row_stack.begin()+stack_ptr);
    file_operation operation = *(_operation_stack.begin()+stack_ptr);

    if(operation == INSERT){
        //如果操作为添加文件，那么移除该文件
        remove_file(row,parent,false);

    }
    else if(operation == REMOVE){
        //如果操作为删除文件，那么重新添加该文件
        insert_file(row,file,parent,false);

    }

}

void sci_file_model::redo(){
    if(stack_ptr>=_file_stack.size()){
        return;
    }
    scicore::sci_file* file= *(_file_stack.begin()+stack_ptr);
    scicore::sci_file* parent= *(_parent_stack.begin()+stack_ptr);
    int row = *(_row_stack.begin()+stack_ptr);
    file_operation operation = *(_operation_stack.begin()+stack_ptr);

    if(operation == INSERT){
        //如果操作为添加文件，那么移除该文件
        insert_file(row,file,parent,false);

    }
    else if(operation == REMOVE){
        //如果操作为删除文件，那么重新添加该文件
        remove_file(row,parent,false);

    }
    stack_ptr++;
}

}
