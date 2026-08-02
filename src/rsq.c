#include "rsq.h"
#include <stdio.h>
#include <stdlib.h>

// Can change 
static const int DEFAULT_CAPACITY = 16;
static const int CAPACITY_SCALATOR = 2;
static const int CAPACITY_REDUCTOR = 4;

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
    rsq_reserve(&curr, DEFAULT_CAPACITY);
    return curr;
}

void rsq_reserve(RSQ *curr, size_t capacity)
{
    if(capacity == 0) {
        fprintf( stderr , "ERROR IN : reserveRSQ() invalid capacity allocate number -> %zu\n" , capacity);
        return;
    }
    curr->size = 0;
    curr->capacity = capacity;
    curr->back = 0;
    curr->push_back = rsq_push_back;
    curr->pop = rsq_pop;
    curr->sum = rsq_sum;
    curr->get = rsq_get;
    curr->begin = rsq_begin;
    curr->end = rsq_end;
    curr->free = rsq_free;
    curr->clear = rsq_clear;
    int *new;
    new = malloc(sizeof(int) * capacity);
    if(new == NULL){
        fprintf( stderr , "ERROR IN : rsq_reserve() in allocate capacity\n");
        return;
    }
    curr->_data = new;
}

void rsq_push_back(RSQ *curr , int number)
{
    if(curr->size >= curr->capacity)
    {
        int *new;
        new = realloc(curr->_data, sizeof(int) * curr->capacity * CAPACITY_SCALATOR);
        if(new == NULL){
            fprintf( stderr , "ERROR IN : rsq_push_back() in allocate capacity\n");
            return;
        }
        curr->capacity *= CAPACITY_SCALATOR;
        curr->_data = new;
    }
    if(curr->size == 0) curr->_data[curr->size] = number;
    else curr->_data[curr->size] = curr->_data[curr->size-1] + number;
    curr->size++;
    curr->back = curr->size-1;
}

void rsq_pop(RSQ *curr)
{
    if(curr->size == 0) return;
    curr->size--;
    curr->_data[curr->size] = 0;
    curr->back = curr->size - 1;
    if(curr->capacity > DEFAULT_CAPACITY && curr->size < curr->capacity / CAPACITY_REDUCTOR)
    {
        int *new = realloc(curr->_data, sizeof(int) * curr->capacity/CAPACITY_REDUCTOR);
        if(new == NULL) {
            fprintf( stderr ,"ERROR IN : rsq_pop() in allocate capacity\n");
            return;
        }
        curr->capacity /= CAPACITY_REDUCTOR;
        curr->_data = new;
    }
}

int rsq_sum(RSQ *curr , int L , int R)
{
    if(L < 0 || R < 0 || (size_t)L >= curr->size || (size_t)R >= curr->size){
        fprintf( stderr, "ERROR IN : rsq_sum() , start index or end index are out of bounds\n");
        return -2000000000;
    }
    if(L==0) return curr->_data[R]; 
    return curr->_data[R] - curr->_data[L-1];
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
    free(curr->_data);
    curr->size = 0;
    curr->capacity = 0;
    curr->_data = NULL;
}

int *rsq_begin(RSQ *curr)
{
    return curr->_data;
}

int *rsq_end(RSQ *curr) 
{
    return &curr->_data[curr->size];
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
        fprintf( stderr , "ERROR IN : rsq_insert_free in allocate capacity\n");
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