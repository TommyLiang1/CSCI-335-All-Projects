#include <iostream>
#include "Graph.h"
#include <fstream>
#include <sstream> 
#include <cstdlib>

using namespace std;

void pathfindDriver(int argc, char **argv) {
    
    //Begin your code here. Feel free to add any helper functions or classes you need,
    //as long as we only have to call this function to run the specified assignment.
    string file_name = argv[1];
    int num_of_vertex = atoi(argv[2]);

    std::ifstream input_file;
    input_file.open(file_name);
    if(input_file.fail())
    {
      cerr << "File failed to open" << endl;
      exit(1);
    }

    Graph map_graph(num_of_vertex);
    string line;
    int vertex, new_vertex;
    double new_weight;

    while(getline(input_file, line))
    {
      if(!line.empty())
      {
        std::stringstream ss(line);
        ss >> vertex;
        while(ss >> new_vertex && ss >> new_weight)
          map_graph.AddConnection(vertex, new_vertex, new_weight);
      }
    }
    input_file.close();

    map_graph.Dijkstra(vertex);
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
		return 0;
    }

    pathfindDriver(argc, argv);
    return 0;
}
