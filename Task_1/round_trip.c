#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    MPI_Status status;

    int my_rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    int commsize = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
  
    // if (my_rank == 0) {
    //     number = -1;
    //     MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    // } else if (my_rank == 1) {
    //     MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
    //             MPI_STATUS_IGNORE);
    //     printf("Process 1 received number %d from process 0\n",
    //         number);
    // }
    // printf("%d\n", 2 % 3);

    int num = 0;
    if(my_rank == 0){
        MPI_Send(&num, 1, MPI_INT, ((my_rank + 1) % commsize), 0, MPI_COMM_WORLD);
        MPI_Recv(&num, 1, MPI_INT, commsize - 1, 0, MPI_COMM_WORLD, &status);
        printf("My rank = %d, i get number = %d\n", my_rank, num);
        ++num;
        printf("I am done\n");
    } else {
        MPI_Recv(&num, 1, MPI_INT, (my_rank - 1), 0, MPI_COMM_WORLD, &status);
        printf("My rank = %d, i get number = %d\n", my_rank, num);
        ++num;
        MPI_Send(&num, 1, MPI_INT, ((my_rank + 1) % commsize), 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}