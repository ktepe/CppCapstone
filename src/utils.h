// ============================================================================
//    Author: Kenneth Perkins
//    Date:   Jan 23, 2021
//    Taken From: http://programmingnotes.org/
//    File:  Utils.h
//    Description: Handles general utility functions
// ============================================================================
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
 
namespace Utils {
    /**
    * FUNCTION: split 
    * USE: Splits a string into tokens and saves them into a vector
    * @param source: String to be broken up into substrings (tokens)
    * @param delimiters: String containing the delimiter character(s)
    * @return: A vector containing all the found tokens in the string
    */
std::vector<std::string> split(const std::string& source, const std::string& delimiters);
};// http://programmingnotes.org/
#endif //UTILS_H
