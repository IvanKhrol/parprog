#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int N = 0;
    double sum = 0.;
	if (argc != 2) {
		printf("Wrong argument's size, please check your input\n");
        MPI_Finalize();
		exit(-1);
	}
	N = atoi(argv[1]);
    
    int my_rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    int commsize = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);

    double start_time =  MPI_Wtime();

    int start_num = my_rank * N / commsize + 1;
    int end_num   = (my_rank == commsize - 1 ) ? N : (my_rank + 1) * N / commsize;
    
    // printf("My rank = %d, start = %d, end = %d\n", my_rank, start_num, end_num);

    for(int i = start_num; i < end_num + 1; ++i)
        sum += 1. / i; 
    // printf("My rank = %d, sum = %lg\n", my_rank, sum);
    if(my_rank != 0){
        MPI_Send(&sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    } else {
        double tmp = 0;
        for(int i = 1; i < commsize; ++i){
            MPI_Recv(&tmp, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sum += tmp;
        }

        double end_time =  MPI_Wtime();
        printf("Summary = %lg in %lg seconds\n", sum, end_time - start_time);
    }

    MPI_Finalize();
}