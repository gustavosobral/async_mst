#include <mpi.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define APP_TAG 0
#define ACK_TAG 1
#define SAFETY_TAG 2
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

void send_safe(int my_id, int num_procs) {
  for(int i = 0; i < num_procs; i++) {
    if(i == my_id)
      continue;
    MPI_Send(0, 1, MPI_INT, i, SAFETY_TAG, MPI_COMM_WORLD);
  }
}

int main(int argc, char* argv[]) {
  int my_id;
  int round;
  int buffer;
  int num_procs;
  int safety_count;
  vector<int> ids_tosend;

  srand (time(NULL));

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  generate_ids(&ids_tosend, my_id, num_procs);

  while(round < ROUND_MAX) {
    safety_count = 0;
    buffer = (round * 100) + my_id;
    
    for(int i = 0; i < ids_tosend.size(); i++)
      MPI_Send(&buffer, 1, MPI_INT, ids_tosend[i], APP_TAG, MPI_COMM_WORLD);

    printf("[LOG] Process: %d| Round: %d\n", my_id, round);
    round++;
  }

  MPI_Finalize();
  return 0;
}
