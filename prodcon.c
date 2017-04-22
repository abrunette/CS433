/*****************prodcon.c**************/
//Author: Aaron Brunette
//Github: abrunette
//Last updated: 2017/03/25
//Compiled with gcc
//Written on Vim
//Purpose: To implement a thread synchronization system.
/***************************************/

//Current Issues: This will not compile. I did not get this file
//to a working state. I hope to complete it sometime in the future
//to complete my knowledge on the topic of mutex's and semaphores,
//as well as checksum.

#include <stdio.h>      //C standard I/O library
#include <unistd.h>     //POSIX OS API
#include <errno.h>      //C error codes
#include <stdlib.h>     //C general library
#include <fcntl.h>      //file control library
#include <time.h>       //time/clock library
#include <pthread.h>    //pthread library
#include <semaphore.h> //semaphore library

/*typedef unsigned char byte;
typedef unsigned short int word16;
typedef unsigned int word32;*/

//GLOBAL VARIABLES
int BUFFER_LEN = 64000;		//buffer length
int buff[BUFFER_LEN];	//prod and cons shared mem
int ntimes;		//number of times the prod and cons cycle
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;	//mutex lock
int checksum = 0;
//sem_t prod, cons;	//semaphore for producer and consumer

//checksum here		**************************

//Producer thread
void *Producer(void* argv)
{
	int i, j;	
	for(i = 0; i < ntimes; i++)
	{
		pthread_mutex_lock(&lock);
	
		for(j = 0; j < 30; j++)
		{
			srand(time(NULL));
			buff[j] = (rand()%256);
			
		}

		pthread_mutex_unlock(&lock);
	}

	pthread_exit(0);
}

//Consumer thread
void *Consumer(void* argv) 
{
	int i, j;	
	for(i = 0; i < ntimes; i++)
	{
		pthread_mutex_lock(&lock);
	
		for(j = 0; j < 30; j++)
		{
			//read out here
		}

		pthread_mutex_unlock(&lock);
	}
	

	pthread_exit(0);
}


//argv[1]=memsize argv[2]=ntimes//
int main(int argc, char* argv[])
{
	if(argc != 3)	//check if user entered the correct amount of arguments
	{
		printf("Usage: ./prodcon <memsize> <ntimes> \n");
		exit(1);	
	}
	if(atoi(argv[2]) > 2000)	//checks if ntimes is too large, 2000 * 32 = 64000bytes = buffer length
	{
		perror("memsize too large.");
		exit(1);
	}
	if(atoi(argv[2]) < 1)	//checks that ntimes is positive
	{
		perror("ntimes must be a positive number.");
		exit(1);
	}
/*
	//BUFFER_LEN  = strtol(argv[1], NULL, 10);	//convert argv[1] to int

	if((memsize % 32) != 0)	//check that memsize is a multiple of 32
	{
		perror("First argument must be a multiple of 32.\n");
		exit(1);
	}
	int blocks = memsize / 32;	//find total blocks of memory
*/
	ntimes = strtol(argc[2], NULL, 10);		//convert ntimes to int

	//semaphore initialize
	sem_init(&counter, 0, 1);

	pthread_t tid[2];	//initialize two threads
	pthread_create(&tid[0], NULL, &Producer, NULL);	//create consumer thread
	pthread_create(&tid[1], NULL, &Consumer, NULL);	//create producer thread
	pthread_join(tid[0], NULL);	//join thread 1
	pthread_join(tid[1], NULL);	//join thread 2
	
	//semaphore destroy
	sem_destroy(&Producer);
	sem_destroy(&Consumer);
	pthread_mutex_destroy(&lock);

	return 0;
}

/*Initializing shared memory
	int id = shmget(ftok(argc[optind], 1), memsize, oflag);
	if(id < 0) //check for memory error
	{
		perror("shmget");
		exit(1);
	}
	
	shm = shmat(id, NULL, 0);
	if(shm == NULL) //check for memory error
	{
		perror("shmat");
		exit(1);
	}
//End of shared memory get */


/*
#define SVSHM_MODE	0664

int main(int argc, char *argv[])
{

	int	c, id, oflag;
	char	*ptr;
	size_t	length;

	oflag = SVSHM_MODE | IPC_CREAT;
	while ((c = getopt(argc, argv, "e")) != -1) {
		switch (c) {
			case 'e':
				oflag |= IPC_EXCL;
				break;
		}
	}

        printf("argc %d optind %d \n", argc, optind);

	if (optind != argc - 2) {
		printf("Usage: shmget [ -e ] <key> <length> \n");
		exit(-1);
	}

	length = atoi(argv[optind + 1]);
	
	id = shmget(ftok(argv[optind], 1), length, oflag);
	if (id == -1) {
		perror("shmget error");
		exit(-1);
	}

	ptr = shmat(id, NULL, 0);
	if (ptr == NULL) {
		perror("shmat error");
		exit(-1);
	}

	exit(0);
}
	
*/

/*
//Taken from www.csee.usf.edu/~kchriste/tools/checksum.c
//=============================================================================
//=  Compute Internet Checksum for count bytes beginning at location addr     =
//=============================================================================
word16 checksum(byte *addr, word32 count)
{
  register word32 sum = 0;

  // Main summing loop
  while(count > 1)
  {
    sum = sum + *((word16 *) addr)++;
    count = count - 2;
  }

  // Add left-over byte, if any
  if (count > 0)
    sum = sum + *((byte *) addr);

  // Fold 32-bit sum to 16 bits
  while (sum>>16)
    sum = (sum & 0xFFFF) + (sum >> 16);

  return(~sum);
}
*/
