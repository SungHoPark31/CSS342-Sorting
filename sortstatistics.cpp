/*
 Assignment 5
 sortStatistics.cpp
 
 This is the class where it does all the sorting.
 */

#include <iostream>
#include <istream>
#include <sstream>
#include <cstdio>
#include <fstream>
#include <string>
#include <iomanip>

#include "arrayList.h"

using namespace std;

//Prints out the entire array
template<class TYPE>
void printOutArray(const ArrayList<TYPE> &item)
{
    //Traverse through the item being passed in and print
    //it out.
    for(int i = 0; i < item.getSize(); i++)
    {
        if(i == (item.getSize() - 1))
        {
            cout << item.getAt(i);
        }
        else
        {
            cout << item.getAt(i) << ", ";
        }
        
    }
    cout << endl;
}

/*
 Reads in the file and and puts it in the arraylist of
 a certain type
 */
template<class TYPE>
void readFile(ArrayList<TYPE> &item, string fileName)
{
    //Create the ifstream
    ifstream inFile;
    
    //Open it
    inFile.open(fileName);
    
    //If it fails, then don't open
    if (inFile.fail())
    {
        cout << "Error Opening file" << endl;
        exit(1);
    }
    
    //Get the line
    TYPE line;
    
    //While there is a number in the line, then append to the array
    while (inFile >> line)
    {
        item.append(line);
    }
    //Close inFile1
    inFile.close();
}

/*
 This is the insertion sort. The order of time is O(n^2) which means that
 it is a bit faster sorting than bubble and selection.
 */
template<class TYPE>
void insertionSort(ArrayList<TYPE> &num, int size)
{
    //Iterate through the size of the array
    for(int i = 0; i < size; i++)
    {
        //Get the elements
        TYPE next = num[i];
        
        //Get the locations
        int location = i;
        
        //While location is greater than zero and the element inside of
        //Location - 1 is greater than next,
        while((location > 0) && (num[location - 1] > next))
        {
            //Copy and shift everything to the right to make room for
            //insertion
            num.swap(location, location - 1);
            //Decrement location to keep shifting
            location--;
        }
        //Set the insertion on the empty element after everything was
        //shifted.
        num[location] = next;
    }
}

/*
 This is the merge sort helper. It splits and sorts.
 divide and conquer strategy
 */
template<class TYPE>
void merge(ArrayList<TYPE> &item, int first, int mid, int last)
{
    //Make a temporary array and copy the size and the max
    ArrayList<TYPE> mergedArray(item.getSize(), item.getMax());
    
    //Subarray indexes. This is the first half.
    int firstHalf = first;
    int firstLast = mid;
    
    //This is the second half.
    int secondHalf = mid + 1;
    int secondLast = last;
    
    //Keeping track where you are in the temp array.
    //Because you are going to be adding items inside
    //of temp.
    int index = firstHalf;
    
    //Check each index of the two halves and compare.
    while ((firstHalf <= firstLast) && (secondHalf <= secondLast))
    {
        //If first half item is less than or equal to
        //second half item.
        if (item[firstHalf] <= item[secondHalf])
        {
            //Put that in the index of temp to merge.
            mergedArray.insertAt(index, item[firstHalf]);
            //Iterate
            firstHalf++;
        }
        else
        {
            //If not, then put the secondHalf element inside
            //of the whole merged array
            mergedArray.insertAt(index, item[secondHalf]);
            //Iterate
            secondHalf++;
        }
        //Increment index of mergedArray
       index++;
    }

    //Compare again to sort it. Maybe it didn't work the first time
    while (firstHalf <= firstLast)
    {
        mergedArray.insertAt(index, item[firstHalf]);
        firstHalf++;
        index++;
    }

    //Same thing
    while (secondHalf <= secondLast)
    {
        mergedArray.insertAt(index, item[secondHalf]);
        secondHalf++;
        index++;
    }

    //Set the temp array to the array being passed in.
    for (index = first; index <= last; index++)
    {
        item[index] = mergedArray[index];
    }
    
    //For some reason, the counters are counting but
    //once it exists this function, all of the counters
    //are not saved.
    //It works for the other sorts, but the merge doesn't
    //do that.
//        cout << "Access: " <<item.numAcc << endl;
//    //     cout << item.getNumSwap() << endl;
//    //   cout << item.getNumRemove() << endl;
//         cout << "Insert: " <<item.numIns << endl;
//    //    cout << item.getNumAppends() << endl;
}


/*
 This is the mergeSort and it will do the sorting.
 It also uses a helper function called merge.
 */
template<class TYPE>
void mergeSort(ArrayList<TYPE> &num, int first, int last)
{
    //If the first index is less than the max
    if(first < last)
    {
        // Get the middle index
        int middle = first + (last - first) / 2;

        //Split the array in half each time
        mergeSort(num, first, middle);
        mergeSort(num, middle + 1, last);

        //Sort them all
        merge(num, first, middle, last);
    }
}

/*
 This is the algorithm for dividing and sorting.
 */
template<class TYPE>
int partition(ArrayList<TYPE> &item, int front,int last)
{
    //Initialize some variables
    //Pivot
    int x= item[front];
    
    //Front
    int i = front;
    int j;

    //From front to the last...
    for(j= front + 1; j < last; j++)
    {
        //If item at j is less than the front
        if(item[j] < x)
        {
            //swap them.
            i = i + 1;
            item.swap(i, j);
        }
    }

    //Swap the front and i.
    item.swap(i, front);
    return i;
}

/*
 This is the quick sort. Much like the mergesort, it is a divide
 and conquer strategy.
 1. It will pick a pivot point, usually the last element in the array
 2. Divides due to that pivot.
 3. Sorts around that pivot
 4. Rinse and repeat.
 */
template<class TYPE>
void quickSort(ArrayList<TYPE> &item, int first, int last)
{
    int divide;
    if(first < last)
    {
        //Divide the array
        divide = partition(item, first, last);
        
        //Keep dividing on both sides
        quickSort(item, first, divide);
        quickSort(item, divide + 1,last);
    }

}

template<class TYPE>
void reportInsertion(ArrayList<TYPE> &item, string fileName)
{
    ArrayList<int> insertion;
    //Insertion
    readFile(insertion, fileName);
    int acc1, swap1, rem1, ins1, app1;

    //Sort it
    insertionSort<int>(insertion, insertion.getSize());
    acc1 = insertion.numAcc;
    swap1 = insertion.numSwap;
    rem1 = insertion.numRem;
    ins1 = insertion.numIns;
    app1 = insertion.numApp;
    
    cout << "Insertion Sort Results: " << endl;
    printOutArray(insertion);
    cout << endl;
    
    //Get the stats
    cout << "Number of: " << setw(10) << "Access"
    << setw(10) << "Swap" << setw(10) << "Remove"
    << setw(10) << "InsertAt" << setw(10) << "Append" << endl;
    //Print out the stats
    cout << "InsertionSort: " << setw(6) << acc1
    << setw(10) << swap1 << setw(10) << rem1
    << setw(10) << ins1 << setw(10) <<
    app1 << endl;
    cout << endl;
    
    //clear
    item.clearStatistics();
    insertion.clearStatistics();
}

template<class TYPE>
void reportMerge(ArrayList<TYPE> &item, string fileName)
{
    //Make a merge array
    ArrayList<int> merge;
    
    readFile(merge, fileName);
    int acc2, swap2, rem2, ins2, app2;
    //Merge
    mergeSort<int>(merge, 0, merge.getSize() - 1);
    cout << "Merge Sort Results: " << endl;
    printOutArray(merge);
    cout << endl;

    //Get stats
    acc2 = merge.getNumAccess();
    swap2 = merge.getNumSwap();
    rem2 = merge.getNumRemove();
    ins2 = merge.getNumInsertAt();
    app2 = merge.getNumAppends();
       
    cout << "Numeber of: " << setw(10) << "Access"
    << setw(10) << "Swap" << setw(10) << "Remove"
    << setw(10) << "InsertAt" << setw(10) << "Append" << endl;
    
    //Print stats
    cout << "MergeSort: " << setw(10) << acc2
    << setw(10) << swap2 << setw(10) << rem2
    << setw(10) << ins2 << setw(10) << app2 << endl;
    cout << endl;
    //clear
    item.clearStatistics();
    merge.clearStatistics();
}

template<class TYPE>
void reportQuick(ArrayList<TYPE> &item, string fileName)
{
    //Make a quick
    ArrayList<int> quick;
    
    readFile(quick, fileName);
    int acc3, swap3, rem3, ins3, app3;
    
    //Sort it
    cout << "Quick Sort Results: " << endl;
    quickSort<int>(quick, 0, quick.getSize());
    printOutArray(quick);
    
    //Print it out
    cout << "Numeber of: " << setw(10) << "Access"
    << setw(10) << "Swap" << setw(10) << "Remove"
    << setw(10) << "InsertAt" << setw(10) << "Append" << endl;
    acc3 = quick.getNumAccess();
    swap3 = quick.getNumSwap();
    rem3 = quick.getNumRemove();
    ins3 = quick.getNumInsertAt();
    app3 = quick.getNumAppends();

    cout << "QuickSort: " << setw(10) << acc3
    << setw(10) << swap3 << setw(10) << rem3
    << setw(10) << ins3 << setw(10) <<
    app3 << endl;
    cout << endl;
    //Clear it
    item.clearStatistics();
    quick.clearStatistics();
}

template<class TYPE>
void report(ArrayList<TYPE> &item, string fileName)
{
    //Read the files
    cout << "FileName: " << fileName << endl;
    cout << "Number of Items: " << item.getSize() << endl;
    cout << endl;
    
    reportInsertion(item, fileName);
    reportMerge(item, fileName);
    reportQuick(item, fileName);
    
}

//int main()
//{
//    ArrayList<int> s;
//    cout << endl;
//    report(s, "dataSmall.txt");
//
//    return 0;
//}

int main(int argc, char* argv[])
{
    ArrayList<int> arr;
    
    if (argc == 1)
    {
        cout << "Please enter text file name" << endl;
        exit(1);
        //printReport1(myArray, dataSmall);
    }
    else if (argc == 2)
    {
        readFile(arr, argv[1]);
        report(arr, argv[1]);
    }
    else if (argc == 3)
    {

        string s;
        stringstream ss;
        ss << argv[1];
        ss >> s;

        if (s == "-d")
        {
            readFile(arr, argv[2]);
            report(arr, argv[2]);
        }
        else
        {
            cout << "Please enter -d and file name for output" << endl;
        }
    }
    return 0;
}

