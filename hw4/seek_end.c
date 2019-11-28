
#include <stdio.h>
//#include "common.h"
//
int get_file_length(FILE* fp,char *string){
        char s1[1024];
        fp = fopen(string,"r");
        if(!fp){
                fprintf(stderr, "file open failed.\n");
                //exit(0);
        }
        
        int count = 0;
        while(1){
            fgets(s1,1024,fp);
            if(feof(fp)) break;
            count++;
        }
        return count;
}

void main(void)
{
	FILE *fp;
	char s1[1024];
	fp = fopen("p1.txt","r");
	int count = 0;
	
	count = get_file_length(fp,"p1.txt");

	printf("File length:%d\n",count);
	fclose(fp);
}
