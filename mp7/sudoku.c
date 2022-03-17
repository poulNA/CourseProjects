#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

/* \|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||/
    This program completes a sudoku board from an incomplete board. is_val_in_row, is_val_in_col,
    and is_val_in_3x3 checks if a certain number is already in that row, col, or 3x3 respectively.
    The is_val_valid function uses the previously stated functions to see if a given number is a 
    valid number for that cell. It makes sure the value is not already in the row, col, and 3x3.
    solve_sudoku checks if the board is full, which will end it. If not, then it will call onto 
    is_val_valid and see what number it can place in the cell. It will then call itself(solve_sudoku)
    again until it reaches the base case if board is completed.

    Partners: ilashl2, gangulo2
   \|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||/
*/
// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  // Fix the row and iterate through cols
  for (int c = 0; c < 9; c++) {
      if (sudoku[i][c] == val) {
	 return 1;
      }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  // Fix the col and iterate through rows
  for (int r = 0; r < 9; r++) {
      if (sudoku[r][j] == val) {
	 return 1;
      }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  // Default to top-left corner of the current box
  int x = (i/3)*3;
  int y = (j/3)*3;

  int row_i ;
  int col_i ;
  // From top-left corner iterate down and right two spaces
  for (row_i = 0; row_i < 3 ; row_i ++) {
      for (col_i = 0; col_i < 3 ; col_i ++) {
 	  if (sudoku[x + row_i][y + col_i] == val) {
	     return 1;
	  }
      }
  }
 return 0;
      
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);
  // BEG TODO
  // All should be 0
	if(is_val_in_row(val,i,sudoku) == 0 && is_val_in_col(val,j,sudoku) == 0 && is_val_in_3x3_zone(val,i,j,sudoku) == 0 ){
  return 1;
}
	else{
		return 0;
	}
	
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i, j;
  int cell;
  // Check board if complete. If not jump.
  for(int r = 0; r < 9; r++){
	for(int c = 0; c < 9; c++){
		   if (sudoku[r][c] == 0) {	 
		   i = r;
		   j = c;	
		goto fill; 
		}
		
	}
  } return 1;
  // Go through 1 to 9 to see if it's a valid number to put in current cell. Use recursive to repeat until board is complete.
  fill:
  for (int num = 1; num < 10; num++) {
      if (is_val_valid(num, i, j, sudoku) == 1) {
	 sudoku[i][j] = num;
	 if (solve_sudoku(sudoku) == 1) {
	    return 1;
	 }
	 sudoku[i][j] = 0;
      }
  }
  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





