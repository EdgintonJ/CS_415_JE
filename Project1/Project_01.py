"""
Program: CS-415 Project 01
Author: Jordan Edginton
Description: This purpose of this project is to help us figure out the asymptotic complexity
of multiple algorithms. There are two modes to the program and the user will determine which mode to use.
The program will provide the user with scatter-plots, if requested, to show the complexity
of the algorithms in the program.
"""

import sys
import math
import matplotlib.pyplot as plt
import numpy as np

# Here we initialize our global variables, mainly used for tracking comparisons and multiplications
euc_div = 0
dbo = 0                     # Decrease By One multiplications
dcf = 0                     # Decrease by Constant Factor multiplications
dac = 0                     # Divide And Conquer multiplications
sel_cmp = 0                 # Selection Comparisons
ins_cmp = 0                 # Insertion Comparisons
list_to_sort = []           # Our list to sort, filled in open_file(), used in manual
rev_list_to_sort = []       # Our list that is reverse sorted, filled in open_file(), not used in manual
list_sorted = []            # Our list that is already sorted, filled in open_file(), not used in manual


def open_file(folder, idx):
    '''
    Here we open our files that hold our items to be sorted and put them
    into the global list variables. The parameter idx represents the index of the file and folder
    represents which folder (smallSet or testSet) to use.
    '''
    global list_to_sort
    global rev_list_to_sort
    global list_sorted
    list_to_sort = []
    rev_list_to_sort = []
    list_sorted = []
    if folder == 1:
        filename = "smallSet/data"
    else:
        filename = filename_rev = filename_sorted = "testSet/data"
        filename_rev += str(idx)
        filename_rev += "_rSorted.txt"
        filename_sorted += str(idx)
        filename_sorted += "_sorted.txt"
        rev_file = open(filename_rev, "r")
        sorted_file = open(filename_sorted, "r")
    filename += str(idx)
    filename += ".txt"
    sort_file = open(filename, "r")
    while 1:
        read_line = sort_file.readline()
        if read_line == '':
            break
        list_to_sort.append(int(read_line))
    if folder != 1:
        while 1:
            read_line = rev_file.readline()
            if read_line == '':
                break
            rev_list_to_sort.append(int(read_line))
        while 1:
            read_line = sorted_file.readline()
            if read_line == '':
                break
            list_sorted.append(int(read_line))


def fib_rec(x):
    '''
    Here is the recursive function for the fibonacci sequence. it isn't used due to run-time
    '''
    if x == 0:
        return 0
    if x == 1:
        return 1
    return fib_rec(x-1) + fib_rec(x-2)


def fib_formula(n):
    '''
    Here is the fibonacci sequence using the formula. This function is used in all fibonacci
    calculation to reduce run time.
    '''
    if n < 0:               # in case input was less than 1
        return 0
    fi = (1 + pow(5, .5)) / 2
    fi_hat = -1 / fi
    return math.floor((1 / pow(5, .5)) * (pow(fi, n) - pow(fi_hat, n)))


def euclid(n1, n2):
    '''
    Here is where we calculate the Greatest Common Denominator of two numbers using Euclid's algorithm
    Along the way it modifies the global variable euc_div to keep track of the amount of divisions.
    It returns the GCD of the two numbers
    '''
    if n2 == 0:         # in case input was less than 1
        return 0
    base = n1
    sub = n2
    global euc_div
    euc_div = 0
    while 1:
        x = base % sub
        euc_div += 1
        if x == 0:
            break
        base = sub
        sub = x
    return sub


def dec_by_one(a, n):
    '''
    Here is one of our recursive functions for calculating an exponential: Decrease By One.
    Parameter a is our base and n is our exponent. Our base case is 1 to reduce run time
    '''
    if n == 1:
        return a
    global dbo
    dbo = dbo + 1
    return a * dec_by_one(a, n-1)


def dec_by_constant(a, n):
    '''
    Here is one of our recursive functions for calculating an exponential: Decrease by Constant Factor.
    Parameter a is our base and n is our exponent. Our base case is 1 to reduce run time
    '''
    if n == 1:
        return a
    global dcf
    dcf = dcf + 1
    if n % 2 == 1:
        return dec_by_constant(a, (n - 1) / 2) ** 2 * a
    else:
        return dec_by_constant(a, n / 2) ** 2


def divide_and_conquer(a, n):
    '''
    Here is one of our recursive functions for calculating an exponential: Divide and conquer.
    Parameter a is our base and n is our exponent. Our base case is 1 to reduce run time
    '''
    if n == 1:
        return a
    global dac
    dac = dac + 1
    if n % 2 == 1:
        return divide_and_conquer(a, (n-1)/2) * divide_and_conquer(a, (n-1)/2) * a
    else:
        return divide_and_conquer(a, n/2) * divide_and_conquer(a, n/2)


def insertion_sort(inp_list):
    '''
    Here we take a list as our parameter, sort it, and return the sorted list.
    Along the way we update our insertion comparison global variable.
    '''
    global ins_cmp
    ins_cmp = 0
    for i in range(0, len(inp_list) - 1):
        ins_cmp += 1
        if inp_list[i] > inp_list[i + 1]:
            iter = i
            while iter >= 0 and inp_list[iter] > inp_list[iter + 1]:
                ins_cmp += 1
                temp = inp_list[iter + 1]
                inp_list[iter + 1] = inp_list[iter]
                inp_list[iter] = temp
                iter -= 1
            ins_cmp += 1
    return inp_list


def selection_sort(inp_list):
    '''
    Here we take a list as our parameter, sort it, and return the sorted list.
    Along the way we update our insertion comparison global variable.
    '''
    global sel_cmp
    sel_cmp = 0
    for i in range(0, len(inp_list) - 1):
        idx = i
        for j in range(i, len(inp_list)):
            sel_cmp += 1
            if inp_list[i] > inp_list[j]:
                idx = j
        temp = inp_list[idx]
        inp_list[idx] = inp_list[i]
        inp_list[i] = temp
    return inp_list


def manual():
    """
    This is our function for the manual input mode (user testing mode).
    We prompt the user for the information of all of the variables and perform the calculations.
    Afterwords we print the results of all of the inputs.
    """
    print('Please provide inputs for the following the variables:')
    k = int(input('Task 1, variable k: '))
    a = int(input('Task 2, variable a: '))
    n2 = int(input('Task 2, variable n: '))
    n3 = int(input('Task 3, variable n (10-100, increments of 10): '))
    while n3 % 10 != 0 or n3 > 100 or n3 < 10:
        n3 = int(input('Invalid number, please input number between 10-100 that is an increment of 10: '))
    open_file(1, n3)
    print("\nFibonacci(", k, ") = ", fib_formula(k), sep='')
    print("gcd(fib(", k+1, "), fib(", k, ")) = ", euclid(fib_formula(k+1), fib_formula(k)), sep="")
    if n2 > 0:
        one = dec_by_one(a, n2)
        fact = dec_by_constant(a, n2)
        conq = divide_and_conquer(a, n2)
    else:
        one = fact = conq = 1
    print("\na^n = ", a, "^", n2, sep='')
    print("Dec_by_one: \t\tResult =", one)
    print("Dec_by_constant: \tResult =", fact)
    print("Divide_and_conquer: Result =", conq)
    ins_sorted = insertion_sort(list_to_sort)
    sel_sorted = selection_sort(list_to_sort)
    print("\nInsertion sorted list:")
    for i in range(len(list_to_sort)):
        if i < len(list_to_sort) - 1:
            print(ins_sorted[i], end=', ')
        else:
            print(ins_sorted[i], end='')
    print("\nInsertion sort: comparisons = ", ins_cmp, sep='')
    print("\nSelection sorted list:")
    for j in range(len(list_to_sort)):
        if j < len(list_to_sort) - 1:
            print(sel_sorted[j], end=', ')
        else:
            print(sel_sorted[j], end='')
    print("\nSelection sort: comparisons = ", sel_cmp, sep='')


def scatter_plot():
    '''
    This is our function for the scatter-plot mode.
    Since there is no input, we set our fibonacci and exponents from 1-20, and our files
    for sorting from 100-1000.
    Afterwords we print the results of all of the inputs.
    '''

    # ---Here we initialize all of our lists for the graphs as well as our global variables---
    fib_list = []               # fibonacci additions list
    euc_list = []               # Euclid's divisions list
    dbo_list = []               # Decrease by one multiplications list
    dcf_list = []               # Decrease by constant factor multiplications list
    dac_list = []               # Divide and conquer multiplications list
    ins_list = []               # insertion sort normal file list
    sel_list = []               # selection sort normal file list
    ins_list_rev = []           # insertion sort reversed file list
    sel_list_rev = []           # selection sort reversed file list
    ins_list_sorted = []        # insertion sort sorted file list
    sel_list_sorted = []        # selection sort sorted file list
    global euc_div
    global dbo
    global dcf
    global dac
    global ins_cmp
    global sel_cmp
    global list_to_sort

    # ---Our loop for the fibonacci, Euclid, and exponential tasks---
    for i in range(1, 21):
        fib_list.append(fib_formula(i + 1) - 1)         # using formula to calculate fib additions to reduce run time
        euclid(fib_formula(i + 1), fib_formula(i))
        euc_list.append(euc_div)
        dbo = dcf = dac = 0                             # need to reset globals since those functions are recursive
        dec_by_one(2, i)                                # each exponential task is using a base of 2
        dbo_list.append(dbo)
        dec_by_constant(2, i)
        dcf_list.append(dcf)
        divide_and_conquer(2, i)
        dac_list.append(dac)

    # ---Our loop for the insertion and selection sorting tasks---
    for j in range(1, 10):
        open_file(2, j * 100)
        insertion_sort(list_to_sort)
        ins_list.append(ins_cmp)
        selection_sort(list_to_sort)
        sel_list.append(sel_cmp)
        insertion_sort(rev_list_to_sort)
        ins_list_rev.append(ins_cmp)
        selection_sort(rev_list_to_sort)
        sel_list_rev.append(sel_cmp)
        insertion_sort(list_sorted)
        ins_list_sorted.append(ins_cmp)
        selection_sort(list_sorted)
        sel_list_sorted.append(sel_cmp)

    # ---x coordinates for our scatter-plots---
    x_coords = np.arange(1, 21, 1)
    sort_coords = np.arange(100, 1000, 100)

    # ---Plot for task 1---
    fig_task_1 = plt.figure('Task 1')
    plt.subplots_adjust(left=.125, bottom=.11, right=.9, top=.88, wspace=.2, hspace=.5)
    task_a = fig_task_1.add_subplot(211)
    task_a.set_title('Fibonacci additions')
    task_a.set_xlabel('k value for Fib(k)')
    task_a.set_ylabel('A(k)')
    task_a.plot(x_coords, fib_list, 'ro')
    task_a.plot(x_coords, fib_list, '-r')

    task_b = fig_task_1.add_subplot(212)
    task_b.set_title("Euclid's algorithm")
    task_b.set_xlabel('k value for gcd(fib(k+1), fib(k))')
    task_b.set_ylabel('D(k)')
    task_b.plot(x_coords, euc_list, 'bo')
    task_b.plot(x_coords, euc_list, '-b')

    # ---Plot for task 2---
    fig_task_2 = plt.figure('Task 2')
    fig_task_2.subplots_adjust(left=.125, bottom=.11, right=.9, top=.88, wspace=.2, hspace=.5)
    exp_task = fig_task_2.add_subplot(211)
    exp_task.set_title('Exponent multiplications')
    exp_task.set_xlabel('Exponent')
    exp_task.set_ylabel('M(n)')
    exp_task.plot(x_coords, dbo_list, 'ro')         # decrease by one
    exp_task.plot(x_coords, dbo_list, '-r')
    exp_task.plot(x_coords, dcf_list, 'bo')         # decrease by constant factor
    exp_task.plot(x_coords, dcf_list, '-b')
    exp_task.plot(x_coords, dac_list, '-g')         # divide and conquer
    exp_task.plot(x_coords, dac_list, 'go')
    # ---Legend setup for exponential algorithms---
    line1 = exp_task.plot(x_coords, dbo_list, 'ro', label='Decrease by one', linewidth=1.0)
    line2 = exp_task.plot(x_coords, dcf_list, 'bo', label='Constant factor', linewidth=1.0)
    line3 = exp_task.plot(x_coords, dac_list, 'go', label='Divide and conquer', linewidth=1.0)
    lns = line1 + line2 + line3
    labels = [l.get_label() for l in lns]
    plt.legend(lns, labels, loc='center left', bbox_to_anchor=(0.7, -0.4))

    # ---Plot for task 3, Best case---
    fig_task_best = plt.figure('Task 3, best case')
    plt.subplots_adjust(left=.15, bottom=.11, right=.9, top=.88, wspace=.2, hspace=.5)
    best_plot = fig_task_best.add_subplot(211)
    best_plot.set_title('Best case')
    best_plot.set_xlabel('file index')
    best_plot.set_ylabel('C(n)')
    best_plot.plot(sort_coords, sel_list_sorted, 'bo')
    best_plot.plot(sort_coords, sel_list_sorted, 'b-')
    best_plot.plot(sort_coords, ins_list_sorted, 'r-')
    best_plot.plot(sort_coords, ins_list_sorted, 'ro')
    # ---Legend setup for selection sort---
    line1 = exp_task.plot(x_coords, dbo_list, 'ro', label='Insertion', linewidth=1.0)
    line2 = exp_task.plot(x_coords, dcf_list, 'bo', label='Selection', linewidth=1.0)
    lns = line1 + line2
    labels = [l.get_label() for l in lns]
    plt.legend(lns, labels, loc='center left', bbox_to_anchor=(0.7, -0.4))

    # ---Plot for task 3, Average case--
    fig_task_avg = plt.figure('Task 3, average case')
    plt.subplots_adjust(left=.15, bottom=.11, right=.9, top=.88, wspace=.2, hspace=.5)
    avg_plot = fig_task_avg.add_subplot(211)
    avg_plot.set_title('Average case')
    avg_plot.set_xlabel('file index')
    avg_plot.set_ylabel('C(n)')
    avg_plot.plot(sort_coords, sel_list, 'bo')
    avg_plot.plot(sort_coords, sel_list, 'b-')
    avg_plot.plot(sort_coords, ins_list, 'r-')
    avg_plot.plot(sort_coords, ins_list, 'ro')
    # ---Legend setup for selection sort---
    line1 = exp_task.plot(x_coords, dbo_list, 'ro', label='Insertion', linewidth=1.0)
    line2 = exp_task.plot(x_coords, dcf_list, 'bo', label='Selection', linewidth=1.0)
    lns = line1 + line2
    labels = [l.get_label() for l in lns]
    plt.legend(lns, labels, loc='center left', bbox_to_anchor=(0.7, -0.4))

    # ---Plot for task 3, worst case---
    fig_task_worst = plt.figure('Task 3, worst case')
    plt.subplots_adjust(left=.15, bottom=.11, right=.9, top=.88, wspace=.2, hspace=.5)
    worst_plot = fig_task_worst.add_subplot(211)
    worst_plot.set_title('Worst case')
    worst_plot.set_xlabel('file index')
    worst_plot.set_ylabel('C(n)')
    worst_plot.plot(sort_coords, sel_list_rev, 'bo')
    worst_plot.plot(sort_coords, ins_list_rev, 'r-')
    # ---Legend setup for selection sort---
    line1 = exp_task.plot(x_coords, dbo_list, 'ro', label='Insertion', linewidth=1.0)
    line2 = exp_task.plot(x_coords, dcf_list, 'bo', label='Selection', linewidth=1.0)
    lns = line1 + line2
    labels = [l.get_label() for l in lns]
    plt.legend(lns, labels, loc='center left', bbox_to_anchor=(0.7, -0.4))

    plt.show()
    plt.close(1)


def main():
    '''
    The main function of the program. We prompt the user for an input and activate either
    manual (user input) or scatter-plot mode based on the input.
    '''
    inp = str(input('Please choose mode: manual input (M/m), scatter-plot (S/s), or quit (Q/q)\n'))
    while inp != 'm' and inp != 'M' and inp != 'S' and inp != 's':
        if inp == 'q' or inp == 'Q':
            sys.exit(0)
        inp = str(input('Invalid input. Please choose mode: manual input (M or m), scatter-plot (S or s), '
                        'or quit (Q/q)\n'))
    if inp == 'm' or inp == 'M':
        manual()
    else:
        scatter_plot()


main()
