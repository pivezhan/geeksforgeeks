/* Here All algorithms for sorting are implemented*/


#include <stdio.h>
#include <stdlib.h>

// C++ program for implementation of Heap Sort
#include <iostream>
using namespace std;

#define swap(a, b) ({    \
  typeof (a) _tmp = (a); \
  (a) = (b);             \
  (b) = _tmp;            \
})

// void swap(int *a, int *b)
// {
//     int temp;
//     temp = *a;
//     *a = *b;
//     *b = temp;
// }

/*
////////////////////////////////////
//////// selection sort ////////////
////////////////////////////////////
The selection sort algorithm sorts an array by repeatedly 
finding the minimum element (considering ascending order) 
from unsorted part and putting it at the beginning. 
The algorithm maintains two subarrays in a given array.
1) The subarray which is already sorted.
2) Remaining subarray which is unsorted.

//// C program for implementation of selection sort
//// Time Complexity: O(n^2) as there are two nested loops.
//// Auxiliary Space: O(1)
//// The good thing about selection sort is it never 
makes more than O(n) swaps and can be useful when 
memory write is a costly operation.
*/
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;
  
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;
  
        // Swap the found minimum element with the first element
        swap(arr[min_idx], arr[i]);
    }
}

/*
///////////////////////////////////
/////////// Bubble sort ///////////
///////////////////////////////////
// Worst and Average Case Time Complexity: O(n*n). 
Worst case occurs when array is reverse sorted.
// Best Case Time Complexity: O(n). 
Best case occurs when array is already sorted.
Auxiliary Space: O(1)

*/
void bubbleSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)     
 
       // Last i elements are already in place  
       for (j = 0; j < n-i-1; j++)
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}
 

/* 
///////////////////////////////////
/////////// Insertion sort ///////////
///////////////////////////////////

To sort an array of size n in ascending order: 
1: Iterate from arr[1] to arr[n] over the array. 
2: Compare the current element (key) to its predecessor. 
3: If the key element is smaller than its predecessor, 
compare it to the elements before. 
Move the greater elements one position up to make space 
for the swapped element.

Function to sort an array using insertion sort
// Time Complexity: O(n^2) 
// Auxiliary Space: O(1)
// Boundary Cases: Insertion sort takes maximum time to sort 
if elements are sorted in reverse order. 
And it takes minimum time (Order of n) 
when elements are already sorted.
*/

void insertionSort1(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


void insertionSort2(int arr[], int n){
	int key, i, j;
	for (i = 1; i < n; ++i){
		for (j = i - 1, key = arr[i]; j >= 0 && arr[j] > key; j--){
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = key;
	}
}


/*
///////////////////////////////////
/////////// Merge Sort ////////////
///////////////////////////////////
MergeSort(arr[], l,  r)
If r > l
     1. Find the middle point to divide the array into two halves:  
             middle m = l+ (r-l)/2
     2. Call mergeSort for first half:   
             Call mergeSort(arr, l, m)
     3. Call mergeSort for second half:
             Call mergeSort(arr, m+1, r)
     4. Merge the two halves sorted in step 2 and 3:
             Call merge(arr, l, m, r)

Time Complexity: Sorting arrays on different machines. 
Merge Sort is a recursive algorithm and time complexity 
can be expressed as following recurrence relation. 
T(n) = 2T(n/2) + θ(n)

The above recurrence can be solved either using the Recurrence Tree
method or the Master method. 
It falls in case II of Master Method and the solution 
of the recurrence is θ(nLogn). 
Time complexity of Merge Sort is  θ(nLogn) in all 3 cases
(worst, average and best) as merge sort always divides the array
into two halves and takes linear time to merge two halves.
Auxiliary Space: O(n)
Algorithmic Paradigm: Divide and Conquer
Sorting In Place: No in a typical implementation
Stable: Yes
*/
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 

void mergeSort(int arr[], int l, int r)
{
/* l is for left index and r is right index of the
sub-array of arr to be sorted */
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
}


/*
///////////////////////////////////
/////////// Heap Sort ////////////
///////////////////////////////////
    Heap Sort Algorithm for sorting in increasing order: 
1. Build a max heap from the input data. 
2. At this point, the largest item is stored at the root of the heap. 
Replace it with the last item of the heap followed by reducing the size of heap by 1. 
Finally, heapify the root of the tree. 
3. Repeat step 2 while the size of the heap is greater than 1.
Time Complexity: Time complexity of heapify is O(Logn). 
Time complexity of createAndBuildHeap() is O(n) and 
the overall time complexity of Heap Sort is O(nLogn).
Applications of HeapSort 
1. Sort a nearly sorted (or K sorted) array 
2. k largest(or smallest) elements in an array 
*/
void heapify(int arr[], int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
 
    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;
 
    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;
 
    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
 
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    // main function to do heap sort
    // Build heap (rearrange  array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
 
    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);
 
        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}


int main()
{
    // int num;
    // printf("How many numbers:\n");
    // scanf("%d", &num);
    // int *input;
    // input = (int*)malloc(num*sizeof(int));
    // int count = 0;
    // while(1)
    // {
    //     scanf("%d", &input[count]);
    //     count++;
    //     if (count == num)
    //     {
    //         break;
    //     }
    // }
    // for (int i = 0; i < num; ++i)
    // {
    //     printf("input= %d\n", input[i]);
    // }
    int num = 5;
    int input[5] = {1, 5, 3, 4, 10};
    for (int i = 0; i < num; ++i)
    {
        printf("input= %d\n", input[i]);
    }

    // heapSort(input, num);
    // insertionSort1(input, num);
    // selectionSort(input, num);
    // bubbleSort(int arr[], int n);
    mergeSort(input, 0, num - 1);

    for (int i = 0; i < num; ++i)
    {
        printf("soted= %d\n", input[i]);
    }
    return 0;
}