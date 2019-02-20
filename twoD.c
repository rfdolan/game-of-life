// 2D Array -- Raymond Dolan

#include <stdio.h>
#include <stdlib.h>
#include "twoD.h"

/** Make a 2D array of integers (this is an example)
 *
 * @param nrows Number of rows
 * @param ncolumns Number of columns
 * @return Pointer to the array of pointers to the rows.
 * 	  or null pointer if unable to allocate memory.
 * 	  Note: Will not free partially-allocated memory.
 *
 * @author Mike Ciaraldi
 */


/** Make a 2D array of characters
 *
 * @param nrows Number of rows
 * @param ncolumns Number of columns
 * @return Pointer to the array of pointers to the rows.
 *        or null pointer if unable to allocate memory.
 *        Note: Will not free partially allocated memory.
 * 
 * @author Raymond Dolan
 */
char** make2Dchar(int nrows, int ncolumns) {

	char **a; // Array of pointers to rows
	unsigned int i; //Loop counter

	//First allocate the array of pointers to rows
	a = (char**) malloc(nrows * sizeof(char *));
	if (!a) { //Unable to allocate the array
		return (char**) NULL;
	}

	//Now allocate array for each row
	for (i = 0; i < nrows; i++){
		//i is the row we are about to allocate
		a[i] = malloc(ncolumns * sizeof (char));
		if (!a[i]){
			return (char**) NULL; //Unable to allocate
		}
	}
	return a;
}

/**
 * freeMem frees the memory taken up by a 2d array.
 * @param Array is the array whose memory we want to clear.
 * @param rows is the number of rows that the array has.
 * @return this function returns void
 */
void freeMem(char **Array, int rows){
	for(int i=0; i<rows; i++){
		// At this point in the loop tehere is at least one more row whose contents need to be freed.
		free(Array[i]);
	}
	// Here Array is a 1D array again, so we can just free it.
	free(Array);
}

/**
 * equals takes two 2D arrays of the same size and compares them for equality.
 * @param First is one of the 2D arrays that is being compared.
 * @param Second is the other array that is being compared.
 * @param nr is the number of rows each array has.
 * @param nc is the number of columns each array has.
 * @return int a nonzero value if they are equal and zero if they are not.
 * NOTE: Arrays passed into this functino are assumed to be the same size.
 */
int equals(char **First, char **Second,int nr,int nc){
	int row = 0;
	int column = 0;
	while(row < nr){
		// Invarient: The current row has not been completely checked for equality.
		while(column < nc){
			// Invarient: The current column has not been completely checked for equality.
			// Check if the character at the current space is the same in both arrays.
			if(First[row][column] == Second[row][column]){
				// If they are the same, continue comparing.
				column++;
			}
			else{
				//If they are not the same, return false.
				return 0;
			}
		}
		// When we reach the end of the row, reset the column incrementer and move to the next row.
		column = 0;
		row++;
	}
	// I every value in both arrays was ther same, return true.
	return 1;
}

