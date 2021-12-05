// Homework 5
// Graph
// Tommy Liang
// This is the file that contains the construction of the classes Vertex and Graph

#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include "binary_heap.h"
#include <iostream>

//This file is for your graph implementation.
//Add everything you need in between the "ifndef and "endif" statements.
//Do not put anything outside those statements
template <typename Object>
class Vertex{
    public:
        friend class Graph<Object>;
        Vertex() = default;
        ~Vertex() = default;
        //Constructor for Vertex class given the vertex value
        Vertex(Object value)
        {
            value_ = value;
            distance_ = 0;
            isknown_ = false;
            start_vertex_ = false;
            prev_path_ = nullptr;
        }
        //mutator method for private member distance_
        int GetDistance()
        {
            return distance_;
        }
    private:
        Object value_;
        double distance_;
        bool isknown_;
        bool start_vertex_;
        Vertex<Object> *prev_path_;
};

template <typename Object>
class Graph{
    public:
        Graph() = default;
        ~Graph() = default;
    private:
        std::unordered_map<Object, Vertex<Object> map_;
        size_t num_vertices_;
};

#endif
