#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void left_rotate(int * , int , int );
int main(int argc, char ** argv){
	int * A = malloc(sizeof(int) * 5);
	for (int i = 0;i < 5;i++){
	    A[i] = i + 1;
	}
	int d = 3;
	int n = 5;
	left_rotate(A,n,d);
	for (int j = 0;j < n;j++){
	  printf("%d",A[j]);
	}
	free(A);
	return EXIT_SUCCESS;
}

void left_rotate(int * A, int n, int d){
	for (int i = 0;i < d;i++){
		int temp = A[0];
		int j;
		for (j = 0;j < n - 1;j++){
			A[j] = A[j + 1];
		}
	       	A[j] = temp;		
	}
}
