#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/** ex17에서 사용한 die 함수. */
void die(const char *message)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    exit(1);
}

// typedef는 가짜 타입을 만드는데, 이 경우에는 함수 포인터에 대한 타입을 만든다.
typedef int (*compare_cb) (int a, int b);

/**
 * 전통적인 버블정렬로, compare_cb를 비교 함수로 사용한다.
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));

    if (!target) {
        die("Memory error.");
    }
    memcpy(target, numbers, count * sizeof(int));

    for (i = 0; i < count; i++) {
        for (j = 0; j < count -1; j++) {
            if (cmp(target[j], target[j + 1]) > 0) {
                temp = target[j + 1];
                target[j + 1] = target[j];
                target[j] = temp;
            }
        }
    }
    return target;
}

int sorted_order(int a, int b)
{
    return a - b;
}

int reverse_order(int a, int b)
{
    return b - a;
}

int strange_order(int a, int b)
{
    if (a == 0 || b == 0) {
        return 0;
    } else {
        return a % b;
    }
}

/**
 * 정렬시킨 다음 출력을 통해 정렬이 제대로 되었는지 확인한다.
 */
void test_sorting(int *numbers, int count, compare_cb cmp)
{
    int i = 0;
    int *sorted = bubble_sort(numbers, count, cmp);

    if (!sorted) {
        die("Failed to sort as requested.");
    }

    for (i = 0; i < count; i++) {
        printf("%d ", sorted[i]);
    }
    printf("\n");
    free(sorted);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        die("USAGE: ex18 4 3 1 5 6");
    }
    int count = argc - 1;
    int i = 0;
    char **inputs = argv + 1;

    int *numbers = malloc(count * sizeof(int));
    if (!numbers) {
        die("Memory error.");
    }
    for (i = 0; i < count; i++) {
        numbers[i] = atoi(inputs[i]);
    }

    test_sorting(numbers, count, sorted_order);
    test_sorting(numbers, count, reverse_order);
    test_sorting(numbers, count, strange_order);

    free(numbers);
    return 0;
}
