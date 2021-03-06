#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "info_line.h"
#include "dbase.h"
#include "utils.h"
#define DBG 0

std::vector<Info_Line> Dbase::boat_read_csv(std::string filename)
{

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

#if DBG
    std::cout << " Database file opened successfully "<< std::endl;
#endif
        std::getline(myFile, line);
    }
    // Read data, line by line
    while(std::getline(myFile, line))
    {
        // Create a stringstream of the current line
        auto xx = Utils::split(line, ",");
#if DBG
    std::cout << "line in the file : "<< line <<std::endl;
#endif           
        for (std::string t: xx)
            {
                _line.index = std::stoi(xx[0]);
                _line.make = xx[1];
                _line.length = std::stoi(xx[2]);
                _line.year = std::stoi(xx[3]);
                _line.price = std::stoi(xx[4]);
             }
        result.emplace_back(_line);
    }
    // Close file
    myFile.close();
    return result;
};

//search the db for the price
int Dbase::get_price(const std::vector<Info_Line> &db, Info_Line asking_price)
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

int Dbase::run_db(Info_Line boat_type)
{
    auto d = boat_read_csv("../data/boat.csv");

    return get_price(d, boat_type);

}
 
