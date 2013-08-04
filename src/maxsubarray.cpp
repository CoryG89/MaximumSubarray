/**
* Filename:		MaxSubSeq.cpp
* Author:		Cory Gross
* Description:	Contains algorithms of different strategy and complexities for
*				solving the Maximum Subsequence Sum problem. Also known as the
*				maximum sub-array. The divide and conquer algorithm is adapted
*				from psuedo-code found in the textbook (Intro to Algorithms, 
*				Cormen). There is also a quadratic time brute force algorithm.
*
* Modified:		March 24, 2012
**/
#include <climits>

/**
* Quadratic time algorithm. Here the computation is a little
* more organized. Second thing
**/
int bruteMaxSum(int A[], int start, int end) {
	int maximum = 0;
	int current = 0;

	for (int i = 0; i <= end; i++) {
		current = 0;
		for (int j = i; j <= end; j++) {
			current += A[j];
			if (current > maximum) {
				maximum = current;
			}
		}
	}
	return maximum;
}


/**
* Divide & Conquer algorithm introduced in Intro to Algorithms. (Cormen). This is
* adapted to only return the sum and not the range so that it will be doing no
* extra work compared to my other algorithms. This was implemented from psuedo-code.
* The divideHelper function is linear time, used to calculate the subsequences that
* cross the mid-point, the prototype is listed above, definition below.
**/
int divideHelper(int A[], int start, int mid, int end);
int divideMaxSum(int A[], int start, int end) {
	int mid = 0;
	int leftSum = 0, rightSum = 0, crossSum = 0;
	if (start == end) {
		return A[start];
	}
	else {
		mid = (start+end)/2;
		leftSum = divideMaxSum(A, start, mid);
		rightSum = divideMaxSum(A, mid+1, end);
		crossSum = divideHelper(A, start, mid, end);
		if (leftSum >= rightSum && leftSum >= crossSum) {
			return (leftSum < 0 ? 0 : leftSum);
		}
		else if (rightSum >= leftSum && rightSum >= crossSum) {
			return (rightSum < 0 ? 0 : rightSum);
		}
		else {
			return (crossSum < 0 ? 0 : crossSum);
		}
	}
}

/**
* Linear time utility algorithm, used by the divide & conquer algorithm above.
* Used to calculate and return the maximum of the sums of sequences that cross
* the midpoint of a given array.
**/
int divideHelper(int A[], int start, int mid, int end) {
	int leftSum = INT_MIN;
	int rightSum = INT_MIN;
	int sum = 0;

	for (int i = mid; i >= start; i--)
	{
		sum += A[i];
		if (sum > leftSum) {
			leftSum = sum;
		}
	}
	sum = 0;
	for (int j = mid + 1; j <= end; j++) {
		sum += A[j];
		if (sum > rightSum) {
			rightSum = sum;
		}
	}
	return leftSum + rightSum;
}

/**
* Adaptation of Kadane's linear time algorithm to solve the problem. Introduced
* by Jay Kadane at Carnegie-Mellon University. It seems to me that one can
* arrive at this algorithm by noting the fact (as noted in the Cormen text),
* that the problem is only interesting if there are negative numbers. And in
* fact (as not noted by Cormen), the only time you should not take the entire
* array, is if at some point the running total drops below 0. At this point,
* you should throw away the current sum and begin again.
**/
int kadaneMaxSum(int A[], int start, int end) {
	int maximum = 0;
	int current = 0;

	for (int i = 0; i <= end; i++) {
		current += A[i];
		if (current < 0) {
			current = 0;
		}
		if (current > maximum) {
			maximum = current;
		}
	}
	return maximum;
}
