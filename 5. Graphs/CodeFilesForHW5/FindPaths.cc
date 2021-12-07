#include <iostream>
#include "graph.h"
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

void pathfindDriver(int argc, char **argv)
{

  //Begin your code here. Feel free to add any helper functions or classes you need,
  //as long as we only have to call this function to run the specified assignment.
  string file_name = argv[1];
  int start_vertex = atoi(argv[2]);

  std::ifstream input_file;
  input_file.open(file_name);
  if (input_file.fail())
  {
    cerr << "File failed to open" << endl;
    exit(1);
  }

  string size;
  getline(input_file, size);

  Graph map_graph(stoi(size));
  string line;
  int vertex, new_vertex;
  double new_weight;

  while (getline(input_file, line))
  {
    std::stringstream ss(line);
    ss >> vertex;
    while (ss >> new_vertex && ss >> new_weight)
      map_graph.AddConnection((int)vertex, (int)new_vertex, (double)new_weight);
  }
  input_file.close();

  map_graph.Dijkstra(start_vertex);
}

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    cout << "Usage: " << argv[0] << " <GRAPH_FILE>"
         << "<STARTING_VERTEX>" << endl;
    return 0;
  }

  pathfindDriver(argc, argv);
  return 0;
}
