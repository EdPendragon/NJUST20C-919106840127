#include <iostream>
#include <stdio.h>
#include <string>
using namespace std; 
string tiqu(string str,int a,int b) { //��ȡ�ַ������д�aλ��bλ���ַ���������ȥǰ�ŵ������ŵȹ���
	string ret="";
	if(a>b) return ret;
	for(int i=a; i<=b; i++) ret+=str[i];
	return ret;
}
bool xiaoyu(string a,string b) {			//�����жϴ������ֵ��ַ���a�Ƿ�С��b(��С���㣬�����Ǹ���)
	if(a.size()<b.size()) return true;
	else if(a.size()>b.size()) return false;
	else for(int i=0; i<a.size(); i++) {  //λ����ͬ
			if(a[i]<b[i]) return true;
			else if(a[i]>b[i]) return false;  //��λ�Ա�
		}
	return false;                        //˵��������ȣ���С�ڣ�false
}
bool xiaoshuxiaoyu(string a,string b){		//�����ж�С������a�Ƿ�С��b 
	int la=a.size(),lb=b.size(),max;
	if(la<=lb) max=lb;
	else max=la;							//la,lb�Ĵ�ֵ
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
string clear(string A) {    				//ȥ���ַ���ǰ�ߵĿ��㣬�ַ���ĩ�Ķ����㣬������ĸ���ת��Ϊ����������
	int dian=0,dianwei;
	string a=A;
	for(int i=0; i<a.size(); i++) {    //�ж��Ƿ���С����
		if(a[i]=='.') {
			dian=1;
			dianwei=i;
			break;
		}
	}
	if(dian) {  							//������С���㣬ȥ��ĩβ������㣬����ĩβֻ��0��ȥ��С����
		for(int i=a.size()-1; i>dianwei; i--) {
			if(a[i]!='0') break;
			if(a[i]=='0') a=tiqu(a,0,i-1);
		}
		if((a[dianwei+1]=='0'&&a.size()==dianwei+2)||(a.size()==dianwei+1)) {   //����С����֮��ֻ��һλ0��ֻ��С����
			a=tiqu(a,0,dianwei-1);
		}
	}
	int fuhao=0,fuhaowei;
	if(a[0]=='-') {
		fuhao=1,fuhaowei=0;             //fuhao��¼����������fuhaowei��¼ĩλ����
		for(int i=1; i<a.size(); i++) {
			if(a[i]=='-') {
				fuhao++;
				fuhaowei=i;
			} else break;
		}
		if(fuhao%2==0) a=tiqu(a,fuhaowei+1,a.size()-1);
		else a=tiqu(a,fuhaowei,a.size()-1);
	}
	int sf=0,j;							//sf��¼�׸���0Ԫ��λ��
	if(a[0]=='-') j=1;
	else j=0; 
	for(; j<a.size(); j++) {
		if(a[j]!='0') {
			sf=j;
			break;
		}
	}
	string tem1="",tem2="";
	if(a[0]=='-') tem1+="-";             //tem1��¼�������
	tem2+=tiqu(a,sf,a.size()-1);		//tem2��¼ȥ��ǰ�����õ�0����ַ���
	a=tem1+tem2;
	int ql=1;							//�ж��Ƿ�ȫ��0
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
