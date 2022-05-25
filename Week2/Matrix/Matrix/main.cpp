#include <iostream>
#include <time.h>
#include <Eigen/Eigen>
#include <Windows.h>
using namespace std;

#pragma comment(linker,"/STACK:40000000,40000000")
#define SIZE 16
//change SIZE to change the matrix to n*n, n = 2^k,k is integer




class Matrix
{
public:
	int num[SIZE][SIZE];
	int size_col,size_row;
	Matrix(int i,int j)
	{
		size_col = i;
		size_row = j;
		for (int i = 0; i < size_col; i++)
		{
			for (int j = 0; j < size_row; j++)
			{
				num[i][j] = 0;
			}
		}
	}
	void SetOne()
	{
		for (int i = 0; i < size_col; i++)
		{
			for (int j = 0; j < size_row; j++)
			{
				num[i][j] = 1;
			}
		}
	}

	void SetZero()
	{
		for (int i = 0; i < size_col; i++)
		{
			for (int j = 0; j < size_row; j++)
			{
				num[i][j] = 0;
			}
		}
	}
	friend Matrix operator+(Matrix& a, Matrix& b)
	{
		Matrix nova(a.size_col, a.size_row);
		for (int i = 0; i < a.size_col; i++)
		{
			for (int j = 0; j < a.size_row; j++)
			{
				nova.num[i][j] = a.num[i][j] + b.num[i][j];
			}
		}
		return nova;
	}
	friend Matrix operator-(Matrix& a, Matrix& b)
	{
		Matrix nova(a.size_col, a.size_row);
		for (int i = 0; i < a.size_col; i++)
		{
			for (int j = 0; j < a.size_row; j++)
			{
				nova.num[i][j] = a.num[i][j] - b.num[i][j];
			}
		}
		return nova;
	}
	friend Matrix operator*(Matrix& a, Matrix& b)
	{
		Matrix nova(a.size_col, b.size_row);
		for (int i = 0; i < a.size_col; i++)
		{
			for (int j = 0; j < b.size_row; j++)
			{
				for (int k = 0; k < a.size_row; k++)
				{
					nova.num[i][j] += (a.num[i][k] * b.num[k][j]);
				}
			}
		}
		return nova;
	}

	void CutFour(Matrix& a, Matrix& b, Matrix& c, Matrix& d)
	{
		a.size_col = size_col / 2;
		a.size_row = size_row / 2;
		b.size_col = size_col / 2; 
		b.size_row = size_row - a.size_row;
		c.size_col = size_col - a.size_col;
		c.size_row = size_row / 2;
		d.size_col = size_col - a.size_col;
		d.size_row = size_row - a.size_row;
		for (int i = 0; i < a.size_col; i++)
		{
			for (int j = 0; j < a.size_row; j++)
			{
				a.num[i][j] = num[i][j];
			}
		}
		for (int i = 0; i < b.size_col; i++)
		{
			for (int j = 0; j < b.size_row; j++)
			{
				b.num[i][j] = num[i][j + a.size_row];
			}
		}
		for (int i = 0; i < c.size_col; i++)
		{
			for (int j = 0; j < c.size_row; j++)
			{
					c.num[i][j] = num[i + a.size_col][j];
			}
		}
		for (int i = 0; i < d.size_col; i++)
		{
			for (int j = 0; j < d.size_row; j++)
			{
				d.num[i][j] = num[i + a.size_col][j + a.size_row];
			}
		}
	}

	void ReunionFour(Matrix& a, Matrix& b, Matrix& c, Matrix& d)
	{
		size_col = a.size_col + c.size_col;
		size_row = a.size_row + b.size_row;
		for (int i = 0; i < a.size_col; i++)
		{
			for (int j = 0; j < a.size_row; j++)
			{
				num[i][j] = a.num[i][j];
			}
		}
		for (int i = 0; i < b.size_col; i++)
		{
			for (int j = 0; j < b.size_row; j++)
			{
				num[i][j + a.size_row] = b.num[i][j];
			}
		}
		for (int i = 0; i < c.size_col; i++)
		{
			for (int j = 0; j < c.size_row; j++)
			{
				 num[i + a.size_col][j] = c.num[i][j];
			}
		}
		for (int i = 0; i < d.size_col; i++)
		{
			for (int j = 0; j < d.size_row; j++)
			{
				num[i + a.size_col][j + a.size_row] = d.num[i][j];
			}
		}
	}

	

};

Matrix* MultiplyRecurrence(Matrix* a, Matrix* b)
{
	if (a->size_col == 1 && a->size_row == 1)
	{
		Matrix* nova = new Matrix(1, 1);
		*nova = *a * *b;
		return nova;
	}
	Matrix* a0 = new Matrix(1, 1);
	Matrix* a1 = new Matrix(1, 1);
	Matrix* a2 = new Matrix(1, 1);
	Matrix* a3 = new Matrix(1, 1);
	Matrix* b0 = new Matrix(1, 1);
	Matrix* b1 = new Matrix(1, 1);
	Matrix* b2 = new Matrix(1, 1);
	Matrix* b3 = new Matrix(1, 1);
	Matrix* P1 = new Matrix(1, 1);
	Matrix* P2 = new Matrix(1, 1);
	Matrix* P3 = new Matrix(1, 1);
	Matrix* P4 = new Matrix(1, 1);
	Matrix* P5 = new Matrix(1, 1);
	Matrix* P6 = new Matrix(1, 1);
	Matrix* P7 = new Matrix(1, 1);
	Matrix* r = new Matrix(1, 1);
	Matrix* s = new Matrix(1, 1); 
	Matrix* t = new Matrix(1, 1);
	Matrix* u = new Matrix(1, 1);

	a->CutFour(*a0, *a1, *a2, *a3);
	b->CutFour(*b0, *b1, *b2, *b3);
	P1 = MultiplyRecurrence(a0, &(*b1 - *b3));
	P2 = MultiplyRecurrence(&(*a0 + *a1), b3);
	P3 = MultiplyRecurrence(&(*a2 + *a3), b0);
	P4 = MultiplyRecurrence(a3, &(*b2 - *b0));
	P5 = MultiplyRecurrence(&(*a0 + *a3), &(*b0 + *b3));
	P6 = MultiplyRecurrence(&(*a1 - *a3), &(*b2 + *b3));
	P7 = MultiplyRecurrence(&(*a0 - *a2), &(*b0 + *b1));
	*r = *P5 + *P4;
	*r = *r + *P6;
	*r = *r - *P2;
	*s = *P1 + *P2;
	*t = *P3 + *P4;
	*u = *P5 + *P1;
	*u = *u - *P3;
	*u = *u - *P7;
	Matrix* nova = new Matrix(0, 0);
	nova->ReunionFour(*r, *s, *t, *u);
	delete(a0); delete(a1); delete(a2); delete(a3); delete(b0); delete(b1); delete(b2); delete(b3);
	delete(P1); delete(P2); delete(P3); delete(P4); delete(P5); delete(P6); delete(P7);
	delete(r); delete(s); delete(t); delete(u);
	return nova;
}

Matrix MultiplyRecurrence(Matrix a, Matrix b)
{
	if (a.size_col == 1 && a.size_row == 1)
	{
		Matrix nova(1, 1);
		nova = a * b;
		return nova;
	}
	Matrix a0(1, 1);
	Matrix a1(1, 1);
	Matrix a2(1, 1);
	Matrix a3(1, 1);
	Matrix b0(1, 1);
	Matrix b1(1, 1);
	Matrix b2(1, 1);
	Matrix b3(1, 1);
	Matrix P1(1, 1);
	Matrix P2(1, 1);
	Matrix P3(1, 1);
	Matrix P4(1, 1);
	Matrix P5(1, 1);
	Matrix P6(1, 1);
	Matrix P7(1, 1);
	Matrix r(1, 1);
	Matrix s(1, 1);
	Matrix t(1, 1);
	Matrix u(1, 1);

	a.CutFour(a0, a1, a2, a3);
	b.CutFour(b0, b1, b2, b3);
	P1 = MultiplyRecurrence(a0, b1 - b3);
	P2 = MultiplyRecurrence(a0 + a1, b3);
	P3 = MultiplyRecurrence(a2 + a3, b0);
	P4 = MultiplyRecurrence(a3, b2 - b0);
	P5 = MultiplyRecurrence(a0 + a3, b0 + b3);
	P6 = MultiplyRecurrence(a1 - a3, b2 + b3);
	P7 = MultiplyRecurrence(a0 - a2, b0 + b1);
	r = P5 + P4;
	r = r + P6;
	r = r - P2;
	s = P1 + P2;
	t = P3 + P4;
	u = P5 + P1;
	u = u - P3;
	u = u - P7;
	Matrix nova(0, 0);
	nova.ReunionFour(r, s, t, u);
	return nova;
}


void CalculateEigen()
{
	Eigen::Matrix<int, SIZE, SIZE> matrix_eigen_a;
	Eigen::Matrix<int, SIZE, SIZE> matrix_eigen_b;
	Eigen::Matrix<int, SIZE, SIZE> matrix_eigen_ans;
	for (int i = 0; i < SIZE*SIZE; i++)
	{
		matrix_eigen_a(i) = 1;
		matrix_eigen_b(i) = 1;
	}
	matrix_eigen_ans = matrix_eigen_a * matrix_eigen_b;
}

int main()
{
	cout << "The size of the matrix is " << SIZE << ", it must be 2^k" << endl;

	time_t eigen_start, eigen_end;
	eigen_start = clock();
	CalculateEigen();
	eigen_end = clock();
	cout << "Using eigen costs " << eigen_end - eigen_start << " ms" << endl;

	time_t common_start, common_end;
	common_start = clock();
	Matrix a_common(SIZE, SIZE), b_common(SIZE, SIZE),ans_common(SIZE,SIZE);
	a_common.SetOne(); b_common.SetOne();
	ans_common = a_common * b_common;
	common_end = clock();
	cout << "Using common multiplication costs " << common_end - common_start << " ms" << endl;

	time_t recur_start, recur_end;
	recur_start = clock();
	Matrix a_recur(SIZE, SIZE), b_recur(SIZE, SIZE);
	a_recur.SetOne(); b_recur.SetOne();
	Matrix ans_recur = MultiplyRecurrence(a_recur, b_recur);
	recur_end = clock();
	cout << "Using recurrence costs " << recur_end - recur_start << " ms" << endl;
	
	bool whether_right = 1;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (ans_common.num[i][j] != ans_recur.num[i][j])
			{
				whether_right = 0;
			}
		}
	}
	if (whether_right == 1) cout << "The answer is right" << endl;
	else cout << "The answer is wrong" << endl;

	cout << "Program will quit in 10s" << endl;
	Sleep(10000);
	return 0;
}