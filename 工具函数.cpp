#include <iostream>
#include <stdio.h>
#include <string>
using namespace std; 
string tiqu(string str,int a,int b) { //提取字符串串中从a位到b位的字符，可用于去前放的正负号等功能
	string ret="";
	if(a>b) return ret;
	for(int i=a; i<=b; i++) ret+=str[i];
	return ret;
}
bool xiaoyu(string a,string b) {			//用于判断代表数字的字符串a是否小于b(无小数点，不考虑负号)
	if(a.size()<b.size()) return true;
	else if(a.size()>b.size()) return false;
	else for(int i=0; i<a.size(); i++) {  //位数相同
			if(a[i]<b[i]) return true;
			else if(a[i]>b[i]) return false;  //按位对比
		}
	return false;                        //说明二者相等，不小于，false
}
bool xiaoshuxiaoyu(string a,string b){		//用于判断小数部分a是否小于b 
	int la=a.size(),lb=b.size(),max;
	if(la<=lb) max=lb;
	else max=la;							//la,lb的大值
	for(int i=0;i<max;i++){
		int na,nb;
		if(i<la) na=a[i];
		else na=0;
		if(i<lb) nb=b[i];
		else nb=0;
		if(na<nb) return true;
		else if(nb<na) return false;
		else continue;
	}
	return false;
}
string clear(string A) {    				//去除字符串前边的空零，字符串末的多余零，将多余的负号转化为单个或正号
	int dian=0,dianwei;
	string a=A;
	for(int i=0; i<a.size(); i++) {    //判断是否有小数点
		if(a[i]=='.') {
			dian=1;
			dianwei=i;
			break;
		}
	}
	if(dian) {  							//假如有小数点，去除末尾多余的零，假如末尾只有0，去除小数点
		for(int i=a.size()-1; i>dianwei; i--) {
			if(a[i]!='0') break;
			if(a[i]=='0') a=tiqu(a,0,i-1);
		}
		if((a[dianwei+1]=='0'&&a.size()==dianwei+2)||(a.size()==dianwei+1)) {   //假如小数点之后只有一位0或只有小数点
			a=tiqu(a,0,dianwei-1);
		}
	}
	int fuhao=0,fuhaowei;
	if(a[0]=='-') {
		fuhao=1,fuhaowei=0;             //fuhao记录负号数量，fuhaowei记录末位负号
		for(int i=1; i<a.size(); i++) {
			if(a[i]=='-') {
				fuhao++;
				fuhaowei=i;
			} else break;
		}
		if(fuhao%2==0) a=tiqu(a,fuhaowei+1,a.size()-1);
		else a=tiqu(a,fuhaowei,a.size()-1);
	}
	int sf=0,j;							//sf记录首个非0元素位置
	if(a[0]=='-') j=1;
	else j=0; 
	for(; j<a.size(); j++) {
		if(a[j]!='0') {
			sf=j;
			break;
		}
	}
	string tem1="",tem2="";
	if(a[0]=='-') tem1+="-";             //tem1记录负号情况
	tem2+=tiqu(a,sf,a.size()-1);		//tem2记录去除前方无用的0后的字符串
	a=tem1+tem2;
	int ql=1;							//判断是否全是0
	for(int i=0;i<a.size();i++){
		if(a[i]!='0'){
			ql=0;
			break;
		}
	}
	if(ql) a="0";
	if(a[0]=='.') a="0"+a;
	return a;
}
