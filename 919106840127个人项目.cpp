#include <iostream>
#include <stdio.h>
#include <cstring>
#include <ctime>
#include <windows.h>
#include <cstdlib>
using namespace std;
const int msize=20;					//���̳���̶�Ϊ20 
int x,y,hx1,hx2,hy1,hy2,num(0);		//x��yΪÿ����������ӵ����꣬hx1��hy1������û�1���壬hy2��hx2���û�2���壬num�غ���
int scomap[20][20]={0}; 			//��ai�����ж�ÿ��λ�õļ�ֵ
char map[20][20];         			//ÿ�λ�������
bool legitimate(int X,int Y){		//�ж�����λ���Ƿ�Ϸ� 
	if(x<0||x>=20||y<0||y>=20) return false;
	else return true;
}
void printmap(){
	printf("   ");
	for(int i=0;i<msize;i++){												//���б�� 
		if(i<10) cout<<"  "<<i;
		else cout<<" "<<i;
	}
	printf("\n");
	for(int i=0;i<msize;i++){													
		if(i<10) cout<<"  "<<i;												//���б�ţ�һλ����Ϊ�ȶ�λ���̣�����ǰ�������ո� 
		else cout<<' '<<i;													//��λ����ǰ��ֻ��һ���ո� 
		for(int j=0;j<msize;j++) cout<<"  "<<map[i][j];						//��ӡÿ������ 
		printf("\n");
	}
}
bool win(int x,int y){				//�ж��Ƿ�ʤ�� 
	for(int i=0;i<6;i++){			//�����ж�
		if(x-i>=0&&x-i+5<msize&&
		map[x-i][y]==map[x-i+1][y]&&
		map[x-i][y]==map[x-i+2][y]&&
		map[x-i][y]==map[x-i+3][y]&&
		map[x-i][y]==map[x-i+4][y]&&
		map[x-i][y]==map[x-i+5][y]) return true;
	}
	for(int i=0;i<6;i++){			//�����ж� 
		if(y-i>=0&&y-i+5<msize&&
		map[x][y-i]==map[x][y-i+1]&&
		map[x][y-i]==map[x][y-i+2]&&
		map[x][y-i]==map[x][y-i+3]&&
		map[x][y-i]==map[x][y-i+4]&&
		map[x][y-i]==map[x][y-i+5]) return true;
	}
	for(int i=0;i<6;i++){			//45�Ƚ��ж� 
		if(y+i<msize&&y+i-5>=0&&x-i>0&&x-i+5<msize&&
		map[x-i][y+i]==map[x-i+1][y+i+1]&&
		map[x-i][y+i]==map[x-i+2][y+i+2]&&
		map[x-i][y+i]==map[x-i+3][y+i+3]&&
		map[x-i][y+i]==map[x-i+4][y+i+4]&&
		map[x-i][y+i]==map[x-i+5][y+i+5]) return true;
	}
	for(int i=0;i<6;i++){			//135�Ƚ��ж� 
		if(y-i>0&&y-i+5<msize&&x-i>0&&x-i+5<msize&&
		map[x-i][y-i]==map[x-i+1][y-i+1]&&
		map[x-i][y-i]==map[x-i+2][y-i+2]&&
		map[x-i][y-i]==map[x-i+3][y-i+3]&&
		map[x-i][y-i]==map[x-i+4][y-i+4]&&
		map[x-i][y-i]==map[x-i+5][y-i+5]) return true;
	}
	return false;
}
void upload(int X,int Y,int peo){		//ʵʱ�ϴ�������Ϣ 
	if(peo==1) map[X][Y]='H';			//1������º���
	else map[X][Y]='O';					//2������°��� 
}
bool peace(){
	for(int i=0;i<msize;i++){
		for(int j=0;j<msize;j++) if(map[i][j]=='+') return false;
	}
	return true;
}
void peoput(int peo){
	printf("Round : %d",num);		//����ʾ�ڼ��غ�
	if(peo==1) cout<<"Gamer 1's x and y :";
	else cout<<"Gamer 2's x and y :";
	cin>>x>>y;
	if(!(legitimate(x,y))){
		
	}
}
int main(){
	
}
