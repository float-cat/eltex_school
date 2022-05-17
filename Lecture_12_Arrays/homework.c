#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int **matrix;
	int i, j, k, l;
	int size;
	int tmp, tmpsize;
	scanf("%d", &size);
	tmpsize = size * size;
	matrix = malloc(size * sizeof(int *));
	for(i = 0; i < size; i++)
		matrix[i] = malloc(size * sizeof(int));
	k = 0; l = size;
	tmp = 1;
	while(tmp <= tmpsize)
	{
		for(i = k; i < l; i++)
		{
			matrix[k][i] = tmp;
			tmp++;
		}
		if(tmp >= tmpsize)
			break;
		for(i = k+1; i < l-1; i++)
		{
			matrix[i][l-1] = tmp;
			tmp++;
		}
		for(i = l-1; i >= k; i--)
		{
			matrix[l-1][i] = tmp;
			tmp++;
		}
		for(i = l-2; i > k; i--)
		{
			matrix[i][k] = tmp;
			tmp++;
		}
		k++;
		l--;
	}
	for(i=0; i<size; i++)
	{
		for(j=0; j<size; j++)
		{
			if(matrix[i][j] < 10)
				printf(" ");
			printf(" %d ", matrix[i][j]);
		}
		printf("\n");
	}
	return 0;
}
