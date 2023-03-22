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
#include <assert.h>

/*****************************************************
* Class Shape
******************************************************/
typedef struct IShapeOperations IShapeOperations;
typedef struct Shape Shape;

struct IShapeOperations {
    uint32_t (*area)(Shape const * const me);
    void (*draw)(Shape const * const me);
};

struct Shape{
    IShapeOperations const *vptr;
    int16_t x; 
    int16_t y; 
};


void Shape_ctor(Shape * const me, int16_t x, int16_t y);
void Shape_dtor(Shape * const me);
void Shape_moveBy(Shape * const me, int16_t dx, int16_t dy);
int16_t Shape_getX(Shape const * const me);
int16_t Shape_getY(Shape const * const me);
uint32_t Shape_area(Shape const * const me);
void Shape_draw(Shape const * const me);

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
uint32_t Rectangle_area(Shape const * const me);
void Rectangle_draw(Shape const * const me);


/*****************************************************
* Class Circle
******************************************************/
typedef struct Circle Circle;

struct Circle {
    Shape super;
    uint16_t rad;
};

void Circle_ctor(Circle * const me, int16_t x, int16_t y, uint16_t rad);
void Circle_dtor(Circle * const me);
uint32_t Circle_area(Shape const * const me);
void Circle_draw(Shape const * const me);


Shape const *largestShape(Shape const *shapes[], uint32_t nShapes);
void drawAllShapes(Shape const *shapes[], uint32_t nShapes);


int main() {

    Rectangle *r1 = malloc(sizeof(Rectangle));
    Rectangle_ctor(r1, 0, 2, 10, 15);

    Rectangle *r2 = malloc(sizeof(Rectangle));
    Rectangle_ctor(r2, -1, 3, 5, 8);

    Circle *c1 = malloc(sizeof(Circle));
    Circle_ctor(c1, 1, -2, 12);

    Circle *c2 = malloc(sizeof(Circle));
    Circle_ctor(c2, 1, -3, 6);

    Shape const *shapes[] = { 
        (Shape *)c1,
        (Shape *)r2,
        (Shape *)c2,
        (Shape *)r1
    };

    Shape const *s;

    s = largestShape(shapes, sizeof(shapes)/sizeof(shapes[0]));
    printf("largestShape s(x=%d,y=%d)\n",
           Shape_getX(s), Shape_getY(s));

    drawAllShapes(shapes, sizeof(shapes)/sizeof(shapes[0]));

    Rectangle_dtor(r1);
    free(r1);
    Rectangle_dtor(r2);
    free(r2);
    Circle_dtor(c1);
    free(c1);
    Circle_dtor(c2);
    free(c2);

    return 0;
}


void Shape_ctor(Shape * const me, int16_t x, int16_t y){
    static IShapeOperations const vptr = {Shape_area,Shape_draw};
    me->vptr = &vptr;
    me->x = x;
    me->y = y;
}

void Shape_dtor(Shape * const me){
}

uint32_t Shape_area(Shape const * const me) {
    assert(0); 
    return 0U;
}

void Shape_draw(Shape const * const me) {
    assert(0);
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
    static IShapeOperations const vptr = {Rectangle_area,Rectangle_draw};
    Shape_ctor((Shape *)me, x, y);
    me->super.vptr = &vptr;
    me->width = width;
    me->height = height;
}

uint32_t Rectangle_area(Shape const * const me) {
    Rectangle const * const me_ = (Rectangle const *)me;
    return (uint32_t)me_->width * (uint32_t)me_->height;
}

void Rectangle_draw(Shape const * const me) {
    Rectangle const * const me_ = (Rectangle const *)me; 
    printf("Rectangle_draw_(x=%d,y=%d,width=%d,height=%d)\n",
           Shape_getX(me), Shape_getY(me), me_->width, me_->height);
}


void Rectangle_dtor(Rectangle * const me)
{
}


void Circle_ctor(Circle * const me, int16_t x, int16_t y, uint16_t rad){
    static IShapeOperations const vptr = {Circle_area, Circle_draw};
    Shape_ctor((Shape *)me, x, y);
    me->super.vptr = &vptr;
    me->rad = rad;
}

uint32_t Circle_area(Shape const * const me) {
    Circle const * const me_ = (Circle const *)me;
    return 3U * (uint32_t)me_->rad * (uint32_t)me_->rad;
}

void Circle_draw(Shape const * const me) {
    Circle const * const me_ = (Circle const *)me;
    printf("Circle_draw_(x=%d,y=%d,rad=%d)\n",
           Shape_getX(me), Shape_getY(me), me_->rad);
}


void Circle_dtor(Circle * const me){
}


Shape const *largestShape(Shape const *shapes[], uint32_t nShapes) {
    Shape const *s = (Shape *)0;
    uint32_t max = 0U;
    uint32_t i;
    for (i = 0U; i < nShapes; ++i) {
        uint32_t area = shapes[i]->vptr->area(shapes[i]);
        if (area > max) {
            max = area;
            s = shapes[i];
        }
    }
    return s;
}

void drawAllShapes(Shape const *shapes[], uint32_t nShapes) {
    uint32_t i;
    for (i = 0U; i < nShapes; ++i) {
        shapes[i]->vptr->draw(shapes[i]);
    }
}
