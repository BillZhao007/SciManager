#ifndef SCI_R_CONVERTER_H
#define SCI_R_CONVERTER_H

#include <QDebug>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#undef slots
#include "Python.h"
#define slots Q_SLOTS

#include <scicore/sci_pdf_paper.h>

namespace sci_r{

    struct weight{
        double database;
        double author;
        double keyword;
        double origin;
        double ref;
        double field;
        weight(): database(0), author(0), keyword(0), origin(0), ref(0), field(0) {}
    };
    std::string Nullize(std::string&);
    bool sci_pdf_paper_input(scicore::sci_pdf_paper&, std::string&);
    bool upload_single(scicore::sci_pdf_paper&);
    std::vector<scicore::sci_pdf_paper> recommend(scicore::sci_pdf_paper&, weight, int);
}

#endif // SCI_R_UPLOAD_H
