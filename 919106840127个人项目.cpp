#include <iostream>
#include <stdio.h>
#include <cstring>
#include <ctime>
#include <windows.h>
#include <cstdlib>
using namespace std;
const int msize=20;					//棋盘长宽固定为20 
int x,y,hx1,hx2,hy1,hy2,num(0);		//x，y为每次输入的棋子的坐标，hx1，hy1保存给用户1悔棋，hy2，hx2给用户2悔棋，num回合数
int scomap[20][20]={0}; 			//给ai用来判断每个位置的价值
char map[20][20];         			//每次画的棋盘
bool legitimate(int X,int Y){		//判断落子位置是否合法 
	if(x<0||x>=20||y<0||y>=20) return false;
	else return true;
}
void printmap(){
	printf("   ");
	for(int i=0;i<msize;i++){												//横行标号 
		if(i<10) cout<<"  "<<i;
		else cout<<" "<<i;
	}
	printf("\n");
	for(int i=0;i<msize;i++){													
		if(i<10) cout<<"  "<<i;												//竖列标号，一位数因为比二位数短，所以前边两个空格 
		else cout<<' '<<i;													//二位数，前方只有一个空格 
		for(int j=0;j<msize;j++) cout<<"  "<<map[i][j];						//打印每行棋盘 
		printf("\n");
	}
}
bool win(int x,int y){				//判断是否胜利 
	for(int i=0;i<6;i++){			//横向判断
		if(x-i>=0&&x-i+5<msize&&
		map[x-i][y]==map[x-i+1][y]&&
		map[x-i][y]==map[x-i+2][y]&&
		map[x-i][y]==map[x-i+3][y]&&
		map[x-i][y]==map[x-i+4][y]&&
		map[x-i][y]==map[x-i+5][y]) return true;
	}
	for(int i=0;i<6;i++){			//纵向判断 
		if(y-i>=0&&y-i+5<msize&&
		map[x][y-i]==map[x][y-i+1]&&
		map[x][y-i]==map[x][y-i+2]&&
		map[x][y-i]==map[x][y-i+3]&&
		map[x][y-i]==map[x][y-i+4]&&
		map[x][y-i]==map[x][y-i+5]) return true;
	}
	for(int i=0;i<6;i++){			//45度角判断 
		if(y+i<msize&&y+i-5>=0&&x-i>0&&x-i+5<msize&&
		map[x-i][y+i]==map[x-i+1][y+i+1]&&
		map[x-i][y+i]==map[x-i+2][y+i+2]&&
		map[x-i][y+i]==map[x-i+3][y+i+3]&&
		map[x-i][y+i]==map[x-i+4][y+i+4]&&
		map[x-i][y+i]==map[x-i+5][y+i+5]) return true;
	}
	for(int i=0;i<6;i++){			//135度角判断 
		if(y-i>0&&y-i+5<msize&&x-i>0&&x-i+5<msize&&
		map[x-i][y-i]==map[x-i+1][y-i+1]&&
		map[x-i][y-i]==map[x-i+2][y-i+2]&&
		map[x-i][y-i]==map[x-i+3][y-i+3]&&
		map[x-i][y-i]==map[x-i+4][y-i+4]&&
		map[x-i][y-i]==map[x-i+5][y-i+5]) return true;
	}
	return false;
}
void upload(int X,int Y,int peo){		//实时上传棋面信息 
	if(peo==1) map[X][Y]='H';			//1号玩家下黑棋
	else map[X][Y]='O';					//2号玩家下白棋 
}
bool peace(){
	for(int i=0;i<msize;i++){
		for(int j=0;j<msize;j++) if(map[i][j]=='+') return false;
	}
	return true;
}
void peoput(int peo){
	printf("Round : %d",num);		//先显示第几回合
	if(peo==1) cout<<"Gamer 1's x and y :";
	else cout<<"Gamer 2's x and y :";
	cin>>x>>y;
	if(!(legitimate(x,y))){
		
	}
}
int main(){
	
}
