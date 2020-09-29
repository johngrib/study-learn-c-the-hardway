#include <stdio.h>  // printf
#include <assert.h> // assert
#include <stdlib.h> // malloc, free
#include <string.h> // strdup

struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight)
{
    struct Person *who = malloc(sizeof(struct Person));
    assert(who != NULL);

    who->name = strdup(name);   // strdup: copy string
    who->age = age;
    who->height = height;
    who->weight = weight;

    return who;
}

void Person_destroy(struct Person *who)
{
    assert(who != NULL);
    free(who->name);    // name을 free하지 않고 who를 free하면 메모리 누수 위험
    free(who);
}

void Person_print(struct Person *who)
{
    printf("Name: %s\n", who->name);
    printf("\tAge: %d\n", who->age);
    printf("\tHeight: %d\n", who->height);
    printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[])
{
    // 두 명에 대한 구조체를 만든다.
    struct Person *joe = Person_create("Joe Alex", 32, 64, 140);
    struct Person *frank = Person_create("Frank Blank", 20, 72, 180);

    // 구조체를 출력하면서 메모리 내 어디에 있는지도 같이 출력한다.
    printf("%s is at memory location %p:\n", joe->name, joe);
    Person_print(joe);

    printf("%s is at memory location %p:\n", frank->name, frank);
    Person_print(frank);

    // 두 명의 나이에 각각 스무 살씩을 더한 다음 다시 출력한다.
    joe->age += 20;
    joe->height -= 2;
    joe->weight += 40;
    Person_print(joe);

    frank->age += 20;
    frank->weight += 20;
    Person_print(frank);

    // 구조체를 제거한다.
    Person_destroy(joe);
    Person_destroy(frank);

    return 0;
}

/*
Joe Alex is at memory location 0x7fc0b7c058e0:
Name: Joe Alex
	Age: 32
	Height: 64
	Weight: 140
Frank Blank is at memory location 0x7fc0b7c05910:
Name: Frank Blank
	Age: 20
	Height: 72
	Weight: 180
Name: Joe Alex
	Age: 52
	Height: 62
	Weight: 180
Name: Frank Blank
	Age: 40
	Height: 72
	Weight: 200
*/
/*
다음 명령으로 간단하게 메모리 누수를 탐지할 수 있다. Person_destroy 함수 호출을 주석처리하고 시험해보자.
$ clang -fsanitize=address -g ex16.c ; ASAN_OPTIONS=detect_leaks=1 ./a.out
*/
