// Rafael Amauri Diniz Augusto --- 651047

// Collection of functions to be used in Prim's algorithm

#ifndef PRIM_HPP
#define PRIM_HPP

#include <limits>

#include "graph.hpp"


class Prim
{
    private:
        // Priority Queue (PQ) to be used in Prim's algorithm
        // vertex 1 // connected_vertex // weight
        std::map<int, std::vector<std::map<int, int>>> priority_queue;
        
        void add_edge_priority_queue(int vertex1, int vertex2, int weight);
        int mst_add_lowest_edge(Graph *g, Graph *mst);

    public:
        void prim_generate_mst(Graph *g, Graph *mst, int current_vertex);
};


// Adds the edge with the lowest value in <priority_queue> to <mst> and then excludes it from the PQ
int Prim::mst_add_lowest_edge(Graph *g, Graph *mst)
{
    int lowest_edge_v1;
    int lowest_edge_v2;
    int lowest_edge_value = std::numeric_limits<int>::max();


    if(LOGGING_PRIM == 1)
    {
        std::cout << "\nCOMECANDO A PQ\n";
        for(auto i : this->priority_queue)
            for(auto j : i.second)
                for(auto k : j)
                    std::cout << i.first << " liga com " << k.first << " com peso " << k.second << "\n";


        std::cout << "TERMINANDO A PQ\n\n";
    }

    for(auto i : this->priority_queue)
        for(auto j : i.second)
            for(auto k : j)
            {
                // Skipping already visited vertexes
                if(g->visited_vertexes[k.first] == 2)
                    continue;

                // Finding lowest value of all edges in the PQ
                if(k.second < lowest_edge_value)
                {
                    if(LOGGING_PRIM == 1)
                        std::cout << "Nova menor aresta é " << k.second << ", pois é menor que " << lowest_edge_value << "\n";

                    lowest_edge_v1     =  i.first;
                    lowest_edge_v2     =  k.first;
                    lowest_edge_value  =  k.second;
                }
            }

    // Adds the selected edge to the MST
    mst->add_edge(lowest_edge_v1, lowest_edge_v2, lowest_edge_value);

    // Deleting added edge from the PQ
    if(LOGGING_PRIM == 1)
        std::cout << "Deletei " << lowest_edge_v1 << " - " << lowest_edge_v2 << " da PQ\n";

    for(int i = 0; i < this->priority_queue.find(lowest_edge_v1)->second.size(); i++)
        if(this->priority_queue.find(lowest_edge_v1)->second.at(i).find(lowest_edge_v2)->first == lowest_edge_v2)
            this->priority_queue.find(lowest_edge_v1)->second.at(i).erase(lowest_edge_v2);

    return lowest_edge_v2;
}


// Adds an edge to the priority queue
void Prim::add_edge_priority_queue(int vertex1, int vertex2, int weight)
{
    std::map<int, int> temp;
    
    temp = {{vertex2, weight}}; 
    this->priority_queue[vertex1].push_back(temp);
}


// Finds the minimum spanning tree and loads it into <mst>
void Prim::prim_generate_mst(Graph *g, Graph *mst, int current_vertex)
{
    g->visited_vertexes[current_vertex] = 1;

    // Add vertexes adjacent to <current vertex> to the PQ
    for(auto i : g->adjacent_vertexes[current_vertex])
        for(auto j : i)
        {
            // Skipping visited vertexes so they don't get added to the PQ
            if(g->visited_vertexes[j.first] != 2)
            {
                g->visited_vertexes[j.first] = 1;
                this->add_edge_priority_queue(current_vertex, j.first, j.second);
            }
        }
    
    // If sizes are different, it means <mst> still hasn't found a way to all the vertexes in <g>
    if(mst->adjacent_vertexes.size() != g->adjacent_vertexes.size())
    {
        g->visited_vertexes[current_vertex] = 2;
        int selected_destination_vertex = this->mst_add_lowest_edge(g, mst);
        
        this->prim_generate_mst(g, mst, selected_destination_vertex);
    }

    return;
}


// Public function
void prim_count_cycles(Graph *g, int current_vertex)
{
    Prim *p = new Prim();
    Graph *mst = new Graph();
    p->prim_generate_mst(g, mst, current_vertex);
    
    g->num_cycles = g->num_edges - mst->num_edges;
    return;
}

#endif