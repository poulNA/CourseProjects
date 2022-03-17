#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
/*
 \||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||/
					INTRO
   This file implements the createMaze, destroyMaze, printMaze, and solveMazeDFS
 * functions. 
   createMaze: creates a maze struct and initializes rows, cols, etc. It fills a 2D 
   array with the maze "walls" and sets the start and end. 
   destroyMaze: frees all the memory heap block for the maze. 
   printMaze: prints the maze using the maze pointer.
   solveMazeDFS: Uses recursive depth first search algorithm to solve the maze given
   the maze pointer, current row, and current col. Base case is if no moves left or
   reaches the end. Recursive step is moving up, down, left, right.

   Partners: gangulo2, ilashl2
 /||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\
 */



/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
  int i, j, k, l, rows, cols;
  //open file r
  FILE* file = fopen(fileName, "r");
  //get cols and rows
  fscanf(file,"%d", &cols); 	
  fscanf(file,"%d", &rows);
  //Allocate
  maze_t* maze = (maze_t*) malloc(sizeof(maze_t)); 
  maze->cells = calloc(rows,sizeof(char*)); 
  
  for (i = 0; i < rows; i++){
    maze->cells[i] = calloc(cols,sizeof(char));
  }
  
  maze->width = cols;
  maze->height = rows;
  //buffer
  char buffer[rows][cols+2];
  
  for (j = 0; j < rows; j++){	 
    fgets(buffer[j],cols+2,file);
  }
	
  for (k = 0; k < rows; k++){
    for (l = 0; l < cols; l++){
      maze->cells[k][l] = buffer[k][l];
      if (buffer[k][l] == 'S'){
	maze->startRow = k;
	maze->startColumn = l;
      }
      if (buffer[i][j] == 'E'){ 
	maze->endRow = k;
	maze->endColumn = l;
      }
    }
  }
  return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{//Deallocate
  int i;
  for (i = 0; i < maze->height; i++){
    free(maze->cells[i]);
  }
  
  free(maze->cells);
  free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{ // print all 
  int i, j;
  for (i = 0; i < maze->height; i++){
    for (j = 0; j < maze->width; j++){
      printf("%c", maze->cells[i][j]);
    }
    printf("\n");
  }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{ 	
  if ( col < 0 || row < 0 || col >= maze->width || row >= maze->height) 	// Valid row and col check
    return 0;
  
  if (maze->cells[row][col] == 'E') // Base case
    return 1;	

  if (maze->cells[row][col] != 'S' && maze->cells[row][col] != ' ')
    return 0;
	
  if (maze->cells[row][col] != 'S')
    maze->cells[row][col] = '*';
  //Check up, down, left, right	
  if (solveMazeDFS(maze,col,row-1))
    return 1;

  if (solveMazeDFS(maze,col,row+1))
    return 1;

  if (solveMazeDFS(maze,col-1,row))
    return 1;

  if (solveMazeDFS(maze,col+1,row))
    return 1;

  //backtrack
  if (maze->cells[row][col] != 'S')
    maze->cells[row][col] = '~';
  //no solution
  return 0;
}
