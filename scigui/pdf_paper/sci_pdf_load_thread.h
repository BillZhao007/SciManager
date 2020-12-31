#ifndef SCI_PDF_LOAD_THREAD_H
#define SCI_PDF_LOAD_THREAD_H

#include <QThread>
#include <QImage>
#include <QQueue>
#include <QMutex>

#include "sci_pdf_utils.h"

class sci_pdf_load_thread:public QThread
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param path：pdf路径
     * @param cache_size：能缓存的最大页数，默认为5
     * @param parent：父对象·
     */
    sci_pdf_load_thread(QString path = "", int cache_size = 5,QObject *parent = nullptr);

    ~sci_pdf_load_thread();

    void load_pdf(QString path);
    /**
     * @brief 获得pdf文件总页数
     * @return 页数
     */
    int get_page_num();
    /**
     * @brief 获得每页的真实大小
     * @return
     */
    QSize get_page_size();

    /**
     * @brief run函数重载
     */
    void run() override;
    /**
     * @brief 清空待缓存队列
     */
    void clear_load_queue();
    /**
     * @brief 将page页加入待缓存队列
     * @param page
     */
    void load_page(int page);

    /**
     * @brief 查询page页是否被缓存
     * @param page
     * @return true如果被缓存
     */
    bool page_loaded(int page);
    /**
     * @brief 获得第page页的图像
     * @param page
     * @return 如果未缓存，则返回空指针，否则返回图像指针
     */
    QImage* get_page(int page);

    void set_cache_size(int size);


signals:
    /**
     * @brief 当缓存一张新页面时发射该信号
     */
    void load_new_image();

private:


    /**
     * @brief 将page页加入缓存中
     * @paramt page
     */
    void add_to_cache(int page);

    /**
     * @brief 能缓存的最大页数
     */
    int _cache_size;

    /**
     * @brief pdf缓存工具
     */
    sci_pdf_utils* _util;

    /**
     * @brief 进程锁
     */
    QMutex* _locker;

    /**
     * @brief 待缓存队列
     */
    QQueue<int> _load_queue;

    /**
     * @brief 已缓存图像映射
     */
    QMap<int,QImage> _cached_page_map;
    /**
     * @brief 已缓存图像队列
     */
    QQueue<int> _cached_page;

};

#endif // SCI_PDF_LOAD_THREAD_H
