#ifndef SCI_FOLDER_H
#define SCI_FOLDER_H

#include "sci_file.h"
#include <vector>

namespace scicore {

/**
 * @brief 文件夹类，文件夹可作为多个文件的分类容器
 */
class sci_folder: public sci_file
{
public:
    sci_folder(std::string name="untitled",sci_file* parent = NULL);
    ~sci_folder();

    std::string write() override;

    void read(std::string data) override;

    /**
     * @brief 在index处插入file
     * @param file：文件指针
     * @param index：插入位置索引
     * @return
     */
    bool insert_file(sci_file *file, int index) override;
    /**
     * @brief 为文件夹添加文件
     * @param file:文件指针
     * @return 是否成功
     */
    bool add_file(sci_file* file) override;
    /**
     * @brief 移除文件夹中文件
     * @param index：文件序号
     * @return 被移除的文件指针
     */
    sci_file* remove_file(int index) override;
    /**
     * @brief 删除文件
     * @param index：文件序号
     * @return 是否成功
     */
    //bool delete_file(int index);
    /**
     * @brief 查找文件序号
     * @param file：文件指针
     * @return 文件序号
     */
    int match_child(sci_file* file) override;

    /**
     * @brief 更改文件在文件列表中的位置
     * @param from：文件初始位置序号
     * @param to：文件目标位置序号
     * @return 是否成功
     */
    bool replace_file(int from,int to);

    /**
     * @brief 获得文件夹下子文件数量
     * @return 子文件数
     */
    int child_count() override;

    /**
     * @brief 获得index索引处子文件指针
     * @param index
     * @return 子文件指针
     */
    sci_file * get_child(int index) override;

    /**
     * @brief 用于visitor模式的接口
     * @param visitor
     */
    void accept_file_visitor(sci_file_visitor *visitor) override;
private:
    /**
     * @brief 文件列表，储存了该文件夹下的子文件指针
     */
    std::vector<sci_file*> _file_list;
};

}



#endif // SCI_FOLDER_H
