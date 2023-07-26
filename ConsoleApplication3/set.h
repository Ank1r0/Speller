#pragma once

typedef unsigned long long ull;
typedef unsigned int uint;

class Set
{
	size_t size;
	char **table;
	ull hashfunc(const char*);

public:
	Set(size_t);
	void add(const char*);
	bool isExist(const char*);
};
