#include <Python.h>
#include "converter.h"
#include <iostream>
const int len_author = 6;    //记录作者，关键词和参考文献长短的全局变量，修改时应与python中的globals.py一同修改
const int len_key = 3;
const int len_ref = 10;

//第一个输入ip是服务器的ip地址，现阶段先用自己的电脑当服务器，展示时通过全局变量设置为静态值；第二个参量是输入的结构体指针
int  upload(char* ip, struct Information* info)                              //C++端调用的上传函数
{   
    Py_Initialize();                          //初始化python

    PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");//修改Python路径

    PyObject* pModule = PyImport_ImportModule("client");  //加载client.py模块
    PyObject* pDict = PyModule_GetDict(pModule);         //获取字典以加载函数和类
    PyObject* pClassInformation = PyDict_GetItemString(pDict, "information");   //通过模块字典调用python的information类
    PyObject* pInstanceInformation = PyInstanceMethod_New(pClassInformation);  //实例化pInformation
    //将数据写入pInformation
    PyObject_CallMethod(pInstanceInformation,"set_database", "s", info->database);
    PyObject_CallMethod(pInstanceInformation,"set_title", "s", info->title);
    PyObject_CallMethod(pInstanceInformation,"set_origin", "s", info->origin);
    PyObject_CallMethod(pInstanceInformation,"set_cite_number", "s", info->cite_number);
    PyObject_CallMethod(pInstanceInformation,"set_date", "s", info->date);
    PyObject_CallMethod(pInstanceInformation,"set_doi", "s", info->doi);
    PyObject_CallMethod(pInstanceInformation,"set_abstract", "s", info->abstract);
    //author,key_word和ref的输入是每一个元素（char*）及其和对应的指标
    for(int i=0; i < len_author; i++)     
        PyObject_CallMethod(pInstanceInformation,"set_author", "si", info->author[i],i);
    for(int i=0; i < len_key; i++)     
        PyObject_CallMethod(pInstanceInformation,"set_key_word", "si", info->key_word[i],i);
    for(int i=0; i < len_ref; i++)     
        PyObject_CallMethod(pInstanceInformation,"set_ref", "si", info->ref[i],i);

    //将pInstanceInformation作为参数，调用send_info
    PyObject* pFunc = PyObject_GetAttrString (pModule, "send_info");
    PyObject* pArgs = Py_BuildValue ("(sO)", ip, pInstanceInformation);  //两个参数建立元组
    PyObject* pRes = PyObject_CallObject (pFunc, pArgs);                      //调用函数发送,结果为是否成功
    int res = PyArg_Parse (pRes, "i", &res);        //转换返回类型
    Py_DECREF(pRes);
    Py_DECREF(pArgs);
    Py_DECREF(pFunc);
    Py_DECREF(pInstanceInformation);
    Py_DECREF(pClassInformation);
    Py_DECREF(pDict);
    Py_DECREF(pModule);
    Py_Finalize();                            //结束python解释器，释放资源

    return res;
}

//查找类似文献,info为输入的，ret为返回的信息写入的结构
int  search (char* ip, struct Information* info, struct Information* result)                             
{   
    Py_Initialize();                          //初始化python

    PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");//修改Python路径

    PyObject* pModule = PyImport_ImportModule("client");  //加载client.py模块
    PyObject* pDict = PyModule_GetDict(pModule);         //获取字典以加载函数和类
    PyObject* pClassInformation = PyDict_GetItemString(pDict, "information");   //通过模块字典调用python的information类
    PyObject* pInstanceInformation = PyInstanceMethod_New(pClassInformation);  //实例化pInformation
    //将数据写入pInformation
    PyObject_CallMethod(pInstanceInformation,"set_database", "s", info->database);
    PyObject_CallMethod(pInstanceInformation,"set_title", "s", info->title);
    PyObject_CallMethod(pInstanceInformation,"set_origin", "s", info->origin);
    PyObject_CallMethod(pInstanceInformation,"set_cite_number", "s", info->cite_number);
    PyObject_CallMethod(pInstanceInformation,"set_date", "s", info->date);
    PyObject_CallMethod(pInstanceInformation,"set_doi", "s", info->doi);
    PyObject_CallMethod(pInstanceInformation,"set_abstract", "s", info->abstract);
    //author,key_word和ref的输入是每一个元素（char*）及其和对应的指标
    for(int i=0; i < len_author; i++)     
        PyObject_CallMethod(pInstanceInformation,"set_author", "si", info->author[i],i);
    for(int i=0; i < len_key; i++)     
        PyObject_CallMethod(pInstanceInformation,"set_key_word", "si", info->key_word[i],i);
    for(int i=0; i < len_ref; i++)     
        PyObject_CallMethod(pInstanceInformation,"set_ref", "si", info->ref[i],i);

    //将pInstanceInformation作为参数，调用search_info
    PyObject* pFunc = PyObject_GetAttrString (pModule, "search_info");
    PyObject* pArgs = Py_BuildValue ("(sO)", ip, pInstanceInformation);  //两个参数建立元组
    PyObject* pRes = PyObject_CallObject (pFunc, pArgs);               //调用函数发送并搜索,结果为返回的一个Information(python中的)实例
    
    PyObject* pStr = PyObject_CallMethod(pRes, "get_database", "");    //获取python中database的str
    PyArg_ParseTuple(pStr, "s", result->database);                     //将pStr转换为char*并存入result->database
    pStr = PyObject_CallMethod(pRes, "get_cite_number", "");  
    PyArg_ParseTuple(pStr, "s", result->cite_number);
    pStr = PyObject_CallMethod(pRes, "get_title", "");  
    PyArg_ParseTuple(pStr, "s", result->title);
    pStr = PyObject_CallMethod(pRes, "get_origin", "");  
    PyArg_ParseTuple(pStr, "s", result->origin);
    pStr = PyObject_CallMethod(pRes, "get_doi", "");  
    PyArg_ParseTuple(pStr, "s", result->doi);
    pStr = PyObject_CallMethod(pRes, "get_date", "");  
    PyArg_ParseTuple(pStr, "s", result->date);
    pStr = PyObject_CallMethod(pRes, "get_origin", "");  
    PyArg_ParseTuple(pStr, "s", result->origin);
    
    for(int i=0; i<len_author; i++)
    {
        pStr = PyObject_CallMethod(pRes, "get_author", "i", i);  
        PyArg_ParseTuple(pStr, "s", result->author[i]);
    }

    for(int i=0; i<len_key; i++)
    {
        pStr = PyObject_CallMethod(pRes, "get_key_word", "i", i);  
        PyArg_ParseTuple(pStr, "s", result->key_word[i]);
    }

    for(int i=0; i<len_ref; i++)
    {
        pStr = PyObject_CallMethod(pRes, "get_ref", "i", i);  
        PyArg_ParseTuple(pStr, "s", result->ref[i]);
    }

    Py_DECREF(pStr);
    Py_DECREF(pRes);
    Py_DECREF(pArgs);
    Py_DECREF(pFunc);
    Py_DECREF(pInstanceInformation);
    Py_DECREF(pClassInformation);
    Py_DECREF(pDict);
    Py_DECREF(pModule);
    Py_Finalize();                            //结束python解释器，释放资源

    return 0;
}
