#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define INF 10000000

typedef struct Graph{
  int* ver;
  int** edg;
  int nvex;
  int nedg;
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
  //printf("%d %d\n",npoint,edge);
  int i,j;
  //allocating each point
  point* cpoint;
  cpoint = malloc(sizeof(point) * npoint);
  
  //allocating and initializing edge matrix
  g -> ver = malloc(sizeof(int) * npoint);
  for (i = 0;i < npoint;i++){
    g -> ver[i] = i;
  }

  g -> edg = malloc(8*npoint);
  for (i = 0;i < npoint;i++){
    g -> edg[i] = malloc(4*npoint);
  }
  g -> edg[6][4] = 25;
  for (i = 0;i < npoint;i++){
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
   }
  g -> nvex = npoint;
  g -> nedg = edge;
  //printf("%d %d\n",tempa,tempb);
  //printf("%d %d %d\n",g -> edg[727][728],g -> edg[87500][87500],g -> edg[15964][4156]);
  free(cpoint);
  fclose(fp);
}

int main(int argc,char** argv){
  Graph g;
  int i;
  CreateGraph(&g, argv[1]);
  free(g.ver);
  for(i = 0;i < g.nvex;i++){
    free(g.edg[i]);}
  free(g.edg);
  return EXIT_SUCCESS;
}

