/*****************************************************************************
* Original Code:
* Code accompanying the Application Note:
* "Object-Oriented Programming in C"
* https://www.state-machine.com/doc/AN_OOP_in_C.pdf
*
* Contact Information:
* https://www.state-machine.com
*
* Code modified for academic purpose
****************************************************************************/

#include <stdio.h>  /* for printf() */
#include <stdint.h>
#include <stdlib.h>

/***************************************************************************
* Class implementation:
****************************************************************************/
typedef struct Shape Shape;

struct Shape{
    int16_t x; 
    int16_t y; 
};

void Shape_ctor(Shape * const me, int16_t x, int16_t y);
void Shape_dtor(Shape * const me);
void Shape_moveBy(Shape * const me, int16_t dx, int16_t dy);
int16_t Shape_getX(Shape const * const me);
int16_t Shape_getY(Shape const * const me);

//***************************************************************************

    
int main() {
    Shape *s1 = malloc(sizeof(Shape));
    Shape_ctor(s1,0,1);
    Shape *s2 = malloc(sizeof(Shape));
    Shape_ctor(s2,-1,2);

    printf("Shape s1(x=%d,y=%d)\n", Shape_getX(s1), Shape_getY(s1));
    printf("Shape s2(x=%d,y=%d)\n", Shape_getX(s2), Shape_getY(s2));
    
    Shape_moveBy(s1, 2, -4);
    Shape_moveBy(s2, 1, -2);
    
    printf("Shape s1(x=%d,y=%d)\n", Shape_getX(s1), Shape_getY(s1));
    printf("Shape s2(x=%d,y=%d)\n", Shape_getX(s2), Shape_getY(s2));

    Shape_dtor(s1);
    free(s1);

    Shape_dtor(s2);
    free(s2);

    return 0;
}

void Shape_ctor(Shape * const me, int16_t x, int16_t y){
    me->x = x;
    me->y = y;
}

void Shape_dtor(Shape * const me){
}

void Shape_moveBy(Shape * const me, int16_t dx, int16_t dy) {
    me->x += dx;
    me->y += dy;
}

/* "getter" operations implementation */
int16_t Shape_getX(Shape const * const me) {
    return me->x;
}
int16_t Shape_getY(Shape const * const me) {
    return me->y;
}
