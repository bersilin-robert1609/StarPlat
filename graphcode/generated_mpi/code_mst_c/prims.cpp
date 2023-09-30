#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <vector>
#include <mpi.h>

using namespace std;

#define INF numeric_limits<ll>::max()
#define ROOT 0
typedef long long int ll;

int32_t my_rank, num_procs;

ll num_nodes;
ll num_local_nodes;
ll total_distance;

vector<vector<ll>> global_weights;
vector<vector<ll>> local_weights;
vector<ll> dist;
vector<ll> parent;
vector<bool> in_tree;

vector<edge_t> mst_edges;

class edge_t
{
public:
    ll src;
    ll dest;
    ll weight;
    edge_t(ll src, ll dest, ll weight) : src(src), dest(dest), weight(weight) {}
};

void reduce_global_min(ll& local_min, ll& global_min)
{
    MPI_Allreduce(&local_min, &global_min, 1, MPI_LONG_LONG_INT, MPI_MIN, MPI_COMM_WORLD);
}

void check_error(int32_t error_code, int32_t my_rank, string message)
{
    if(error_code != MPI_SUCCESS)
    {
        cerr<<"Error: "<<message<<" in process "<<my_rank<<endl;
        MPI_Finalize();
        exit(-1);
    }
}

void first_parse(ifstream &fin)
{
    // all lines have the form: <src> <dest> <weight>
    // Get num of lines
    string line;
    ll max_node = 0;
    while(getline(fin, line))
    {
        istringstream iss(line);
        ll src, dest, weight;
        iss>>src>>dest>>weight;
        max_node = max(max_node, max(src, dest));
    }
    num_nodes = max_node + 1;

    global_weights.resize(num_nodes, vector<ll>(num_nodes, INF));
}

int32_t main(int argc, char** argv)
{
    if(argc != 2)
    {
        cerr<<"Usage: "<<argv[0]<<" <input_file>"<<endl;
        exit(-1);
    }

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    ifstream fin;
    fin.open(argv[1]);
    check_error(fin.is_open() ? MPI_SUCCESS : MPI_ERR_FILE, my_rank, "opening input file");

    if(my_rank == ROOT)
    {
        first_parse(fin);

    }
    else
    {

    }
}