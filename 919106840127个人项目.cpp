#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <windows.h>
#include <stdlib.h>
using namespace std;
int jin;							//�ж��Ƿ��н���
const int msize=20;					//���̳���̶�Ϊ20
int x,y,hx1,hx2,hy1,hy2,num(0);		//x��yΪÿ����������ӵ����꣬hx1��hy1������û�1���壬hy2��hx2���û�2���壬num�غ���
int scomap[20][20]= {0}; 			//��ai�����ж�ÿ��λ�õļ�ֵ
char map[20][20];         			//ÿ�λ�������
bool nohand(int x,int y,char qi) {	//�ж��Ƿ�����˽���
	if(jin==0) return false;
	int ain(0),blankn(0),four(0),five(0);		//four��five�ֱ�������˸������ֵĻ�/���ĺ��������������һ�������
	for(int mx=-1; mx<2; mx++) {
		for(int my=-1; my<2; my++) {		//�˸�����
			ain=0;
			blankn=0;
			if(mx==0&&my==0) continue;  //�ų��Լ�����
			for(int k=1; k<=4; k++) {				//ÿ������4��λ��
				if(x+mx*k>=0&&x+mx*k<msize&&y+my*k>=0&&y+my*k<msize&&map[x+mx*k][y+my*k]==qi) ain++;//�Լ�������
				else if(x+mx*k>=0&&x+mx*k<msize&&y+my*k>=0&&y+my*k<msize&&map[x+mx*k][y+my*k]=='+') {		//�ո�
					blankn++;
					break;
				} else break;						//�����߽���߱��з����ӿ�ס
			}
			for(int k=1; k<=4; k++) {				//ÿ������4��λ��(�෴����)
				if(x-mx*k>=0&&x-mx*k<msize&&y-my*k>=0&&y-my*k<msize&&map[x-mx*k][y-my*k]==qi) ain++;//�Լ�������
				else if(x-mx*k>=0&&x-mx*k<msize&&y-my*k>=0&&y-my*k<msize&&map[x-mx*k][y-my*k]=='+') {		//�ո�
					blankn++;
					break;
				} else break;						//�����߽���߱��з����ӿ�ס
			}
			if(ain==4&&(blankn==1||blankn==2)) five++;  //����ͳ���
			else if(ain==3&&(blankn==1||blankn==2)) four++;   //���ĺ�����
		}
	}
	if(four>=4||five>=4) return true;					//�˸�����Ὣ�жϽ��ֵ���������飬���Դ��ڵ���4 
	else return false;
}
bool legitimate(int X,int Y) {		//�ж�����λ���Ƿ�Ϸ�
	if(X<0||X>=20||Y<0||Y>=20||map[X][Y]!='+') return false;
	else return true;
}
void printmap() {					//��ӡ��ǰ������Ϣ
	printf("   ");
	for(int i=0; i<msize; i++) {												//���б��
		if(i<10) cout<<"  "<<i;
		else cout<<" "<<i;
	}
	printf("\n");
	for(int i=0; i<msize; i++) {
		if(i<10) cout<<"  "<<i;												//���б�ţ�һλ����Ϊ�ȶ�λ���̣�����ǰ�������ո�
		else cout<<' '<<i;													//��λ����ǰ��ֻ��һ���ո�
		for(int j=0; j<msize; j++) cout<<"  "<<map[j][i];					//��ӡÿ������,��Ϊ���д�ӡ��y��ͬ��������[j][i]
		printf("\n");
	}
}
bool win(int x,int y) {				//�ж��Ƿ�ʤ��
	for(int i=0; i<6; i++) {			//�����ж�
		if(x-i>=0&&x-i+5<msize&&
		        map[x-i][y]==map[x-i+1][y]&&
		        map[x-i][y]==map[x-i+2][y]&&
		        map[x-i][y]==map[x-i+3][y]&&
		        map[x-i][y]==map[x-i+4][y]&&
		        map[x-i][y]==map[x-i+5][y]&&map[x-i][y]!='+') return true;		//һ��ʼû���ǵ�������ʱȫ��+�����
	}
	for(int i=0; i<6; i++) {			//�����ж�
		if(y-i>=0&&y-i+5<msize&&
		        map[x][y-i]==map[x][y-i+1]&&
		        map[x][y-i]==map[x][y-i+2]&&
		        map[x][y-i]==map[x][y-i+3]&&
		        map[x][y-i]==map[x][y-i+4]&&
		        map[x][y-i]==map[x][y-i+5]&&map[x][y-i]!='+') return true;
	}
	for(int i=0; i<6; i++) {			//45�Ƚ��ж�
		if(y+i<msize&&y+i-5>=0&&x-i>0&&x-i+5<msize&&
		        map[x-i][y+i]==map[x-i+1][y+i+1]&&
		        map[x-i][y+i]==map[x-i+2][y+i+2]&&
		        map[x-i][y+i]==map[x-i+3][y+i+3]&&
		        map[x-i][y+i]==map[x-i+4][y+i+4]&&
		        map[x-i][y+i]==map[x-i+5][y+i+5]&&map[x-i][y+i]!='+') return true;
	}
	for(int i=0; i<6; i++) {			//135�Ƚ��ж�
		if(y-i>0&&y-i+5<msize&&x-i>0&&x-i+5<msize&&
		        map[x-i][y-i]==map[x-i+1][y-i+1]&&
		        map[x-i][y-i]==map[x-i+2][y-i+2]&&
		        map[x-i][y-i]==map[x-i+3][y-i+3]&&
		        map[x-i][y-i]==map[x-i+4][y-i+4]&&
		        map[x-i][y-i]==map[x-i+5][y-i+5]&&map[x-i][y-i]!='+') return true;
	}
	return false;
}
void upload(int X,int Y,int peo) {		//ʵʱ�ϴ�������Ϣ
	if(peo==1) map[X][Y]='H';			//1������º���
	else map[X][Y]='O';					//2������°���
}
void peoinput(int peo) {
	if(peo==1) num++;
	printf("Round : %d\n",num);		//����ʾ�ڼ��غ�
	if(peo==1) cout<<"Gamer 1's x and y :";
	else cout<<"Gamer 2's x and y :";
	cin>>x>>y;
	while(peo==1&&nohand(x,y,'H')) {
		cout<<"Nohand!!!\n"<<endl<<"Please input again : ";
		cin>>x>>y;
	}
	if(x==-1&&y==-1) {				//����x��y����-1�������
		map[hx1][hy1]='+';
		map[hx2][hy2]='+';			//��ԭ��һ��������
		printmap();
		cout<<"Please input again : "<<endl;		//��������
		cin>>x>>y;
	}
	while(peo==1&&nohand(x,y,'H')) {
		cout<<"Nohand!!!\n"<<endl<<"Please input again : ";
		cin>>x>>y;
	}
	if(!legitimate(x,y)) {
		cout<<"What you have input is not correct."<<endl<<"Please input again : ";
		cin>>x>>y;
	}
	while(peo==1&&nohand(x,y,'H')) {
		cout<<"Nohand!!!\n"<<endl<<"Please input again : ";
		cin>>x>>y;
	}
	if(x==-1&&y==-1) {				//����x��y�ٴζ���-1�����ٴλ���
		map[hx1][hy1]='+';
		map[hx2][hy2]='+';			//��ԭ��һ��������
		printmap();
		cout<<"Please input again : "<<endl;		//��������
		cin>>x>>y;
	}
	while(peo==1&&nohand(x,y,'H')) {
		cout<<"Nohand!!!\n"<<endl<<"Please input again : ";
		cin>>x>>y;
	}
	if(num==1) {
		hx1=x;
		hy1=y;
	} else {
		hx2=x;
		hy2=y;
	}
}
void valuemap(char qi) {				//����scomap����ÿһ����λ�������ֵ,qi����ɫ
	char eni;
	if(qi=='H') eni='O';
	else eni='H';
	if(qi=='H'&&num==1) {
		scomap[9][9]=100001;       	//����ai�����ҵ�һ����Ĭ���������̽�������
	}
	int enin(0),ain(0),blankn(0); 	//����һ�������ϵ��˵������������Ե����������հ���λ
	for(int i=0; i<msize; i++) {
		for(int j=0; j<msize; j++) scomap[i][j]=0;		//��ֵ����
	}
	for(int i=0; i<msize; i++) {		//��ʼ�����ֵ���������ϱȽ����еļ�Ȩ������Ϊ�����������������
		for(int j=0; j<msize; j++) {
			if(legitimate(i,j)&&map[i][j]=='+') {			//ֻ�кϷ�λ�õĿ�λ�ſ���
				if(qi=='H'&&nohand(i,j,'H')) {
					scomap[i][j]=-1;
					continue;
				}
				for(int mx=-1; mx<2; mx++) {
					for(int my=-1; my<2; my++) {				//һ���˸�����
						enin=0;
						ain=0;
						blankn=0;
						if(mx==0&&my==0) continue;
						for(int k=1; k<=5; k++) {				//ÿ������5��λ��
							if(i+mx*k>=0&&i+mx*k<msize&&j+my*k>=0&&j+my*k<msize&&map[i+mx*k][j+my*k]==qi) ain++;//�Լ�������
							else if(i+mx*k>=0&&i+mx*k<msize&&j+my*k>=0&&j+my*k<msize&&map[i+mx*k][j+my*k]=='+') {		//�ո�
								blankn++;
								break;
							} else break;						//�����߽���߱��з����ӿ�ס
						}
						for(int k=1; k<=5; k++) {				//ÿ������5��λ��,������
							if(i-mx*k>=0&&i-mx*k<msize&&j-my*k>=0&&j-my*k<msize&&map[i+mx*k][j+my*k]==qi) ain++;//�Լ�������
							else if(i-mx*k>=0&&i-mx*k<msize&&j-my*k>=0&&j-my*k<msize&&map[i+mx*k][j+my*k]=='+') {  		//�ո�
								blankn++;
								break;
							} else break;						//�����߽���߱��з����ӿ�ס
						}
						if(ain>=5)	scomap[i][j]=100000; 						//���������
						else if(ain==4) {
							if(blankn==2) {					//����
								scomap[i][j]=92000;
								if(qi=='H') scomap[i][j]+=100;		//����ai���֣�������Ȩ
							} else if(blankn==1) {				//����
								scomap[i][j]=90000;
								if(qi=='H') scomap[i][j]+=100;
							}
						} else if(ain==3) {
							if(blankn==2) {					//����
								scomap[i][j]=81000;
								if(qi=='H') scomap[i][j]+=100;
							} else if(blankn==1) {				//����
								scomap[i][j]=80000;
								if(qi=='H') scomap[i][j]+=100;
							}
						} else if(ain==2) {
							if(blankn==2) {					//����
								scomap[i][j]=71000;
								if(qi=='H') scomap[i][j]+=100;
							} else if(blankn==1) {				//����
								scomap[i][j]=10000;
								if(qi=='H') scomap[i][j]+=100;
							}
						} else if(ain==1) {
							if(blankn==2) {					//���
								scomap[i][j]=61000;
								if(qi=='H') scomap[i][j]+=100;
							} else if(blankn==1) {				//�߶�
								scomap[i][j]=60000;
								if(qi=='H') scomap[i][j]+=100;
							}
						}
						blankn=0;
						for(int k=1; k<=5; k++) {				//ÿ������5��λ��
							if(i+mx*k>=0&&i+mx*k<msize&&j+my*k>=0&&j+my*k<msize&&map[i+mx*k][j+my*k]==eni) enin++;	//�з�����
							else if(i+mx*k>=0&&i+mx*k<msize&&j+my*k>=0&&j+my*k<msize&&map[i+mx*k][j+my*k]=='+') {	//�ո�
								blankn++;
								break;
							} else break;						//�����߽���߱��з����ӿ�ס
						}
						for(int k=1; k<=5; k++) {				//ÿ������5��λ��,������
							if(i-mx*k>=0&&i-mx*k<msize&&j-my*k>=0&&j-my*k<msize&&map[i+mx*k][j+my*k]==eni) enin++;	//�з�����
							else if(i-mx*k>=0&&i-mx*k<msize&&j-my*k>=0&&j-my*k<msize&&map[i+mx*k][j+my*k]=='+') {		//�ո�
								blankn++;
								break;
							} else break;						//�����߽���߱��з����ӿ�ס
						}
						if(enin>=5)	scomap[i][j]=99999; 						//���������
						else if(enin==4) {
							if(blankn==2) {					//����
								scomap[i][j]=93000;
								if(qi=='O') scomap[i][j]+=100;		//����ai���֣�������Ȩ������5��ķ�����Ӧ�õ��ڽ���
							} else if(blankn==1) {				//����
								scomap[i][j]=91000;
								if(qi=='O') scomap[i][j]+=100;
							}
						} else if(enin==3) {
							if(blankn==2) {					//����
								scomap[i][j]=81000;
								if(qi=='O') scomap[i][j]+=100;
							} else if(blankn==1) {				//����
								scomap[i][j]=80000;
								if(qi=='O') scomap[i][j]+=100;
							}
						} else if(enin==2) {
							if(blankn==2) {					//����
								scomap[i][j]=71000;
								if(qi=='O') scomap[i][j]+=100;
							} else if(blankn==1) {				//����
								scomap[i][j]=10000;
								if(qi=='O') scomap[i][j]+=100;
							}
						} else if(enin==1) {
							if(blankn==2) {					//���
								scomap[i][j]=61000;
								if(qi=='O') scomap[i][j]+=100;
							} else if(blankn==1) {				//�߶�
								scomap[i][j]=60000;
								if(qi=='O') scomap[i][j]+=100;
							}
						}
					}
				}
			}
		}
	}
}
void aiinput(int ai) {				//int ai ����ai�Ⱥ��֣�1���֣�2����
	if(ai==1) num++;
	printf("Round : %d",num);		//����ʾ�ڼ��غ�
	cout<<endl;
	if(ai==1) valuemap('H');		//����ÿ��λ�õļ�ֵ
	else valuemap('O');
	int maxvalue(0),maxn(0),xm[401],ym[401];	//maxvlaue����ֵ��maxn����ֵ��������xm��ym����������������ֵλ�õ�����
	for(int i=0; i<msize; i++) {					//�������ֵ
		for(int j=0; j<msize; j++) if(scomap[i][j]>maxvalue) maxvalue=scomap[i][j];
	}
	for(int i=0; i<msize; i++) {
		for(int j=0; j<msize; j++) {
			if(scomap[i][j]==maxvalue) {
				xm[maxn]=i;
				ym[maxn]=j;
				maxn++;
			}
		}
	}
	srand((unsigned)time(0));				//�ҵ�һ�������
	int index=rand()%maxn;
	x=xm[index];
	y=ym[index];
	if(ai==1) {
		hx1=x;
		hy1=y;
	} else {
		hx2=x;
		hy2=y;
	}
}
void clear() {						//��յ�ͼ���ָ�num,����int��Ϊÿ����Ϸ��Ҫ�����������Բ���Ҫ����
	for(int i=0; i<msize; i++) {
		for(int j=0; j<msize; j++) map[i][j]='+';		//���ָ̻�ԭ״
	}
	num=0;							//num����
}
void pvp() {							//���˶�ս
	for(int i=0; i<200; i++) {
		peoinput(1);				//������Ҳ���
		upload(x,y,1);
		printmap();
		if(win(x,y)) {				//�������ʤ��
			cout<<"The gamer 1 has won!!! Congratulation!!!\n";
			clear();
			break;
		}
		peoinput(2);				//������Ҳ���
		upload(x,y,2);
		printmap();
		if(win(x,y)) {				//�������ʤ��
			cout<<"The gamer 2 has won!!! Congratulation!!!\n";
			clear();
			break;
		}
		if(num==200) {					//����200�غϣ�������
			cout<<"Ther is no winer in this time.\n";
			clear();
			break;
		}
	}
}
void pve() {							//�˻���ս
	int hand,comp;					//����Ⱥ���
	cout<<"Please choose your number,1 or 2 ? : ";
	cin>>hand;
	if(hand==1) comp=2;
	else if(hand==2) comp=1;
	if(hand==1) {
		for(int i=0; i<200; i++) {	//�������
			peoinput(hand);					//�������
			upload(x,y,hand);
			printmap();
			if(win(x,y)) {				//���ʤ��
				cout<<"The gamer "<<hand<<" has won!!! Congratulation!!!\n";
				clear();
				break;
			}
			aiinput(comp);					//��������
			upload(x,y,comp);
			printmap();
			if(win(x,y)) {
				cout<<"The gamer "<<comp<<" has won!!! Congratulation!!!\n";
				clear();
				break;
			}
			if(num==200) {					//����200�غϣ�������
				cout<<"Ther is no winer in this time.\n";
				clear();
				break;
			}
		}
	} else {
		for(int i=0; i<200; i++) {		//��������
			aiinput(comp);					//��������
			upload(x,y,comp);
			printmap();
			if(win(x,y)) {
				cout<<"The gamer "<<comp<<" has won!!! Congratulation!!!\n";
				clear();
				break;
			}
			peoinput(hand);					//�������
			upload(x,y,hand);
			printmap();
			if(win(x,y)) {				//���ʤ��
				cout<<"The gamer "<<hand<<" has won!!! Congratulation!!!\n";
				clear();
				break;
			}
			if(num==200) {					//����200�غϣ�������
				cout<<"Ther is no winer in this time.\n";
				clear();
				break;
			}
		}
	}
}
void eve() {							//�ۿ�������ս
	for(int i=0; i<200; i++) {
		aiinput(1);					//����1����
		upload(x,y,1);
		printmap();
		
		if(win(x,y)) {
			cout<<"The computer 1 has won!!! Congratulation!!!\n";
			clear();
			break;
		}
		aiinput(2);					//����2����
		upload(x,y,2);
		printmap();
		
		if(win(x,y)) {
			cout<<"The computer 1 has won!!! Congratulation!!!\n";
			clear();
			break;
		}
		if(num==200) {					//����200�غϣ�������
			cout<<"Ther is no winer in this time.\n";
			clear();
			break;
		}
	}
}
int main() {
	cout<<"Do you want to have nohand? Please input 1 or 0 : ";			//ѡ���Ƿ��н���
	cin>>jin;
	cout<<endl;
	while(1) {						//��ѭ�����������Ϸ
		clear();						//���ȳ�ʼ����ͼ
		cout<<"Which model is what you want?\n";
		cout<<"The first one(1) is pvp, the second one(2) is pve, the third one(3) is watching eve.\n";
		cout<<"If you would like to quit the program, plearse input 0 : ";				//�������
		int m;
		cin>>m;							//ѡ����Ϸģʽ
		if(m==1) pvp();
		else if(m==2) pve();
		else if(m==3) eve();
		else if(m==0) break;
		cout<<endl;
	}
	return 0;
}
