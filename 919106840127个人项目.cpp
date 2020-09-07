//注意：乘法的小数点未加上 
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
string jiafaz(string A,string B) {    //正数加法 
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
string zhengshujian(string A,string B) {    //因减法的特殊性，将整数减法与小数减法分开编写（正的） 
	string jieguo="";
	string a=clear(A),b=clear(B);
	int la=a.size(),lb=b.size();
	if(xiaoyu(a,b)) {						//假如是小数减大数，则转化为负的大减小 
		jieguo+="-";
		jieguo+=zhengshujian(b,a);
		jieguo=clear(jieguo);
		return jieguo;
	}
	if(a[0]=='-'&&b[0]!='-'){				//假如是负数减正数，则转化为负号加加法 
		jieguo+="-";
		jieguo+=jiafaz(tiqu(a,1,a.size()-1),b);
		jieguo=clear(jieguo);
		return jieguo;
	}
	if(a[0]!='-'&&b[0]=='-'){				//假如是正数减负数，则转化为加法 
		jieguo+=jiafaz(tiqu(b,1,b.size()-1),a);
		jieguo=clear(jieguo);
		return jieguo;
	}
	if(a[0]=='-'&&b[0]=='-'){				//假如是负数减负数，则转化为后减前 
		jieguo+=zhengshujian(tiqu(b,1,b.size()-1),tiqu(a,1,a.size()-1));
		jieguo=clear(jieguo);
		return jieguo;
	}
	int flag=0;							//flag代表借位
	while(la>0) {
		int na=a[la-1]-'0',nb;					//na,nb记录a、b当前位置的数字
		if(lb>0) nb=b[lb-1]-'0';
		else nb=0;
		int sum=na-nb;
		if(sum>=0) {
			a[la-1]='0'+sum;
			flag=0;
		} else {
			a[la-1]='0'+sum+10;
			flag=1;								//flag=1说明要借位
		}
		if(flag) a[la-2]--;						//借位
		la--;
		lb--;
	}
	jieguo+=a;
	jieguo=clear(jieguo);						//再次去首0 
	return jieguo;
}
string xiaoshujian(string A,string B){			//小数点后的减法，即0.几减0.几 
	string a=A,b=B;
	if(a==b) return ".0";
	int la=a.size(),lb=b.size(),max=la;
	if(la>lb){
		int tem=la-lb;
		for(int i=0;i<tem;i++) b+="0";
	}
	else if(la<lb){
		max=lb;
		int tem=lb-la;
		for(int i=0;i<tem;i++) a+="0";
	}
	la=a.size(),lb=b.size();
	while(max>0){
		int na=a[max-1]-'0',nb;
		nb=b[max-1]-'0';
		int sum=na-nb;
		if(sum>=0){
			a[max-1]='0'+sum;
		}
		else{
			a[max-1]='0'+sum+10;
			if(max!=1){
				a[max-2]--;
			}
		}
		max--;
	}
	string jieguo="."+a;			//注意返回结果有小数点
	jieguo=clear(jieguo);
	if(jieguo[0]=='0') jieguo=tiqu(jieguo,1,jieguo.size()-1);
	return jieguo;
}
string jianfa(string A,string B){				//带小数的减法 
	string a=clear(A),b=clear(B);
	if(a[0]=='-'&&b[0]=='-'){					//负减负化为后减前 
		return jianfa(tiqu(b,1,b.size()-1),tiqu(a,1,a.size()-1));
	}
	if(a[0]=='-'&&b[0]!='-'){					//负数减正数化为负加法 
		string jieguo="-";
		jieguo+=jiafaz(tiqu(a,1,a.size()-1),b);
		return jieguo;
	}
	if(a[0]!='-'&&b[0]=='-'){					//正减负化为加法 
		return jiafaz(a,tiqu(b,1,b.size()-1));
	}
	if(xiaoyu(a,b)){
		string jieguo="-";
		jieguo+=jianfa(b,a);
		return jieguo;
	}
	int diana=0,dianb=0;
	for(int i=1;i<a.size();i++) if(a[i]=='.'){
		diana=i;
		break;
	}
	for(int i=1;i<b.size();i++) if(b[i]=='.'){		//因为小数点不可能在第0位，所以i从1开始 
		dianb=i;
		break;
	}
	if(diana==0&&dianb==0) return zhengshujian(a,b);//整数减法 
	if(diana!=0&&dianb==0){
		b+=".0";
		dianb=b.size()-2;
	}
	else if(dianb!=0&&diana==0){
		a+=".0";				//若只有一个没有小数点，则加上小数点零
		diana=a.size()-2;
	}
	string a1=tiqu(a,0,diana-1),a2=tiqu(a,diana+1,a.size()-1),b1=tiqu(b,0,dianb-1),b2=tiqu(b,dianb+1,b.size()-1);//分开前后
	if(xiaoshuxiaoyu(a2,b2)) a1=zhengshujian(a1,"1");
	string tem1,tem2=xiaoshujian(a2,b2);
	tem1=zhengshujian(a1,b1);
	string jieguo=tem1+tem2;
	jieguo=clear(jieguo);
	return jieguo;
}
string jiafa(string A,string B){			//用之前的正数加法与减法函数进行 
	string a=A,b=B;
	if(a[0]=='-'&&b[0]=='-'){			//负负相加等于负号加上正数加 
		string jieguo="-";
		jieguo+=jiafaz(tiqu(a,1,a.size()-1),tiqu(b,1,b.size()-1));
		return jieguo;
	}
	if(a[0]=='-'&&b[0]!='-'){			//负正相加等于后减前 
		return jianfa(b,tiqu(a,1,a.size()-1));
	}
	if(a[0]!='-'&&b[0]=='-'){			//正负相加等于前减后 
		return jianfa(a,tiqu(b,1,b.size()-1));
	}
	if(a[0]!='-'&&b[0]!='-') return jiafaz(a,b);		//正正相加不用动 
}
string chengfa(string A,string B){				//乘法 
	string a=clear(A),b=clear(b);
	int dian=0;								//记录小数点后的位数 
	for(int i=a.size()-1;i>=0;i--){
		if(a[i]=='.'){
			dian+=a.size()-1-i;
			a=tiqu(a,0,dian-1)+tiqu(a,dian+1,a.size()-1);
			break;
		}
	}
	for(int i=b.size()-1;i>=0;i--){
		if(b[i]=='.'){
			dian+=b.size()-1-i;
			b=tiqu(b,0,dian-1)+tiqu(b,dian+1,b.size()-1);
			break;
		}
	}
	int la=a.size(),lb=b.size(),max;
	if(la>lb) max=la;
	else max=lb;											//长度 
	int na[max]={0},nb[max]={0},result[2*max]={0};
	for(int i=la-1,j=0;i>=0;i--,j++)	na[j]=a[i]-'0';		//以int保存数值 
	for(int i=lb-1,j=0;i>=0;i--,j++) 	nb[j]=b[i]-'0';		//以int保存数值 
	for(int i=0;i<la;i++){							//每一位相乘 
		for(int j=0;j<lb;j++) result[i+j]+=na[i]*nb[j];
	}
	for(int i=0;i<(la+lb);i++){					//进位 
		if(result[i]>9){
			result[i+1]+=result[i]/10;
			result[i]&=10;						//向前一位进位，此位保留个位数 
		}
	}
	int i;
	for(i=la+lb;i>=0;i--){					//转化回字符串 
		if(result[i]==0) continue;				//遇到0则停止 
		else break;
	}
	string result_="";
	for(;i>=0;i--) result_+=result[i];
	return result_;
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
