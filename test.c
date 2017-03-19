#include <stdio.h>

int main(int argc, char **argv)
{
	int i;
	int retry = 0;

	while (1)
	{
		i = 0;
		while(i < 1000000000)
		{
			i++;
		}
		retry++;
		if (retry == 5)
			break;
	}
	printf("Coucou\n");
}
