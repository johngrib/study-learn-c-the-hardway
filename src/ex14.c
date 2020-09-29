#include <stdio.h>
#include <ctype.h>

// 전방 선언
int can_print_it(char ch);
void print_letters(char arg[]);

void print_arguments(int argc, char *argv[])
{
    int i = 0;
    for (i = 0; i < argc; i++) {
        print_letters(argv[i]);
    }
}

void print_letters(char arg[])
{
    int i = 0;
    for (i = 0; arg[i] != '\0'; i++) {
        char ch = arg[i];

        if (can_print_it(ch)) {
            printf("'%c' == %d ", ch, ch);
        }
    }
    printf("\n");
}

int can_print_it(char ch)
{
    return isalpha(ch) || isblank(ch);
}

int main(int argc, char *argv[])
{
    print_arguments(argc, argv);
    return 0;
}

/*
$ ./ex14 a1b2c3 824 "a 3 s 7 d f"
'e' == 101 'x' == 120 
'a' == 97 'b' == 98 'c' == 99 

'a' == 97 ' ' == 32 ' ' == 32 's' == 115 ' ' == 32 ' ' == 32 'd' == 100 ' ' == 32 'f' == 102 
*/

