
#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int DEFAULT_MEMORY = 16;
static const int MEMORY_SCALATOR = 2;
static const int MEMORY_REDUCTOR = 4;

typedef struct vector_free{
    vector *_data;
    struct vector_free *next;
}vector_free;

vector_free cleaner = {
    ._data = NULL,
    .next = NULL,
};


static void vect_init(struct vector *curr , size_t memory);
static size_t vect_size_type(Type type);
static int vect_amplify(struct vector *curr , char * _function);
static int vect_reduce(struct vector *curr , char * _function);

static size_t vect_size_type(Type type)
{
    switch (type)
    {
        case INT:
            return sizeof(int);
            break;
        case LONG_LONG:
            return sizeof(long long);
            break;
        case CHAR:
            return sizeof(char);
            break;
        case STRING:
            return sizeof(char *);
            break;
        case FLOAT:
            return sizeof(float);
            break;
        case DOUBLE:
            return sizeof(double);
            break;
        default:
            return sizeof(void *);
    }
}

vector vect_new(Type type)
{
    vector curr;
    curr.type = type;
    curr._memory_Type = vect_size_type(type);
    curr.back = 0;
    curr.reserve = vect_reserve;
    curr.push_back = vect_push_back;
    curr.pop = vect_pop;   
    curr.erase = vect_erase;
    curr.get = vect_get;
    curr.insert = vect_insert;
    curr.begin = vect_begin;
    curr.end = vect_end;
    curr.empty = vect_empty;
    curr.clear = vect_clear;
    curr.free = vect_free;
    vect_init(&curr , DEFAULT_MEMORY);
    return curr;
}

vector vect_new_custom(size_t memory_Type)
{
    vector curr;
    curr._memory_Type = memory_Type;
    curr.type = CUSTOM;
    curr.back = 0;
    curr.reserve = vect_reserve;
    curr.push_back = vect_push_back;
    curr.pop = vect_pop;   
    curr.erase = vect_erase;
    curr.get = vect_get;
    curr.insert = vect_insert;
    curr.begin = vect_begin;
    curr.end = vect_end;
    curr.empty = vect_empty;
    curr.clear = vect_clear;
    curr.free = vect_free;
    vect_init(&curr , DEFAULT_MEMORY);
    return curr;
}

static void vect_init(vector *curr , size_t memory)
{
    curr->memory = memory;
    curr->size = 0;
    curr->_data = malloc(curr->_memory_Type * memory);
    if(curr->_data == NULL){ 
        fprintf(stderr , "ERROR IN : vector_reserve() in allocate memory\n");
        curr->memory = 0;
        return;
    }
}

void vect_reserve(vector *curr , size_t memory)
{
    if(memory <= curr->memory) return;
    if(curr->memory == 0) {
        vect_init(curr , memory);
        return;
    }
    void * temp = curr->_data;
    curr->_data = realloc(curr->_data , curr->_memory_Type * memory);
    if(curr->_data == NULL){
        fprintf(stderr , "ERROR IN : vector_reserve() in allocate memory\n");
        curr->_data = temp;
        return;
    }
    curr->memory = memory;
}

static int vect_amplify(vector *curr , char * _function)
{
    if(curr->size >= curr->memory)
    {
        void *temp = curr->_data;
        curr->_data = realloc(curr->_data , curr->_memory_Type * curr->memory * MEMORY_SCALATOR);
        if(curr->_data == NULL){
            fprintf( stderr , "ERROR IN : %s() in allocate memory\n" , _function);
            curr->_data = temp;
            return 0;
        }
        curr->memory *= MEMORY_SCALATOR;
    }
    return 1;
}

static int vect_reduce(vector *curr , char * _function)
{
    if(curr->size < curr->memory / MEMORY_REDUCTOR && curr->memory/MEMORY_REDUCTOR > DEFAULT_MEMORY)
    {
        void *temp = curr->_data;
        curr->_data = realloc(curr->_data , curr->_memory_Type * curr->memory / MEMORY_REDUCTOR);
        if(curr->_data == NULL){
            fprintf( stderr , "ERROR IN : %s() in allocate memory\n" , _function);
            curr->_data = temp;
            return 0;
        }
        curr->memory /= MEMORY_REDUCTOR;
    }
    return 1;
}

void vect_push_back(vector *curr , void *value)
{
    if(!vect_amplify(curr , "vect_push_back")) return;
    memcpy((char *)curr->_data  + (curr->size * curr->_memory_Type), value , curr->_memory_Type);
    curr->size++;
    curr->back = curr->size -1;
}

void vect_pop(vector *curr)
{
    if(curr->size == 0) return;
    if(!vect_reduce(curr , "vect_pop")) return;
    curr->size--;
    curr->back = curr->size -1;
}

void vect_insert(vector *curr , int index , void * value)
{
    if(curr->size == 0 && index == 0) {
        vect_push_back(curr , value);
        return;
    }
    if(index < 0 || index > curr->size)
    {
        fprintf(stderr , "ERROR IN : vect_insert() index out of bounds\n");
        return;
    }
    if(!vect_amplify(curr , "vect_insert")) return;
    memmove(
    (char *)curr->_data + (index + 1) * curr->_memory_Type,
    (char *)curr->_data + index * curr->_memory_Type,
    (curr->size - index) * curr->_memory_Type
    );
    memcpy((char *)curr->_data + curr->_memory_Type * index , value , curr->_memory_Type);
    curr->size++;
    curr->back = curr->size -1;
}

void vect_erase(vector *curr , int index)
{
    if(curr->size == 0) return;
    if(index < 0 || index >= curr->size){
        fprintf(stderr , "ERROR IN : vect_erase() index out of bounds\n");
        return;
    }
    if(!vect_reduce(curr , "vect_erase")) return;
    memmove(
    (char *)curr->_data + index * curr->_memory_Type,
    (char *)curr->_data + (index + 1) * curr->_memory_Type,
    (curr->size - index - 1) * curr->_memory_Type
    );
    curr->size--;
    curr->back = curr->size -1;
}

void * vect_get(vector *curr , int index)
{
    if(index < 0 || (size_t)index >= curr->size){
        fprintf(stderr , "ERROR IN : vect_get() index out of bounds\n");
        return NULL;
    }
    return ((char *)curr->_data) +  index * curr->_memory_Type;
}

void *vect_begin(vector *curr)
{
    return curr->_data;
}

void *vect_end(vector *curr)
{
    return (char *) curr->_data + curr->_memory_Type * curr->size;
}

int vect_empty(vector *curr)
{
    return curr->size == 0;
}
void vect_clear(vector *curr)
{
    curr->size = 0;
}

void vect_free(vector *curr)
{
    free(curr->_data);
    curr->_data = NULL;
    curr->size = 0;
    curr->memory = 0;
}


void vect_insert_free(vector *curr)
{
    vector_free *temp = malloc(sizeof(vector_free));
    if(temp == NULL) {
        fprintf( stderr , "ERROR IN : vect_insert_free() in allocate memory\n");
        return;
    }
    temp->_data = curr;
    temp->next = cleaner.next;
    cleaner.next = temp;
}

void vect_free_all()
{
    vector_free *ptr = cleaner.next;
    while (ptr != NULL)
    {
        vector_free *temp = ptr;
        ptr = ptr->next;
        vect_free(temp->_data);
        free(temp);
    }
    cleaner.next = NULL;   
}