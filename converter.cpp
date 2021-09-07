/* ****************************************************** *
 * AUTHOR:      Noah Krim
 * ASSIGNMENT:  Lab 01.5 - Base Converter
 * CLASS:       CS_066
 * ------------------------------------------------------ *
 * FILE: converter.cpp
 *  Definition file for base convertion functions.
 * ****************************************************** */

#include "converter.h"

#include <iostream> // FOR TESTING
using std::cout;
using std::endl;

using std::string;

/* ------------------------------------------------------ *
 * All functions take in as an argument a stripped and 
 * pre-validated string representing the input number, and
 * produces a string representing that same number 
 * but in the output base.
 * ------------------------------------------------------ */

/* ====================================================== *
 * From Binary
 * ====================================================== */
string bin_twos_compliment(const string& bin) {
	string out = "";

	// invert every bit
	for(size_t i=0; i<bin.length(); i++)
		out.push_back(bin[i]=='0' ? '1' : '0');

	// add 1, starting from right side
	size_t i = out.length();
	while(i>0 && out[i-1] == '1')
		out[--i] = '0';
	// conditional ensures no overflow and maintains -0 -> 0
	if(i > 0)
		out[i-1] = '1';

	// return
	return out;
}

string bin_to_oct(const string& bin, bool is_negative) {
	string oct;
	oct.reserve(bin.length()/3 + 1);

	unsigned char buffer = 0;
	unsigned char bit_count = 0;

	for(size_t i=bin.length(); i>0; i--) {
		// parse bit from string and insert into numberical buffer
		if(bin[i-1] == '1')
			buffer |= 1<<bit_count;
		bit_count++;

		// when 3 bits have been found, convert to octal digit
		if(bit_count >= 3) {
			oct.push_back('0'+buffer);
			buffer = 0;
			bit_count = 0;
		}
	}
	// add remaining digit, if it exists
	if(bit_count > 0) {
		// if negative, pad buffer with 1s
		if(is_negative) {
			while(bit_count < 3)
				buffer |= 1<<(bit_count++);
		}
		oct.push_back('0'+buffer);
	}

	// delete leading 0s
	while(oct.size() > 1 && oct.back() == '0')
		oct.pop_back();

	// reverse and return
	string_reverse(oct);
	return oct;
}

string bin_to_hex(const string& bin, bool is_negative) {
	string hex;
	hex.reserve(bin.length()/4 + 1);

	unsigned char buffer = 0;
	unsigned char bit_count = 0;

	for(size_t i=bin.length(); i>0; i--) {
		// parse bit from string and insert into numberical buffer
		if(bin[i-1] == '1')
			buffer |= 1<<bit_count;
		bit_count++;

		// when 3 bits have been found, convert to octal digit
		// also convert when on last digit and buffer is non-zero
		if(bit_count >= 4) {
			hex.push_back(to_hex_digit(buffer));
			buffer = 0;
			bit_count = 0;
		}
	}
	// add remaining digit, if it exists
	if(bit_count > 0) {
		// if negative, pad buffer with 1s
		if(is_negative) {
			while(bit_count < 4)
				buffer |= 1<<(bit_count++);
		}
		hex.push_back(to_hex_digit(buffer));
	}

	// delete leading 0s
	while(hex.size() > 1 && hex.back() == '0')
		hex.pop_back();
	string_reverse(hex);
	return hex;
}

string bin_to_dec(const string& bin) {
	string dec = "0";

	// construct dec string from bin bits using dec_str math functions
	for(size_t i=0; i<bin.length(); i++) {
		dec_str_times_two(dec);
		if(bin[i] == '1')
			dec_str_plus_one(dec);
	}

	return dec;
}

string bin_to_dec_signed(const string& bin) {
	if(bin[0] != '1')
		return bin_to_dec(bin);

	string bin_tc = bin_twos_compliment(bin); 
	string dec = "-";
	dec.append(bin_to_dec(bin_tc));

	return dec;
}

// OLD NUMERICAL APPROACH, NOW USING DEC_STRs
/*string bin_to_dec(const string& bin, bool is_negative) {
	string dec;

	unsigned long long buffer = 0;

	// parse binary to numerical representation
	for(size_t i=0; i<bin.length(); i++) {
		if(bin[bin.length()-1-i] == '1')
			buffer += (1ULL<<i);
	}

	// decode decimal string from numerical buffer
	do {
		dec.push_back('0'+(buffer%10));
		buffer /= 10;
	} while(buffer > 0);

	// delete leading 0s
	while(dec.size() > 1 && dec.back() == '0')
		dec.pop_back();
	// if negative, append hyphen
	if(is_negative)
		dec.push_back('-');

	// reverse and return
	string_reverse(dec);
	return dec;
}*/



/* ====================================================== *
 * From Octal
 * ====================================================== */
std::string oct_twos_compliment(const string& oct) {
	string out = "";

	// invert every bit
	for(size_t i=0; i<oct.length(); i++)
		out.push_back('7'-oct[i]+'0');

	// add 1, starting from right side
	size_t i = out.length();
	while(i>0 && out[i-1] == '7')
		out[--i] = '0';
	// conditional ensures no overflow and maintains -0 -> 0
	if(i > 0)
		out[i-1]++;

	// return
	return out;
}

string oct_to_bin(const string& oct) {
	string bin;
	bin.reserve(oct.length()*3);

	for(auto it=oct.rbegin(); it!=oct.rend(); ++it) {
		unsigned char n = *it-'0';
		bin.push_back('0'+(n&1));
		n>>=1;
		bin.push_back('0'+(n&1));
		n>>=1;
		bin.push_back('0'+(n&1));
	}

	// delete leading 0s
	// while(bin.back() == '0')
	// 	bin.pop_back();

	// reverse and return
	string_reverse(bin);
	return bin;
}

string oct_to_hex(const string& oct) {
	string hex;
	hex.reserve(oct.length()*3/4 + 1);

	unsigned char buffer[4];
	unsigned char dig_count = 0;
	unsigned char a, b, c; // parsed hex digit values

	for(size_t i=oct.length(); i>0; i--) {
		// Append up to 4 octal digits to the buffer
		buffer[dig_count++] = oct[i-1]-'0';

		// Parse every 4 octal digits into 3 hex digits
		if(dig_count >= 4) {
			a = ((buffer[1]&0b001)<<3) | buffer[0];
			b = ((buffer[2]&0b011)<<2) | (buffer[1]>>1);
			c = ((buffer[3]      )<<1) | (buffer[2]>>2);
			hex.push_back(to_hex_digit(a));
			hex.push_back(to_hex_digit(b));
			hex.push_back(to_hex_digit(c));

			// reset
			dig_count = 0;
		}
	}
	// perform a final conversion, if necessary
	if(dig_count > 0) {
		// fill buffer with 0s
		while(dig_count < 4)
			buffer[dig_count++] = 0;
		// do final conversion
		a = ((buffer[1]&0b001)<<3) | buffer[0];
		b = ((buffer[2]&0b011)<<2) | (buffer[1]>>1);
		c = ((buffer[3]      )<<1) | (buffer[2]>>2);
		hex.push_back(to_hex_digit(a));
		hex.push_back(to_hex_digit(b));
		hex.push_back(to_hex_digit(c));
	}

	// delete leading 0s
	while(hex.size() > 1 && hex.back() == '0')
		hex.pop_back();

	// reverse and return
	string_reverse(hex);
	return hex;
}

string oct_to_dec(const string& oct) {
	string bin = oct_to_bin(oct);
	return bin_to_dec(bin);
}

string oct_to_dec_signed(const string& oct) {
	string bin = oct_to_bin(oct);
	return bin_to_dec_signed(bin);
}

// OLD NUMERICAL APPROACH, NOW USING DEC_STR MATH AND BIN AS INTERMEDIARY
/*string oct_to_dec(const string& oct, bool is_negative) {
	string dec;

	unsigned long long buffer = 0;

	// parse octal to numerical representation
	for(size_t i=0; i<oct.length(); i++) {
		buffer <<= 3;
		buffer += oct[i] - '0';
	}

	// decode decimal string from numerical buffer
	do {
		dec.push_back('0'+(buffer%10));
		buffer /= 10;
	} while(buffer > 0);

	// delete leading 0s
	while(dec.size() > 1 && dec.back() == '0')
		dec.pop_back();
	// append hyphen if negative
	if(is_negative)
		dec.push_back('-');

	// reverse and return 
	string_reverse(dec);
	return dec;
}*/



/* ====================================================== *
 * From Decimal - Math Functions
 * ====================================================== */
std::string& dec_str_plus_one(string& dec) {
	// check for negative, perform subtraction instead
	if(dec[0] == '-') {
		dec.erase(dec.begin());
		dec_str_minus_one(dec);
		// prepend negative if non-zero
		if(!(dec.size() == 1 && dec[0] == '0'))
			dec.insert(dec.begin(), '-');
		return dec;
	}

	// push all trailing 9s to 0s
	size_t i=dec.size();
	while(i>0 && dec[i-1]=='9')
		dec[--i] = '0';

	// prepend a 1 if whole string traversed
	if(i == 0)
		dec.insert(dec.begin(), '1');
	// add 1 to first non-9 digit
	else
		dec[i-1]++;

	// return reference to parameter for easy chaining
	return dec;
}

std::string& dec_str_minus_one(string& dec) {
	// check for negative, perform addition instead
	if(dec[0] == '-') {
		dec.erase(dec.begin());
		dec_str_plus_one(dec);
		// prepend negative if non-zero
		if(!(dec.size() == 1 && dec[0] == '0'))
			dec.insert(dec.begin(), '-');
		return dec;
	}

	// push all trailing 0s to 9s
	size_t i=dec.size();
	while(i>0 && dec[i-1]=='0')
		dec[--i] = '9';

	// make -1 if whole string traversed
	if(i == 0)
		dec = "-1";
	// sub 1 from first non-0 digit
	else
		dec[i-1]--;

	// delete trailing 0s
	while(*dec.begin() == '0')
		dec.erase(dec.begin());
	// check for complete deletion and make "0" if so
	if(dec.empty())
		dec.push_back('0');

	// return reference to parameter for easy chaining
	return dec;
}

const char dec_times_table[] = {
	'0', '2', '4', '6', '8',
	'0', '2', '4', '6', '8'
};
string& dec_str_times_two(string& dec) {
	bool carry = false;
	bool is_negative = dec[0] == '-';

	// multiply each digit by two, carrying any excess
	size_t i=dec.size();
	for(; i>0 && dec[i-1]!='-'; i--) {
		char old_c = dec[i-1];
		dec[i-1] = dec_times_table[dec[i-1]-'0'];
		if(carry) {
			carry = false;
			dec[i-1]++;
		}
		if(old_c >= '5')
			carry = true;
	}

	// account for carry bit after string traversal
	if(carry) {
		if(is_negative)
			dec.insert(dec.begin()+1, '1');
		else
			dec.insert(dec.begin(), '1');
	}

	// return reference to parameter for easy chaining
	return dec;
}

const char dec_div_table[] = {
	'0', '0', '1', '1', '2',
	'2', '3', '3', '4', '4'
};
std::string& dec_str_div_two(std::string& dec) {
	bool half_carry = false;
	bool is_negative = dec[0] == '-';

	// divide each digit by two, carrying any halves
	for(size_t i=!!is_negative; i<dec.size(); i++) {
		char old_c = dec[i]-'0';
		dec[i] = dec_div_table[dec[i]-'0'];
		if(half_carry) {
			half_carry = false;
			dec[i] += 5;
		}
		if(old_c&1)
			half_carry = true;
	}

	// no need to account for carry after string traversal

	// delete leading 0s
	//  for negatives
	if(is_negative) {
		while(dec.size() > 2 && dec[1] == '0')
			dec.erase(dec.begin()+1);
		// if "-0", remove hyphen
		if(dec[1] == '0')
			dec.erase(dec.begin());
	}
	//  for positives
	else {
		while(dec.size() > 1 && dec[0] == '0')
			dec.erase(dec.begin());
	}

	// return reference to parameter for easy chaining
	return dec;
}

/* ====================================================== *
 * From Decimal - Conversion Functions
 * ====================================================== */
string dec_to_bin(const string& dec) {
	string bin;

	unsigned ones_count = 0;
	bool is_negative = dec[0] == '-';

	// initialize copy of dec
	string dec_copy = dec;
	if(is_negative)
		dec_copy.erase(dec_copy.begin());

	// perform decimal to binary conversion on dec str
	while(dec_copy.size() > 1 || dec_copy[0] != '0') {
		bool is_odd = (dec_copy.back()-'0')&1;
		if(is_odd)
			ones_count++;
		// append '1' if odd, '0' if even
		bin.push_back('0'+is_odd);
		// divide dec by two
		dec_str_div_two(dec_copy);
	}

	// if negative, append a zero so two's compliment is valid
	//  unless there is only one 1, then it is a power of two
	if(is_negative && ones_count > 1)
		bin.push_back('0');

	// reverse bin
	string_reverse(bin);

	// if negative, convert to two's compliment
	if(is_negative)
		bin = bin_twos_compliment(bin);

	// if bin is empty, set to "0"
	if(bin.empty())
		bin = "0";

	// return
	return bin;
}

string dec_to_oct(const string& dec) {
	bool is_negative = dec[0] == '-';
	return bin_to_oct(dec_to_bin(dec), is_negative);
}
string dec_to_hex(const string& dec) {
	bool is_negative = dec[0] == '-';
	return bin_to_hex(dec_to_bin(dec), is_negative);
}

/* ====================================================== *
 * From Hexzdecimal
 * ====================================================== */
constexpr unsigned char from_hex_digit(char h) {
	return h>='A' ? h-'A'+10 : (h>='a' ? h-'a'+10 : h-'0');
}
constexpr char to_hex_digit(unsigned char n) {
	return n>=10 ? 'A'+n-10 : '0'+n;
}

std::string hex_twos_compliment(const string& hex) {
	string out = "";

	// invert every bit
	for(size_t i=0; i<hex.length(); i++) 
		out.push_back(to_hex_digit(15-from_hex_digit(hex[i])));

	// add 1, starting from right side
	size_t i = out.length();
	while(i>0 && out[i-1] == 'F')
		out[--i] = '0';
	// conditional ensures no overflow and maintains -0 -> 0
	if(i > 0) {
		if(out[i-1] == '9')
			out[i-1] = 'A';
		else
			out[i-1]++;
	}

	// return
	return out;
}

string hex_to_bin(const string& hex) {
	string bin;
	bin.reserve(hex.length()*4);

	for(auto it=hex.rbegin(); it!=hex.rend(); ++it) {
		unsigned char n = from_hex_digit(*it);
		bin.push_back('0'+(n&1));
		n>>=1;
		bin.push_back('0'+(n&1));
		n>>=1;
		bin.push_back('0'+(n&1));
		n>>=1;
		bin.push_back('0'+(n&1));
	}

	// delete leading 0s
	// while(bin.back() == '0')
	// 	bin.pop_back();

	// reverse and return
	string_reverse(bin);
	return bin;
}

string hex_to_oct(const string& hex) {
	string oct;
	oct.reserve(hex.length()*4/3 + 1);

	unsigned char buffer[3];
	unsigned char dig_count = 0;
	unsigned char a, b, c, d; // parsed oct digit values

	for(size_t i=hex.length(); i>0; i--) {
		// Append up to 3 hex digits to the buffer
		buffer[dig_count++] = from_hex_digit(hex[i-1]);

		// Parse every 3 hex digits into 4 oct digits
		if(dig_count >= 3) {
			a =   buffer[0]&0b0111;
			b = ((buffer[1]&0b0011)<<1) | (buffer[0]>>3);
			c = ((buffer[2]&0b0001)<<2) | (buffer[1]>>2);
			d =   buffer[2]>>1;
			oct.push_back(a+'0');
			oct.push_back(b+'0');
			oct.push_back(c+'0');
			oct.push_back(d+'0');

			// reset
			dig_count = 0;
		}
	}
	// perform a final conversion, if necessary
	if(dig_count > 0) {
		// fill buffer with 0s
		while(dig_count < 3)
			buffer[dig_count++] = 0;
		// do final conversion
		a =   buffer[0]&0b0111;
		b = ((buffer[1]&0b0011)<<1) | (buffer[0]>>3);
		c = ((buffer[2]&0b0001)<<2) | (buffer[1]>>2);
		d =   buffer[2]>>1;
		oct.push_back(a+'0');
		oct.push_back(b+'0');
		oct.push_back(c+'0');
		oct.push_back(d+'0');
	}

	// delete leading 0s
	while(oct.size() > 1 && oct.back() == '0')
		oct.pop_back();

	// reverse and return
	string_reverse(oct);
	return oct;
}

string hex_to_dec(const string& hex) {
	string bin = hex_to_bin(hex);
	return bin_to_dec(bin);
}

string hex_to_dec_signed(const string& hex) {
	string bin = hex_to_bin(hex);
	return bin_to_dec_signed(bin);
}

// OLD NUMERICAL APPROACH, NOW USING DEC_STR MATH AND BIN AS INTERMEDIARY
/*string hex_to_dec(const string& hex, bool is_negative) {
	string dec;

	unsigned long long buffer = 0;

	// parse octal to numerical representation
	for(size_t i=0; i<hex.length(); i++) {
		char c = toupper(hex[i]);
		buffer <<= 4;
		buffer += c>='A' ? c-'A'+10 : c-'0';
	}

	// decode decimal string from numerical buffer
	do {
		dec.push_back('0'+(buffer%10));
		buffer /= 10;
	} while(buffer > 0);

	// delete leading 0s
	while(dec.size() > 1 && dec.back() == '0')
		dec.pop_back();
	// append hyphen if negative
	if(is_negative)
		dec.push_back('-');

	// reverse and return 
	string_reverse(dec);
	return dec;
}*/