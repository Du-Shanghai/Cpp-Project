#include <easyx.h>			// Reference graphics library header file
#include <conio.h>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<Windows.h>
#include"putperson.h"
using namespace std;
int patient = 0; //�������� 
int len;//���г���
int wid;//���п��
int hnum;
double rate1;
int  check_patient(int posx, int posy, int len, int wid);
class Person
{

	

public:
	int  x;//���ں�����
	int  y;//����������
	int index;         //��ר�� 
	int state;//״̬:-2���Ҹ���,-1��,0����,1����
//	static int patient;//��������
	Person()
	{
		state = -1;
		srand(int(time(0)));
	}

	void virtual move(int i) = 0;//�������ǵ��ƶ�
	bool insert()//���һ�����Ƿǻᱻ����Ⱦ   ���и��ۼ��� ����move 
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
Person* map[1000][1000];   //map ���� 
Person* people[100000];    //��¼���е��ˣ������˶�
class Location_em :public Person     //�� 
{
public:
	Location_em()
	{
		state = -1;
	}
	void move(int i) {   //�����ƶ� 
		return;
	}
};
bool check(int posx, int posy)//�������ط���û����
{
	if (posx < 0 || posy < 0 || posx >= len || posy >= wid)
		return false;
	if (map[posx][posy]->state == -1)//���û�˷�����
		return true;
	else//������˷��ؼ�
		return false;
}
Location_em e[100000];
int en = 0;
class Location_ge :public Person		//���벡�ˣ�û���ж������ᴫȾ 
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
class Location_pa :public Person    //���� 
{
public:

	friend void Findperson(int posx, int posy, int len, int wid);
	Location_pa()
	{
		state = 1;

	}
	void move(int i)   //���ƶ��Ĳ���   ���ˣ��������� 
	{
		int posx, posy;  //Ŀ�ĵ� 
		do {
			posx = gaussrand(13, x);  //���˵��ƶ������Լ� 
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
class Location_heath :public Person   //�������� 
{
public:
	int rate;//�������	
	Location_heath() {
		rate = rand() % 10;
		state = 0;

	}
	void move(int i)   //�������ƶ�    i��ʾ�ڼ����� 
	{
		int posx, posy;  //Ŀ�ĵ� 
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
			if (rate > 7)   //���� 
			{
				g[gn].index = index;
				g[gn].set(x, y);
				people[i] = &g[gn];
				map[x][y] = &g[gn++];

			}
			else				//��Ϊ���߸�Ⱦ�� ao wu~ 
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
	int num;//�����˿���
	int i = 0;//��������
	int j = 0;//��������
	cout << "********����������ģ�����鴫�����********" << endl;
ahead3:
	cout << "********������ü���Ⱦ���ʣ�";
	cin >> rate1;
	if (rate1 <= 0 || rate1 > 1)
	{
		cout << "********��������ȷ��Ⱦ���ʣ�********" << endl;
		goto ahead3;
	}
ahead1:
	cout << "********������������д�С����*���Ҿ�С��1000����";
	cin >> len >> wid;
	if (len >= 1000 || wid >= 1000)//������й����������û����¶�����д�С
	{
		cout << "********���й���********" << endl;
		goto ahead1;
	}
	if (len <= 0 || wid <= 0)//������г��Ȼ���Ϊ������
	{
		cout << "********��������ȷ�ĳ��д�С��********" << endl;
	}
ahead2:
	cout << "********���������������";
	cin >> num;
	if (num > len * wid)//����˿������࣬����������˿���
	{
		cout << "********�����˿ڹ��࣡********" << endl;
		goto ahead2;
	}
	if (num < 0)//����˿���Ϊ����
	{
		cout << "********��������ȷ���˿�����********" << endl;
		goto ahead2;
	}
	cout << "��ʼ���ɳ���" << endl;
	initgraph(len, wid, SHOWCONSOLE);
	for (int i = 0; i < len; i++)
		for (int j = 0; j < wid; j++)
			em[i][j].set(i, j);

	for (int i = 0; i < len; i++)
		for (int j = 0; j < wid; j++)
			map[i][j] = &em[i][j];
	cout << "��ʼ�����˿�" << endl;
	int N = len / 2, M = wid / 2;

	int tx, ty;//Ŀ��λ�� ��������λ��չ����̬�ֲ� 
	for (int i = 0, count = 0; i < num; i++)
	{
		do {
			tx = gaussrand(len / 5, N);    //��һ������Ϊ���� 
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
	cout << "�������" << endl;
	//��ͼ�ο�
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
			cout << "��Ⱦ�����ѳ���80% " << k << "��" << endl;
			flag = 1;
		}
		for (int i = 0; i < num; i += (num > 10000 ? num * 0.00001 + rand() % 10 : 1))
		{
			people[i]->move(people[i]->index);
			

		}	cout << "����������" << patient << endl;
		FlushBatchDraw();
	}
	cleardevice();
	EndBatchDraw();
	settextstyle(len/8,0, _T("����"));	
	outtextxy(len/7, wid / 3, "��ȫ����Ⱦ!");
	getchar();
	
	cout << k << "��";
	return 0;
}
int  check_patient(int posx, int posy, int len, int wid)   //��Χ���˼�⣬������������insert 
{
	int num = 0; //ͳ�Ʋ���������Խ��Խ���׸�Ⱦ 
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