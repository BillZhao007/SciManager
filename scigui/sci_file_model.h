#ifndef SCI_FILE_MODEL_H
#define SCI_FILE_MODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <QQueue>

#include "../scicore/sci_library.h"

namespace scigui{

enum file_operation{
    INSERT,
    REMOVE
};

class sci_file_model:public QAbstractItemModel,public scicore::sci_library
{
    Q_OBJECT
public:
    sci_file_model(QObject *parent = 0);

    ~sci_file_model();
    /**
     * @brief 获取parent节点row行column列的文件索引
     * @param row
     * @param column
     * @param parent
     * @return 文件索引
     */
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;

    /**
     * @brief 获得child节点的父节点索引
     * @param child
     * @return
     */
    QModelIndex parent(const QModelIndex &child) const override;

    /**
     * @brief 获得parent节点的行数
     * @param parent
     * @return
     */
    int rowCount(const QModelIndex &parent) const override;

    /**
     * @brief 获得column节点的列数
     * @param parent
     * @return
     */
    int columnCount(const QModelIndex &parent) const override;

    /**
     * @brief 获取index索引上role处的数据
     * @param index
     * @param role
     * @return
     */
    QVariant data(const QModelIndex &index, int role) const override;

    /**
     * @brief 获取第section列的标题
     * @param section
     * @param orientation
     * @param role
     * @return
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    /**
     * @brief Qt可编辑模型的重载函数
     * @param index
     * @return
     */
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    /**
     * @brief 在索引index处通过值value设置该处model的数据
     * @param index
     * @param value
     * @param role
     * @return
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    /**
     * @brief 清空模型内所有文件，TODO未验证
     */
    void clear();

    /**
     * @brief 设置根节点root
     * @param root
     */
    void set_root(scicore::sci_file *root) override;
    /**
     * @brief 在row行处插入file文件
     * @param row：插入位置
     * @param file:文件指针
     * @param parent：父节点
     * @return 是否成功
     */
    bool insert_file(int row, scicore::sci_file* file, const QModelIndex &parent = QModelIndex());

    /**
     * @brief 在row行处插入file文件
     * @param row：插入位置
     * @param file:文件指针
     * @param parent：父节点
     * @return 是否成功
     */
    bool insert_file(int row, scicore::sci_file* file, scicore::sci_file* parent, bool into_stack = true);

    /**
     * @brief 在尾部插入file文件
     * @param file:文件指针
     * @param parent：父文件
     * @return
     */
    bool add_file(scicore::sci_file* file, scicore::sci_file* parent);

    /**
     * @brief 移除row处文件
     * @param row：移除位置
     * @param parent：父节点
     * @return 被移除文件指针
     */
    scicore::sci_file* remove_file(int row, const QModelIndex &parent = QModelIndex());

    /**
     * @brief 移除row处文件
     * @param row：移除位置
     * @param parent：父节点
     * @return 被移除文件指针
     */
    scicore::sci_file* remove_file(int row, scicore::sci_file* parent, bool into_stack = true);

    /**
     * @brief 获取索引index处的文件指针
     * @param index
     * @return
     */
    scicore::sci_file * file_from_index(const QModelIndex &index) const;

    /**
     * @brief 获得file的ModelIndex
     * @param file：文件指针
     * @return
     */
    QModelIndex index_of(scicore::sci_file* file);

    void undo();

    void redo();
private:

    void _push(int row, scicore::sci_file* file, scicore::sci_file* parent, file_operation operation);
    void _pop();

    int stack_size;
    int stack_ptr;//指向下一个被push入的index
    QQueue<scicore::sci_file*> _file_stack;
    QQueue<scicore::sci_file*> _parent_stack;
    QQueue<int> _row_stack;
    QQueue<file_operation> _operation_stack;
};

}


#endif // SCI_FILE_MODEL_H
