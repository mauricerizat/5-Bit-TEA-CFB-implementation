# 5-Bit-TEA-CFB-implementation
A console-based C++ program that performs encryption and decryption using the TEA block cipher implemented with the Cipher Feedback Mode.

## IMPORTANT

THIS PROGRAM IS WRITTEN IN C++ (C++11 recommended)

THIS README DEMONSTRATES THE EXECUTION OF THIS PROGRAM ON A LINUX TERMINAL WITH A C++ COMPILER

This program is designed to encrypt/decrypt 7-bit ASCII characters. The use of non ASCII characters may cause undefined behaviour during the runtime of the program. 

K is a hardcoded global constant, therefore to change the bit value of the CFB program, the value of GLOBAL_CONST_K must be changed from the Task5.h file and the program must be recompiled.

## FILE IO 

Please place all plaintext and ciphertext files to be processed in the "data" folder.

Make sure to include the extention of the file if required.

The output file will also be stored in the "data" folder.

This has been done to minimize clutter.
 
## COMPILATION 

Enter the following command into the terminal to compile the program along with all dependencies:

**make**

##EXECUTION 

Enter the following command into the terminal to run the program

**./CFBTEA.out**

## CLEAN 

Enter the following command into the terminal to remove all objects and .out files associated with the program:

**make clean**

## NOTES
This program outputs ciphertext as a bitstream which works fine for encryption and decryption.

However it would be preferrable to output ciphertext as a hexadecimal string and there is some coode in the source for this, albeit commented out. The reason for this is that the binary to hexadecimal string conversion produces some errors, primarily in the last few characters (bytes). I will have to deal with this when I get the chance. 

Contact me at mauricerizat@gmail.com to report bugs
