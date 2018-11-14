// rot13 string encoder/decoder tool 
// written by Mike Hedlund 11/12/2018
// last updated 11/13/2018
// github repo: https://github.com/CausticKirbyZ/rot13

//            _   _ _____ 
//  _ __ ___ | |_/ |___ / 
// | '__/ _ \| __| | |_ \ 
// | | | (_) | |_| |___) |
// |_|  \___/ \__|_|____/ 



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
enum { false, true };

void decoder(char *mes);
void encoder(char *mes);
void readfile(char *filename);
void printhelp();
// global variables
char * buffer;
int rot = 13;

int main(int argc, char ** argv)
{    
    if (argc <= 2) {
        printhelp();
        return 0;
    }
    
    bool encode=true,decode=false,file=false;
    char *filename;
    for(int i=0; i < argc; i++)
    {
        if (strcmp(argv[i],"-o") == 0)
            rot = atoi(argv[i+1]); 
        else if(strcmp(argv[i],"-e") == 0)
        {
            encode = true;
            decode = false;
            continue; 
        }
        else if (strcmp(argv[i],"-d") == 0)
        {
            decode = true;
            encode = false;
            continue;
        }
        else if (strcmp(argv[i],"-f") == 0)
        {
            filename = argv[i+1];
            file = true;
        }
        else if(strcmp(argv[i],"--help") == 0)
        {
            printhelp();
            return 0;
        }        
        else
            continue;        
    }

    //main logic
    if(file)
        readfile(filename);
    else 
        buffer = argv[argc-1];

    if(encode)
        encoder(buffer);
    else if(decode)
        decoder(buffer);
    else
        printf("wrong input");

    printf("%s\n",buffer);

    return 0;
}
// encodes global buffer
void encoder(char *mes)
{
    for(int i = 0; i < strlen(mes); i++)
    {
        if(mes[i] == 10)
            continue; 
        else if(mes[i] + rot > 126)
            mes[i] = mes[i] + rot - 94;
        else 
            mes[i] = mes[i] + rot;
    }
}
// decodes global buffer
void decoder(char *mes)
{
    for(int i = 0; i < strlen(mes); i++)
    {
        if(mes[i] == 10)
            continue; 
        else if(mes[i] - rot < 32)
            mes[i] = mes[i] - rot + 94;
        else 
            mes[i] = mes[i] - rot;
    }
}

// reads contents of file into global buffer variable
void readfile(char *filename)
{
    long length;
    FILE *f = fopen(filename, "r");

    if(f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);

        if(buffer)
        {
            fread(buffer, 1, length, f);
        }
        fclose (f);
    }
}

// prints help 
void printhelp()
{
    printf("\x1B[32mhttps://github.com/CausticKirbyZ/rot13\n");
    printf("\x1B[34m           _   _ _____\n _ __ ___ | |_/ |___ /\n| \'__/ _ \\| __| | |_ \\\n| | | (_) | |_| |___) |\n|_|  \\___/ \\__|_|____/\n\n\n");
    printf("\x1B[37mrot13 [-d|-e] [-o] <charoffset> [-f] <filename> \n\n  options:\n ------------------- \n\n  -d          decode\n  -e          encode\n  -o          offset\n  -f          file input\n  --help      help me\n\n");
}