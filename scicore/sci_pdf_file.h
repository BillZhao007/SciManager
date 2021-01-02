#ifndef SCI_PDF_FILE_H
#define SCI_PDF_FILE_H

#include "sci_file.h"

namespace scicore {

class sci_pdf_file:public sci_file
{
public:
    sci_pdf_file(std::string name="untitiled", sci_file* parent = NULL);
    sci_pdf_file(std::string name="untitiled",std::string path="", sci_file* parent = NULL);

    std::string write() override;

    void read(std::string data) override;

    void accept_file_visitor(sci_file_visitor* visitor) override;

    std::string get_path();

    void set_path(std::string);
protected:
    std::string _path;

};

}


#endif // SCI_PDF_FILE_H
