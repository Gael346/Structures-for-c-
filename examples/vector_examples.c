#include "vector.h"
#include <stdio.h>

int main()
{

    // Example 1
    CREATE_VECT(x , INT);

    for(int i = 0; i < 10; i++)
    {
        x.push_back(&x , VDATE(i));
    }

    for(size_t i = 0; i < x.size; i++)
    {
        int value;
        VGET(x , i , value);
        printf("%i\n" , value);
    }

    x.insert(&x , 4 , VDATE(100));

    int value = PARSE(x.get(&x , 4) , int);
    printf("POS: %i , VALUE %i\n" , 4 , value);

    x.erase(&x , 5);
    x.pop(&x);
    x.pop(&x);

    if(!x.empty(&x))
    {
        printf("VECTOR IS NOT EMPTY\n");

        for(int i = 0; i < x.size; i++)
        {
            int value;
            VGET(x , i , value);
            printf("%i\n" , value);
        }
    }

    // Liberate all vector created with CREATE_VECT 
    vect_free_all();

    // Example 2
    vector y = vect_new(STRING);

    vect_push_back(&y , VDATE("Word"));
    vect_insert(&y , 0 , VDATE("Hello"));
    vect_push_back(&y , VDATE("this"));

    for(size_t i = 0; i < y.size; i++)
    {
        str value;
        VGET(y , i , value);
        printf("%s " , value);
    }
    printf("\n");

    vect_erase(&y , 0);

    str value_str;
    VGET(y , 0 , value_str);
    printf("POS:%i , VALUE: %s\n" , 0 ,  value_str);

    vect_clear(&y);
    if(vect_empty(&y)) 
    {
        printf("NOT EMPTY\n");
    }

    vect_free(&y);
}