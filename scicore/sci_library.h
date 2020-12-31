#ifndef SCI_LIBRARY_H
#define SCI_LIBRARY_H

#include "sci_file.h"
#include <vector>


namespace scicore {

/**
 * @brief 图书馆类，用于储存文件树并完成一系列操作（目前啥操作都没有
 */
class sci_library
{
public:
    sci_library();

    /**
     * @brief 设置根节点
     * @param root:根文件（推荐为文件夹folder）
     */
    virtual void set_root(sci_file *root);

    /**
     * @brief 获取根节点
     * @return
     */
    virtual sci_file* get_root();

    /**
     * @brief 在root文件下按照名称name查找
     * @param name
     * @param root
     * @return
     */
    virtual std::vector<sci_file*> search_on_name(std::string name,sci_file* root);

    /**
     * @brief 获取以root为根节点下的所有子文件数
     * @param root
     * @return
     */
    static long long total_file(sci_file* root);
protected:
    sci_file* _root;
};

}


#endif // SCI_LIBRARY_H
