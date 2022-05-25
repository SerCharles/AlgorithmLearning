#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
using namespace std;

#include "Sorts.h"

#define GROUP_NUM 5
#define LESS_GROUP 1
#define MAX_TIME 500000
int g_SizeList[9] = { 10,100,1000,10000,100000,1000000,10000000,100000000,200000000 };

int main()
{	
	time_t start, end, buffer;
	double t;
	int i;
	cout << "Please input the size of the data" << endl;
	cout << "input a integer between 0 to 8"<<endl; 
	cout << "representing 10,100,1000,10000,100000,1000000,10000000,100000000,200000000" << endl;
	cin >> i;
	{
		int kk;
		cout << "Please input the type of sorting" << endl;
		cout << "1:insert\n2:shell\n3:merge\n4:quick\n5:radix\n";
		cin >> kk;
		if(kk == 1)
		{
			cout << "The size is " << g_SizeList[i] << endl;
			start = clock();
			bool whether_right = 1;
			bool whether_success = 1;
			for (int ii = 0; ii < GROUP_NUM; ii++)
			{
				g_GenerateRandomNumbers(g_NumList, g_SizeList[i]);
				g_InsertSort(g_NumList, g_SizeList[i]);
				for (int j = 0; j < g_SizeList[i] - 1; j++)
				{
					if (g_NumList[j] > g_NumList[j + 1]) whether_right = 0; 
				}
				buffer = clock() - start;
				if (buffer > MAX_TIME)
				{
					whether_success = 0;
					break;
				}
			}
			if (!whether_success)
			{
				cout << "Time cost of Insert Sort is too high"<<endl;
			}
			else
			{
				end = clock();
				t = double(end - start) / GROUP_NUM;
				if (whether_right) cout << "The answer is right" << endl;
				else cout << "The answer is wrong" << endl;
				cout << "Time cost of Insert Sort is " << t << " ms" << endl;
			}
			cout << "------------------------------------------------------------------------" << endl;
		}

		else if(kk == 2)
		{
			cout << "The size is " << g_SizeList[i] << endl;
			start = clock();
			bool whether_right = 1;
			bool whether_success = 1;
			for (int ii = 0; ii < GROUP_NUM; ii++)
			{
				g_GenerateRandomNumbers(g_NumList, g_SizeList[i]);
				g_ShellSort(g_NumList, g_SizeList[i]);
				for (int j = 0; j < g_SizeList[i] - 1; j++)
				{
					if (g_NumList[j] > g_NumList[j + 1]) whether_right = 0;
				}
				buffer = clock() - start;
				if (buffer > MAX_TIME)
				{
					whether_success = 0;
					break;
				}
			}
			if (!whether_success)
			{
				cout << "Time cost of Shell Sort is too high" << endl;
			}
			else
			{
				end = clock();
				t = double(end - start) / GROUP_NUM;
				if (whether_right) cout << "The answer is right" << endl;
				else cout << "The answer is wrong" << endl;
				cout << "Time cost of Shell Sort is " << t << " ms" << endl;
			}
			cout << "------------------------------------------------------------------------" << endl;
		}

		else if(kk == 3)
		{
			cout << "The size is " << g_SizeList[i] << endl;
			start = clock();
			bool whether_right = 1;
			bool whether_success = 1;
			for (int ii = 0; ii < GROUP_NUM; ii++)
			{
				g_GenerateRandomNumbers(g_NumList, g_SizeList[i]);
				g_MergeSort(g_NumList, g_SizeList[i]);
				for (int j = 0; j < g_SizeList[i] - 1; j++)
				{
					if (g_NumList[j] > g_NumList[j + 1]) whether_right = 0;
				}
				buffer = clock() - start;
				if (buffer > MAX_TIME)
				{
					whether_success = 0;
					break;
				}
			}
			if (!whether_success)
			{
				cout << "Time cost of Merge Sort is too high" << endl;
			}
			else
			{
				end = clock();
				t = double(end - start) / GROUP_NUM;
				if (whether_right) cout << "The answer is right" << endl;
				else cout << "The answer is wrong" << endl;
				cout << "Time cost of Merge Sort is " << t << " ms" << endl;
			}
			cout << "------------------------------------------------------------------------" << endl;
		}

		else if(kk == 4)
		{
			cout << "The size is " << g_SizeList[i] << endl;
			start = clock();
			bool whether_right = 1;
			bool whether_success = 1;
			for (int ii = 0; ii < GROUP_NUM; ii++)
			{
				g_GenerateRandomNumbers(g_NumList, g_SizeList[i]);
				g_QuickSort(g_NumList, g_SizeList[i]);
				for (int j = 0; j < g_SizeList[i] - 1; j++)
				{
					if (g_NumList[j] > g_NumList[j + 1]) whether_right = 0;
				}
				buffer = clock() - start;
				if (buffer > MAX_TIME)
				{
					whether_success = 0;
					break;
				}
			}
			if (!whether_success)
			{
				cout << "Time cost of Quick Sort is too high" << endl;
			}
			else
			{
				end = clock();
				t = double(end - start) / GROUP_NUM;
				if (whether_right) cout << "The answer is right" << endl;
				else cout << "The answer is wrong" << endl;
				cout << "Time cost of Quick Sort is " << t << " ms" << endl;
			}
			cout << "------------------------------------------------------------------------" << endl;
		}

		else
		{
			cout << "The size is " << g_SizeList[i] << endl;
			start = clock();
			bool whether_right = 1;
			bool whether_success = 1;
			for (int ii = 0; ii < GROUP_NUM; ii++)
			{
				g_GenerateRandomNumbers(g_NumList, g_SizeList[i]);
				g_RadixSort(g_NumList, g_SizeList[i]);
				for (int j = 0; j < g_SizeList[i] - 1; j++)
				{
					if (g_NumList[j] > g_NumList[j + 1]) whether_right = 0;
				}
				buffer = clock() - start;
				if (buffer > MAX_TIME)
				{
					whether_success = 0;
					break;
				}
			}
			if (!whether_success)
			{
				cout << "Time cost of Radix Sort is too high" << endl;
			}
			else
			{
				end = clock();
				t = double(end - start) / GROUP_NUM;
				if (whether_right) cout << "The answer is right" << endl;
				else cout << "The answer is wrong" << endl;
				cout << "Time cost of Radix Sort is " << t << " ms" << endl;
			}
			cout << "------------------------------------------------------------------------" << endl;
		}
	}
	
	cout << "The program will quit in 10s";
	Sleep(10000);
	return 0;
}