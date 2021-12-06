#include <iostream>
#include "Graph.h"
#include <fstream>
#include <sstream> 
#include <cstdlib>

using namespace std;

template <typename Object>
void pathfindDriver(int argc, char **argv, Graph<Object> &graph) {
    
    //Begin your code here. Feel free to add any helper functions or classes you need,
    //as long as we only have to call this function to run the specified assignment.
    string file_name = argv[1];
    int vertex = atoi(argv[2]);

    std::ifstream input_file;
    input_file.open(file_name);
    if(input_file.fail())
    {
      cerr << "File failed to open" << endl;
      exit(1);
    }
    
    string line;
    Object vertex, new_vertex;
    double new_weight;
    getline(input_file, line);
    while(getline(input_file, line))
    {
      if(!line.empty())
        std::stringstream ss(line);
        ss >> vertex;
        graph.AddVertex(vertex);
        while(ss >> new_vertex && ss >> new_weight)
          graph.AddConnection(vertex, new_vertex, new_weight);
    }
    input_file.close();

    graph.Dijkstra(vertex);
    int count = 1;
    while(graph.Contains(count))
    {
      graph.GetShortestPath(count);
      ++count;
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
		return 0;
    }

    Graph<int> graph;
    pathfindDriver(argc, argv, graph);

    return 0;
}
