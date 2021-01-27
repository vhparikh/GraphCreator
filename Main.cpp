#include <iostream>
#include <cstring>

using namespace std;

struct vertex {

  char* name;

  vertex(char* newN) {
    name = newN;
  }

};

const int size = 20;

int findIndex(vertex** list, char* n);
void addVertex(vertex** list);
void addEdge(vertex** list, int** table);
void removeEdge(vertex** list, int** table);

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
