
#include <stdio.h>
#include <string.h>

int main(){
	FILE* fp;
	fp = fopen("p1.txt","r");
	char s1[10];
	int i=0;
	char *ptr;
	while(1){
		fgets(s1, 10, fp);
		ptr = strchr(s1,' ');
		printf("%s\n",ptr);
		ptr = strchr(ptr+1,' ');
		printf("%s\n",ptr);

		i++;
		if(i>2) break;	
	}
	fclose(fp);
}
	
