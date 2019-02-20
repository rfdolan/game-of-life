/* Game of Life -- Raymond Dolan
*/
#include <stdio.h>
#include <stdlib.h>
#include "twoD.h"
#define LIVE_CELL 'x'
#define DEAD_CELL 'o'


/**
 * cellExists checks to see if the given cell is within the board.
 * @param row is the row in which the space in question is located.
 * @param column is the column in which the space in question is located.
 * @param nr is the number of rows that the board has.
 * @param nc is the number of columns that the board has.
 * @return either 0 for false or a nonzero number for true, signifying whether the given cell is on the board or not.
 */
int cellExists(unsigned int row, unsigned int column, unsigned int nr, unsigned int nc){
	// Here the program checks to see if our space is inside of the board by making sure that it is not in a 
	// negative row/column or one outside of our bounds.
	return(column >= 0 && column < nc && row >= 0 && row < nr);
}

	
/**
 * numAliveAdjacent finds the number of live cells around a given cell.
 * @param row is the row in which our cell is located.
 * @param column is the column in which our cell is located.
 * @param nr is the number of rows on our board.
 * @param nc is the number of columns on our board.
 * @param Board is the 2D array holding our game of life at this time.
 * @return int This function returns the number of alive nodes adjacent to the given node.
 */
int numAliveAdjacent(unsigned int row, unsigned int column, unsigned int nr, unsigned int nc, char **Board){
	int numAlive = 0; // Store the number of alive cells in a variable
	// In each of the following statements below the program checks to see if a cell adjacent to the given is on
	// the board, and if it is, the program then checks to see if that adjacent cell is occupied by an alive node.
	// If yes, then it adds one to numAlive.
	if(cellExists(row-1,column-1,nr,nc)){
		if(Board[row-1][column-1] == LIVE_CELL){
			numAlive++;
		}
	}
	if(cellExists(row-1,column,nr,nc)){
		if(Board[row-1][column] == LIVE_CELL){
			numAlive++;
		}
	}
	if(cellExists(row-1,column+1,nr,nc)){
		if(Board[row-1][column+1] == LIVE_CELL){
			numAlive++;
		}
	}
	if(cellExists(row,column-1,nr,nc)){
		if(Board[row][column-1] == LIVE_CELL){
			numAlive++;
		}
	}
	if(cellExists(row,column+1,nr,nc)){
		if(Board[row][column+1] == LIVE_CELL){
			numAlive++;
		}
	}
	if(cellExists(row+1,column-1,nr,nc)){
		if(Board[row+1][column-1] == LIVE_CELL){
			numAlive++;
		}
	}
	if(cellExists(row+1,column,nr,nc)){
		if(Board[row+1][column] == LIVE_CELL){
			numAlive++;
		}
	}
	if(cellExists(row+1,column+1,nr,nc)){
		if(Board[row+1][column+1] == LIVE_CELL){
			numAlive++;
		}
	}
	return numAlive; // Return the number of cells that are alive.
}

/**
 * PlayOne takes in an array with a board state and gives the state after one generation.
 * @param nr is an integer representing the number of rows on the board.
 * @param nc is an integer representing the number of columns on the board.
 * @param Old[][] is the boardstate given to the function.
 * @param New[][] is the array that will be updated with the new boardstate. 
 * @return this function returns void.
 */
void PlayOne (unsigned int nr, unsigned int nc, char **Old, char **New){
	for(int i = 0; i < nr; i++){ //go through the rows
		// Invarient: At this point in the loop, there are still rows that need to be checked.
		for(int j = 0; j < nc; j++){ //go through the columns
			//Invarient: At this point in the loop there are still columns that need to be checked.
			char currentSpace = Old[i][j];
			if(currentSpace == DEAD_CELL ){
				// If our current space is dead and has exactly 3 neighbors, its corresponding 
				// space in the new array becomes alive.
				if(numAliveAdjacent(i, j, nr, nc, Old) == 3){
					New[i][j] = LIVE_CELL;
				}
				// If there are not 3 neighbors to the dead cell, it's corrresponding space in 
				// the new array remains dead.
				else{
					New[i][j] = DEAD_CELL;
				}
			}
			// If the cell is not dead it must be alive, so if it meets the requirements to survive, 
			// occupy its space in the new array with another live cell.
			else if((1 < numAliveAdjacent(i, j, nr, nc, Old)) && ((numAliveAdjacent(i, j, nr, nc, Old) < 4))){
				New[i][j] = LIVE_CELL;
			}
			// If it does not meet the requirements of survival, occupy its space in the new array with a dead cell
			else{
				New[i][j] = DEAD_CELL;
			}
		}
	}
}

/**
 * output prints a 2D array to the console.
 * @param array is the arrray of characters that we wish to print.
 * @param nr is the number of rows in array.
 * @param nc is the number of columns in the array.
 * @return void, but prints the array to the console.
 */
void output(char **array, unsigned int nr, unsigned int nc){
	int column = 0; // Integer used to increment through the columns.
	int row = 0; // Integer used to increment through the rows.
	while(row < nr){
		// At this point in the loop we are not finished printing the given row.
		while(column<nc){
			// At this point in the loop we are not yet finished printing the given column.
			// If the cell we are currently at is in the array...
			if(cellExists(row,column,nr,nc)){
				// And if it is dead, print a space.
				if(array[row][column] == DEAD_CELL){
					printf(" ");

				}
				// If it is not dead, print a character denoting a live cell.
				else{
					printf("%c", LIVE_CELL);
				}
				column++; // Continue through the column.
			}
		}
		// If we are at the end of a column, we should move to the next line, reset our column incrementer, 
		// and go to the next row.
		printf("\n");
		column = 0;
		row++;
	}	
}

/**
 * center moves the pattern to the appproximate center of the board.
 * @param Array is the board with the pattern in the top left corner.
 * @param nr is the number of rows in the array.
 * @param nc is the number of columns in the array.
 * @param farthestX is the farthest live cell in the x direction relative to 0.
 * @param farthestY is the farthesy live cell in the y direction relative to 0.
 * @return void but the inputted Array is modified to now have the pattern in the center.
 */
void center(char **Array,int nr,int nc,int farthestX,int farthestY){
	char **buffer = make2Dchar(nr, nc); // Create a buffer array.
	int xOffset = ((nc-farthestX)/2); // Create a variable to hold how far in the x direction we should offest the pattern.
	int yOffset = ((nr-farthestY)/2); // Create a variable to hold how far in the y direction we should offest the pattern.
	// Fill the buffer with dead cells.
	for(int i=0; i<nr; i++){
		// Invarient: The current row is not completely full of dead cells.
		for(int j=0; j<nc; j++){
			// Invarient: The current column is not completely full of dead cells.
			buffer[i][j] = DEAD_CELL;
		}
	}
	// Place the pattern in the center of the buffer.
	for(int i=0; i<=farthestY;i++){
		// Invarient: The current row of buffer does not have the entire pattern filled in yet.
		for(int j=0; j<=farthestX;j++){
			// Invarient: The curretn column of buffer does not have the entire pattern filled in yet.
			buffer[i+yOffset][j+xOffset] = Array[i][j];
		}
	}
	// Copy buffer into our original array.
	for(int i=0; i<nr;i++){
		// Invarient: The current row has not been completely copied into Array yet.
		for(int j=0; j<nc; j++){
			// Invarient: The current column has not been completely copied into Array yet.
			Array[i][j] = buffer[i][j];
		}
	}
	// Free the memory used by buffer.
	freeMem(buffer, nr);
}

/** Main function.
 * @param argc Number of words on the command line.
 * @param argv Array of pointers to character strings containing the
 *    words on the command line.
 * @return 0 if success, 1 if invalid command line or unable to open file.
 *
 */
int main(int argc, char **argv) {
	printf("Game of Life\n");

	char *inputFileName; // Name of file containing initial grid
	FILE *input; // Stream descriptor for file containing initial grid
	int nrows; // Number of rows in the grid
	int ncolumns; // Number of columns in the grid
	int gens; // Number of generations to produce
	int doPrint; // 1 if user wants to print each generation, 0 if not
	int doPause; // 1 if user wants to pause after each generation, 0 if not
	char **gridA; // A 2D array to hold the previous generation of the pattern
	char **gridB; // A 2D array to hold the current generation of the pattern
	char **gridC; //A 2D array to be filled with the next generation of the pattern

	// See if there are the right number of arguments on the command line
	if ((argc < 5) || (argc > 7)) {
		// If not, tell the user what to enter.
		printf("Usage:\n");
		printf("  ./life rows columns generations inputFile [print] [pause]\n");
		return EXIT_FAILURE;
	}

	/* Save the command-line arguments.
	   Also need to check if print and/or pause arguments were entered,
	   and if so, what they were.
	   A switch statement might be handy here.
	*/
	nrows = atoi(argv[1]); // Convert from character string to integer.
	ncolumns = atoi(argv[2]);
	gens = atoi(argv[3]);
	inputFileName = argv[4];
	doPause = 0;
	doPrint = 0;
	switch (argc){
		// If there are 7 arguments, make the value of doPause correspond with what was entered.
		case(7):
			if(argv[6][0] == 'y'){
			       	doPause = 1;
			}
		// If there were 6 arguments or we fell through from the previous statement, update doPrint accordingly.
	 	case(6):
			if(argv[5][0] == 'y'){
				doPrint = 1;
			}
			break;
	}		

	// Allocate the arrays that will hold the grid
	gridA = make2Dchar(nrows, ncolumns); // Grid that will hold our oldest array.
	gridB = make2Dchar(nrows, ncolumns); // Grid that will hold the current generation (Old in the PlayOne function).
	gridC = make2Dchar(nrows, ncolumns); // Grid that will be updated with the next generation (New in the PlayOne function).

	// Attempt to open the input file.
	input = fopen(inputFileName, "r");
	// If the input file is not able to be opened, return a failure.
	if (!input) { 
		printf("Unable to open input file: %s\n", inputFileName);
		freeMem(gridA, nrows);	
		freeMem(gridB, nrows);
		freeMem(gridC, nrows);
		return EXIT_FAILURE;
	}

	int c; // Character that holds the current character from the file.
	int row = 0; // Integer that tells us what row in the array we are updating.
	int column = 0; // Integer that tells us what column in the array we are updating.
	int farthestX = 0; // Integer that holds the farthest live cell in the x direction.
	int farthestY = 0; // Integer that holds the farthest live cell in the y direction.
	while((c = fgetc(input)) != EOF){
		// Invarient: At this point in the loop we have not his the end of the file yet.
		// If the number of columns and number of rows are more that where we currently are, check what character we have.
		if(column < ncolumns && row < nrows){
			// If the character is a dead cell, update gridB accordingly.
			if(c == DEAD_CELL){
				gridB[row][column] = c;
				column++;
			}
			// If a character is alive, check if it is the farthest in the x or y direction and update accordingly
			else if(c == LIVE_CELL){
				gridB[row][column] = c;
				if(farthestX < column){
					farthestX = column;
				}
				if(farthestY < row){
					farthestY = row;
				}
				column++;
			}
			// If our next character is a newline, then keep adding dead cells until we have filled the row.
			else if(c == '\n'){
				while(column < ncolumns){
					// Invarient: At this point in the loop we have not reached the end of the current row.
					gridB[row][column] = DEAD_CELL;
					column++;
				}
				// Increment to the next row and reset our column index after we have reached the end of the row.
				row++;
				column = 0;
			}
			// If the character is not a live cell, dead cell, or newline, it is invalid, so return an error.
			else{
				printf("Invalid character! \n");
				freeMem(gridA, nrows);
				freeMem(gridB, nrows);
				freeMem(gridC, nrows);
				return EXIT_FAILURE;
			}
		}
		// If the file has more data in it that the board cna fit, return an error.
		else{
			printf("Input file too large! \n");
			freeMem(gridA, nrows);
			freeMem(gridB, nrows);
			freeMem(gridC, nrows);
			return EXIT_FAILURE;
		}	
	}

	// Close the file buffer
	fclose(input);

	// Fills up the rest of the grid with dead cells.	
	while(row < nrows){
		// Invarient: At this point the last row of the board has not yet been filled with dead cells.
		while(column < ncolumns){
			// Invarient: At this point the last column has not yet been filled with dead cells.
			gridB[row][column] = DEAD_CELL;
			column++;
		}
		// Once we reach the end of a row, increment the row and reset the column index.
		row++;
		column = 0;
	}

	// Center the pattern.
	center(gridB, nrows, ncolumns, farthestX, farthestY);

	char **Temp; // Placeholder value to be used when reallocating the arrays
	int currentGen = 0; // Integer to keep track of what generation we are on
	
	// Print the first generation.
	output(gridB, nrows, ncolumns);

	//play the game, pausing and printing as requested	
	while(currentGen < gens){
		// Invarient: Not every desired generation has been played.
		PlayOne(nrows, ncolumns, gridB, gridC); // Preform one generation.
		// If the user wants to print every generation, print the board C (the current board).
		if(doPrint){
			output(gridC, nrows, ncolumns);
		}
		// If the n-1st and n+1st boards are the same, we are oscillating, so exit.
		if(equals(gridA, gridC, nrows, ncolumns)){
			// If it hasn't been printed already, print the final generation.
			if(!doPrint){
				output(gridB, nrows, ncolumns);
			}
			printf("%s %d %s \n", "Terminated after ", (currentGen + 1), 
			" generations. Reason: Oscillating between two states.");
			freeMem(gridA, nrows);
			freeMem(gridB, nrows);
			freeMem(gridC, nrows);
			return EXIT_SUCCESS;
		}
		// If the nth and n+1st boards are the same, we are in a steady state, so exit.
		if(equals(gridB, gridC, nrows, ncolumns)){
			// If it hasn't been printed already, print the final generation.
			if(!doPrint){
				output(gridB, nrows, ncolumns);
			}
			printf("%s %d %s \n", "Terminated after ", (currentGen + 1), 
			" generations. Reason: Steady state reached.");
			freeMem(gridA, nrows);
			freeMem(gridB, nrows);
			freeMem(gridC, nrows);
			return EXIT_SUCCESS;
		}
		// If the user wants to pause before every generation, wait for them to press a key.
		if(doPause){
			printf("Press enter to proceed to next generation.");
			getchar();	
		}
		Temp = gridA; // Assign the value of A(the previous generation's board) to Temp.
		gridA = gridB; // Assign the value of B(the current board) to A
		gridB = gridC; // Assign the value of C (the new board) to B.
		gridC = Temp; // Assign the value of Temp (an unimportant board) to C.
		currentGen++; // Increment the generation.
	}	

	// If it hasn't been printed already, print the final generation.
	if(!doPrint){
		output(gridB, nrows, ncolumns);
	}
	printf("%s %d %s \n", "Terminated after ", currentGen, " generations. Reason: Target number of generations reached.");
	 
	freeMem(gridA, nrows);
	freeMem(gridB, nrows);
	freeMem(gridC, nrows);
	return EXIT_SUCCESS;
}


