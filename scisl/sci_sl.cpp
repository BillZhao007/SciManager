#include "sci_sl.h"




namespace scisl {

sci_sl::sci_sl()
{

}

void sci_sl::set_path(std::string path){
    _path = path;
}

std::string sci_sl::get_path(){
    return _path;
}



}
