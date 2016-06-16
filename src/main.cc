#include <mpi.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

#define APP_TAG 0
#define ACK_TAG 1
#define SAFETY_TAG 2
#define ROUND_MAX 10

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

void send_safe(int my_id, int num_procs, int buffer) {
  for(int i = 0; i < num_procs; i++) {
    if(i == my_id)
      continue;
    MPI_Send(&buffer, 1, MPI_INT, i, SAFETY_TAG, MPI_COMM_WORLD);
  }
}

int main(int argc, char* argv[]) {
  int my_id;
  int round;
  int buffer;
  int num_procs;
  int ack_count;
  int safety_count;
  MPI_Status status;
  vector<int> ids_tosend;

  srand (time(NULL));

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  while(round < ROUND_MAX) {
    safety_count = 0;
    buffer = (round * 100) + my_id;
    generate_ids(&ids_tosend, my_id, num_procs);
    ack_count = ids_tosend.size();

    // Send random number of application messages
    for(int i = 0; i < ids_tosend.size(); i++)
      MPI_Send(&buffer, 1, MPI_INT, ids_tosend[i], APP_TAG, MPI_COMM_WORLD);

    if(ack_count == 0) {
      send_safe(my_id, num_procs, buffer);
      safety_count++;
    }

    // Whaits until recieve safety for all neighbor
    while(safety_count < num_procs) {
      MPI_Recv(&buffer, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

      switch(status.MPI_TAG) {
        case APP_TAG:
          MPI_Send(&buffer, 1, MPI_INT, status.MPI_SOURCE, ACK_TAG, MPI_COMM_WORLD);
          break;
        case ACK_TAG:
          ack_count--;
          if(ack_count == 0) {
            send_safe(my_id, num_procs, buffer);
            safety_count++;
          }
          break;
        case SAFETY_TAG:
          safety_count++;
      }
    }

    printf("[LOG] Process %d synced! Round %d\n", my_id, round + 1);
    usleep(1000);
    round++;
  }

  MPI_Finalize();
  return 0;
}
