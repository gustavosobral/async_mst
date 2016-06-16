#include <mpi.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define ROUND_MAX 4

using namespace std;

void generate_ids(vector<int> *vec, int my_id, int num_procs) {
  int generated_id;
  int size = rand() % num_procs;
  for(int i = 0; i < size; i++) {
    generated_id = rand() % num_procs;
    if(generated_id != my_id)
      vec->push_back(generated_id);
  }
}

int main(int argc, char* argv[]) {
  int my_id;
  int num_procs;
  int round;
  vector<int> ids_tosend;

  srand (time(NULL));

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  generate_ids(&ids_tosend, my_id, num_procs);

  for(int i = 0; i < ids_tosend.size(); i++)
    printf("[LOG] My id: %d | Value: %d\n", my_id, ids_tosend[i]);

  while(round < ROUND_MAX) {
    printf("[LOG] Process: %d| Round: %d\n", my_id, round);
    round++;
  }

  MPI_Finalize();
  return 0;
}
