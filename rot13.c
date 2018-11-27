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

void encoder(char *mes);
void decoder(char *mes);
void encoder_chst(char *mes);
void decoder_chst(char *mes);
void readfile(char *filename);
void printhelp();
bool exclude(char c);
int strpos(char c);
// global variables
char * exclusions = "";
char * charset = "entire ascii table";
char * buffer;
int rot = 13;

int main(int argc, char ** argv)
{
    if (argc <= 2) 
    {
        printhelp();
        return 0;
    }
    
    bool encode=true,decode=false,file=false,chst=false;
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
        else if (strcmp(argv[i],"-ex") == 0)
        {
            exclusions = argv[i+1];
        }
        else if (strcmp(argv[i],"-ch") == 0)
        {
            chst = true;
            charset = argv[i+1];
        }
        else if(strcmp(argv[i],"--help") == 0)
        {
            printhelp();
            return 0;
        }        
        else
            continue;
    }

    printf("charset: %s\n", charset);


    //main logic
    if(file)
        readfile(filename);
    else 
        buffer = argv[argc-1];

    if(encode)
        (chst) ? encoder_chst(buffer) : encoder(buffer);
    else if(decode)
        (chst) ? decoder_chst(buffer) : decoder(buffer);
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
        if(exclude(mes[i]))
            continue;
        else 
            mes[i] = (mes[i] + rot) % 127;
    }
}
// decodes global buffer
void decoder(char *mes)
{
    for(int i = 0; i < strlen(mes); i++)
    {
        if(exclude(mes[i]))
            continue;
        else 
            mes[i] = (mes[i] - rot + 127) % 127;
    }
}

// encodes global buffer
void encoder_chst(char *mes)
{
    for(int i = 0; i < strlen(mes); i++)
    {
        if(exclude(mes[i]) || strpos(mes[i]) == -1)
            continue;
        else if (strpos(mes[i]) == -1)
            continue;
        else 
            mes[i] = charset[(strpos(mes[i]) + rot) % strlen(charset)];
        
    }
}

void decoder_chst(char *mes)
{
    for(int i = 0; i < strlen(mes); i++)
    {
        if( exclude(mes[i]) || strpos(mes[i]) == -1)
            continue;
        else 
            mes[i] = charset[
                ( 
                    strpos(mes[i]) - rot + strlen(charset) 
                ) % strlen(charset) ];
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
// returns true if char is in exclusion list
bool exclude(char c)
{
    for(int i = 0; i < strlen(exclusions); i++)
        if(c == exclusions[i])
            return true;
    return false;
}
int strpos(char c)
{
    int i = (int)(strchr(charset, c) - charset);
    return (i > -1 && i < 128) ? i : -1 ;
}

// prints help 
void printhelp()
{    
    printf("\x1B[34m           _   _ _____\n _ __ ___ | |_/ |___ /\n| \'__/ _ \\| __| | |_ \\\n| | | (_) | |_| |___) |\n|_|  \\___/ \\__|_|____/\n");
    printf("\x1B[32mhttps://github.com/CausticKirbyZ/rot13\n\n\n");
    printf("\x1B[37mrot13 (-d | -e) [-o <charoffset>][-ex <exclusion list][-ch <charset>] ( (-f <filename>) | <message> )\n\n"
    "  Usage:\n"
    "--------------------------------------\n\n"
    "  ./rot13 -e message\n"
    "  ./rot13 -e -o 7 -f file1.txt\n"
    "  ./rot13 -d -o 3 -ch abcd -f file2.txt\n"
    "  ./rot13 -e -o 5 -ex , -f file3.csv\n\n\n"    
    

    "  Options:\n"
    "--------------------------------------\n\n"
    "  -d               decode\n"
    "  -e               encode\n"
    "  -o               offset\n"
    "  -f               file input\n"
    "  -ex              exclusion list\n"
    "  -ch              character set, default is entire ascii table\n"
    "  -h, --help       help me\n\n");
}



        