"""
Program: CS-415 Project 02b
Author: Jordan Edginton
Description: This purpose of this project is to multiply large integers using karatsuba's
algorithm for multiplication. We ask the user for inputs and convert those input(s) into arrays to
be used for single-digit multiplications.
"""

import sys


def user_inp():
    '''
    Here we get the user's input for the 2 tasks. We make sure that both the
    inputs are an integer (0-9) and that it's within range (1-1000).
    '''
    inp = str(input('Please enter a number between 1-1000\n'))
    while 1:
        try:
            ret = int(inp)
            x = 1
        except ValueError:
            inp = str(input('Invalid input, please enter an integer between 1-1000\n'))
            x = 0
        if x == 1:
            if ret > 1000 or ret < 1:
                inp = str(input('Input out of range, please enter an integer between 1-1000\n'))
            else:
                break
    return ret


def int_to_array(inp):
    '''
    This function converts an integer into an array that we can use for karatsuba's algorithm.
    Only used for user inputs.
    '''
    ret_arr = []
    inp_str = str(inp)
    for i in range(len(inp_str)):
        ret_arr.append(int(inp_str[i]))
    return ret_arr


def array_to_int(arr):
    '''
    This function converts an array to an integer. Only used for printing the final results.
    '''
    ret_val = 0
    for i in range(len(arr)):
        ret_val += arr[-i - 1] * 10 ** i
    return ret_val


def karatsuba_mult(a, b):
    '''
    This is the function that utilizes karatsuba's algorithm (and it's a doozy).
    First we copy our 2 arrays into variable and then stare any 0's that are their last element [-1] and put them
    aside. we then check if either one has 1 item and if so if that item is 0. if so,
    that would be a multiplication by 0 which would be 0. we then check to see if both arrays have only 1 item
    (this is our base case) and if so, we do our 1-digit multiplication and return. If base-case isn't reached,
    we add 0's to the front of both arrays to make them divisible by 2 for splitting (if needed). We then split
    them and call the function recursively.
    '''

    # --- Set-up our arrays and store any 0's at the ends of them.
    arr_a = a.copy()
    arr_b = b.copy()
    tens = 0
    while arr_a[-1] == 0 and len(arr_a) > 1:
        tens += 1
        arr_a.pop(-1)
    while arr_b[-1] == 0 and len(arr_b) > 1:
        tens += 1
        arr_b.pop(-1)
    if (len(arr_a) == 1 and arr_a[0] == 0) or (len(arr_b) == 1 and arr_b[0] == 0):
        return [0]

    # --- Base case with 1-digit multiplication
    if len(arr_a) == 1 and len(arr_b) == 1:
        one_mult = [0, a[0] * b[0]]             # Here is the 1 digit multiplication
        while one_mult[1] > 9:
            one_mult[0] += 1
            one_mult[1] -= 10
        if one_mult[0] == 0:
            one_mult.pop(0)
        for i in range(tens):
            one_mult.append(0)
        return one_mult

    # --- More array set-up. I wanted to make sure that the bigger array was a, then add 0's to the
    # --- beginning of each array to make them divisible by 2 for splitting.
    if len(arr_a) < len(arr_b):
        temp = arr_b.copy()
        arr_b = arr_a.copy()
        arr_a = temp
    while len(arr_a) > len(arr_b) or len(arr_b) % 2 == 1:
        arr_b.insert(0, 0)
    if len(arr_a) < len(arr_b):
        arr_a.insert(0, 0)

    # --- Here we split the arrays in two.
    left_a = []
    right_a = []
    left_b = []
    right_b = []
    split = int(len(arr_a) / 2)
    for i in range(len(arr_a)):
        if i < split:
            left_a.append(arr_a[i])
            left_b.append(arr_b[i])
        else:
            right_a.append(arr_a[i])
            right_b.append(arr_b[i])

    # --- Here we start our recursive calls
    left = karatsuba_mult(left_a, left_b)
    right = karatsuba_mult(right_a, right_b)
    a_sum = add_array(left_a, right_a, 0)
    b_sum = add_array(left_b, right_b, 0)
    middle = sub_array(karatsuba_mult(a_sum, b_sum), add_array(left, right, 0))

    # --- Here we add our 0's from the split and add back all of the 0's we took out at the beginning
    for s in range(split * 2 + tens):
        left.append(0)
    for s in range(split + tens):
        middle.append(0)
    for p in range(tens):
        right.append(0)

    # --- Here we take out all redundant 0's at the beginning of the arrays (if needed)
    while left[0] == 0 and len(left) > 1:
        left.pop(0)
    while middle[0] == 0 and len(middle) > 1:
        middle.pop(0)
    while right[0] == 0 and len(right) > 1:
        right.pop(0)

    return add_array(left, middle, right)


def add_array(a, b, c):
    '''
    This function is equivalent to 'a + b + c' but with a, b, and c being arrays.
    Some additions require 3 additions, so we check if c == 0 which means there's only 2 additions needed.
    '''
    tot = []
    while len(tot) < len(a) or len(tot) < len(b):
        tot.append(0)
    for i in range(len(a)):
        tot[-1 - i] = a[-1 - i]
    for j in range(len(b)):
        tot[-1 - j] = tot[-1 - j] + b[-1 - j]
    if c != 0:
        while len(tot) < len(c):
            tot.insert(0, 0)
        for k in range(len(c)):
            tot[-1 - k] = tot[-1 - k] + c[-1 - k]
    for g in range(len(tot)):
        while tot[-1 - g] > 9:
            if g == len(tot) - 1:
                tot.insert(0, 0)
            tot[-1 - g] -= 10
            tot[-1 - g - 1] += 1
    return tot


def sub_array(a, b):
    '''
    This function is equivalent to 'a - b' but with a and b being arrays.
    '''
    ret_val = a.copy()
    for i in range(len(b)):
        ret_val[-1 - i] -= b[-1 - i]
    for k in range(len(ret_val) - 1):
        if ret_val[-1 - k] < 0:
            ret_val[-1 - k] += 10
            ret_val[-1 - k - 1] -= 1
    return ret_val


def expo(a, b):
    '''
    This is the exponentiation algorithm for task 2. It uses the Decrease_by_Constant_Factor
    method to go through the recursive calls.
    '''
    if b == 1:
        return a
    if b == 2:
        a2 = a.copy()
        return karatsuba_mult(a, a2)
    if b % 2 == 0:
        return karatsuba_mult(expo(a, b/2), expo(a, b/2))
    return karatsuba_mult(a, karatsuba_mult(expo(a, (b-1)/2), expo(a, (b-1)/2)))


def main():
    '''
    The main function of the program. We prompt the user for an input and activate either
    Task_1(karatsuba_mult()), Task_2 (expo()), or quit depending on the input.
    '''
    while 1:
        inp = str(input('Please choose mode: Task_1 (1), Task_2 (2), or quit (Q/q)\n'))
        while inp != '1' and inp != '2':
            if inp == 'q' or inp == 'Q':
                sys.exit(0)
            inp = str(input('Invalid input. Please choose mode: Task_1 (1), Task_2 (2), or quit (Q/q)\n'))
        if inp == '1':
            a = int_to_array(user_inp())
            b = int_to_array(user_inp())
            print(array_to_int(karatsuba_mult(a, b)))
        else:
            a = int_to_array(user_inp())
            b = user_inp()
            print(array_to_int(expo(a, b)))


main()
