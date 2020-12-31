#ifndef SCI_SL_FOLDER_H
#define SCI_SL_FOLDER_H

#include "sci_sl_file.h"
#include "scicore/sci_folder.h"

#include <string>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>

namespace scisl {

class sci_sl_folder:public sci_sl_file
{
public:
    sci_sl_folder(scicore::sci_folder* folder){
        _folder = folder;
    }

    void write(char* path){
        /*
        std::string content;
        for(int i = 0 ; i<_folder->child_count(); i++){
            content+=_folder->get_child(i)->get_name();
        }*/
    }

    void read(char* path){
    }

    int type(){
        return 1;
    }

    //const char* path(){
    //    return "none";
    //}

    char* desc(){
        return "no desc";
    }
protected:
    scicore::sci_folder* _folder;
};


}

#endif // SCI_SL_FOLDER_H
