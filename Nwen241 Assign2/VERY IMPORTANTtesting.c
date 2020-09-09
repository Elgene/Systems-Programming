#include <stdio.h>
struct rect {
float width;
float length;
} name;
typedef struct rect rect_t;
int main(void){
    rect_t *p;
    *p = (rect_t*) malloc(sizeof(rect_t)*10); 
   
}
//////part 1 chalenge question/////VERY IMPORTANT
#include <stdio.h>
#include <stdlib.h>

int main(void){
    short a[] = {1, 2, 4, 8, 16, 32}; short *pa = a; short **ppa = &pa;
    printf("&a value %d\n",&a);
    printf("&pa value %d\n",&pa);
    printf("&ppa value %d\n",&ppa);
    
    printf("ppa value %d\n",ppa );
    printf("*ppa value %d\n",*ppa);
    printf("*ppa+2 value %d\n",*ppa+2);
   
   
}
