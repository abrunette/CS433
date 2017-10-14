/*****************vmmpr.cpp**************/
//Author: Aaron Brunette
//Github: abrunette
//Last updated: 2017/04/25
//Compiled with gcc
//Written on Vim
//Purpose: Perform page replacement using FIFO, LRU, and Optimal algorithms.
/***************************************/

#include <iostream>   	//input/output library
#include <cstdlib>	//general purpose C library
#include <cerrno> 	//error handling
#include <ctime>	//clock/time library	
#include <time.h>
using namespace std;

//Global Variables
const int numPageref = 15;	//number of page references to be generated
const int numFramecount = 3;	//number of frames allowed

//Purpose: To search for a value in an array.
// returns true if it is found.
//Parameters: array is the array to be searched
// through. value is the value that is being
// searched for.
//Algorithm: Increment through the array with a
// for loop.
bool searchArray(int array[], int value)
{
	for(int i = 0; i < numFramecount; i++)
	{
		if(array[i] == value)
			return true;
	}

	return false;	//value not found in array
}

//Purpose: To determine the number of page faults
// generated when using the FIFO algorithm to swap
// pages.
//Parameters: Frefpages is the array of page references
// FpageFrames is the 
//Algorithm: First in first out page swap algorithm
int FIFOpages(int FrefPages[numPageref])
{
	int Fresult = 0;
	int FIFOframearray[numFramecount];
	int frameLoc = 0;	//will alternate between 0, 1, 2 

	//initialize page frames to nothing
	for(int k = 0; k < numFramecount; k++)
	{
		FIFOframearray[k] = -1;
	}

	for(int i = 0; i < numPageref; i++)
	{
		if(!searchArray(FIFOframearray, FIFOframearray[i]))	//page not in frame
		{
			FIFOframearray[frameLoc] = FrefPages[i];
			Fresult++;	//page fault occurred, increment counter
			if(frameLoc == (numFramecount - 1))
				frameLoc = 0;	//return to front
			else
				frameLoc++;
		}
		else {}	//page is in frame
	}

	return Fresult;
}

//Purpose: To determine the number of page faults 
// generated when using the LRU algorithm to swap
// pages.
//Parameters: 
//Algorithm: Least recently used page swap algorithm
int LRUpages(int LrefPages[numPageref])
{
	int Lresult = 0;
	int LRUframearray[numFramecount];
	
	//initialize page frames to nothing
	for(int negCount = 0; negCount < numFramecount; negCount++)
	{
		LRUframearray[negCount] = -1;
	}

	for(int i = 0; i < numPageref; i++)
	{
		if(!searchArray(LRUframearray, LRUframearray[i]))	//page not in frame
		{
			if(searchArray(LRUframearray, -1))	//empty frame
			{
				for(int j = 0; j < numFramecount; j++)
				{
					if(LRUframearray[j] == -1)	
					{
						LRUframearray[j] = LrefPages[i];
						break;
					}
				}
			}
			else	//no empty frames
			{
				for(int queueMV = (numFramecount - 2); queueMV > 0; queueMV--)
				{
					LRUframearray[(queueMV + 1)] = LRUframearray[queueMV];
				}
				LRUframearray[0] = LrefPages[i];
			}
		}
		else	//page is in frame
		{
			for(int pcount = 0; pcount < numFramecount; pcount++)
			{
				
			}
		}
	}

	return Lresult;
}

//Purpose: To determine the number of page faults
// generated when using the Optimal algorithm to
// swap pages.
//Parameters:
//Algorithm: Optimal page swap algorithm
int OPTIMALpages(int OrefPages[numPageref])
{
	int Oresult = 0;
	int OPTframearray[numFramecount];



	return Oresult;
}

//Purpose:
//User information:
//Algorithm: 
//Input: 
//Output: 
int main()
{
	srand(time(NULL));	//initialize random seed
	int pageReflist[numPageref];	//array for page references
	
	cout << "Randomly generating " << numPageref  << " page references...\n\n";
	for(int i = 0; i < numPageref; i++)
		pageReflist[i] = rand() % 10;	//store a random number between 0 and 9 in array

	//read out list of page references
	cout << "| ";
	for(int k = 0; k < numPageref; k++)
	{
		cout << pageReflist[k] << " | ";
	}

	//Run three different algorithms
	int FIFOfaults = FIFOpages(pageReflist);
	int LRUfaults = LRUpages(pageReflist);
	int OPTIMALfaults = OPTIMALpages(pageReflist);

	//Output results
	cout << "\n\nAlgorithm results:\n"
	     << "****************************************************************************\n"
	     << "FIFO Algorithm had " << FIFOfaults << " page faults.\n"
	     << "LRU Algorithm had " << LRUfaults << " page faults.\n"
	     << "Optimal Algorithm had " << OPTIMALfaults << " page faults.\n\n";

	exit(0);
}

/*
			while(counter != numPageref)
			{
				for(int l = 0; l < numFramecount; l++)
				{
					if(LRUpages[l] == -1)
					{
						(LRUpages[l])++;
						LRUframearray[l] = LrefPages[i];
						break;
					}
					else if(LRUpages[l] == numFramecount)
					{
						LRUframearray[l] = LrefPages[i];
						LRUframearray[l] = 0;
					}
				}
				counter++;
			}
*/


			/*
			while(frameLoc < numPageref)
			{
				LRUframearray[frameLoc] = LrefPages[i];
				
				for(int j = 0; j < numFramecount; j++)
				{
					if(LRUpages[j] != -1)
						(LRUpages[j])++;
				}			
				LRUpages[frameLoc] = 0;
				frameLoc++;
				counter++;
			}
			*/



/*
		if(!searchArray(LRUframearray, LRUframearray[i]))	//page not in frame
		{
			Lresult++;

			for(int l = 0; l < numFramecount; l++)
			{
				if(LRUframearray[l] == -1)	//empty page frame exists
				{
					LRUframearray[l] = LrefPages[i];
					for(int m = 0; m < numFramecount; m++)
					{
						if(LRUframearray[m] != -1)
							(LRUpages[m])++;
					}
					break;
				}
				if(LRUpages[l] == (numFramecount - 1))	//least recently used
				{
					LRUframearray[l] = LrefPages[i];
					for(int n = 0; n < numFramecount; n++)
						(LRUpages[n])++;			

					LRUpages[l] = 0;
					break;
				}
			}
		}
		else //page is in frame
		{
			if(searchArray(LRUpages, -1))	//if empty frame exists
			{
				for(int o = 0; o < numFramecount; o++)
				{
					if(LRUpages[o] == -1)	//empty frame
						{}	//do nothing

					else if(LRUframearray[o] != LrefPages[i])	//if frame is not LRU
						(LRUpages)++;
			
					else	//LRU frame
						LRUpages[o] = 0;
				}
				
			}
			else	//no more empty frames
			{
				for(int p = 0; p < numFramecount; p++)
				{
					if(LRU)
				}
			}
			
		}

*/






