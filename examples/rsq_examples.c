#include "rsq.h"
#include <stdio.h>

int main()
{
    // Example 1

    CREATE_RSQ(x);

    x.insert(&x, 1 );
    x.insert(&x, 5 );
    x.insert(&x, 12 );
    x.insert(&x, 8 );
    x.insert(&x, 7 );

    x.pop(&x);

    for(int i = 0 ; i < x.size; i++)
    {
        printf("%i\n" , x.get(&x , i));
    }

    if(!rsq_empty(&x))
    {
        int sum = x.sum(&x , 1 , x.back);
        printf("SUM: %i\n" , sum);
    }

    // Liberate all RSQ created with CREATE_RSQ
    rsq_free_all();

    // Example 2

    RSQ y = rsq_new();

    for(int i = 0; i < 10 ; i++)
    {
        rsq_insert(&y , i);
    }

    rsq_pop(&y);

    y.clear(&y);
    rsq_insert(&y , 1);
    rsq_insert(&y , 4);
    rsq_insert(&y , 6);

    printf("POS: %i , VALUE: %i\n" , 1 , rsq_get(&y,1));
    printf("SUM: %i" , rsq_sum(&y , y.front , 1));

    rsq_free(&y);
}