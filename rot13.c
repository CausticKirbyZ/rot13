// rot13 string encoder/decoder tool 
// github repo: // rot13 string encoder/decoder tool 
// written by Mike Hedlund 11/12/2018
// github repo: https://github.com/CausticKirbyZ/rot13

//            _   _ _____ 
//  _ __ ___ | |_/ |___ / 
// | '__/ _ \| __| | |_ \ 
// | | | (_) | |_| |___) |
// |_|  \___/ \__|_|____/ 


#include <stdio.h>
#include <string.h>

#define maxchar 10000

void decode(char * mes);
void encode(char * mes);

char buff[maxchar];

int main(int argc, char ** argv)
{
    if(strcmp(argv[1],"-d") == 0)
        // decode(argv[2])
        decode(argv[2]);
    else if(strcmp(argv[1], "-e") == 0)
        // encdoe(argv[2])
        encode(argv[2]);
    else if(strcmp(argv[1],"--help") == 0)
        {
            printf("           _   _ _____\n _ __ ___ | |_/ |___ / \n| \'__/ _ \\| __| | |_ \\ \n| | | (_) | |_| |___) |\n|_|  \\___/ \\__|_|____/                       \n\n");
            printf("rot13 [option] filename \noptions: \n  -d          decode\n  -e          encode\n  --help      help me\n\n");
        }
    else
        printf("wrong syntax\n");

    return 0;
}

void encode(char *filename)
{
    FILE *f;
    f = fopen(filename,"r");
    while(fgets(buff,maxchar,f) != NULL)
    {    
        for(int i = 0; i < strlen(buff); i++)
            if(buff[i] == 10)
                continue;
            else if(buff[i] + 13 >126)
                buff[i] = buff[i] + 13 - 94;
            else
                buff[i] = buff[i] + 13;        
        printf("%s",buff);
    }
    fclose(f);
    return;
}

void decode(char *filename)
{
    FILE *f;
    f = fopen(filename,"r");
    while(fgets(buff,maxchar,f) != NULL)
    {    
        for(int i = 0; i < strlen(buff); i++)
            if(buff[i] == 10)
                continue;
            else if(buff[i] - 13 < 32)
                buff[i] = buff[i] - 13 + 94;
            else
                buff[i] = buff[i] - 13;        
        printf("%s",buff);
    }
    fclose(f);
    return;
}

