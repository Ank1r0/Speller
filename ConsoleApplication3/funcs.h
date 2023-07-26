#pragma once
#include <stdbool.h>

bool verification_slow(const char** database, const char* word);

bool verification_fast(const char** database, const char* word, size_t size);


