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
template <typename Object>
class Graph;

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
        //accessor method for private member distance_
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
        std::list<std::pair< Vertex<Object>*, double>> adjacent_nodes_;
};

template <typename Object>
class VertexDistance{
 public:
 	bool operator()(const Vertex<Object> *lhs, const Vertex<Object> * rhs) const{
 		//defined to aid with the priority queue for Dijkstra method
 		return lhs->GetDistance() > rhs->GetDistance(); 
 	}
};

template <typename Object>
class Graph{
    public:
        Graph() = default;
        ~Graph() = default;

        //AddVertex function
        bool AddVertex(Object v1)
        {
            if(map_.find(v1) == map_.end())
            {
                map_[v1] = Vertex<Object>(v1);
                return true;
            }
            return false;
        }

        //AddConnection function
        void AddConnection(Object v1, Object v2, double weight)
        {
            if(map_.find(v1) == map_.end())
                map_[v1] = Vertex<Object>(v1);
            if(map_.find(v2) == map_.end())
                map_[v2] = Vertex<Object>(v2);
            Vertex<Object> *temp = &map_[v2];
            std::pair<Vertex<Object>*, double> new_connection = std::make_pair(temp, weight);
            map_[v1].adjacent_nodes_.push_back(new_connection);
        }

        double WeightOfEdge(Object &v1, Object &v2) const
        {
            auto a = map_.find(v1);
            if(a != map_.end())
            {
                auto b = a->second.adjacent_nodes_.begin();
                auto aEnd = a->second.adjacent_nodes_.end();
                while(b != aEnd)
                {
                    if(b->first->value_ == v2)
                        return b->second;
                    b++;
                }
            }
            return DBL_MAX;
        }

        //checks if two vertices are connected or not
        bool IsConnected(const Object &v1, const Object v2)
        {
            if(map_.find(v1) == map_.end() || map_.find(v2) == map_.end())
                return false;
            for(auto it = map_[v1].adjacent_nodes_.begin(); it != map_[v1].adjacent_nodes_.end(); ++it)
                if(it->first->id_ == v2)
                    return true;
        }

        //Dijkstra method
        void Dijkstra(Object start)
        {
            std::priority_queue<Vertex<Object> *, std::vector<Vertex<Object> *>, VertexDistance<Object>> queue;
            for(auto it = map_.begin(); it != map_.end(); ++it)
                Reset(it->second);
            //setting up priority queue
            map_[start].distance_ = 0.0;
            Vertex<Object> *v1 = &map_[start];
            v1->start_vertex_ = true;
            queue.push_back(v1);
            //Dijkstra implementation
            while(true)
            {
                bool finished = false;
                while(!queue.empty() && !finished)
                {
                    v1 = queue.top();
                    queue.pop();
                    if(!v1->isknown_)
                        finished = true;
                }
                if(!finished)
                    break;
                v1->isknown_ = true;
                for(auto it = v1->adjacent_nodes_.begin(); it != v1->adjacent_nodes_.end(); ++it)
                {
                    if(v1->distance_ + it->second < it->first->distance_)
                    {
                        it->first->distance_ = v1->distance_ + it->second;
                        it->first->prev_path_ = v1;
                        queue.push_back(it->first);
                    }
                }
            }
        }

        //contains method for map_
        bool Contains(const Object &vertex) const
        {
            return map_.find(vertex) != map_.end();
        }

        //accessor method for private member num_vertices_
        size_t GetSize() const
        {
            return map_.size();
        }

        void Reset(Vertex<Object> v1)
        {
            v1.distance_ = DBL_MAX;
            v1.isknown_ = false;
            v1.prev_path_ = nullptr;
            v1.start_vertex_ = false;
        }
    private:
        std::unordered_map<Object, Vertex<Object>> map_;
        size_t num_vertices_;
};

#endif
