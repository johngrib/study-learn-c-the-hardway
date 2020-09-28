#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    // argv에 들어있는 문자열들을 사용한다.
    for (i = 1;  i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }

    // 문자열 배열
    char *states[] = {
        "California", "Oregon", "Washington", "Texas"
    };

    int num_states = 4;

    for (i = 0; i < num_states; i++) {
        printf("state %d: %s\n", i, states[i]);
    }
    return 0;
}

/*
$ ./ex13 qwer asdf zxcv
arg 1: qwer
arg 2: asdf
arg 3: zxcv
state 0: California
state 1: Oregon
state 2: Washington
state 3: Texas
*/
