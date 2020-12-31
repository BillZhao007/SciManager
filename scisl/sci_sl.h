#ifndef SCI_SL_H
#define SCI_SL_H

#include <string>
#include "scicore/sci_file.h"

namespace scisl {

class sci_sl
{
public:
    sci_sl();

    virtual void save()=0;

    virtual void load()=0;

    void set_path(std::string path);

    std::string get_path();
protected:
    std::string _path;
};




}



#endif // SCI_SL_H
