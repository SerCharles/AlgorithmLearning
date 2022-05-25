#include<iostream>
#include<cstring>
#include"cp_integer.h"
using namespace std;
void cp_integer::output()
{
	
	cout <<"The num is "<< real_num << endl;
}
void cp_integer::set(int i)
{
	real_num = i;
}
int cp_integer::get()
{
	return real_num;
}
int judge(char str[],bool positive);
int switch_to_int(char str[]);
//10>=i>=1:在第i位有非法字符； i>10 长度太大 i=-1超过int范围  i=-2 超过限制的范围 i=-3设置范围不合理 i=0字符前面都是0 i=-100正常
void cp_integer::input()
{
	while (1)
	{
		try
		{
			i_input();

		}
		catch (int i)
		{
			if (i > 10)
			{
				cout << "The length of the number is " << i << " (excluding the first -), it exceeds 10, it cannot be an integer!" << endl;
			}
			else if (i >= 1)
			{
				cout << "The char at the " << i << "th position (excluding the first -) is invalid!" << endl;
			}
			else if (i == 0)
			{
				cout << "Except 0, the first place of a number cannot be 0!" << endl;
			}
			else if (i == -1)
			{
				cout << "The number exceeds the range of int!" << endl;
				cout << "An integer should stay in the range of -2147483648～2147483647!" << endl;
			}
			/*else if (i == -2)
			{
				cout << "The number exceeds your range!" << endl;
			}
			else if (i == -3)
			{
				cout << "The range you set is invalid, min > max!" << endl;
			}*/
			if(i!=-100) cout << "Invalid input, please try again" << endl;
			else break;
		}
	}
}
void cp_integer::input(int max)
{
	while (1)
	{
		try
		{
			i_input(max);
		}
		catch (int i)
		{
			if (i > 10)
			{
				cout << "The length of the number is " << i << " (excluding the first -), it exceeds 10, it cannot be an integer!" << endl;
			}
			else if (i >= 1)
			{
				cout << "The char at the " << i << "th position (excluding the first -) is invalid!" << endl;
			}
			else if (i == 0)
			{
				cout << "Except 0, the first place of a number cannot be 0!" << endl;
			}
			else if (i == -1)
			{
				cout << "The number exceeds the range of int!" << endl;
				cout << "An integer should stay in the range of -2147483648～2147483647!" << endl;
			}
			else if (i == -2)
			{
				cout << "The number exceeds your range!" << endl;
				cout << "The number should not be larger than " << max << endl;
			}
			/*else if (i == -3)
			{
			cout << "The range you set is invalid, min > max!" << endl;
			}*/
			if (i != -100) cout << "Invalid input, please try again" << endl;
			else break;
		}
	}
}
void cp_integer::input(int min, char c)
{
	while (1)
	{
		try
		{
			i_input(min, c);
		}
		catch (int i)
		{
			if (i > 10)
			{
				cout << "The length of the number is " << i << " (excluding the first -), it exceeds 10, it cannot be an integer!" << endl;
			}
			else if (i >= 1)
			{
				cout << "The char at the " << i << "th position (excluding the first -) is invalid!" << endl;
			}
			else if (i == 0)
			{
				cout << "Except 0, the first place of a number cannot be 0!" << endl;
			}
			else if (i == -1)
			{
				cout << "The number exceeds the range of int!" << endl;
				cout << "An integer should stay in the range of -2147483648～2147483647!" << endl;
			}
			else if (i == -2)
			{
				cout << "The number exceeds your range!" << endl;
				cout << "The number should not be smaller than " << min << endl;
			}
			/*else if (i == -3)
			{
			cout << "The range you set is invalid, min > max!" << endl;
			}*/
			if (i != -100) cout << "Invalid input, please try again" << endl;
			else break;
		}
	}
}
void cp_integer::input(int min, int max)
{
	while (1)
	{
		try
		{
			i_input(min, max);
		}
		catch (int i)
		{
			if (i > 10)
			{
				cout << "The length of the number is " << i << " (excluding the first -), it exceeds 10, it cannot be an integer!" << endl;
			}
			else if (i >= 1)
			{
				cout << "The char at the " << i << "th position (excluding the first -) is invalid!" << endl;
			}
			else if (i == 0)
			{
				cout << "Except 0, the first place of a number cannot be 0!" << endl;
			}
			else if (i == -1)
			{
				cout << "The number exceeds the range of int!" << endl;
				cout << "An integer should stay in the range of -2147483648～2147483647!" << endl;
			}
			else if (i == -2)
			{
				cout << "The number exceeds your range!" << endl;
				cout << "The number should not be smaller than " << min << ", or larger than " << max << endl;
			}
			else if (i == -3)
			{
				cout << "The range you set is invalid, min > max!" << endl;
			}
			if (i != -100&&i!=-3) cout << "Invalid input, please try again" << endl;
			else break;
		}
	}
}
void cp_integer::i_input()
{
	char str[1000] = { 0 }; 
	int length = strlen(str);
		num = 0;
		cout << "Please input an integer." << endl;
		cin >> str;
		//int   -2147483648～2147483647 
		if (str[0] == '-')
		{
			if (judge(&str[1],0)==1)
			{
					num = 0 - switch_to_int(&str[1]);
			}	
			else if (judge(&str[1], 0) == 2)
			{
				num = 0-2147483648;
			}
		}
		else
		{
			if (judge(str,1))
			{
				num = switch_to_int(str);
			}
		}
		real_num = num;
		throw - 100;
}
void cp_integer::i_input(int max)
{
	char str[1000] = { 0 };
	int length = strlen(str);
	num = 0;
	cout << "Please input an integer, which is not larger than "<<max << endl;
	cin >> str;
	//int   -2147483648～2147483647 
	if (str[0] == '-')
	{
		if (judge(&str[1], 0) == 1)
		{
			num = 0 - switch_to_int(&str[1]);
		}
		else if (judge(&str[1], 0) == 2)
		{
			num = 0 - 2147483648;
		}
	}
	else
	{
		if (judge(str, 1))
		{
			num = switch_to_int(str);
		}
	}
	if (num > max) throw -2;
	real_num = num;
	throw - 100;
}
void cp_integer::i_input(int min, char c)
{
		char str[1000] = { 0 };
		int length = strlen(str);
		num = 0;
		cout << "Please input an integer, which is not smaller than "<<min << endl;
		cin >> str;
		//int   -2147483648～2147483647 
		if (str[0] == '-')
		{
			if (judge(&str[1], 0) == 1)
			{
				num = 0 - switch_to_int(&str[1]);
			}
			else if (judge(&str[1], 0) == 2)
			{
				num = 0 - 2147483648;
			}
		}
		else
		{
			if (judge(str, 1))
			{
				num = switch_to_int(str);
			}
		}
		if (num < min) throw - 2;
		real_num = num;
		throw - 100;
}
void cp_integer::i_input(int min, int max)
{
	if (min > max) throw - 3;
		char str[1000] = { 0 };
		int length = strlen(str);
		num = 0;
		cout << "Please input an integer, which is not smaller than "<<min<<" and not larger than "<<max << endl;
		cin >> str;
		//int   -2147483648～2147483647 
		if (str[0] == '-')
		{
			if (judge(&str[1], 0) == 1)
			{
				num = 0 - switch_to_int(&str[1]);
			}
			else if (judge(&str[1], 0) == 2)
			{
				num = 0 - 2147483648;
			}
		}
		else
		{
			if (judge(str, 1))
			{
				num = switch_to_int(str);
			}
		}
		if (num<min || num>max) throw -2;
		real_num = num;
		throw - 100;
}
int judge(char str[],bool positive)
{
	int length = strlen(str);
	if (str[0] == '0'&&str[1]!=0)
	{
		throw 0;
	}
	if (length > 10)
	{
		throw length;
	}
	else
	{
		int i;
		for (i = 0; i < length; i++)
		{
			if (str[i] > '9' || str[i] < '0')
			{
				throw i + 1;
			}
		}
		if (length == 10)
		{
			if (str[0] > '2')
			{
				throw - 1;
			}
			if (str[0] == '2')
			{
				int k = 1,n=0;
				for (i = 9; i >= 1; i--)
				{
					n += (str[i] - '0')*k;
					k *= 10;
				}
				if (positive == 1)
				{
					if (n > 147483647)
					{
						throw -1;
					}
				}
				if (positive == 0)
				{
					if (n > 147483648)
					{
						throw - 1;
					}
					if (n == 147483648) return 2;
				}
			}
		}
	}
	return 1;
}
int switch_to_int(char str[])
{
	int k = 1, n = 0,i;
	int length = strlen(str);
	for (i = length-1; i >= 0; i--)
	{
		n += (str[i] - '0')*k;
		k *= 10;
	}
	return n;
}