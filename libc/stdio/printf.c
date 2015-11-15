#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void print(const char* data, size_t data_length)
{
	for ( size_t i = 0; i < data_length; i++ )
		putchar((int) ((const unsigned char*) data)[i]);
}

int printf(const char* restrict format, ...)
{
	va_list parameters;
	va_start(parameters, format);

	int written = 0;
	size_t amount;
	bool rejected_bad_specifier = false;

	while ( *format != '\0' )
	{
		if ( *format != '%' )
		{
		print_c:
			amount = 1;
			while ( format[amount] && format[amount] != '%' )
				amount++;
			print(format, amount);
			format += amount;
			written += amount;
			continue;
		}

		const char* format_begun_at = format;

		if ( *(++format) == '%' )
			goto print_c;

		if ( rejected_bad_specifier )
		{
		incomprehensible_conversion:
			rejected_bad_specifier = true;
			format = format_begun_at;
			goto print_c;
		}
		if ( *format == 'X') {
			format++;
			char result[10]="0x00000000";
			long num = va_arg(parameters, long);
			int index = 10;
			while(num != 0) {
				int curr = num % 16;
				//ASCII value of '0' is 48
				int toAdd = 48;

				//if we have a number greater than 9, then it'll be A-E
				//this means we want to base the difference off of 65, the 
				//ASCII value of A.
				if (curr > 9) {
					toAdd = 65;
					curr = curr - 10;
				}

				toAdd = toAdd + curr;
				//we add this to our result array.
				result[--index] = (char) toAdd;
				num = num / 16;
			}
			print((const char *) &result, 10);

		}
		else if ( *format == 'c' )
		{
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			print(&c, sizeof(c));
		}
		else if ( *format == 's' )
		{
			format++;
			const char* s = va_arg(parameters, const char*);
			print(s, strlen(s));
		}
		else
		{
			goto incomprehensible_conversion;
		}
	}

	va_end(parameters);

	return written;
}
