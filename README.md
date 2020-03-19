# CSS342-Sorting
Get an instinctive understanding of how different sorting algorithms 
perform at load.  Introduce the idea of monitoring what your program 
is doing. Give you practice in various sorting algorithms. 

You will implement an ArrayList class deriving from the provided 
ListInterface class.   

You will add additional instrumentation to your ArrayList class 
that will return the number of times a particular method has been called.
See header file.  Note that the statistic variables must be static.  
IE when you make a new array as part of merge sort, any manipulation to 
the new array must count in your statistics. 

You will write a program to read in a data file, and an optional command 
from the command line.   The data file will contain integer values in a 
random order, one value per line.  The optional command ‘-d’ will tell 
the program to dump the sorted output of the file to cout. 

So “sortstatistics -d filename” will read in the file, and print out 
the sorted file.  “sortstatistics filename’ will print out the statistics,
but not the sorted file. 

You will read in the data file and sort it using a Insertion Sort, 
Merge Sort, and Quick Sort. 

