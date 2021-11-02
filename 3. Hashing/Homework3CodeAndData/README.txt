Author: Tommy Liang
Date: 11/04/2021
    
Comments: 

All parts of the assignment is completed

I had trouble getting the FindPos() function in doube_hashing to work 
because the collision count is not within acceptable range.

I also had trouble debugging the case A, case B, and case C situation 
because the outputs were all together so the error for one part is shared for the rest.

To run the program:
	You can compile everything by typing 
		make clean
		make all
	To run each program individually
		./create_and_test_hash words.txt query_words.txt linear
		./create_and_test_hash words.txt words.txt query_words.txt quadratic 	
		./create_and_test_hash words.txt words.txt query_words.txt double
		./spell_check document1_short.txt wordsEn.txt
		./spell_check document1.txt wordsEn.txt
		make clean
	You delete all .o files and executables.

Input files:
	document1_short.txt
	document1.txt
	query_words.txt
	words.txt
	wordsEn.txt

End of Comments.

Note: the files create_and_test_hash.cc and quadratic_probing.h were provided by the professor.

Only the basic implementations of spell checker file and create and test hash file were provided through spell_check.cc and create_and_test_hash.cc. 
Some functions in the spell_check.cc and create_and_test_hash.cc were either added or being modified by me.

You will use this exact README for your Homework 3.