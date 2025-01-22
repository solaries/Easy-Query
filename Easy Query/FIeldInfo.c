
#include "FieldInfo.h"
#include <string.h>
#include <ctype.h>

char* trim_whitespaces(char *str)
{
	char *end;
	// trim leading space
	while(isspace(*str))
		str++;

	if(*str == 0) // all spaces?
		return str;

	// trim trailing space
	end = str + strnlen(str, 128) - 1;

	while(end > str && isspace(*end))
		end--;

	// write new null terminator
	*(end+1) = '\0';

	return str;
}
