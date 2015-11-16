#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void print(const char* data, size_t data_length)
{
	for ( size_t i = 0; i < data_length; i++ )
	{
		putchar((int) ((const unsigned char*) data)[i]);
	}
}

int _print_addr(unsigned long address) {
	printf("%X\n", address);
}

//helper function exposed to assembly i can use to print debugs
int _printf(const char* restrict format, ...) {
	va_list parameters;
	va_start(parameters, format);
	printf(format, parameters);
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
			//get our number
			unsigned long num = va_arg(parameters, unsigned long);
			long temp = num;
			int size = 0;
			while(temp != 0) {
				temp = temp / 16;
				size++;
			}

			//we want our string to be 0x<number>\0
			size=size+3;

			//create our result string
			char* result;
			memcpy(result, 0, size);
			//we start at the second to last index
			int index = size-2;
			while(index >= 2) {
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
				result[index--] = (char) toAdd;
				num = num / 16;
			}
			result[0] = '0';
			result[1] = 'x';
			result[size-1] = '\0';
			print(result, strlen(result));
		}
		else if ( *format == 'i' ) {
			format++;
			//get our number
			long num = va_arg(parameters, long);
			long temp = num;
			int size = 0;

			while(temp != 0) {
				temp = temp / 10;
				size++;
			}

			//we want our string to be number\0
			size=size+1;

			//create our result string
			char* result;
			memcpy(result, 0, size);

			//we start at the second to last index
			int index = size-2;
			while(index >= 0) {
				int curr = num % 10;
				//ASCII value of '0' is 48
				int toAdd = 48;
				toAdd = toAdd + curr;
				//we add this to our result array.
				result[index--] = (char) toAdd;
				num = num / 10;
			}
			result[size-1] = '\0';
			print(result, strlen(result));
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
