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
	for (int h = 0;h < 100;h++)//������100�ε�ʱ��
	{
		int sum = 0;
		// ��ʽ��������Ԫ�������ۼӵ������������
		for (int i = 0; i < n; i++)
			sum += a[i];

		 //˫��·ʽ
		int sum1 = 0, sum2 = 0;
		for (int i = 0;i < n; i += 2) {
			sum1 += a[i];
			sum2 += a[i + 1];
		}
		sum = sum1 + sum2;

		// ����·ʽ
		int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
		for (int i = 0;i < n; i += 4) {
			sum1 += a[i];
			sum2 += a[i + 1];
			sum3 += a[i + 2];
			sum4 += a[i + 3];
		}
		sum = sum1 + sum2 + sum3 + sum4;


		//�ݹ�
		rec(n, a);

		//ʵ�ַ�ʽ2������ѭ��
		for (int m = n; m > 1; m /= 2) // log(n)������
			for (int i = 0; i < m / 2; i++)
				a[i] = a[i * 2] + a[i * 2 + 1];// ����Ԫ����������洢��������ǰ��
		// a[0]Ϊ���ս��

	}
}
int main()
{
	int n=0;
	int* tp = new int[21];//��¼�����n��2^3-2^23
	for (int i = 0,j = 8;i < 21;i++)
	{
		tp[i] = j;
		j *= 2;
	}
	for (int c = 0;c < 21;c++)//�Զ�����n��2^3��2^23
	{
		n = tp[c];
		int* a = new int[n];
		for (int i = 0;i < n;i++)
			a[i] = i;
		double dff=0, begin_=0, _end=0, time=0;
		QueryPerformanceFrequency(&frequency);//���ʱ��Ƶ��
		dff = (double)frequency.QuadPart;//ȡ��Ƶ��
		QueryPerformanceCounter(&frequency);
		begin_ = frequency.QuadPart;//��ó�ʼֵ
		
		add(a, n);

		QueryPerformanceCounter(&frequency);
		_end = frequency.QuadPart;//�����ֵֹ
		time = (_end - begin_) / dff;//��ֵ����Ƶ�ʵõ�ʱ��
		cout << time * 1000 << endl;
	}
	return 0;
}
