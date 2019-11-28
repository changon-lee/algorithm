#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(){
	FILE* fp;
	char *string = (char*)malloc(sizeof(char*)*1024);
	scanf("%s",string);
	fp = fopen(string,"r");
	double a,b,c,d;
	if(fp){
		//double a,b,c,d;
		fscanf(fp,"%lf",&a);
		fscanf(fp,"%lf",&b);
		fscanf(fp,"%lf",&c);
		fscanf(fp,"%lf",&d);
	}
	fclose(fp);
	printf("%lf %lf %lf %lf",a,b,c,d);
	free(string);
}


