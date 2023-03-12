#include<iostream>
#include <windows.h>
#include <stdlib.h>
using namespace std;
LARGE_INTEGER frequency;
void rec(int n, int* a)
{
	if (n == 1)
		return;
	else
	{
		for (int i = 0; i < n / 2; i++)
			a[i] += a[n - i - 1];
		n = n / 2;
		rec(n,a);
	}
}
void add(int* a, int n)
{
	for (int h = 0;h < 100;h++)//测运行100次的时间
	{
		int sum = 0;
		// 链式：将给定元素依次累加到结果变量即可
		for (int i = 0; i < n; i++)
			sum += a[i];

		 //双链路式
		int sum1 = 0, sum2 = 0;
		for (int i = 0;i < n; i += 2) {
			sum1 += a[i];
			sum2 += a[i + 1];
		}
		sum = sum1 + sum2;

		// 四链路式
		int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
		for (int i = 0;i < n; i += 4) {
			sum1 += a[i];
			sum2 += a[i + 1];
			sum3 += a[i + 2];
			sum4 += a[i + 3];
		}
		sum = sum1 + sum2 + sum3 + sum4;


		//递归
		rec(n, a);

		//实现方式2：二重循环
		for (int m = n; m > 1; m /= 2) // log(n)个步骤
			for (int i = 0; i < m / 2; i++)
				a[i] = a[i * 2] + a[i * 2 + 1];// 相邻元素相加连续存储到数组最前面
		// a[0]为最终结果

	}
}
int main()
{
	int n=0;
	int* tp = new int[21];//记录待测的n，2^3-2^23
	for (int i = 0,j = 8;i < 21;i++)
	{
		tp[i] = j;
		j *= 2;
	}
	for (int c = 0;c < 21;c++)//自动测试n从2^3到2^23
	{
		n = tp[c];
		int* a = new int[n];
		for (int i = 0;i < n;i++)
			a[i] = i;
		double dff=0, begin_=0, _end=0, time=0;
		QueryPerformanceFrequency(&frequency);//获得时钟频率
		dff = (double)frequency.QuadPart;//取得频率
		QueryPerformanceCounter(&frequency);
		begin_ = frequency.QuadPart;//获得初始值
		
		add(a, n);

		QueryPerformanceCounter(&frequency);
		_end = frequency.QuadPart;//获得终止值
		time = (_end - begin_) / dff;//差值除以频率得到时间
		cout << time * 1000 << endl;
	}
	return 0;
}
