#include <iostream>
#include <stdio.h>
#include <cstring>						//本程序采用字符串输入，通过关键字识别出操作数与运算符 
using namespace std;
class arithmetic {						//四则运算 
	private:							
		double a;						//左操作数 
		double b;						//右操作数 
		char fu;						//+，-，*，/ 
	public:
		double seta(double ina);
		double setb(double inb);
		char setfu(char infu);			//以上三个函数为设置数据 
		double cal();					//计算 
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
double arithmetic::cal() {              //根据不同运算符进行不同运算 
	if(fu=='+') return a+b;
	if(fu=='-') return a-b;
	if(fu=='*') return a*b;
	if(fu=='/') return a/b;
}
double shibied(char str[],int i)		//识别数字
{
	double sum=0;						//用来保存返回值 
	if(str[i]>='0'&&str[i]<='9'&&str[i+1]>='0'&&str[i+1]<='9')        //十进制 
	{
		int t=i+1,dian;					//dian用来保存小数点的位置 
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
		int tem=dian-t;                 //小数点距离最后一位的距离
		for(int j=tem;j>0;j--)	sum/=10;//计算小数 点 
		return sum;
	}
} 
