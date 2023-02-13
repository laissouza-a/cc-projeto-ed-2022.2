#include <stdio.h>

int main (void)
{
    int n, m;

    while (1)
    {
        printf("Digite as dimensões da casa em dm: ");
        scanf("%d %d", &n, &m);

        if (n >= 10 && m >= 10)
            break;

        printf("\nImpossivel ter uma casa com menos de 1 m (10 dm)\n");
    }
    
    printf("\n\n");

    for (int i = 0; i < n ; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (j == 0 || j + 1 == m || i == 0 || i + 1 == n)
            {
                printf("1");
            }
            else
            {
                printf("0");
            }

            if (j + 1 == m)
                printf("\n");
        }

        
    }
    
    printf("\n\n");

    return 0;
}