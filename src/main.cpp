/**
 * Filename: 	main.cpp
 * Author:		Cory Gross
 * Description: Driver demonstrating various algorithms and their efficiencies
 *				in solving the maximum subsequences sum problem. Illustrates
 *				high-scrutiny empirical analysis of algorithmic performance.
 *
 * Modified:	March 30, 2012
 */
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>

#include "CPrecisionTimer.h"	// high resolution windows timer
#include "maxsubarray.h"		// include maximum sub array algorithms

using namespace std;

int main()
{
	/** Attempt to create and initialize file input object,
	    check for error.*/
	ifstream inFile;
	inFile.open("input.txt");
	if(inFile.fail())
	{
		cout << endl << endl << "There was a problem opening the input file.";
		cout << endl << "Press enter to continue..";
		cin.get();
		cout << endl;
		return 1;
	}


	/** Parse CSV file, print input, fill initial data structure */
	const int INPUT_SIZE = 10;
	int input[INPUT_SIZE];
	for(int i = 0; i < INPUT_SIZE; i++)
	{
		if (!inFile.eof())
			inFile >> input[i];
		else
			break;
		if(!inFile.eof())
			inFile.get();
		else
			break;
	}
	inFile.close();


	/** Display input, run algorithms, print results */
	cout << endl << "Collected input: ";
	for (int i = 0; i < INPUT_SIZE; i++)
	{
		cout << input[i];
		if (i != INPUT_SIZE - 1)
			cout << ", ";
	}


	cout << endl << endl;
	cout << "Algorithm 1-- bruteMaxSum: ";
	cout << bruteMaxSum(input, 0, INPUT_SIZE - 1);

	cout << endl << endl;
	cout << "Algorithm 2-- DivideMaxSum: ";
	cout << divideMaxSum(input, 0, INPUT_SIZE - 1);

	cout << endl << endl;
	cout << "Algorithm 3-- KadaneMaxSum: ";
	cout << kadaneMaxSum(input, 0, INPUT_SIZE - 1) << endl << endl;


	/** Create arrays of arrays to store random input data */
	const int SAMPLE_NUM = 19;
	int *A[SAMPLE_NUM];


	/** Dynamically allocate space for sample data arrays. The number
	 *  of elements in each array will begin at 10 and grow by 5 elements
	 *  for each new array. Fill dynamic arrays with random integers 
	 *  (-100 to 100 inclusive). This is a jagged 2D-array. */
	srand(static_cast<unsigned int>(time(NULL)));
	for (int i = 0; i < SAMPLE_NUM; i++)
		A[i] = new int[(i+2) * 5];
	for (int i = 0; i < SAMPLE_NUM; i++)
		for (int j = 0; j < (i+2) * 5; j++)
			A[i][j] = static_cast<int>(201.0*(rand()/(RAND_MAX + 1.0)))-100;


	/** First 3 columns are actual results from each algorithm */
	/** Last 3 columns are the expected theoretical results of each */
	int results[19][6];


	/** Number of executions to run for performance timing of each
	 *  algorithm. To get meaningful results, the number of executions
	 *  often must be very high (N >= 10000) or possibly (N >= 1000) */
	const int NUM_EXEC = 10000;														


	/** ALGORITHM 1 - PERFORMANCE TIMING (QUADRATIC) */
	cout << "Algorithm 1- Quadratic time (input sizes == 10-100 step 5, "
		 << NUM_EXEC << " executions):" << endl;
	for (int i = 0; i < SAMPLE_NUM; i++)
	{
		CPrecisionTimer timer;
		double totalTime = 0.0;
		timer.Start();
		for (int j = 1; j < NUM_EXEC; j++)
		{
			bruteMaxSum(A[i], 0, ((i+2) * 5 ) - 1);
		}
		totalTime = timer.Stop();
		totalTime *= 10000;
		results[i][0] = static_cast<int>(ceil(totalTime));
		cout << results[i][0] << endl;
	}
	cout << endl << endl;

	/** ALGORITHM 2 - PERFORMANCE TIMING (N*LOG(N)) */
	cout << "Algorithm 2- n*logn time (input sizes == 10-100 step 5, "
		 << NUM_EXEC << " executions):" << endl;
	for (int i = 0; i < SAMPLE_NUM; i++)
	{
		CPrecisionTimer timer;
		double totalTime = 0.0;
		timer.Start();
		for (int j = 1; j < NUM_EXEC; j++)
		{
			divideMaxSum(A[i], 0, ((i+2) * 5 ) - 1);
		}
		totalTime = timer.Stop();
		totalTime *= 10000;
		results[i][1] = static_cast<int>(ceil(totalTime));
		cout << results[i][1] << endl;
	}
	cout << endl << endl;

	/** ALGORITHM 3 - PERFORMANCE TIMING (LINEAR) */
	cout << "Algorithm 3- Linear time (input sizes == 10-100 step 5, "
		 << NUM_EXEC << " executions):" << endl;
	for (int i = 0; i < SAMPLE_NUM; i++)
	{
		CPrecisionTimer timer;
		double totalTime = 0.0;
		timer.Start();
		for (int j = 1; j < NUM_EXEC; j++)
		{
			kadaneMaxSum(A[i], 0, ((i+2) * 5 ) - 1);
		}
		totalTime = timer.Stop();
		totalTime *= 10000;
		results[i][2] = static_cast<int>(ceil(totalTime));
		cout << results[i][2] << endl;
	}
	cout << endl << endl;


	/** Calculate theoretical results */
	for (int i = 0; i < SAMPLE_NUM; i++)
	{
		int currentSize = (i+2) * 5;
		double log2Size = log((double)currentSize)/log(2.0);

		results[i][3] = currentSize * currentSize;  // n^2
		results[i][4] = static_cast<int>(ceil(currentSize*log2Size)); // n*logn
		results[i][5] = currentSize;				// n
	}


	/** Create file output object, check for errors */
	ofstream outFile;
	outFile.open("output.txt");
	if(outFile.fail())
	{
		cout << endl << endl;
		cout << "There was a problem opening/creating output file.";
		cout << endl << "Press enter to continue..";
		cin.get();
		cout << endl;
		return 1;
	}


	/** Write output to file */
	outFile << "Algoithm-1,Algorithm-2,Algorithm-3,";
	outFile << "T(n) = n^2,T(n) = n*log(n),T(n)=n";
	outFile << endl;
	for(int i = 0; i < SAMPLE_NUM; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			outFile << results[i][j];
			if (j < 5)
				outFile << ",";
		}
		if (i < SAMPLE_NUM - 1)
			outFile << endl;
	}
	outFile.close();


	cout << endl << "Press enter to continue..";
	cin.get();
	cout << endl;
	return 0;
}