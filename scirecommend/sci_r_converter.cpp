#include "sci_r_converter.h"
using namespace std;

const char* null_c = "&";
const int len_author = 6;
const int len_key = 7;
const int len_field = 3;
const int len_ref = 10;
const char* suc_msg = "OK";
const char* err_msg = "error";
std::string null_str = std::string(null_c);

namespace sci_r{

std::string Nullize(std::string &content){
    if(content == "") return null_str;
    else return content;
}

bool upload_single(scicore::sci_pdf_paper &paper) {
    Py_Initialize();
    if (!Py_IsInitialized()) return false;
    PyObject* pModule = PyImport_ImportModule("converter");
    if (!pModule) {
        qDebug()<< "Cant open python file converter.py\n" << endl;
        return false;
    }

    PyObject* pFunUploadInfo = PyObject_GetAttrString(pModule,"send_converter");
    if(!pFunUploadInfo){
        qDebug()<<"Get function send_converter failed"<<endl;
        return false;
    }

    PyObject* args = PyTuple_New(7+len_author+len_key+len_field+len_ref);

    PyObject *auth[len_author], *kw[len_key], *f[len_field];

    PyObject *db = Py_BuildValue("s", Nullize(paper.database).c_str());
    PyObject *t  = Py_BuildValue("s", Nullize(paper.title).c_str());
    PyObject *ori  = Py_BuildValue("s", Nullize(paper.origin).c_str());
    PyObject *date  = Py_BuildValue("s", Nullize(paper.date).c_str());
    PyObject *c  = Py_BuildValue("s", to_string(paper.citation_times).c_str());
    PyObject *id  = Py_BuildValue("s", Nullize(paper.id).c_str());
    PyObject *ab  = Py_BuildValue("s", Nullize(paper.abstract).c_str());
    PyObject *ref[len_ref];
    for(int i=0; i<len_ref; i++)
        ref[i] = Py_BuildValue("s", null_c);

    if(paper.authors.size() <= len_author) {
        for(int i=0; i<paper.authors.size(); i++)
            auth[i] = Py_BuildValue("s", paper.authors[i].c_str());
        for(int i=paper.authors.size(); i<len_author; i++)
            auth[i] = Py_BuildValue("s", null_c);
    }
    else {
        for(int i=0; i<len_author-1; i++)
            auth[i] = Py_BuildValue("s", paper.authors[i].c_str());
        auth[len_author-1] = Py_BuildValue("s", paper.authors[paper.authors.size()-1].c_str());
    }

    if(paper.key_words.size() <= len_key) {
        for(int i=0; i<paper.key_words.size(); i++)
            kw[i] = Py_BuildValue("s", paper.key_words[i].c_str());
        for(int i=paper.key_words.size(); i<len_key; i++)
            kw[i] = Py_BuildValue("s", null_c);
    }
    else {
        for(int i=0; i<len_key; i++)
            kw[i] = Py_BuildValue("s", paper.key_words[i].c_str());
    }

    if(paper.fields.size() <= len_field) {
        for(int i=0; i<paper.fields.size(); i++)
            f[i] = Py_BuildValue("s", paper.fields[i].c_str());
        for(int i=paper.fields.size(); i<len_field; i++)
            f[i] = Py_BuildValue("s", null_c);
    }
    else {
        for(int i=0; i<len_field; i++)
            f[i] = Py_BuildValue("s", paper.fields[i].c_str());
    }

    PyTuple_SetItem(args, 0, db);
    PyTuple_SetItem(args, 1, c);
    PyTuple_SetItem(args, 2, t);
    for(int i=0; i<len_author; i++)
        PyTuple_SetItem(args, 3+i, auth[i]);
    for(int i=0; i<len_key; i++)
        PyTuple_SetItem(args, 3+len_author+i, kw[i]);
    PyTuple_SetItem(args, 3+len_author+len_key, ori);
    PyTuple_SetItem(args, 4+len_author+len_key, date);
    for(int i=0; i<len_ref; i++)
        PyTuple_SetItem(args, 5+len_author+len_key+i, ref[i]);
    PyTuple_SetItem(args, 5+len_author+len_key+len_ref, id);
    PyTuple_SetItem(args, 6+len_author+len_key+len_ref, ab);
    for(int i=0; i<len_field; i++)
        PyTuple_SetItem(args, 7+len_author+len_key+len_ref+i, f[i]);

    PyEval_CallObject(pFunUploadInfo, args);
    Py_Finalize();
    return true;
}

//pair<int,int> upload_multiple(){

//}

bool sci_pdf_paper_input(scicore::sci_pdf_paper &paper, std::string &str) {
    if(str == "") return false;
    std::vector<std::string> after_split;

    char *strs = new char[str.length() + 1];
    strcpy(strs, str.c_str());
    char * d = "|";
    char *p = strtok(strs, d);
    while(p) {
        string s = p; //分割得到的字符串转换为string类型
        after_split.push_back(s); //存入结果数组
        p = strtok(NULL, d);
    }

    if(after_split.size() != 6+len_author+len_key+len_field+len_ref) return false;
    paper.database = after_split[0];
    paper.citation_times = atoi(after_split[1].c_str());
    paper.title = after_split[2];
    paper.authors.clear();
    for(int i=0; i<len_author; i++)
        paper.authors.push_back(after_split[3+i]);
    paper.key_words.clear();
    for(int i=0; i<len_key; i++)
        paper.key_words.push_back(after_split[3+len_author+i]);
    paper.origin = after_split[3+len_author+len_key];
    paper.date = after_split[4+len_author+len_key];
    paper.id = after_split[5+len_author+len_key+len_ref];
    paper.fields.clear();
    for(int i=0; i<len_field; i++)
        paper.fields.push_back(after_split[6+len_author+len_key+len_ref+i]);
    return true;
}

std::vector<scicore::sci_pdf_paper> recommend(scicore::sci_pdf_paper &paper, weight wt, int rec) {
    std::vector<scicore::sci_pdf_paper> res;
    std::string cache_pth = "./cache";
    Py_Initialize();
    if (!Py_IsInitialized()) return res;
    PyObject* pModule = PyImport_ImportModule("converter");
    if (!pModule) {
        qDebug()<< "Cant open python file converter.py\n" << endl;
        return res;
    }

    PyObject* pFunUploadInfo = PyObject_GetAttrString(pModule,"search_converter");
    if(!pFunUploadInfo){
        qDebug()<<"Get function search_converter failed"<<endl;
        return res;
    }

    PyObject* args = PyTuple_New(15+len_author+len_key+len_field+len_ref);

    PyObject *auth[len_author], *kw[len_key], *f[len_field], *ref[len_ref];

    PyObject *db = Py_BuildValue("s", Nullize(paper.database).c_str());
    PyObject *t  = Py_BuildValue("s", Nullize(paper.title).c_str());
    PyObject *ori  = Py_BuildValue("s", Nullize(paper.origin).c_str());
    PyObject *date  = Py_BuildValue("s", Nullize(paper.date).c_str());
    PyObject *c  = Py_BuildValue("s", to_string(paper.citation_times).c_str());
    PyObject *id  = Py_BuildValue("s", Nullize(paper.id).c_str());
    PyObject *ab  = Py_BuildValue("s", Nullize(paper.abstract).c_str());
    PyObject *wt_db = Py_BuildValue("s", to_string(wt.database).c_str());
    PyObject *wt_aut = Py_BuildValue("s", to_string(wt.author).c_str());
    PyObject *wt_kw = Py_BuildValue("s", to_string(wt.keyword).c_str());
    PyObject *wt_ori = Py_BuildValue("s", to_string(wt.origin).c_str());
    PyObject *wt_ref = Py_BuildValue("s", to_string(wt.ref).c_str());
    PyObject *wt_f = Py_BuildValue("s", to_string(wt.field).c_str());
    PyObject *c_pth = Py_BuildValue("s", cache_pth.c_str());
    PyObject *rec_n = Py_BuildValue("s", to_string(rec).c_str());
    for(int i=0; i<len_ref; i++)
        ref[i] = Py_BuildValue("s", null_c);

    if(paper.authors.size() <= len_author) {
        for(int i=0; i<paper.authors.size(); i++)
            auth[i] = Py_BuildValue("s", paper.authors[i].c_str());
        for(int i=paper.authors.size(); i<len_author; i++)
            auth[i] = Py_BuildValue("s", null_c);
    }
    else {
        for(int i=0; i<len_author-1; i++)
            auth[i] = Py_BuildValue("s", paper.authors[i].c_str());
        auth[len_author-1] = Py_BuildValue("s", paper.authors[paper.authors.size()-1].c_str());
    }

    if(paper.key_words.size() <= len_key) {
        for(int i=0; i<paper.key_words.size(); i++)
            kw[i] = Py_BuildValue("s", paper.key_words[i].c_str());
        for(int i=paper.key_words.size(); i<len_key; i++)
            kw[i] = Py_BuildValue("s", null_c);
    }
    else {
        for(int i=0; i<len_key; i++)
            kw[i] = Py_BuildValue("s", paper.key_words[i].c_str());
    }

    if(paper.fields.size() <= len_field) {
        for(int i=0; i<paper.fields.size(); i++)
            f[i] = Py_BuildValue("s", paper.fields[i].c_str());
        for(int i=paper.fields.size(); i<len_field; i++)
            f[i] = Py_BuildValue("s", null_c);
    }
    else {
        for(int i=0; i<len_field; i++)
            f[i] = Py_BuildValue("s", paper.fields[i].c_str());
    }

    PyTuple_SetItem(args, 0, db);
    PyTuple_SetItem(args, 1, c);
    PyTuple_SetItem(args, 2, t);
    for(int i=0; i<len_author; i++)
        PyTuple_SetItem(args, 3+i, auth[i]);
    for(int i=0; i<len_key; i++)
        PyTuple_SetItem(args, 3+len_author+i, kw[i]);
    PyTuple_SetItem(args, 3+len_author+len_key, ori);
    PyTuple_SetItem(args, 4+len_author+len_key, date);
    for(int i=0; i<len_ref; i++)
        PyTuple_SetItem(args, 5+len_author+len_key+i, ref[i]);
    PyTuple_SetItem(args, 5+len_author+len_key+len_ref, id);
    PyTuple_SetItem(args, 6+len_author+len_key+len_ref, ab);
    for(int i=0; i<len_field; i++)
        PyTuple_SetItem(args, 7+len_author+len_key+len_ref+i, f[i]);
    PyTuple_SetItem(args, 7+len_author+len_key+len_ref+len_field, wt_db);
    PyTuple_SetItem(args, 8+len_author+len_key+len_ref+len_field, wt_aut);
    PyTuple_SetItem(args, 9+len_author+len_key+len_ref+len_field, wt_kw);
    PyTuple_SetItem(args, 10+len_author+len_key+len_ref+len_field, wt_ori);
    PyTuple_SetItem(args, 11+len_author+len_key+len_ref+len_field, wt_ref);
    PyTuple_SetItem(args, 12+len_author+len_key+len_ref+len_field, wt_f);
    PyTuple_SetItem(args, 13+len_author+len_key+len_ref+len_field, rec_n);
    PyTuple_SetItem(args, 14+len_author+len_key+len_ref+len_field, c_pth);

    PyEval_CallObject(pFunUploadInfo, args);
    Py_Finalize();
    std::string res_pth = cache_pth + "/recommendation.txt";
    std::string tmp_str;
    ifstream file;
    bool tmp_bool;
    file.open(res_pth.c_str(), ios::in);
    if(file.is_open()) {
        for(int i=0; i<rec; i++) {
            scicore::sci_pdf_paper pp;
            getline(file, tmp_str);
            tmp_bool = sci_pdf_paper_input(pp, tmp_str);
            if(!tmp_bool) {
                res.clear();
                return res;
            }
            res.push_back(pp);
        }
        file.close();
    }
    return res;
}

}
