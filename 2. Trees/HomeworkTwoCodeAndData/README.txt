Author: Tommy Liang
Date: 10/11/2021
    
Comments: 

All parts of the assignment is completed except that the value/calculation
for 5b isn't within the acceptable range and I'm not sure how to fix that.

I encounter a bunch of bugs with the function headers dealing with adding
const in the paramters or even after the function. I also struggled with
printing out all enzyme acronyms for a given recognition sequence. It turned
out that I needed to adjust the insert functions for the avl_tree.h and bst_tree.headers

To run the program:
	make clean
	make all
	./query_tree rebase210.txt AVL < input_part2a.txt
	./query_tree rebase210.txt BST < input_part2a.txt
	./test_tree rebase210.txt sequences.txt AVL
	./test_tree rebase210.txt sequences.txt BST
	./test_tree_mod rebase210.txt sequences.txt AVL
	./test_tree_mod rebase210.txt sequences.txt BST
	make clean

Input files:
	input_part2a.txt
	rebase210.txt
	sequences.txt

End of Comments.

Note: the files avl_tree.h and dsexceptions.h were provided by the professor.

Only the basic implementations of AVL Tree were provided through avl_tree.h. Some functions in the avl_tree.h were either added or being modified by me.

You will use this exact Makefile for your Homework 2. Do not submit it! 

You can compile everything by typing 

make all

You can compile one program individually by just typing make <Program Name>, for example

make query_tree

By typing 

make clean

You delete all .o files and executables.
