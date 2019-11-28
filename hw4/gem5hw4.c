#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

#define MODE1 0
#define MODE2 1
#define MODE3 2

typedef struct knapsack{
	int *index;  // Lists of path
	int count_index; // how many indexes are in index*?
	double result; // contain knapsack result
}KNAPSACK;

double max(double a, double b){
	if(a>b){
		return a;
	}
	else{
		return b;
	}
}

int find_index(int *arr, int arr_len, int find){
	int i;

	for(i=1;i<arr_len;i+=2){
		if(arr[i] == find){
		       	return ((i/2)+1);
		}
	}

	return 0;	
}
KNAPSACK* solve_knapsack_problem(double arr[], int arr_len){
	int w,i;
	int *index;
	int row = (arr_len/2)-1;
	int column = (int)(arr[arr_len-2]);
	double v[row+1][column+1];
	for(i=0;i<=column;i++){
		v[0][i] = 0;
	}
	for(i=0;i<=row;i++){
		v[i][0] = 0;
	}
	for(i=1;i<=row;i++){
		for(w=1;w<=column;w++){
			if((arr[2*(i-1)])<=(w)){
				v[i][w] = max(v[i-1][w],v[i-1][w-(int)ceil(arr[2*(i-1)])]+arr[2*i-1]);
			}
			else{
				v[i][w] = v[i-1][w];
			}
		}
	}
	double result = v[row][column];
	double res = result;
	int tmp = column;
	int count_index = 0;

	for(i=row;(i>0&&res>0);i--){
		if(res == v[i-1][column]){
			continue;
		}
		else{
			count_index++;
			res = res-arr[2*i-1];
                        column = column - arr[2*(i-1)];
		}
	}
	res = result;
	column = tmp;

	//find path
	index = (int*)calloc(count_index,sizeof(int*));
	row = (arr_len/2)-1;
	count_index = 0;
	for(i=row;(i>0&&res>0);i--){
		if(res == v[i-1][column]){
			continue;
		}
		else{
			index[count_index] = i;
			
			count_index++;
			res = res - arr[2*i-1];
			column = column - arr[2*(i-1)];
			
		}
	}

	KNAPSACK *k = (KNAPSACK*)malloc(sizeof(KNAPSACK*));
	k->index = index;
	k->result = result;
	k->count_index = count_index;

	return k;

}

void free_knapsack(KNAPSACK* k){
	free(k->index);
	free(k);
}

int find_if_int(double a){
	if((int)a-a == 0){
		return TRUE;
	}
	else{
		return FALSE;
	}
}
void print_knapsack(KNAPSACK* k,int tmp, int MODE,int arr_len){
	
	int i;
	
	if(MODE == MODE2 || MODE == MODE1){
		for(i=(k->count_index)-1;i>=0; i--){
			if(tmp == k->index[i] && tmp != 0){
				printf("%dx0.5 ",k->index[i]);
			}
			else{	
			printf("%d ",k->index[i]);}
		}
		if(find_if_int(k->result)){
			printf("%.lf\n",k->result);
		}
		else{
		printf("%.1lf\n",k->result);}
	}
	else if(MODE == MODE3){
		int c = 0;
		for(i=(k->count_index)-1;i>=0;i--){
			if(k->index[i] == arr_len/2 && tmp!= 0){
				continue;}

			if(tmp == k->index[i] && tmp != 0){
				printf("%dx2 ",k->index[i]);
				c++;
			}
			else{
				printf("%d ",k->index[i]);}
		}
		printf("%.lf\n",k->result);
	}

}
void print_knapsack_pb4(KNAPSACK* k_1, KNAPSACK* k_2){
	int tmp;
	int i=k_1->count_index;
	while(1){
		tmp = k_1->index[i-1];
		printf("%d 1 ",tmp);
		i--;
		if(i == 0) break;
	}
	i = k_2->count_index;
	while(1){
		tmp = k_2->index[i-1];
		printf("%d 2 ",tmp);
		i--;
		if(i == 0) break;
	}
	printf("%.lf\n",k_1->result + k_2->result);
}



double* get_input_items(int n){
	double *arr = (double*)malloc(sizeof(double*)*n);
	int i;
	for(i=0;i<n;i++){
		
		scanf("%lf",&arr[i]);
	}
	return arr;

}
double* modulate_array(double* arr,int index){
	int w = 2*index-2;
	int v = 2*index-1;
	arr[w] = arr[w]/2;
	arr[v] = arr[v]/2;
	return arr;
}

double* normalize_array(double* arr,int index){
        int w = 2*index-2;
        int v = 2*index-1;
        arr[w] = arr[w]*2;
        arr[v] = arr[v]*2;
        return arr;
}
double* double_array(double* arr, int index,int arr_len,double knapsack_size){
	arr[arr_len-2] = arr[2*index-2];
	arr[arr_len-1] = arr[2*index-1];
	arr[arr_len] = knapsack_size;
	arr[arr_len+1] = -1;
	return arr;
}
void enlarge_array(int *s, double** ar){
	int newsize= *s+10;
	int i;
	double* temp = (double*)calloc(newsize,sizeof(double*));
	for(i=0;i<*s;i++){
		temp[i]=(*ar)[i];
	}
	free(*ar);
	*ar = temp;
	*s += 10;
}
KNAPSACK* knapsack_initialize(int* index, int count, double result){
	KNAPSACK *k = (KNAPSACK*)malloc(sizeof(KNAPSACK*));
	k->index = index;
	k->count_index = count;
	k->result = result;
	return k;
}
int main(){
	// Find Val(i,w)
	// if(w >= weight[i])
	// -> max(Val(i-1,w), Val(i-1,w-weight[i])+value[i])
	// else
	// -> Val(i-1,w)
	int i,n;
	double *arr;
	char* string = malloc(sizeof(char)*1024);
	string = "../study/algorithm/hw4/p1.txt";
	
	printf("Input file for 1st, 2nd, 3rd Problem : %s",string);
	
	//scanf("%s",string);
	FILE *fp = fopen(string,"r");
	if ( !fp ) {
		fprintf(stderr, "cannot open file %s\n","p1.txt");
		exit(0);
	}
	int SIZE = 10;
	int count=0;
	arr = (double*)calloc(SIZE,sizeof(double*));
	while(1){
		fscanf(fp,"%lf",&arr[count]);
		if(arr[count] == -1) break;
		if(count+1==SIZE){
			enlarge_array(&SIZE,&arr);}
		count++;
	}
	fclose(fp);
	
	//arr = get_input_items(10);
	int arr_len = count+1;
	printf("1st Problem Start\n");	
	KNAPSACK* knapsack;
	// First Problem
	knapsack = solve_knapsack_problem(arr,arr_len);
	print_knapsack(knapsack,0,MODE1,arr_len);	
	printf("1st Problem Done.\n");
	// Second Problem
	printf("2nd Problem starts\n");
	int row = (arr_len/2) -1; 
	double final_result = knapsack->result;
	int* final_index = knapsack->index;
	int final_count = knapsack->count_index;
	int tmp=0;

	for(i=1;i<=row;i++){
		
		arr = modulate_array(arr,i);
		knapsack = solve_knapsack_problem(arr,arr_len);
	//	print_knapsack(knapsack,0);
		if(final_result < knapsack->result){
			final_result = knapsack->result;  
			final_index = knapsack->index;
			final_count = knapsack->count_index;
			tmp = i;
		}
		arr = normalize_array(arr,i);
	}

	KNAPSACK* final_knapsack = knapsack_initialize(final_index,final_count,final_result);
	print_knapsack(final_knapsack,tmp,MODE2,arr_len);
	printf("2nd Problem Done,\n");
	final_result = 0;
	// Third Problem
	printf("3rd Problem Starts\n");
	double* third_array = (double*)malloc(sizeof(double*)*(arr_len+2));
	for(i=0;i<arr_len;i++){
		third_array[i] = arr[i];
	}
	double knapsack_size = arr[arr_len-2];
	for(i=1;i<=row;i++){
		third_array = double_array(arr,i,arr_len,knapsack_size);
		//printf("%.2lf %.2lf\n", third_array[10],third_array[11]);
		knapsack = solve_knapsack_problem(third_array,arr_len+2);
		//print_knapsack(knapsack,0,MODE3,arr_len);
		if(final_result < knapsack->result){
			final_result = knapsack->result;
			final_index = knapsack->index;
			final_count = knapsack->count_index;
			tmp = i;
		}
	}
	KNAPSACK* third_knapsack = knapsack_initialize(final_index,final_count,final_result);
	print_knapsack(third_knapsack,tmp,MODE3,arr_len);
	printf("3rd Problem Done\n");	
	string = "../study/algorithm/hw4/p4.txt";
	printf("Input file for 4th Problem : %s",string);
 	
	//scanf("%s", string);
	
	fp = fopen(string,"r");
        if ( !fp ) {
		fprintf(stderr, "cannot open file %s\n","p4.txt");
	        exit(0);
	}
        count=0;
	free(arr);
        arr = (double*)malloc(sizeof(double*)*(SIZE+1));
	while(1){
		fscanf(fp,"%lf",&arr[count]);
	//	printf("%.2lf ",arr[count]);
		if(arr[count] == -1) break;
		count++;
	}
	fclose(fp);
	printf("4th Problem Start\n");
	knapsack = solve_knapsack_problem(arr,arr_len);
	
	i=0;

	while(1){
		tmp = knapsack->index[i];
		i++;
		arr[2*tmp-2]=0;
		arr[2*tmp-1]=0;
		if(i == knapsack->count_index) break;
	}
	KNAPSACK* knapsack_2 = solve_knapsack_problem(arr,arr_len);
	print_knapsack_pb4(knapsack,knapsack_2);	
	printf("4th Problem Done\n");

	free_knapsack(knapsack);
	free_knapsack(knapsack_2);
	free_knapsack(final_knapsack);
	free_knapsack(third_knapsack);
	free(arr);
//	free(string);
}
