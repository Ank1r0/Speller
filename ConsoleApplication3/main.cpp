#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>

#include "funcs.h"
#include <fstream>
#include <iostream>

#include "set.h"

using namespace std;

char* converter(const char* WordIn)
{
	char* WordOut = (char*)malloc(strlen(WordIn)+1);
	unsigned int i = 0, k = 0;
	while (WordIn[i] != '\0')
	{
		if (WordIn[i] >= 'A' && WordIn[i] <= 'Z')
		{
			WordOut[k] = WordIn[i] - ('A' - 'a');
			++i;
			++k;
			continue;
		}
		if (WordIn[i] < 'a' || WordIn[i] > 'z')
		{
			++i;
			continue;
		}
		WordOut[k] = WordIn[i];
		++i;
		++k;
	}
	WordOut[k] = '\0';
	return WordOut;
}

// Функция перестановки соседних символов
char** Correct1(const char* word)
{
	const int len = strlen(word);
	char** ArWords = (char**)calloc(len, sizeof(char*));
	unsigned char dest_i = 0;
	
	// letter
	// dsfgds,gfhggfjh,NULL,dtrrhyu,fgjfgj, NULL
	
	for (int i = 0; i < len-1; ++i)
	{
		if(word[i] == word[i+1])
		{
			continue;
		}
		ArWords[dest_i] = (char*)malloc(len + 1);
		strncpy(ArWords[dest_i], word, i);
		ArWords[dest_i][i] = word[i + 1];
		ArWords[dest_i][i+1] = word[i];
		strcpy(ArWords[dest_i] + i + 2, word + i + 2);
		++dest_i;
	}
	return ArWords;
}

char** Correct2(const char* word)
{
	unsigned int count = 0;
	const int len = strlen(word);
	char** ArWords = (char**)calloc(len + 1, sizeof(char*));
	unsigned char dest_i = 0;

	for (int i = 0; i < len; ++i)
	{
		if (word[i] == word[i + 1])
		{
			continue;
		}
		ArWords[dest_i] = (char*)malloc(len);
		strncpy(ArWords[dest_i], word, i);
		strcpy(ArWords[dest_i] + i, word + i + 1);
		++dest_i;
	}
	return  ArWords;
}

char** Correct3(const char* word)
{
	unsigned int count = 0;
	const int len = strlen(word);
	char** ArWords = (char**)calloc(len * 26 + 1 - len, sizeof(char*));

	for (int i = 0; i < len; ++i)
	{
		for (int j = 'a'; j <= 'z'; ++j)
		{
			if(word[i] == j) continue;
			ArWords[count] = (char*)malloc(len + 1);
			strcpy(ArWords[count], word);
			ArWords[count][i] = j;
			++count;
		}
	}
	return ArWords;
}

char** Correct4(const char* word)
{
	unsigned int count = 0;
	const int len = strlen(word);
	char** ArWords = (char**)calloc(((len + 1) * 26) + 1, sizeof(char*));

	for (int i = 0; i < len + 1; ++i)
	{
		for (int j = 'a'; j <= 'z'; ++j)
		{
			if (i > 0 && word[i-1] == j) continue;
			
			ArWords[count] = (char*)malloc(len + 2);
			
			strncpy(ArWords[count], word, i);
			ArWords[count][i] = j;
			strcpy(ArWords[count] + i + 1, word + i);
			++count;
		}
	}
	return ArWords;
}

void checkText(const char* filename, Set &dict)
{
	std::ifstream ifs(filename);
	if (!ifs.is_open())
	{
		cerr << "Can't open file: " << filename << '\n';
		return;
	}
	string word;
	char *temp;
	char** ((*f_arr[4]))(const char*) = {Correct1, Correct2, Correct3, Correct4};

	while (!ifs.eof())
	{
		ifs >> word;
		temp = converter(word.c_str());
		if (*temp)
		{
			if(!dict.isExist(temp))
			{
				cout << "Incorrect: " << temp << "\tVariants: ";
				char **list = nullptr;
				for (int j = 0; j < 4; ++j)
				{
					list = f_arr[j](temp);
					size_t i = 0;
					while (list[i])
					{
						if(dict.isExist(list[i]))
						{
							cout << list[i] << " ";
							free(list[i]);
						}
						++i;
					}
					free(list);
				}
				cout << "\n";
			}
		}
		free(temp);
	}
}

int main()
{
	Set dict(200000);
	
	clock_t begin = clock();
	std::ifstream ifs("large");
	char buf[100];

	unsigned int size = 0;
	while (!ifs.eof())
	{
		ifs.getline(buf, 100);
		dict.add(buf);
		++size;
	}
	ifs.close();
	cout << "Loading finish. Dict size: " << size << "; Time: " << clock() - begin << "ms\n";

	begin = clock();
	
	checkText("text.txt", dict);
	printf("Time: %d ms\n", clock() - begin);

	system("pause");
	return 0;
}


// Бинарный поиск: 28 мс