#include <stdio.h>
#include <stdint.h>

void	print_bit(int nb)
{
	uint32_t		bit = 1 << 31L;
	int			index = 0;

	while (bit)
	{
		if (index % 8 == 0 && index != 0)
			printf(" ");
		if (bit & nb)
			printf("1");
		else
			printf("0");
		bit >>= 1;
		index++;
	}
	printf("\n");
}

#define FIRST 0xFF000000
#define SECOND 0x00FF0000
#define THIRD 0x0000FF00
#define FOURTH 0x000000FF
/*
	carriage->arg[0] = (act & FIRST) >> 6;
	carriage->arg[1] = (act & SECOND) >> 4;
	carriage->arg[2] = (act & THIRD) >> 2;
	carriage->arg[3] = (act & FOURTH);
*/
int main()
{
	int number = 42;
	print_bit(number);

	unsigned char answer[4];

	answer[0] = number & 0xFF000000;
	answer[1] = number & SECOND;
	answer[2] = number & THIRD;
	answer[3] = number & FOURTH;
/*
	uint32_t bit = 1 << 8;
	int index = 0;
	int tmp = 0;
	int res = 0;
	int devide = 1;
	while (index < 32)
	{
		tmp = (bit & number) | tmp;
		bit >>= 1;
		if (index % 8 == 0 && index != 0)
		{
			res = res | (tmp << (32 - (8 * (devide + 1))));
			printf("tmp moved: ");
			print_bit(tmp << (32 - (8 * devide)));
			bit = 1 << (8 * (devide + 1) - 1);
			tmp = 0;
			printf("tmp: ");
			print_bit(tmp);
			devide++;
		} 

		index++;
	}
	*/

	
	for (int i = 0; i < 4; i++)
		printf("%X ", answer[i]);



	return 0;
}