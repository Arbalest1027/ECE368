#define true 1
#define false 0 
#define INF 100000

/*This struct represent a single vertex of a map.*/
typedef struct node
{
  int x; 
  int y; 
  int distance; 
  int index; 
  int parent; 
  int visited;
}Vertex;

/*
This struct represents a single node in an adjacency list
*/
typedef struct Adj_Node
{
  struct Adj_Node* next;
  int weight;
  int index;
}Adj_Node;

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
	//short_path(v,v[curr].distance,weight,index,curr);
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
