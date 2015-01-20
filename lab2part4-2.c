#include "stdio.h"

//currently incomplete, need more complete understanding of component

void quickSort(unsigned char a[], int l, int r);
int partition(unsigned char a[], int l, int r);

int main()
{

	volatile (int*) sdram_o; //sdram read address
	volatile (int*) sdram_f; //sdram write address
	volatile (int*) arr_size; //array size retrieved
	volatile (int*) start_flag; //start flag retrieved
	volatile (int*) done; //end flag output
	volatile (int*) avg; //avg calculation output

	unsigned char aob[32], low, temp; //unsigned array of bytes. low and temp used for bubble sort
	int arr; //array size
	int start; //start flag
	int i,j; //indexes for sort
	int sum; 

	while(1)
	{
		*(done) = 0;		
		do{
			start = *(start_flag);			
		}(while start == 0);  //poll for start flag
		
		arr = *(arr_size); //get size
		aob = *(sdram_o); // get address of original array

//		quickSort(aob, 0, arr-1);   //quicksorting is an option, may be buggy right now since converted from an int version
		
/*
		for(i = 0; i < arr; i++)  //bubble sort option
		{
			low = aob[i];
			for(j = i+1; j < arr; j++)
			{
				if(aob[j] < low)
				{
					low = aob[j];	
					aob[j] = aob[i];
					aob[i] = low;
				}
			}
		}
		
*/

		*(sdram_f) = aob; //write the new array into sdram

/*
		sum = 0;
		for(i = 0; i < arr; i++)
		{
			sum = aob[i] + sum;
		}
		sum = sum/arr;
		*(avg) = sum; //write into the output
*/

		*(done) = 1; //done flag used by HPS for polling
	}


	return 0;
}

void quickSort(unsigned char a[], int l, int r)
{
	int j;
	if( l < r)
	{
		j = partition(a,l,r);
		quickSort(a,l,j-1);
		quickSort(a,j+1,r);
	}
}

int partition(unsigned char a[], int l, int r)
{
	unsigned char pivot, t;
	int i,j;
	pivot = a[l];
	i = l;
	j = r+1;

	while(1)
	{
		do
		{
			++i;
		}while(a[i] <= pivot && i <= r);
		do
		{
			--j;
		}while(a[j] > pivot);
		if(i >= j) break;
		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}
	t = a[l];
	a[l] = a[j];
	a[j] = t;
	return j;
}
