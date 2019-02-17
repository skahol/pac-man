#include<iostream>
using namespace std;
//#include<windows.h>			//---> to use Sleep(ms) .
#include<time.h>			// --> for srand and clock_t in delay()
#include<queue>
#include<conio.h>
#define n 14
#define m 24
// use of kbhit() defined under conio.h library
/**********************************************
	X	 obstacles
	#	 enemy
	*    player
	o    small fruit
	0    large fruit
    n/2 =enemy.
    enemy even horizantal mov
    odd than vertical
    toggle left right & top down.
************************************************/
static int score=0;
	char a[n][m]={
	{'A',' ',' ','X','X','o',' ',' ',' ',' ',' ',' ',' ','o','o','o','o','X','X',' ',' ','o','0',' '},
	{' ',' ',' ','X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','o',' ','X','X',' '},
	{' ',' ',' ',' ',' ',' ','X','X',' ',' ',' ',' ','X','X',' ',' ',' ',' ',' ','o',' ','X','X',' '},
	{'X','X',' ',' ',' ',' ','X','X',' ',' ',' ',' ','X','X',' ',' ',' ',' ',' ','o',' ',' ',' ',' '},
	{'X','X',' ',' ',' ',' ','X','X',' ',' ',' ',' ',' ',' ',' ',' ','X','X','o',' ',' ',' ',' ','o'},
	{'o',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','o',' ',' ',' ',' ','o'},
	{'o',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','o',' ',' ',' ',' ','o'},
	{'o',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','o',' ',' ',' ',' ','o'},
	{'o',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','o',' ',' ',' ',' ','o'},
	{'o',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','o',' ',' ',' ',' ','o'},
	{'o',' ','X','X','X',' ',' ',' ',' ',' ','o','o','X','X',' ',' ',' ',' ','o',' ',' ',' ',' ','o'},
	{'o',' ','X','X','X',' ',' ',' ',' ',' ','o','o','X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	{'o',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	{'0','o','X','o','o','o','o','o','o','X',' ',' ','o','o','o','o','o',' ',' ','o','o','0','o','o'} };


class CP		//--->CurrentPosition
{	public:
	int row;
	int col;
		CP(){		}
		CP(int r,int c)
		{
			row=r;
			col=c;
		}
};

queue<CP> q;
CP enemyPos;	

queue<char> tq;			// queue for storing   initial values stored enemy position before enemy generation

void enemyGen()
{		
	int numOfEnemy=n/2;
	int er,ec;				//--->enemy row & col.
	srand(time(0));			//--->diff rand num generation for each compiltion & set seed to curr time.
	while(numOfEnemy-- >0){
		er=rand()%n;
		ec=rand()%m;
		// if newEnemy at obstacle, oldEnemy or ActorInitialPostion recreate it. 
		while(a[er][ec]=='X' || a[er][ec]=='#' || a[er][ec]=='A'){
			er=rand()%n;
			ec=rand()%m;
		}
		q.push(CP(er,ec));
		//---> storing initial position of enemy before gen., storing either furit or otherwise(space).
		//---> order will be maintained so while checking must use pop() .
		//----> size of q and tq queue will be same.
		tq.push(a[er][ec]);	
		a[er][ec]='#';
	}
}

void delay(int number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not acheived 
    while (clock() < start_time + milli_seconds); 
} 

queue<CP> qtemp;
queue<char> temp;	// after while loop setting initial pos. values of enemy to queue
CP obj;
void enemyMovement(){
	while(!q.empty()){
		enemyPos=q.front();
		int r=enemyPos.row;
		int c=enemyPos.col;
		if(r%2==0 && c%2==0){		//---> horizantal movement.
			if(a[r][c+1]!='|' && a[r][c+1]!='X' && a[r][c+1]!='A' && a[r][c+1]!='#'){
				temp.push(a[r][c+1]);
				a[r][c+1]='#';
				obj.row=r;
				obj.col=c+1;
				qtemp.push(obj);
				a[r][c]=tq.front();
				tq.pop();
			}
			else{
				temp.push(a[r][c-1]);
				a[r][c-1]='#';
				obj.row=r;
				obj.col=c-1;
				qtemp.push(obj);
				a[r][c]=tq.front();
				tq.pop();
			}
		}
		
		else{			//---> vertical movement
			if(a[r-1][c]!='_' && a[r-1][c]!='X' && a[r-1][c]!='A' && a[r-1][c]!='#'){
				temp.push(a[r-1][c]);
				a[r-1][c]='#';
				obj.row=r-1;
				obj.col=c;
				qtemp.push(obj);
				a[r][c]=tq.front();
				tq.pop();
			}
			else{
				temp.push(a[r+1][c]);
				a[r+1][c]='#';
				obj.row=r+1;
				obj.col=c;
				qtemp.push(obj);
				a[r][c]=tq.front();
				tq.pop();
			}
		}
		q.pop();
	}
	while(!temp.empty()){
		tq.push(temp.front());
		temp.pop();
	}
	while(!qtemp.empty()){
		q.push(qtemp.front());
		qtemp.pop();
	}
}

void displayGrid()
{
	system("cls");
	cout<<"Score :"<<score<<endl;
	cout<<"__________________________"<<endl;
	for(int i=0;i<n;i++) {
		cout<<"|";
		for(int j=0;j<m;j++)
		{
			cout<<a[i][j];
		}
		cout<<"|"<<endl;
	}
	cout<<"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\""<<endl;
}

// initial position of actor.
CP actor(0,0);	
int returnValue;

int actorMovement()
{
	char press;
	int ar=actor.row;
	int ac=actor.col;
	
	if(kbhit()){			//---->for actor movement
		press=getch();
		if(press=='q')
		{
			cout<<"\nI QUIT"<<endl;
			returnValue=-1;
		}
		else if(press==' '){
			system("pause");
		}
		else if(press=='a' && ac-1>=0 && a[ar][ac-1]!='X' && a[ar][ac-1]!='#')	//--->move left
		{
			if(a[ar][ac-1]=='o')
				score+=10;
			else if(a[ar][ac-1]=='0')
				score+=100;
				
			returnValue=1;
			a[ar][ac-1]='A';
			a[ar][ac]=' ';
		}
		else if(press=='d' && ac+1<m && a[ar][ac+1]!='X'&& a[ar][ac+1]!='#')	//--->move right
		{	
			if(a[ar][ac+1]=='o')
				score+=10;
			else if(a[ar][ac+1]=='0')
				score+=100;
				
			returnValue=1;
			a[ar][ac+1]='A';
			a[ar][ac]=' ';
		}
		else if(press=='w' && ar-1>=0 && a[ar-1][ac]!='X' && a[ar-1][ac]!='#')	//--->move up
		{	
			if(a[ar-1][ac]=='o')
				score+=10;
			else if(a[ar-1][ac]=='0')
				score+=100;
				
			returnValue=1;
			a[ar-1][ac]='A';
			a[ar][ac]=' ';
		}
		else if(press=='s' && ar+1<n && a[ar+1][ac]!='X' && a[ar+1][ac]!='#')	//--->move DOWN
		{	
			if(a[ar+1][ac]=='o')
				score+=10;
			else if(a[ar+1][ac]=='0')
				score+=100;
				
			returnValue=1;
			a[ar+1][ac]='A';
			a[ar][ac]=' ';
		}
		else if(press!='a' || press!='s' || press!='d' || press!='w')
		{	returnValue=1;	}		// do nothing return game in progress.
		
		else{
			cout<<"\nGAME OVER"<<endl;
			returnValue=-1;
		}
	}
	else
	{
		returnValue=1;
	}
	return returnValue;
}

int main()
{	
	enemyGen();
	displayGrid();
	system("pause");
	int valueReturn;	//==1 gameinProgress_____==-1 gameover.
	
  while(1)
  {		
	valueReturn=actorMovement();
	if(valueReturn==-1)		// game over
	{
		cout<<"\nGAME OVER";
		break;
	}
	enemyMovement();		//--> delay will be used for enemy movement.
	displayGrid();
	delay(5);			//---> delay in seconds.
   }
   return 0;
}
