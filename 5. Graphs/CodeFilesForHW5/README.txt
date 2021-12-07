Author: Tommy Liang
Date: 12/07/2021
    
Comments: 

All parts of the assignment is completed

I had trouble getting part 2 of the homework, the Dijkstra method to work.
Originally, it was an issue with the indices but after solving that issue,
there was also another issue with making sure that I update the shortest path
as it seems that the shortest path wasn't what I printed out.

I also had trouble debugging why all the functions weren't working on gradescope.
This error was due to really tiny errors like misnamed header files or forgetting
to input certain libraries

To run the program:
	You can compile everything by typing 
		make clean
		make all
	To run each program individually
    () = choose any of the possibilities separated by a ','
    Part 1 of Homework   
        ./CreateGraphAndTest (Graph1.txt, Graph2.txt) (AdjacencyQueries1.txt, AdjacencyQueries2.txt)
	Part 2 of Homework
        ./FindPaths (Graph1.txt, Graph2.txt) <integer>
    The integer value must be a vertex that exists in the text file that is read om/
        make clean
	You delete all .o files and executables.

Input files:
    Graph1.txt
    Graph2.txt
    AdjacencyQueries1.txt
    AdjacencyQueries2.txt

End of Comments.

Note: the files test
binary_heap.h was provided by the professor.

However all the function implementations are in CreateGraphAndTest.cc, FindPaths.cc, amd graph.h

This is the README for Homework 5.