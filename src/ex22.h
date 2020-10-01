#ifndef _ex22_h
#define _ex22_h

// ex22.c 에 있는 THE_SIZE를 다른 .c 파일에서도 사용 가능하게 한다.
extern int THE_SIZE;

// ex22 의 내부 static 변수를 가져오거나 설정한다.
int get_age();
void set_age(int age);

// update_ratio 내에 있는 static 변수 값을 업데이트한다.
double update_ratio(double ratio);

void print_size();

#endif

