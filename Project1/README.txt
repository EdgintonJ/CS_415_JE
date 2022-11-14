
Name: Jordan Edginton 	1 member
CS415 SP '21
Project 01


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

When running the program:

	All 3 tasks are in the program Project_01.py
	
	When you run the program a prompt will apear. It will ask for an input to determine which
	mode to run (M/m for manual input [user testing mode], S/s for scatter-plot, and Q/q to quit). 

	If manual is chosen, more prompts will pop up to ask for the variables for k in task 1, both a and n in task 2,
	and the file index for the insertion and selction sort in task 3. After all variables have been input, the results for 
	each of the tasks will be printed out. No scatterplot will print.

	If scatter-plot is chosen the values of the fibonacci, euclid, and n value for exp(a,n) are from 1 to 21; while the
	values for the sorting files are from 100-900. After a minute of running 5 matplotlib windows will pop up, 
	with each window labeled as the task (Task 1, Task 2, Task 3 best case, Task 3 average case, and Task 3 worst case). 
	Task 1 will not have a legend (I didn't think it was needed), but task 2 and 3 both have legends to 
	specify the lines on the graph. When finished, close all plot windows and the program will end.

Notes:
	There are 2 fibonacci functions, one that is recursive and the other that uses the formula. For task 1 calculations,
	only the formula function [fib_formula()] was used to save run time. 
	
	I will admit, I still don't fully understand matplotlib and the code is a mess because of that; but it works.

	I used code or used information from the following websites, all having to do with using matplotlib and pycharm:
	(just citing my sources)

		https://matplotlib.org/stable/index.html

		https://www.jetbrains.com/help/pycharm/installing-uninstalling-and-upgrading-packages.html

		https://stackoverflow.com/questions/6541123/improve-subplot-size-spacing-with-many-subplots-in-matplotlib

		https://stackoverflow.com/questions/43832268/create-a-legend-outside-of-the-graph




