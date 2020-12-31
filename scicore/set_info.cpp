#include "set_info.h"
using namespace std;
int set_info(scicore::sci_pdf_paper & paper, std::string cache_root){
    if(paper.is_extract){
        return 0;
    }
    else{
        std::string title = paper.title;
        std::string file_name = cache_root + "\\" + title + ".json";

        Py_Initialize();
        if ( !Py_IsInitialized() ){
            return -1;
        }
        //import download module
        PyObject* pModule = PyImport_ImportModule("download");
        if (!pModule) {
                printf("Cant open python file!\n");
                return -1;
            }
        //import get_info from download
        PyObject* pFunget_info= PyObject_GetAttrString(pModule,"get_info");

        if(!pFunget_info){
            printf("Get function get_info failed");
            return -1;
        }
        //call get_info
        PyObject* args = PyTuple_New(2);

        PyObject *arg1  = Py_BuildValue("s", title.c_str());
        PyObject *arg2  = Py_BuildValue("s", cache_root.c_str());
        PyTuple_SetItem(args, 0, arg1);
        PyTuple_SetItem(args, 1, arg2);
        PyEval_CallObject(pFunget_info, args);
        Py_Finalize();
//        printf("save json successfully");
        // load info from json file
        QString qfile_name = QString::fromStdString(file_name);
//        qDebug() << qfile_name;
        QFile file(qfile_name);
        if (!file.open(QIODevice::ReadOnly)){
            printf("Unable to load JSON file");
            return -1;
        }
        QByteArray data=file.readAll();
        file.close();
        QJsonDocument doc=QJsonDocument::fromJson(data);
        if (doc.isObject()){
            QJsonObject obj=doc.object();
            QString abstract = obj.value("abstract").toString();
            QJsonArray author = obj.value("authors").toArray();
            QJsonArray field = obj.value("fieldsOfStudy").toArray();
            QString year = obj.value("year").toString();
            QString venue = obj.value("venue").toString();
            QJsonArray topic = obj.value("topics").toArray();
            paper.abstract = abstract.toStdString();
            for (QJsonArray::const_iterator iter = author.begin(); iter != author.end(); ++iter) {
                QJsonValue value = *iter;
                paper.authors.push_back(value.toString().toStdString());
            }
            for (QJsonArray::const_iterator iter = field.begin(); iter != field.end(); ++iter) {
                QJsonValue value = *iter;
                paper.fields.push_back(value.toString().toStdString());
            }
            paper.date = year.toStdString();
            paper.database = venue.toStdString();
            for (QJsonArray::const_iterator iter = topic.begin(); iter != topic.end(); ++iter) {
                QJsonValue value = *iter;
                paper.key_words.push_back(value.toString().toStdString());
            }
//            printf("finish!");
        }
    paper.is_extract = true;
    return 0;
    }
}
