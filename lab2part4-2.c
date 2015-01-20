#include "stdio.h"


void quickSort(unsigned char a[], int l, int r);
int partition(unsigned char a[], int l, int r);

int main()
{

	volatile (int*) sdram_o;
	volatile (int*) sdram_f;
	volatile (int*) arr_size;
	volatile (int*) start_flag;
	volatile (int*) done;
	volatile (int*) avg;

	unsigned char aob[32], low, temp;
	int arr;
	int start;
	int i,j;
	int sum;

	while(1)
	{
		*(done) = 0;		
		do{
			start = *(start_flag);			
		}(while start == 0);
		
		arr = *(arr_size);
		aob = *(sdram_o);

//		quickSort(aob, 0, arr-1);
		
/*
		for(i = 0; i < arr; i++)
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

		*(sdram_f) = aob;

/*
		sum = 0;
		for(i = 0; i < arr; i++)
		{
			sum = aob[i] + sum;
		}
		sum = sum/arr;
		*(avg) = sum;
*/

		*(done) = 1;


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
