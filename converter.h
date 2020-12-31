#ifndef CONVERTER_H
#define CONVERTER_H
struct Information    //注意需要分配内存
{
    char* database;
    char* title;
    char* cite_number;
    char* author[6];   //长度为6
    char* key_word[3]; //长度为3
    char* origin;
    char* date;
    char* doi;
    char* abstract;
    char* ref[10];  //长度为10
};
int  upload(char* ip, struct Information* info);
int  search (char* ip, struct Information* info, struct Information* result);
#endif // CONVERTER_H
