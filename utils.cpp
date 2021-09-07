/* ****************************************************** *
 * AUTHOR:      Noah Krim
 * ASSIGNMENT:  Lab 01.5 - Base Converter
 * CLASS:       CS_066
 * ------------------------------------------------------ *
 * FILE: utils.cpp
 *  Definition file for misc utility functions.
 * ****************************************************** */

#include "utils.h"

/* ------------------------------------------------------ *
 * string_reverse:
 *  reverses a string in-place.
 * 
 * IN:
 *  str : string : string to reverse
 * OUT:
 *  RETURN : void
 *  str : string : reversed string
 * ------------------------------------------------------ */
void string_reverse(std::string& str) {
    int n = str.length()/2;
    for(int i=0; i<n; i++)
        std::swap(str[i], str[str.length()-1-i]);
}