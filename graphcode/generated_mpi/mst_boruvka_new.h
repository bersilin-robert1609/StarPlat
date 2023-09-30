#ifndef GENCPP_MST_BORUVKA_NEW_H
#define GENCPP_MST_BORUVKA_NEW_H
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<atomic>
#include<set>
#include<vector>
#include"../mpi_header/graph_mpi.h"

void Boruvka(Graph& g, boost::mpi::communicator world );

#endif