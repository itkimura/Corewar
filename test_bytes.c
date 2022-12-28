#include <stdio.h>
#include <unistd.h>

/* 
 * https://stackoverflow.com/questions/30407091/why-does-casting-a-char-array-to-an-int-pointer-and-writing-to-it-using-the-poin
 */
void	print_bit(int nb)
{
	uint32_t	bit = 1 << 31L;
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
/* 
 * test of reverse_bytes
 */
int	reverse_bytes(unsigned char *bytes, int len)
{
	unsigned char	four_bytes[4];
	int				index;

	index = 0;
	while (len-- > 0)
	{
		four_bytes[index] = bytes[len];
		index++;
	}
	printf("reverse_bytes unsigned char: ");
	for (int index = 0; index < 4; index++)
		printf("%02d ", four_bytes[index]);
	printf("\nprint_bit: ");
	print_bit(*(int *)&four_bytes[0]);
	return (*(int *)&four_bytes[0]);
}

/* like atoi, convert bytes to decimal */
uint32_t	bytes_to_decimal(unsigned char *bytes, int start_idx, int end_idx)
{
	uint32_t	res;
	uint32_t	tmp;
	short int	shifted_value;

	shifted_value = 0;
	res = 0;
	while (end_idx >= start_idx)
	{
		tmp = (uint32_t)bytes[end_idx];
		res = (tmp << shifted_value) | res;
		shifted_value += 8;
		end_idx--;
	}
	printf("\nprint_bit: ");
	print_bit(res);
	return (res);
}

int main(void)
{
	unsigned char bytes[4]; //unsigned char = 1 byte
	bytes[0] = 0;
	bytes[1] = 0;
	bytes[2] = 0;
	bytes[3] = 42;
	printf("----- before -----\n");
	printf("unsigned char array: ");
	for (int index = 0; index < 4; index++)
		printf("%02d ", bytes[index]);
	printf("\n");
	print_bit(*(int *)&bytes[0]);
	printf("\n----- reverse_bytes -----\n");
	printf("reverse_bytes = %x\n", reverse_bytes(bytes, 4));
	printf("\n----- bytes_to_decimal -----");
	printf("bytes_to_decimal = %x\n", bytes_to_decimal(bytes, 0, 3));
	return (0);
}
