#ifndef GENCPP_MST_PRIMS_NEW_H
#define GENCPP_MST_PRIMS_NEW_H
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<atomic>
#include<set>
#include<vector>
#include<queue>
#include"../mpi_header/graph_mpi.h"

class edge_t
{
public:
    int src;
    int dst;
    int weight;
    edge_t(int src, int dst, int weight) : src(src), dst(dst), weight(weight) {}
    edge_t() : src(-1), dst(-1), weight(INT_MAX) {}
    bool operator<(const edge_t &e) const
    {
        return weight < e.weight;
    }
};

void reduce_global_min(int in[], int inout[], int *len, MPI_Datatype *dptr)
{
    if(in[2] < inout[2])
    {
        inout[0] = in[0];
        inout[1] = in[1];
        inout[2] = in[2];
    }
}

void Compute_MST_Prims(Graph &g, int start_node, std::vector<int> &mst_weights, int &num_mst_nodes, boost::mpi::communicator world);

#endif