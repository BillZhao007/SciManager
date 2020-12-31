#ifndef SCI_PDF_UTILS_H
#define SCI_PDF_UTILS_H



#include <QObject>
#include <QImage>
#include <QSize>
#include <QDebug>
#include "poppler-qt5.h"

class sci_pdf_utils
{
public:
    explicit sci_pdf_utils(QString filePath = "");
    ~sci_pdf_utils();

    //读取
    void load(QString path);

    //获取指定页pdf图像(页码从0开始)
    QImage get_pdf_image(int pageNumber,int dpi = 300);
    //获取pdf总页码
    int get_num_pages();
    //获取pdf页面大小
    QSize get_page_size();

private:
    //读取文件
    void _load_pdf();

    QString filePath;
    int numPages;
    QSize pageSize;

    Poppler::Document* document;
};

#endif // SCI_PDF_UTILS_H
