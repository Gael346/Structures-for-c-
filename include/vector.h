#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef char * str;

#define PARSE(variable, type) (*(type *)(variable))

#define VGET(vector , index , allocator) allocator = *((__typeof__(allocator) *)vect_get(&vector , index))

#define CREATE_VECT( name , type) \
    vector name = vect_new(type); \
    vect_insert_free(&name);

#define CREATE_VECT_CUSTOM( name , type) \
    vector name = vect_new_custom(sizeof(type)); \
    vect_insert_free(&name);

#define VDATE(value) \
    __builtin_choose_expr( \
        __builtin_types_compatible_p(__typeof__(value), char[sizeof(value)]), \
        (void *)&(char *){(char *)(uintptr_t)(value)}, \
        (void *)&(__typeof__(value)){value} \
    )

typedef enum
{
    INT,
    LONG_LONG,
    CHAR,
    STRING,
    FLOAT,
    DOUBLE,
    CUSTOM
}Type;

typedef struct vector
{
    Type type;
    void *_data;
    size_t _element_Size;
    size_t size;
    size_t capacity;
    size_t back;
    void (*reserve)(struct vector *self, size_t capacity);
    void (*push_back)(struct vector *self, void *value);
    void (*pop)(struct vector *self);
    void *(*get)(struct vector *self, int index);
    void (*insert)(struct vector *self, int index, void *value);
    void (*erase)(struct vector *self, int index);
    void *(*begin)(struct vector *self);
    void *(*end)(struct vector *self);
    int (*empty)(struct vector *self);
    void (*clear)(struct vector *self);
    void (*free)(struct vector *self);
}vector;


void vect_free_all();
void vect_insert_free(vector *curr);

vector vect_new(Type type); 
vector vect_new_custom(size_t capacity_Type);
void vect_reserve(struct vector *curr , size_t capacity);

void vect_push_back(struct vector *curr , void *value);
void vect_pop(struct vector *curr);
void vect_insert(struct vector *curr , int index , void * value);
void vect_erase(struct vector *curr , int index);

void * vect_get(struct vector *curr , int index);
void *vect_begin(struct vector *curr);
void *vect_end(struct vector *curr);

int vect_empty(struct vector *curr);
void vect_clear(struct vector *curr);
void vect_free(struct vector *curr);


#endif 