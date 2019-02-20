/**
 * twoD.h
 *
 * @author: Mike Ciaraldi
 */

#ifndef TWOD_H_
#define TWOD_H_

// Function prototypes:
int** make2Dint(int nrows, int ncolumns);
char** make2Dchar(int nrows, int ncolumns);
void freeMem(char **Array, int size);
int equals(char **Array, char **Other, int nr, int nc);
#endif /* 2D_H_ */
