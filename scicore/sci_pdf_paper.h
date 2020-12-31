#ifndef SCI_PDF_PAPER_H
#define SCI_PDF_PAPER_H

#include "sci_pdf_file.h"

#include <vector>
#include <QObject>

class sci_pdf_detail_widget;

namespace scicore {

class sci_pdf_paper:public sci_pdf_file
{
public:
    sci_pdf_paper(std::string name="untitiled", sci_file* parent = NULL);
    sci_pdf_paper(std::string name,std::string path, sci_file* parent = NULL);

    std::string write() override;

    void read(std::string data) override;

    void accept_file_visitor(sci_file_visitor* visitor) override;

    //论文信息
    std::string database;
    std::string title;
    std::vector<std::string> authors;
    std::vector<std::string> key_words;
    std::string origin; //来源 //待补充
    std::string date;
    int citation_times; //待补充
    std::string id; //待补充
    std::string abstract;
    std::vector<std::string> fields;
//    std::vector<std::string> topics;
    std::vector<std::string> recommend;

    bool is_extract;
    std::vector<sci_pdf_detail_widget*> page_list;
};

}



#endif // SCI_PDF_PAPER_H
