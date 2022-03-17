/*
/|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\
				INTRO

The game of life program requires a countLiveNeighbor function, where 
it checks the surrounding cells of the current one for alive cells. 
This was done by following the given algorithm on the wiki and it
checks one before and one after the given row as well as one before and
one after the given column. It checks for ones and increments the liveN
counter. It also needs an updateBoard function that keeps an alive
cell alive or kills it and keeps a dead cell cead or resurrects it,
depending on the number of live neighbors so we need to call countLiveNeigbor.
The program also needs an aliveStable function to determine whether to end
the game or keep going. It'll check if the board of the next iteration of 
the game is the same as before or zero. It does this by calling on updateBoard
and comparing it to the original.

Partners: ilashl2, gangulo2

\|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||/

 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
    int liveN = 0;
	for (int i = row-1; i <= row+1; i++) {
	    if (0 <= i && i <= boardRowSize-1) {
	       for (int j = col-1; j <= col+1; j++) {
		   if (0 <= j && j <= boardColSize-1) {
		      if ((i*boardColSize+j) != (row*boardColSize+col)) {
			 if (board[i*boardColSize+j] == 1) {
			    liveN++;
			 }
		      }
		   }
	       }
	    }
	}
    return liveN;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
     int liveN = 0;
     int cell = 0;
     int hold[boardRowSize * boardColSize];
     int* temp = hold;
     for (int i = 0; i < boardRowSize; i++) {
	 for (int j = 0; j < boardColSize; j++) {
	     liveN = countLiveNeighbor(board, boardRowSize, boardColSize, i, j);
	     cell = board[i*boardColSize+j];
	     // Alive cell needs 2 or 3 to live
	     if (cell == 1) {
	        if (liveN == 2 || liveN == 3) {
		   temp[i*boardColSize+j] = 1;
		} else {
		      temp[i*boardColSize+j] = 0;
		  }
   	     }
	     // Dead cell needs 3 to come alive
	     if (cell == 0) {
		if (liveN == 3) {
		   temp[i*boardColSize+j] = 1;
		} else {
		      temp[i*boardColSize+j] = 0;
		  }
	     }
	 }
     }
     // Copy board
     for (int i = 0; i < (boardRowSize * boardColSize); i++) {
	 board[i] = temp[i];
     }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
	int current[boardRowSize * boardColSize];
	int* mod = current; 
	int ones = 0;
	//all zeros case
	for (int i = 0; i < (boardRowSize * boardColSize); i++) {
	    if (board[i] == 1) {
	       ones++;
	    }
	}
	if (ones == 0) {
	   return 0;
	}
	// Copy board      
	for (int i = 0; i < (boardRowSize * boardColSize); i++){
	    mod[i] = board[i];
	}
	// Compare alive case
	updateBoard(mod, boardRowSize, boardColSize); 
	for (int j = 0; j < (boardRowSize * boardColSize); j++){ 
	    if (board[j] == 1 && mod[j] != board[j]) {
	       return 0;
	    }
	}
	return 1;	
}

				
				
			

