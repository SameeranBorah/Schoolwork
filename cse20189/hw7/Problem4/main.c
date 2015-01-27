#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define LINELEGNTH 1024

char *rot13(char *s)
{
    char *cyphertext = (char *)malloc(sizeof(char)*LINELEGNTH);
    int i;
    for(i=0; i<LINELEGNTH; ++i)
        cyphertext[i]=s[i];
    char *p = cyphertext;
    
    char c;
    
    while(*p) {
        c = *p;
        if(c>='A' && c<='M') *p+=13;
        if(c>='N' && c<='Z') *p-=13;
        if(c>='a' && c<='m') *p+=13;
        if(c>='n' && c<='z') *p-=13;
        ++p;
    }
    char * ret = cyphertext; 
    free(cyphertext); 
    return ret;
}

void rot13file(FILE *fp)
{

 	static char line[LINELEGNTH];
	while(fgets(line, LINELEGNTH, fp)>0) 
			printf("%s",rot13(line));


}

int main(int argc, char *argv[])
{
        int n;
        FILE *fp;
 
        if(argc>1) {
                for(n=1; n<argc; ++n) {
                        if(!(fp=fopen(argv[n], "r"))) {
                                fprintf(stderr, "ERROR: Couldn\'t read %s\n", argv[n]);
                                exit(EXIT_FAILURE);
                        }
                        rot13file(fp);
                        fclose(fp);
                }
        }
        else{
            exit(EXIT_FAILURE);
        }
      	
        return EXIT_SUCCESS;
}
