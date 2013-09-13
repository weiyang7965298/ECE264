

#include "pa03.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Read a file of integers.
 *
 * Arguments:
 *
 * filename: the name of a file that contains a list of integers (one
 * per line)
 * 
 * numberOfIntegers: pointer to store the number of integers in the
 * file. You need to update the value stored at the address which is
 * the pointer's value
 *
 * Returns:
 *
 * a array of integers from the file, or NULL if *any* error is
 * encountered.
 *
 * You do NOT know how many integers are in the file until you have
 * read it. Once you know how many integers there are, you can modify
 * the "numberOfIntegers" variable. (Note that this is a pointer, not
 * an integer) You must allocate memory to store the integers.
 * 
 * Once memory is allocated to store the integers, you will need to
 * re-read the values from the file. To do this, you must reset the
 * file pointer to the beginning of the file using the function
 * "fseek".
 * 
 * You should not use rewind (if you have learned it somewhere).  The
 * difference of rewind and fseek is that rewind does not tell you
 * whether it fails.  
 *
 * One way to read integeres is to use the "fscanf" function.  It is
 * easier than reading one character at a time by using fgetc.
 *
 * You must use malloc in this function.
 * 
 * Some old books encourage readers to type cast in front of malloc,
 * something like
 *
 * int * ptr = (int *) malloc(sizeof(int) * size);
 *
 * Type cast is no longer needed and in fact is discouraged now.  You
 * should *NOT* type cast malloc.  It is discouraged even though it is
 * not wrong.
 *
 * The allocated memory will be released in pa03.c. You do not need to
 * worry about releasing memory.
 *
 * You will receive zero if you allocate a large array whose size is
 * independent of the number of integers in the file.  For example, if
 * you write this
 *
 * int array[10000];
 * 
 *
 */

int * readIntegers(const char * filename, int * numberOfIntegers)
{   
  FILE *f = fopen(filename, "r");
  if(f == NULL) 
    {
      fclose(f);
      return NULL;
    }
  

  //  *numberOfIntegers = 0;
  int n = 0 ;  // the number of integers
  int temp = 0; // temporary value
  while(fscanf(f, "%d", & temp) == 1)
    { 
      // (*numberOfIntegers) ++
      n++;    
    } 
  // printf("\n length is %d\n", n);  this line is test the length.
  *numberOfIntegers = n;
  
  int *arr;
  arr = malloc(sizeof(int) * n);
  fseek(f,0,SEEK_SET);

  int i=0;
  while(fscanf(f, "%d", & arr[i]) == 1)
    //while(fscanf(f, "%d",&temp) == 1)
    {
      // arr[i] = temp;
      i++;
    }              
  fclose(f);
  return arr;
}

/**
 * Sort an (ascending) array of integers
 *
 * Arguments:
 * arr    The array to search
 * length Number of elements in the array
 *
 * Uses "quicksort" to sort "arr".  Use the first element of the array
 * as the pivot.  
 *
 * Your solution MUST use recursive function (or functions)
 * 
 * quicksort works in the following way: 
 * 
 * find an element in the array (this element is called the
 * pivot). 
 *
 * rearrange the array's elements into two parts: the part smaller
 * than this pivot and the part greater than this pivot; make the pivot
 * the element between these two parts
 * 
 * sort the first and the second parts separately by repeating the 
 * procedure described above
 * 
 * You will receive no point if you use any other sorting algorithm.
 * You cannot use selection sort, merge sort, or bubble sort.
 * 
 * Some students are fascinated by the name of bubble sort.  In
 * reality, bubble sort is rarely used because it is slow.  It is a
 * mystery why some students (or even professors) like bubble sort.
 * Other than the funny name, bubble sort has nothing special and is
 * inefficient, in both asymptotic complexity and the amount of data
 * movement.  There are many algorithms much better than bubble sort.
 * You would not lose anything if you do not know (or forget) bubble
 * sort.
 *
 */
void swap(int *a, int *b)
{
  int temp;
  temp  = *a;
  *a = *b;
  *b = temp;
}

void quicksort(int *arr, int ind1, int ind2)
{ 
  int left;
  int right;
  int pivot;
  if(ind1 == ind2)
    {return;}
  if(ind1 < ind2)
    {
      left = ind1;
      right = ind2;
      //pivot = arr[ind1];
      pivot = ind1;
      while(left < right)
	{

	  while(arr[right] > arr[pivot]&&(right > ind1))
	    {right--;}
	  while(arr[left] <= arr[pivot]&&(left < ind2))
	    {left++;}
          if(left < right)
	    {
	      swap(&arr[left], &arr[right]);
	    }
	}

      swap(&arr[pivot], &arr[right]);
      // swap(&pivot, &arr[right]);
      quicksort(arr,ind1, left-1);
      quicksort(arr,right+1,ind2);
    }
}

void sort(int * arr, int length)
{
  quicksort(arr, 0, length-1);
}
/**
 * Use binary search to find 'key' in a sorted array of integers
 *
 * Arguments:
 * 
 * arr The array to search. Must be sorted ascending.  You do not need
 *        to check. This array is from the result of your sort
 *        function. Make sure your sort function is correct before you
 *        start writing this function.
 *
 * length Number of elements in the array
 * key    Value to search for in arr
 *
 * Returns:
 * The index of 'key', or -1 if key is not found.
 *
 * Since the array is sorted, you can quickly discard many elements by
 * comparing the key and the element at the center of the array. If
 * the key is the same as this element, you have found the index.  If
 * the key is greater than this element, you can discard the first
 * half of the array.  If the key is smaller, you can discard the
 * second half of the array.  Now you have only half of the array to
 * search.  Continue this procedure until either you find the index or
 * it is impossible to find a match.
 * 
 * Your solution MUST use recursive function (or functions)
 *
 * Don't forget that arrays are 'zero-indexed'. Also, you must
 * use a binary search to pass this question.
 * 
 * You will receive no point if you do the following because it is not
 * binary search.  This is called linear search because it checks
 * every element.
 *
 * int ind;
 * for (ind = 0; ind < length; ind ++)
 * {
 *    if (arr[ind] == key)
 *    {
 *       return ind;
 *    }
 * }
 * return -1;
 */

int searchhelp(int * arr,int low, int high, int key)
{ 

  int mid = (low + high) / 2;
  // printf("mid is %d , arr[mid] is %d\n", mid, arr[mid]);   this line is to check the code;
   if(low > high){ return -1;}
   if(arr[mid] == key){return mid;}
   if(arr[mid]> key){return searchhelp(arr,low,mid-1,key);}
   else {return searchhelp(arr,mid+1,high,key);}
}

int search(int * arr, int length, int key)
{
  return (searchhelp(arr, 0, length - 1 , key));
}


