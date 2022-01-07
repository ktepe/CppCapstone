#ifndef DBASE_H
#define DBASE_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "utils.h"
#include "info_line.h"

namespace Dbase {
    std::vector<Info_Line> boat_read_csv(std::string filename){

        std::vector<Info_Line> result;

        // Create an input filestream
        std::ifstream myFile(filename);

        // Make sure the file is open
        if(!myFile.is_open()) throw std::runtime_error("Could not open file");

        // Helper vars
        std::string line, colname;

        Info_Line _line;

        // Read the column names
        if(myFile.good())
        {
            // Extract the first line in the file
            std::getline(myFile, line);
        }
        // Read data, line by line
        while(std::getline(myFile, line))
        {
            // Create a stringstream of the current line
            auto xx = Utils::split(line, ",");

            for (std::string t: xx)
                {
                    //std::cout << "t : "<< t << std::endl;
                    _line.index = std::stoi(xx[0]);
                    _line.make = xx[1];
                    _line.length = std::stoi(xx[2]);
                    _line.year = std::stoi(xx[3]);
                    _line.price = std::stoi(xx[4]);
                    //std::cout << "line.index : "<< _line.index << " line.price "<< _line.price <<std::endl;
                }
            result.emplace_back(_line);
        }
        // Close file
        myFile.close();
        return result;
    };

    int get_price(const std::vector<Info_Line> &db, Info_Line asking_price)
    {
        for (long unsigned int i=0; i < db.size(); i++)
        {    
            if (asking_price.make == db[i].make)
                if(asking_price.length == db[i].length)
                    if(asking_price.year == db[i].year)
                        return db[i].price;
        }
        return 0;
    };

    int run_db(Info_Line boat_type)
    {
        auto d = boat_read_csv("../data/boat.csv");

        return get_price(d, boat_type);

    }
} // name space

#endif