#include <stdio.h>
#include <stdlib.h>
/*The function main prints out a row of Pascal's Pyramid.
  After asking for user input for which row, implement
  a loop use the given formula (result*numerator)/den
  that computates each number in the row and print.
	
  Partners: gangulo2, ilashl2
*/  
int main()
{
  int row;

  printf("Enter a row index: ");
  scanf("%d",&row);

  // Write your code here
  // Initialize
  unsigned long result = 1;
  unsigned long num = row;
  unsigned long den = 1;
  //Print out 1 off the bat
  printf("1 ");
  /*print out the row starting from
  second number. Use the given formula.
  */
  for (int i = 0; i < row ; i++) {
	result = (result * num) / den;
	num--;
	den++;
	printf("%lu ", result);
  }		
  printf("\n");
  return 0;
}
