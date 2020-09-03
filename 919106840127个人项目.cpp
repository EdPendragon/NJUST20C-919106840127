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
double shibied(char str[],int i) {	//识别数字
	double sum=0;						//用来保存返回值
	int len=strlen(str);                 //字符串长度
	if(str[i]>='0'&&str[i]<='9'&&str[i+1]!='x'&&str[i+1]!='b'&&str[i+1]!='o') {      //十进制
		int t=i,dian=-1;					//dian用来保存小数点的位置
		for(; t<len; t++) {
			if((str[t]>'9'||str[t]<'0')&&str[t]!='.') break;
			if(str[t]=='.') dian=t;
		}
		t--;
		for(int j=i; j<=t; j++) {
			if(str[j]=='.') continue;
			sum*=10;
			sum+=str[j]-'0';
		}
		int tem=dian-t;                 //小数点距离最后一位的距离
		if(dian==-1) tem=0;				//假如没有小数点则tem为0，不计算
		for(int j=tem; j>0; j--)	sum/=10; //计算小数点
		return sum;
	}
	if(str[i]=='0'&&(str[i+1]=='b'||str[i+1]=='B')) {				  //二进制
		int t=i+2,dian=-1;					//dian用来保存小数点的位置
		for(; t<len; t++) {
			if((str[t]>'1'||str[t]<'0')&&str[t]!='.') break;
			if(str[t]=='.') dian=t;
		}
		t--;
		for(int j=i+2; j<=t; j++) {
			if(str[j]=='.') continue;
			sum*=2;
			sum+=str[j]-'0';
		}
		int tem=dian-t;					//小数点距离最后一位的距离
		if(dian==-1) tem=0;				//假如没有小数点则tem为0，不计算
		for(int j=tem; j>0; j--) sum/=2; //计算小数点
		return sum;
	}
	if(str[i]=='0'&&(str[i+1]=='o'||str[i+1]=='O')) {				  //八进制
		int t=i+2,dian=-1;					//dian用来保存小数点的位置
		for(; t<len; t++) {
			if((str[t]>'7'||str[t]<'0')&&str[t]!='.') break;
			if(str[t]=='.') dian=t;
		}
		t--;
		for(int j=i+2; j<=t; j++) {
			if(str[j]=='.') continue;
			sum*=8;
			sum+=str[j]-'0';
		}
		int tem=dian-t;					//小数点距离最后一位的距离
		if(dian==-1) tem=0;				//假如没有小数点则tem为0，不计算
		for(int j=tem; j>0; j--) sum/=8; //计算小数点
		return sum;
	}
	if(str[i]=='0'&&(str[i+1]=='x'||str[i+1]=='X')) {				  //十六进制
		int t=i+2,dian=-1;					//dian用来保存小数点的位置
		for(; t<len; t++) {
			if((str[t]>'9'||str[t]<'0')&&(str[t]<'a'&&str[t]>'f')&&str[t]!='.') break;
			if(str[t]=='.') dian=t;
		}
		t--;
		for(int j=t; j>=i; j--) {
			if(j==dian) continue;
			sum*=16;
			if(str[j]>='0'&&str[j]<='9') sum+=str[j]-'0';
			else if(str[j]>='a'&&str[j]<='f') sum+=10+str[j]-'a';
		}
		int tem=dian-t;					//小数点距离最后一位的距离
		if(dian==-1) tem=0;				//假如没有小数点则tem为0，不计算
		for(int j=tem; j>0; j--) sum/=16; //计算小数点
		return sum;
	}
}
int main() {
	char instr[60];						//以字符串的形式输入运算式（暂时只用于四则运算）
	while(cin>>instr) {
		if(instr[0]=='O'&&instr[1]=='F'&&instr[2]=='F') break;  //输入OFF退出
		double calstr1[60];      //将字符串内的操作数转化为double保存在数组1中
		int k=0,n=strlen(instr),n1;          //n是字符串长度，n1用来保存转化为double之后的长度
		for(int i=0; i<n;i++) {
			if(instr[i]>='0'&&instr[i]<='9') {            //保存第0，2，4，6，8……位的操作数
				calstr1[k++]=shibied(instr,i);
				for(int j=i+1; j<n; j++) {
					if(instr[j]=='+'||instr[j]=='-'||instr[j]=='*'||instr[j]=='/') {
						i=j-1;
						break;
					}
				}
				continue;
			} else if(instr[i]=='+'||instr[i]=='-'||instr[i]=='*'||instr[i]=='/') {
				if(instr[i]=='*') calstr1[k++]=1;
				else if(instr[i]=='/') calstr1[k++]=2;
				else if(instr[i]=='+') calstr1[k++]=3;
				else if(instr[i]=='-') calstr1[k++]=4;  //区分开四则运算符号，乘除优先级高，加减优先级低
			}
		}
		n1=k;
		arithmetic szys;		//创建四则运算类的一个对象，用来得到每一步计算的数值
		for(int i=0; i<n1; i++) { //计算乘除
			if((i%2!=1)||calstr1[i]==3||calstr1[i]==4) continue;
			else if(calstr1[i]==1||calstr1[i]==2) {
				szys.seta(calstr1[i-1]);
				szys.setb(calstr1[i+1]);
				if(calstr1[i]==1) szys.setfu('*');
				else szys.setfu('/');
				calstr1[i-1]=szys.cal();  //将calstr1的第i-1与i+1项的运算结果保存在i-1的位置
				int te=i;
				for(; te<n1-2; te++)	calstr1[te]=calstr1[te+2]; //每一项向前提2位
				n1-=2;  //长度减2
				i--;	//i退回一位
			}
		}
		for(int i=0; i<n1; i++) { //计算加减
			if(i%2!=1) continue;
			else {
				szys.seta(calstr1[i-1]);
				szys.setb(calstr1[i+1]);
				if(calstr1[i]=='3') szys.setfu('+');
				else szys.setfu('-');
				calstr1[i-1]=szys.cal();	//将calstr1的第i-1与i+1项的运算结果保存在i-1的位置
				int te=i;
				for(; te<n1-2; te++) calstr1[te]=calstr1[te+2]; //每一项向前提2位
				n1-=2;
				i--;
			}
		}
		cout<<"本次计算结果为"<<calstr1[0]<<endl; //因为每计算一次就会向前退两位，故最终只剩下calstr1[0]即为答案
	}
	return 0;
}
