#include <stdio.h>
#include <time.h>
#include <string.h>

bool verification_slow(const char** database, const char* word)
{
	while(*database)
	{
		if (strcmp(*database, word) == 0)
		{
			return 1;
		}
		++database;
	}
	return 0;
}

bool verification_fast(const char** database, const char* word, size_t size)
{
	unsigned long long max = size, min = 0;
	int current, cmp;
	while (1)
	{
		current = (min + max) / 2;
		cmp = strcmp(database[current], word);
		if (cmp == 0)
		{
			return 1;
		}
		if (cmp == -1)
		{
			min = current + 1;
		}
		else
		{
			max = current - 1;
		}
		if (min > max)
		{
			return 0;
		}
	}
}