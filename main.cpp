/* ****************************************************** *
 * AUTHOR:      Noah Krim
 * ASSIGNMENT:  Lab 01.5 - Base Converter
 * CLASS:       CS_066
 * ****************************************************** */

#include <iostream>
#include <string>
#include <regex>

#include "converter.h"

using namespace std;

// remove whitespace, commas, and convert to uppercase
void prepare_string(string& str) {
    auto it=str.begin(); 
    while(it!=str.end()) {
        if(isspace(*it) || *it==',')
            it = str.erase(it);
        else {
            *it = toupper(*it);
            ++it;
        }
    }
}

// clear all but 1 leading 0 for cleaner output
void clear_redundant_leading_zeros(string& str) {
    while(str.size() >= 2 && str[0] == '0' && str[1] == '0')
        str.erase(str.begin());
}

void print_instructions() {
    cout << endl
         << "/=====================================================================\\"<< endl
         << "| Base Converter                                                      |" << endl
         << "+---------------------------------------------------------------------+" << endl
         << "| Instructions:                                                       |" << endl
         << "| - Enter a number in binary, octal, decimal, or hexadecimal.         |" << endl
         << "| - To select the input base, either:                                 |" << endl
         << "|   - Select the base to convert from after entering your number.     |" << endl
         << "|   - Or include \"b:\", \"o:\", \"d:\", or \"h:\" before your initial input. |" << endl
         << "| - Enter \"help\" at any time to view these instructions.              |" << endl
         << "| - Enter \"q\" at any time to quit.                                    |" << endl
         << "+---------------------------------------------------------------------+" << endl
         << "| Examples:                                                           |" << endl
         << "| - from binary                                                       |" << endl
         << "|  > 1001101     (then enter \"b\" to select binary)                    |" << endl
         << "|  > 0b0110                                                           |" << endl
         << "|  > b: 1101                                                          |" << endl
         << "|  > b: -010                                                          |" << endl
         << "| - from octal                                                        |" << endl
         << "|  > 7426301     (then enter \"o\" to select octal)                     |" << endl
         << "|  > 0o2305                                                           |" << endl
         << "|  > o: 3042                                                          |" << endl
         << "|  > o: -765                                                          |" << endl
         << "| - from decimal                                                      |" << endl
         << "|  > 2318394     (then enter \"d\" to select decimal)                   |" << endl
         << "|  > 4,292                                                            |" << endl
         << "|  > d: 3042                                                          |" << endl
         << "|  > d: -127                                                          |" << endl
         << "| - from hexadecimal                                                  |" << endl
         << "|  > 0384028     (then enter \"h\" to select hexadecimal)               |" << endl
         << "|  > fF29cD0                                                          |" << endl
         << "|  > 0x1241                                                           |" << endl
         << "|  > h: 8F8B                                                          |" << endl
         << "|  > h: -abc                                                          |" << endl
         << "| - conversion results can be reused as input by entering \"`base`:\"   |" << endl
         << "|  > b:          (previous binary output used as input)               |" << endl
         << "|  > d:          (previous decimal output used as input)              |" << endl
         << "|  > s:          (previous signed decimal output used as input)       |" << endl
         << "|  > h: -        (previous hex output NEGATED and then used as input) |" << endl
         << "| - instructions                                                      |" << endl
         << "|  > help                                                             |" << endl
         << "| - quit                                                              |" << endl
         << "|  > q                                                                |" << endl
         << "\\=====================================================================/" << endl;
}

int main() {
    regex base_selection_r("^([BODSH]):");
    regex bin_validator_r("^(?:0B)?(-?[01]+)$");
    regex oct_validator_r("^(?:0O)?(-?[0-7]+)$");
    regex dec_validator_r("^(-?[0-9]+)$");
    regex hex_validator_r("^(?:0X)?(-?[0-9A-F]+)$");

    regex quit_validator_r("^Q");
    regex help_validator_r("^HELP");

    smatch m;

    string input_buffer;
    string input_suffix;
    string bin_str;
    string oct_str;
    string dec_str;
    string sig_str;
    string hex_str;

    // print instructions
    print_instructions();

    // main io loop
    while(true) {

        char base = '\0';
        bool valid_input = false;

        // read input
        cout << endl << "> ";
        getline(cin, input_buffer);
        prepare_string(input_buffer);

        // quit if "q" leads the input_buffer
        if(regex_search(input_buffer, quit_validator_r))
            return 0;

        // check for "help" command
        else if(regex_search(input_buffer, help_validator_r))
            print_instructions();

        // attempt to read explicit base selection
        else if(regex_search(input_buffer, m, base_selection_r)) {
            base = m[1].str()[0];
            input_suffix = m.suffix();

            // if only a '-' is included, negate the previous result;
            bool negate_previous = false;
            if(input_suffix.size() == 1 && input_suffix[0] == '-') {
                negate_previous = true;
                input_suffix = "";
            }

            // if suffix is empty, attempt to recall previous result
            if(input_suffix.empty()) {
                switch(base) {
                    case 'B':
                        if((valid_input = !bin_str.empty()) && negate_previous)
                            bin_str.insert(bin_str.begin(), '-');
                        break;
                    case 'O':
                        if((valid_input = !oct_str.empty()) && negate_previous)
                            oct_str.insert(oct_str.begin(), '-');
                        break;
                    case 'S':
                        base = 'D';
                        dec_str = sig_str;
                        // continue to case D
                    case 'D':
                        if((valid_input = !dec_str.empty()) && negate_previous) {
                            if(dec_str[0] == '-')
                                dec_str.erase(dec_str.begin());
                            else
                                dec_str.insert(dec_str.begin(), '-');
                        }
                        break;
                    case 'H':
                        if((valid_input = !hex_str.empty()) && negate_previous)
                            hex_str.insert(hex_str.begin(), '-');
                        break;
                }
                if(!valid_input)
                    cout << "No previous results found, please include new input." << endl;
            }
            // otherwise, validate input using base validator
            else {
                switch(base) {
                    case 'B':
                        if(regex_match(input_suffix, m, bin_validator_r)) {
                            bin_str = m[1];
                            valid_input = true;
                        }
                        else
                            cout << "Invalid binary input." << endl 
                                 << "Binary input consists of only 0s and 1s." << endl;
                        break;
                    case 'O':
                        if(regex_match(input_suffix, m, oct_validator_r)) {
                            oct_str = m[1];
                            valid_input = true;
                        }
                        else
                            cout << "Invalid octal input." << endl
                                 << "Octal input consists of numerical digits in the range [0 - 7]." << endl;
                        break;
                    case 'D':
                    case 'S':
                        if(regex_match(input_suffix, m, dec_validator_r)) {
                            dec_str = m[1];
                            valid_input = true;
                        }
                        else
                            cout << "Invalid decimal input." << endl
                                 << "Decimal input consists of numerical digits." << endl;
                        break;
                    case 'H':
                        if(regex_match(input_suffix, m, hex_validator_r)) {
                            hex_str = m[1];
                            valid_input = true;
                        }
                        else
                            cout << "Invalid hexadecimal input." << endl
                                 << "Hexadecimal input consists of numerical digits and letters in the range [A - F]." << endl;
                        break;
                }
            }
        }

        // unknown initial base, narrow the options
        else {
            unsigned valid_bases = 0;
            unsigned valid_base_bitmap = 0;

            if(regex_match(input_buffer, m, bin_validator_r)) {
                bin_str = m[1];
                valid_input = true;
                valid_bases++;
                valid_base_bitmap |= 0b0001;
                base = 'B'; // in case this is the only valid one
            }

            if(regex_match(input_buffer, m, oct_validator_r)) {
                oct_str = m[1];
                valid_input = true;
                valid_bases++;
                valid_base_bitmap |= 0b0010;
                base = 'O'; // in case this is the only valid one
            }

            if(regex_match(input_buffer, m, dec_validator_r)) {
                dec_str = m[1];
                valid_input = true;
                valid_bases++;
                valid_base_bitmap |= 0b0100;
                base = 'D'; // in case this is the only valid one
            }

            if(regex_match(input_buffer, m, hex_validator_r)) {
                hex_str = m[1];
                valid_input = true;
                valid_bases++;
                valid_base_bitmap |= 0b1000;
                base = 'H'; // in case this is the only valid one
            }

            // if no valid bases, complain
            if(!valid_input) {
                cout << "Could not determine any valid base from input number." << endl;
            }
            // more than one valid base, ask the user
            if(valid_bases > 1) {
                input_suffix = input_buffer;
                base = '\0';

                do {
                    cout << endl
                         << "Input: " << input_suffix << endl
                         << "Select your input's base from the options below:" << endl;
                    if(valid_base_bitmap&0b0001)
                        cout << " - \"b\" -> binary" << endl;
                    if(valid_base_bitmap&0b0010)
                        cout << " - \"o\" -> octal" << endl;
                    if(valid_base_bitmap&0b0100)
                        cout << " - \"d\" -> decimal" << endl;
                    if(valid_base_bitmap&0b1000)
                        cout << " - \"h\" -> hexadecimal" << endl;

                    cout << "> ";
                    getline(cin, input_buffer);
                    prepare_string(input_buffer);
                    if(!input_buffer.empty()) {
                        base = input_buffer[0];
                        switch(base) {
                            case 'B':
                                if(bin_str.empty()) {
                                    cout << "Input is not a valid binary number." << endl;
                                    base = '\0';
                                }
                                break;
                            case 'O':
                                if(oct_str.empty()) {
                                    cout << "Input is not a valid octal number." << endl;
                                    base = '\0';
                                }
                                break;
                            case 'D':
                            case 'S':
                                if(dec_str.empty()) {
                                    cout << "Input is not a valid decimal number." << endl;
                                    base = '\0';
                                }
                                break;
                            case 'H':
                                if(hex_str.empty()) {
                                    cout << "Input is not a valid hexadecimal number." << endl;
                                    base = '\0';
                                }
                                break;
                            default:
                                cout << "Unknown base option, try again.";
                                base = '\0';
                        }
                    }
                } while(base=='\0');
            }
            // only one valid base, it's already in `base` var
        }

        // if input is valid at this point, perform conversions
        if(valid_input) {
            cout << endl;
            switch(base) {
                case 'B':
                    cout << "From binary: " << bin_str;
                    if(bin_str[0] == '-') {
                        bin_str = bin_twos_compliment(bin_str.substr(1));
                        cout << " -> " << bin_str;
                    }
                    cout << endl;
                    clear_redundant_leading_zeros(bin_str);
                    cout << "- octal       -> " << (oct_str=bin_to_oct(bin_str)) << endl;
                    cout << "- hexadecimal -> " << (hex_str=bin_to_hex(bin_str)) << endl;
                    cout << "- decimal     -> " << (dec_str=bin_to_dec(bin_str)) << endl;
                    cout << "- signed dec  -> " << (sig_str=bin_to_dec_signed(bin_str)) << endl;
                    break;
                case 'O':
                    cout << "From octal: " << oct_str;
                    if(oct_str[0] == '-') {
                        oct_str = oct_twos_compliment(oct_str.substr(1));
                        cout << " -> " << oct_str;
                    }
                    cout << endl;
                    clear_redundant_leading_zeros(oct_str);
                    cout << "- binary      -> " << (bin_str=oct_to_bin(oct_str)) << endl;
                    cout << "- hexadecimal -> " << (hex_str=oct_to_hex(oct_str)) << endl;
                    cout << "- decimal     -> " << (dec_str=oct_to_dec(oct_str)) << endl;
                    cout << "- signed dec  -> " << (sig_str=oct_to_dec_signed(oct_str)) << endl;
                    break;
                case 'D':
                case 'S':
                    sig_str = dec_str; // for compatability with reuse command
                    cout << "From decimal: " << dec_str << endl;
                    clear_redundant_leading_zeros(dec_str);
                    cout << "- binary      -> " << (bin_str=dec_to_bin(dec_str)) << endl;
                    cout << "- octal       -> " << (oct_str=bin_to_oct(bin_str, dec_str[0]=='-')) << endl;
                    cout << "- hexadecimal -> " << (hex_str=bin_to_hex(bin_str, dec_str[0]=='-')) << endl;
                    break;
                case 'H':
                    cout << "From hexadecimal: " << hex_str;
                    if(hex_str[0] == '-') {
                        hex_str = hex_twos_compliment(hex_str.substr(1));
                        cout << " -> " << hex_str;
                    }
                    cout << endl;
                    clear_redundant_leading_zeros(hex_str);
                    cout << "- binary      -> " << (bin_str=hex_to_bin(hex_str)) << endl;
                    cout << "- octal       -> " << (oct_str=hex_to_oct(hex_str)) << endl;
                    cout << "- decimal     -> " << (dec_str=hex_to_dec(hex_str)) << endl;
                    cout << "- signed dec  -> " << (sig_str=hex_to_dec_signed(hex_str)) << endl;
                    break;
            }
        }
    }

    return 0;
}