#include <SFML/Graphics.hpp>
#include<iostream>
#include<cstdio>
#include<windows.h>
using namespace std;
const bool ALIVE = true;
const bool DEAD = false;
class GAMEOFLIVE
{
public:
	void init();
	void change();
	~GAMEOFLIVE() = default;
	GAMEOFLIVE(int n) : maxn(n) { 
		graph = new bool*[maxn];
		for (int i = 0; i < maxn; i++)
			graph[i] = new bool[maxn]; 
	};
	bool get_value(int i, int j) {
		return graph[i][j];
	};
	void print();
private:
	int cnt_num(int i, int j);
	//bool graph[maxn][maxn];
	bool **graph;
	const int maxn; 
};

void GAMEOFLIVE::init()
{
	srand(time(NULL));
	for (int i = 1; i < maxn - 1; i++)
	{
		for (int j = 1; j < maxn - 1; j++)
		{
			graph[i][j] = (rand() % 2) ? ALIVE : DEAD;
		}
	}
}


void GAMEOFLIVE::change()
{
//	bool graph2[maxn][maxn];
	bool **graph2;
	graph2 = new bool*[maxn];
	for (int i = 0; i < maxn; i++)
		graph2[i] = new bool[maxn];

	for (int i = 1; i < maxn - 1; i++)
	{
		for (int j = 1; j < maxn - 1; j++)
		{
			int t = cnt_num(i, j);
			if (t == 3)
				graph2[i][j] = ALIVE;
			else if (t == 2)
				graph2[i][j] = graph[i][j];
			else
				graph2[i][j] = DEAD;
		}
	}

	for (int i = 1; i < maxn - 1; i++)
		for (int j = 1; j < maxn - 1; j++)
			graph[i][j] = graph2[i][j];
}

int GAMEOFLIVE::cnt_num(int ii, int jj)
{
	int dx[] = { -1 , 1 , 0 , 0 ,  1 , -1 , 1 , -1 };
	int dy[] = { 0 , 0 , 1 , -1 ,  -1 , 1 , 1 , -1 };

	int ans = 0;
	for (int i = 0; i < 8; i++)
		if (graph[ii + dx[i]][jj + dy[i]] == ALIVE)
			ans++;
	return ans;
}


void GAMEOFLIVE::print()
{
	for (int i = 1; i < maxn - 1; i++)
	{
		for (int j = 1; j < maxn - 1; j++)
		{
			if (graph[i][j] == ALIVE)
				printf("*");
			else
				printf("_");
		}
		printf("\n");
	}

	return;
}

/*
int main()
{
	GAMEOFLIVE test;
	test.init();
	while (true)
	{
		system("cls");
		test.change();
		test.print();
		Sleep(100);
	}
}
*/

int main()
{

	//sf::CircleShape shape(5.f);
	//sf::CircleShape shape2(10.f);
	//shape.setFillColor(sf::Color::Green);
	
	int n;
	cout << "请输入规模(建议大于等于10)" << endl;
	cin >> n; 
	int tt;
	cout << "请输入快慢(数字越小越快)" << endl; 
	cin >> tt;
	GAMEOFLIVE test(n);
	sf::RenderWindow window(sf::VideoMode(500, 500), "GameOfLive");
	//sf::CircleShape shape[n][n];
	sf::CircleShape **shape;
	shape = new sf::CircleShape*[n];
	for (int i = 0; i < n; i++)
		shape[i] = new sf::CircleShape[n];
	for (int i = 1; i < n - 1; i++)
	{
		for (int j = 1; j < n - 1; j++)
		{
			shape[i][j].setPosition(i * 30  + 2.0 , j * 30  + 3.0 );
			shape[i][j].setRadius( 5.0);
			shape[i][j].setFillColor(sf::Color::Green);
		}
	}

	// 隐藏控制台黑框窗口
	HWND hwnd;
	hwnd = FindWindow("ConsoleWindowClass", NULL); //处理顶级窗口的类名和窗口名称匹配指定的字符串,不搜索子窗口。  
	if (hwnd)
	{
		ShowWindow(hwnd, SW_HIDE);               //设置指定窗口的显示状态  
	}


	test.init(); 
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		test.change();
		//test.print();
		window.clear();
		for (int i = 1; i < n - 1; i++)
		{
			for (int j = 1; j < n - 1; j++)
			{
				if ( test.get_value(i, j) == ALIVE )
					window.draw(shape[i][j]);

			}
		}
		window.display();
		Sleep(tt);
	}
	return 0;
}
