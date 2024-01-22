//============================================================================
// Name        : assign4_376.cpp
// Author      : Benjamin Luzier
// SRU ID      : A01356408
// Copyright   : 2023
// Description : Quicksort Program to dunamically allocate an array to hold test scores
//============================================================================

#include <iostream>
#include <fstream>
using namespace std;

int partition(void *a, int low, int high); //Function prototypes
void Quicksort(int *a, int low, int high);
void swap(int *a, int low, int high);

int main() {
	fstream file; //fstream file to read
	int input, *a, i, size = 0; //variable deceleration

	file.open("input.txt"); //opens the file

	while (file >> input){ //gets the size the dynamic array needs to be
		size++; //increments the size
	}
	a = new int[size]; //creates the dynamic array with the size set to size

	file.clear(); //resets the file stream
	file.seekg(0, ios::beg); //moves the pointer back to the beggining

	for(i=0; i < size; i++){ //for loop to add the contents of the file to the dynamic array
		file >> a[i];
	}

	file.close(); //closes the file as it is no longer needed

	cout << "\nDisplay Input Data: "; //for loop to display the contents of the dynamic, unsorted array
	for (i = 0; i < size; i++){
		cout << a[i] << " ";
	}

	Quicksort(a, 0, size - 1); //Quicksort is called to dynamically sort the array

	cout << "\n\nDisplay Ascending Order: "; //displays the dynamic array sorted
	for (i = 0; i < size; i++){
		cout << a[i] << " ";
	}

	delete[] a; //deletes the array to prevent memory leak

	return 0;
}

int partition(int *a, int low, int high){ //partition function that requires a pointer int, and the low and high values of the array its
										  //pre condition is to be called by quick sort, its role is to find the partition value of the array,
										  //returns the right value as the partition for the array

  int left, right; //declares low and high ints
  int pivot_item, pivot; //declares the pivot ints

  pivot_item = *(a + low); //gets the pivot pointer for the low value
  pivot = left = low; //makes the left the low one
  right = high;	//makes the right the high one

  while ( left < right )
  {
	  /* Move left while item < pivot */
	  while( *(a + left) <= pivot_item )
       left++;
    /* Move right while item > pivot */
    while( *(a + right) > pivot_item )
       right--;
    if ( left < right )
       swap(a, left, right);
   }
  /* right is a final position for the pivot */
  a[low] = a[right];
  a[right] = pivot_item;

  return right; //returns the right value from the function call

}

void Quicksort(int *a, int low, int high)//It is called by main for the pre condition, its role is to sort the array
										 //and its post condition is the fully sorted array
{
	if(low >= high) //base case
		return;

	int p = partition(a, low, high); //find the Partition of the array array

	Quicksort(a, low, p - 1); //sort left part

	Quicksort(a, p + 1, high); //sort right part


}

void swap(int *a, int low, int high)//pre condition is called by partition
									//its role is to swap to values that need to be in the correct order
{									//its post condition is the two values swapped
	int temp;						// creates the temp value to hold the value to be swapped

	temp = a[low];	//puts the low value in temp
	a[low] = a[high]; //puts the value at high to low
	a[high] = temp; //swaps the high value to what is held in temp

}
