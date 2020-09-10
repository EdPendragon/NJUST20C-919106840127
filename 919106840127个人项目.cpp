#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <windows.h>
#include <stdlib.h>
using namespace std;
int jin;							//判断是否有禁手
const int msize=20;					//棋盘长宽固定为20
int x,y,hx1,hx2,hy1,hy2,num(0);		//x，y为每次输入的棋子的坐标，hx1，hy1保存给用户1悔棋，hy2，hx2给用户2悔棋，num回合数
int scomap[20][20]= {0}; 			//给ai用来判断每个位置的价值
char map[20][20];         			//每次画的棋盘
bool nohand(int x,int y,char qi) {	//判断是否出现了禁手
	if(jin==0) return false;
	int ain(0),blankn(0),four(0),five(0);		//four和five分别代表下了该棋后出现的活/冲四和五的数量，超过一个则禁手
	for(int mx=-1; mx<2; mx++) {
		for(int my=-1; my<2; my++) {		//八个方向
			ain=0;
			blankn=0;
			if(mx==0&&my==0) continue;  //排除自己本身
			for(int k=1; k<=4; k++) {				//每个方向共4个位置
				if(x+mx*k>=0&&x+mx*k<msize&&y+my*k>=0&&y+my*k<msize&&map[x+mx*k][y+my*k]==qi) ain++;//自己方的棋
				else if(x+mx*k>=0&&x+mx*k<msize&&y+my*k>=0&&y+my*k<msize&&map[x+mx*k][y+my*k]=='+') {		//空格
					blankn++;
					break;
				} else break;						//超过边界或者被敌方棋子卡住
			}
			for(int k=1; k<=4; k++) {				//每个方向共4个位置(相反方向)
				if(x-mx*k>=0&&x-mx*k<msize&&y-my*k>=0&&y-my*k<msize&&map[x-mx*k][y-my*k]==qi) ain++;//自己方的棋
				else if(x-mx*k>=0&&x-mx*k<msize&&y-my*k>=0&&y-my*k<msize&&map[x-mx*k][y-my*k]=='+') {		//空格
					blankn++;
					break;
				} else break;						//超过边界或者被敌方棋子卡住
			}
			if(ain==4&&(blankn==1||blankn==2)) five++;  //活五和冲五
			else if(ain==3&&(blankn==1||blankn==2)) four++;   //活四和眠四
		}
	}
	if(four>=4||five>=4) return true;					//八个方向会将判断禁手的情况算两遍，所以大于等于4 
	else return false;
}
bool legitimate(int X,int Y) {		//判断落子位置是否合法
	if(X<0||X>=20||Y<0||Y>=20||map[X][Y]!='+') return false;
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
		for(int j=0; j<msize; j++) cout<<"  "<<map[j][i];					//打印每行棋盘,因为按行打印，y相同，所以是[j][i]
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
		        map[x-i][y]==map[x-i+5][y]&&map[x-i][y]!='+') return true;		//一开始没考虑到空棋盘时全是+的情况
	}
	for(int i=0; i<6; i++) {			//纵向判断
		if(y-i>=0&&y-i+5<msize&&
		        map[x][y-i]==map[x][y-i+1]&&
		        map[x][y-i]==map[x][y-i+2]&&
		        map[x][y-i]==map[x][y-i+3]&&
		        map[x][y-i]==map[x][y-i+4]&&
		        map[x][y-i]==map[x][y-i+5]&&map[x][y-i]!='+') return true;
	}
	for(int i=0; i<6; i++) {			//45度角判断
		if(y+i<msize&&y+i-5>=0&&x-i>0&&x-i+5<msize&&
		        map[x-i][y+i]==map[x-i+1][y+i+1]&&
		        map[x-i][y+i]==map[x-i+2][y+i+2]&&
		        map[x-i][y+i]==map[x-i+3][y+i+3]&&
		        map[x-i][y+i]==map[x-i+4][y+i+4]&&
		        map[x-i][y+i]==map[x-i+5][y+i+5]&&map[x-i][y+i]!='+') return true;
	}
	for(int i=0; i<6; i++) {			//135度角判断
		if(y-i>0&&y-i+5<msize&&x-i>0&&x-i+5<msize&&
		        map[x-i][y-i]==map[x-i+1][y-i+1]&&
		        map[x-i][y-i]==map[x-i+2][y-i+2]&&
		        map[x-i][y-i]==map[x-i+3][y-i+3]&&
		        map[x-i][y-i]==map[x-i+4][y-i+4]&&
		        map[x-i][y-i]==map[x-i+5][y-i+5]&&map[x-i][y-i]!='+') return true;
	}
	return false;
}
void upload(int X,int Y,int peo) {		//实时上传棋面信息
	if(peo==1) map[X][Y]='H';			//1号玩家下黑棋
	else map[X][Y]='O';					//2号玩家下白棋
}
void peoinput(int peo) {
	if(peo==1) num++;
	printf("Round : %d\n",num);		//先显示第几回合
	if(peo==1) cout<<"Gamer 1's x and y :";
	else cout<<"Gamer 2's x and y :";
	cin>>x>>y;
	while(peo==1&&nohand(x,y,'H')) {
		cout<<"Nohand!!!\n"<<endl<<"Please input again : ";
		cin>>x>>y;
	}
	if(x==-1&&y==-1) {				//假如x，y都是-1，则悔棋
		map[hx1][hy1]='+';
		map[hx2][hy2]='+';			//还原上一步的棋盘
		printmap();
		cout<<"Please input again : "<<endl;		//重新输入
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
	if(x==-1&&y==-1) {				//假如x，y再次都是-1，则再次悔棋
		map[hx1][hy1]='+';
		map[hx2][hy2]='+';			//还原上一步的棋盘
		printmap();
		cout<<"Please input again : "<<endl;		//重新输入
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
void valuemap(char qi) {				//定义scomap数组每一个空位的下棋价值,qi是棋色
	char eni;
	if(qi=='H') eni='O';
	else eni='H';
	if(qi=='H'&&num==1) {
		scomap[9][9]=100001;       	//假如ai先手且第一步，默认下在棋盘近似中心
	}
	int enin(0),ain(0),blankn(0); 	//代表一个方向上敌人的棋子数，电脑的棋子数，空白棋位
	for(int i=0; i<msize; i++) {
		for(int j=0; j<msize; j++) scomap[i][j]=0;		//价值清零
	}
	for(int i=0; i<msize; i++) {		//开始计算价值，采用网上比较流行的加权法，分为进攻、防守两种情况
		for(int j=0; j<msize; j++) {
			if(legitimate(i,j)&&map[i][j]=='+') {			//只有合法位置的空位才考虑
				if(qi=='H'&&nohand(i,j,'H')) {
					scomap[i][j]=-1;
					continue;
				}
				for(int mx=-1; mx<2; mx++) {
					for(int my=-1; my<2; my++) {				//一共八个方向
						enin=0;
						ain=0;
						blankn=0;
						if(mx==0&&my==0) continue;
						for(int k=1; k<=5; k++) {				//每个方向共5个位置
							if(i+mx*k>=0&&i+mx*k<msize&&j+my*k>=0&&j+my*k<msize&&map[i+mx*k][j+my*k]==qi) ain++;//自己方的棋
							else if(i+mx*k>=0&&i+mx*k<msize&&j+my*k>=0&&j+my*k<msize&&map[i+mx*k][j+my*k]=='+') {		//空格
								blankn++;
								break;
							} else break;						//超过边界或者被敌方棋子卡住
						}
						for(int k=1; k<=5; k++) {				//每个方向共5个位置,反方向
							if(i-mx*k>=0&&i-mx*k<msize&&j-my*k>=0&&j-my*k<msize&&map[i+mx*k][j+my*k]==qi) ain++;//自己方的棋
							else if(i-mx*k>=0&&i-mx*k<msize&&j-my*k>=0&&j-my*k<msize&&map[i+mx*k][j+my*k]=='+') {  		//空格
								blankn++;
								break;
							} else break;						//超过边界或者被敌方棋子卡住
						}
						if(ain>=5)	scomap[i][j]=100000; 						//六连分最高
						else if(ain==4) {
							if(blankn==2) {					//活五
								scomap[i][j]=92000;
								if(qi=='H') scomap[i][j]+=100;		//黑棋ai先手，进攻加权
							} else if(blankn==1) {				//冲五
								scomap[i][j]=90000;
								if(qi=='H') scomap[i][j]+=100;
							}
						} else if(ain==3) {
							if(blankn==2) {					//活四
								scomap[i][j]=81000;
								if(qi=='H') scomap[i][j]+=100;
							} else if(blankn==1) {				//眠四
								scomap[i][j]=80000;
								if(qi=='H') scomap[i][j]+=100;
							}
						} else if(ain==2) {
							if(blankn==2) {					//活三
								scomap[i][j]=71000;
								if(qi=='H') scomap[i][j]+=100;
							} else if(blankn==1) {				//眠三
								scomap[i][j]=10000;
								if(qi=='H') scomap[i][j]+=100;
							}
						} else if(ain==1) {
							if(blankn==2) {					//活二
								scomap[i][j]=61000;
								if(qi=='H') scomap[i][j]+=100;
							} else if(blankn==1) {				//眠二
								scomap[i][j]=60000;
								if(qi=='H') scomap[i][j]+=100;
							}
						}
						blankn=0;
						for(int k=1; k<=5; k++) {				//每个方向共5个位置
							if(i+mx*k>=0&&i+mx*k<msize&&j+my*k>=0&&j+my*k<msize&&map[i+mx*k][j+my*k]==eni) enin++;	//敌方的棋
							else if(i+mx*k>=0&&i+mx*k<msize&&j+my*k>=0&&j+my*k<msize&&map[i+mx*k][j+my*k]=='+') {	//空格
								blankn++;
								break;
							} else break;						//超过边界或者被敌方棋子卡住
						}
						for(int k=1; k<=5; k++) {				//每个方向共5个位置,反方向
							if(i-mx*k>=0&&i-mx*k<msize&&j-my*k>=0&&j-my*k<msize&&map[i+mx*k][j+my*k]==eni) enin++;	//敌方的棋
							else if(i-mx*k>=0&&i-mx*k<msize&&j-my*k>=0&&j-my*k<msize&&map[i+mx*k][j+my*k]=='+') {		//空格
								blankn++;
								break;
							} else break;						//超过边界或者被敌方棋子卡住
						}
						if(enin>=5)	scomap[i][j]=99999; 						//六连分最高
						else if(enin==4) {
							if(blankn==2) {					//活五
								scomap[i][j]=93000;
								if(qi=='O') scomap[i][j]+=100;		//白棋ai后手，防御加权，但对5棋的防御仍应该低于进攻
							} else if(blankn==1) {				//冲五
								scomap[i][j]=91000;
								if(qi=='O') scomap[i][j]+=100;
							}
						} else if(enin==3) {
							if(blankn==2) {					//活四
								scomap[i][j]=81000;
								if(qi=='O') scomap[i][j]+=100;
							} else if(blankn==1) {				//眠四
								scomap[i][j]=80000;
								if(qi=='O') scomap[i][j]+=100;
							}
						} else if(enin==2) {
							if(blankn==2) {					//活三
								scomap[i][j]=71000;
								if(qi=='O') scomap[i][j]+=100;
							} else if(blankn==1) {				//眠三
								scomap[i][j]=10000;
								if(qi=='O') scomap[i][j]+=100;
							}
						} else if(enin==1) {
							if(blankn==2) {					//活二
								scomap[i][j]=61000;
								if(qi=='O') scomap[i][j]+=100;
							} else if(blankn==1) {				//眠二
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
void aiinput(int ai) {				//int ai 代表ai先后手，1先手，2后手
	if(ai==1) num++;
	printf("Round : %d",num);		//先显示第几回合
	cout<<endl;
	if(ai==1) valuemap('H');		//计算每个位置的价值
	else valuemap('O');
	int maxvalue(0),maxn(0),xm[401],ym[401];	//maxvlaue最大价值，maxn最大价值的数量，xm和ym数组用来保存最大价值位置的坐标
	for(int i=0; i<msize; i++) {					//求出最大价值
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
	srand((unsigned)time(0));				//找到一个随机数
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
void clear() {						//清空地图，恢复num,其余int因为每次游戏都要重新输入所以不需要操作
	for(int i=0; i<msize; i++) {
		for(int j=0; j<msize; j++) map[i][j]='+';		//棋盘恢复原状
	}
	num=0;							//num归零
}
void pvp() {							//人人对战
	for(int i=0; i<200; i++) {
		peoinput(1);				//先手玩家操作
		upload(x,y,1);
		printmap();
		if(win(x,y)) {				//先手玩家胜利
			cout<<"The gamer 1 has won!!! Congratulation!!!\n";
			clear();
			break;
		}
		peoinput(2);				//后手玩家操作
		upload(x,y,2);
		printmap();
		if(win(x,y)) {				//后手玩家胜利
			cout<<"The gamer 2 has won!!! Congratulation!!!\n";
			clear();
			break;
		}
		if(num==200) {					//到达200回合，和棋了
			cout<<"Ther is no winer in this time.\n";
			clear();
			break;
		}
	}
}
void pve() {							//人机对战
	int hand,comp;					//玩家先后手
	cout<<"Please choose your number,1 or 2 ? : ";
	cin>>hand;
	if(hand==1) comp=2;
	else if(hand==2) comp=1;
	if(hand==1) {
		for(int i=0; i<200; i++) {	//玩家先手
			peoinput(hand);					//玩家下棋
			upload(x,y,hand);
			printmap();
			if(win(x,y)) {				//玩家胜利
				cout<<"The gamer "<<hand<<" has won!!! Congratulation!!!\n";
				clear();
				break;
			}
			aiinput(comp);					//电脑下棋
			upload(x,y,comp);
			printmap();
			if(win(x,y)) {
				cout<<"The gamer "<<comp<<" has won!!! Congratulation!!!\n";
				clear();
				break;
			}
			if(num==200) {					//到达200回合，和棋了
				cout<<"Ther is no winer in this time.\n";
				clear();
				break;
			}
		}
	} else {
		for(int i=0; i<200; i++) {		//电脑先手
			aiinput(comp);					//电脑下棋
			upload(x,y,comp);
			printmap();
			if(win(x,y)) {
				cout<<"The gamer "<<comp<<" has won!!! Congratulation!!!\n";
				clear();
				break;
			}
			peoinput(hand);					//玩家下棋
			upload(x,y,hand);
			printmap();
			if(win(x,y)) {				//玩家胜利
				cout<<"The gamer "<<hand<<" has won!!! Congratulation!!!\n";
				clear();
				break;
			}
			if(num==200) {					//到达200回合，和棋了
				cout<<"Ther is no winer in this time.\n";
				clear();
				break;
			}
		}
	}
}
void eve() {							//观看机机对战
	for(int i=0; i<200; i++) {
		aiinput(1);					//电脑1下棋
		upload(x,y,1);
		printmap();
		
		if(win(x,y)) {
			cout<<"The computer 1 has won!!! Congratulation!!!\n";
			clear();
			break;
		}
		aiinput(2);					//电脑2下棋
		upload(x,y,2);
		printmap();
		
		if(win(x,y)) {
			cout<<"The computer 1 has won!!! Congratulation!!!\n";
			clear();
			break;
		}
		if(num==200) {					//到达200回合，和棋了
			cout<<"Ther is no winer in this time.\n";
			clear();
			break;
		}
	}
}
int main() {
	cout<<"Do you want to have nohand? Please input 1 or 0 : ";			//选择是否有禁手
	cin>>jin;
	cout<<endl;
	while(1) {						//可循环输入进行游戏
		clear();						//首先初始化地图
		cout<<"Which model is what you want?\n";
		cout<<"The first one(1) is pvp, the second one(2) is pve, the third one(3) is watching eve.\n";
		cout<<"If you would like to quit the program, plearse input 0 : ";				//介绍语句
		int m;
		cin>>m;							//选择游戏模式
		if(m==1) pvp();
		else if(m==2) pve();
		else if(m==3) eve();
		else if(m==0) break;
		cout<<endl;
	}
	return 0;
}
