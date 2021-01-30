//reference for shortest path https://www.youtube.com/watch?v=XB4MIexjvY0

#include <iostream>
#include <cstring>
#include <limits>
#include <vector>
#include <iterator>
#include <iomanip>

using namespace std;


const int size = 20;                                                                                                  
const int infinity = numeric_limits<int>::max();

struct vertex {
  
  char* name;

  vertex(char* newN) {
    name = newN;
  }
};

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

int findIndex(vertex** list, char* n);
void addVertex(vertex** list);
void addEdge(vertex** list, int** table);
void removeEdge(vertex** list, int** table);
void removeVertex(vertex** list, int** table);
void callShortPath(vertex** list, int** table);
void shortPath(properties** pList, int** table, vertex** list, int eIndex);

int main() {

  int* adjacencyTable[size];
  vertex* list[size];
  char input[50];
  bool quit = false;
  
  for (int i = 0; i < size; i++) {
    adjacencyTable[i] = new int[size];

    for (int j = 0; j < 20; j++) {
      adjacencyTable[i][j] = -1;
    }
    
    list[i] = NULL;
  }

  cout << "Welcome to Graph Creator!" << endl;
  
  while (quit == false) {

    cin.get(input, 50);
    cin.get();

    if (strcmp(input, "add vertex") == 0) {
      addVertex(list);
    }

    else if (strcmp(input, "add edge") == 0) {
      addEdge(list, adjacencyTable);
    }

    else if (strcmp(input, "remove edge") == 0) {
      removeEdge(list, adjacencyTable);
    }

    else if (strcmp(input, "remove vertex") == 0) {
      removeVertex(list, adjacencyTable);
    }

    else if (strcmp(input, "short path") == 0) {
      callShortPath(list, adjacencyTable);
    }
    
    else if (strcmp(input, "print") == 0) {

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
    }
    
    else if (strcmp(input, "quit") == 0) {
      quit = true;
    }
    
  }
  
}

void shortPath(properties** pList, int** table, vertex** list, int eIndex) {

  int lowCost = infinity;
  int sIndex = -1;

  for(int i = 0; i < size; i++) {

    if (pList[i]->v != NULL && pList[i]->cost < lowCost && pList[i]->flagged == false) {
      lowCost = pList[i]->cost;
      sIndex = i;
    }
  }

  if (sIndex == -1) {
    return;
  }

  if (sIndex == eIndex) {
    return;
  }

  pList[sIndex]->flagged = true;
  
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

  shortPath(pList, table, list, eIndex);
}

void callShortPath(vertex** list, int** table) {

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


  properties* pList[size];

  for(int i = 0; i < size; i++) {
    pList[i] = new properties(list[i]);
  }

  pList[fIndex]->cost = 0;
  pList[fIndex]->path.push_back(list[fIndex]);
  shortPath(pList, table, list, sIndex);

  if (pList[sIndex]->cost == infinity) {
    cout << "there is no path from these two vertices" << endl;
  }
  else {
    cout << "shortest path is: ";

    for (vector<vertex*>::iterator it = pList[sIndex]->path.begin(); it != pList[sIndex]->path.end(); it++) {
      cout << (*it)->name  << " ";
    }
  
    cout << endl;
    cout << "cost of shortest path is: " << pList[sIndex]->cost << endl;
  }
}

void removeVertex(vertex** list, int** table) {

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

  for (int i = 0; i < size; i++) {
    table[index][i] = -1;
    table[i][index] = -1;
  }

  delete list[index];
  list[index] = NULL;
}

void removeEdge(vertex** list, int** table) {

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

  table[fIndex][sIndex] = -1;
  
}

int findIndex(vertex** list, char* n) {

  int index = 0;

  while (list[index] != NULL && strcmp(list[index]->name, n) != 0) {
    index++;
  }

  if (list[index] == NULL || strcmp(list[index]->name, n) != 0) {
    return -1;
  }
  else {
    return index;
  }
  
}

void addEdge(vertex** list, int** table) {

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
  
  if (fIndex == sIndex) {
    cout << "this is invalid can't have two of the same vertexes for edge" << endl;
    return;
  }
  else {
    cout << "enter the weight you would like for the edge" << endl;
    cin >> data;
    cin.get();

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

void addVertex(vertex** list) {

  char* input = new char[50];
  int index = 0;
  
  cout << "name the vertex" << endl;
  cin.get(input, 50);
  cin.get();

  while (index < size && list[index] != NULL) {
    index++;
  }

  if (list[index] != NULL) {
    cout << "not enough space" << endl;
    return;
  }
  else {
    list[index] = new vertex(input);
  }
  
}
