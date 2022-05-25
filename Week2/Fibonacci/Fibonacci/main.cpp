#include<time.h>
#include<iostream>
#include<Windows.h>
using namespace std;

int FinalNumber = 0;
long long Answer = 0;
long long NumList[50001000] = { 0 };
const int DataList[10] = { 10,50,500,1000,3000,10000,100000,1000000,10000000,50000000};

long long CalculateRecursion(int x) //recursion
{
	if (x == 0) return 0;
	if (x == 1) return 1;
	return CalculateRecursion(x - 1) + CalculateRecursion(x - 2);
}

long long CalculateByStep(int num) //remember all steps
{
	NumList[0] = 0;
	NumList[1] = 1;
	for (int i = 2; i <= num; i++)
	{
		NumList[i] = NumList[i - 1] + NumList[i - 2];
	}
	return NumList[num];
}

class Matrix_2_2
{
public:
	long long num[4];
	Matrix_2_2() 
	{ 
		num[0] = 0; num[1] = 0; num[2] = { 0 }; num[3] = { 0 }; 
	}
	friend Matrix_2_2 operator*(Matrix_2_2 a, Matrix_2_2 b);
	void SetIdentity()
	{ 
		num[0] = 1; num[1] = 0; num[2] = 0; num[3] = 1; 
	}
};

Matrix_2_2 operator*(Matrix_2_2 a, Matrix_2_2 b)
{
	Matrix_2_2 nova;
	nova.num[0] = a.num[0] * b.num[0] + a.num[1] * b.num[2];
	nova.num[1] = a.num[0] * b.num[1] + a.num[1] * b.num[3];
	nova.num[2] = a.num[2] * b.num[0] + a.num[3] * b.num[2];
	nova.num[3] = a.num[2] * b.num[1] + a.num[3] * b.num[3];
	return nova;
}

Matrix_2_2 CalculateByMatrix(int times)
{
	if (times == 0)
	{
		Matrix_2_2 ans;
		ans.SetIdentity();
		return ans;
	}
	else if (times == 1)
	{
		Matrix_2_2 ans;
		ans.num[0] = 1; ans.num[1] = 1; ans.num[2] = 1; ans.num[3] = 0;
		return ans;
	}
	else
	{
		int first = times / 2;
		int second = times - first;
		return CalculateByMatrix(first)*CalculateByMatrix(second);
	}
}

int main()
{
	for (int i = 0; i < 10; i++)
	{

		memset(NumList, 0, sizeof(NumList));
		cout << "It is dataset " << i + 1 << ", calculate Fibonacci[" << DataList[i] << "]." << endl;
		
		if (i <= 1)
		{
			time_t start_recursion = 0, stop_recursion = 0;
			start_recursion = clock();
			long long ans_recursion = CalculateRecursion(DataList[i]);
			stop_recursion = clock();
			int ms_recursion = (stop_recursion - start_recursion)*1000/CLOCKS_PER_SEC;
			cout << "Using Recursion, the answer is " << ans_recursion << ", spends time of " << ms_recursion << " ms." << endl;
		}
		else
		{
			cout << "Using Recursion, the time cost is too large" << endl;
		}
		time_t start_steps = 0, stop_steps = 0;
		start_steps = clock();
		long long ans_steps = CalculateByStep(DataList[i]);
		stop_steps = clock();
		int ms_steps = (stop_steps - start_steps)*1000/CLOCKS_PER_SEC;
		cout << "Calculating by steps, the answer is " << ans_steps << ", spends time of " << ms_steps << " ms." << endl;



		time_t start_matrix = 0, stop_matrix = 0;
		start_matrix = clock();
		Matrix_2_2 the_matrix = CalculateByMatrix(DataList[i]);
		long long ans_matrix = the_matrix.num[1];
		stop_matrix = clock();
		int ms_matrix = (stop_matrix - start_matrix)*1000/CLOCKS_PER_SEC;
		cout << "Calculating by matrix, the answer is " << ans_matrix << ", spends time of " << ms_matrix << " ms." << endl;
		cout << endl;
		cout << endl;
		cout << endl;
	}
	cout << "The program will close in 10s" << endl;
	Sleep(10000);
	return 0;
}