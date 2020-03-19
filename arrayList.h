/*
 Assignment 5
 arraylist.h
 
 This is the array.h file. Everything is implemented here because it is
 a template class. ArrayList is derived from the ListInterface class and
 implements those methods as well as some other methods that are needed
 for this.
 
 author: sunghopark
 */

#ifndef arrayList_h
#define arrayList_h

#include "listInterface.h"
#include <stdio.h>
#include <iostream>

template<class TYPE>
class ArrayList : public ListInterface<TYPE>
{
public:
    //Make the static variables for counting.
    static int numApp;
    static int numIns;
    static int numRem;
    static int numSwap;
    static int numAcc;
    
    //Constructor
    ArrayList();
    ArrayList(int size);
    ArrayList(const ArrayList<TYPE> &other);
    ArrayList(int c, int m);
    
    ~ArrayList();

    // The easy way to access an element
    TYPE &operator[](int index) const throw (std::out_of_range);
    
    TYPE &operator=(const TYPE &other);

    // Tell of it is empty
    bool isEmpty() const;

    // Return the number of elements in the list
    int getSize() const;

    // Inserts at the location.
    void insertAt(int index, const TYPE &newEntry)
    throw (std::out_of_range);
    
    // delete at location
    void removeAt (int index) throw (std::out_of_range);

    // Append to end
    void append(const TYPE &newEntry);

    void swap(int from, int to) throw(std::out_of_range);

    // Get an item at location
    TYPE& getAt(int index) const throw (std::out_of_range);
    
    // Clear everything
    void clearAll();

    // Clear out any instrumentation
    void clearStatistics();
       
    // Provide statistics on number of times method was performed
    int getNumAccess() const;  // operator [] OR getAt
    int getNumSwap() const;
    int getNumRemove() const;
    int getNumInsertAt() const;
    int getNumAppends() const;
    int getMax() const;
    
    void resize();
    
private:
    static const int DEFAULT = 100;
    int count;
    int max;
    TYPE *item = nullptr;
};


template<class TYPE>
ArrayList<TYPE>::ArrayList()
{
    //Make a default array with max and count initiatied.
    max = DEFAULT;
    item = new TYPE[max];
    count = 0;
}

template<class TYPE>
ArrayList<TYPE>::ArrayList(int size)
{
    //Make max the size.
    max = size;
    count = 0;
    item = new TYPE[size];
}

template<class TYPE>
ArrayList<TYPE>::ArrayList(const ArrayList<TYPE> &other)
{
    //Set the objects in this class to other
    *this = other;
}

template<class TYPE>
ArrayList<TYPE>::ArrayList(int c, int m)
{
    count = c;
    max = m;
    item = new TYPE[max];

}

template<class TYPE>
ArrayList<TYPE>::~ArrayList()
{
    //Clear everything and delete the item.
    //clearAll();
    clearStatistics();
    for(int i = 0; i < max; i++)
    {
        item = nullptr;
        delete [] item;
    }
    clearAll();
    
}

template<class TYPE>
bool ArrayList<TYPE>::isEmpty() const
{
    //If the count, which is the number of entries in the array,
    //is 0, then it is empty.
    if(count == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class TYPE>
int ArrayList<TYPE>::getSize() const
{
    //Return what is inside of the array
    return count;
}

template<class TYPE>
void ArrayList<TYPE>::resize()
{
    //Create a temporary array and update the max.
    int sizeOfTemp = max * 2;
    TYPE *temp = new TYPE[sizeOfTemp];
    
    //Copy over the elements in item to temp
    for(int i = 0; i < count; i++)
    {
        temp[i] = item[i];
    }
    //Delete the item array and return the temp with the new
    //size.
    delete [] item;
    item = temp;
    temp = nullptr;
    max = sizeOfTemp;
}

template<class TYPE>
void ArrayList<TYPE>::insertAt(int index, const TYPE &newEntry)
                                        throw (std::out_of_range)
{
    //If it is negatively out of bounds, then throw exception
    if(index < 0 || index > max)
    {
        throw(std::out_of_range("Out of Range!"));
    }
    else
    {
        
        //An ArrayList Resizes so if an index is out of bounds,
        //Resize it.
        if(count >= max)
        {
            //Resize until count is greater than the maximum
            //passed in.
            resize();
        }
        //Update count and resize it +1 because when you insert,
        //you shift the values after the index until the count,
        //then add the newEntry.
        if((index >= 0) && (index <= count + 1) && (count < max))
        {
            //Update count because it is gonna be added anyways.
            
            count++;
            //Start from count and decrease as you get closer to index
            for(int i = count; i >= index; i--)
            {
                //Set the element inside of item[i] to item[i + 1]
                //to shift everything to the right
                item[i + 1] = item[i];
            }
            //Add the entry to the index
            item[index] = newEntry;
        }
    }
    numIns++;
}

template<class TYPE>
void ArrayList<TYPE>::append(const TYPE &newEntry)
{
    //If the items inside of the array equals the max, then resize
    if(count >= max)
    {
        resize();
        item[count] = newEntry;
        count++;
    }
    else
    {
        //Increment count to get add it to the end of the list.
        if(count < max)
        {
            item[count] = newEntry;
            count++;
        }
        
    }
    numApp++;
}

template<class TYPE>
TYPE& ArrayList<TYPE>::operator[](int index) const
                                        throw (std::out_of_range)
{
    //Return the [].
    if(index < count && index >= 0)
    {
        numAcc++;
        //std::cout << numAcc << std::endl;
        return item[index];
    }
    else
    {
        throw(std::out_of_range("Out of Bounds"));
    }
}

template<class TYPE>
TYPE& ArrayList<TYPE>::operator=(const TYPE &other)
{
    //If they are equal to another, then return this
    if(this == &other)
    {
        return *this;
    }
    
    //Delete this
    delete [] this->item;
    
    //Copy everything in
    this->max = other.max;
    this->count = other.count;
    
    //Make a new Item array
    this->item = new TYPE[this->max];
    
    //Copy everything in
    for(int i = 0; i < max; i++)
    {
        item[i] = other[i];
    }
    //return this.
    return *this;
}

template<class TYPE>
void ArrayList<TYPE>::removeAt(int index)
                                    throw (std::out_of_range)
{
    if(index > count || index < 0)
    {
        throw(std::out_of_range("Out of Bounds"));
    }
    else
    {
        //Shift everything to the left
        for(int i = index; i < count - 1; i++)
        {
            item[i] = item[i + 1];
        }
        count--;
    }
    numRem++;
}

template<class TYPE>
void ArrayList<TYPE>::swap(int from, int to)
                                    throw(std::out_of_range)
{
    if((from >= count || from < 0) || (to >= count || to < 0))
    {
        throw(std::out_of_range("Out of Bounds"));
    }
    else
    {
        //Create a temporary variable with a TYPE
        TYPE temp = item[from];
        
        //Store it in temp and swap the variables
        item[from] = item[to];
        item[to] = temp;
        numSwap++;
        //std::cout << numSwap << std::endl;
    }
}

template<class TYPE>
TYPE& ArrayList<TYPE>::getAt(int index) const
                                    throw (std::out_of_range)
{
    if(index >= 0 && index < count)
    {
        //Get the index of the item.
        numAcc++;
        //std::cout << numAcc << std::endl;
        return item[index];
    }
    else
    {
        throw(std::out_of_range("Out of Bounds"));
    }
}

template<class TYPE>
void ArrayList<TYPE>::clearAll()
{
    //Clears all the items in the array list
    //by setting the count to zero.
    count = 0;
}

template<class TYPE>
void ArrayList<TYPE>::clearStatistics()
{
    //Clears the method counts.
    numApp = 0;
    numIns = 0;
    numRem = 0;
    numSwap = 0;
    numAcc = 0;
}

template<class TYPE>
int ArrayList<TYPE>::getNumAccess() const
{
    return numAcc;
}

template<class TYPE>
int ArrayList<TYPE>::getNumSwap() const
{
    return numSwap;
}

template<class TYPE>
int ArrayList<TYPE>::getNumRemove() const
{
    return numRem;
}

template<class TYPE>
int ArrayList<TYPE>::getNumInsertAt() const
{
    return numIns;
}

template<class TYPE>
int ArrayList<TYPE>::getNumAppends() const
{
    return numApp;
}

template<class TYPE>
int ArrayList<TYPE>::getMax() const
{
    return max;
}

//Initialize the static variables.
template<class TYPE>
int ArrayList<TYPE>::numApp = 0;
template<class TYPE>
int ArrayList<TYPE>::numIns = 0;
template<class TYPE>
int ArrayList<TYPE>::numSwap = 0;
template<class TYPE>
int ArrayList<TYPE>::numRem = 0;
template<class TYPE>
int ArrayList<TYPE>::numAcc = 0;

#endif /* arraylist_h */
