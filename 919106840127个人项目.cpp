//!!!!!!!注意：目前小数减法仍然有很大的bug，负整数减法仍然有小瑕疵，9月6日不要忘记bug内容 
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
bool xiaoyu(string a,string b) { //该函数用于判断两字符串大小
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
bool dengyu(string A,string B) { //该函数用于判断两字符串数字相等
	string a=A,b=B;
	if(a.size()!=b.size()) return false;
	for(int i=0; i<a.size(); i++) {
		if(a[i]!=b[i]) return false;
	}
	return true;
}
string quling(string str) {   //此函数用于去除字符串首0
	int sf=0;		//首个非0的元素位置
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
string clear(string str) {   //此函数用于去除小数点后的尾0,并且将字符串前的--变成+
	int youdian=0;	//看是否有小数点
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
	string a=A,b=B,a1="",a2="",b1="",b2="";  	//用a与b代替A与B进行运算，a1、a2为a的小数点前后两部分，b1、b2同理
	a=clear(a);
	b=clear(b);
	a=quling(a);
	b=quling(b);
	if(dengyu(a,b)) return "0";
	int diana,dianb,la1,la2,lb1,lb2; //diana,dianb用来记录a，b小数点位置，la1、la2记录a的小数点前和小数点后位置，lb1、lb2同理
	int pa=0,pb=0;		//用于判断a，b是否有小数点
	for(int i=0; i<a.size(); i++) if(a[i]=='.') {
			diana=i;
			pa=1;
			break;		//记录a的小数点位置
		}
	for(int i=0; i<b.size(); i++) if(b[i]=='.') {
			dianb=i;
			pb=1;
			break;		//记录b的小数点位置
		}
	if(pa==1&&pb==0) b=b+".0";
	else if(pa==0&&pb==1) a=a+".";		//假设只有一个字符串没有小数点则给它加上小数点0
	else if(pa==0&&pb==0) {			//否则进行整数减法
		string jieguo="";
		if(xiaoyu(a,b)) {     //假如a小于b
			string tem=a;
			a=b;
			b=tem;
			jieguo="-"+jieguo;
		}
		int flag=0,la=a.size(),lb=b.size();  //flag记录进位情况，la，lb记录a、b的长度
		while(la>0) {
			int na=a[la-1]-'0',nb;	//na保存a当前数字，nb保存b当前数字或者0
			if(lb>0) nb=b[lb-1]-'0';
			else nb=0;
			if(na>=nb) {
				a[la-1]='0'+na-nb;
				flag=0;
			} else {
				a[la-1]='0'+na+10-nb;
				flag=1;
			}
			if(flag) a[la-2]--;		//假如flag说明此次运算借位了，往前一位需要减一
			la--;
			lb--;					//准备进行下一位计算
		}
		jieguo+=a;
		jieguo=clear(jieguo);
		jieguo=quling(jieguo);
		if(a[0]=='-'&&b[0]=='-') jieguo="-"+jieguo;
		jieguo=clear(jieguo);
		return jieguo;
	}
	for(int i=0; i<diana; i++) a1+=a[i];		//从a[0]到a[diana-1]记录为a1
	for(int i=diana+1; i<a.size(); i++) a2+=a[i];		//从a[diana+1]到最后一位记录为a2
	for(int i=0; i<dianb; i++) b1+=b[i];		//从b[0]到b[dianb-1]记录为b1
	for(int i=dianb+1; i<b.size(); i++) b2+=b[i];		//从b[dianb+1]到最后一位记录为b2
	string jieguo="";
	if(xiaoyu(a1,b1)) { //假如a1小于b1
		string tem=b1;
		b1=a1;
		a1=tem;
		jieguo="-"+jieguo;
		tem=b2;
		b2=a2;
		a2=tem;
	}
	int flag=0,xiaohou,flag_=0;   //小后代表小数点后的位数，即两个字符串小数部分长的那一个
	la2=a2.size(),lb2=b2.size();//flag记录进位情况，la1,lb1记录a1、b1的长度,flag_判断小数点前第一位是否需要为小数点后第一位借位
	if(la2>lb2) xiaohou=la2;
	else xiaohou=lb2;
	while(xiaohou>0) {
		int na2,nb2,jiana=0,jianb=0;	//判断是否要la2，lb2--
		if(xiaohou==la2) {		//假如当前位置可减
			na2=a2[la2-1]-'0';
			jiana=1;
		} else na2=0;
		if(xiaohou==lb2) {		//假如当前位置可减
			nb2=b2[lb2-1]-'0';
			jianb=1;
		} else nb2=0;
		if(la1==1) {				//考虑小数点后第一位的情况
			if(na2>nb2) {
				a2[la2-1]='0'+na2-nb2;
				flag_=0;
			} else {
				a2[la2-1]='0'+na2-nb2+10;
				flag_=1;
			}						//以上几行进行减法
			if(flag_) a1[a1.size()-1]--;
		} else {						//正常情况
			if(na2>nb2) {
				a2[la2-1]='0'+na2-nb2;
				flag=0;
			} else {
				a[la2-1]='0'+na2+10-nb2;
				flag=1;
			}						//以上几行进行减法
			if(flag) a2[la2-2]--;
		}
		xiaohou--;
		if(jiana) la2--;
		if(jianb) lb2--;			//假如有jiana，jianb，则--
	}
	flag=0;
	la1=a1.size(),lb1=b1.size();	//flag记录进位情况，la1，lb1记录a1、b1的长度
	while(la1>0) {
		int na1=a1[la1-1]-'0',nb1;  	//na1保存a1当前数字，nb1保存b1当前数字或者0
		if(lb1>0) nb1=b1[lb1-1]-'0';
		else nb1=0;
		if(na1>nb1) {
			a1[la1-1]='0'+na1-nb1;
			flag=0;
		} else {
			a1[la1-1]='0'+na1+10-nb1;
			flag=1;
		}
		if(flag) a1[la1-2]--;		//假如flag说明此次运算借位了，往前一位需要减一
		la1--;
		lb1--;						//往前一位
	}
	jieguo=jieguo+a1+"."+a2;
	return jieguo;
}
string jiafa(string A,string B) {
	string a=A,b=B,a1="",a2="",b1="",b2="";     //用a与b代替A与B进行运算,a1、a2为a的小数点前后两部分，b1、b2同理
	int diana,dianb,la1,la2,lb1,lb2; //diana,dianb用来记录a，b小数点位置，la1、la2记录a的小数点前和小数点后位置，lb1、lb2同理
	int pa=0,pb=0;		//用于判断a,b是否有小数点
	for(int i=0; i<a.size(); i++) if(a[i]=='.') {
			diana=i;
			pa=1;
			break;		//记录a的小数点位置
		}
	for(int i=0; i<b.size(); i++) if(b[i]=='.') {
			dianb=i;
			pb=1;
			break;		//记录b的小数点位置
		}
	if(pa==1&&pb==0) b=b+".0";
	else if(pa==0&&pb==1) a=a+".0";		//假如只有一个字符串没有小数点则加上小数点0
	else if(pa==0&&pb==0) {			//否则进行整数加法
		if(a.size()<b.size()) {
			string tem=b;
			b=a;
			a=tem;						//若b比a长则交换
		}
		int jin=0,sum,la=a.size(),lb=b.size();
		while(la>0) {
			int na=a[la-1]-'0',nb;//保存a当前数字
			if(lb>0) nb=b[lb-1]-'0';
			else nb=0;			//保存b当前数字，假如长度不够则为0
			sum=na+nb+jin;      //总和
			if(sum>=10) {
				a[la-1]='0'+sum%10;
				jin=1;
			} else {
				a[la-1]='0'+sum;
				jin=0;
			}
			la--;
			lb--;		//准备计算下一位
		}
		if(jin) a="1"+a;
		return a;
	}
	for(int i=0; i<diana; i++) a1+=a[i];		//从a[0]到a[diana-1]记录为a1
	for(int i=diana+1; i<a.size(); i++) a2+=a[i];		//从a[diana+1]到最后一位记录为a2
	for(int i=0; i<dianb; i++) b1+=b[i];		//从b[0]到b[dianb-1]记录为b1
	for(int i=dianb+1; i<b.size(); i++) b2+=b[i];		//从b[dianb+1]到最后一位记录为b2
	if(a2.size()<b2.size()) {
		string tem=b2;
		b2=a2;
		a2=tem;		//假如b2比a2更长，则交换两字符串，便于将加法结果保存在较长的字符串内
	}
	la2=a2.size();
	lb2=b2.size();
	int flag=0;
	while(la2>0) {
		int na2=a2[la2-1]-'0',nb2;			//获取a2当前数字
		if(la2==lb2) {
			nb2=b2[lb2-1]-'0';
			lb2--;
		} else nb2=0;						//记录b2当前数字，假如长度还未达到lb2则记录为0
		int sum=na2+nb2+flag;	//总和
		if(sum>=10) {
			a2[la2-1]='0'+sum%10;
			flag=1;
		} else {
			a2[la2-1]='0'+sum;
			flag=0;
		}					//将和保存在a2[la2-1]中，并表明进位
		la2--;				//准备计算下一位
	}
	if(flag) a1[a1.size()-1]+=1;
	if(a1.size()<b1.size()) {
		string tem=b1;
		b1=a1;
		a1=tem;		//假如b1比a1更长，则交换两字符串，便于将加法结果保存在较长的字符串内
	}
	la1=a1.size();
	lb1=b1.size();
	flag=0;		//保存进位值
	while(la1>0) {
		int na1=a1[la1-1]-'0',nb1;		//获取a1当前数字
		if(lb1>0) nb1=b1[lb1-1]-'0';
		else nb1=0;		//记录b1当前数字，假如长度已经到达lb1则记录为0
		int sum=na1+nb1+flag;  //总和
		if(sum>=10) {
			a1[la1-1]='0'+sum%10;
			flag=1;
		} else {
			a1[la1-1]='0'+sum;
			flag=0;
		}						//将和保存在a1[la1-1]中，并标明进位
		la1--;
		lb1--;		//准备计算下一位
	}
	if(flag) a1="1"+a1;		//最前边进位
	string jieguo;			//用来保存返回值
	if(a2!="0") jieguo=a1+'.'+a2;		//假如两者相加结果不是整数，返回小数点前的a1，小数点，再加上小数点后的a2
	else jieguo=a1;						//假如结果是整数，则a2为0，小数点可以省略，直接返回a1
	return jieguo;		//返回结果
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
