#include <mpi.h>
#include <stdio.h>
#include <vector>

#define ROUND_MAX 4

using namespace std;

int my_id;
int num_procs;

void generate_ids(vector<int> *vec) {
  vec->push_back(3);
  vec->push_back(10);
  vec->push_back(4);
}

int main(int argc, char* argv[]) {
  int my_id;
  int num_procs;
  int round;
  vector<int> ids_tosend;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  
  generate_ids(&ids_tosend);
  for(int i = 0; i < ids_tosend.size(); i++)
    printf("[LOG] %d\n", ids_tosend[i]);

  while(round < ROUND_MAX) {
    printf("[LOG] Process: %d| Round: %d\n", my_id, round);
    round++;
  }

  MPI_Finalize();
  return 0;
}
