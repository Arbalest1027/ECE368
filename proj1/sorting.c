#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "sorting.h"
#include <math.h>


/******************************
*[Your name]
*[Filename.c]: [Date of creation].
*[your_email@purdue.edu]
*Compiling: [gcc -Werror -lm -Wall -O3 sorting.c sorting_main.c -o proj1]
*******************************/


/*
	loads the file into Arr and returns Arr, size of array is stored in *Size
	when there is a file error, or memory allocation error, return NULL, and	
	set *Size to 0
*/
long *Load_From_File(char *Filename, int *Size)
{
    long *Arr = NULL;
    *Size = 0;
    FILE * data = fopen(Filename,"r");
    if (data == NULL){
      return NULL;
    }
    fscanf(data,"%d",Size);
    Arr = malloc(sizeof(long) * (*Size));
    fseek(data,0,SEEK_SET);
    int i;
    fscanf(data,"%ld",&Arr[0]);
    for(i = 0;i < (*Size) + 1;i++){
      fscanf(data,"%ld",&Arr[i]);
    }
    fclose(data);
    return Arr;
}

/*
	Save the Array to the file Filename
	Return the number of elBements saved to file
*/
int Save_To_File(char *Filename, long *Array, int Size)
{
    int n_written = 0;
    int i;
    FILE * output = fopen(Filename,"w");
    for (i = 0;i < Size;i++){
      fprintf(output,"%ld \n",Array[i]);
      n_written++;
    }
    fclose(output);
    return n_written;
}


/*
	Print the sequence in the order in which it appears in the triangle
 	2^(p)3^(q) is the largest number, 
	If Size is 0 or 1, an empty file should be created
*/
int Print_Seq(char *Filename, int length)
{
    int seq_size = 0;
    int i,j;
    long tri = 1,limit = 1;
    FILE * out = fopen(Filename,"w");
    for (i = 0; limit <= length;i++){
      tri = limit;
      for (j = 0; j <= i && tri <= length;j++){
	fprintf(out,"%ld\n",tri);
	seq_size++;
	tri = tri / 2;
	tri = 3 * tri;
      }
      //      fprintf(out,"\n");
      limit = limit * 2;
    }
    fclose(out);
    return seq_size;
}

int help_seq(int length){
    int seq_size = 0;
    int i,j;
    long tri = 1,limit = 1;
    for (i = 0; limit <= length;i++){
      tri = limit;
      for (j = 0; j <= i && tri <= length;j++){
	seq_size++;
	tri = tri / 2;
	tri = 3 * tri;
      }
      limit = limit * 2;
    }
    return seq_size;
}

void Shell_Insertion_Sort(long *a, int length, double *ncomp, double *nswap)
{
  int i,j,k;
  long temp;
  //
  int x,y,c;
    long tri = 1,limit = 1;
    int num_seq = help_seq(length);
    int idx = 0;
    int * seq = malloc(sizeof(int) * num_seq);
    for (x = 0; limit <= length;x++){
      tri = limit;
      for (y = 0; y <= x && tri <= length;y++){
	seq[idx] = tri;
	tri = tri / 2;
	tri = 3 * tri;
	idx++;
      }
      limit = limit * 2;
    }
    //
    //    printf("%d\n",seq[num_seq]);
    for (c = num_seq - 1;c >= 0;c--){
      k = seq[c];
      for (i = k; i < length;i++){
	temp = a[i];
	j = i;
	(*ncomp)++;
	while (j >= k && a[j - k] > temp){
	  a[j] = a[j - k];
	  j = j - k;
	  (*nswap)++;
	  (*ncomp)++;
	}
	a[j] = temp;
      }
      }
        (*nswap) = 3 * (*nswap);
	free(seq);
}


void Shell_Selection_Sort(long *a, int length, double *ncomp, double *nswap)
{
  int i,j,index;
  long temp;
  int x,y,c,k;
    long tri = 1,limit = 1;
    int num_seq = help_seq(length);
    int idx = 0;
    int * seq = malloc(sizeof(int) * num_seq);
    for (x = 0; limit <= length;x++){
      tri = limit;
      for (y = 0; y <= x && tri <= length;y++){
	seq[idx] = tri;
	tri = tri / 2;
	tri = 3 * tri;
	idx++;
      }
      limit = limit * 2;
    }
    //
    for (c = num_seq / 2;c >= 0;c--){
      k = seq[c] - 1;
      for (i = k;i < length - k;i++){
	index = i;
	for (j = i + 1;j < length;j++){
	  (*ncomp)++;
	  if (a[j] < a[index]){
	    index = j;
	  }
	}
	if (index != i){
	  temp = a[index];
	  a[index] = a[i];
	  a[i] = temp;
	  (*nswap)++;
	}
      }
    }
    (*nswap) = 3 * (*nswap);
    free(seq);
}

