#include "get_title.h"

int get_title(std::string file_name){
    //initialize
    Py_Initialize();
    if ( !Py_IsInitialized() )
    {
        return -1;
    }
    //import download module
    PyObject* pModule = PyImport_ImportModule("get_title");
    if (!pModule) {
            printf("Cant open python file!\n");
            return -1;
        }
    //import download from download
    PyObject* pFundownload= PyObject_GetAttrString(pModule,"get_title");

    if(!pFundownload){
        printf("Get function download failed");
        return -1;
    }
    //call download
    PyObject* args = PyTuple_New(1);

    PyObject *arg1  = Py_BuildValue("s", file_name.c_str());
    PyTuple_SetItem(args, 0, arg1);
    PyEval_CallObject(pFundownload, args);
    Py_Finalize();
    return 0;
}
