#include <stdio.h>
#include <unistd.h>

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
	return (res);
}

int main(void)
{
	unsigned char bytes[4];
	bytes[0] = 1;
	bytes[1] = 1;
	bytes[2] = 1;
	bytes[3] = 1;

	printf("reverse_bytes = %x\n", reverse_bytes(bytes, 4));
	printf("bytes_to_decimal = %x\n", bytes_to_decimal(bytes, 0, 3));
	return (0);
}
