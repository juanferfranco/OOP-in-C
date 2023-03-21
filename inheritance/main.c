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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*****************************************************
* Class Shape
******************************************************/
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


/*****************************************************
* Class Rectangle
******************************************************/
typedef struct Rectangle Rectangle;

struct Rectangle {
    Shape super;
    uint16_t width;
    uint16_t height;
};

void Rectangle_ctor(Rectangle * const me, int16_t x, int16_t y, uint16_t width, uint16_t height);
void Rectangle_dtor(Rectangle * const me);


int main() {

    Rectangle *r1 = malloc(sizeof(Rectangle));
    Rectangle_ctor(r1, 0, 2, 10, 15);
    
    Rectangle *r2 = malloc(sizeof(Rectangle));   
    Rectangle_ctor(r2, -1, 3, 5, 8);

    printf("Rect r1(x=%d,y=%d,width=%d,height=%d)\n",
            Shape_getX((Shape *)r1), Shape_getY((Shape *)r1), 
            r1->width, r1->height);

    printf("Rect r2(x=%d,y=%d,width=%d,height=%d)\n", 
            Shape_getX((Shape *)r2), Shape_getY((Shape *)r2), 
            r2->width, r2->height);

    Shape_moveBy((Shape *)r1, -2, 3);
    Shape_moveBy((Shape *)r2, 2, -1);

    printf("Rect r1(x=%d,y=%d,width=%d,height=%d)\n", 
            Shape_getX((Shape *)r1), Shape_getY((Shape *)r1), 
            r1->width, r1->height);
        
    printf("Rect r2(x=%d,y=%d,width=%d,height=%d)\n", 
            Shape_getX((Shape *)r2), Shape_getY((Shape *)r2), 
            r2->width, r2->height);

    Rectangle_dtor(r1);
    free(r1);

    Rectangle_dtor(r2);
    free(r2);
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

int16_t Shape_getX(Shape const * const me) {
    return me->x;
}

int16_t Shape_getY(Shape const * const me) {
    return me->y;
}


void Rectangle_ctor(Rectangle * const me, int16_t x, int16_t y,uint16_t width, uint16_t height)
{
    Shape_ctor(&me->super, x, y);
    me->width = width;
    me->height = height;
}

void Rectangle_dtor(Rectangle * const me)
{
}