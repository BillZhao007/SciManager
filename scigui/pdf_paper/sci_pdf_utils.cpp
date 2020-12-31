#include "sci_pdf_utils.h"

sci_pdf_utils::sci_pdf_utils(QString filePath) {
    this->document = NULL;
    this->filePath = filePath;
    _load_pdf();
}

sci_pdf_utils::~sci_pdf_utils() {
}

void sci_pdf_utils::load(QString path){
    this->filePath = path;
    _load_pdf();
}

QImage sci_pdf_utils::get_pdf_image(int pageNumber, int dpi) {
    QImage image;

    if(pageNumber<0||pageNumber>=get_num_pages()){
        return image;
    }

    if (!document) {
        // ... error message ....
        return image;
    }
    // Document starts at page 0
    Poppler::Page* pdfPage = document->page(pageNumber);
    if (pdfPage == 0) {
        // ... error message ...
        return image;
    }
    // Generate a QImage of the rendered page
    image = pdfPage->renderToImage(dpi, dpi, -1, -1, -1, -1);
    if (image.isNull()) {
        // ... error message ...
        return image;
    }
    // after the usage, the page must be deleted
    delete pdfPage;
    return image;
}

int sci_pdf_utils::get_num_pages() {
    return numPages;
}

QSize sci_pdf_utils::get_page_size() {
    return pageSize;
}

//加载pdf，如果路径无效，则返回空的
void sci_pdf_utils::_load_pdf() {
    if(document){
        delete document;
        document = NULL;
    }

    numPages = 0;
    pageSize = QSize(400,400);

    if(filePath.isEmpty()){
        return;
    }

    document = Poppler::Document::load(filePath);
    if (!document || document->isLocked()) {
        // ... error message ....
        delete document;
        document = NULL;
        return;
    }

    numPages = document->numPages();
    Poppler::Page* pdfPage = document->page(0);
    pageSize = pdfPage->pageSize();
    delete pdfPage;
}
