
#include <math.h>
#include <stdio.h>
void get_input(int* n)
{
	int i=0;
	for(i=0;i<10;i++){
	scanf("%d",n);}
}
int main()
{
	//int a = 5;
	//int b = 2;
	//int c[3] = {1,2,3};
	//printf("%lf\n", (double)(a/b));
	//double f = 5.1;
	//printf("%d\n",(int)ceil(f));
	//printf("%d\n",(int)floor(f));
	FILE *fp = fopen("p1.txt","r");
	char buffer[4];
	fscanf(fp,"%s", buffer);
	printf("%s\n",buffer);
	fscanf(fp,"%s",buffer);
	printf("%s\n",buffer);
	double buf;
	fscanf(fp,"%lf",&buf);
	printf("%lf\n",buf);
	//fgets(buffer,sizeof(buffer),fp);
	//printf("%s\n",buffer);
	//fgets(buffer,sizeof(buffer),fp);
	//printf("%s\n",buffer);
	char c[2] = "-1";
	printf("%c\n",c);
	fclose(fp);
}

