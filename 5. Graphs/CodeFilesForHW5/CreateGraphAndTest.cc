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

template <typename Object>
void graphTestDriver(int argc, char **argv, Graph<Object> &graph) {
    
    //Begin your code here. Feel free to add any helper functions or classes you need,
    //as long as we only have to call this function to run the specified assignment.
    const string graph_file_name = argv[1];
    const string adjacent_file_name = argv[2];

    std::ifstream input_file;
    input_file.open(graph_file_name);
    if(input_file.fail())
    {
      cerr << "Graph file failed to open" << endl;
      exit(1);
    }

    string line;
    Object vertex, new_vertex;
    double new_weight;

    getline(input_file, line); //get first line which contains the number of vertices
    while(getline(input_file, line))
    {
      if(!line.empty())
      {
        std::stringstream ss(line);
        ss >> vertex;
        graph.AddVertex(vertex);
        while(ss >> new_vertex && ss >> new_weight)
          graph.AddConnection(vertex, new_vertex, new_weight);
      }
    }
    input_file.close();

    std::ifstream a_input_file;
    a_input_file.open(adjacent_file_name);
    if(a_input_file.fail())
    {
      cerr << "Adjacency file failed to open" << endl;
      exit(1);
    }

    int v1, v2;

    while(getline(a_input_file, line))
    {
      std::stringstream ss(line);
      ss >> v1;
      ss >> v2;
      double weightOfEdge = graph.WeightOfEdge(v1, v2);
      if(weightOfEdge != DBL_MAX) //v1 and v2 are connected
        cout << v1 << " " << v2 << ": connected " << weightOfEdge << endl;
      else
        cout << v1 << " " << v2 << ": not_connected " << endl;
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_File>" << "<ADJACENCY_QUERYFILE>" << endl;
		return 0;
    }

    Graph<int> map_graph;
    graphTestDriver(argc, argv, map_graph);

    return 0;
}
