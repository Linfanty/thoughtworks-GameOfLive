#include<bits/stdc++.h>
#include<windows.h>
using namespace std ;
const bool ALIVE = true ;
const bool DEAD = false ;
const int maxn = 10;
class GAMEOFLIVE
{
	public:
		void init();
		void change();
		void print() ;
	private:
		int cnt_num( int i , int j ) ;
		bool graph[maxn][maxn];
};

void GAMEOFLIVE::init()
{
	srand(time(NULL));
	for( int i = 1 ; i < maxn -1 ; i++)
	{
		for( int j = 1 ; j < maxn - 1 ; j++)
		{
			graph[i][j] = ( rand() % 2 ) ? ALIVE : DEAD ;
		}
	}
}


void GAMEOFLIVE::change()
{
	bool graph2[maxn][maxn];
	
	for( int i = 1 ; i < maxn - 1 ; i++)
	{
		for( int j = 1 ; j < maxn - 1  ; j++)
		{
			int t = cnt_num( i , j ) ;
			if( t == 3 )
				graph2[i][j] = ALIVE ;
			else if( t == 2 )
				;
			else 
				graph2[i][j] = DEAD ;
		}
	}

	for( int i = 1 ; i < maxn  - 1 ; i++)
		for( int j = 1 ; j < maxn - 1  ; j++)
			graph[i][j] = graph2[i][j];
}

int GAMEOFLIVE::cnt_num( int ii , int jj )
{
	int dx[] = { -1 , 1 , 0 , 0 ,  1 , -1 , 1 , -1 } ;
	int dy[] = { 0 , 0 , 1 , -1 ,  -1 , 1 , 1 , -1 } ;

	int ans = 0 ; 
	for( int i = 0 ; i < 8 ; i++)
		if( graph[ ii + dx[i] ][ jj+dy[i] ] == ALIVE )
			ans++;
	return ans ;
}


void GAMEOFLIVE::print()
{
	for( int i = 1 ; i < maxn - 1 ; i++)
	{
		for( int j = 1 ; j < maxn -1 ; j++)
		{
			if( graph[i][j] == ALIVE )
				printf("*");
			else 
				printf("_");
		}
		printf("\n");
	}

	return ;
}




int main()
{
	GAMEOFLIVE demo; 
	demo.init();

	while(true)
	{
		demo.change();
		Sleep(100);
		system("cls");
		demo.print();
	}
	return 0 ;
}

