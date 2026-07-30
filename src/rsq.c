#include "rsq.h"
#include <stdio.h>
#include <stdlib.h>

// Can change 
static const int DEFAULT_MEMORY = 16;
static const int MEMORY_SCALATOR = 2;
static const int MEMORY_REDUCTOR = 4;

typedef struct RSQ_free
{
    RSQ *data;
    struct RSQ_free *next;
}RSQ_free;

static RSQ_free cleaner = {
    .data = NULL,
    .next = NULL,
};


RSQ rsq_new()
{
    RSQ curr;
    rsq_reserve(&curr, DEFAULT_MEMORY);
    return curr;
}

void rsq_reserve(RSQ *curr, size_t memory)
{
    if(memory == 0) {
        fprintf( stderr , "ERROR IN : reserveRSQ() invalid memory allocate number -> %zu\n" , memory);
        return;
    }
    curr->size = 0;
    curr->memory = memory;
    curr->back = 0;
    curr->front = 0;
    curr->insert = rsq_insert;
    curr->pop = rsq_pop;
    curr->sum = rsq_sum;
    curr->get = rsq_get;
    curr->begin = rsq_begin;
    curr->end = rsq_end;
    curr->free = rsq_free;
    curr->clear = rsq_clear;
    int *new;
    new = malloc(sizeof(int) * memory);
    if(new == NULL){
        fprintf( stderr , "ERROR IN : rsq_reserve() in allocate memory\n");
        return;
    }
    curr->datas = new;
}

void rsq_insert(RSQ *curr , int number)
{
    if(curr->size >= curr->memory)
    {
        int *new;
        new = realloc(curr->datas, sizeof(int) * curr->memory * MEMORY_SCALATOR);
        if(new == NULL){
            fprintf( stderr , "ERROR IN : rsq_insert() in allocate memory\n");
            return;
        }
        curr->memory *= MEMORY_SCALATOR;
        curr->datas = new;
    }
    if(curr->size == 0) curr->datas[curr->size] = number;
    else curr->datas[curr->size] = curr->datas[curr->size-1] + number;
    curr->size++;
    curr->back = curr->size-1;
}

void rsq_pop(RSQ *curr)
{
    if(curr->size == 0) return;
    curr->size--;
    curr->datas[curr->size] = 0;
    curr->back = curr->size - 1;
    if(curr->memory > DEFAULT_MEMORY && curr->size < curr->memory / MEMORY_REDUCTOR)
    {
        int *new = realloc(curr->datas, sizeof(int) * curr->memory/MEMORY_REDUCTOR);
        if(new == NULL) {
            fprintf( stderr ,"ERROR IN : rsq_pop() in allocate memory\n");
            return;
        }
        curr->memory /= MEMORY_REDUCTOR;
        curr->datas = new;
    }
}

int rsq_sum(RSQ *curr , int L , int R)
{
    if(L < 0 || R < 0 || (size_t)L >= curr->size || (size_t)R >= curr->size){
        fprintf( stderr, "ERROR IN : rsq_sum() , start index or end index are out of bounds\n");
        return -2000000000;
    }
    if(L==0) return curr->datas[R]; 
    return curr->datas[R] - curr->datas[L-1];
}

int rsq_get(RSQ *curr, int index)
{
    if(index < 0 || (size_t)index >= curr->size) {
        fprintf( stderr , "ERROR IN : rsq_get() , index is out of bounds\n");
        return -2000000000;
    }
    return rsq_sum(curr , index, index);
}

void rsq_free(RSQ *curr)
{
    free(curr->datas);
    curr->size = 0;
    curr->memory = 0;
    curr->datas = NULL;
}

int *rsq_begin(RSQ *curr)
{
    return curr->datas;
}

int *rsq_end(RSQ *curr) 
{
    return &curr->datas[curr->size];
}

int rsq_empty(RSQ *curr)
{
    return curr->size == 0;
}

void rsq_clear(RSQ *curr)
{
    curr->size = 0;
    curr->back = 0;
}

void rsq_insert_free(RSQ *curr)
{
    RSQ_free *temp = malloc(sizeof(RSQ_free));
    if(temp == NULL) {
        fprintf( stderr , "ERROR IN : rsq_insert_free in allocate memory\n");
        return;
    }
    temp->data = curr;
    temp->next = cleaner.next;
    cleaner.next = temp;
}

void rsq_free_all()
{
    RSQ_free *ptr = cleaner.next;
    while (ptr != NULL)
    {
        RSQ_free *temp = ptr;
        ptr = ptr->next;
        temp->data->free(temp->data);
        free(temp);
    }
    cleaner.next = NULL;   
}