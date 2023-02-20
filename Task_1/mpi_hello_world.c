#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int commsize;
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);

    // Get the rank of the process
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Print off a hello world message
    printf("Communicator size = %d, My rank = %d \n", commsize, my_rank);
    // Finalize the MPI environment.
    MPI_Finalize();
}