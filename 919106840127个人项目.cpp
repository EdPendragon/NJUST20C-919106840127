#include <iostream>
#include <string.h>
#include <cstring>
#include <stdio.h>
using namespace std;
string jiafa(string a,string b) {
	if(a.size()<b.size()) {	//确保位数较大的字符串为a
		string t=a;
		a=b;
		b=t;	//交换
	}
	int la=a.size(),lb=b.size(),flag=0,na,nb;          //flag判断进位,na为a当前位数字，nb为b当前位数字
	while(la>0) {
		na=a[la-1]-'0';		//获取a当前数字
		if(lb>0) nb=b[lb-1]-'0';		//获取b当前数字
		else nb=0;        //否则为0
		int sum=na+nb+flag;	//和为a，b当前的值加上进位
		if(sum>=10) {
			a[la-1]='0'+sum%10;		//将和存放在较长的字符串上，即a
			flag=1;		//进位
		} else {
			a[la-1]='0'+sum;     //将和存放在较长的字符串上，即b
			flag=0;    //不进位
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
