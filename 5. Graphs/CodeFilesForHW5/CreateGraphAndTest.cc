// Homework 5
// Create Graph And Test
// Tommy Liang
// This is the file that contains the driver for part 1 of Homework 5

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "graph.h"

using namespace std;

void graphTestDriver(int argc, char **argv)
{

  // Begin your code here. Feel free to add any helper functions or classes you need,
  // as long as we only have to call this function to run the specified assignment.
  const string graph_file_name = argv[1];
  const string adjacent_file_name = argv[2];

  std::ifstream input_file;
  input_file.open(graph_file_name);
  if (input_file.fail())
  {
    cerr << "Graph file failed to open" << endl;
    exit(1);
  }

  // Create Graph
  int num_of_vertices;
  input_file >> num_of_vertices;
  Graph map_graph(num_of_vertices);

  string line;
  int vertex, new_vertex;
  double new_weight;

  // Add edges
  while (getline(input_file, line))
  {
    if (!line.empty())
    {
      std::stringstream ss(line);
      ss >> vertex;
      while (ss >> new_vertex && ss >> new_weight)
        map_graph.AddConnection(vertex, new_vertex, new_weight);
    }
  }
  input_file.close();

  std::ifstream a_input_file;
  a_input_file.open(adjacent_file_name);
  if (a_input_file.fail())
  {
    cerr << "Adjacency file failed to open" << endl;
    exit(1);
  }

  // Checks connection between two vertices
  int v1, v2;
  while (getline(a_input_file, line))
  {
    std::stringstream ss(line);
    ss >> v1;
    ss >> v2;
    // Does all the printing in IsConnected()
    map_graph.IsConnected(v1, v2);
  }
}

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    cout << "Usage: " << argv[0] << " <GRAPH_File>"
         << "<ADJACENCY_QUERYFILE>" << endl;
    return 0;
  }

  graphTestDriver(argc, argv);
  return 0;
}
