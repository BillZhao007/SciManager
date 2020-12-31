#include "sci_ui_file.h"

namespace scigui {

sci_ui_file::sci_ui_file(sci_file_model* model)
{
    this->_model = model;
}

void sci_ui_file::set_model(sci_file_model* model){
    this->_model=model;
}

}

