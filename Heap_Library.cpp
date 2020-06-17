/***
This library contains basics operations that can be applied on a complete binary-max
heap, along with heap sort algorithm.

Complete Binary Max-Heap Operations:

insert(value), extract_max(), get_max(), shift_down(i), shift_up(i), parent(i),
left_child(i),right_child(i), remove(i), update(i,val)

Application of Binary Max-heap:

In-place sorting a given array of numbers in asymptotically optimal time i.e. O(N*logN)

***/


#include <bits/stdc++.h>
using namespace std;

// 1 based indexing is used to store the heap

// Maximum possible size of heap
const int max_size=100000+7;

// upper bound of int data type
const int positive_infinity=INT_MAX;

// array to store the heap
vector <int> heap(max_size);

// current size of heap
int size_of_heap=0;


// return parent index of a child if it exits
int parent(int i)
{
    // if i is root node, then it has no parent and hence return -1
    // else return i/2 rounded down
    if(i==1)
        return -1;

    return i/2;
}

// returns left child index of a node if it exists
int left_child(int i)
{
    // if i is leaf node then it has no left child hence return -1 else return 2*i


    int l=2*i;

    if(l>size_of_heap)
        return -1;

    return l;
}

// return right child index of a node i if it exists
int right_child(int i)
{
    // if i is leaf node then it has no right child hence return -1
    // else return 2*i+1

    int r=2*i+1;

    if(r>size_of_heap)
        return -1;

    return r;
}

// if the current state of the array violates the property of max heap
// due to presence of some higher priority value at higher depth, then we
// can repeatedly move that node towards root until we achieve the correct
// heap structure
void shift_up(int i)
{
    while(i>1 and heap[parent(i)]<heap[i])
    {
        swap(heap[i],heap[parent(i)]);
        i=parent(i);
    }
}

// if the current state of the array violates the property of max heap
// due to presence of some lower priority value at lower depth, then we
// can repeatedly move that node down until we achieve the correct
// heap structure

// to make choice between left and right child to be used for swapping,
// select that child which has higher priority
void shift_down(int i)
{
    int mxindex=i;
    int l=left_child(i);

    if(l<=size_of_heap and heap[l]>heap[mxindex])
        mxindex=l;

    int r=right_child(i);

    if(r<=size_of_heap and heap[r]>heap[mxindex])
        mxindex=r;

    // if swapping is actually required
    if(i!=mxindex)
    {
        swap(heap[i],heap[mxindex]);

        shift_down(mxindex);
    }
}

// returns max value i.e. root priority
int get_max()
{
    return heap[1];
}


// first we check if our heap is full
// if not then we insert the new node according to the rule of insertion in
// a complete binary tree i.e. insert it as a leaf in the next vacant position
// Then it is possible that the heap structure is disturbed
// So we just shift up that node until we achieve correct state
void insert(int value)
{
    if(size_of_heap==max_size)
    {
        cout<< "No room for a new value!";
        return;
    }

    size_of_heap=size_of_heap+1;
    heap[size_of_heap]=value;

    shift_up(size_of_heap);
}

// here the goal is to check out the root of heap and then pop it off
// so we remove the last node i.e. the last node at last level in the heap
// and place it at the root
// then perform shift down operation to rectify the heap structure
int extract_max()
{
    int result=heap[1];

    heap[1]=heap[size_of_heap];
    size_of_heap=size_of_heap-1;
    shift_down(1);

    return result;
}

// to remove a node at index i, the trick is to set it's value positive infinity
// then shift up so that it moves to the root
// then call extract max and pop it off
int remove(int i)
{
    heap[i]=positive_infinity;
    shift_up(i);

    return extract_max();
}

// if new value of node i is greater then previous value then there is a chance
// that we need to move that node up to obtain correct heap
// in other case we need to shift down the node i
void update(int i,int new_value)
{
    int old_value=heap[i];
    heap[i]=new_value;

    if(old_value<new_value)
        shift_up(i);
    else
        shift_down(i);
}

// 1-based indexing is used for the input array

// we convert an array to heap as following:
// the subtrees of the leaf nodes already satisfy the heap property so
// no need to move them
// the internal nodes however need to be shifted downwards to obtain
// correct heap structure
// since there are at most n/2(rounded-up) nodes so we call shift_down operation
// for nodes indexed from 1 to n/2(rounded-up)
void build_heap(vector <int> &a,int n)
{
    size_of_heap=n;
    for(int i=ceil(n/2.0);i>=1;i--)
        shift_down(i);
}

// first we build complete binary max heap from the array in-place
// now we know that the first element would be maximum value so we swap it with the
// last value in the array
// we repeat above step n-1 times by constructing heap in every iteration using
// shift_down for first value and downsizing the array in each step
void heap_sort(vector <int> &a,int n)
{
    build_heap(a,n);

    int repeat=n-1;

    while(repeat-- >0)
    {
        swap(a[1],a[size_of_heap]);
        size_of_heap=size_of_heap-1;
        shift_down(1);
    }
}

int main()
{

    return 0;
}
