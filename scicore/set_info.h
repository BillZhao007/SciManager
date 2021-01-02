#ifndef GET_INFO_H
#define GET_INFO_H
#include <Python.h>
#include <QCoreApplication>
#include <fstream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QString>
#include <QDebug>
#include <scicore/sci_pdf_paper.h>
using namespace std;
int set_info(scicore::sci_pdf_paper & paper, std::string cache_root);

#endif // GET_INFO_H
