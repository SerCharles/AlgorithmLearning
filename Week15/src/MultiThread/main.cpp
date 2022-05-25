#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
using namespace std;

#include "Sorts.h"
#include "MultiSorts.h"

#define GROUP_NUM 5
#define LESS_GROUP 1
#define MAX_TIME 500000
int g_SizeList[12] = { 10,20,50,100,200,500,700,1000,2000,5000,7000,10000 };

int main()
{	
	time_t start, end, buffer;
	double t;
	omp_set_nested(true);
	/*int i;
	cout << "Please input the size of the data" << endl;
	cout << "input a integer between 0 to 5"<<endl; 
	cout << "representing 10,20,50,100,200,500" << endl;
	cin >> i;
	*/
	
	int kk;
	cout << "Please input the type of sorting" << endl;
	cout << "1:merge_single\n2:quick_single\n3:merge_multi\n4:quick_multi\n";
	cin >> kk;
	for(int i = 0; i <= 5; i ++)
	{
		if(kk == 1)
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
				cout << "Time cost of Single Thread Merge Sort is too high" << endl;
			}
			else
			{
				end = clock();
				t = double(end - start) / GROUP_NUM;
				if (whether_right) cout << "The answer is right" << endl;
				else cout << "The answer is wrong" << endl;
				cout << "Time cost of Single Thread Merge Sort is " << t << " ms" << endl;
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
				cout << "Time cost of Single Thread Quick Sort is too high" << endl;
			}
			else
			{
				end = clock();
				t = double(end - start) / GROUP_NUM;
				if (whether_right) cout << "The answer is right" << endl;
				else cout << "The answer is wrong" << endl;
				cout << "Time cost of Single Thread Quick Sort is " << t << " ms" << endl;
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
				g_MergeSortMultiThread(g_NumList, g_SizeList[i]);
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
				cout << "Time cost of Multi Thread Merge Sort is too high" << endl;
			}
			else
			{
				end = clock();
				t = double(end - start) / GROUP_NUM;
				if (whether_right) cout << "The answer is right" << endl;
				else cout << "The answer is wrong" << endl;
				cout << "Time cost of Multi Thread Merge Sort is " << t << " ms" << endl;
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
				g_QuickSortMultiThread(g_NumList, g_SizeList[i]);
				for (int j = 0; j < g_SizeList[i] - 1; j++)
				{
					if (g_NumList[j] > g_NumList[j + 1])
					{
						whether_right = 0;
					}
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
				cout << "Time cost of Multi Thread Quick Sort is too high" << endl;
			}
			else
			{
				end = clock();
				t = double(end - start) / GROUP_NUM;
				if (whether_right) cout << "The answer is right" << endl;
				else cout << "The answer is wrong" << endl;
				cout << "Time cost of Multi Thread Quick Sort is " << t << " ms" << endl;
			}
			cout << "------------------------------------------------------------------------" << endl;
		}
	}
	
	cout << "The program will quit in 10s";
	Sleep(10000);
	return 0;
}