#include <iostream>
#include <string.h>
#include <cstring>
#include <stdio.h>
using namespace std;
string jiafa(string a,string b) {
	if(a.size()<b.size()) {	//ȷ��λ���ϴ���ַ���Ϊa
		string t=a;
		a=b;
		b=t;	//����
	}
	int la=a.size(),lb=b.size(),flag=0,na,nb;          //flag�жϽ�λ,naΪa��ǰλ���֣�nbΪb��ǰλ����
	while(la>0) {
		na=a[la-1]-'0';		//��ȡa��ǰ����
		if(lb>0) nb=b[lb-1]-'0';		//��ȡb��ǰ����
		else nb=0;        //����Ϊ0
		int sum=na+nb+flag;	//��Ϊa��b��ǰ��ֵ���Ͻ�λ
		if(sum>=10) {
			a[la-1]='0'+sum%10;		//���ʹ���ڽϳ����ַ����ϣ���a
			flag=1;		//��λ
		} else {
			a[la-1]='0'+sum;     //���ʹ���ڽϳ����ַ����ϣ���b
			flag=0;    //����λ
		}
		la--;
		lb--;
	}
	if(flag==1) a="1"+a;
	return a;
}
int main() {
	string test1,test2;
	cin>>test1>>test2;
	cout<<jiafa(test1,test2);
	return 0;
}
