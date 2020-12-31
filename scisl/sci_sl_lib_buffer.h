#ifndef SCI_SL_LIB_BUFFER_H
#define SCI_SL_LIB_BUFFER_H

#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>

#include <vector>
#include <string>

#include "sci_sl.h"

namespace scisl {

class sci_sl_lib_buffer:public sci_sl
{
public:
    sci_sl_lib_buffer();
    /**
     * @brief 构造函数，设置路径为path
     * @param path
     */
    sci_sl_lib_buffer(std::string path);

    ~sci_sl_lib_buffer();
    /**
     * @brief 向储存中添加图书馆路径
     * @param path：路径
     * @param index：添加位置，如果为负数，则为从后往前计数
     * @return 是否成功
     */
    bool add_library(std::string path, int index = -1);
    /**
     * @brief 清除所有储存的图书馆
     */
    void clear_all();
    /**
     * @brief 获取储存的图书馆路径数
     * @return 路径数
     */
    int get_library_count();

    /**
     * @brief 获得index处的图书馆路径
     * @param index：如果为负数，则从后往前计数
     * @return
     */
    std::string get_library_path(int index);

    /**
     * @brief 重载函数，储存本文件
     */
    void save();

    /**
     * @brief 重载函数，从_path处读取本文件
     */
    void load();

private:
    std::vector<std::string> _name_list;

};

}


#endif // SCI_SL_LIB_BUFFER_H
