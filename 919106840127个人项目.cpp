#include <iostream>
#include <stdio.h>
#include <cstring>						//����������ַ������룬ͨ���ؼ���ʶ���������������� 
using namespace std;
class arithmetic {						//�������� 
	private:							
		double a;						//������� 
		double b;						//�Ҳ����� 
		char fu;						//+��-��*��/ 
	public:
		double seta(double ina);
		double setb(double inb);
		char setfu(char infu);			//������������Ϊ�������� 
		double cal();					//���� 
};
double arithmetic::seta(double ina) {
	a=ina;
}
double arithmetic::setb(double inb) {
	b=inb;
}
char arithmetic::setfu(char infu) {
	fu=infu;
}
double arithmetic::cal() {              //���ݲ�ͬ��������в�ͬ���� 
	if(fu=='+') return a+b;
	if(fu=='-') return a-b;
	if(fu=='*') return a*b;
	if(fu=='/') return a/b;
}
double shibied(char str[],int i)		//ʶ������
{
	double sum=0;						//�������淵��ֵ 
	if(str[i]>='0'&&str[i]<='9'&&str[i+1]>='0'&&str[i+1]<='9')        //ʮ���� 
	{
		int t=i+1,dian;					//dian��������С�����λ�� 
		for(t=i+1;str[t]!='\0';t++)
		{
			if((str[t]>'9'||str[t]<'0')&&str[t]!='.') break;
			if(str[t]=='.') dian=t;
		}
		t--;
		for(int j=t;j>=i;j--)
		{
			sum*=10;
			sum+=str[j]-'0';
		}
		int tem=dian-t;                 //С����������һλ�ľ���
		for(int j=tem;j>0;j--)	sum/=10;//����С�� �� 
		return sum;
	}
} 
