#include <easyx.h>			// Reference graphics library header file
#include <conio.h>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<Windows.h>
#include"putperson.h"
using namespace std;
int patient = 0; //病人数量 
int len;//城市长度
int wid;//城市宽度
int hnum;
double rate1;
int  check_patient(int posx, int posy, int len, int wid);
class Person
{

	

public:
	int  x;//所在横坐标
	int  y;//所在纵坐标
	int index;         //人专用 
	int state;//状态:-2自我隔离,-1空,0健康,1发病
//	static int patient;//病人数量
	Person()
	{
		state = -1;
		srand(int(time(0)));
	}

	void virtual move(int i) = 0;//用于人们的移动
	bool insert()//检测一个人是非会被被感染   进行概论计算 辅助move 
	{
		double r = (double)(rand() % 100) + 1.0;  //1-100
		if (rate1 * check_patient(x, y, len, wid) * 100.0 >= r)
			return true;
		else
			return false;
	}
	void set(int x1, int y1)
	{
		x = x1, y = y1;
	}

};
Person* map[1000][1000];   //map 城市 
Person* people[100000];    //记录所有的人，方便运动
class Location_em :public Person     //空 
{
public:
	Location_em()
	{
		state = -1;
	}
	void move(int i) {   //不会移动 
		return;
	}
};
bool check(int posx, int posy)//检查这个地方有没有人
{
	if (posx < 0 || posy < 0 || posx >= len || posy >= wid)
		return false;
	if (map[posx][posy]->state == -1)//如果没人返回真
		return true;
	else//如果有人返回假
		return false;
}
Location_em e[100000];
int en = 0;
class Location_ge :public Person		//隔离病人，没有行动力不会传染 
{
public:

	Location_ge()
	{

		state = -2;
	}
	void move(int i)
	{
		return;
	}
};
Location_ge* g = new Location_ge[100000];
int gn = 0;
void Findperson(int posx, int posy, int len, int wid);
class Location_pa :public Person    //病人 
{
public:

	friend void Findperson(int posx, int posy, int len, int wid);
	Location_pa()
	{
		state = 1;

	}
	void move(int i)   //会移动的病人   来了，他们来了 
	{
		int posx, posy;  //目的地 
		do {
			posx = gaussrand(13, x);  //病人的移动能力稍减 
			posy = gaussrand(13, y);
		} while (check(posx, posy) == 0);
		Person* t;
		t = map[posx][posy];
		map[posx][posy] = map[x][y];
		map[x][y] = t;
		x = posx, y = posy;
		map[x][y] = people[i];
		Findperson(x, y, len, wid);
		setfillcolor(RED);
		setlinecolor(RED);
		fillcircle(posx, posy, 1);
	}

};
Location_pa* p = new Location_pa[100000];
int pn = 0;
class Location_heath :public Person   //健康人数 
{
public:
	int rate;//隔离概率	
	Location_heath() {
		rate = rand() % 10;
		state = 0;

	}
	void move(int i)   //健康人移动    i表示第几号人 
	{
		int posx, posy;  //目的地 
		do {
			posx = gaussrand(23, x);
			posy = gaussrand(23, y);
		} while (check(posx, posy) == 0);
		Person* t;
		t = map[posx][posy];
		map[posx][posy] = map[x][y];
		map[x][y] = t;
		x = posx, y = posy;
		map[x][y] = people[i];
		if (insert() == true)
		{
			hnum--;
			if (rate > 7)   //隔离 
			{
				g[gn].index = index;
				g[gn].set(x, y);
				people[i] = &g[gn];
				map[x][y] = &g[gn++];

			}
			else				//成为行走感染者 ao wu~ 
			{
				p[pn].index = index;
				p[pn].set(x, y);
				map[x][y] = &p[pn];
				people[i] = &p[pn++];
			}
			patient++;
		}
		setfillcolor(WHITE);
		setlinecolor(WHITE);
		fillcircle(posx, posy, 1);
	}

};


bool size_check(int len, int wid, int x, int y)
{
	if (x >= len || x < 0)  return false;
	if (y >= wid || y < 0)  return false;
	if (map[x][y]->state != -1) return false;
	return true;
}
Location_em em[1000][1000];
Location_heath* h = new Location_heath[100000];
int hn = 0;
int main()
{
	int num;//城市人口数
	int i = 0;//辅助变量
	int j = 0;//辅助变量
	cout << "********本程序用于模拟疫情传播情况********" << endl;
ahead3:
	cout << "********请输入该疾病染病率：";
	cin >> rate1;
	if (rate1 <= 0 || rate1 > 1)
	{
		cout << "********请输入正确的染病率！********" << endl;
		goto ahead3;
	}
ahead1:
	cout << "********现在请输入城市大小（长*宽，且均小于1000）：";
	cin >> len >> wid;
	if (len >= 1000 || wid >= 1000)//如果城市过大，则请求用户重新定义城市大小
	{
		cout << "********城市过大！********" << endl;
		goto ahead1;
	}
	if (len <= 0 || wid <= 0)//如果城市长度或宽度为非正数
	{
		cout << "********请输入正确的城市大小！********" << endl;
	}
ahead2:
	cout << "********请输入城市人数：";
	cin >> num;
	if (num > len * wid)//如果人口数过多，则从新输入人口数
	{
		cout << "********城市人口过多！********" << endl;
		goto ahead2;
	}
	if (num < 0)//如果人口数为负数
	{
		cout << "********请输入正确的人口数！********" << endl;
		goto ahead2;
	}
	cout << "开始生成城市" << endl;
	initgraph(len, wid, SHOWCONSOLE);
	for (int i = 0; i < len; i++)
		for (int j = 0; j < wid; j++)
			em[i][j].set(i, j);

	for (int i = 0; i < len; i++)
		for (int j = 0; j < wid; j++)
			map[i][j] = &em[i][j];
	cout << "开始布置人口" << endl;
	int N = len / 2, M = wid / 2;

	int tx, ty;//目标位置 ，以中心位置展开正态分布 
	for (int i = 0, count = 0; i < num; i++)
	{
		do {
			tx = gaussrand(len / 5, N);    //第一个数据为方差 
			ty = gaussrand(wid / 5, M);
		} while (size_check(len, wid, tx, ty) == false);
		if (count < 20)
		{
			p[pn].index = count;
			p[pn].set(tx, ty);
			map[tx][ty] = &p[pn];
			people[count] = &p[pn];
			count++;
			patient++;
			setfillcolor(RED); 
			setlinecolor(RED);
			fillcircle(tx, ty, 1);
		}

		else
		{
			h[hn].index = i;
			h[hn].set(tx, ty);
			map[tx][ty] = &h[hn];
			people[i] = &h[hn++];
			setfillcolor(WHITE);
			setlinecolor(WHITE);
			fillcircle(tx, ty, 1);
		}

	}
	cout << "布置完成" << endl;
	//接图形库
	srand(int(time(0)));
	int k = 0;//k=days;
	tx = 0, ty = 0;
	int flag = 0;
	getchar();
	BeginBatchDraw();
	for (k = 0; patient < num; k++)
	{
		cleardevice();
		//getchar();
		if (patient > num * 0.8 && flag == 0)
		{
			cout << "感染人数已超过80% " << k << "天" << endl;
			flag = 1;
		}
		for (int i = 0; i < num; i += (num > 10000 ? num * 0.00001 + rand() % 10 : 1))
		{
			people[i]->move(people[i]->index);
			

		}	cout << "病人数量：" << patient << endl;
		FlushBatchDraw();
	}
	cleardevice();
	EndBatchDraw();
	settextstyle(len/8,0, _T("宋体"));	
	outtextxy(len/7, wid / 3, "已全部感染!");
	getchar();
	
	cout << k << "天";
	return 0;
}
int  check_patient(int posx, int posy, int len, int wid)   //周围病人检测，用来辅助函数insert 
{
	int num = 0; //统计病人数，人越多越容易感染 
	if (posx < len && posy + 1 < wid)
	{
		if (map[posx][posy + 1]->state == 1)  num++;
	}

	if (posx + 1 < len && posy < wid)
	{
		if (map[posx + 1][posy]->state == 1)  num++;
	}

	if (posx - 1 > 0 && posy + 1 < wid)
	{
		if (map[posx - 1][posy + 1]->state == 1)  num++;
	}

	if (posx - 1 > 0 && posy - 1 > 0)
	{
		if (map[posx - 1][posy - 1]->state == 1)  num++;
	}

	if (posx - 1 > 0 && posy < wid)
	{
		if (map[posx - 1][posy]->state == 1)  num++;
	}

	if (posx + 1 < len && posy - 1 > 0)
	{
		if (map[posx + 1][posy - 1]->state == 1)  num++;
	}

	if (posx < len && posy - 1>0)
	{
		if (map[posx][posy - 1]->state == 1)  num++;
	}

	if (posx + 1 < len && posy + 1 < wid)
	{
		if (map[posx + 1][posy + 1]->state == 1)  num++;
	}
	return num;
}
void Findperson(int posx, int posy, int len, int wid)
{
	int num = 0;

	if (posx < len && posy + 1 < wid)
	{
		if (map[posx][posy + 1]->state == 0)
			if ((double)(rand() % 100) + 1 <= rate1 * 100)
			{
				p[pn].index = map[posx][posy + 1]->index;
				p[pn].set(posx, posy + 1);
				people[p[pn].index] = &p[pn];
				map[posx][posy + 1] = &p[pn++]; num++;
				setfillcolor(RED);
				setlinecolor(RED);
				fillcircle(posx,posy+1, 1);
			}
	}

	if (posx + 1 < len && posy < wid)
	{
		if (map[posx + 1][posy]->state == 0)
			if ((double)(rand() % 100) + 1 <= rate1 * 100)
			{
				p[pn].index = map[posx + 1][posy]->index;
				p[pn].set(posx + 1, posy);
				people[p[pn].index] = &p[pn];
				map[posx + 1][posy] = &p[pn++]; num++;
				setfillcolor(RED);
				setlinecolor(RED);
				fillcircle(posx+1, posy, 1);
			}
	}

	if (posx - 1 > 0 && posy + 1 < wid)
	{
		if (map[posx - 1][posy + 1]->state == 0)
			if ((double)(rand() % 100) + 1 <= rate1 * 100)
			{
				p[pn].index = map[posx - 1][posy + 1]->index;
				p[pn].set(posx - 1, posy + 1);
				people[p[pn].index] = &p[pn];
				map[posx - 1][posy + 1] = &p[pn++]; num++;
				setfillcolor(RED);
				setlinecolor(RED);
				fillcircle(posx-1, posy + 1, 1);
			}
	}

	if (posx - 1 > 0 && posy - 1 > 0)
	{
		if (map[posx - 1][posy - 1]->state == 0)
			if ((double)(rand() % 100) + 1 <= rate1 * 100)
			{
				p[pn].index = map[posx - 1][posy - 1]->index;
				p[pn].set(posx - 1, posy - 1);
				people[p[pn].index] = &p[pn];
				map[posx - 1][posy - 1] = &p[pn++]; num++;
				setfillcolor(RED);
				setlinecolor(RED);
				fillcircle(posx-1, posy -1, 1);
			}
	}

	if (posx - 1 > 0 && posy < wid)
	{
		if (map[posx - 1][posy]->state == 0)
			if ((double)(rand() % 100) + 1 <= rate1 * 100)
			{
				p[pn].index = map[posx - 1][posy]->index;
				p[pn].set(posx - 1, posy);
				people[p[pn].index] = &p[pn];
				map[posx - 1][posy] = &p[pn++]; num++;
				setfillcolor(RED);
				setlinecolor(RED);
				fillcircle(posx-1, posy, 1);
			}
	}

	if (posx + 1 < len && posy - 1 > 0)
	{
		if (map[posx + 1][posy - 1]->state == 0)
			if ((double)(rand() % 100) + 1 <= rate1 * 100)
			{
				p[pn].index = map[posx + 1][posy - 1]->index;
				p[pn].set(posx + 1, posy - 1);
				people[p[pn].index] = &p[pn];
				map[posx + 1][posy - 1] = &p[pn++]; num++;
				setfillcolor(RED);
				setlinecolor(RED);
				fillcircle(posx+1, posy - 1, 1);
			}
	}

	if (posx < len && posy - 1>0)
	{
		if (map[posx][posy - 1]->state == 0)
			if ((double)(rand() % 100) + 1 <= rate1 * 100)
			{
				p[pn].index = map[posx][posy - 1]->index;
				p[pn].set(posx, posy - 1);
				people[p[pn].index] = &p[pn];
				map[posx][posy - 1] = &p[pn++]; num++;
				setfillcolor(RED);
				setlinecolor(RED);
				fillcircle(posx, posy - 1, 1);
			}
	}

	if (posx + 1 < len && posy + 1 < wid)
	{
		if (map[posx + 1][posy + 1]->state == 0)
			if ((double)(rand() % 100) + 1 <= rate1 * 100)
			{
				p[pn].index = map[posx + 1][posy + 1]->index;
				p[pn].set(posx + 1, posy + 1);
				people[p[pn].index] = &p[pn];
				map[posx + 1][posy + 1] = &p[pn++]; num++;
				setfillcolor(RED);
				setlinecolor(RED);
				fillcircle(posx+1, posy + 1, 1);
			}
	}
	patient += num;
}