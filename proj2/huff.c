#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
           
#define MAXSIZE 100000000
            
typedef char* HCode;
           
typedef struct node
{
    int weight;
    int data;
    int parent,lchild,rchild;
}Node;
           
int sum_bit,count;//number of leaves and length of code
            
Node huffmanNode[260];
            
int num[8];
            
int code[260];
           
HCode *HC;//array of characters

//determine whether been recorded
int isInNode(int value)
{
    int i = 1;
    for(;i<=count;i++)
    {
        if(huffmanNode[i].data == value)
        {
            return i;
        }
    }
    return 0;
}
            
void calWeight(char *file){
    count = 0;
    FILE *f;
    int a;
    f = fopen(file,"rb");
    if(f == NULL){
        printf("Fail to open");
        return;
    }
    //find weight for each charactor
    while(!feof(f)){
        a = fgetc(f);
        if(a == EOF) break;
        if(!isInNode(a)){
            count++;
            huffmanNode[count].weight = 1;
            huffmanNode[count].data   = a;
        }
        else
        {
            int i = isInNode(a);
            huffmanNode[i].weight++;
        }
    }
    fclose(f);
}
//get count of bytes before compression
int getSumBytes(){
    int i=1;
    int result = 0;
    for(;i<=count;i++)
    {
        result +=huffmanNode[i].weight;
    }
    return result;
}
//after compression
int getSumBits()
{
    int i = 1;
    int result = 0;
    for(;i<=count;i++)
    {
        result+=huffmanNode[i].weight * strlen(HC[i]);
    }
    return result;
}
 
void createHufmanTree(Node * huffmanTree)
{
    int m = 2*count - 1;
    int m1,m2,x1,x2,i,j;
    //initialize all nodes
    for(i=1;i<=count;i++){
        huffmanTree[i].data = huffmanNode[i].data;
        huffmanTree[i].lchild = -1;
        huffmanTree[i].rchild = -1;
        huffmanTree[i].parent = -1;
        huffmanTree[i].weight = huffmanNode[i].weight;
    }
    for(;i<=m;i++){
        huffmanTree[i].data = 0;
	huffmanTree[i].weight = 0;
        huffmanTree[i].lchild = -1;
	huffmanTree[i].rchild = -1;
        huffmanTree[i].parent = -1;
    }
    for(i=count+1;i<=m;i++){
        m1 = m2 = MAXSIZE;
        x1 = x2 = 0;
        for(j=1;j<i;j++){
            if(huffmanTree[j].parent == -1 && huffmanTree[j].weight <m1){
                m2 = m1;
		x2 = x1;
                m1 = huffmanTree[j].weight;
		x1 = j;
            }
            else if(huffmanTree[j].parent == -1&&huffmanTree[j].weight<m2){
                m2 = huffmanTree[j].weight;
                x2 = j;
            }
 
        }
	//combining branches into a tree
            huffmanTree[x1].parent = i;
	    huffmanTree[x2].parent = i;
            huffmanTree[i].lchild = x1;
	    huffmanTree[i].rchild = x2;
            huffmanTree[i].weight = m1+m2;
    }
}

//get the code from each leave path and store them into my array
HCode * getHuffmanCode(Node * huffmanTree,HCode *HC,int code[])
{
    int i = 1,c,start,f;
    char * cd = (char *)malloc((count+1)*sizeof(char));
    cd[count] = '\0';
    for(;i<=count;i++)
    {
        start = count;
        for(c=i,f=huffmanTree[i].parent;f!=-1;c=f,f=huffmanTree[f].parent)
        {
            if(huffmanTree[f].lchild == c)
	      cd[--start] = '0';
            else
	      cd[--start] = '1';
        }
        HC[i] = (char *)malloc((count+1-start)*sizeof(char));
        strcpy(HC[i],&cd[start]);
        code[i] = huffmanTree[i].data;
    }
    free(cd);
    return HC;
}

//printing my tree to the binary file
void freToFile(int code[],HCode *HC,char* filename)
{
    int i;
    FILE *fe = fopen(filename,"wb");
    for(i=1;i<=count;i++)
    {
      fprintf(fe,"%s %d\n",HC[i],code[i]);
    }
    char c = '#';

    fprintf(fe,"%c",c);
    fprintf(fe,"%d",getSumBits());
    fprintf(fe,"%c",c);

    fprintf(fe,"%c",c);
    fprintf(fe,"%d",count);
    fprintf(fe,"%c",c);
    fprintf(fe,"%c",'~');//indicator of the end of my tree
    fclose(fe);
}

void compress_file(char* file1,char*file2)
{
    int i,sum = 0,flag = 0,j,k = 0;
    int eight[1000];//eight bit buffer
    memset(eight,-1,1000*sizeof(int));//initialize all to -1
    FILE *fo = fopen(file1,"rb");
    FILE *fw = fopen(file2,"ab");
    int aa;//counting compressed bits
    if(fo == NULL||fw == NULL)
    {
        printf("Fail to read");
        return;
    }
    int sum_bytes = getSumBytes();
    while(!feof(fo))
    {
      //read each charactor
        sum = 0;
        int a = fgetc(fo);
        for(i=0;i<=count;i++)
        {
            if(code[i] == a)
            {
	      //if more than 8 in buffer, get code and output
	      //else continue buffering
                flag+=strlen(HC[i]);
                int len = strlen(HC[i]);
                if(flag<8)
                {
                    for(j=0;j<len;j++)
                    eight[k++] = HC[i][j]-'0';
                }
                else if(flag>=8)
                {
                    for(j=0;k<8;j++)
                      eight[k++] = HC[i][j]-'0';
                    for(;j<len;j++)
                      eight[k++] = HC[i][j]-'0';
		    //convert number in bffer into int than into binary into the file
                    sum = eight[0]*128+eight[1]*64+eight[2]*32+eight[3]*16+eight[4]*8
		      +eight[5]*4+eight[6]*2+eight[7]*1;
		    int temp = 0;
		    //empty and shift the buffer
		    for(;j<8;j++){
		      eight[j] = -1;}
                    while (eight[temp+8] != -1){
                       eight[temp] = eight[temp+8];
		       temp++;
		    }
		    k = k - 8;
		    flag = flag - 8;//update buffer flag
                    char c = sum;
                    fputc(c,fw);
                    fflush(fw);
                    //i = count + 1;
                }
            }
        }
    }
    aa = sum_bytes;
    //after writing, rest bits not equal to 8
    if(flag)
    {
        sum+=eight[0]*128+eight[1]*64+eight[2]*32+eight[3]*16+eight[4]*8
                        +eight[5]*4+eight[6]*2+eight[7]*1;
        char c = sum;
        fputc(c,fw);
        sum_bit +=flag;
        fflush(fw);
    }
    fclose(fw);
    fclose(fo);
}
 

 
int main(int argc, char **argv){
                //获取文件的词频
        calWeight(argv[1]);
	//initialize trees and build it
  clock_t t;
  t = clock();
        Node *huffmanTree = (Node *)malloc((2*count)*sizeof(Node));
        createHufmanTree(huffmanTree);
        HC = (HCode *)malloc((count+1)*sizeof(HCode));;
	char *append = malloc(strlen(argv[1])+6);
	sprintf(append,"%s.huff",argv[1]);
        HC = getHuffmanCode(huffmanTree,HC,code);
        freToFile(code,HC,append);
        compress_file(argv[1],append);
  t = clock() - t;
  double time = ((double)t)/CLOCKS_PER_SEC;
  printf("Time takes to compress:%f",time);
        free(append);
	int i;
	for (i = 1;i <= count;i ++){
	  free(HC[i]);
	}
	free(HC);
	free(huffmanTree);
	return EXIT_SUCCESS;
}
