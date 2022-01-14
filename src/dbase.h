#ifndef DBASE_H
#define DBASE_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "info_line.h"

class Dbase 
{
    public:
        int run_db(Info_Line boat_type);

    private:
        std::vector<Info_Line> boat_read_csv(std::string filename);
        int get_price(const std::vector<Info_Line> &db, Info_Line asking_price);  
}; 
#endif