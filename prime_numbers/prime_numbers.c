#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void primes(unsigned int n, bool *array);

int main(void)
{
    unsigned int n;

    do
    {
        printf("Enter a number n up to which you want to list prime numbers (n > 0): ");
        if(scanf("%u", &n) != 1)
        {
            printf("You entered an invalid value!\n");
            while(getchar() != '\n');
            continue;
        }
    }
    while(n < 1);

    bool *array = (bool *)malloc((n + 1) * sizeof(bool));
    if (array == NULL)
    {
        printf("Memory allocation error!\n");
        return 1;
    }

    primes(n, array);

    for(int i = 2; i <= n; i++)
    {
        if(array[i])
        {
            printf("%u ", i);
        }
    }

    free(array);
    array = NULL;
    return 0;
}

void primes(unsigned int n, bool *array)
{
    for(int i = 0; i <= n; i++)
    {
        array[i] = true;
    }
    array[0] = array[1] = false;

    for(int i = 2; i * i <= n; i++)
    {
        if(array[i])
        {
            for(int j = i * i; j <= n; j += i)
            {
                array[j] = false;
            }
        }
    }
}
