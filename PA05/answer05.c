#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa05.h"

/*
 * Read a file of integers.
 *
 * Arguments:
 *
 * filename: the name of a file that contains a list of integers (one
 * per line)
 * 
 * numInteger: pointer to store the number of integers in the
 * file. You need to update the value stored at the address which is
 * the pointer's value.  If the function fails to update the value, it
 * is considered reading the file has failed.
 *
 * Returns:
 *
 * a array of integers from the file, or NULL if *any* error is
 * encountered.
 *
 * Hint: use fscanf
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
 * You will receive zero if you allocate a large array whose size is
 * independent of the number of integers in the file.  For example, if
 * you write this
 *
 * int array[10000];
 * 
 *
 */

int * readInteger(char * filename, int * numInteger)
{  
  FILE *f = fopen(filename, "r");
  if(f == NULL)
    {
      fclose(f);
      return NULL;
    }
  int n = 0 ; // the number of integers
  int temp = 0; // temporary value
  while(fscanf(f, "%d", & temp) == 1)
    {
      n++;
    }
  *numInteger = n;
  
  int *arrInteger;
  arrInteger = malloc(sizeof(int) * n);
  fseek(f,0,SEEK_SET);

  int i=0;
  while(fscanf(f, "%d", & arrInteger[i]) == 1)
    {
      i++;
    }
  fclose(f);
  return arrInteger;
   
}

/* ----------------------------------------------- */

/*
 * Read a file of strings. This is similar to readInteger. However,
 * each string is an array of characters. The function needs to
 * allocate memory for an array of strings, i.e., array of arrays of
 * characters. In other words, this is a two-dimensional array (thus,
 * char **).
 *
 * Arguments:
 *
 * filename: the name of a file that contains a list of strings (one
 * per line)
 * 
 * numString: pointer to store the number of strings in the
 * file. You need to update the value stored at the address which is
 * the pointer's value.  If the function fails to update the value, it
 * is considered reading the file has failed.
 *
 * Returns:
 *
 * a array of strings from the file, or NULL if *any* error is
 * encountered.
 *
 * Hint: use fgets. 
 * 
 * Remember that an array of strings is a two-dimensional array of
 * characters
 *
 * You do NOT know how many strings are in the file until you have
 * read it. Once you know how many strings there are, you can modify
 * the "numberOfStrings" variable. (Note that this is a pointer, not
 * an string) You must allocate memory to store the strings.
 * 
 * Once memory is allocated to store the strings, you will need to
 * re-read the values from the file. To do this, you must reset the
 * file pointer to the beginning of the file using the function
 * "fseek". 
 *
 * You should not use rewind (if you have learned it somewhere).  The
 * difference of rewind and fseek is that rewind does not tell you
 * whether it fails.  
 *
 * One way to read stringes is to use the "fscanf" function.  It is
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
 * You will receive zero if you allocate a large array whose size is
 * independent of the number of strings in the file.  For example, if
 * you write this
 *
 * char array[10000];
 * 
 *
 */

char * * readString(char * filename, int * numString)
{
  char buf[MAXIMUM_LENGTH];
  FILE *f = fopen(filename, "r");
  if(f == NULL)
    {
      return NULL;
    } 

  int n = 0 ; // the number of line
  while(fgets(buf, MAXIMUM_LENGTH, f) != NULL)
    {
      n++;
    }
  
  *numString = n;
  
  char * * arrString;
  arrString = malloc(sizeof(char*) * (*numString));
  fseek(f,0,SEEK_SET);

  int i = 0;
  while(fgets(buf,MAXIMUM_LENGTH,f) != NULL)
    {
      arrString[i] = malloc(sizeof(char)*(strlen(buf)+1));
      strcpy(arrString[i],buf);
      i++;
    }

  fclose(f);
  return arrString;
}

/* ----------------------------------------------- */
/*
 * print an array of integers, one integer per line
 */
void printInteger(int * arrInteger, int numInteger)
{
  int i;
  for(i = 0; i < numInteger; i++)
    {
       printf("%d\n", arrInteger[i]);
    }
}

/* ----------------------------------------------- */
/*
 * print an array of strings, one string per line
 *
 * Hint: printf("%s" ... can print a string
 */
void printString(char * * arrString, int numString)
{
  int i;
  for(i = 0; i < numString; i++)
    {
      printf("%s", arrString[i]);    
      int len = strlen(arrString[i]);    
      if(len == 0 || arrString[i][len-1] != '\0')
        {printf("\n");}
    }
}

/* ----------------------------------------------- */
/*
 * release the memory occupied by the array of integers
 */
void freeInteger(int * arrInteger, int numInteger)
{ 
  free(arrInteger);
}

/* ----------------------------------------------- */
/*
 * release the memory occupied by the array of strings
 *
 * Hint: an array of strings is a two-dimensional array of characters
 */
void freeString(char * * arrString, int numString)
{
  int i;
  for (i = 0; i < numString; i++){free(arrString[i]);}
  free(arrString);
}

/* ----------------------------------------------- */
/*
 * Write integers to a file, one integer per line
 *
 * Arguments:
 *
 * filename: the name of a file.
 * arrInteger: an array of integers
 * numInteger: the number of integers 
 *
 * Returns:
 * 1 if saving to the file successfully
 * 0 if *any* error is encountered
 *
 * Hint: use fprintf(... %d
 *
 */

int saveInteger(char * filename, int * arrInteger, int numInteger)
{  
  FILE * f;
  f = fopen(filename,"w");
  if(f == NULL){return 0;}
  int i;
  for(i = 0; i < numInteger; i++)
  {fprintf(f, "%d\n", arrInteger[i]);}
  fclose(f);
  return 1;
}

/* ----------------------------------------------- */
/*
 * Write strings to a file, one string per line
 *
 * Arguments:
 *
 * filename: the name of a file.
 * arrString: an array of strings
 * numString: the number of strings 
 *
 * Returns:
 * 1 if saving to the file successfully
 * 0 if *any* error is encountered
 *
 * Hint: use fprintf(... %s
 *
 */

int saveString(char * filename, char * * arrString, int numString)
{   
  FILE *f;
 
  f = fopen(filename, "w");
  if(f == NULL){return 0;}
   int i;
  for(i = 0; i < numString; i++)
    {
      fprintf(f, "%s", arrString[i]);
      int strlength = strlen(arrString[i]);
      if(arrString[i][strlength - 1] != '\n' || strlength == 0)
      {fprintf(f,"\n");}
    }
  fclose(f);
  return 1;
}

/* ----------------------------------------------- */
/*
 * sort an arry of integers by calling the built-in qsort function in
 * the C library.  You need to provide the comparison function. Please
 * read the Linux manual about qsort
 *
 */
int compint(const void * p1, const void *p2)
{
  /* const: the function can read, cannot write */
  /* p1 stores the address of an element in the array 
     p2
   */
  int * intp1 = (int *) p1; 
  int * intp2 = (int *) p2; 
  int intv1 = * intp1;  /* get the value at that address */
  int intv2 = * intp2;  /* get the value at that address */
  if(intv1 < intv2){return -1;}
  if(intv1 == intv2){return 0;}
  return 1;
}
void sortInteger(int * arrInteger, int numInteger)
{
  qsort(arrInteger, numInteger, sizeof(int), compint);
}


/* ----------------------------------------------- */
/*
 * sort an arry of strings by calling the built-in qsort function in
 * the C library.  You need to provide the comparison function. Please
 * read the Linux manual about qsort
 *
 * Hint: use strcmp in the comparison function
 *
 */
int compstring(const void *p1, const void *p2)
{return strcmp(*((char **)p1),*((char **)p2));}

void sortString(char * * arrString, int numString)
{
  qsort(arrString, numString, sizeof(char*), compstring);
}


