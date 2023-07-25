#include "main.h"
/**
 * handle_print - Prints an argument based on its type
 * @FRT: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int handle_print(const char *FRT, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	FRT_t FRT_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; FRT_types[i].FRT != '\0'; i++)
		if (FRT[*ind] == FRT_types[i].FRT)
			return (FRT_types[i].FNA(list, buffer, flags, width, precision, size));

	if (FRT_types[i].FRT == '\0')
	{
		if (FRT[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (FRT[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (FRT[*ind] != ' ' && FRT[*ind] != '%')
				--(*ind);
			if (FRT[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &FRT[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
