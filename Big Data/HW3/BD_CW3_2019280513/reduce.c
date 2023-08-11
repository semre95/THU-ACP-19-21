#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include "mpi.h"

#define MAX_LEN 4194304

long get_time_us()  // return the time in the unit of us
{
    struct timeval my_time;  //us
    gettimeofday(&my_time, NULL);
    long runtime_us = 1000000 * my_time.tv_sec + my_time.tv_usec; // us
    return runtime_us;
}

// TODO
// you can add your function as you want if needed
void partial_sum(int first[], int second[], int len)
{
    for (int k=0; k<len; k++)
    {
        second[k] += first[k];
    }
}
// TODO

int main(int argc, char *argv[])
{
    int size, rank;

    MPI_Init(&argc,&argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    srand(time(NULL));  // seed for rand() to generate the array randomly

    int *a, *b;     // the array used to do the reduction
   
    int *res;   // the array to record the result of YOUR_Reduce
    int *res2;  // the array to record the result of MPI_Reduce
    
    int count;
    long begin_time, end_time, use_time, use_time2; // use_time for YOUR_Reduce & use_time2 for MPI_Reduce
    
    int i;

    // initialize
    a = (int*)malloc(MAX_LEN * sizeof(int));
    b = (int*)malloc(MAX_LEN *sizeof(int));
    res = (int*)malloc(MAX_LEN * sizeof(int));
    res2 = (int*)malloc(MAX_LEN * sizeof(int));
    memset(a, 0 , sizeof(a));
    memset(b,0,sizeof(b));
    memset(res, 0 , sizeof(res));
    memset(res2, 0 , sizeof(res2));

    // TODO
    // you can add some variable or some other things as you want if needed
    
    int *partial;
    partial = (int*)malloc(MAX_LEN * sizeof(int));
    memset(partial, 0, sizeof(partial));
    // TODO

    for(count=4; count<=MAX_LEN; count*=16) // length of array : [ 4  64  1024  16384  262144  4194304 ]
    {
        // the element of array is generated randomly
    	for(i=0; i<MAX_LEN; i++)
        {
        	b[i]=a[i] = rand() % MAX_LEN;
        }

        // MPI_Reduce and then print the usetime, the result will be put in res2[]
        MPI_Barrier(MPI_COMM_WORLD);
        begin_time = get_time_us();
        MPI_Reduce(a, res2, count, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        end_time = get_time_us();
        use_time2 = end_time - begin_time;        
        if(rank == 0)
	    if(count!=4)
            printf("%d int use_time : %ld us [MPI_Reduce]\n", count, use_time2);


        // YOUR_Reduce and then print the usetime, the result should be put in res[]
        MPI_Barrier(MPI_COMM_WORLD);
        begin_time = get_time_us();
        // TODO
        // you should delete the next line, and do the reduction using your idea
        // MPI_Reduce(b, res, count, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

        if (rank == 1){
            MPI_Send(b, count, MPI_INT, 0, 2, MPI_COMM_WORLD);
        }
        if (rank == 2){
            MPI_Recv(partial, count, MPI_INT, 3, 0, MPI_COMM_WORLD, &status);
            partial_sum(partial, b, count);
            MPI_Send(b, count, MPI_INT, 0, 1, MPI_COMM_WORLD);
        }
        if (rank == 3){
            MPI_Send(b, count, MPI_INT, 2, 0, MPI_COMM_WORLD);
        }
        if (rank == 0){
            MPI_Recv(partial, count, MPI_INT, 1, 2, MPI_COMM_WORLD, &status);
            partial_sum(partial, b, count);
            if (size > 2){
                MPI_Recv(partial, count, MPI_INT, 2, 1, MPI_COMM_WORLD, &status);
                partial_sum(partial, b, count);
            }
            for (int i=0; i<count;i++)
                res[i] = b[i];
        }

        // TODO
        MPI_Barrier(MPI_COMM_WORLD);
        end_time = get_time_us();
        use_time = end_time - begin_time;
        if(rank == 0 )
		if(count!=4)
            printf("%d int use_time : %ld us [YOUR_Reduce]\n", count, use_time);

        
        // check the result of MPI_Reduce and YOUR_Reduce
        if(rank == 0)
		if(count !=4)
        {
            int correctness = 1;
            for(i=0; i<count; i++)
            {
                if(res2[i] != res[i])
                {
                    correctness = 0;
                }
            }
            if(correctness == 0)
                printf("WRONG !!!\n");
            else
                printf("CORRECT !\n");
        }
    }

    MPI_Finalize();

    return 0;
}
