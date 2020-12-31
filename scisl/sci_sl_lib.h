#ifndef SCI_SL_LIB_H
#define SCI_SL_LIB_H

#include "../scicore/sci_library.h"

#include "sci_sl.h"

namespace scisl {
/**
 * @brief 通过装饰器模式使得library具有储存功能
 */
class sci_sl_lib:public sci_sl
{
public:
    sci_sl_lib(std::string path="",scicore::sci_library* lib = NULL);

    void save();

    void load();
protected:
    scicore::sci_library* _library;
};

/**
 * @brief 将root及其子文件全部存储至path中
 * @param root
 * @param path
 */
void save(scicore::sci_file* root,std::string path);

/**
 * @brief 将path中的library读取出来，返回根节点
 * @param path
 * @return
 */
scicore::sci_file* load(std::string path);

}


#endif // SCI_SL_LIB_H
