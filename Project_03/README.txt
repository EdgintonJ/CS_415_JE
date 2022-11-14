
Name: Jordan Edginton 	1 member
CS415 SP '21
Project 03a


The following is the software needed/used:
	C++ 17
	Clion 2019.3.4
	"cmake_minimum_required(VERSION 3.15)"
	MinGW compiler was used

With the exception of some includes (<time.h>, <deque>), there are no packages in the project.	

When running the program:
	The program requires 1 argument which is a .txt file for the input. 
	When the program is started, a prompt will appear asking whether the user wants to make the index using a BST(a), 
	a 2-3 tree(b), make both and search for every word(c), or quit (d). if a or b are chosen, the tree will be created and the 
	user will be asked 4 options: print the entire index (1), search for a word in te index (2), create a file
	containing the index (3), or quit (4). if c is chosen, the user will not be prompted anything and the system will print out 
	the tree constructors along with the times it took to search for every item in both trees.

Notes:
	I basically copy-pasted the BST class for my 2-3 tree class (Btree) and just modified existing functions
	and variables as well as creating some new functions.
	
	For my reOrgTree() function, I used code from one of my CS315 projects that 
	required us to iterately traverse through a BST. I just modified it for the 2-3 tree.

	I think my reOrgTree() function could have been more efficient, but I'm strapped for time 
	and I don't want to risk breaking my project.

	I couldn't test option c for the engmix_sanitized.txt (BST recursion depth), even when setting 
	clion to release (it was on debug). I did make a shortened version however (only ~6k words) which did work.




