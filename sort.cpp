/* Here All algorithms for sorting are implemented*/

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <cstring>
#include <cassert>

using namespace std;
#define RANGE 20

// #define swap(a, b) ({    \
//   typeof (a) _tmp = (a); \
//   (a) = (b);             \
//   (b) = _tmp;            \
// })


void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
/*
////////////////////////////////////
//////// priority queue ////////////
////////////////////////////////////
A typical priority queue supports following operations.
insert(item, priority): Inserts an item with given priority.
getHighestPriority(): Returns the highest priority item.
deleteHighestPriority(): Removes the highest priority item.

Using Array: A simple implementation is to use array of following 
structure.

struct item {
   int item;
   int priority;
}
insert() operation can be implemented by adding an item 
at end of array in O(1) time.
getHighestPriority() operation can be implemented by linearly
searching the highest priority item in array. 
This operation takes O(n) time.
deleteHighestPriority() operation can be implemented by first 
linearly searching an item, then removing the item by moving all 
subsequent items one position back.

Using linked list:
We can also use Linked List, time complexity of all operations with 
linked list remains same as array. 
The advantage with linked list is deleteHighestPriority() can 
be more efficient as we don’t have to move items.

Using Heaps:
Heap is generally preferred for priority queue implementation 
because heaps provide better performance compared arrays or linked list. 
In a Binary Heap, getHighestPriority() can be implemented in O(1) time, 
insert() can be implemented in O(Logn) time and deleteHighestPriority() 
can also be implemented in O(Logn) time.
With Fibonacci heap, insert() and getHighestPriority() can be 
implemented in O(1) amortized time and deleteHighestPriority() can 
be implemented in O(Logn) amortized time.

               peek()    push()    pop()
-----------------------------------------
Linked List |   O(1)      O(n)      O(1)
            |
Binary Heap |   O(1)    O(Log n)   O(Log n)
*/
typedef struct node {
    int data;
    int priority;
    struct node* next;
} Node;

// Function to create a new node
Node* newNode(int data, int priority)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->priority = priority;
    temp->next = NULL;
    return temp;
}

// Function to find the maximum node in a heap
Node* findMax(Node* root)
{
    Node* current = root;
    Node* parent = NULL;
    while (current->next != NULL) {
        parent = current;
        current = current->next;
    }
    return current;
}

// return value at the head
int peek(Node** head)
{
    return (*head)->data;
}

// Remove element with high 
// priority from a heap
void getHighestPriority(Node** head)
{
    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

void insert(Node** head, int data, int priority)
{
    Node* start = (*head);

    // Create a new node
    Node* temp = newNode(data, priority);
    
    // Special case: The head of the list has lesser
    // priority than the new node. so add the new node
    // before the head node and change the head node
    if (start == NULL || priority > start->priority) {
    temp->next = *head;
    (*head) = temp;
    }
    else {
        // Traverse the list to find 
        // the position to insert the new node
        while (start->next != NULL && 
        start->next->priority < priority) {
            start = start->next;
        }
        // Either at the end of the list or
        // at required position
        temp->next = start->next;
        start->next = temp;
        }
}

//Function to check if list is empty
int isEmpty(Node** head)
{
    return (*head) == NULL;
}





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
        for (j = i + 1; j < n; j++)
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
Replace it with the last item of the heap followed by reducing the size 
of heap by 1. 
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

/*
///////////////////////////////////
/////////// Counting Sort ////////////
///////////////////////////////////
Counting sort is a sorting technique based on keys between a
 specific range. It works by counting the number of objects 
 having distinct key values (kind of hashing). 
 Then doing some arithmetic to calculate the position of each
  object in the output sequence.
Time Complexity: O(n+k) where n is the number of elements in input array 
and k is the range of input. 
Auxiliary Space: O(n+k)
 
For simplicity, consider the data in the range 0 to 9. 
Input data: 1, 4, 1, 2, 7, 5, 2
  1) Take a count array to store the count of each unique object.
  Index:     0  1  2  3  4  5  6  7  8  9
  Count:     0  2  2  0   1  1  0  1  0  0

  2) Modify the count array such that each element at each index 
  stores the sum of previous counts. 
  Index:     0  1  2  3  4  5  6  7  8  9
  Count:     0  2  4  4  5  6  6  7  7  7

The modified count array indicates the position of each object in 
the output sequence.
 
  3) Output each object from the input sequence followed by 
  decreasing its count by 1.
  Process the input data: 1, 4, 1, 2, 7, 5, 2. Position of 1 is 2.
  Put data 1 at index 2 in output. Decrease count by 1 to place 
  next data 1 at an index 1 smaller than this index.
*/
void countingSort(int arr[], int n)
{
    // The output character array that will have sorted arr
    int *output;
    output = (int*)calloc(n, sizeof(int));
    // Create a count array to store count of inidividul
    // characters and initialize count array as 0
    int count[RANGE + 1], i;
    memset(count, 0, sizeof(count));

        // Store count of each character
    for (i = 0; i < n; ++i)
        ++count[arr[i]];

     // Change count[i] so that count[i] now contains actual
    // position of this character in output array
    for (i = 1; i <= RANGE; ++i)
        count[i] += count[i - 1];
    // Build the output character array
    for (i = 0; i < n; ++i) {
        output[count[arr[i]] - 1] = arr[i];
        --count[arr[i]];
    }
 
    /*
     For Stable algorithm
     for (i = n-1; i>=0; --i)
    {
        output[count[arr[i]]-1] = arr[i];
        --count[arr[i]];
    }
    For Logic : See implementation
    */
    // Copy the output array to arr, so that arr now
    // contains sorted characters
    for (i = 0; i < n; ++i)
        arr[i] = output[i];
}


/*
///////////////////////////////////
/////////// Radix Sort ////////////
///////////////////////////////////
https://www.geeksforgeeks.org/radix-sort/

Counting sort is a sorting technique based on keys between a
 specific range. It works by counting the number of objects 
 having distinct key values (kind of hashing). 
What if the elements are in the range from 1 to n2? 
We can’t use counting sort because counting sort will take O(n2) which is worse than comparison-based sorting algorithms. Can we sort such an array in linear time? 

Radix Sort is the answer. The idea of Radix Sort is to do 
digit by digit sort starting from least significant digit 
to most significant digit. Radix sort uses counting sort as 
a subroutine to sort.

Do following for each digit i where i varies from least significant 
digit to the most significant digit.
Sort input array using counting sort (or any stable sort) according
to the i’th digit.

Original, unsorted list:
170, 45, 75, 90, 802, 24, 2, 66

Sorting by least significant digit (1s place) gives: 
[*Notice that we keep 802 before 2, because 802 occurred 
before 2 in the original list, and similarly for pairs 
170 & 90 and 45 & 75.]

170, 90, 802, 2, 24, 45, 75, 66

Sorting by next digit (10s place) gives: 
[*Notice that 802 again comes before 2 as 802 comes before 
2 in the previous list.]

802, 2, 24, 45, 66, 170, 75, 90

Sorting by the most significant digit (100s place) gives:
2, 24, 45, 66, 75, 90, 170, 802

What is the running time of Radix Sort? 
Let there be d digits in input integers. 
Radix Sort takes O(d*(n+b)) time where b is the base for 
representing numbers, for example, for the decimal system, 
b is 10. What is the value of d? If k is the maximum possible value, 
then d would be O(logb(k)). So overall time complexity is 
O((n+b) * logb(k)). Which looks more than the time complexity 
of comparison-based sorting algorithms for a large k. 
Let us first limit k. Let k <= nc where c is a constant. 
In that case, the complexity becomes O(nLogb(n)). 
But it still doesn’t beat comparison-based sorting algorithms. 
What if we make the value of b larger?. 
What should be the value of b to make the time complexity linear? 
If we set b as n, we get the time complexity as O(n). 
In other words, we can sort an array of integers with a range from 
1 to nc if the numbers are represented in base n 
(or every digit takes log2(n) bits).


Is Radix Sort preferable to Comparison based sorting algorithms like 
Quick-Sort? 
If we have log2n bits for every digit, the running time of Radix appears
 to be better than Quick Sort for a wide range of input numbers. 
 The constant factors hidden in asymptotic notation are higher 
 for Radix Sort and Quick-Sort uses hardware caches more effectively. 
 Also, Radix sort uses counting sort as a subroutine and counting 
 sort takes extra space to sort numbers.
*/
void radixSort(int arr[], int n)
{
    
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
    // mergeSort(input, 0, num - 1);
    countingSort(input, num);

    for (int i = 0; i < num; ++i)
    {
        printf("sorted= %d\n", input[i]);
    }

    // priority queue
    Node* pq = newNode(4, 1);
    insert(&pq, 3, 2);
    insert(&pq, 5, 3);
    insert(&pq, 1, 4);

    while(!isEmpty(&pq)) {
        printf(" priority: %d ", peek(&pq));
        getHighestPriority(&pq);
    }

    return 0;
}