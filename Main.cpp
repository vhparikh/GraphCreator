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

void addVertex(vertex** list);
void addEdge(vertex** list, int** table);

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

  while (quit == false) {

    cin.get(input, 50);
    cin.get();

    if (strcmp(input, "add vertex") == 0) {
      addVertex(list);
    }

    else if (strcmp(input, "add edge") == 0) {
      //call edge
    }
    
    else if (strcmp(input, "print") == 0) {
      for (int i = 0; i < size; i++) {
	if (list[i] != NULL) {
	  cout << list[i]->name << endl;
	}
      }
    }
    
    else if (strcmp(input, "quit") == 0) {
      quit = true;
    }
    
  }
  
}

void addEdge(vertex** list, int** table) {

  char input[50];
  int index = 0;
  
  cout << "what is the first vertex of the edge" << endl;
  cin.get(input, 50);
  cin.get();

  while (index < size && strcmp(list[index]->name, input) != 0) {
    index++;
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
