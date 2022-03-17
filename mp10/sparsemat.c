#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

/* \|||||||||||||||||||||||||INTRO|||||||||||||||||||||||/
    This program takes a sparse matrix given in a file and
    stores it in memory in the form of a sortedlinked list.
   It scanned the file and stored the row and column size,
   in the tuples struct. It also stored the row, col, 
   and value in the tuples_node struct. It did this by
   seeing if it was a zero, which had it delete the node. 
   If it wasn't zero, it found the same row and col and
   adjusted the value of the node. If the node didn't exist
   with the same value, it inserted a new node with that info.
   Edge cases include inserting at beginning, inserting at the 
   end, and the start of the linked list.
   It did this by using gv_tuple, which extracts the value.
   add_tuples took two matrices and added their values and 
   stored it in a new matrix.
   save_tuples opened up a given file and writes the matrix in 
   that file. It does this by writing row size and col size
   and then walking through the linked list
   and writing the row, col, and value.
   destroy_tuples walks through the linked list and frees
   each node.

   Partners: gangulo2, ilashl2
   /|||||||||||||||||||||||||||||||||||||||||||||||||||\ */



sp_tuples * load_tuples(char* input_file)
{
FILE* file = fopen(input_file, "r");

// Allocate
sp_tuples* tuples = (sp_tuples*) malloc(sizeof(sp_tuples));
// Set sp_tuples row and col
tuples->tuples_head = NULL;

int rows, cols;
fscanf(file, "%d %d", &rows, &cols);
tuples->m = rows;
tuples->n = cols;

while (!feof(file)) {
   int r, c;
   double val;
   fscanf(file, "%d %d %lf", &r, &c, &val);
   set_tuples(tuples, r, c, val);
}


    fclose(file);
    return tuples;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
    sp_tuples_node * current = mat_t->tuples_head;
  
    while(current != NULL)
    {
        if(current ->row == row && current->col == col)
        {
            return current ->value;
        }
        else
        {
            current = current ->next;
        }

    }
    return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    int colSize = mat_t->n;
	int location = row*colSize + col;
	sp_tuples_node * current = mat_t->tuples_head;
	sp_tuples_node * insert = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
	
	if(value == 0) 
	{
		if(current != NULL)
		{
			while(current->next != NULL) 
			{
				sp_tuples_node * x = current->next;
				if(x->row == row && x->col == col) 
				{
					current->next = x->next; 
					free(x);
					break;
				}
				current = current->next;
			}
		}
		return; 
	}
	else if(current == NULL) 
	{
		insert->row = row;
		insert->col = col;
		insert->value = value;
		mat_t->tuples_head = insert;
		insert->next = NULL;		
	}
	else if(location <  (current->row)*colSize + current->col) 
	{
		insert->row = row;
		insert->col = col;
		insert->value = value;
		insert->next = current; 
		mat_t->tuples_head = insert;
	}
	else
	{
		while(current->next != NULL)
		{
			if(current->row == row && current->col == col)
			{
				current->value = value; //replace old value if co-ordinates already exist
				return;
			}
			else if(location < (current->next->row)*colSize + current->next->col) //insert new node
			{				
				sp_tuples_node * temp = current->next;
				insert->row = row;
				insert->col = col;
				insert->value = value;
				current->next = insert;
				insert->next = temp;
				return;	
			}
			current = current->next;	
		}
		insert->row = row; //insert at end of linked list
		insert->col = col;
		insert->value = value;
		current->next = insert;
		insert->next = NULL;
					
	}
}




void save_tuples(char * file_name, sp_tuples * mat_t)
{
    int colsize = mat_t->n;
    int rowsize = mat_t->m;
    sp_tuples_node* current = mat_t->tuples_head;
FILE *file1 = fopen(file_name, "w");
    colsize = mat_t->n;
    rowsize = mat_t->m;
    fprintf(file1, "%d %d\n", rowsize, colsize);
int rows, cols;
double val;

 while(current != NULL)
    {
    rows = current-> row;
    cols = current-> col;
    val = current-> value;
    fprintf(file1, "%d %d %lf\n", rows, cols, val);
    current = current->next;
    }
fclose(file1);
	return;
}

void non_zero(sp_tuples * mat_t)
{
	sp_tuples_node * current = mat_t->tuples_head;
	mat_t->nz = 0;
	
	while(current != NULL) //count non-zero elements
	{
		mat_t->nz++;
		current = current->next;
	}
}

sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    sp_tuples *matC = (sp_tuples *)malloc(sizeof(sp_tuples));
    matC->tuples_head = NULL;
    matC->m = matA->m;
    matC->n = matA->n;
    int r, c;
    if((matA->m == matB->m) && (matA->n == matB->n)){
        sp_tuples_node *startB = matB->tuples_head;
        sp_tuples_node *startA = matA->tuples_head;
        double A = 0;
        double B = 0;
        while(startA != NULL){
                r = startA->row;
                c = startA->col;
                A = gv_tuples(matC, r, c) + startA->value; 
                set_tuples(matC, r, c, A); 
                startA = startA ->next;
            
        }

        while (startB != NULL)
        {
                r = startB->row;
                c = startB->col;
                B = gv_tuples(matC, r, c) + startB->value;
                set_tuples(matC, r, c, B);
                startB = startB->next;
        }
        non_zero(matC);
        return matC; 
    }
     else
    return NULL;
}


/*
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    return retmat;

}
*/

	
void destroy_tuples(sp_tuples * mat_t){
if(mat_t != NULL){	
sp_tuples_node *delete = mat_t->tuples_head;
sp_tuples_node *temp;

    while(delete != NULL){
        temp = delete;
        delete = delete->next;
        free(temp);
     }
    free(mat_t);
}  
}