#include <stdio.h>

void print_vowel(char letter, int location)
{
    switch (letter) {
        case 'a':
        case 'A':
            printf("%d: 'A'\n", location);
            break;

        case 'e':
        case 'E':
            printf("%d: 'E'\n", location);
            break;

        case 'i':
        case 'I':
            printf("%d: 'I'\n", location);
            break;

        case 'o':
        case 'O':
            printf("%d: 'O'\n", location);
            break;

        case 'u':
        case 'U':
            printf("%d: 'U'\n", location);
            break;

        case 'y':
        case 'Y':
            printf("%d: 'Y'\n", location);
            break;

        default:
            printf("%d: %c is not a vowel\n", location, letter);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("ERROR: You need one argument.\n");
        return 1;
    }

    int i = 0;
    for (i = 0; argv[1][i] != '\0'; i++) {
        char letter = argv[1][i];
        print_vowel(letter, i);
    }
    return 0;
}
