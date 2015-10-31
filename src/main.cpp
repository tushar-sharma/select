#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cstring>
#include "insertionSort.h"
using namespace std; 
/*
 * Author : Tushar Sharma 
 * Last Modified : Oct 30, 2015 
 *
 */ 

int COMPARECOUNT = 0; 


int printArray(vector<int> unsortedArray,int start, int size, string message, fstream& fp) 
{
	int run_once = 1;
    if (fp.is_open()) {
		if (run_once-- == 1) 
			fp<<message<<endl;
        for (int i = start; i < (start + size); i++) {
	    if (i == 0) 
	        fp<<unsortedArray[i];
	    else fp<<","<<unsortedArray[i];
	}
    }
    fp<<endl;
    return 0;
}

int readAllNumbers(vector<int>& unsortedArray, char *filename)
{
    fstream fp;
    int number;
    fp.open(filename, ios::in | ios::binary);

    if(fp.is_open()){ 
        while (fp >> number) {
        unsortedArray.push_back(number); 
        fp.get();
    }
    }
    fp.close();
    return 0;
}


int instructions() {
    cout<<"Error! Usage: ./src/main rt\n";    
    exit(-1);
}


int select1(vector<int>& arr, int n, int k)
{
	if (k <= n) return arr[k - 1]; 

    else return(-1);
}


int count = 0; 
int quicksort(vector<int>& arr, int left, int right)
{
    if (left >= right) return 0;

    //int size = (right - left + 1);

    //int start = left;

    //cout<<"\n***************BEG***************************\n";

    //array[lowerIndex+(higherIndex-lowerIndex)/2];
    srand((unsigned)time(0));
    int range = (right -left);
    int index = left + int((range * rand()) / (RAND_MAX + 1.0));

    if (count == 0) index = 5;
    count++;

    int pivot = arr[index];
    //cout<<"pivot is "<<pivot<<" index is "<<index<<" size is "<<size<<endl;
    //printArray(arr, start, size);

    /*int pivot = 57; //asume 
    int index = 0; //assume
    */

    //swap 
    int temp = arr[index];
    arr[index] = arr[left];
    arr[left] = temp;

    int l = left + 1;
    int r = right;

    //cout<<"\nl r = "<<l<<" "<<r<<endl;

   while (l <= r) {
        //keep on moving right unless we find anything greater than pivot
        while (l <= r && arr[l] <= pivot) { l++; COMPARECOUNT++;}
        //TODO remove
        //cout<<"\nl = "<<l;

        //keep on moving right unless we find anything greater than pivot
        while (l <= r && arr[r] >= pivot) {r--; COMPARECOUNT++;}

        //TODO remove
        //cout<<" r = "<<r<<endl;

        if (l < r) {
            temp = arr[l];
            arr[l] = arr[r];
            arr[r] = temp;
            l++;
            r--;
        }
    }

    ///cout<<"\nl r = "<<l<<" "<<r<<endl;
    //swap the pivot with the rightmost of the left partition
    temp = arr[left];  //arr[l]
    arr[left] = arr[r];  //arr[right] is pivot
    arr[r] = temp;

    //printArray(arr, left,  size);
    //cout<<"\n***************END***************************\n";
    quicksort(arr, left, r - 1); // r-1
    quicksort(arr, r + 1, right);  // r+1
    return 0;
}



int main(int argc, char **argv) {
 
    
    // check if it has atleast 3 argument
    if (argc < 4) {
        instructions();
    }

    clock_t time_start; //, time_stop; 
 
    time_start = clock(); 
    vector<int> unsortedArray; 

    fstream fp;
    fp.open("outs/output.txt" , ios::out | ios::binary);

    //argv[1] is filename passed as input
    // read and store values from the text file
    readAllNumbers(unsortedArray, argv[1]);
	printArray(unsortedArray, 0, unsortedArray.size(), "Unsorted Array is", fp);

    int left = 0, right = unsortedArray.size() -1;
    //argv[2] has the type. eg q for quicksort, m for merge sort

	int k = atoi(argv[3]), ksmall;
    if (strcmp(argv[2], "1") == 0){
        quicksort(unsortedArray, left, right);
	   	ksmall = select1(unsortedArray, unsortedArray.size(), k);
	}
	else if (strcmp(argv[2], "2") == 0) {
		//if the size of the array < 25 
		//sort the array using insertion sort 
		if(unsortedArray.size() < 25) {
			insertionSort(unsortedArray);
     		ksmall = select1(unsortedArray, unsortedArray.size(),k);
		}
	}

    else instructions();

    cout<<"\nPlease see outs/output.txt for the answer.\n";
    printArray(unsortedArray, 0, unsortedArray.size(), "Sorted Array is", fp); 

    cout<<"\nThe total key comparison were "<<COMPARECOUNT<<endl;

    double duration = ( clock() - time_start ) / (double) CLOCKS_PER_SEC;
    cout<<"\nThis program took "<<duration<<" seconds to execute. Thank you for running.\n"<<endl;

	if (ksmall != -1)
	    fp<<"The "<<k<<"th smallest element in array is "<<ksmall<<endl;
	else 
		fp<<k<<"th smallest is not found in the array"<<endl;

	fp.close();
    return 0;
}
