#include <iostream>
#include <ctime>
#include <vector>
#include <stdlib.h>

using namespace std;
typedef int Numtype;

void printvector_2d(int row, int column, vector<vector<Numtype>> v_in);
void printvector_1d(vector<Numtype> v_in);
void inintial_vector(int row, int column, vector <vector<Numtype>> &m);
int min(int num_1, int num_2);
int MPS_RE(vector<vector<Numtype>> m, int I, int J);
int DP_MPS_UD(vector<vector<Numtype>> m, vector<vector<Numtype>> &r, int I, int J);
int DP_MPS_BU(vector<vector<Numtype>> m, vector<vector<Numtype>> &r, int row, int column);
int DP_MPS_BU2l(vector<vector<Numtype>> m, vector<vector<Numtype>> &r, int row, int column);
int DP_MPS_BU1l(vector<vector<Numtype>> m, vector<Numtype> &r, int row, int column);

int main()
{
	int row, column, temp;
	int result_re, result_DP_UD, result_DP_BU, result_DP_BU1l, result_DP_BU2l;
	clock_t start_time, end_time;
	double cost_time = 0;
	srand(1); //固定随机数种子
	cout << "请输入行数与列数\n";
	scanf_s("%d %d", &row, &column);
	if (column <= row)
	{
		temp = column;
	}
	else temp = row;
	vector<vector<Numtype>> r_dp_ud(row, vector<Numtype>(column, -1));
	vector<vector<Numtype>> r_dp_bu(row, vector<Numtype>(column));
	vector<vector<Numtype>> graph(row, vector<Numtype>(column));
	vector<vector<Numtype>>r_dp_bu2l(2, vector<Numtype>(temp));
	vector<Numtype>r_dp_bu1l(temp);
	inintial_vector(row, column, graph); //初始化网格图
	//以下使用递归
	start_time = clock();
	result_re = MPS_RE(graph, row, column);
	end_time = clock();
	cost_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	cout << "递归求得的最小路径和为：" << result_re << endl << "递归使用的时间为：" << cost_time << "s\n" << endl;
	
	//以下使用自顶向下动态规划
	start_time = clock();
	result_DP_UD = DP_MPS_UD(graph, r_dp_ud, row, column);
	end_time = clock();
	cost_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	cout << "自顶向下DP求得的最小路径和为：" << result_DP_UD << endl << "自顶向下DP使用的时间为：" << cost_time << "s\n" << endl;
	//以下使用自底向上动态规划
	start_time = clock();
	result_DP_BU = DP_MPS_BU(graph, r_dp_bu, row, column);
	end_time = clock();
	cost_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	cout << "自底向上DP求得的最小路径和为：" << result_DP_BU << endl << "自底向上DP使用的时间为：" << cost_time << "s\n" << endl;
	//以下使用自底向上动态规划（两行的动态表）
	start_time = clock();
	result_DP_BU2l = DP_MPS_BU2l(graph, r_dp_bu2l, row, column);
	end_time = clock();
	cost_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	cout << "自底向上DP使用两行动态表求得的最小路径和为：" << result_DP_BU2l << endl << "自底向上DP使用两行动态表的时间为：" << cost_time << "s\n" << endl;
	//以下使用自底向上动态规划（单行的动态表）
	start_time = clock();
	result_DP_BU1l = DP_MPS_BU1l(graph, r_dp_bu1l, row, column);
	end_time = clock();
	cost_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	cout << "自底向上DP使用单行动态表求得的最小路径和为：" << result_DP_BU1l << endl << "自底向上DP使用单行动态表的时间为：" << cost_time << "s\n" << endl;
	system("pause");
	return 0;
}


//二维数组输出函数
void printvector_2d(int row, int column, vector<vector<Numtype>> v_in)
{
	int a = 0, b = 0;
	for (a; a < row; a++)
	{
		for (b = 0; b < column; b++)
		{
			cout << v_in[a][b] << " ";
		}
		cout << "\n";
	}
}

//一维数组输出函数
void printvector_1d(vector<Numtype> v_in)
{
	int a = 0, b = 0;
	for (a; a < v_in.size(); a++)
	{
		cout << v_in[a] << " ";
	}
	cout << "\n";
}

//对网格图进行初始化
void inintial_vector(int row, int column, vector <vector<Numtype>> &m)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			m[i][j] = rand() % 100;
		}
	}
}

//求最小值函数
int min(int num_1, int num_2)
{
	if (num_1 > num_2) return num_2;
	else return num_1;
}

//递归实现MCS
int MPS_RE(vector<vector<Numtype>> m, int I, int J)
{
	int i = I - 1;
	int j = J - 1;
	int r;
	if (i == 0 && j == 0)
	{
		return m[i][j];
	}
	if (i > 0 && j > 0)
	{
		r = min(MPS_RE(m, I - 1, J), MPS_RE(m, I, J - 1)) + m[i][j];
	}
	else if (i == 0)
	{
		r = MPS_RE(m, I, J - 1) + m[i][j];
	}
	else
	{
		r = MPS_RE(m, I - 1, J) + m[i][j];
	}
	return r;
}

//带memo的DP
int DP_MPS_UD(vector<vector<Numtype>> m, vector<vector<Numtype>> &r, int I, int J)
{
	int i = I - 1;
	int j = J - 1;
	if (i == 0 && j == 0)
	{
		return m[i][j];
	}
	if (r[i][j] == -1)
	{
		if (i > 0 && j > 0)
		{
			r[i][j] = min(DP_MPS_UD(m, r, I - 1, J), DP_MPS_UD(m, r, I, J - 1)) + m[i][j];
		}
		else if (i == 0)
		{
			r[i][j] = DP_MPS_UD(m, r, I, J - 1) + m[i][j];
		}
		else
		{
			r[i][j] = DP_MPS_UD(m, r, I - 1, J) + m[i][j];
		}
		return r[i][j];
	}
	else return r[i][j];
}

//自底向上的DP
int DP_MPS_BU(vector<vector<Numtype>> m, vector<vector<Numtype>> &r, int row, int column)
{
	int i, j;
	r[0][0] = m[0][0];
	for (j = 1; j < column; j++)
	{
		r[0][j] = r[0][j - 1] + m[0][j];
	}

	for (i = 1; i < row; i++)
	{
		r[i][0] = r[i - 1][0] + m[i][0];
	}
	for (i = 1; i < row; i++)
	{
		for (j = 1; j < column; j++)
		{
			r[i][j] = min(r[i - 1][j], r[i][j - 1]) + m[i][j];
		}
	}
	return r[row - 1][column - 1];
}

//自底向上使用两行的DP
int DP_MPS_BU2l(vector<vector<Numtype>> m, vector<vector<Numtype>> &r, int row, int column)
{
	int i, j;
	if (column <= row)
	{
		r[0][0] = m[0][0];
		for (j = 1; j < column; j++)
		{
			r[0][j] = r[0][j - 1] + m[0][j];
		}
		for (i = 1; i < row; i++)
		{
			r[i % 2][0] = r[(i - 1) % 2][0] + m[i][0];
			for (j = 1; j < column; j++)
			{
				r[i % 2][j] = min(r[(i - 1) % 2][j], r[i % 2][j - 1]) + m[i][j];
			}
		}
		return r[(row - 1) % 2][column - 1];
	}
	else
	{
		r[0][0] = m[0][0];
		for (i = 1; i < row; i++)
		{
			r[0][i] = r[0][i - 1] + m[i][0];
		}
		for (j = 1; j < column; j++)
		{
			r[j % 2][0] = r[(j - 1) % 2][0] + m[0][j];
			for (i = 1; i < row; i++)
			{
				r[j % 2][i] = min(r[(j - 1) % 2][i], r[j % 2][i - 1]) + m[i][j];
			}
		}
		return r[(column - 1) % 2][row - 1];
	}
}

//自底向上使用一行的DP
int DP_MPS_BU1l(vector<vector<Numtype>> m, vector<Numtype> &r, int row, int column)
{
	int i, j;
	if (column <= row)
	{
		r[0] = m[0][0];
		for (j = 1; j < column; j++)
		{
			r[j] = r[j - 1] + m[0][j];
		}
		for (i = 1; i < row; i++)
		{
			r[0] = r[0] + m[i][0];
			for (j = 1; j < column; j++)
			{
				r[j] = min(r[j], r[j - 1]) + m[i][j];
			}
		}
		return r[column - 1];
	}
	else
	{
		r[0] = m[0][0];
		for (i = 1; i < row; i++)
		{
			r[i] = r[i - 1] + m[i][0];
		}
		for (j = 1; j < column; j++)
		{
			r[0] = r[0] + m[0][j];
			for (i = 1; i < row; i++)
			{
				r[i] = min(r[i], r[i - 1]) + m[i][j];
			}
		}
		return r[row - 1];
	}
}