/*minqueue.h*/

//
// Min queue that stores (key, value) pairs using a min-heap 
// implementation.  When pop is called, the key from the 
// (key, value) pair with the smallest value is returned; if 
// two pairs have the same value, the smaller key is returned.
// Push and pop have O(lgN) time complexity.
//
// << Brian Huang >>
//
// Original author: Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project #07
//

#pragma once

#include <iostream>
#include <vector>
#include <exception>
#include <stdexcept>
#include <map>
using namespace std;


template<typename TKey, typename TValue>
class minqueue
{
private:

	struct NODE
	{
		TKey    Key;
		TValue  Value;
	};
	NODE *queue;
	std::map<TKey, int> min;
	int Capacity;
	int arraysize;
	int getLeftChildIndex(int nodeIndex) {
            return 2 * nodeIndex + 1;
      }
    int getRightChildIndex(int nodeIndex) {
            return 2 * nodeIndex + 2;
      }
    int getParentIndex(int nodeIndex) {
            return (nodeIndex - 1) / 2;
      }

	
public:
  //
  // default constructor:
  //
  // Queue has a max capacity for efficient implementation.
  // This max capacity must be specified at queue creation.
  //
  minqueue(int capacity)
  {
    //
    // TODO:
    //
    queue = new NODE[capacity];
    arraysize = 0;
    Capacity = capacity;
  }
  
  //
  // fill constructor:
  //
  // This allows for the efficient O(N) construction of
  // a queue with an initial set of keys, all with the same
  // initial value.  The max capacity of the queue is 
  // set to the # of keys provided for initialization;
  // it is assumed the keys are in ascending order.
  //
  minqueue(vector<TKey> keys, TValue initialValue)
  {
    //
    // TODO:
    //
    queue = new NODE[keys.size()];
	for(int i = 0; i < keys.size(); i++)
	{
		queue[i].Key = keys[i];
		queue[i].Value = initialValue;
		min.emplace(keys[i],i);
	}
    arraysize = keys.size();
    Capacity = keys.size();
  }
  
  
  //
  // destructor:
  //
  virtual ~minqueue()
  {
    //
    // TODO:
    //
    delete [] queue;
  }
  

  //
  // empty:
  //
  // Returns true if empty, false if not.
  //
  bool empty()
  {
	  if(arraysize ==0)
	  {
		  return true;
	  }
	  else
	  {
		  return false;
	  }
  
  }

  // SiftUp
  ///while heap property is broken. Sifting is done as following:
  //compare node's value with parent's value. If they are in wrong order, swap them.
  
  void siftUp(int nodeIndex) {
      int parentIndex;
      if (nodeIndex != 0) {
            parentIndex = getParentIndex(nodeIndex);
			//compare node's value with parent's value and if they 
			//are in wrong order swap them
            if (queue[parentIndex].Value > queue[nodeIndex].Value) {
                  //swapping values
                  swap(queue[nodeIndex], queue[parentIndex]);
				  //swap indexes in map
				  swap(min[queue[parentIndex].Key], min[queue[nodeIndex].Key]);
                  //siftUp parent
                  siftUp(parentIndex);
            }
			else if(queue[parentIndex].Value == queue[nodeIndex].Value)
			{
				  if (queue[parentIndex].Key > queue[nodeIndex].Key) {
					  //swapping values
					  swap(queue[nodeIndex], queue[parentIndex]);
					  //swap indexes in map
					  swap(min[queue[parentIndex].Key], min[queue[nodeIndex].Key]);
					  //siftUp parent
					  siftUp(parentIndex);
				  }
			}
      }
	}
  //siftDown :
  //if current node has no children, sifting is over;
  //if current node has one child: check, if heap property 
  //is broken, then swap current node's value and child value; sift down the child;
  //if current node has two children: find the smallest of them.
  //If heap property is broken, then swap current node's value 
  //and selected child value; sift down the child.
  void siftDown(int nodeIndex) {
      int leftChildIndex, rightChildIndex, minIndex;
      leftChildIndex = getLeftChildIndex(nodeIndex);
      rightChildIndex = getRightChildIndex(nodeIndex);
	  minIndex = nodeIndex;
      if (rightChildIndex >= arraysize) {//right child doesn't exist
            //no child
            if (leftChildIndex >= arraysize){
                  return;
			}
			//one left child
            else{
                  //minimum index is left child
                  minIndex = leftChildIndex;
			}
      }
	  else {//right child exist
            //two child
            if (queue[leftChildIndex].Value == queue[rightChildIndex].Value){
                  if(queue[leftChildIndex].Key < queue[rightChildIndex].Key)//values the same so compare keys
				  {
					  //minimum index is left child
					  minIndex = leftChildIndex;
				  }
				  else
				  {
					  //minimum index is right child
					  minIndex = rightChildIndex;
				  }
			}
			else if(queue[leftChildIndex].Value < queue[rightChildIndex].Value){
                  //minimum index is left child
                  minIndex = leftChildIndex;
		    }
			//one right child 
            else
			{
				  //minimum index is right child
                  minIndex = rightChildIndex;
			}
      }
	  //compare values if the values are different
      if (queue[nodeIndex].Value > queue[minIndex].Value) {
            //swapping values
			swap(queue[nodeIndex], queue[minIndex]);
			//swap indexes in map
			swap(min[queue[minIndex].Key], min[queue[nodeIndex].Key]);
			//siftDown the child
            siftDown(minIndex);
      }
	  //if values are the same then compare keys
	  else if(queue[nodeIndex].Value == queue[minIndex].Value)
			{
				  if (queue[nodeIndex].Key > queue[minIndex].Key) {
					//swapping values
					swap(queue[nodeIndex], queue[minIndex]);
					//swap indexes in map
					swap(min[queue[minIndex].Key], min[queue[nodeIndex].Key]);
					//siftDown the child
					siftDown(minIndex);
				  }
			}
  }
    
	// deletequeue:
	//
	//find the position of key using map and delete the key and 
	//index from the map then overwrite queue[p] with queue[arraysize-1]
	// and then decrement the arraysize then siftup and siftdown if there
	// the parentIndex of p exist.
	//
  void deletequeue(TKey Key, TValue value)
  {
	  //key not in minqueue
	  if(min.find(Key) == min.end())
	  {
		  return;
	  }
	  //find position of the key in O(1) lookup
	  int p = min[Key];
	  //the key we need to delete is the last pair in the queue
	  if(p == arraysize-1)
	  {
		  arraysize--;
		  return;
	  }
		  //overwrite queue[p] with queue[arraysize-1]
		  queue[p] = queue[arraysize-1];
		  //update the map
		  min.erase(Key);
		  min[queue[p].Key] = p;
		  arraysize--;
		  //siftup and siftdown
		  if(getParentIndex(p) < arraysize && getParentIndex(p) >= 0)
		  {
			  siftUp(p);
			  siftDown(p);
		  }
	  return;
	  
  }
  

// push:
//
// Inserts the given (key, value) pair into the queue such that
// pop always returns the pair with the minimum value. If the
// key is *already* in the queue, it's value is updated to the
// given value and the queue reordered. If the key is not in
// the queue, the (key, value) pairs is added and the queue
// reordered.
//
// NOTE: if two keys have the same value, i.e. (key1, value) and
// (key2, value), then those pairs are ordered into ascending value
// by their key.
//
  void pushinorder(TKey key, TValue value)
  {
    // insert a new (key, value) pair but the queue is full so we throw runtime error
	if(min.find(key) == min.end() && arraysize == Capacity)
	{
      throw runtime_error("minqueue::pushinorder: queue full");
	}
	else if(min.find(key) == min.end())//insert new pair and queue is not full
	{
		arraysize++;
	    //traditional push
	    queue[arraysize-1].Key = key;
	    queue[arraysize-1].Value = value;
		//add new key with new index to the map
		min.emplace(key, arraysize-1);
		siftUp(arraysize-1);
		return;
	}
	else //insert already existing pair and queue can be full
	{
		//find and delete old pair
		deletequeue(key,value);
		arraysize++;
	    //traditional push
	    queue[arraysize-1].Key = key;
	    queue[arraysize-1].Value = value;
		//add new key with new index to the map
		min.emplace(key, arraysize-1);
		//siftup
		siftUp(arraysize-1);
		return;
	}
  }


  //
  // front:
  //
  // Returns the key at the front of the queue; does *not* pop the 
  // (key, value) pair.  Throws a logic_error exception if the queue
  // is empty.
  //
  TKey minfront()
  {
    if (empty())
    {
      throw logic_error("minqueue::minfront: queue empty");
    }
    return queue[0].Key;
  }


  //
  // pop:
  //
  // Pops and discards the (key, value) pair at the front of the queue.
  // Throws a logic_error exception if the queue is empty.
  //

  void minpop()
  {
    if (empty())
    {
      throw logic_error("minqueue::minpop: queue empty");
    }
	//popping the only element in the queue
	if(arraysize-1 == 0)
	{
		//update map
		min.erase(queue[0].Key);
	}
	//popping min element in the queue
	else
	{
		//update map
		min.erase(queue[0].Key);
		//overwrite queue[0] with queue[arraysize-1]
		queue[0] = queue[arraysize-1];
		//update the index of the new key at queue[0] as 0
		min[queue[arraysize-1].Key] = 0;
	}
    arraysize--;
	//siftdown if the queue is not empty
	if(arraysize > 0)
	{
		siftDown(0);
	}
  }

};