#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

int rows = 2;
int cols = 2;

vector<vector<int>> Iterative(vector<vector<int>> first, vector<vector<int>> second)
{

	vector <vector<int>> multiply;

	vector <int> v;
	int rows = first.size();
	int cols = first[0].size();
	int range = second[0].size();

	multiply.resize(rows, vector<int>(range, 0));
	int sum = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < range; j++)
		{
			for (int k = 0; k < cols; k++)
			{
				sum = sum + first[i][k] * second[k][j];
			}
			multiply[i][j] = sum;
			sum = 0;
		}
	}

	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			cout << multiply[i][j] << " ";

		}
		cout << "\n";
	}
	return multiply;
}


vector<vector<int>> Cal_Sum_Strassen(vector<vector<int>> first, vector<vector<int>> second)
{
	int n = first.size();
	vector<vector<int>> Result;
	Result.resize(n, vector<int>(n, 0));
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			Result[i][j] = first[i][j] + second[i][j];
		}
	}
	return Result;
}

vector<vector<int>> Cal_Sub_Strassen(vector<vector<int>> first, vector<vector<int>> second)
{
	int n = first.size();
	vector<vector<int>> Result;
	Result.resize(n, vector<int>(n, 0));
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			Result[i][j] = first[i][j] - second[i][j];
		}
	}
	return Result;
}

vector<vector<int>> Strassen(vector<vector<int>> first, vector<vector<int>> second)
{
	int n = first.size();

	vector<vector<int>> multiply;
	multiply.resize(n, vector<int>(n, 0));

	if (n == 1)
	{
		multiply[0][0] = first[0][0] * second[0][0];
		return multiply;
	}
	else {
		vector<vector<int>> a11, a12, a21, a22;
		vector<vector<int>> b11, b12, b21, b22;
		vector<vector<int>> c11, c12, c21, c22;
		vector<vector<int>> p1, p2, p3, p4, p5, p6, p7;

		a11.resize(n / 2, vector<int>(n / 2, 0));
		a12.resize(n / 2, vector<int>(n / 2, 0));
		a21.resize(n / 2, vector<int>(n / 2, 0));
		a22.resize(n / 2, vector<int>(n / 2, 0));

		b11.resize(n / 2, vector<int>(n / 2, 0));
		b12.resize(n / 2, vector<int>(n / 2, 0));
		b21.resize(n / 2, vector<int>(n / 2, 0));
		b22.resize(n / 2, vector<int>(n / 2, 0));

		c11.resize(n / 2, vector<int>(n / 2, 0));
		c12.resize(n / 2, vector<int>(n / 2, 0));
		c21.resize(n / 2, vector<int>(n / 2, 0));
		c22.resize(n / 2, vector<int>(n / 2, 0));

		p1.resize(n / 2, vector<int>(n / 2, 0));
		p2.resize(n / 2, vector<int>(n / 2, 0));
		p3.resize(n / 2, vector<int>(n / 2, 0));
		p4.resize(n / 2, vector<int>(n / 2, 0));
		p5.resize(n / 2, vector<int>(n / 2, 0));
		p6.resize(n / 2, vector<int>(n / 2, 0));
		p7.resize(n / 2, vector<int>(n / 2, 0));

		vector<vector<int>> firstResult;
		vector<vector<int>> secondResult;
		firstResult.resize(n / 2, vector<int>(n / 2, 0));
		secondResult.resize(n / 2, vector<int>(n / 2, 0));


		for (int i = 0; i < n / 2; i++)
		{
			for (int j = 0; j < n / 2; j++)
			{
				a11[i][j] = first[i][j];
				a12[i][j] = first[i][j + n / 2];
				a21[i][j] = first[i + n / 2][j];
				a22[i][j] = first[i + n / 2][j + n / 2];

				b11[i][j] = second[i][j];
				b12[i][j] = second[i][j + n / 2];
				b21[i][j] = second[i + n / 2][j];
				b22[i][j] = second[i + n / 2][j + n / 2];
			}
		}

		firstResult = Cal_Sum_Strassen(a11, a22);
		secondResult = Cal_Sum_Strassen(b11, b22);
		p1 = Strassen(firstResult, secondResult);

		firstResult = Cal_Sum_Strassen(a21, a22);
		p2 = Strassen(firstResult, b11);

		secondResult = Cal_Sub_Strassen(b12, b22);
		p3 = Strassen(a11, secondResult);

		secondResult = Cal_Sub_Strassen(b21, b11);
		p4 = Strassen(a22, secondResult);

		firstResult = Cal_Sum_Strassen(a11, a12);
		p5 = Strassen(firstResult, b22);

		firstResult = Cal_Sub_Strassen(a21, a11);
		secondResult = Cal_Sum_Strassen(b11, b12);
		p6 = Strassen(firstResult, secondResult);

		firstResult = Cal_Sub_Strassen(a12, a22);
		secondResult = Cal_Sum_Strassen(b21, b22);
		p7 = Strassen(firstResult, secondResult);

		c12 = Cal_Sum_Strassen(p3, p5);
		c21 = Cal_Sum_Strassen(p2, p4);

		firstResult = Cal_Sum_Strassen(p1, p4);
		secondResult = Cal_Sum_Strassen(firstResult, p7);
		c11 = Cal_Sub_Strassen(secondResult, p5);

		firstResult = Cal_Sum_Strassen(p1, p3);
		secondResult = Cal_Sum_Strassen(firstResult, p6);
		c22 = Cal_Sub_Strassen(secondResult, p2);


		for (int i = 0; i < n / 2; i++)
		{
			for (int j = 0; j < n / 2; j++)
			{
				multiply[i][j] = c11[i][j];
				multiply[i][j + n / 2] = c12[i][j];
				multiply[i + n / 2][j] = c21[i][j];
				multiply[i + n / 2][j + n / 2] = c22[i][j];
			}
		}
	}

	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			cout << multiply[i][j] << " ";

		}
		cout << "\n";
	}

	return multiply;
}


int main()
{
	float cpu_time_used;
	clock_t start;
	clock_t stop;
	vector<vector<int>> first;
	vector<vector<int>> second;

	first.resize(rows, vector<int>(cols, 0));
	second.resize(rows, vector<int>(cols, 0));

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			first[i][j] = rand() % 10 ;
			second[i][j] = rand() % 10;
		}
	}
	cout << "Result of Iterative Multiplication is:\n";
	start = clock(); // start timer
	Iterative(first, second);
	stop = clock(); // end timer
	cpu_time_used = float(stop - start) / CLOCKS_PER_SEC; //time in seconds
	cout << "\nTime of Multiplication using iterative is:  " << cpu_time_used << endl;

	cout << "\n\nResult of Strassen Multiplication is:\n";
	start = clock(); // start timer
	Strassen(first, second);
	stop = clock(); // end timer
	cpu_time_used = float(stop - start) / CLOCKS_PER_SEC; //time in seconds
	cout << "\nTime of Multiplication using Strassen is:  " << cpu_time_used << endl;

	getchar();
	return 0;
}