#ifndef RSQ_H
#define RSQ_H
#include <stddef.h>

//  Can change the name of functions
#define Get_RSQ(self , number) self.get(&self, number)
#define Begin_RSQ(self) rsq_begin(&self)
#define End_RSQ(self) rsq_end(&self)
#define CREATE_RSQ(name) \
    RSQ name = rsq_new(); \
    rsq_insert_free(&name)

typedef struct RSQ
{
    int *datas;
    size_t size;
    size_t back;
    size_t front;
    size_t memory;
    void (*insert)(struct RSQ *self , int number);
    void (*pop)(struct RSQ *curr);
    int (*sum)(struct RSQ *self , int start , int end);
    int (*get)(struct RSQ *self , int index);
    int *(*begin)(struct RSQ *self);
    int *(*end)(struct RSQ *self);
    void (*free)(struct RSQ *self);
    void (*clear)(struct RSQ *self);
}RSQ;

void rsq_insert_free(RSQ *curr);
void rsq_free_all(void);

RSQ rsq_new(void);
void rsq_reserve(RSQ *curr, size_t memory);
void rsq_insert(RSQ *curr , int number);
void rsq_pop(RSQ *curr);
int rsq_sum(RSQ *curr , int L , int R);
int rsq_get(RSQ *curr, int index);
int *rsq_begin(RSQ *curr);
int *rsq_end(RSQ *curr);
int rsq_empty(RSQ *curr);
void rsq_clear(RSQ *curr);
void rsq_free(RSQ *curr);

#endif 