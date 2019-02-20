Raymond Dolan -- Assignment 2

My program takes in an input of a pattern from a .txt file and runs the game of life on it on
a board of the specified size for the specified number of generations or until a steady state
or oscillation is reached. The user may also have the program print the board at each step and/or
wait until the user presses enter to continue. The input for the function is as follows

./life numberOfRows numberOfColumns numberOfGenerations inputFileName [whether or not to print (y/n)] [whether or not to pause at each step (y/n)]

The number of rows should be a positive integer value.

The number of columns should be a positive integer value.

The number of generations should be a positive integer value.

The format for the input file is as follows. The user should enter an "x" for living cells they want and
an "o" for dead cells. The pattern should make a rectangle, with "o"s filling in the spaces between "x"s. 

The printing and pausing arguments are optional, and default to n if not specified. 

