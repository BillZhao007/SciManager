#include "sci_sl_lib_buffer.h"

#include <QMessageBox>

namespace scisl {

sci_sl_lib_buffer::sci_sl_lib_buffer()
{

}

sci_sl_lib_buffer::sci_sl_lib_buffer(std::string path){
    set_path(path);
}

sci_sl_lib_buffer::~sci_sl_lib_buffer(){
    //save();
}

bool sci_sl_lib_buffer::add_library(std::string path, int index){
    int true_index = index>=0?index:_name_list.size()+index+1;
    //检查合法性
    if(true_index<0||true_index>_name_list.size()){
        return false;
    }
    //检查是否重复
    for(int i = 0; i<_name_list.size(); i++){
        if(path == _name_list[i]){
            return false;
        }
    }

    _name_list.insert(_name_list.begin()+true_index,path);
    return true;
}

void sci_sl_lib_buffer::clear_all(){
    _name_list.clear();
}

int sci_sl_lib_buffer::get_library_count(){
    return _name_list.size();
}

std::string sci_sl_lib_buffer::get_library_path(int index){
    int true_index = index>=0?index:_name_list.size()+index;
    //检查合法性
    if(true_index<0||true_index>=_name_list.size()){
        return "";
    }

    return _name_list[true_index];
}

void sci_sl_lib_buffer::save(){
    //依次存储图书馆路径
    QJsonArray lib_array;
    for(int i = 0; i < _name_list.size(); i++){
        QJsonObject lib_obj;
        //存入信息
        lib_obj["path"] = QString::fromStdString(_name_list[i]);

        lib_array.append(lib_obj);
    }
    QJsonObject obj;
    obj["library"] = lib_array;

    QJsonDocument jdoc;
    jdoc.setObject(obj);

    //打开文件
    QFile file(QString::fromStdString(_path));
    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(NULL,"错误","错误：写入失败，图书馆列表文件失效！路径："+QString::fromStdString(_path));
        //qDebug() << "File open failed! path: " << QString::fromStdString(_path);
        return;
    } else {
        //qDebug() <<"File open successfully!" << QString::fromStdString(_path);;
    }

    file.write(jdoc.toJson(QJsonDocument::Indented)); //Indented:表示自动添加/n回车符
    file.close();
}

void sci_sl_lib_buffer::load(){
    //清空存储
    _name_list.clear();
    //读取文件
    QFile file(QString::fromStdString(_path));
    if(!file.open(QIODevice::ReadOnly)) {
        //QMessageBox::critical(NULL,"错误","错误：读取失败，图书馆列表文件失效！路径："+QString::fromStdString(_path));
        //qDebug() << "File open failed! path: "<<QString::fromStdString(_path);
        return;
    } else {
        qDebug() <<"File open successfully!"<<QString::fromStdString(_path);
    }
    QJsonParseError *error=new QJsonParseError;
    QJsonDocument jdc=QJsonDocument::fromJson(file.readAll(),error);
    file.close();
    //判断文件是否完整，如果不存在文件，可能会在这里报错
    if(error->error!=QJsonParseError::NoError)
    {
      qDebug()<<"parseJson:"<<error->errorString()<<QString::fromStdString(_path);
      return;
    }

    QJsonObject obj = jdc.object();

    QJsonArray lib_array = obj["library"].toArray();

    for(int i = 0; i < lib_array.size(); i++){
        QJsonObject file_obj(lib_array[i].toObject());
        _name_list.push_back(file_obj["path"].toString().toStdString());
        //qDebug()<<"lib_path"<<file_obj["path"].toString();
    }
}


}
