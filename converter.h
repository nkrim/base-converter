/* ****************************************************** *
 * AUTHOR:      Noah Krim
 * ASSIGNMENT:  Lab 01.5 - Base Converter
 * CLASS:       CS_066
 * ------------------------------------------------------ *
 * FILE: converter.h
 *  Header file for base convertion functions.
 * ****************************************************** */

#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include "utils.h"

/* ------------------------------------------------------ *
 * All functions take in as an argument a stripped and 
 * pre-validated std::string representing the input std::number, and
 * produces a string representing that same number in 
 * but in the output base.
 * ------------------------------------------------------ */

/* ====================================================== *
 * From Binary
 * ====================================================== */
std::string bin_twos_compliment(const std::string& bin);
// is_negative argument used to front-pad result with 1-bits
std::string bin_to_oct(const std::string& bin, bool is_negative=false);
std::string bin_to_hex(const std::string& bin, bool is_negative=false);
std::string bin_to_dec(const std::string& bin);
std::string bin_to_dec_signed(const std::string& bin);

/* ====================================================== *
 * From Octal
 * ====================================================== */
std::string oct_twos_compliment(const std::string& oct);
std::string oct_to_bin(const std::string& oct);
std::string oct_to_hex(const std::string& oct);
std::string oct_to_dec(const std::string& oct);
std::string oct_to_dec_signed(const std::string& oct);

/* ====================================================== *
 * From Decimal
 * ====================================================== */
std::string& dec_str_plus_one(std::string& dec);
std::string& dec_str_minus_one(std::string& dec);
std::string& dec_str_times_two(std::string& dec);
std::string& dec_str_div_two(std::string& dec);

std::string dec_to_bin(const std::string& dec);
std::string dec_to_oct(const std::string& dec);
std::string dec_to_hex(const std::string& dec);

/* ====================================================== *
 * From Hexzdecimal
 * ====================================================== */
constexpr unsigned char from_hex_digit(char h);
constexpr char to_hex_digit(unsigned char n);
std::string hex_twos_compliment(const std::string& hex);
std::string hex_to_bin(const std::string& hex);
std::string hex_to_oct(const std::string& hex);
std::string hex_to_dec(const std::string& hex);
std::string hex_to_dec_signed(const std::string& hex);

#endif