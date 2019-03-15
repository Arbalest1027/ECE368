#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define true 1
#define false 0 
#define INF 100000

/*
This struct represent a single vertex of a map.
*/
typedef struct node
{
  int x; 
  int y; 
  int distance; 
  int index; 
  int parent; 
  int visited;
}Vertex;

/*This struct represents a single node in an adjacency list*/
typedef struct Adj_Node
{
  struct Adj_Node* next;
  int weight;
  int index;
}Adj_Node;

/*This struct helps us build a set of adjacency lists, i.e., an adjacency list for all the nodes of the map*/
typedef struct Adj_List
{
  struct Adj_Node *head;  // pointer to head node of list
}Adj_List;


/*Global function declarations*/
int Dijkstra(Vertex v[], Adj_List *adj_list, int src, int dest, int nvert);
int extract_min(Vertex v[], int n);
void print_path(Vertex v[], int src, int dest);
void reinit(Vertex v[], int nvert);
void path_helper(Vertex v[], Adj_List *adj_list, int curr);
Adj_Node* create_adj_node(int index, int weight);
void Destroy_adj_list(Adj_List* adj_list, int n);
void Destroy_list(Adj_Node *adj_node);



/*Frees the memory allocated for the adjacency list*/
void Destroy_adj_list(Adj_List* adj_list, int n)
{
  int i = 0;
  // Adj_List *ptr = adj_list;
  Adj_Node * temp;
  for (i = 0;i < n;i++){
    while (adj_list[i].head != NULL){
      temp =  adj_list[i].head;
      adj_list[i].head = adj_list[i].head -> next;
      free(temp);}
  }
  free(adj_list);
}

/*Creates adjacent nodes */
Adj_Node* create_adj_node(int index, int weight)
  {
    Adj_Node* node = malloc(sizeof(Adj_Node));
    node->next  = NULL;
    node->index = index;
    node->weight = weight;
    return node;
  }


/*Re-initialize vertices array*/
void reinit(Vertex vertices[], int nvert){
  int i = 0;
  for(i = 0; i < nvert; i++){
      vertices[i].distance = INF;
      vertices[i].parent = -1;
      vertices[i].index = i;
      vertices[i].visited = false;
    }
}

void path_helper(Vertex v[], Adj_List *adj_list, int curr){
  int index = 0;
  int weight = 0;
  Adj_Node *list_ptr = adj_list[curr].head;

  while(list_ptr != NULL){
      index = list_ptr->index;
      weight = list_ptr->weight;

      if(v[index].visited == false ){
	if(v[index].distance > v[curr].distance + weight){
	  v[index].distance = v[curr].distance + weight;}
	v[index].parent = curr;
      }
      list_ptr = list_ptr->next;
    }
}


/*min heap*/
int extract_min(Vertex v[], int n)
{
  int min = INF;
  int min_index = 0;
  int i = 0;

  for(i=0;i<n;i++){
      if (v[i].visited == false && v[i].distance < min){
	  min = v[i].distance;
	  min_index = v[i].index;
	}
    }
  return min_index;
}


/*Dijkstra's algorithm*/
int Dijkstra(Vertex v[], Adj_List *adj_list, int src, int dest, int nvert)
{
  int curr = src; //most recent node extracted
  int n = nvert;

  v[src].distance = 0;
  v[curr].visited = true;

  while(curr != dest){
      path_helper(v,adj_list,curr);
      curr = extract_min(v,nvert);
      v[curr].visited = true;
      n--;
   }
  if(n==0){
      return 0;
    }
  return 1;
}



void print_path(Vertex v[], int src, int dest)
{
  int i = dest; //ctr
  int j = 0; //ctr
  int path[10000] = {0}; 

  printf("%d\n",v[dest].distance);

  path[j] = dest;
  j++;

  while(i != src){
      path[j] = v[i].parent;
      i = v[i].parent;
      j++;
    }
  while(j >= 1){
      printf("%d ",path[j - 1]);
      j--;
    }
  printf("\n");
}

int main(int argc, char** argv){
  int nvert = 0; //no. of vertices
  int nedge = 0; //no. of edges
  //int nquery = 0; //no. of queries
  //int src = 0; //source vertex in map query
  //int dest = 0; //destination vertex in map query
  int c = 0; //counter
  int i, j = 0; //arbitrary variables used in fscanf
  int adj_weight = 0; //stores weights of adjacent nodes during the creation of adj_list
  // int Dijkstra_res = 0; //result of Dijkstra's algorithm
  FILE* fptr;
  clock_t t;
  t = clock();
  
  fptr = fopen(argv[1],"r");
  fscanf(fptr," %d %d",&nvert,&nedge);

  Vertex * vertices = malloc(sizeof(Vertex) * nvert);
  Adj_List *adj_list = malloc(nvert * sizeof(Adj_List));
  for (i=0; i<nvert; i++){
      adj_list[i].head = NULL;
    }
/*Initializing the vertex array's attributes*/
  for(c = 0; c < nvert; c++){
      fscanf(fptr," %d %d %d",&i,&vertices[c].x,&vertices[c].y);
      vertices[c].distance = INF;
      vertices[c].parent = -1;
      vertices[c].index = c;
      vertices[c].visited = false;
    }

/*Initializing the adjacency list and adding edges*/
  for (c = 0;c < nedge;c++){
      fscanf(fptr," %d %d",&i,&j);
      adj_weight = sqrt((pow((vertices[j].x - vertices[i].x),2) + pow((vertices[j].y - vertices[i].y),2)));
      Adj_Node* newNode = create_adj_node(i,adj_weight);
      newNode->next = adj_list[j].head;
      adj_list[j].head = newNode;
 
      // Since graph is undirected, add an edge from dest to src also
      newNode = create_adj_node(j,adj_weight);
      newNode->next = adj_list[i].head;
      adj_list[i].head = newNode;
    }
  //
  fclose(fptr);
  t = clock() - t;
  double time = ((double)t)/CLOCKS_PER_SEC;
  printf("Time takes to load:%f\n",time);
  /*fptr = fopen(argv[2],"r");
  fscanf(fptr,"%d",&nquery);
  for (c = 0;c < nquery;c++){
      fscanf(fptr," %d %d",&src,&dest);
      Dijkstra_res = Dijkstra(vertices,adj_list,src,dest,nvert);
      if(Dijkstra_res == 1){
	  print_path(vertices,src,dest); //This if statement checks if a path between the given 2 vertices was found
	}
      else {
	printf("INF\n");
	printf("%d %d \n",src,dest);
      }
      reinit(vertices,nvert);
    }

    fclose(fptr);
  t = clock() - t;
  time = ((double)t)/CLOCKS_PER_SEC;
  printf("Time takes to find path:%f\n",time);*/
  int i;
  Adj_Node* temp;
  for (i = 0;i < nvert;i++){
    printf("%d: ",i);
    temp = adj_list[i].head;
    while (temp != NULL){
      printf("%d ",temp -> index);
      temp = temp -> next;
    }
    prinf("\n");
  }
  Destroy_adj_list(adj_list,nvert);
  free(vertices);
  return 0;
}
