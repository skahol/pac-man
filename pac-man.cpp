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
	A    player
	o    small fruit
	0    large fruit
    enemy even horizantal mov
    odd then move vertical
************************************************/
static int score=0;
	char a[n][m]={
	{'A',' ',' ','X','X',' ','o','0','o',' ',' ',' ','o','o','o',' ','X','X','X',' ',' ','o','0','o'},
	{' ',' ',' ','X','X',' ',' ',' ',' ',' ',' ',' ','o','o','o',' ','X','X','X',' ',' ',' ',' ',' '},
	{' ',' ',' ','X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','o',' ','X','X',' ','o',' ','0',' ',' ','X','X',' ',' '},
	{'X','X',' ',' ',' ',' ',' ','X','X',' ','0',' ','X','X',' ',' ',' ',' ','o',' ','X','X',' ','o'},
	{'X','X',' ',' ',' ',' ',' ','X','X',' ','o',' ',' ',' ',' ','o','X','X',' ',' ',' ',' ',' ','o'},
	{'X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','X','0',' ',' ',' ',' ','o'},
	{' ',' ',' ',' ',' ',' ',' ','o','o',' ',' ',' ',' ',' ',' ','0','X','X',' ',' ',' ',' ',' ','0'},
	{'0',' ',' ',' ',' ',' ',' ','o','o',' ',' ',' ',' ',' ',' ',' ','X','X','o',' ',' ',' ',' ','o'},
	{'o',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','o',' ',' ',' ',' ',' ',' ',' ','o'},
	{'o',' ','X','X','X',' ',' ','X','X',' ','o','o','X','X',' ',' ','0',' ','o',' ',' ',' ',' ','o'},
	{'o',' ','X','X','X',' ',' ','X','X',' ','o','o','X','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	{'o',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	{'0','o',' ','o','o','0','o',' ',' ',' ',' ',' ',' ','o','0','o','o',' ',' ','o','o','0','o','o'} };


class CP		//--->CurrentPosition
{	public:
	int row;
	int col;
	bool isHorizantal;	// enemy movement
		CP(){		}
		CP(int r,int c,bool flag)
		{
			row=r;
			col=c;
			isHorizantal=flag;
		}
};
static int counter=0;

int numOfFruits(){
	int count=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++)
			if(a[i][j]=='o' || a[i][j]=='0')
				count++;
		
	}
	return count;
}

queue<CP> q;
CP enemyPos;	

queue<char> tq;			// queue for storing   initial values stored enemy position before enemy generation

void enemyGen()
{		
	int numOfEnemy=3;
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
		bool isHorizantal;	// even direction
		if(er%2==0 && ec%2==0){
			isHorizantal=true;
		}
		else
			isHorizantal=false;
			
		q.push(CP(er,ec,isHorizantal));
									//---> storing initial position of enemy before gen., storing either furit or otherwise(space).
		tq.push(a[er][ec]);			//---> order will be maintained so while checking must use pop() .
		a[er][ec]='#';				//----> size of q and tq queue will be same.	
	}
}

void delay(double number_of_seconds) 
{ 
    double milli_seconds = 1000 * number_of_seconds; 
    clock_t start_time = clock(); 
    while (clock() < start_time + milli_seconds); 
} 

queue<CP> qtemp;
queue<char> temp;	// after while loop setting initial pos. values of enemy to queue
static bool flag=false;	//--->for back-forth of enemy till obstacle.

void enemyMovement(){
	while(!q.empty()){
		enemyPos=q.front();
		int r=enemyPos.row;
		int c=enemyPos.col;
		bool isEven=enemyPos.isHorizantal;
		if(isEven){		//---> horizantal movement.	
			if(flag==false && c+1<m && a[r][c+1]!='|' && a[r][c+1]!='X' && a[r][c+1]!='A' && a[r][c+1]!='#'){
				temp.push(a[r][c+1]);
				a[r][c+1]='#';
			    CP obj(r,c+1,true);
				qtemp.push(obj);
				a[r][c]=tq.front();
				tq.pop();
				if(c+2==m || a[r][c+2]=='X'|| a[r][c+2]=='#')
					flag=true;
			}
			else {
				temp.push(a[r][c-1]);
				a[r][c-1]='#';
				CP obj(r,c-1,true);
				qtemp.push(obj);
				a[r][c]=tq.front();
				tq.pop();
				if(c-2<0 || a[r][c-2]=='X' || a[r][c-2]=='#')
					flag=false;
			}
		}
		
		else{			//---> vertical movement
			if(flag==false && r-1>=0 && a[r-1][c]!='=' && a[r-1][c]!='X' && a[r-1][c]!='A' && a[r-1][c]!='#'){
				temp.push(a[r-1][c]);
				a[r-1][c]='#';
				CP obj(r-1,c,false);
				qtemp.push(obj);
				a[r][c]=tq.front();
				tq.pop();
				if(r-2<0 || a[r-2][c]=='X' || a[r-2][c]=='#'){
					flag=true;
				}
			}
			
			else {
				temp.push(a[r+1][c]);
				a[r+1][c]='#';
				CP obj(r+1,c,false);
				qtemp.push(obj);
				a[r][c]=tq.front();
				tq.pop();
				if(r+2==n || a[r+2][c]=='X' || a[r+2][c]=='#'){
					flag=false;
				}
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
	cout<<"\t\t=========================="<<endl;
	for(int i=0;i<n;i++) {
		cout<<"\t\t|";
		for(int j=0;j<m;j++)
		{
			cout<<a[i][j];
		}
		cout<<"|"<<endl;
	}
	cout<<"\t\t=========================="<<endl;
}

// initial position of actor.	
static int ar=0;	// row coords of actor
static int ac=0;	// cols coords of actor
int returnValue;

int actorMovement()
{
	char press;
	if(kbhit()){			//---->for actor movement
		press=getch();
		if(press=='q')
		{
			cout<<"\nI QUIT"<<endl;
			returnValue=-1;
		}
		else if(press=='a' && ac-1>=0 && a[ar][ac-1]!='X')	//--->move left
		{
			if(a[ar][ac-1]=='#')
				return -1;
			if(a[ar][ac-1]=='o'){
				score+=10;
				counter++; 
			}
			else if(a[ar][ac-1]=='0'){
				score+=100;	
				counter++;
			}
			a[ar][ac-1]='A';
			a[ar][ac]=' ';
			ac--;
			returnValue=1;
		}
		else if(press=='d' && ac+1<m && a[ar][ac+1]!='X')	//--->move right
		{	
			if(a[ar][ac+1]=='#')
				return -1;
				
			if(a[ar][ac+1]=='o'){
				score+=10;
				counter++;
			}
			else if(a[ar][ac+1]=='0'){
				score+=100;
				counter++;
			}
			a[ar][ac+1]='A';
			a[ar][ac]=' ';
			ac++;
			returnValue=1;
		}
		else if(press=='w' && ar-1>=0 && a[ar-1][ac]!='X')	//--->move up
		{	
			if( a[ar-1][ac]=='#')
				return -1;
			if(a[ar-1][ac]=='o'){
				score+=10;
				counter++;
			}
			else if(a[ar-1][ac]=='0'){
				score+=100;
				counter++;
			}
			a[ar-1][ac]='A';
			a[ar][ac]=' ';
			ar--;
			returnValue=1;
		}
		else if(press=='s' && ar+1<n && a[ar+1][ac]!='X')	//--->move DOWN
		{	
			if(a[ar+1][ac]=='#')
				return -1;
			if(a[ar+1][ac]=='o'){
				score+=10;
				counter++;
			}
			else if(a[ar+1][ac]=='0'){
				score+=100;
				counter++;
			}
			a[ar+1][ac]='A';
			a[ar][ac]=' ';
			ar++;
			returnValue=1;
		}
		else if(press!='a' || press!='s' || press!='d' || press!='w')
		{	returnValue=1;	}	
		
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
	cout<<"\t\t\tBOARD SETUP...\n";
	system("pause");
	int valueReturn;	
	int count=numOfFruits();
	
  while(1)
  {		
  	if(count==counter){
  		cout<<"\n\tWINNER WINNER CHICKEN DINNER!!!\n";
  		cout<<"\t\tTotal Score :"<<score<<endl;
  		break;
	}
	valueReturn=actorMovement();
	if(valueReturn==-1)		// game over
	{
		cout<<"\nGAME OVER";
		break;
	}
	enemyMovement();		//--> delay will be used for enemy movement.
	displayGrid();
	
	delay(1);			//---> delay in seconds.
   }
   return 0;
}
