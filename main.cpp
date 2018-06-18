/*
 * Author: Aryan Gupta
 * Graph Creator - this program allows the user to create a Graph using an adjacency matrix 
 */

#include <iostream> 
#include <cstring> 
#include <vector> 
#include <limits> 
#include <algorithm>

using namespace std;

//make a vertex struct which contains a vector of the edges (pointers to other vertexes), a name, and the weights of the edges (in order)
struct vertex {
  char * name;
  vector < vertex * > edges;
  vector < int > weight;
};

//function declarations
void addEdge(vector < vertex * > AM, char * first, char * second, int weight);
void removeEdge(vector < vertex * > &AM, char * first, char * second);
void removeVertex(vector < vertex * > &AM, char * name);
void print(vector < vertex * > AM);
void find(vector < vertex * > AM, vertex * first, vertex * second);

int main() {
  //creates adjacency matrix
  vector < vertex * > AM;

  cout << "Enter PRINT to print." << endl;
  cout << "Enter EDGE to add an edge." << endl;
  cout << "Enter REDGE to remove an edge." << endl;
  cout << "Enter VERTEX to add a vertex." << endl;
  cout << "Enter RVERTEX to remove a vertex." << endl;
  cout << "Enter FIND to find shortest path." << endl;
  cout << "Enter QUIT to quit." << endl;
  
  while (true) {
    //print out commands
    cout << '\n';
    cout << "Enter a command: ";
    //gets input for command
    char * input = new char[100];
    cin.getline(input, 100);
    if (strcmp(input, "PRINT") == 0) {
      //calls print function
      print(AM);
    } else if (strcmp(input, "EDGE") == 0) {
      //gets the vertexes and weight
      char * first = new char();
      char * second = new char();
      int weight;
      cout << "Enter the first vertex: ";
      cout << "> ";
      cin.getline(first, 20);;
      cout << "\nEnter the second vertex: ";
      cin.getline(second, 20);

      cout << "\nEnter the weight: ";
      cout << "> ";
      cin >> weight;
      cin.get();
      //calls the funcion to add the edge
      addEdge(AM, first, second, weight);
    } else if (strcmp(input, "REDGE") == 0) {
      //gets the vertexes that the edge is supposed to be on
      char * first = new char();
      char * second = new char();
      cout << "Input the name of the first vertex (where the edge originates):" << endl;
      cout << "< ";
      cin.getline(first, 20);
      cout << "Input the name of the second vertex:" << endl;
      cout << "< ";
      cin.getline(second, 20);
      //calls the function to remove the edge
      removeEdge(AM, first, second);
    } else if (strcmp(input, "VERTEX") == 0) {
      //adds the vertex with a name into the vector of all the vertexes
      char * name = new char();
      cout << "Input the name of the vertex:";
      cin.getline(name, 20);
      vertex * temp = new vertex();
      temp -> name = name;
      AM.push_back(temp);
    } else if (strcmp(input, "RVERTEX") == 0) {
      //gets the name of the vertex to be removed
      char * name = new char();
      cout << "\nEnter the name of the vertex: ";
      cout << "> ";
      cin.getline(name, 20);
      //calls the function to remove the vertex
      removeVertex(AM, name);
    } else if (strcmp(input, "FIND") == 0) {
      //gets the vertexes where the path should be found between
      char * first = new char();
      char * second = new char();
      cout << "Input the starting vertex name: " << endl;
      cout << "> ";
      cin.getline(first, 20);
      cout << "Input the second vertex name: " << endl;
      cout << "> ";
      cin.getline(second, 20);
      //checks that both vertexes exist
      //then calls the function if they do
      vertex * firstV = NULL;
      vertex * secondV = NULL;

      for (vector < vertex * > ::iterator it = AM.begin(); it != AM.end(); ++it) {
        if (strcmp(( * it) -> name, first) == 0) {
          firstV = * it;
        } else if (strcmp(( * it) -> name, second) == 0) {
          secondV = * it;
        }
      }
      if (firstV != NULL && secondV != NULL) {

        find(AM, firstV, secondV);
      } else {

        cout << "\nSome vertexes don't exist. " << endl;
      }
    }else if(strcmp(input, "QUIT") == 0){
      exit(0); 
    
    }else {
      cout << endl;
      cout << "Not a valid input." << endl;
    }
  }
} // int main() '}'

void addEdge(vector < vertex * > AM, char * first, char * second, int weight) {
  //check if the vertexes exist
  vertex * firstV = NULL;
  vertex * secondV = NULL;
  for (vector < vertex * > ::iterator it = AM.begin(); it != AM.end(); ++it) {
    if (strcmp(( * it) -> name, first) == 0) {
      firstV = * it;
    } else if (strcmp(( * it) -> name, second) == 0) {
      secondV = * it;
    }
  }
  //add the edge to the vector in the first vertex and add the weight
  if (firstV != NULL && secondV != NULL) {
    firstV -> edges.push_back(secondV);
    firstV -> weight.push_back(weight);

  }
}

void removeVertex(vector < vertex * > & AM, char * name) {
  vertex * temp = NULL;
  //finds the vertex with name and deletes the vertex

  for (vector < vertex * > ::iterator it = AM.begin(); it != AM.end(); ++it) {
    if (strcmp(( * it) -> name, name) == 0) {
      temp = * it;
      AM.erase(it);
      break;
    }
  }
  //deletes any edges to temp
  for (vector < vertex * > ::iterator it = AM.begin(); it != AM.end(); ++it) {
    vector < vertex * > vEdges = ( * it) -> edges;
    vector < int > vWeight = ( * it) -> weight;
    int count = 0;
    cout << (*it)->name << ", ";
    //this is pretty much removeEdge method of removing edges
    for (vector < vertex * > ::iterator it2 = vEdges.begin(); it2 != vEdges.end(); ++it2) {
      count++;
      cout << (*it2)->name;
      if (( * it2) == temp) {
	vEdges.erase(it2);
	vWeight.erase(vWeight.begin() + (count - 1));
	( * it) -> edges = vEdges;
	( * it) -> weight = vWeight;
	break;
      }
    }
  }

  
}
void removeEdge(vector < vertex * > &AM, char * first, char * second) {
  //makes sure that the vertexes exist and find the vertex pointers corresponding to the names
  vertex * firstV = NULL;
  vertex * secondV = NULL;
  for (vector < vertex * > ::iterator it = AM.begin(); it != AM.end(); ++it) {
    if (strcmp(( * it) -> name, first) == 0) {
      firstV = * it;
    } else if (strcmp(( * it) -> name, second) == 0) {
      secondV = * it;
    }
  }
  //go through edges of first
  //delete edge
  //delete weight from weights
  vector < vertex * > fEdges = firstV -> edges;
  vector < int > fWeights = firstV -> weight;
  int count = 0;
  for (vector < vertex * > ::iterator it = fEdges.begin(); it != fEdges.end(); ++it) {
    count++;
    if (( * it) == secondV) {
      fEdges.erase(it);
      fWeights.erase(fWeights.begin() + (count - 1));
      firstV -> edges = fEdges;
      firstV -> weight = fWeights;
      break;
    }
  }

}
//method to check for containment of a vertex in a vector of vertexes
bool contains(vector < vertex * > AM, vertex * ver) {
  if (std::find(AM.begin(), AM.end(), ver) != AM.end()) {
    return true;
  }
  return false;
}

void find(vector < vertex * > AM, vertex * start, vertex * end) {
  //create vectors that are needed
  //1. storing the path
  //2. storing the temp path
  //3. sptSet- shortest path tree set
  //4. lengths of the paths
  //5. more temporary vectors used - connected path, etc.
  vector < vector < vertex * >> paths;
  vector < vertex * > newPath;
  vector < vertex * > sptSet;
  vector < int > length;
  vector < vertex * > con;
  vector < vertex * > c; //temporary vertex used to perform operations
  //starts dijkstras algorithm - first add the starting vertex into the vectors 
  c.push_back(start);
  paths.push_back(c);
  sptSet.push_back(start);
  //assign the first distance to be zero
  length.push_back(0);
  //set up temporary vertex pointers so operations can be perforned on them easier
  vertex * current;
  vertex * next;
  vertex * previous;
  //make numbers to store needed values - counting and lengths, etc.
  int currentLength;
  int count;
  int count2;
  int minimum;
  bool finished = false;
  bool found;
  //calls functions on the next vector - iterates through connected vertexes
  //set the variables back to the default state each call
  while (!finished) {
    found = false;
    finished = true;
    count = 0;
    minimum = std::numeric_limits < int > ::max();
    for (vector < vertex * > ::iterator it = sptSet.begin(); it != sptSet.end(); ++it) { //goes through the set of vertexes
      count++;
      current = ( * it);
      currentLength = length.at(count - 1);
      con = current -> edges;
      count2 = 0;
      if (!con.empty()) { //if there are more vertexes, check them
        finished = false;
        //finds the one with smallest weight
        for (vector < vertex * > ::iterator it2 = con.begin(); it2 != con.end(); ++it2) {
          count2++;
          if (!contains(sptSet, ( * it2))) {
            //adds to the SPTset
            if ((currentLength + current -> weight.at(count2 - 1)) < minimum) {
              minimum = currentLength + current -> weight.at(count2 - 1);
              next = ( * it2);
              previous = current;
              found = true;
            }
          }
        }
      }
    }
    //print out the result
    //
    if (finished || !found) {
      cout << "There is no path between the vertices." << endl;
      return;
    }
    for (vector < vector < vertex * >> ::iterator it = paths.begin(); it != paths.end(); ++it) {
      //goes through values and sets them again
      c = ( * it);
      if (c.back() == previous) {
        newPath = ( * it);
        newPath.push_back(next);
        paths.push_back(newPath);
        length.push_back(minimum);
        sptSet.push_back(next);
        break;
      }
    }
    //check to make sure all vertices exist in AM
    for(vector<vertex*>::iterator it = newPath.begin(); it!=newPath.end(); ++it){
      //cout << (*it)->name << endl;
      bool exist = false;
      for(vector<vertex*>::iterator it1 = AM.begin(); it1!=AM.end(); ++it1){
	if(strcmp((*it)->name, (*it1)->name)==0){
	  exist = true;
	  break;
	}
      }
      if(!exist){
	cout << "no path found" << endl;
	return; 
      }
    }
    if (next == end) { //since the last node is found, then print out the route and length to it!
      cout << "\nShortest path: ";
      for (vector < vertex * > ::iterator it = newPath.begin(); it != newPath.end(); ++it) {
        cout << ( * it) -> name << " ";
      }
      cout << "\nTotal weight: " << minimum << endl;
      return;
    }
  }
}

void print(vector < vertex * > v) {
  //prints a row of the things in the vertex
  cout << " ";
  for (vector < vertex * > ::iterator it = v.begin(); it != v.end(); ++it) {
    cout << "      " << ( * it) -> name;
  }
  //checks if it is connected and print if it is or not
  for (vector < vertex * > ::iterator it = v.begin(); it != v.end(); ++it) {
    cout << endl;
    cout << ( * it) -> name;
    vector < vertex * > connect = ( * it) -> edges;
    vector < int > length = ( * it) -> weight;
    //see if connected and print or not
    for (vector < vertex * > ::iterator ite = v.begin(); ite != v.end(); ++ite) {
      int count = 0;
      bool found = false;
      if (connect.empty()) {
        cout << "      " << "0";
      } else {
        for (vector < vertex * > ::iterator iter = connect.begin(); iter != connect.end(); ++iter) {
          count++;
          if (( * iter) -> name == ( * ite) -> name) {
            //print out 1 if there is an edge
            cout << "      " << length.at(count-1);
            found = true;
          }
        }
        if (!found) {
          cout << "      " << "0";
        }
      }
    }
  }
  cout << endl;
}
