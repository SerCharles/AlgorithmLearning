/*
filename: Sorts.cpp
description:definations of insert, merge, quick, shell and radix sort for uint
date: 3/25/2019
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

#include "Sorts.h"

unsigned int g_NumList[MAX];
unsigned int auxiliary[MAX];
int num_remain[80000000];

int min(int a, int b)
{
	if (a <= b) return a;
	else return b;
}

void swap(unsigned int& a, unsigned int& b)
{
	unsigned int temp = a;
	a = b;
	b = temp;
}

void g_GenerateRandomNumbers(unsigned int num_list[], int num)
{
	//srand((int)time);
	for (int i = 0; i < num; i++)
	{
		unsigned int trigger_1 = 1 << 15,trigger_2 = 1<<30;
		num_list[i] = rand() * trigger_2 + rand() * trigger_1 + rand();
	}
}

void g_InsertSort(unsigned int num_list[], int num)
{
	for(int i = 1; i < num; i ++)
	{
		unsigned int num_now = num_list[i];
		bool whether_success = 0;
		for (int j = i - 1; j >= 0; j--)
		{
			if (num_now >= num_list[j])
			{
				for (int k = i; k > j + 1; k--)
				{
					num_list[k] = num_list[k - 1];
				}
				num_list[j + 1] = num_now;
				whether_success = 1;
				break;
			}
		}
		if (!whether_success)
		{
			for (int k = i; k > 0; k--)
			{
				num_list[k] = num_list[k - 1];
			}
			num_list[0] = num_now;
		}
	}
}

void g_ShellSort(unsigned int num_list[], int num)
{
	int dist[5] = { 7,5,3,2,1 };
	for (int ii = 0; ii < 5; ii++)
	{
		int d = dist[ii];
		for (int i = 1; i < num; i++)
		{
			unsigned int num_now = num_list[i];
			bool whether_success = 0;

			for (int j = i - d; j >= 0; j = j - d)
			{
				if (num_now >= num_list[j])
				{
					for (int k = i; k > j + d; k = k - d)
					{
						num_list[k] = num_list[k - d];
					}
					num_list[j + d] = num_now;
					whether_success = 1;
					break;
				}
			}

			if (!whether_success)
			{
				int k = i;
				for (k = i; k >= d; k = k - d)
				{
					num_list[k] = num_list[k - d];
				}
				num_list[k] = num_now;
			}
		}
	}
}

void MergeList(unsigned int num_list[], int length, int first, int second, int total_length)
{
	int place_1 = 0, place_2 = 0;
	while (place_1 < length || place_2 < length)
	{
		if (place_1 >= length)
		{
			if (place_2 + second >= total_length) break;
			auxiliary[first + place_1 + place_2] = num_list[place_2 + second];
			place_2++;
		}
		else if (place_2 >= length || place_2 + second >= total_length)
		{
			auxiliary[first + place_1 + place_2] = num_list[place_1 + first];
			place_1++;
		}
		else
		{
			unsigned int current_1 = num_list[place_1 + first];
			unsigned int current_2 = num_list[place_2 + second];
			if (current_1 <= current_2)
			{
				auxiliary[first + place_1 + place_2] = current_1;
				place_1++;
			}
			else
			{
				auxiliary[first + place_1 + place_2] = current_2;
				place_2++;
			}
		}
	}
	for (int i = first; i < min(second + length, total_length); i++)
	{
		num_list[i] = auxiliary[i];
	}
}

void g_MergeSort(unsigned int num_list[], int num)
{
	int size = 1;
	while (size < num)
	{
		int start_place = 0;
		while (start_place + size < num)
		{
			MergeList(num_list, size, start_place, start_place + size, num);
			start_place += (2 * size);
		}
		size = size << 1;
	}

}



int Partition(unsigned int num_list[], int start, int end)
{
	int criterion = num_list[end];
	int small = start - 1;
	for (int i = start; i < end; i++)
	{
		if (num_list[i] < criterion)
		{
			small++;
			swap(num_list[small], num_list[i]);
		}
	}
	small++;
	swap(num_list[small], num_list[end]);
	return small;
}

vector<int> stack_start, stack_end, stack_middle;

void g_QuickSort(unsigned int num_list[], int num)
{
	int start = 0, end = num - 1, middle = 0;
	stack_start.clear();
	stack_middle.clear();
	stack_end.clear();

	do
	{
		if (start >= end)
		{
			if (stack_start.empty()) return;
			start = stack_middle.back() + 1;
			end = stack_end.back();
			stack_start.pop_back();
			stack_middle.pop_back();
			stack_end.pop_back();
		}
		else
		{
			middle = Partition(num_list, start, end);
			stack_start.push_back(start);
			stack_middle.push_back(middle);
			stack_end.push_back(end);
			start = start;
			end = middle - 1;
		}

	} while (!stack_start.empty() || start < end);

}

unsigned int GetRemain(unsigned int number, int time, int once)
{
	for (int i = 1; i <= time; i++)
	{
		number = number >> once;
	}
	return number % (1<<once);
}

void g_RadixSort(unsigned int num_list[], int num)
{
	//num_remain = (int*)malloc(sizeof(int)*MAX);
	int once = min(log2(num),26); //>26,overflow
	double time = (double(32)) / double(once);
	for (int i = 0; i < time; i++)
	{
		for (int j = 0; j < (1 << once); j++)
		{
			num_remain[j] = 0;
		}
		for (int j = 0; j < num; j++)
		{
			unsigned int remain = GetRemain(num_list[j],i,once);
			num_remain[remain] ++;
		}
		for (int j = 1; j < (1 << once); j++)
		{
			num_remain[j] += num_remain[j - 1];
		}
		for (int j = num - 1; j >= 0; j--)
		{
			unsigned int the = num_list[j];
			unsigned int remain = GetRemain(num_list[j], i, once);
			auxiliary[num_remain[remain] - 1] = the;
			num_remain[remain] --;
		}
		for (int j = 0; j < num; j++)
		{
			num_list[j] = auxiliary[j];
		}
	}
	//free(num_remain);
}