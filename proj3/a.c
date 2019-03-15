#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define INF 10000000

typedef struct Graph{
  int* ver;
  long int** edg;
}Graph;

typedef struct point{
  int x;
  int y;
}point;

void CreateGraph(Graph* g,char* filename){
  FILE* fp = fopen(filename,"r");
  int npoint = 0;
  int edge = 0;
  fscanf(fp," %d %d",&npoint,&edge);//num of points and edges
  printf("%d %d\n",npoint,edge);
  int i,j;
  //allocating each point
  point* cpoint;
  cpoint = malloc(sizeof(point) * npoint);
  
  //allocating and initializing edge matrix
  g -> ver = malloc(sizeof(int) * npoint);
  for (i = 0;i < npoint;i++){
    g -> ver[i] = i;
  }
  
  /*for (i = 0;i < npoint;i++){
    for (j = 0;j < npoint;j++){
      if (i == j){
	g -> edg[i][j] = 0;}
      else{
	g -> edg[i][j] = INF;}
    }
  }
  //get each point
  int tempx,tempy,tempidx;
  for (i = 0;i < npoint;i++){
    fscanf(fp," %d %d %d",&tempidx,&tempx,&tempy);
    cpoint[i].x = tempx;
    cpoint[i].y = tempy;
  }
  //get each edge
  int tempa,tempb;
  for (i = 0;i < edge;i++){
    fscanf(fp," %d %d",&tempa,&tempb);
    g -> edg[tempa][tempb] = ((cpoint[tempa].x)-(cpoint[tempb].x))*((cpoint[tempa].x)-(cpoint[tempb].x))+((cpoint[tempa].y)-(cpoint[tempb].y))*((cpoint[tempa].y)-(cpoint[tempb].y));
    g -> edg[tempa][tempb] = sqrt((double)g -> edg[tempa][tempb]);
    }*/
    fclose(fp);
}

int main(int argc,char** argv){
  Graph g;
  int i;
  g.edg = malloc(8*100000);
  for (i = 0;i < 100000;i++){
    g.edg[i] = malloc(8);
  }
  g.edg[6][4] = 25;
  CreateGraph(&g, argv[1]);
  return EXIT_SUCCESS;
}
