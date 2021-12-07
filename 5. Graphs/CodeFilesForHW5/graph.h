// Homework 5
// Graph
// Tommy Liang
// This is the file that contains the construction of the classes Vertex and Graph

#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include "binary_heap.h"
#include <iostream>
#include <unordered_map>
#include <list>
#include <cfloat>
#include <queue>

//This file is for your graph implementation.
//Add everything you need in between the "ifndef and "endif" statements.
//Do not put anything outside those statements
class Graph;

class AdjacentNode{
public: 
    int node_;
    double weight_; 

    AdjacentNode(const int &node, const double &weight): node_{node}, weight_{weight}
    {
    }
};

class Vertex{
    public:
        Vertex() = default;
        ~Vertex() = default;
        //Constructor for Vertex class given the vertex value
        Vertex(int value)
        {
            value_ = value;
            distance_ = 0;
            isknown_ = false;
            path_ = nullptr;
        }
        int value_;
        double distance_;
        bool isknown_;
        Vertex *path_;
        vector<AdjacentNode> adjacent_nodes_;
};

class VertexDistance{
 public:
 	bool operator()(const Vertex *lhs, const Vertex *rhs) const{
 		//defined to aid with the priority queue for Dijkstra method
 		return lhs->distance_ > rhs->distance_; 
 	}
};

class Graph{
    public:
        Graph() = default;
        ~Graph() = default;
        Graph(int numVertices) : map_(++numVertices)
	    {
	    	for (int i = 1; i < numVertices + 1; i++)
	    		map_[i] = new Vertex(i);
	    }

        //AddConnection function
        void AddConnection(int v1, int v2, double weight)
        {
            AdjacentNode adjNode(v2, weight);
            map_[v1]->adjacent_nodes_.push_back(adjNode);
        }

        //checks if two vertices are connected or not and completes part 1 to Homework 5
        void IsConnected(const int &v1, const int &v2)
        {
            bool result = false;
            size_t size = map_[v1]->adjacent_nodes_.size();
            for(unsigned i = 0; i < size; i++)
            {
                if(map_[v1]->adjacent_nodes_[i].node_ == v2)
                {
                    result = true;
                    cout << v1 << " " << v2 << ": connected " << map_[v1]->adjacent_nodes_[i].weight_ << endl;
                    break;
                }
            }
            if(!result)
                cout << v1 << " " << v2 << ": not_connected " << endl;
        }

        // helper method for Dijkstra
        void PrintPath(Vertex* v1) {
			if (v1->path_ != nullptr) {
				//next vertex
				PrintPath(v1->path_);
			}
			cout << v1->value_ << " ";
		}

        //Dijkstra method
        void Dijkstra(int start)
        {
            map_[start]->distance_ = 0;
            std::priority_queue<Vertex *, std::vector<Vertex *>, VertexDistance> queue;
            queue.push(map_[start]);

            //Dijkstra implementation
            while(!queue.empty())
            {
                Vertex *v1 = queue.top();
                queue.pop();
                v1->isknown_ = true;

                for(unsigned i = 0; i < v1->adjacent_nodes_.size(); i++)
                {
                    int num_vertex = v1->adjacent_nodes_[i].node_;
                    Vertex *v2 = map_[num_vertex];
                    
                    if(!v2->isknown_)
                    {
                        double weight = v1->adjacent_nodes_[i].weight_;
                        if(v1->distance_ + weight < v2->distance_)
                        {
                            v2->distance_ = v1->distance_ + weight;
                            v2->path_ = v1;
                        }
                        queue.push(v2);
                    }
                }
            }

            for(unsigned i = 1; i < map_.size(); i++)
            {
                cout << map_[i]->value_ << ": ";
                double smallest_distance = map_[i]->distance_;

                PrintPath(map_[i]);
                if(smallest_distance != numeric_limits<int>::max())
                {
                    cout.precision(1);
                    cout << fixed;
                    cout << "Cost: " << smallest_distance << endl;
                }
                else
                    cout << "not_possible" << endl;
            }
        }

        //accessor method for private member num_vertices_
        size_t GetSize() const
        {
            return map_.size();
        }

    private:
        vector<Vertex*> map_;
        size_t num_vertices_;
};

#endif
