/** Algorithm Prototypes - Listed here in order of efficiency
    Defined in file MaxSubSeq.cpp----------------------------*/
int bruteMaxSum(int A[], int start, int end);	// Alg. #1 - O(n^2)
int divideMaxSum(int A[], int start, int end);  // Alg. #2 - O(nlogn)
int kadaneMaxSum(int A[], int start, int end);	// Alg. #3 - O(n)