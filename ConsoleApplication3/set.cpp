#include "set.h"
#include <cmath>
#include <cstring>
#include <cstdio>

#define ARRAY_OVERLOAD 1

typedef unsigned long long ull;
typedef unsigned int uint;

ull Set::hashfunc(const char* word)
{
	ull hashcode = 0;

	for (uint j = 0; j < strlen(word); ++j)
	{
		hashcode += (ull)pow(word[j], j + 1);
	}
	return hashcode;
}

Set::Set(size_t size)
{
	this->size = size;
	this->table = new char*[size]();
}

void Set::add(const char* key)
{
	uint index = hashfunc(key) % size;
	char lenght = strlen(key)+1;
	if (this->table[index] == nullptr)
	{
		this->table[index] = new char[lenght];
		strcpy_s(this->table[index], lenght, key);
		return;
	}
	uint i = index == size-1 ? 0 : index+1;
	while (i != index)
	{
		if (this->table[i] == nullptr)
		{
			this->table[i] = new char[lenght];
			strcpy_s(this->table[i], lenght, key);
			return;
		}
		i = i == size - 1 ? 0 : i + 1;
	}
	perror("Array is full!\n");
	system("pause");
	exit(ARRAY_OVERLOAD);
}

bool Set::isExist(const char* key)
{
	uint index = hashfunc(key) % size;
	if (this->table[index] == nullptr)
		return false;
	if (strcmp(this->table[index], key) == 0)
		return true;
	uint i = index == size - 1 ? 0 : index + 1;
	while (this->table[i] != nullptr && i != index)
	{
		if (strcmp(this->table[i], key) == 0)
		{
			return true;
		}
		i = i == size - 1 ? 0 : i + 1;
	}
	return false;
}
