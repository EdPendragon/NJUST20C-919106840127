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
double shibied(char str[],int i) {	//ʶ������
	double sum=0;						//�������淵��ֵ
	int len=strlen(str);                 //�ַ�������
	if(str[i]>='0'&&str[i]<='9'&&str[i+1]!='x'&&str[i+1]!='b'&&str[i+1]!='o') {      //ʮ����
		int t=i,dian=-1;					//dian��������С�����λ��
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
		int tem=dian-t;                 //С����������һλ�ľ���
		if(dian==-1) tem=0;				//����û��С������temΪ0��������
		for(int j=tem; j>0; j--)	sum/=10; //����С����
		return sum;
	}
	if(str[i]=='0'&&(str[i+1]=='b'||str[i+1]=='B')) {				  //������
		int t=i+2,dian=-1;					//dian��������С�����λ��
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
		int tem=dian-t;					//С����������һλ�ľ���
		if(dian==-1) tem=0;				//����û��С������temΪ0��������
		for(int j=tem; j>0; j--) sum/=2; //����С����
		return sum;
	}
	if(str[i]=='0'&&(str[i+1]=='o'||str[i+1]=='O')) {				  //�˽���
		int t=i+2,dian=-1;					//dian��������С�����λ��
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
		int tem=dian-t;					//С����������һλ�ľ���
		if(dian==-1) tem=0;				//����û��С������temΪ0��������
		for(int j=tem; j>0; j--) sum/=8; //����С����
		return sum;
	}
	if(str[i]=='0'&&(str[i+1]=='x'||str[i+1]=='X')) {				  //ʮ������
		int t=i+2,dian=-1;					//dian��������С�����λ��
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
		int tem=dian-t;					//С����������һλ�ľ���
		if(dian==-1) tem=0;				//����û��С������temΪ0��������
		for(int j=tem; j>0; j--) sum/=16; //����С����
		return sum;
	}
}
int main() {
	char instr[60];						//���ַ�������ʽ��������ʽ����ʱֻ�����������㣩
	while(cin>>instr) {
		if(instr[0]=='O'&&instr[1]=='F'&&instr[2]=='F') break;  //����OFF�˳�
		double calstr1[60];      //���ַ����ڵĲ�����ת��Ϊdouble����������1��
		int k=0,n=strlen(instr),n1;          //n���ַ������ȣ�n1��������ת��Ϊdouble֮��ĳ���
		for(int i=0; i<n;i++) {
			if(instr[i]>='0'&&instr[i]<='9') {            //�����0��2��4��6��8����λ�Ĳ�����
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
				else if(instr[i]=='-') calstr1[k++]=4;  //���ֿ�����������ţ��˳����ȼ��ߣ��Ӽ����ȼ���
			}
		}
		n1=k;
		arithmetic szys;		//���������������һ�����������õ�ÿһ���������ֵ
		for(int i=0; i<n1; i++) { //����˳�
			if((i%2!=1)||calstr1[i]==3||calstr1[i]==4) continue;
			else if(calstr1[i]==1||calstr1[i]==2) {
				szys.seta(calstr1[i-1]);
				szys.setb(calstr1[i+1]);
				if(calstr1[i]==1) szys.setfu('*');
				else szys.setfu('/');
				calstr1[i-1]=szys.cal();  //��calstr1�ĵ�i-1��i+1���������������i-1��λ��
				int te=i;
				for(; te<n1-2; te++)	calstr1[te]=calstr1[te+2]; //ÿһ����ǰ��2λ
				n1-=2;  //���ȼ�2
				i--;	//i�˻�һλ
			}
		}
		for(int i=0; i<n1; i++) { //����Ӽ�
			if(i%2!=1) continue;
			else {
				szys.seta(calstr1[i-1]);
				szys.setb(calstr1[i+1]);
				if(calstr1[i]=='3') szys.setfu('+');
				else szys.setfu('-');
				calstr1[i-1]=szys.cal();	//��calstr1�ĵ�i-1��i+1���������������i-1��λ��
				int te=i;
				for(; te<n1-2; te++) calstr1[te]=calstr1[te+2]; //ÿһ����ǰ��2λ
				n1-=2;
				i--;
			}
		}
		cout<<"���μ�����Ϊ"<<calstr1[0]<<endl; //��Ϊÿ����һ�ξͻ���ǰ����λ��������ֻʣ��calstr1[0]��Ϊ��
	}
	return 0;
}
