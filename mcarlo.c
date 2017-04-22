/*****************mcarlo.c**************/
//Author: Aaron Brunette
//Github: abrunette
//Last updated: 2017/03/14
//Compiled with gcc
//Written on Vim
//Purpose: To estimate the value of pi using a monte carlo simulation.
/***************************************/

//Current Issues: Not a great approximation of pi. 100,000,000 points gives roughly 3.09.
//Possible problems are the generation of the random double. Changed the original instruction
//from random(), which is not C standard, to rand(). rand() is seeded by time.h, although
//it did not seem to increase the accuracy of the pi result. There is also a possible issue in
//creating and joining the threads. Each thread does userInput number of dots, this results in
//userInput * tCount number of final dots (i.e. userInput = 100, tCount = 4, total points = 400)
//I am not sure if this was the original intent of the assignment, but using that results in skewed
//approximations of pi (~15 using tCount of 4), so I quick fixed that by dividing by tCount. This
//lowers the accuracy of the pi calculation.

#include <stdio.h>      //C standard I/O library
#include <unistd.h>     //POSIX OS API
#include <errno.h>      //C error codes
#include <stdlib.h>     //C general library
#include <fcntl.h>      //file control library
#include <time.h>       //time/clock library
#include <pthread.h>    //pthread library
#include <math.h>	//C Math library

//Global variable
double hit_count = 0;

//Purpose: Generate a random double variable and return it.
double random_double()
{
	return rand() / ((double)RAND_MAX + 1);
}

//Purpose: In a new thread, generate a number of random points.
// If the points fall inside the circle, increments the global
// variable. returns nothing;
//Parameters: Takes the first argument from command line and 
//converts it to a number to generate simulations.
//Algorithm: Use a for loop to generate a specified number of
// random points within a 1x1 box. Creates a random x and y
// coordinate. Increments the global variable if the product
// of the too coordinates multiplied and added together is
// less then one.
void *monteCarlo(void* argv) 
{
	//convert argument to int
	char* theConvert = (char*)argv;
	int pointNum = atoi(theConvert);

	double x, y;	//coordinate variables
	int i;		//counter

	srand(time(NULL));	//seed random

	//while there are still points to be made
	//continues to generate coordinates
	for(i = 0; i < pointNum; i++) {
		x = random_double() * 2.0 - 1.0;
		y = random_double() * 2.0 - 1.0;

		//find position, if position is
		//within circle, increment hit_count
		if (sqrt(x*x + y*y) < 1.0)
			++hit_count;
	}

	//exit thread
	pthread_exit(0);	
}

//Purpose: To create a new thread that generates a specified
// number of random coordinates in order to calulate the
// approximate value of pi.
//User information: ./mcarlo <simulation count>
//Input: Takes one argument from command line to determine how
//many simulations will be run.
//Output: Outputs an estimation of pi based on simulations.
int main(int argc, char *argv[]) 
{
	int tCount = 5;		//number of threads to be created
	pthread_t tid[tCount];	//declare threads
	int i = 0;		//counter

	//check if there is too few arguments
	if(argc == 1) {
		printf("Too few arguments, requires at least 1.");
		return 0;
	}
	//check if there are too many arguments
	else if(argc > 2) {
		printf("Too many arguments, requires 1.");
		return 0;
	}

	//convert argument to double
	double userInput = atoi(argv[1]);

	//create threads
    	for (i = 0; i < tCount; i++)
    	{
		//printf("Creating thread %d ... \n", i);
		pthread_create(&tid[i], NULL, &monteCarlo, (void *)argv[1]);
    	}

    	//join and wait for all threads
    	for (i = 0; i < tCount; i++)
    	{
		pthread_join(tid[i], NULL);
		//printf("Completed join with thread %d \n", i);
    	}

	//estimate pi based on the number of total hits in the circle by
	//the total number of points generated
	double pi = ((4 * hit_count) / userInput) / tCount;

	printf("\nPi is approximately: %f\n", pi);

	return 0;
}
