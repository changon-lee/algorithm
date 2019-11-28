

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_SIZE 1024
void Swap(int A[], int i, int j)
{
	int tmp = A[i];
	A[i] = A[j];
	A[j] = tmp;
}

int Partition(int A[], int p, int r){
	int x = A[p];
	int i = p-1;
	int j = r+1;
	while(1){
		while(1){
			j--;
			if(A[j] <= x) break;
		}
		while(1){
			i++;
			if(A[i] >= x) break;
		}
		if( i < j){
			Swap(A, i, j);
		}
		else{
			return j;
		}
	}
}

void Quicksort(int A[], int p, int r){
	if(p < r)
	{
		/*int pivot = rand()%(p-r);
		Swap(A,p,pivot);*/
		int q = Partition(A, p, r);
		Quicksort(A,p,q);
		Quicksort(A,q+1,r);
	}
}

void insertion_sort(int A[], int N )
{
	int i, j;
	int key;
	for (i=1; i<N; i++) {
    		key = A[i];
    	for (j=i-1; j >= 0 && A[j] > key ; j--) A[j+1] = A[j];
    	A[j+1] = key;
  	}
}

int main()
{
	int i,j;
	int arr[ARRAY_SIZE];
	for(i = 0; i < ARRAY_SIZE; i++){
		arr[i] = i;
	}
	
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	Quicksort(arr,0,ARRAY_SIZE-1);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Sort done.\n");
	printf("Time %.5f seconds.\n", cpu_time_used);

	

	return 0;
}


