
Name: Jordan Edginton 	1 member
CS415 SP '21
Project 02b


The following is the software needed/used:
	Pycharm 
	Python v 3.8

The following are the packages in the pycharm project (copy-pasted from the project interpreter in pycharm):
	Cython		0.29.22	
	Pillow		8.1.0	
	cycler		0.10.0	
	kiwisolver	1.3.1	
	matplotlib	3.3.4	
	numpy		1.20.1	
	pip		21.0.1	
	pyparsing	2.4.7	
	python-dateutil	2.8.1	
	setuptools	40.8.0	
	six		1.15.0	
	
	Note: I had copied the entire project from project 1 and so these were already in the project, but I didn't use them.
		It should run without them, but I didn't check to make sure. 

When running the program:
	
	When the program is started a prompt will apear. The prompt will ask for an input: Task_1 (1), Task_2 (2), or quit (Q/q).
	If 1 is input, then the karatsuba's algorithm will be applied to the next 2 inputs. If 2 is input, the exponentiation 
	algorithm will be applied. After the task is chosen it will ask for 2 numbers between 1-1000. After both are input
	their result will be printed (it may take a bit of time) and it will go back to the task choosing prompt. This will
	repeat until quit is chosen.

Notes:

	The karatsuba's algorithm picture from wikipedia was a life saver for this project (although implementing it was 
	more difficult). 

	The code for this project is a bit... messy. I think I over-complicated the karatsuba_mult() function and so 
	it's one jumbled mess. 

	I think I did the expo(a, b) function not as intended. I had 'a' be sent as an array instead of as an integer. I did 
	this though because I would have had to convert it to an array for every karatsuba_mult() call 
	and for the base case 'b == 1'. 


