//!!!!!!!ע�⣺ĿǰС��������Ȼ�кܴ��bug��������������Ȼ��С覴ã�9��6�ղ�Ҫ����bug���� 
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
bool xiaoyu(string a,string b) { //�ú��������ж����ַ�����С
	if(a.size()<b.size()) return true;
	else if(a.size()>b.size()) return false;
	else {
		for(int i=0; i<a.size()-1; i++) {
			if(a[i]<b[i]) return true;
			else if(a[i]>b[i]) return false;
			else continue;
		}
		if(a[a.size()-1]>=b[b.size()-1]) return false;
		if(a[a.size()-1]<b[b.size()-1]) return true;
	}
}
bool dengyu(string A,string B) { //�ú��������ж����ַ����������
	string a=A,b=B;
	if(a.size()!=b.size()) return false;
	for(int i=0; i<a.size(); i++) {
		if(a[i]!=b[i]) return false;
	}
	return true;
}
string quling(string str) {   //�˺�������ȥ���ַ�����0
	int sf=0;		//�׸���0��Ԫ��λ��
	if(str[0]=='-') sf=1;
	for(int i=sf; i<str.size(); i++) {
		if(str[i]!='0') {
			sf=i;
			break;
		}
	}
	string jie="";
	if(str[0]=='-') jie+="-";
	for(int i=sf; i<str.size(); i++) jie+=str[i];
	return jie;
}
string clear(string str) {   //�˺�������ȥ��С������β0,���ҽ��ַ���ǰ��--���+
	int youdian=0;	//���Ƿ���С����
	for(int i=0; i<str.size(); i++) {
		if(str[i]=='.') youdian=1;
	}
	if(youdian==0) return str;
	int biao=str.size()-1;
	string jie="";
	for(int i=str.size()-1; i>=0; i--) {
		if(str[i]=='0') continue;
		else {
			biao=i;
			break;
		}
	}
	int j=0;
	if(str[0]=='-'&&str[1]=='-') j=2;
	if(biao==str.size()-1) {
		for(; j<str.size(); j++) {
			jie+=str[j];
		}
	} else {
		for(; j<=biao; j++) {
			jie+=str[j];
		}
	}
	return jie;
}
string jianfa(string A,string B) {
	string a=A,b=B,a1="",a2="",b1="",b2="";  	//��a��b����A��B�������㣬a1��a2Ϊa��С����ǰ�������֣�b1��b2ͬ��
	a=clear(a);
	b=clear(b);
	a=quling(a);
	b=quling(b);
	if(dengyu(a,b)) return "0";
	int diana,dianb,la1,la2,lb1,lb2; //diana,dianb������¼a��bС����λ�ã�la1��la2��¼a��С����ǰ��С�����λ�ã�lb1��lb2ͬ��
	int pa=0,pb=0;		//�����ж�a��b�Ƿ���С����
	for(int i=0; i<a.size(); i++) if(a[i]=='.') {
			diana=i;
			pa=1;
			break;		//��¼a��С����λ��
		}
	for(int i=0; i<b.size(); i++) if(b[i]=='.') {
			dianb=i;
			pb=1;
			break;		//��¼b��С����λ��
		}
	if(pa==1&&pb==0) b=b+".0";
	else if(pa==0&&pb==1) a=a+".";		//����ֻ��һ���ַ���û��С�������������С����0
	else if(pa==0&&pb==0) {			//���������������
		string jieguo="";
		if(xiaoyu(a,b)) {     //����aС��b
			string tem=a;
			a=b;
			b=tem;
			jieguo="-"+jieguo;
		}
		int flag=0,la=a.size(),lb=b.size();  //flag��¼��λ�����la��lb��¼a��b�ĳ���
		while(la>0) {
			int na=a[la-1]-'0',nb;	//na����a��ǰ���֣�nb����b��ǰ���ֻ���0
			if(lb>0) nb=b[lb-1]-'0';
			else nb=0;
			if(na>=nb) {
				a[la-1]='0'+na-nb;
				flag=0;
			} else {
				a[la-1]='0'+na+10-nb;
				flag=1;
			}
			if(flag) a[la-2]--;		//����flag˵���˴������λ�ˣ���ǰһλ��Ҫ��һ
			la--;
			lb--;					//׼��������һλ����
		}
		jieguo+=a;
		jieguo=clear(jieguo);
		jieguo=quling(jieguo);
		if(a[0]=='-'&&b[0]=='-') jieguo="-"+jieguo;
		jieguo=clear(jieguo);
		return jieguo;
	}
	for(int i=0; i<diana; i++) a1+=a[i];		//��a[0]��a[diana-1]��¼Ϊa1
	for(int i=diana+1; i<a.size(); i++) a2+=a[i];		//��a[diana+1]�����һλ��¼Ϊa2
	for(int i=0; i<dianb; i++) b1+=b[i];		//��b[0]��b[dianb-1]��¼Ϊb1
	for(int i=dianb+1; i<b.size(); i++) b2+=b[i];		//��b[dianb+1]�����һλ��¼Ϊb2
	string jieguo="";
	if(xiaoyu(a1,b1)) { //����a1С��b1
		string tem=b1;
		b1=a1;
		a1=tem;
		jieguo="-"+jieguo;
		tem=b2;
		b2=a2;
		a2=tem;
	}
	int flag=0,xiaohou,flag_=0;   //С�����С������λ�����������ַ���С�����ֳ�����һ��
	la2=a2.size(),lb2=b2.size();//flag��¼��λ�����la1,lb1��¼a1��b1�ĳ���,flag_�ж�С����ǰ��һλ�Ƿ���ҪΪС������һλ��λ
	if(la2>lb2) xiaohou=la2;
	else xiaohou=lb2;
	while(xiaohou>0) {
		int na2,nb2,jiana=0,jianb=0;	//�ж��Ƿ�Ҫla2��lb2--
		if(xiaohou==la2) {		//���統ǰλ�ÿɼ�
			na2=a2[la2-1]-'0';
			jiana=1;
		} else na2=0;
		if(xiaohou==lb2) {		//���統ǰλ�ÿɼ�
			nb2=b2[lb2-1]-'0';
			jianb=1;
		} else nb2=0;
		if(la1==1) {				//����С������һλ�����
			if(na2>nb2) {
				a2[la2-1]='0'+na2-nb2;
				flag_=0;
			} else {
				a2[la2-1]='0'+na2-nb2+10;
				flag_=1;
			}						//���ϼ��н��м���
			if(flag_) a1[a1.size()-1]--;
		} else {						//�������
			if(na2>nb2) {
				a2[la2-1]='0'+na2-nb2;
				flag=0;
			} else {
				a[la2-1]='0'+na2+10-nb2;
				flag=1;
			}						//���ϼ��н��м���
			if(flag) a2[la2-2]--;
		}
		xiaohou--;
		if(jiana) la2--;
		if(jianb) lb2--;			//������jiana��jianb����--
	}
	flag=0;
	la1=a1.size(),lb1=b1.size();	//flag��¼��λ�����la1��lb1��¼a1��b1�ĳ���
	while(la1>0) {
		int na1=a1[la1-1]-'0',nb1;  	//na1����a1��ǰ���֣�nb1����b1��ǰ���ֻ���0
		if(lb1>0) nb1=b1[lb1-1]-'0';
		else nb1=0;
		if(na1>nb1) {
			a1[la1-1]='0'+na1-nb1;
			flag=0;
		} else {
			a1[la1-1]='0'+na1+10-nb1;
			flag=1;
		}
		if(flag) a1[la1-2]--;		//����flag˵���˴������λ�ˣ���ǰһλ��Ҫ��һ
		la1--;
		lb1--;						//��ǰһλ
	}
	jieguo=jieguo+a1+"."+a2;
	return jieguo;
}
string jiafa(string A,string B) {
	string a=A,b=B,a1="",a2="",b1="",b2="";     //��a��b����A��B��������,a1��a2Ϊa��С����ǰ�������֣�b1��b2ͬ��
	int diana,dianb,la1,la2,lb1,lb2; //diana,dianb������¼a��bС����λ�ã�la1��la2��¼a��С����ǰ��С�����λ�ã�lb1��lb2ͬ��
	int pa=0,pb=0;		//�����ж�a,b�Ƿ���С����
	for(int i=0; i<a.size(); i++) if(a[i]=='.') {
			diana=i;
			pa=1;
			break;		//��¼a��С����λ��
		}
	for(int i=0; i<b.size(); i++) if(b[i]=='.') {
			dianb=i;
			pb=1;
			break;		//��¼b��С����λ��
		}
	if(pa==1&&pb==0) b=b+".0";
	else if(pa==0&&pb==1) a=a+".0";		//����ֻ��һ���ַ���û��С���������С����0
	else if(pa==0&&pb==0) {			//������������ӷ�
		if(a.size()<b.size()) {
			string tem=b;
			b=a;
			a=tem;						//��b��a���򽻻�
		}
		int jin=0,sum,la=a.size(),lb=b.size();
		while(la>0) {
			int na=a[la-1]-'0',nb;//����a��ǰ����
			if(lb>0) nb=b[lb-1]-'0';
			else nb=0;			//����b��ǰ���֣����糤�Ȳ�����Ϊ0
			sum=na+nb+jin;      //�ܺ�
			if(sum>=10) {
				a[la-1]='0'+sum%10;
				jin=1;
			} else {
				a[la-1]='0'+sum;
				jin=0;
			}
			la--;
			lb--;		//׼��������һλ
		}
		if(jin) a="1"+a;
		return a;
	}
	for(int i=0; i<diana; i++) a1+=a[i];		//��a[0]��a[diana-1]��¼Ϊa1
	for(int i=diana+1; i<a.size(); i++) a2+=a[i];		//��a[diana+1]�����һλ��¼Ϊa2
	for(int i=0; i<dianb; i++) b1+=b[i];		//��b[0]��b[dianb-1]��¼Ϊb1
	for(int i=dianb+1; i<b.size(); i++) b2+=b[i];		//��b[dianb+1]�����һλ��¼Ϊb2
	if(a2.size()<b2.size()) {
		string tem=b2;
		b2=a2;
		a2=tem;		//����b2��a2�������򽻻����ַ��������ڽ��ӷ���������ڽϳ����ַ�����
	}
	la2=a2.size();
	lb2=b2.size();
	int flag=0;
	while(la2>0) {
		int na2=a2[la2-1]-'0',nb2;			//��ȡa2��ǰ����
		if(la2==lb2) {
			nb2=b2[lb2-1]-'0';
			lb2--;
		} else nb2=0;						//��¼b2��ǰ���֣����糤�Ȼ�δ�ﵽlb2���¼Ϊ0
		int sum=na2+nb2+flag;	//�ܺ�
		if(sum>=10) {
			a2[la2-1]='0'+sum%10;
			flag=1;
		} else {
			a2[la2-1]='0'+sum;
			flag=0;
		}					//���ͱ�����a2[la2-1]�У���������λ
		la2--;				//׼��������һλ
	}
	if(flag) a1[a1.size()-1]+=1;
	if(a1.size()<b1.size()) {
		string tem=b1;
		b1=a1;
		a1=tem;		//����b1��a1�������򽻻����ַ��������ڽ��ӷ���������ڽϳ����ַ�����
	}
	la1=a1.size();
	lb1=b1.size();
	flag=0;		//�����λֵ
	while(la1>0) {
		int na1=a1[la1-1]-'0',nb1;		//��ȡa1��ǰ����
		if(lb1>0) nb1=b1[lb1-1]-'0';
		else nb1=0;		//��¼b1��ǰ���֣����糤���Ѿ�����lb1���¼Ϊ0
		int sum=na1+nb1+flag;  //�ܺ�
		if(sum>=10) {
			a1[la1-1]='0'+sum%10;
			flag=1;
		} else {
			a1[la1-1]='0'+sum;
			flag=0;
		}						//���ͱ�����a1[la1-1]�У���������λ
		la1--;
		lb1--;		//׼��������һλ
	}
	if(flag) a1="1"+a1;		//��ǰ�߽�λ
	string jieguo;			//�������淵��ֵ
	if(a2!="0") jieguo=a1+'.'+a2;		//����������ӽ����������������С����ǰ��a1��С���㣬�ټ���С������a2
	else jieguo=a1;						//����������������a2Ϊ0��С�������ʡ�ԣ�ֱ�ӷ���a1
	return jieguo;		//���ؽ��
}
int main() {
	string ceshi1,ceshi2,jieguo;
	while(cin>>ceshi1>>ceshi2) {
		if(ceshi1=="0"&&ceshi2=="0") break;
		else jieguo=jianfa(ceshi1,ceshi2);
		cout<<jieguo<<endl;
	}
	return 0;
}
