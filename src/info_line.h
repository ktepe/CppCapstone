#ifndef INFO_LINE_H
#define INFO_LINE_H

#include <string>

struct Info_Line{
    int index;
    std::string make;
    int length;
    int year;
    int price;

    Info_Line () {}

    Info_Line (std::string m, int l, int y)
    {
        make = m;
        length = l;
        year = y; 
    }

};

#endif
