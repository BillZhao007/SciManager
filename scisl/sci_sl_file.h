#ifndef SCI_SL_FILE_H
#define SCI_SL_FILE_H


#include "../scicore/sci_file.h"

namespace scisl {
/**
 * @brief 存储和读取功能的抽象类
 */
class sci_sl_file
{
public:
    sci_sl_file();
    /**
     * @brief 用于向信息存储文件中写入信息的函数
     * @param path
     */
    virtual void write(char* path)=0;

    /**
     * @brief 用于从信息存储文件中读入信息的函数
     * @param path
     */
    virtual void read(char* path)=0;

    /**
     * @brief 用于返回文件类型的函数，1为folder，2为pdf_paper
     * @return
     */
    virtual int type()=0;

    /**
     * @brief 用于生成信息存储文件路径的函数，该路径将保存在library中
     * @return
     */
    virtual const char* path();

    /**
     * @brief 设置路径
     */
    void set_path(std::string );

    /**
     * @brief 用于生成文件简要描述的函数，该描述将保存在library中
     * @return
     */
    virtual char* desc()=0;
protected:
     std::string _savepath;
};

}


#endif // SCI_SL_FILE_H
