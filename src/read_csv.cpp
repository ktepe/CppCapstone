#include <string>
#include <fstream>
#include <vector>
#include <iostream>

#include "dbase.h"


int main() 
{
    // Read three_cols.csv and ones.csv
    auto three_cols = Dbase::boat_read_csv("../data/boat.csv");
    //write_csv("ones_copy.csv", ones);
    for (Info_Line i : three_cols)
        std::cout << "index of return " << i.index << std::endl;

    Info_Line x("Beneteau", 50, 2014);

    std::cout << Dbase::get_price(three_cols, x) << std::endl;

    Info_Line y("Jeanneau", 49, 2019);

    std::cout << Dbase::get_price(three_cols, y) << std::endl;

    Info_Line z("Jeanneau", 30, 2019);

    std::cout << Dbase::get_price(three_cols, z) << std::endl;

    return 0;
}
