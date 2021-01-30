//Created by Vatsal Parikh
//Date 1/29/21
//creates a graph with adjacency table
//reference for shortest path https://www.youtube.com/watch?v=XB4MIexjvY0

//imports
#include <iostream>
#include <cstring>
#include <limits>
#include <vector>
#include <iterator>
#include <iomanip>

using namespace std;

//constants
const int size = 20;                                                                                                  
const int infinity = numeric_limits<int>::max();

//struct to create a vertex
struct vertex {
  
  char* name;

  vertex(char* newN) {
    name = newN;
  }
};

//struct that has properties for a vertex needed for shortest path
struct properties {

  vertex* v;
  int cost;
  vector<vertex*> path;
  bool flagged;

  properties() {
    v = NULL;
    cost = infinity;
    flagged = false;
  }

  properties(vertex* newV) {
    v = newV;
    cost = infinity;
    flagged = false;
  }
};

//prototypes
int findIndex(vertex** list, char* n);
void addVertex(vertex** list);
void addEdge(vertex** list, int** table);
void removeEdge(vertex** list, int** table);
void removeVertex(vertex** list, int** table);
void callShortPath(vertex** list, int** table);
void shortPath(properties** pList, int** table, vertex** list, int eIndex);

int main() {

  //create table and list of vertices to coordinate to table
  int* adjacencyTable[size];
  vertex* list[size];
  char input[50];
  bool quit = false;

  //intialize them
  for (int i = 0; i < size; i++) {
    adjacencyTable[i] = new int[size];

    for (int j = 0; j < 20; j++) {
      adjacencyTable[i][j] = -1;
    }
    
    list[i] = NULL;
  }

  //welcome prompts
  cout << "Welcome to Graph Creator!" << endl;
  cout << "Commands: add vertex, add edge, remove edge, remove vertex, short path and quit" << endl;
  
  while (quit == false) {

    //get input
    cin.get(input, 50);
    cin.get();

    //add vertex
    if (strcmp(input, "add vertex") == 0) {
      addVertex(list);
    }

    //add edge
    else if (strcmp(input, "add edge") == 0) {
      addEdge(list, adjacencyTable);
    }

    //remove edge
    else if (strcmp(input, "remove edge") == 0) {
      removeEdge(list, adjacencyTable);
    }

    //remove vertex
    else if (strcmp(input, "remove vertex") == 0) {
      removeVertex(list, adjacencyTable);
    }

    //find short path
    else if (strcmp(input, "short path") == 0) {
      callShortPath(list, adjacencyTable);
    }

    //this was here for debug only
    /*else if (strcmp(input, "print") == 0) {

      for (int i = 0; i < size; i++) {
	if (list[i] != NULL) {
	  cout << list[i]->name << " ";
	}
      }
      
      cout << endl;
      for (int i = 0; i < size; i++) {
	for (int j = 0; j < size; j++) {
	  cout << adjacencyTable[i][j] << " ";
	}

	cout << endl;
      }
      }*/

    //quit
    else if (strcmp(input, "quit") == 0) {
      quit = true;
    }

    //else
    else {
      cout << "Invalid command" << endl;
    }
  }
}

//uses Dijkstra's to find shortest path
void shortPath(properties** pList, int** table, vertex** list, int eIndex) {

  //stores the lowest cost vertex
  int lowCost = infinity;
  int sIndex = -1;

  //finds the lowest cost vertex
  for(int i = 0; i < size; i++) {

    if (pList[i]->v != NULL && pList[i]->cost < lowCost && pList[i]->flagged == false) {
      lowCost = pList[i]->cost;
      sIndex = i;
    }
  }

  //if index is still -1 there isn't and existent path
  if (sIndex == -1) {
    return;
  }

  //if it equals the end point we have our point we can exit this function
  if (sIndex == eIndex) {
    return;
  }

  //flag it so we don't loop on it
  pList[sIndex]->flagged = true;

  //relaxaton of the edges to the vertex
  for (int i = 0; i < size; i++) {

    if (table[sIndex][i] != -1 && pList[sIndex]->cost + table[sIndex][i] < pList[i]->cost) {
      pList[i]->cost = pList[sIndex]->cost + table[sIndex][i];
      pList[i]->path.clear();
      
      for (vector<vertex*>::iterator it = pList[sIndex]->path.begin(); it != pList[sIndex]->path.end(); it++) {
	pList[i]->path.push_back(*it);
      }

      pList[i]->path.push_back(list[i]);
    }
  }

  //call function again for next vertex
  shortPath(pList, table, list, eIndex);
}

//calls ShortPath
void callShortPath(vertex** list, int** table) {

  //gets the vertices for the path from user
  char* input = new char[50];
  int fIndex = 0;
  int sIndex = 0;
  
  cout << "what is the starting vertex" << endl;
  cin.get(input, 50);
  cin.get();

  fIndex = findIndex(list, input);

  if (fIndex == -1) {
    cout << "vertex not found" << endl;
    return;
  }

  cout << "what is the ending vertex" << endl;
  cin.get(input, 50);
  cin.get();

  sIndex = findIndex(list, input);

  if (sIndex == -1) {
    cout << "vertex not found" << endl;
    return;
  }

  //create array of properties
  properties* pList[size];

  //set them to the vertices
  for(int i = 0; i < size; i++) {
    pList[i] = new properties(list[i]);
  }

  //the source vertex need to be intialized for ShortPath
  pList[fIndex]->cost = 0;
  pList[fIndex]->path.push_back(list[fIndex]);
  shortPath(pList, table, list, sIndex);

  //if the cost is still infinity it is 99.999% likely there isn't a path
  //potentially cost could be value of infinity but verrry unlikely
  if (pList[sIndex]->cost == infinity) {
    cout << "there is no path from these two vertices" << endl;
  }

  //else print out the path and cost
  else {
    cout << "shortest path is: ";

    for (vector<vertex*>::iterator it = pList[sIndex]->path.begin(); it != pList[sIndex]->path.end(); it++) {
      cout << (*it)->name  << " ";
    }
  
    cout << endl;
    cout << "cost of shortest path is: " << pList[sIndex]->cost << endl;
  }
}

//removes vertex from graph
void removeVertex(vertex** list, int** table) {

  //gets the vertex user wants to remove
  char* input = new char[50];
  int index = 0;
  
  cout << "what is the vertex you would like to delete" << endl;
  cin.get(input, 50);
  cin.get();

  index = findIndex(list, input);

  if (index == -1) {
    cout << "vertex not found" << endl;
    return;
  }

  //remove edges going from or to the vertex
  for (int i = 0; i < size; i++) {
    table[index][i] = -1;
    table[i][index] = -1;
  }

  //delete the vertex from the list
  delete list[index];
  list[index] = NULL;
}

//removes edge from graph
void removeEdge(vertex** list, int** table) {

  //gets the edge user wants to remove
  char* input = new char[50];
  int fIndex = 0;
  int sIndex = 0;

  cout << "what is the first vertex of the edge" << endl;
  cin.get(input, 50);
  cin.get();

  fIndex = findIndex(list, input);

  if (fIndex == -1) {
    cout << "vertex not foud" << endl;
    return;
  }

  cout << "what is the second vertex of the edge" << endl;
  cin.get(input, 50);
  cin.get();

  sIndex = findIndex(list, input);

  if (sIndex == -1) {
    cout << "vertex not found" << endl;
    return;
  }

  //set it to -1
  table[fIndex][sIndex] = -1;
}

//gets index of vertex
int findIndex(vertex** list, char* n) {

  //loop through list
  for (int i = 0; i < size; i++) {

    //if found return i
    if (list[i] != NULL && strcmp(list[i]->name, n) == 0) {
      return i;
    }
  }

  //or return -1 for not found
  return -1;
}

//adds edge to graph
void addEdge(vertex** list, int** table) {

  //get vertices for edge from user
  char* input = new char[50];
  int data = 0;
  int fIndex = 0;
  int sIndex = 0;
  
  cout << "what is the first vertex of the edge" << endl;
  cin.get(input, 50);
  cin.get();

  fIndex = findIndex(list, input);
  
  if (fIndex == -1) {
    cout << "the vertex is inexistent" << endl;
    return;
  }
  
  cout << "what is the second vertex of the edge" << endl;
  cin.get(input, 50);
  cin.get();

  sIndex = findIndex(list, input);
  
  if (sIndex == -1) {
    cout << "the vertex is inexistent" << endl;
    return;
  }

  //if the vertices are the same it doesn't work
  if (fIndex == sIndex) {
    cout << "this is invalid can't have two of the same vertexes for edge" << endl;
    return;
  }

  //else
  else {

    //get weight
    cout << "enter the weight you would like for the edge" << endl;
    cin >> data;
    cin.get();

    //if the weight was positive add it into the table
    if (data >= 0) {

      if (table[fIndex][sIndex] == -1) {
	table[fIndex][sIndex] = data;
      }
      else {
	cout << "an edge already exists" << endl;
      }
    }
    else {
      cout << "invalid weight" << endl;
    }
  }
}

//adds vertex to graph
void addVertex(vertex** list) {

  //get vertex name from user
  char* input = new char[50];
  int index = 0;
  
  cout << "name the vertex" << endl;
  cin.get(input, 50);
  cin.get();
  
  //add it to the list
  while (index < size && list[index] != NULL) {
    index++;
  }

  //if the list is already full
  if (list[index] != NULL) {
    cout << "not enough space" << endl;
    return;
  }

  //else add it to the list
  else {
    list[index] = new vertex(input);
  }
}
