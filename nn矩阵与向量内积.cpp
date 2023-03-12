#include<iostream>
#include <windows.h>
#include <stdlib.h>
using namespace std;
LARGE_INTEGER frequency;
int main()
{
	int n = 0;
	cin >> n;
	//Initialize array a and b
	int* a = new int[n];
	for (int i = 0;i < n;i++)
		a[i] = i;
	int** b = new int* [n];
	for (int i = 0;i < n;i++)
	{
		b[i] = new int[n];
		for (int j = 0;j < n;j++)
			b[i][j] = i + j;
	}

	int* sum = new int[n];

	double dff, begin_, _end, time;
	QueryPerformanceFrequency(&frequency);//���ʱ��Ƶ��
	dff = (double)frequency.QuadPart;//ȡ��Ƶ��
	QueryPerformanceCounter(&frequency);
	begin_ = frequency.QuadPart;//��ó�ʼֵ

	for (int h = 0;h < 100;h++)//ִ��100��
	{
		//ƽ���㷨
		for (int i = 0; i < n; i++) {
			sum[i] = 0.0;
			for (int j = 0; j < n; j++)
				sum[i] += b[j][i] * a[j];
		}

		//cache�Ż��㷨
		for (int i = 0; i < n; i++)
			sum[i] = 0.0;
		for (int j = 0; j < n; j++)
			for (int i = 0; i < n; i++)
				sum[i] += b[j][i] * a[j];

		//cache�Ż��㷨 + unroll
		if (n % 2 == 0)
		{
			for (int i = 0; i < n; i++)
				sum[i] = 0.0;
			for (int j = 0; j < n; j++)
			{
				for (int i = 0; i < n; i += 2)
				{
					sum[i] += b[j][i] * a[j];
					sum[i + 1] += b[j][i + 1] * a[j];
				}
			}
		}
		else
		{
			for (int i = 0; i < n; i++)
				sum[i] = 0.0;
			for (int j = 0; j < n; j++)
			{
				for (int i = 0; i < n - 1; i += 2)
				{
					sum[i] += b[j][i] * a[j];
					sum[i + 1] += b[j][i + 1] * a[j];
				}
				sum[n - 1] += b[j][n - 1] * a[j];
			}
		}
	}

	QueryPerformanceCounter(&frequency);
	_end = frequency.QuadPart;//�����ֵֹ
	time = (_end - begin_) / dff;//��ֵ����Ƶ�ʵõ�ʱ��(ms)
	cout << time *1000 << "ms" << endl;

	return 0;
}
