#ifndef SCI_SL_PDF_PAPER_H
#define SCI_SL_PDF_PAPER_H

#include "sci_sl_file.h"
#include "scicore/sci_pdf_paper.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>

namespace scisl{

class sci_sl_pdf_paper:public sci_sl_file
{
public:
    sci_sl_pdf_paper(scicore::sci_pdf_paper* paper){
        _paper = paper;
    }

    void write(char* path){
        QFile file(QString::fromStdString(path));

        if(!file.open(QIODevice::WriteOnly)) {
            qDebug() << "File open failed! save path: "<<QString(path);
            return;
        } else {
            qDebug() <<"File open successfully! save path"<<QString(path);
        }

        QJsonObject obj;

        obj["database"] = QString::fromStdString(_paper->database);
        obj["title"] = QString::fromStdString(_paper->title);

        QJsonArray author_array;
        for(int i = 0; i < _paper->authors.size(); i++){
            QJsonObject author_obj;
            author_obj["name"] = QString::fromStdString(_paper->authors[i]);
            author_array.append(author_obj);
        }
        obj["authors"] = author_array;

        QJsonArray key_words_array;
        for(int i = 0; i < _paper->key_words.size(); i++){
            QJsonObject key_word_obj;
            key_word_obj["name"] = QString::fromStdString(_paper->key_words[i]);
            key_words_array.append(key_word_obj);
        }
        obj["key_words"] = key_words_array;

        obj["origin"] = QString::fromStdString(_paper->origin);
        obj["date"] = QString::fromStdString(_paper->date);
        obj["citation_times"] = _paper->citation_times;
        obj["id"] = QString::fromStdString(_paper->id);
        obj["abstract"] = QString::fromStdString(_paper->abstract);

        QJsonDocument jdoc;
        jdoc.setObject(obj);
        file.write(jdoc.toJson(QJsonDocument::Indented)); //Indented:表示自动添加/n回车符
        file.close();

    }

    void read(char* path){
        QFile file(QString::fromStdString(path));
        if(!file.open(QIODevice::ReadOnly)) {
            qDebug() << "File open failed! path: "<<QString::fromStdString(path);
            return;
        } else {
            qDebug() <<"File open successfully!"<<QString::fromStdString(path);
        }
        QJsonParseError *error=new QJsonParseError;
        QJsonDocument jdc=QJsonDocument::fromJson(file.readAll(),error);
        file.close();
        //判断文件是否完整
        if(error->error!=QJsonParseError::NoError)
        {
          qDebug()<<"parseJson:"<<error->errorString();
          return;
        }

        QJsonObject obj = jdc.object();

        _paper->database = obj["database"].toString().toStdString();
        _paper->title = obj["title"].toString().toStdString();
        _paper->authors.clear();
        QJsonArray author_array = obj["author"].toArray();
        for(int i = 0; i< author_array.size(); i++){
            QJsonObject author_obj(author_array[i].toObject());
            _paper->authors.push_back(author_obj["name"].toString().toStdString());
        }
        _paper->key_words.clear();
        QJsonArray key_words_array = obj["key_words"].toArray();
        for(int i = 0; i< key_words_array.size(); i++){
            QJsonObject key_word_obj(key_words_array[i].toObject());
            _paper->authors.push_back(key_word_obj["name"].toString().toStdString());
        }
        _paper->origin = obj["origin"].toString().toStdString();
        _paper->date = obj["date"].toString().toStdString();
        _paper->citation_times = obj["citation_times"].toInt();
        _paper->id = obj["id"].toString().toStdString();
        _paper->abstract = obj["abstract"].toString().toStdString();

    }

    int type(){
        return 2;
    }

    //char* path(){
    //    return (char*)std::string("data/pp/"+_paper->get_name()+".pp").c_str();
    //}

    char* desc(){
        return (char*)_paper->get_path().c_str();
    }

private:
    scicore::sci_pdf_paper* _paper;

};


}


#endif // SCI_SL_PDF_PAPER_H
