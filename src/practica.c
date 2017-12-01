/*
 ============================================================================
 Name        : practica.c
 Author      : Francisco Marquina
 Version     :
 Copyright   : Your copyright notice
 Description : Hello MPI World in C 
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"
#include <math.h>

#define PI 3.14159265

float  getSin(float dato) {
		return sin(dato);
}

int main(int argc, char* argv[]){

	//dimensión del array pasado por parámetro
	int width_maze = strtol(argv[1], NULL, 10);
	// string to long(string, endptr, base)

	//Nuestro tablero de juego
	float maze[width_maze][width_maze];

	//Random
	time_t t;

	//Creamos nuestro archivo
	FILE *file;

	int  my_rank; /* rank of process */
	int  p;       /* number of processes */
	int source;   /* rank of sender */
	int dest;     /* rank of receiver */
	int tag=0;    /* tag for messages */
	char message[100];        /* storage for message */
	int i,j;

	MPI_Status status ;   /* return status for receive */
	
	/* start up MPI */
	
	MPI_Init(&argc, &argv);
	
	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
	
	/* find out number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &p); 
	
	
	if (my_rank ==0){

	    /*  open for writing */

		file = fopen("~/data_gnuplot", "rb+");

	    if (file == NULL) {
	        printf("File does not exists \n");
	  //      file = fopen("~/data_gnuplot", "wb");
	    }

		/* Intializes random number generator */
		srand((unsigned) time(&t));

		//variables para el primer caso
		int x1 = rand() % 100;
		int y1 = rand() % 100;

		/* Print random numbers from 0 to 100 */
		printf("Aleatorio: %d\n", rand() % 100);
		printf("[%d,%d]=%f \n", x1,y1, maze[x1][y1]);

		printf ("seno: %f\n",getSin(5.6));

		//inicializamos el tablero
		for (i=0; i<width_maze; i++) {
			for (j=0; j<width_maze; j++) {
				maze[i][j] = 0.0;
	//		    fprintf(file, "[%d,%d]=%f ", i,j, maze[i][j]);
				printf("[%d,%d]=%f ", i,j, maze[i][j]);
			}
		//	fprintf(file, "\n");
			printf("\n");
		}

		//fclose(file);

		printf("Hello MPI World From process 0: Num processes: %d\n",p);
		for (source = 1; source < p; source++) {
			MPI_Recv(message, 100, MPI_CHAR, source, tag,
				  MPI_COMM_WORLD, &status);
			printf("%s\n",message);
		}

	}
	else{
		/* create message */
		sprintf(message, "Hello MPI World from process %d!", my_rank);
		dest = 0;
		/* use strlen+1 so that '\0' get transmitted */
		MPI_Send(message, strlen(message)+1, MPI_CHAR,
		   dest, tag, MPI_COMM_WORLD);
	}

	/* shut down MPI */
	MPI_Finalize();

	return 0;
}
