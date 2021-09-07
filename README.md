Base Converter
==============
author: Noah Krim  
assignment: Lab 01.5 - Base Converter  
class: PCC CS066 - Barkeshli  

Converts binary, octal, decimal, signed decimal, and hexadecimal numbers of arbitrary length to each of the other bases. Uses digit-wise math performed on strings to avoid usual 64-bit integer boundaries.

How to Run
----------
Ensure you're working in this repo's directory.  
Compile the program and run it:
```bash
$ make
$ ./basecon
```

To run the program with the provided test input:
```bash
$ cat test.in | ./basecon

```

A version of the test output with the input collated inline is available in `test.out`

Program Instructions
--------------------
```
/=====================================================================\
| Base Converter                                                      |
+---------------------------------------------------------------------+
| Instructions:                                                       |
| - Enter a number in binary, octal, decimal, or hexadecimal.         |
| - To select the input base, either:                                 |
|   - Select the base to convert from after entering your number.     |
|   - Or include "b:", "o:", "d:", or "h:" before your initial input. |
| - Enter "help" at any time to view these instructions.              |
| - Enter "q" at any time to quit.                                    |
+---------------------------------------------------------------------+
| Examples:                                                           |
| - from binary                                                       |
|  > 1001101     (then enter "b" to select binary)                    |
|  > 0b0110                                                           |
|  > b: 1101                                                          |
|  > b: -010                                                          |
| - from octal                                                        |
|  > 7426301     (then enter "o" to select octal)                     |
|  > 0o2305                                                           |
|  > o: 3042                                                          |
|  > o: -765                                                          |
| - from decimal                                                      |
|  > 2318394     (then enter "d" to select decimal)                   |
|  > 4,292                                                            |
|  > d: 3042                                                          |
|  > d: -127                                                          |
| - from hexadecimal                                                  |
|  > 0384028     (then enter "h" to select hexadecimal)               |
|  > fF29cD0                                                          |
|  > 0x1241                                                           |
|  > h: 8F8B                                                          |
|  > h: -abc                                                          |
| - conversion results can be reused as input by entering "`base`:"   |
|  > b:          (previous binary output used as input)               |
|  > d:          (previous decimal output used as input)              |
|  > s:          (previous signed decimal output used as input)       |
|  > h: -        (previous hex output NEGATED and then used as input) |
| - instructions                                                      |
|  > help                                                             |
| - quit                                                              |
|  > q                                                                |
\=====================================================================/
```
