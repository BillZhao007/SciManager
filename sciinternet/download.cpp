#include "download.h"

int download(std::string title, std::string save_path){
    //initialize
    Py_Initialize();
    if ( !Py_IsInitialized() )
    {
        return -1;
    }
    //import download module
    PyObject* pModule = PyImport_ImportModule("download");
    if (!pModule) {
            printf("Cant open python file!\n");
            return -1;
        }
    //import download from download
    PyObject* pFundownload= PyObject_GetAttrString(pModule,"download");

    if(!pFundownload){
        printf("Get function download failed");
        return -1;
    }
    //call download
    PyObject* args = PyTuple_New(3);

    PyObject *arg1  = Py_BuildValue("s", title.c_str());
    PyObject *arg2  = Py_BuildValue("s", save_path.c_str());
    PyObject *arg3  = Py_BuildValue("s", "arxiv");
    PyTuple_SetItem(args, 0, arg1);
    PyTuple_SetItem(args, 1, arg2);
    PyTuple_SetItem(args, 2, arg3);
    PyEval_CallObject(pFundownload, args);
    Py_Finalize();
    return 0;
}
