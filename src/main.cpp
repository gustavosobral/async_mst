#include <mpi.h>
#include <stdio.h>

#define ROUND_MAX 4

int main(int argc, char* argv[]) {
  int my_id;
  int num_procs;
  int round;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  while(round < ROUND_MAX) {
    printf("[LOG] Process: %d| Round: %d\n", my_id, round);
    round++;
  }

  MPI_Finalize();
  return 0;
}
