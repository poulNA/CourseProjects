#include "game.h"
/* \|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||/
				INTRO
    This program is the 2048 game. 
    For make_game, put the input row 
    and col in the game struct for mygame. Initialize each cell to -1
    and score to 0.
    For remake_game, do the same as make_game just with the new ptr,
    row and col.
    For get_cell, make sure the row and col point to a valid cell of 
    the game board. Make sure row and col is >= 0 and < row and column
    size.
    For move_w, create a checker array to keep track of which cells 
    have already been combined. Iterate through a column from top to
    bottom, but skipping the first row and find a non-empty cell. 
    For that non-empty cell, find a empty position closest to the top 
    to put it in. If that non-empty cell is below a cell with the same
    value, then merge the two sums and place it in the cell that was 
    above. Increment the score by that sum. If in that column a cell 
    has already been merged, then don't merge again.
    For move_a, move_s, and move_d, do the same algorithm and consider,
    which way to slide and merge.
    For legal_move_check, iterate through the board and check the bottom
    and right of the current cell. If the bottom or right are empty or 
    the same value as the current cell, then return 1. If not then 
    return 0. When at the rightmost column, don't check to the right
    and when at the bottommost row, don't check below.

    Partners: ilashl2, gangulo2
   /|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\ */
game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame->rows = rows;
    mygame->cols = cols;
    mygame->score = 0;
    // place a -1 for every cell
    for (int i = 0; i < rows; i++) {
	for (int j = 0; j < cols; j++) {
	    mygame->cells[i*cols+j] = -1;
	}
    }

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
	(*_cur_game_ptr)->rows = new_rows;
        (*_cur_game_ptr)->cols = new_cols;
        (*_cur_game_ptr)->score = 0;
        for (int i = 0; i < new_rows; i++) {
	    for (int j = 0; j < new_cols; j++) {
	    (*_cur_game_ptr)->cells[i*new_cols+j] = -1;
	    }
        }

	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    //Bounds check
    if (row >= 0 && col >= 0 && row < cur_game->rows && col < cur_game->cols) {
    return cur_game->cells + row*(cur_game->cols) + col;
    }
    return NULL;
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
    int slide = 0;
    int flag = 0;
    //Checker array
    int *combine = malloc(cur_game->rows*sizeof(int));
    
    for (int j = 0; j < cur_game->cols; j ++) {
	//Fill out checker array with 0s
	for (int c = 0; c < cur_game->rows; c++) {
	    combine[c] = 0;
	}
	//Look for a cell with value
	for (int i = 1; i < cur_game->rows; i++) {
    	    if (cur_game->cells[i*(cur_game->cols) +j] == -1) {
		continue;
	    }
	    int new = i;
	    //Look for empty spot to move cell to
	    for (int n = 0; n < i; n++) {
		//Slide
		if (cur_game->cells[n*(cur_game->cols) +j] == -1) {
		   slide = 1;
		   cur_game->cells[n*(cur_game->cols) +j] = cur_game->cells[i*(cur_game->cols) +j];
		   cur_game->cells[i*(cur_game->cols) +j] = -1;
		   new = n;
		   break;
	        }
	    }
	    //Merge
	    if (new > 0 && combine[new-1] == 0) {
	       if (cur_game->cells[new*(cur_game->cols) +j] == cur_game->cells[(new-1)*(cur_game->cols) +j]) {
	       	  cur_game->cells[(new-1)*(cur_game->cols) +j] = 2*(cur_game->cells[(new-1)*(cur_game->cols) +j]);
		  cur_game->score += cur_game->cells[(new-1)*(cur_game->cols) +j];
		  cur_game->cells[(new*(cur_game->cols) +j)] = -1;
	          combine[new-1] = 1;
		  flag = 1;
	       }
	    }
	}
    }
    if (slide == 0 && flag == 0) {
       return 0;
    }
    return 1;
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
    int slide = 0;
    int flag = 0;
    int *combine = malloc(cur_game->rows*sizeof(int));
    
    for (int j = 0; j < cur_game->cols; j ++) {
	for (int c = 0; c < cur_game->rows; c++) {
	    combine[c] = 0;
	}
	for (int i = cur_game->rows-2; i >= 0; i--) {
    	    if (cur_game->cells[i*(cur_game->cols) +j] == -1) {
		continue;
	    }
	    int new = i;
	    for (int n = cur_game->rows-1; n > i; n--) {
		if (cur_game->cells[n*(cur_game->cols) +j] == -1) {
		   slide = 1;
		   cur_game->cells[n*(cur_game->cols) +j] = cur_game->cells[i*(cur_game->cols) +j];
		   cur_game->cells[i*(cur_game->cols) +j] = -1;
		   new = n;
		   break;
	        }
	    }
	    if (new < cur_game->rows-1 && combine[new+1] == 0) {
	       if (cur_game->cells[new*(cur_game->cols) +j] == cur_game->cells[(new+1)*(cur_game->cols) +j]) {
	       	  cur_game->cells[(new+1)*(cur_game->cols) +j] = 2*(cur_game->cells[(new+1)*(cur_game->cols) +j]);
		  cur_game->score += cur_game->cells[(new+1)*(cur_game->cols) +j];
		  cur_game->cells[(new*(cur_game->cols) +j)] = -1;
	          combine[new+1] = 1;
		  flag = 1;
	       }
	    }
	}
    }
    if (slide == 0 && flag == 0) {
       return 0;
    }
    return 1;
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    int slide = 0;
    int flag = 0;
    int *combine = malloc(cur_game->cols*sizeof(int));
    
    for (int i = 0; i < cur_game->rows; i ++) {
	for (int c = 0; c < cur_game->cols; c++) {
	    combine[c] = 0;
	}
	for (int j = 1; j < cur_game->cols; j++) {
    	    if (cur_game->cells[i*(cur_game->cols) +j] == -1) {
		continue;
	    }
	    int new = j;
	    for (int n = 0; n < j; n++) {
		if (cur_game->cells[i*(cur_game->cols) +n] == -1) {
		   slide = 1;
		   cur_game->cells[i*(cur_game->cols) +n] = cur_game->cells[i*(cur_game->cols) +j];
		   cur_game->cells[i*(cur_game->cols) +j] = -1;
		   new = n;
		   break;
	        }
	    }
	    if (new > 0 && combine[new-1] == 0) {
	       if (cur_game->cells[i*(cur_game->cols) +new] == cur_game->cells[i*(cur_game->cols) +(new-1)]) {
	       	  cur_game->cells[i*(cur_game->cols) +(new-1)] = 2*(cur_game->cells[i*(cur_game->cols) +(new-1)]);
		  cur_game->score += cur_game->cells[i*(cur_game->cols) +(new-1)];
		  cur_game->cells[i*(cur_game->cols) +(new)] = -1;
	          combine[new-1] = 1;
		  flag = 1;
	       }
	    }
	}
    }
    if (slide == 0 && flag == 0) {
       return 0;
    }
    return 1;
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
    int slide = 0;
    int flag = 0;
    int *combine = malloc(cur_game->cols*sizeof(int));
    
    for (int i = 0; i < cur_game->rows; i ++) {
	for (int c = 0; c < cur_game->cols; c++) {
	    combine[c] = 0;
	}
	for (int j = cur_game->cols-2; j >= 0; j--) {
    	    if (cur_game->cells[i*(cur_game->cols) +j] == -1) {
		continue;
	    }
	    int new = j;
	    for (int n = cur_game->cols-1; n > j; n--) {
		if (cur_game->cells[i*(cur_game->cols) +n] == -1) {
		   slide = 1;
		   cur_game->cells[i*(cur_game->cols) +n] = cur_game->cells[i*(cur_game->cols) +j];
		   cur_game->cells[i*(cur_game->cols) +j] = -1;
		   new = n;
		   break;
	        }
	    }
	    if (new < cur_game->cols-1 && combine[new+1] == 0) {
	       if (cur_game->cells[i*(cur_game->cols) +new] == cur_game->cells[i*(cur_game->cols) +(new+1)]) {
	       	  cur_game->cells[i*(cur_game->cols) +(new+1)] = 2*(cur_game->cells[i*(cur_game->cols) +(new+1)]);
		  cur_game->score += cur_game->cells[i*(cur_game->cols) +(new+1)];
		  cur_game->cells[i*(cur_game->cols) +(new)] = -1;
	          combine[new+1] = 1;
		  flag = 1;
	       }
	    }
	}
    }
    if (slide == 0 && flag == 0) {
       return 0;
    }
    return 1;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
    for (int i = 0; i < cur_game->rows; i++) {
 	for (int j = 0; j < cur_game->cols; j++) {
	    //Check bottom and right. Careful about out of bounds on the borders 
	    int right = -3;
	    int bot = -3;
 	    int cell = cur_game->cells[i*cur_game->cols + j];
	    if (j < cur_game->cols - 1) {
		right = cur_game->cells[(i)*cur_game->cols + (j+1)];
	    }
	    if (i < cur_game->rows - 1) {
	        bot = cur_game->cells[(i+1)*cur_game->cols + (j)];
	    }
	    if (right == -1 || right == cell || bot == -1 || bot == cell || cell == -1) {
	       return 1;
	    }
	}
    }
    return 0;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
