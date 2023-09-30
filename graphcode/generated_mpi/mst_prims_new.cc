#include "mst_prims_new.h"
using namespace std;

void Compute_MST_Prims(Graph &g, int start_node, std::vector<int> &mst_weights, int &num_mst_nodes, boost::mpi::communicator world)
{
    MPI_Op reduce_edge_op;
    MPI_Op_create((MPI_User_function *)reduce_global_min, 1, &reduce_edge_op);

    NodeProperty<bool> inMST;
    inMST.attachToGraph(&g, (bool)false);

    if(world.rank() == g.get_node_owner(start_node))
    {
        inMST.setValue(start_node, true);
        num_mst_nodes++;
    }

    // A minheap of edges
    priority_queue<edge_t> pq;
    for(int i=g.start_node(); i<=g.end_node(); i++)
    {
        for(int j: g.getNeighbors(i))
        {
            Edge e = g.get_edge(i, j);
            pq.push(edge_t(i, j, g.weights.getValue(e)));
        }
    }
    
    world.barrier();

    while(true)
    {
        int min_edge[] = {-1, -1, INT_MAX};
        while(!pq.empty())
        {
            edge_t e = pq.top();
            pq.pop();
            if(!inMST.getValue(e.src) && inMST.getValue(e.dst))
            {
                min_edge[0] = e.src;
                min_edge[1] = e.dst;
                min_edge[2] = e.weight;
                break;
            }
        }

        int min_edge_global[] = {-1, -1, INT_MAX};
        MPI_Allreduce(&min_edge[0], &min_edge_global[0], 3, MPI_INT, reduce_edge_op, world);

        if(min_edge_global[2] == INT_MAX)
        {
            break;
        }
        
        if(world.rank() == g.get_node_owner(min_edge_global[0]))
        {
            inMST.setValue(min_edge_global[0], true);
        }
        num_mst_nodes++;
        mst_weights.push_back(min_edge_global[2]);
    }
}