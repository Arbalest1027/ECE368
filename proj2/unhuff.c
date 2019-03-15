#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

#define MAXSIZE 100000000
            
typedef char* HCode;
           
typedef struct node{
    int weight;
    int data;
    int parent,lchild,rchild;
}Node;
           
int sum_bit,count;
            
Node huffmanNode[260];
            
int num[8];
            
int code[260];
           
HCode *HC;

//a lossless pow fucntion
int powmy(int a,int b){
 if(b==0) return 1;
    int i = 0;
    int result = 1;
    for(;i<b;i++){
        result *=a;
    }
    return result;
}

//read the tree from binary file
HCode* freFromFile(int code[],HCode *HC,char *filename){
    int i;
    FILE *fe = fopen(filename,"rb");
    fseek(fe,0,SEEK_SET);
    if(fe==NULL)
    {
        printf("Fail to read");
        return NULL;
    }
        int k;
        int num[10];
        int m;
        int flag = 0;
        char* cd = malloc((256+1)*sizeof(char));
        char c = fgetc(fe);
        for(i=1;flag != 1;i++){
	  //when reaches #, end of reading tree
            if(c=='#') break;
	    //each space indicates a path
            int j = 0;
            while(c!=' '){
                cd[j++] = c;
                c = fgetc(fe);
            }
            cd[j] = '\0';//end of string
            //store the code to our array
            HC[i] = (char *)malloc((j+1)*sizeof(char));
            strcpy(HC[i],&cd[0]);
            //each space next indicates the corresponding character of each path code
            c = fgetc(fe);
            k = 0;
            while(c!='\n'){
                num[k++] = c-'0';
                c = fgetc(fe);
            }
            code[i] = 0;
            m = 0;
            //convert binary into int
            for(k=k-1;k>=0;k--){
                code[i]+=num[k]*powmy(10,m);
                m++;
            }
            c = fgetc(fe);
        }
        //getting bits read to determine the last byte has 8 bits
        c = fgetc(fe);
        k = 0;
        while(c!='#'){
            num[k++] = c-'0';
            c = fgetc(fe);
        }
        m = 0;
        sum_bit = 0;
        for(k=k-1;k>=0;k--){
	  sum_bit+=(num[k]*powmy(10,m));//convert
            m = m + 1;
        }
        c = fgetc(fe);  c = fgetc(fe);//read next data to achieve byte after compression
        k = 0;
        while(c!='#'){
            num[k++] = c-'0';
            c = fgetc(fe);
        }
        m = 0;  count = 0;
        for(k=k-1;k>=0;k--)
        {
	  count+=num[k]*powmy(10,m);//convert
            m++;
        }
        fclose(fe);
	free(cd);
        return HC;
}

//convert ascii into binary
int  swap(int data)
{
    int i = 0;
    while(data){
        num[i++] = data % 2;
        data = data / 2;
    }
    return i;
} 

void uncompress_file(char* file1,char* file2)
{
 
    FILE *fo = fopen(file1,"rb");
    FILE *fw = fopen(file2,"wb");
    if(fo==NULL ||fw == NULL)
    {
        printf("Fail to open");
        return;
    }
    char str[1000];
    int i,j,k,temp = 0;
    int index;
    int sum_bit2 = sum_bit;
    fseek(fo,0,SEEK_SET);
    int data = fgetc(fo);
    while (data != '~'){ data = fgetc(fo);   }//skip the tree part
    while(!feof(fo))
    {
       if(sum_bit2<0) break;
       //everytime we read, deduct 8 bits
       int data = fgetc(fo);
       sum_bit2 -=8;
       if(data == -1) break;
       //when no need to read 8 bits
       if(sum_bit2<0){
            index = 0-sum_bit2;
       }
       else{
           index = 0;
       }
       if(data == -1) break;
       memset(num,0,sizeof(num));
       //convert data into binary
       swap(data);
       i = temp;
       //store each bits into the buffer
       for(k=7;k>=index;i++,k--){
           if(num[k])
              str[i] = '1';
            else
              str[i] = '0';
 
           str[i+1] ='\0';
           //compare the buffer with the path codes
           for(j=1;j<=count;j++){
               if(strcmp(str,HC[j])==0){
                    fputc(code[j],fw);
                    fflush(fw);
                    j = count+1;
                    i = -1;
               }
           }
       }
       if(i){
            temp = i;
       }
       else{
            temp = 0;
       }
    }
    sum_bit2 = 0;
    fclose(fw);
    fclose(fo);
}

int main(int argc, char **argv){
       HC = (HCode *)malloc(257*sizeof(HCode));
  clock_t t;
  t = clock();
       HC = freFromFile(code,HC,argv[1]);
       char* append = malloc(strlen(argv[1])+8);
       sprintf(append,"%s.unhuff",argv[1]);
       uncompress_file(argv[1],append);
  t = clock() - t;
  double time = ((double)t)/CLOCKS_PER_SEC;
  printf("Time takes to decompress:%f",time);
  FILE* temp = fopen(append,"r+");
  fseek(temp,-1,SEEK_END);
  if ((int)fgetc(temp) == 39){
    fseek(temp,-1,SEEK_END);
    fputc(' ',temp);
  }
  fclose(temp);
  int i;
  for (i = 1;i <= count;i++){
    free(HC[i]);
  }
       free(HC);
       free(append);
    return 0;
}
