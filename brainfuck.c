#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define VALID_COUNT 8

int strcopyvalid(char *dest, char *source);
int isvalid(char);
int jmp(int, char*);

int DEBUG = 0;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stdout, "Usage: %s [-d] <program>", __FILE__);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "-d") == 0)
    {
        DEBUG = 1;
        argv[1] = argv[2];
    }

    char c;
    int len = 0;
    for (; (c = argv[1][len]) != '\0'; len++) {}

    char program[len];
    int plength = strcopyvalid(program, argv[1]);
    printf("Program length: %d\n", plength);
    printf("Program:\n");
    for (int i = 0; i < plength; i++)
    {
        printf("%c", program[i]);
    }
    putchar('\n');
    
    int tape[30000];
    int head = 0;
    for (int i = 0; i < plength; i++)
    {
        char c = program[i]; 
        if (DEBUG)
        {
            printf("Current HEAD: %d\nCurrent value at: %d\nCurrent program counter: %i\nEncountered: %c\n------\n", head, tape[head], i, c);
        }
            
        switch (c)
        {
            case '+':
                tape[head]++;
                break;
            case '-':
                tape[head]--;
                break;
            case '>':
                head++;
                break;
            case '<':
                head--;
                break;
            case '[':
                if (tape[head] == 0)
                {
                    i = jmp(i, program);
                }
                break;
            case ']':
                if (tape[head] != 0)
                {
                    i = jmp(i, program);
                }
                break;
            case '.':
                putchar(tape[head]);
                if (DEBUG)
                {
                    putchar('\n');
                }
                fflush(stdout);
                break;
            case ',':
                tape[head] = getchar();
        }
    }

    exit(EXIT_SUCCESS);
}

char valid[VALID_COUNT] = {'+', '-', '<', '>', '[', ']', '.', ','};
int strcopyvalid(char *dest, char *source)
{
    int pos = 0;
    char c;
    for (int i = 0; (c = source[i]) != '\0'; i++)
    {
        if (isvalid(c))
        {
            if (DEBUG)
            {
                printf("Determined %c is valid char.\n", c);
            }
            dest[pos++] = c;
        }
    }
    return pos;
}

int isvalid(char c)
{
    for (int i = 0; i < VALID_COUNT; i++)
    {
        if (valid[i] == c)
        {
            return 1;
        }
    }
    return 0;
}

int jmp(int i, char pr[])
{
    int forwardmode = pr[i] == '[' ? 1 : 0;

    if (forwardmode)
    {
        i++;
        int braces = 1;
        while (braces > 0)
        {
            if (pr[i] == '[')
            {
                braces++;
            }
            else if (pr[i] == ']')
            {
                braces--;
            }
            i++;
        }
        return i--;
    }
    else
    {
        i--;
        int braces = 1;
        while (braces > 0)
        {
            if (pr[i] == '[')
            {
                braces--;
            }
            else if (pr[i] == ']')
            {
                braces++;
            }
            i--;
        }
        return i++;
    }
}
