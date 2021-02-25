// HW4BFSDFS.cpp : 定義主控台應用程式的進入點。
//


#include <iostream>
#include<cstdlib>
#include<iomanip>
#include<queue>
using namespace std;
int second[30][30] = { 0 };
int visit[30][30] = { 0 };
int visit_3[30][30] = { 0 };
int third[30][30] = { 0 };
int fire[30][30] = { 0 };
int visit_fire[30][30] = { 0 };
void go(int **a, int i, int j, int r, int c, int x);

int main()
{
	int r, c = 0;
	cin >> r >> c;
	int f, g = 0;
	cin >> f >> g;
	char **map;
	map = new char*[r];
	for (int i = 0; i < r; i++)
		map[i] = new char[c];
	int **werit;
	werit = new int*[r];
	for (int i = 0; i < r; i++)
		werit[i] = new int[c];
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++) {
			cin >> map[i][j];
		}
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++) {
			if (map[i][j] == '+')werit[i][j] = 1;
			else if (map[i][j] == '%')werit[i][j] = -1;
			else if (map[i][j] == '$')werit[i][j] = 0;
		}
	cout << "[1]show the map :" << endl;

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cout << setw(2) << werit[i][j];
		}
		cout << endl;
	}
	cout << "===========================================" << endl;
	int x = 1;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++) {
			while (visit[i][j] == 0 && werit[i][j] != 1)
			{
				second[i][j] = x;
				visit[i][j] = 1;
				go(werit, i, j, r, c, x);
				x += 1;
			}
		}
	cout << "[2]show the map :" << endl;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++)
		{
			cout << setw(3) << second[i][j];
		}
		cout << endl;
	}
	cout << endl << "The number of regions is? " << x - 1 << endl;
	cout << "===========================================" << endl;
	//third question
	queue<int>quack;
	int u, s = 0;
	int o, p = 0;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
		{
			if (werit[i][j] == -1)
			{
				visit_3[i][j] = 1;
				o = i;
				p = j;
				int w = i * c + j;
				quack.push(w);
			}
		}
	int distance = 50;

	while (!quack.empty())
	{
		int current = quack.front();
		quack.pop();

		int m = current %c;
		int b = (current - m) / c;
		//cout <<"current"<<current<< "b" << b << "m" << m << endl;
		if (m + 1 < c && werit[b][m + 1] == 0 && visit_3[b][m + 1] == 0)
		{
			//cout << "向右" << endl;
			visit_3[b][m + 1] = 1;
			third[b][m + 1] = third[b][m] + 1;
			int w = b * c + m + 1;
			if (m + 1 == c - 1)
			{
				if (distance > third[b][m + 1]) {
					distance = third[b][m + 1];
				}
			}
			quack.push(w);
		}
		if (m - 1 >= 0 && werit[b][m - 1] == 0 && visit_3[b][m - 1] == 0)
		{
			//cout << "向左" << endl;
			visit_3[b][m - 1] = 1;
			third[b][m - 1] = third[b][m] + 1;//知道因為小戴是-1
			int w = b * c + m - 1;
			if (m - 1 == 0)
			{
				if (distance > third[b][m - 1]) {
					distance = third[b][m - 1];
				}
			}
			quack.push(w);
		}
		if (b + 1 < r && werit[b + 1][m] == 0 && visit_3[b + 1][m] == 0)
		{
			//cout << "向下" << endl;
			visit_3[b + 1][m] = 1;
			third[b + 1][m] = third[b][m] + 1;
			int w = (b + 1) * c + m;
			if (b + 1 == r - 1) //打蟲::記得矩陣是從0開始
			{
				if (distance > third[b + 1][m]) {
					distance = third[b + 1][m];
				}
			}
			quack.push(w);
		}
		if (b - 1 >= 0 && werit[b - 1][m] == 0 && visit_3[b - 1][m] == 0)
		{
			//cout << "向上" << endl;
			visit_3[b - 1][m] = 1;
			third[b - 1][m] = third[b][m] + 1;
			int w = (b - 1) * c + m;
			if (b - 1 == 0)
			{
				if (distance > third[b - 1][m]) {
					distance = third[b - 1][m];
				}
			}
			quack.push(w);
		}

	}
	if (o == 0 || p == 0 || o == r-1 || p == c-1)//解決小戴原本就在邊界
		distance = 0;
	third[o][p] = -1;
	if (distance == 50)distance = -1;
	cout << "[3]show the map :" << endl;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++)
		{
			cout << setw(3) << third[i][j];
		}
		cout << endl;
	}
	cout << endl << "Is there a minmum path? " << distance;
	cout << endl << "===========================================" << endl;
	//第四題火源
	queue<int>fire_queue;

	visit_fire[f][g] = 1;
	int h = f * c + g;
	int distance_fire = 50;
	fire_queue.push(h);
	while (!fire_queue.empty())
	{
		int current = fire_queue.front();
		fire_queue.pop();
		int m = current %c;
		int b = (current - m) / c;
		if (m + 1 < c && werit[b][m + 1] != 1 && visit_fire[b][m + 1] == 0)
		{
			visit_fire[b][m + 1] = 1;
			fire[b][m + 1] = fire[b][m] + 1;
			int w = b * c + m + 1;
			/*		if (m + 1 == c)
					{
						if (distance_fire>fire[b][m + 1])
							distance_fire = fire[b][m + 1];
					}*/
			fire_queue.push(w);
		}
		if (m - 1 >= 0 && werit[b][m - 1] != 1 && visit_fire[b][m - 1] == 0)
		{
			visit_fire[b][m - 1] = 1;
			fire[b][m - 1] = fire[b][m] + 1;//知道因為小戴是-1
			int w = b * c + m - 1;
			if (m - 1 == 0)
			{
				if (distance_fire > fire[b][m - 1])
					distance_fire = fire[b][m - 1];
			}
			fire_queue.push(w);
		}
		if (b + 1 < r && werit[b + 1][m] != 1 && visit_fire[b + 1][m] == 0)
		{
			visit_fire[b + 1][m] = 1;
			fire[b + 1][m] = fire[b][m] + 1;
			int w = (b + 1) * c + m;
			//if (b + 1 == r-1)
			//{
			//	if (distance_fire>fire[b + 1][m])
			//		distance_fire = fire[b + 1][m];
			//}
			fire_queue.push(w);
		}
		if (b - 1 >= 0 && werit[b - 1][m] != 1 && visit_fire[b - 1][m] == 0)
		{
			visit_fire[b - 1][m] = 1;
			fire[b - 1][m] = fire[b][m] + 1;
			int w = (b - 1) * c + m;
			//if (b - 1 == 0)
			//{
			//	if (distance_fire>fire[b - 1][m])
			//		distance_fire = fire[b - 1][m];
			//}
			fire_queue.push(w);
		}
		if (b - 1 >= 0 && m - 1 >= 0 && werit[b - 1][m - 1] != 1 && visit_fire[b - 1][m - 1] == 0)
		{
			visit_fire[b - 1][m - 1] = 1;
			fire[b - 1][m - 1] = fire[b][m] + 1;
			int w = (b - 1) * c + m - 1;
			/*		if (b - 1 == 0)
					{
						if (distance_fire>fire[b - 1][m - 1])
							distance_fire = fire[b - 1][m - 1];
					}*/
			fire_queue.push(w);
		}
		if (b - 1 >= 0 && m + 1 < c && werit[b - 1][m + 1] != 1 && visit_fire[b - 1][m + 1] == 0)
		{
			visit_fire[b - 1][m + 1] = 1;
			fire[b - 1][m + 1] = fire[b][m] + 1;
			int w = (b - 1) * c + m + 1;
			//if (b - 1 == 0)
			//{
			//	if (distance_fire>fire[b - 1][m + 1])
			//		distance_fire = fire[b - 1][m + 1];
			//}
			fire_queue.push(w);
		}
		if (b + 1 < r && m - 1 >= 0 && werit[b + 1][m - 1] != 1 && visit_fire[b + 1][m - 1] == 0)
		{
			visit_fire[b + 1][m - 1] = 1;
			fire[b + 1][m - 1] = fire[b][m] + 1;
			int w = (b + 1) * c + m - 1;
			//if (b - 1 == 0)
			//{
			//	if (distance_fire>fire[b - 1][m])
			//		distance_fire = fire[b - 1][m];
			//}
			fire_queue.push(w);
		}
		if (b + 1 < r && m + 1 < c && werit[b + 1][m + 1] != 1 && visit_fire[b + 1][m + 1] == 0)
		{
			visit_fire[b + 1][m + 1] = 1;
			fire[b + 1][m + 1] = fire[b][m] + 1;
			int w = (b + 1) * c + m + 1;
			//if (b - 1 == 0)
			//{
			//	if (distance_fire>fire[b - 1][m])
			//		distance_fire = fire[b - 1][m];
			//}
			fire_queue.push(w);
		}

	}
	fire[f][g] = -1;
	cout << "[4]show the map :" << endl;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++)
		{
			cout << setw(3) << fire[i][j];
		}
		cout << endl;
	}
	//第四題火源---->有無跑出
	int datastr = 50;
	int z = 0;
	int v = 0;
	{
		int i = 0;
		for (int j = 0; j < c; j++)
		{
			if (third[i][j] > 0)
			{
				if (third[i][j] < fire[i][j]) {

					int sample = third[i][j];
					if (datastr > sample)
						datastr = sample;
				}
				else if (third[i][j] > fire[i][j] && fire[i][j] == 0)
				{
					z = 1;
				}
				else if (third[i][j] > fire[i][j] && fire[i][j] != -1)
				{
					v = 1;
				}
			}
		}
	}
	int haha=0;
	{
		int i = r - 1;
		for (int j = 0; j < c; j++)
		{
			if (third[i][j] > 0)
			{
				if (third[i][j] < fire[i][j]) {
                    haha=1;
					int sample = third[i][j];
					if (datastr > sample)
						datastr = sample;
				}
				else if (third[i][j] > fire[i][j] && fire[i][j] == 0)
				{
					z = 1;
				}
				else if (third[i][j] > fire[i][j] && fire[i][j] != -1)
				{
					v = 1;
				}
			}
		}
	}
	{
		int j = 0;
		for (int i = 0; i < r; i++)
		{
			if (third[i][j] > 0)
			{
				if (third[i][j] < fire[i][j]) {

					int sample = third[i][j];
					if (datastr > sample)
						datastr = sample;
				}
				else if (third[i][j] > fire[i][j] && fire[i][j] == 0)
				{
					z = 1;
				}
				else if (third[i][j] > fire[i][j] && fire[i][j] != -1)
				{
					v = 1;
				}
			}
		}
	}
	{
		int j = c - 1;
		for (int i = 0; i < r; i++)
		{
			if (third[i][j] > 0)
			{
				if (third[i][j] < fire[i][j]) {

					int sample = third[i][j];
					if (datastr > sample)
						datastr = sample;
				}
				else if (third[i][j] > fire[i][j] && fire[i][j] == 0)
				{
					z = 1;
				}
				else if (third[i][j] > fire[i][j] && fire[i][j] != -1)
				{
					v = 1;
				}
			}
		}
	}
	if (datastr == 50)datastr = -1;
	if (z == 1)datastr = distance;
	if (v == 1&&haha==0)datastr = -1;

	cout << endl << "Can they escape from the fire? " << datastr;


	//第四題火源
	for (int i = 0; i < r; i++)
		delete[]map[i];
	delete[]map;

	for (int i = 0; i < r; i++)
		delete[]werit[i];
	delete[]werit;

	return 0;
}

void go(int **a, int i, int j, int r, int c, int x) {
	if ((j + 1) < c&&a[i][j + 1] != 1 && visit[i][j + 1] == 0)
	{
		//cout << "A" << endl;
		visit[i][j + 1] = 1;
		second[i][j + 1] = x;
		go(a, i, j + 1, r, c, x);
	}
	if (j - 1 >= 0 && a[i][j - 1] != 1 && visit[i][j - 1] == 0)
	{
		//cout << "B" << endl;
		visit[i][j - 1] = 1;
		second[i][j - 1] = x;
		go(a, i, j - 1, r, c, x);
	}
	if (i - 1 >= 0 && a[i - 1][j] != 1 && visit[i - 1][j] == 0)
	{
		//cout << "C" << endl;
		visit[i - 1][j] = 1;
		second[i - 1][j] = x;
		go(a, i - 1, j, r, c, x);
	}
	if (i + 1 < r &&a[i + 1][j] != 1 && visit[i + 1][j] == 0)
	{
		//	cout << "D" << endl;
		visit[i + 1][j] = 1;
		second[i + 1][j] = x;
		go(a, i + 1, j, r, c, x);
	}

	//不能用else if 因為使用代表要第一個錯之後才能用
}
