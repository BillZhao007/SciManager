#include "sci_sl_file.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QDateTime>

namespace scisl {

sci_sl_file::sci_sl_file()
{
    _savepath = "";
}

int indepandent_id = 0;

const char* sci_sl_file::path(){
    if(_savepath.empty()){
        QDateTime current_date_time =QDateTime::currentDateTime();
        QString current_date =current_date_time.toString("yyyyMMddhhmmsszzz") + QString::number(indepandent_id++) + ".info";
        _savepath = current_date.toStdString();
    }

    return _savepath.c_str();
}

void sci_sl_file::set_path(std::string path){
    _savepath = (char*)path.c_str();
}

}
