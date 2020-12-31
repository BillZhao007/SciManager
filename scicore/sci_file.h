#ifndef SCI_FILE_H
#define SCI_FILE_H

#include <string>
#include <QObject>

namespace scicore {


class sci_file_visitor;


/**
 * @brief 文件类，虚基类，负责为存储系统提供存储信息
 */
class sci_file //: public QObject
{
public:
    sci_file(std::string name="untitiled", sci_file* parent = NULL);
    virtual ~sci_file();

    /**
     * @brief 返回该文件的类型；
     * @return
     */
    virtual char type();
    /**
     * @brief get_name
     * @return
     */
    virtual std::string get_name();
    /**
     * @brief set_name
     * @return
     */
    virtual bool set_name(std::string);
    /**
     * @brief 输出自身存储信息
     * @return 返回std::string，即需要存储的信息
     */
    virtual std::string write() = 0;
    /**
     * @brief 读取来自data中的储存信息
     */
    virtual void read(std::string data) = 0;
    /**
     * @brief 子文件数目
     * @return 默认返回0
     */
    virtual int child_count();
    /**
     * @brief 获得index索引处子文件指针
     * @param index：文件索引
     * @return 默认返回空指针
     */
    virtual sci_file* get_child(int index);

    /**
     * @brief 获取父文件指针
     * @return 父文件指针
     */
    virtual sci_file* get_parent();

    /**
     * @brief 设置父节点
     * @param parent
     */
    virtual void set_parent(sci_file* parent);

    /**
     * @brief 获得指针file的索引
     * @param file：子文件指针
     * @return 默认返回-1
     */
    virtual int match_child(sci_file* file);

    /**
     * @brief 添加子文件
     * @param file：子文件指针
     * @return 默认返回false
     */
    virtual bool insert_file(sci_file* file,int index);

    /**
     * @brief 直接在末尾添加文件，里面调用insert_file
     * @param file：文件指针
     * @return
     */
    virtual bool add_file(sci_file* file);

    /**
     * @brief 移除index处子文件
     * @param index
     * @return 默认返回NULL
     */
    virtual sci_file* remove_file(int index);

    /**
     * @brief 彻底删除文件，本函数调用remove_file，不需要重载
     * @param index
     */
    void delete_file(int index);

    /**
     * @brief 删除自身
     */
    void delete_self();


    /**
     * @brief 用于visitor模式添加扩展功能的接口，每个子类都需要重载
     * @param visitor
     */
    virtual void accept_file_visitor(sci_file_visitor* visitor)=0;


protected:
    /**
     * @brief 父文件指针
     */
    sci_file* _parent;
    /**
     * @brief 文件名
     */
    std::string _name;
};

}

#endif // SCI_FILE_H
