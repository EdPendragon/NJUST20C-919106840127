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
	return a;
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
string zhengshujian(string A,string B) {    //������������ԣ�������������С�������ֿ���д
	string jieguo="";
	string a=clear(A),b=clear(B);
	int la=a.size(),lb=b.size();
	if(xiaoyu(a,b)) {						//������С������������ת��Ϊ���Ĵ��С 
		jieguo+="-";
		jieguo+=zhengshujian(b,a);
		jieguo=clear(jieguo);
		return jieguo;
	}
	if(a[0]=='-'&&b[0]!='-'){				//�����Ǹ�������������ת��Ϊ���żӼӷ� 
		jieguo+="-";
		jieguo+=jiafa(tiqu(a,1,a.size()-1),b);
		jieguo=clear(jieguo);
		return jieguo;
	}
	if(a[0]!='-'&&b[0]=='-'){				//��������������������ת��Ϊ�ӷ� 
		jieguo+=jiafa(tiqu(b,1,b.size()-1),a);
		jieguo=clear(jieguo);
		return jieguo;
	}
	if(a[0]=='-'&&b[0]=='-'){				//�����Ǹ�������������ת��Ϊ���ǰ 
		jieguo+=zhengshujian(tiqu(b,1,b.size()-1),tiqu(a,1,a.size()-1));
		jieguo=clear(jieguo);
		return jieguo;
	}
	int flag=0;							//flag�����λ
	while(la>0) {
		int na=a[la-1]-'0',nb;					//na,nb��¼a��b��ǰλ�õ�����
		if(lb>0) nb=b[lb-1]-'0';
		else nb=0;
		int sum=na-nb;
		if(sum>=0) {
			a[la-1]='0'+sum;
			flag=0;
		} else {
			a[la-1]='0'+sum+10;
			flag=1;								//flag=1˵��Ҫ��λ
		}
		if(flag) a[la-2]--;						//��λ
		la--;
		lb--;
	}
	jieguo+=a;
	jieguo=clear(jieguo);						//�ٴ�ȥ��0 
	return jieguo;
}
int main() {
	string ceshi1,ceshi2,jieguo;
	while(cin>>ceshi1>>ceshi2) {
		if(ceshi1=="0"&&ceshi2=="0") break;
		else jieguo=zhengshujian(ceshi1,ceshi2);
		cout<<jieguo<<endl;
	}
	return 0;
}
