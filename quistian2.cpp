/**************************************************************************
*                                                                         *
*     Program Filename:  quistian2.cpp                                    *
*     Author          :  Alfonso Quistian                                 *
*     Date Written    :  February 15, 2016                                *
*     Purpose         :  To play a version of Tic-Tac-Toe 		   		  *
*     Input from      :  Keyboard                                         *
*     Output to       :  Screen                                           *
*                                                                         *
**************************************************************************/
#include <iostream.h>
#include <conio.h>
#include <time.h>

typedef  char  TicTacToeBoard[5][5];

void initializeBoard(TicTacToeBoard);
void printBoard(TicTacToeBoard);
void playerTakesTurn(TicTacToeBoard);
void computerTakesTurn(TicTacToeBoard);
bool gameIsNotOver(TicTacToeBoard);
void announceResult(TicTacToeBoard);

int main()
{
   TicTacToeBoard  B;
   initializeBoard(B);
   printBoard(B);
   playerTakesTurn(B);

   while (gameIsNotOver(B))
   {
      printBoard(B);
      computerTakesTurn(B);
      printBoard(B);

      if (gameIsNotOver(B))
	  { playerTakesTurn(B);
	  }
      else
		break;
      // end if
   }
   // end while
   printBoard(B);
   announceResult(B);
   return 0;
}
// end function main

/**************************************************************************
*                                                                         *
*     Function Name   :  InitializeBoard                                  *
*     Purpose         :  Creates the board                                *
*	  Called by		  :  Main											  *
*     Calls		      :  None                                             *
*                                                                         *
**************************************************************************/

void initializeBoard(TicTacToeBoard board)
{
	board[0][0] = '+';		//0,0 will be the board status: + means still playable
	board[0][1]=board[1][0] = '1';
	board[0][2]=board[2][0] = '2';
	board[0][3]=board[3][0] = '3';
	board[0][4]=board[4][0] = '4';	//gives a guide for board
	
		for( int i = 1 ; i < 5 ; i++)//fills the rest with *
		{
			for( int j = 1 ; j < 5; j++)
				{board[i][j] = '*';
			}//end inner for
		}//end outer for
}
//end initializeBoard
/**************************************************************************
*                                                                         *
*     Function Name   :  PrintBoard  	                                  *
*     Purpose         :  To print the board                               *
*	  Called by		  :  Main											  *
*     Calls		      :  None                                             *
*                                                                         *
**************************************************************************/
void printBoard(TicTacToeBoard board)
{
	system("cls");
	cout<<endl<<"  ";
		for( int i = 0 ; i < 5 ; i++)
		{
			for( int j = 0 ; j < 5 ; j++)
			{
				if((i==0 && j==0))
				{
					j=j+1;				//skips the 0,0 position
					cout<<"   ";
				}//end if
				
				cout << board[i][j]<<" ";  //print the spot and a space after
				
				if(i==0 && j ==4)
				{
					cout<<" Y" <<endl; //prints the Y axis name
				}//end if
				if (j==0 && i!=0)
				{
					cout<< " ";
				}//end if
				if(j%5==4)	//makes sure to only print the needed number per row
				{
					cout<<endl;	
					cout<<"  ";
				}//end if
				
			}//end inner for
		}//end outer for
		cout<<"X"<<endl<<endl;		//prints the X axis name
}
//end printBoard
/**************************************************************************
*                                                                         *
*     Function Name   :  PlayerTakesTurn                                  *
*     Purpose         :  To allow the player's turn                       *
*	  Called by		  :  Main											  *
*     Calls		      :  isInBounds, spotIsEmpty, isWinningLine           *
*                                                                         *
**************************************************************************/
void playerTakesTurn(TicTacToeBoard board)
{
	bool isInBounds(int, int, int); // checks if 1st int is in-between 2nd an 3rd int (inclusively)
	bool spotIsEmpty(int, int, TicTacToeBoard); //checks if a spot is empty
	int isWinningLine(int, int, TicTacToeBoard); //checks the last move for a win
	
	int moveX, moveY;
	cout<< "Enter a move to play: (integers only!) ~ row then column"<<endl;
	cin>>moveX>> moveY;
	
	while(!(isInBounds(moveX,1,4)) || !(isInBounds(moveY,1,4)))
	{	//checks if the move is within the bounds
		if(!isInBounds(moveX,1,4))
			{
			cout<<"your X is out of the range (1-4). Please enter a valid move"<<endl;
			}//end if
		if(!isInBounds(moveY,1,4))
			{
			cout<<"your Y is out of the range (1-4). Please enter a valid move"<<endl;
			}//end if
	cout<< "Enter a move to play: (example: 'x y')"<<endl;
	cin>>moveX>> moveY;
	}//end while
	
	if(spotIsEmpty(moveX, moveY, board))	//then check the availability of the spot
		{	board[moveX][moveY] = 'P';
		}//end if
	else 
		{ 	board[moveX][moveY] = 'x'; //shows the taken spot
			board[0][0] = '-'; //a shortcut to end the game.
		}//end else
	
	//see if the move has caused a win
	int result = isWinningLine(moveX, moveY, board);
	if(result == 1)
		{	board[0][0] = '1';
		}//end if
	else if(result == 2)
		{	board[0][0] = '0';
		}//end else if
}
//end playerTakesTurn
/**************************************************************************
*                                                                         *
*     Function Name   :  computerTakesTurn                                *
*     Purpose         :  computer takes its turn, it also finds 		  *
*					  :  a winning move or does a random one or it        *
*					  :  blocks a winning player move, though it may 	  *
*					  :  inadvertently lose doing any of these moves.	  *
*	  Called by		  :  Main											  *
^											  							  *
*     Calls		      :  isWinningLine , random, spotIsEmpty , wait		  *
*                     :  checkOffDiagonal, checkColumn, checkMainDiagonal *
*					  :  checkRow, checkWinStatus, makeComputerTurn		  *
**************************************************************************/
void computerTakesTurn(TicTacToeBoard board)
{
	int isWinningLine(int, int, TicTacToeBoard);
	double random(long&);
	bool spotIsEmpty(int, int,TicTacToeBoard);
	void wait(int,int,string);
	void checkOffDiagonal(int&, int&, TicTacToeBoard);
	void checkMainDiagonal(int&, int&, TicTacToeBoard);
	void checkColumn(int&, int&,int, TicTacToeBoard);
	void checkRow(int&, int&, int, TicTacToeBoard);
	int checkWinStatus(int, int);
	void makeComputerTurn(int, int, int&, int&);//sets cMoveX & Y to the move and sets the place on the board
	
	cout<< "Computer is taking its turn"<<endl;
	int cMoveX, cMoveY; //computerMove X & Y
	long seed = time(0);
	
	int test1 = isWinningLine(4,1,board); //tests the entire board to see if either player is close
	int test2 = isWinningLine(1,2,board);
	int test3 = isWinningLine(3,3,board);
	int test4 = isWinningLine(2,4,board);//end the tests
	
	int pCounter, cCounter; //counts the p's and c's
	pCounter = cCounter = 0;
	int tester1, tester2; //place to save tester integers

	
	if(test1==20|| test1 == 10) //if col 1, row 4, or the off diagonal is close for a win, then find the empty spot
	{
		checkOffDiagonal(pCounter, cCounter, board);
		tester1 = checkWinStatus(pCounter,cCounter);
		pCounter=cCounter=0;
		checkColumn(pCounter, cCounter, 1, board);
		tester2 = checkWinStatus(pCounter,cCounter);
		
		if (tester1 == 20 || tester1 == 10)
		{	//find the empty spot in the off diagonal
			for(int i=1 ;i< 5 ; i++)
			{	
			if(spotIsEmpty(i,5-i,board))
				{	makeComputerTurn(i,5-i,cMoveX,cMoveY);
				}//end if
			}//end for
		}//end if 
		else if (tester2 == 20|| tester2 == 10)
		{	//find the empty spot in column 1
			for(int i = 1 ;i< 5 ; i++)
			{	if(spotIsEmpty(i,1,board))
					{	makeComputerTurn(i,1,cMoveX,cMoveY);
					}//end if
			}//end for
		}//end if 
	else {	//find the empty spot in row 4
			for(int i = 1 ;i< 5 ; i++)
			{	if(spotIsEmpty(4,i,board))
					{	makeComputerTurn(4,i,cMoveX,cMoveY);
					}//end if
			}//end for
		}//end else 
	}//end if(test1==20..)
		
	else if (test2 == 20|| test2 == 10) //if row 1 or col 2 is close to a win, then find the empty spot
	{
		checkRow(pCounter, cCounter,1, board);
		tester1 = checkWinStatus(pCounter,cCounter);
		
		if(tester1==20|| tester1 == 10)
		{	//find the empty spot in row 1
			for(int i = 1 ;i< 5 ; i++)
			{	if(spotIsEmpty(1,i,board))
					{	makeComputerTurn(1,i,cMoveX,cMoveY);
					}//end if
			}//end for
		}//end if 
		else 
		{
			//find the empty spot in column 2
			for(int i = 1 ;i< 5 ; i++)
			{	if(spotIsEmpty(i,2,board))
					{	makeComputerTurn(i,2,cMoveX,cMoveY);
					}//end if
			}//end for
		}//end else
	}//end else if (test2 == 20...)
		
	else if ( test3 ==20|| test3 == 10)//if row 3, column 3, or mainDiagonal has a close win, then find the empty spot
	{
		checkMainDiagonal(pCounter, cCounter, board);
		tester1= checkWinStatus(pCounter,cCounter);
		pCounter = cCounter = 0;
		checkRow(pCounter, cCounter, 3, board);
		tester2 = checkWinStatus(pCounter,cCounter);
		
		if(tester1 == 20 || tester1 == 10)
		{	//find the empty spot in the main diagonal
			for(int i = 1 ;i< 5 ; i++)
			{	if(spotIsEmpty(i,i,board))
					{	makeComputerTurn(i,i,cMoveX,cMoveY);
					}//end if
			}//end for
		}//end if
		else if (tester2 == 20|| tester2 == 10)
		{	//find the empty spot in row 3
			for(int i = 1 ;i< 5 ; i++)
			{	if(spotIsEmpty(3,i,board))
					{	makeComputerTurn(3,i,cMoveX,cMoveY);
					}//end if
			}//end for
		}//end else if
		else 
		{	//find the empty spot in column 3
			for(int i = 1 ;i< 5 ; i++)
			{	if(spotIsEmpty(i,3,board))
					{	makeComputerTurn(i,3,cMoveX,cMoveY);
					}//end if
			}//end for
		}
	}//end else if (test3...)
		
	else if (test4 == 20|| test4 == 10)
	{//if row 2 or col 4 is close, then find the empty spot
		checkRow(pCounter, cCounter, 2, board);
		tester1= checkWinStatus(pCounter,cCounter);
		if(tester1 == 20|| tester1 == 10)
		{	//find the empty spot in row 2
			for(int i = 1 ;i< 5 ; i++)
			{	if(spotIsEmpty(2,i,board))
					{	makeComputerTurn(2,i,cMoveX,cMoveY);
					}//end if
			}//end for
		}//end if
		else
		{	//find the empty spot in column 4
			for(int i = 1 ;i< 5 ; i++)
			{	if(spotIsEmpty(i,4,board))
					{	makeComputerTurn(i,4,cMoveX,cMoveY);
					}//end if
			}//end for
		}//end else
	}//end else if (test4==20...)
		
	else 
	{ //Do a random move
		cMoveX = 4 * random(seed)+1;
		cMoveY = 4 * random(seed)+1;
		while(!spotIsEmpty(cMoveX,cMoveY,board)) //find an empty spot, if move is taken
			{
			cMoveX = 4 * random(seed)+1;
			cMoveY = 4 * random(seed)+1;
			}//end while
	}//end else
		
		wait(1,2,"."); //gives the program a little pause( 2 one second pauses, printing '.' )
		board[cMoveX][cMoveY] = 'C';	//places the computer's move
	
		//see if the move has caused a win
		int result = isWinningLine(cMoveX,cMoveY,board);
		if(result == 1)
			{board[0][0] = '1';
			}//end if
		else if(result == 2)
			{board[0][0] = '0';
			}//end else if
}
//end computerTakesTurn
/**************************************************************************
*                                                                         *
*     Function Name   :  gameIsNotOver	                                  *
*     Purpose         :  To check the state of the board                  *
*	  Called by		  :  Main											  *
*     Calls		      :  spotIsEmpty                                            *
*                                                                         *
**************************************************************************/
bool gameIsNotOver(TicTacToeBoard board)
{
	bool spotIsEmpty(int, int, TicTacToeBoard);
	bool result;
	int emptySpots = 0;
	
	for(int i = 1; i <5; i++) //check if all the spots are taken
	{
		for(int j = 1; j < 5 ; j++)
		{	if(spotIsEmpty(i,j,board)) //count the empty spots
				{	emptySpots++;
				}
		}
	}//end outer for
	if (emptySpots == 0 && (board[0][0] == '+'))
		{	board[0][0]='T'; //shortcut a tie if no winner and no more spots
		}
		
	if(board[0][0] == '+') //if its not +, then continue
		result = true;
	else result = false;
	
	return result;
}
//end gameIsNotOver
/**************************************************************************
*                                                                         *
*     Function Name   :  announceResult	                                  *
*     Purpose         :  To print the result                              *
*	  Called by		  :  Main											  *
*     Calls		      :  None                                             *
*                                                                         *
**************************************************************************/
void announceResult(TicTacToeBoard board)
{
	string result;
	cout<<"GAME OVER"<<endl;
	cout<<"RESULT: "<<endl;
	if(board[0][0] == '-')
	{
		result = "Player has chosen already taken spot. Ending game in a draw";
	}
	else if (board[0][0] == '1')
	{
		result = "Player has triumphantly beaten the computer!";
	}
	else if (board[0][0] == '0')
	{
		result = "Computer has bested another opponent.";
	}
	else if (board[0][0] == 'T')
	{
		result = "Players have stalled to a Stalemate";
	}
	else result = "board error: " && board[0][0] &&" ";
	cout<<result<<endl;
}
//end announceResult

/**customMethods
/***************************************************************************
*                                                                         *
*     Function Name   :  isInBounds		                                  *
*     Purpose         :  checks if an integer is within the bounds(inclusively) *
*	  Called by		  :  playerTakesTurn								  *
*     Calls		      :  None    	                                      *
*                                                                         *
**************************************************************************/

bool isInBounds(int x, int min, int max)
{
	bool inBounds;
	if (x>max || x<min)
		inBounds = false;
	else inBounds = true;

return inBounds;	
}
//end isInBounds
/**************************************************************************
*                                                                         *
*     Function Name   :  spotIsEmpty	                                  *
*     Purpose         :  checks if the spot is empty					  *
*	  Called by		  :  playerTakesTurn, computerTakesTurn				  *
*     Calls		      :  None    	                                      *
*                                                                         *
**************************************************************************/
bool spotIsEmpty(int x, int y, TicTacToeBoard board)
{
	bool isEmpty;
	if(board[x][y] == '*')
	{
		isEmpty= true;
	}
	else isEmpty = false;
	return isEmpty;
}
//end spotIsEmpty
/**************************************************************************
*                                                                         *
*     Function Name   :  isWinningLine	                                  *
*     Purpose         :  checks if there is a winning line				  *
*	  Called by		  :  playerTakesTurn & computerTakesTurn			  *
*     Calls		      :  checkWinStatus, checkOffDiagonal, checkMainDiagonal
*					  :  checkRow, checkColumn							  *
*                                                                         *
**************************************************************************/
int isWinningLine(int X, int Y, TicTacToeBoard board)
{
	int checkWinStatus(int, int);
	void checkOffDiagonal(int&, int&, TicTacToeBoard);
	void checkMainDiagonal(int&, int&, TicTacToeBoard);
	void checkRow(int&, int&, int, TicTacToeBoard);
	void checkColumn(int&, int&, int, TicTacToeBoard);

	int pCounter=0, cCounter=0;//count the number of p's and c's in a line
	int result;
	//check Diagonals if move is on the diagonal
	if((X ==Y)) 
	{//check main diagonal,
		checkMainDiagonal(pCounter,cCounter, board);
	}	
	else if( (X==1 && Y== 4)|| (X==2 && Y==3)|| (X== 3 && Y == 2) ||(X==4 && Y==1))
	{//if its an off diagonal
		checkOffDiagonal(pCounter,cCounter, board);
	}//end else if
	result = checkWinStatus(pCounter, cCounter); //test the diagonal results, if any
	
	if (result == 0 ) //if neither player has won yet.
	{
		pCounter=0;//Check the row status, and reset pCounter and cCounter
		cCounter=0;
		checkRow(pCounter,cCounter, X, board);
		result = checkWinStatus(pCounter, cCounter); //check the row results
	}
	
	//if there is still no winner, check the column
	if(result== 0)
	{
		//count the column moves and reset pCounter and cCounter
		pCounter=0;
		cCounter=0;
		checkColumn(pCounter, cCounter, Y, board);
		result = checkWinStatus(pCounter, cCounter);//check the column result 
	}	
	return result;	
}
//end isWinningLine
/**************************************************************************
*                                                                         *
*     Function Name   :  checkWinStatus                                   *
*     Purpose         :  returns a line status							  *
*	  Called by		  :	 isWinningLine									  *
*     Calls		      :  None    	                                      *
*                                                                         *
**************************************************************************/
int checkWinStatus(int p, int c)
{
	int winStatus; //0 is neutral, 1 is player win, 2 is Computer win
					   //10 is a near player win, 20 is a near computer win
					   
	if(c==1 && p == 3)	//if there is 3 p's and 1 c
		winStatus =1;
	else if (p==2 && c ==1 )
		winStatus=10; // if there are 2 p's and 1 c
	else if(p==1 && c == 3)
		winStatus = 2;// if there are 3 c's and 1 p
	else if( c==2 && p== 1)
		winStatus=20; //if there are 2 c's and 1 p	
	else 
		winStatus = 0;// if neither player has won
	
	return winStatus;	
}
//end checkWinStatus
/**************************************************************************
*                                                                         *
*     Function Name   :  random  		                                  *
*     Purpose         :  returns a random number						  *
*	  Called by		  :	 computerTakesTurn								  *
*     Calls		      :  None    	                                      *
*                                                                         *
**************************************************************************/
double random(long &x)
{
   x = x*843314861L + 453816693L;
   if (x < 0)
   {
      x += 2147483647L;
      x ++;
   }// end if
   return x*0.4656612E-9;
}
// end random
/**************************************************************************
*                                                                         *
*     Function Name   :  wait	  		                                  *
*     Purpose         :  Waits for a time								  *
*	  Called by		  :	 coomputerTakesTurn								  *
*     Calls		      :  None    	                                      *
*                                                                         *
**************************************************************************/
void wait(int waitTime, int repeats,string in)
{	for(int i = 0 ; i<repeats; i++)
	{	cout<<in;
		double timer = time(0);
		while(time(0)-timer <= waitTime)
		{		
		}//do Nothing
	}//end for
}
//end wait
/**************************************************************************
*                                                                         *
*     Function Name   :  checkMainDiagonal	                              *
*     Purpose         :  check the main Diagonal, counts the p's and c's  *
*	  Called by		  :	 isWinningLine									  *
*     Calls		      :  None    	                                      *
*                                                                         *
**************************************************************************/
void checkMainDiagonal(int& pCounter, int& cCounter, TicTacToeBoard board)
{	for (int i =1 ; i < 5 ; i++) 
		{
			if(board[i][i] == 'P')
				pCounter++;
			else if(board[i][i] == 'C' )
				cCounter++;
		}//end for
}
//end checkMainDiagonal
/**************************************************************************
*                                                                         *
*     Function Name   :  checkoffDiagonal	                              *
*     Purpose         :  check the off Diagonal, counts the p's and c's   *
*	  Called by		  :	 isWinningLine									  *
*     Calls		      :  None    	                                      *
*                                                                         *
**************************************************************************/
void checkOffDiagonal(int& pCounter, int& cCounter, TicTacToeBoard board)
{	for (int i =1; i<5 ; i++)
		{
			if(board[i][5-i]=='P')
				pCounter++;
			else if(board[i][5-i]=='C')
				cCounter++;
		}//end for
}
//end checkOffDiagonal
/**************************************************************************
*                                                                         *
*     Function Name   :  checkRow			                              *
*     Purpose         :  check the row, counts the p's and c's  		  *
*	  Called by		  :	 isWinningLine									  *
*     Calls		      :  None    	                                      *
*                                                                         *
**************************************************************************/
void checkRow(int& pCounter, int& cCounter, int moveX, TicTacToeBoard board)
{	for(int i = 1; i<5 ; i++)
		{
			if(board[moveX][i]=='P')
				pCounter++;
			else if(board[moveX][i]=='C')
				cCounter++;
		}//end for
}
//end checkRow
/**************************************************************************
*                                                                         *
*     Function Name   :  checkColumn		                              *
*     Purpose         :  check the column, counts the p's and c's  		  *
*	  Called by		  :	 isWinningLine									  *
*     Calls		      :  None    	                                      *
*                                                                         *
**************************************************************************/
void checkColumn(int& pCounter, int& cCounter, int moveY, TicTacToeBoard board)
{	for(int i = 1; i<5 ; i++)
		{
			if(board[i][moveY]=='P')
				pCounter++;
			else if(board[i][moveY]=='C')
				cCounter++;
		}//end for
}
//end checkColumn
/*******************************************************************************
*                                                                       	   *
*     Function Name   :  makeComputerTurn	                           		   *
*     Purpose         :  combine some repetitive code and set the computer turn*
*	  Called by		  :	 computerMove									 	   *
*     Calls		      :  None    	                                   		   *
*                                                                  			   *
**************************************************************************/
void makeComputerTurn(int cMoveX, int cMoveY,int& inputX, int& inputY)
{		inputX = cMoveX;
		inputY = cMoveY;
}
//end makeComputerTurn

/**END PROGRAM**/