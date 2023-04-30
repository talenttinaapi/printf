#include "main.h"
/**
 *print_char - ...
 *@types: ...
 *@buffer: ...
 *@flags: ...
 *@width: ...
 *@precision: ...
 *@size: Size specifier
 *Return: ...
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char v = va_arg(types, int);

	return (handle_write_char(v, buffer, flags, width, precision, size));
}
/**
 *print_string - ...
 *@types: ...
 *@buffer: ...
 *@flags: ...
 *@width: ...
 *@precision: ...
 *@size: Size specifier
 *Return: ...
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, j;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}
	while (str[length] != '\0')
		length++;
	if (precision >= 0 && precision < length)
		length = precision;
	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (j = width - length; j > 0; j--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (j = width - length; j > 0; j--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}
	return (write(1, str, length));
}
/**
 *print_percent - ...
 *@types: ...
 *@buffer: ....
 *@flags: ...
 *@width: ...
 *@precision: ...
 *@size: ...
 *Return: ...
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
/**
 *print_int - ..
 *@types: ...
 *@buffer: ...
 *@flags: ...
 *@width: ...
 *@precision: ...
 *@size: ...
 *Return: ....
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	int is_negative = 0;
	long int k = va_arg(types, long int);
	unsigned long int num;

	k = convert_size_number(k, size);

	if (k == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)k;
	if (k < 0)
	{
		num = (unsigned long int)((-1) * k);
		is_negative = 1;
	}
	while (num > 0)
	{
		buffer[j--] = (num % 10) + '0';
		num /= 10;
	}
	j++;
	return (write_number(is_negative, j, buffer, flags, width, precision, size));
}
/**
 *print_binary - ...
 *@types: ...
 *@buffer: ...
 *@flags: ...
 *@width: ...
 *@precision: ...
 *@size: ...
 *Return: ...
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int k, v, j, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	k = va_arg(types, unsigned int);
	v = 2147483648; /* (2 ^ 31) */
	a[0] = k / v;
	for (j = 1; j < 32; j++)
	{
		v /= 2;
		a[j] = (k / v) % 2;
	}
	for (j = 0, sum = 0, count = 0; j < 32; j++)
	{
		sum += a[j];
		if (sum || j == 31)
		{
			char z = '0' + a[j];
			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
