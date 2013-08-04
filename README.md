MaximumSubarray
===============
C++ program profiling three algorithms of different complexities which solve
the maximum subarray problem. This program is meant to illustrate high-scrutiny
empirical analysis of algorithmic performance.

This program was developed to be run on the Windows platform. More specifically
this program has a dependency on the high-resolution timer included in 
`windows.h`. The accuracy / resolution of `clock()` is not sufficient for
profiling.


Algorithms
----------

 - **Algorithm 1** -- Brute force quadratic time algorithm.
 - **Algorithm 2** -- Recursive divide and conquer algorithm with
                      n*logn running time.
 - **Algorithm 3** -- Kadane's algorithm, which is the only known linear time
					  algorithm to solve this problem.

### Algorithm 1

```cpp
/**
* Quadratic time algorithm.
**/
int bruteMaxSum(int A[], int start, int end) {
	int maximum = 0;
	int current = 0;

	for (int i = start; i <= end; i++) {
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
```

### Algorithm 2

```cpp
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
		mid = (start + end) / 2;
		leftSum = divideMaxSum(A, start, mid);
		rightSum = divideMaxSum(A, mid + 1, end);
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
```
```cpp
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
```

### Algorithm 3

```cpp
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
```

Results
-------

### Algorithm 1

![Algorithm 1 Actual Complexity][alg1-actual]

![Algorithm 1 Theoretical Complexity][alg1-actual]

### Algorithm 2

![Algorithm 2 Actual Complexity][alg2-actual]

![Algorithm 2 Theoretical Complexity][alg2-theo]

### Algorithm 3

![Algorithm 3 Actual Complexity][alg3-actual]

![Algorithm 3 Theoretical Complexity][alg3-theo]

[alg1-actual]: img/alg1_actual.jpg
[alg1-theo]: img/alg1_theo.jpg
[alg2-actual]: img/alg2_actual.jpg
[alg2-theo]: img/alg2_theo.jpg
[alg3-actual]: img/alg3_actual.jpg
[alg3-theo]: img/alg3_theo.jpg