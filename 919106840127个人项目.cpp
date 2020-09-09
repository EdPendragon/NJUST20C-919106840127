#include <iostream>
#include <stdio.h>
#include <cstring>
#include <ctime>
#include <windows.h>
#include <cstdlib>
using namespace std;
const int msize=20;					//棋盘长宽固定为20
int x,y,hx1,hx2,hy1,hy2,num(0);		//x，y为每次输入的棋子的坐标，hx1，hy1保存给用户1悔棋，hy2，hx2给用户2悔棋，num回合数
int scomap[20][20]= {0}; 			//给ai用来判断每个位置的价值
char map[20][20];         			//每次画的棋盘
bool legitimate(int X,int Y) {		//判断落子位置是否合法
	if(x<0||x>=20||y<0||y>=20) return false;
	else return true;
}
void printmap() {					//打印当前棋面信息 
	printf("   ");
	for(int i=0; i<msize; i++) {												//横行标号
		if(i<10) cout<<"  "<<i;
		else cout<<" "<<i;
	}
	printf("\n");
	for(int i=0; i<msize; i++) {
		if(i<10) cout<<"  "<<i;												//竖列标号，一位数因为比二位数短，所以前边两个空格
		else cout<<' '<<i;													//二位数，前方只有一个空格
		for(int j=0; j<msize; j++) cout<<"  "<<map[i][j];						//打印每行棋盘
		printf("\n");
	}
}
bool win(int x,int y) {				//判断是否胜利
	for(int i=0; i<6; i++) {			//横向判断
		if(x-i>=0&&x-i+5<msize&&
		        map[x-i][y]==map[x-i+1][y]&&
		        map[x-i][y]==map[x-i+2][y]&&
		        map[x-i][y]==map[x-i+3][y]&&
		        map[x-i][y]==map[x-i+4][y]&&
		        map[x-i][y]==map[x-i+5][y]) return true;
	}
	for(int i=0; i<6; i++) {			//纵向判断
		if(y-i>=0&&y-i+5<msize&&
		        map[x][y-i]==map[x][y-i+1]&&
		        map[x][y-i]==map[x][y-i+2]&&
		        map[x][y-i]==map[x][y-i+3]&&
		        map[x][y-i]==map[x][y-i+4]&&
		        map[x][y-i]==map[x][y-i+5]) return true;
	}
	for(int i=0; i<6; i++) {			//45度角判断
		if(y+i<msize&&y+i-5>=0&&x-i>0&&x-i+5<msize&&
		        map[x-i][y+i]==map[x-i+1][y+i+1]&&
		        map[x-i][y+i]==map[x-i+2][y+i+2]&&
		        map[x-i][y+i]==map[x-i+3][y+i+3]&&
		        map[x-i][y+i]==map[x-i+4][y+i+4]&&
		        map[x-i][y+i]==map[x-i+5][y+i+5]) return true;
	}
	for(int i=0; i<6; i++) {			//135度角判断
		if(y-i>0&&y-i+5<msize&&x-i>0&&x-i+5<msize&&
		        map[x-i][y-i]==map[x-i+1][y-i+1]&&
		        map[x-i][y-i]==map[x-i+2][y-i+2]&&
		        map[x-i][y-i]==map[x-i+3][y-i+3]&&
		        map[x-i][y-i]==map[x-i+4][y-i+4]&&
		        map[x-i][y-i]==map[x-i+5][y-i+5]) return true;
	}
	return false;
}
void upload(int X,int Y,int peo) {		//实时上传棋面信息
	if(peo==1) map[X][Y]='H';			//1号玩家下黑棋
	else map[X][Y]='O';					//2号玩家下白棋
}
bool peace() {
	for(int i=0; i<msize; i++) {
		for(int j=0; j<msize; j++) if(map[i][j]=='+') return false;
	}
	return true;
}
void peoinput(int peo) {
	if(peo==1) num++;
	printf("Round : %d",num);		//先显示第几回合
	if(peo==1) cout<<"Gamer 1's x and y :";
	else cout<<"Gamer 2's x and y :";
	cin>>x>>y;
	if(x==-1&&y==-1) {				//假如x，y都是-1，则悔棋
		map[hx1][hy1]='+';
		map[hx2][hy2]='+';			//还原上一步的棋盘
		printmap();
		cout<<"Please input again : "<<endl;		//重新输入
		cin>>x>>y;
	}
	if(!(legitimate(x,y))) {
		cout<<"What you have input is not correct."<<endl<<"Please input again : ";
		cin>>x>>y;
	}
	if(x==-1&&y==-1) {				//假如x，y再次都是-1，则再次悔棋
		map[hx1][hy1]='+';
		map[hx2][hy2]='+';			//还原上一步的棋盘
		printmap();
		cout<<"Please input again : "<<endl;		//重新输入
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
void valuemap(char qi){				//定义scomap数组每一个空位的下棋价值,qi是棋色 
	char eni;
	if(qi=='H') eni=O;
	else eni='H';
	if(qi=='H'&&num==1){
		scomap[9][9]=100001;       	//假如ai先手且第一步，默认下在棋盘近似中心 
	}
	int enin(0),ain(0),blankn(0); 	//代表一个方向上敌人的棋子数，电脑的棋子数，空白棋位
	for(int i=0;i<msize;i++){
		for(int j=0;j<msize;j++) scomap[i][j]=0;		//价值清零 
	} 
	for(int i=0;i<msize;i++){		//开始计算价值，采用网上比较流行的加权法，分为进攻、防守两种情况 
		for(int j=0;j<msize;j++){
			if(legitimate(i,j)&&map[i][j]=='+'){			//只有合法位置的空位才考虑 
				for(int mx=-1;mx<2;mx++){
					for(int my=-1;my<2;my++){				//一共八个方向 
						enin=0;
						ain=0;
						blankn=0;
						if(mx==0&&my==0) continue;
						for(int k=1;k<=5;k++){				//每个方向共5个位置 
							if(legitimate(i+mx*k,j+my*k)&&map[i+mx*k][j+my*k]==qi) ain++;		//自己方的棋 
							else if(legitimate(i+mx*k,j+my*k)&&map[i+mx*k][j+my*k]=='+'){		//空格 
								blankn++;
								break;
							}
							else break;						//超过边界或者被敌方棋子卡住 
						}
						for(int k=1;k<=5;k++){				//每个方向共5个位置,反方向 
							if(legitimate(i+mx*k,j+my*k)&&map[i+mx*k][j+my*k]==qi) ain++;		//自己方的棋 
							else if(legitimate(i+mx*k,j+my*k)&&map[i+mx*k][j+my*k]=='+'){		//空格 
								blankn++;
								break;
							}
							else break;						//超过边界或者被敌方棋子卡住 
						}
						if(ain>=5)	scomap[i][j]=100000; 						//六连分最高
						else if(ain==4){
							if(blankn==2){					//活五 
								scomap[i][j]=92000;
								if(qi=='H') scomap[i][j]+=100;		//黑棋ai先手，进攻加权 
							}
							else if(blankn==1){				//冲五 
								scomap[i][j]=90000;
								if(qi=='H') scomap[i][j]+=100;
							}
						}
						else if(ain==3){
							if(blankn==2){					//活四 
								scomap[i][j]=81000;
								if(qi=='H') scomap[i][j]+=100;
							}
							else if(blankn==1){				//眠四 
								scomap[i][j]=80000;
								if(qi=='H') scomap[i][j]+=100;
							}
						}
						else if(ain==2){
							if(blankn==2){					//活三 
								scomap[i][j]=71000;
								if(qi=='H') scomap[i][j]+=100;
							}
							else if(blankn==1){				//眠三 
								scomap[i][j]=10000;
								if(qi=='H') scomap[i][j]+=100;
							}
						}
						else if(ain==1){
							if(blankn==2){					//活二 
								scomap[i][j]=61000;
								if(qi=='H') scomap[i][j]+=100;
							}
							else if(blankn==1){				//眠二 
								scomap[i][j]=60000;
								if(qi=='H') scomap[i][j]+=100;
							}
						}
						blankn=0;
						for(int k=1;k<=5;k++){				//每个方向共5个位置 
							if(legitimate(i+mx*k,j+my*k)&&map[i+mx*k][j+my*k]==eni) enin++;		//敌方的棋 
							else if(legitimate(i+mx*k,j+my*k)&&map[i+mx*k][j+my*k]=='+'){		//空格 
								blankn++;
								break;
							}
							else break;						//超过边界或者被敌方棋子卡住 
						}
						for(int k=1;k<=5;k++){				//每个方向共5个位置,反方向 
							if(legitimate(i+mx*k,j+my*k)&&map[i+mx*k][j+my*k]==eni) enin++;		//敌方的棋 
							else if(legitimate(i+mx*k,j+my*k)&&map[i+mx*k][j+my*k]=='+'){		//空格 
								blankn++;
								break;
							}
							else break;						//超过边界或者被敌方棋子卡住 
						}
						if(enin>=5)	scomap[i][j]=99999; 						//六连分最高
						else if(enin==4){
							if(blankn==2){					//活五 
								scomap[i][j]=91000;
								if(qi=='O') scomap[i][j]+=100;		//白棋ai后手，防御加权，但对5棋的防御仍应该低于进攻 
							}
							else if(blankn==1){				//冲五 
								scomap[i][j]=89999;
								if(qi=='O') scomap[i][j]+=100;		
							}
						}
						else if(enin==3){
							if(blankn==2){					//活四 
								scomap[i][j]=81000;
								if(qi=='O') scomap[i][j]+=100;
							}
							else if(blankn==1){				//眠四 
								scomap[i][j]=80000;
								if(qi=='O') scomap[i][j]+=100;
							}
						}
						else if(enin==2){
							if(blankn==2){					//活三 
								scomap[i][j]=71000;
								if(qi=='O') scomap[i][j]+=100;
							}
							else if(blankn==1){				//眠三 
								scomap[i][j]=10000;
								if(qi=='O') scomap[i][j]+=100;
							}
						}
						else if(enin==1){
							if(blankn==2){					//活二 
								scomap[i][j]=61000;
								if(qi=='O') scomap[i][j]+=100;
							}
							else if(blankn==1){				//眠二 
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
void aiinput(int ai){				//int ai 代表ai先后手，1先手，2后手 
	if(ai==1) num++;
	printf("Round : %d",num);		//先显示第几回合
	if(ai==1) cout<<"Gamer 1's x and y :";
	else cout<<"Gamer 2's x and y :";
	if(ai==1) valuemap('H');		//计算每个位置的价值 
	else valuemap('O');
	int maxvalue(0),maxn(0),xm[401],ym[401];	//maxvlaue最大价值，maxn最大价值的数量，xm和ym数组用来保存最大价值位置的坐标
	for(int i=0;i<msize;i++){					//求出最大价值 
		for(int j=0;j<msize;j++) if(scomap[i][j]>maxvalue) maxvalue=scomap[i][j];
	}
	for(int i=0;i<msize;i++){
		for(int j=0;j<msize;j++){
			if(scomap[i][j]==maxvalue){
				xm[maxn]=i;
				ym[maxn]=j;
				maxn++;
			}
		}
	}
	srand((unsigned)time(0));				//找到一个随机数 
	int index=rand()%maxvalue;
	x=xm[index];
	y=ym[index];
}
int main() {

}
