#include <iostream>
#include <iomanip>
#include <windows.h>
#include<fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

void handleSpecialCard(int specialCardType, int& turn, int deck[8][15], int player1[50], int player2[50], int& topCard);
void dealCards(int deck[][15], int player1[50], int player2[50]);

void initialize(int deck[][15]);

void printPlayerhand(int player[50]);

void printBoard(int player1[50], int player2[50], int topCard, int turn, int choice , int discardPile[120]);

bool isValidPlay(int playerCard, int topCard);

void playTurn(int player[50], int &topCard, int choice, int discardPile[120]);

void pickcard(int deck[8][15], int player[50]);

void updateDiscardPile(int discardPile[120], int deck[8][15]);

void callUNO(int& playerSize, bool& isUNOCalled, int turn,int& p1,int& p2);

void shuffle(int deck[8][15]);

void mainMenu();

void saveLoadGameResult(bool load, int &Wins_p1, int &Wins_p2, int winner);

bool isHandEmpty(int player[50]);

const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int RED = 4;
const int YELLOW = 6;
const int WHITE = 7;

void setColor(int textColor, int bgColor) 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}
void clearScreen() 
{
	system("CLS");
}
int main() 
{
	int winner=0;
	int Wins_p1 =0 , Wins_p2=0;
	bool load = true;
	saveLoadGameResult(load, Wins_p1, Wins_p2, winner);
	load=false;
	int turn = 1, playerSize=0, counter=0;
	int playerCard ;
	int topCard = -1; // Only one top card is needed
	int discardPile[120] = {-1};
	int deck[8][15], player1[50], player2[50];
	int choice, specialCardType,playerchoice,bari;
	bool isUNOCalled = false,firstTurn=true;
	int p1=0,p2=0;

	cout<<"=== Welcome To Uno! ==="<<endl;
	cout<<"1.Play Game."<<endl;
	cout<<"2.Game History."<<endl;
	cout<<"3.Exit"<<endl;
	cout<<"Enter your choice:";
	cin>>bari;
	if(bari==1)
	{
	initialize(deck);
	shuffle(deck);
	dealCards(deck, player1, player2);
	printPlayerhand(player1);
	do 
	{
		cout<<"Choose:"<< endl;
		cout<<"1. Play a card "<<endl;
		cout<<"2. Draw a card "<< endl;
		cout<<"Enter Your Choice: " ;
		cin>>playerchoice;
		if(playerchoice==1)
		{
		    cout << endl;
		    if (turn % 2 != 0) 
			{
		        cout << "Player 1, enter your choice (0-7): ";
		        cin >> choice;

		        if (choice < 0 || choice >= 50 || player1[choice] == -1) 
				{
		            cout << "Invalid input! Try again." << endl;
		            continue;
		        }
				playerCard=player1[choice];
		        if (firstTurn||isValidPlay(playerCard, topCard)) 
				{
					topCard=playerCard;
		            printBoard(player1, player2, topCard, turn, choice , discardPile);
		            specialCardType = topCard % 100;
		            handleSpecialCard(specialCardType, turn, deck, player1, player2, topCard);
		            firstTurn=false;
		        } 
				else 
				{
		            cout<<"Invalid Card! Try a different move."<<endl;
		            turn++;
		        }
		    }
			else 
			{
		        cout << "Player 2, enter your choice (0-7): ";
		        cin >> choice;
		        if (choice < 0 || choice >= 50 || playerCard == -1) 
				{
		            cout << "Invalid input! Try again." << endl;
		            continue;
		        }
					playerCard=player2[choice];
		            if (isValidPlay(playerCard, topCard)) 
					{
						topCard=playerCard;
		                printBoard(player1, player2, topCard, turn,choice, discardPile);
		                specialCardType = topCard % 100;
		                handleSpecialCard(specialCardType, turn, deck, player1, player2, topCard);  
					}
					else{                                                    
		               cout << "Invalid Card! Try a different move." << endl;
		                turn++;
		            }
		        }
	    	}
	    	else if(playerchoice==2)
	    	{
	    		cout<<"Drawing Card....."<< endl;
	    		if(turn%2==0)
	    		{
	    			pickcard(deck,player2);	
				}
				else
				{
					pickcard(deck,player1);
				}
			}
	for (int i = 0; i < 50; i++) 
    {
	    if (turn % 2 == 0) {
	        if (player1[i] != -1)
             {
	            playerSize++;
	        }
	    } else {
	        if (player2[i] != -1) 
            {
	            playerSize++;
	        }
	    }
	}
	callUNO(playerSize, isUNOCalled, turn,p1,p2);
	        turn++;
	        for(int i = 0 ; i<8 ; i++)
	        {
	        	for(int j = 0 ; j<15 ; j++)
	        	{
	        		if(deck[i][j] == -1)
	        		{
	        			counter++;
					}
				}
			}
			if(counter==120)
			{
				cout<<"Deck Is Empty, Update Discard Pile: "<< endl;
			}
			if(turn%2!=0)
            {
		if(isHandEmpty(player1))
		{
			if(p1==1)
			{
			winner=1;
			cout<<"PLayer 1 Wins";
}
			else
			{
				pickcard(deck,player1);
				pickcard(deck,player1);
			}
		}
    }
		else
		{
			if(isHandEmpty(player2))
		{
			if(p2==1)
			{
				winner =2;
			cout<<"PLayer 2 Wins";
			break;
			}
			else
			{
				pickcard(deck,player2);
				pickcard(deck,player2);
			}
		}
	}
	turn++;
}while(true);
}
if(bari==2)
{
   saveLoadGameResult(load, Wins_p1, Wins_p2, winner);	
}
if(bari==3)
{
	cout<<"Exiting the Game";
}
}
void initialize(int deck[8][15]) 
{
	float line = 1;
	for (int i = 0; i < 8; i++) 
	{
	    for (int j = 0; j < 15; j++) 
		{
	        if (i % 2 == 0) 
			{
	            deck[i][j] = int(line) * 100 + j;
	        } 
			else 
			{
	        	if (j == 0 || j == 14 || j == 13) 
				{
	                    deck[i][j] = -1;
	            } 
				else 
				{
	                    deck[i][j] = int(line) * 100 + j;
	            }
	        }
	    }
	    line += 0.50;
	}
}
void dealCards(int deck[][15], int player1[50], int player2[50]) 
{
	srand(time(0));
	for (int i = 0; i < 50; i++) player1[i] = player2[i] = -1;
	for (int i = 0; i < 7; i++) 
	{
	    int x = rand() % 8, y = rand() % 15;
	    int a = rand() % 8, b = rand() % 15;
	    while (deck[x][y] == -1 || deck[a][b] == -1) 
		{
	        x = rand() % 8;
	        y = rand() % 15;
	        a = rand() % 8;
	        b = rand() % 15;
	    }
	    player1[i] = deck[x][y];
	    player2[i] = deck[a][b];
	    deck[x][y] = -1;
	    deck[a][b] = -1;
	}
}
bool isValidPlay(int playerCard, int topCard) 
{
	int playerColor = playerCard / 100;
	int playerType = playerCard % 100;
	int topColor = topCard / 100;
	int topType = topCard % 100;
	return(playerColor == topColor || playerType == topType || playerType >= 13);
}
void playTurn(int player[50], int& topCard, int choice, int discardPile[120]) 
{
	static int card = 0;

	if (choice < 0 || choice >= 50) 
	{
	    cout << "Invalid choice index!" << endl;
	    return;
	}
	topCard = player[choice];
	discardPile[card] = player[choice];
	player[choice] = -1;
	int color = topCard / 100;
	char type = topCard % 100;
	    
	if (card >= 120) 
	{
		cout << "Discard pile is full!" << endl;
	    return;
	}	
	if (type == 1) 
	{ 
		type='1'; 
	} 
	else if (type == 2) 
	{ 
		type='2'; 
	} 
	else if (type == 3) 
	{ 
		type='2'; 
	} 
	else if (type == 4) 
	{ 
		type='4'; 
	}
	if (type == 5) 
	{ 
		type='5'; 
	} 
	else if (type == 6) 
	{ 
		type='6'; 
	} 
	else if (type == 7) 
	{
		type='7'; 
	} 
	else if (type == 8) 
	{ 
		type='8'; 
	}
	else if (type == 9) 
	{ 
		type='9'; 
	} 
	else if (type == 10) 
	{ 
		type='S'; 
	} 
	else if (type == 11) 
	{ 
		type='R'; 
	} 
	else if (type == 13 || type == 14) 
	{ 
		type='W'; 
	}
	else if (type == 12) 
	{ 
		type='D'; 
	} 
	switch (color) 
	{
	        case 1:
	            setColor(BLACK, RED);
	            cout << " ------- " << endl
	                 << " -     - " << endl
	                 << " -  " << type << "  - " << endl
	                 << " -     - " << endl
	                 << " ------- " << endl;
	            break;
	        case 2:
	            setColor(BLACK, BLUE);
	            cout << " ------- " << endl
	                 << " -     - " << endl
	                 << " -  " << type << "  - " << endl
	                 << " -     - " << endl
	                 << " ------- " << endl;
	            break;
	        case 3:
	            setColor(BLACK, YELLOW);
	            cout << " ------- " << endl
	                 << " -     - " << endl
	                 << " -  " << type << "  - " << endl
	                 << " -     - " << endl
	                 << " ------- " << endl;
	            break;
	        case 4:
	            setColor(BLACK, GREEN);
	            cout << " ------- " << endl
	                 << " -     - " << endl
	                 << " -  " << type << "  - " << endl
	                 << " -     - " << endl
	                 << " ------- " << endl;
	        	break;
		}
		setColor(WHITE, BLACK);
		cout << endl;
		card++;
}
void handleSpecialCard(int specialCardType, int& turn, int deck[8][15], int player1[50], int player2[50], int& topCard) 
{
	if (specialCardType == 10 || specialCardType == 11) 
	{
	    cout << "Special Card Played - Skip/Reverse!" << endl;
	    turn++;
	} 
	else if (specialCardType == 12) 
	{
	    cout << "Draw 2 Played!" << endl;
	    if (turn % 2 == 0) 
		{
	        pickcard(deck, player1);
	        pickcard(deck, player1);
	    } 
		else 
		{
	        pickcard(deck, player2);
	        pickcard(deck, player2);
	    }
	} 
	else if (specialCardType == 13 || specialCardType == 14) 
	{
	    int color;
	    cout << "Choose a Color (1-Red, 2-Blue, 3-Yellow, 4-Green): ";
	    cin >> color;
	    topCard = color * 100 + specialCardType;
	}
}
void printBoard(int player1[50], int player2[50], int topCard, int turn, int choice , int discardPile[120]) 
{
	clearScreen();
	cout << "Player 1's Cards: " << endl;
	printPlayerhand(player1);
	cout << "\nTop Card: " << endl;
	if(turn%2==0)
	{
	    playTurn(player2, topCard, choice,discardPile);
	}
	else
	{
		playTurn(player1, topCard, choice, discardPile);
	}
	cout << "Player 2's Cards: " << endl;
	printPlayerhand(player2);
}
void pickcard(int deck[8][15], int player[50]) 
{
	for (int i = 0; i < 50; i++) 
	{
	    if (player[i] == -1) 
		{
	        int x, y;
	        do 
			{
	            x = rand() % 8;
	            y = rand() % 15;
	        } while (deck[x][y] == -1);
	        player[i] = deck[x][y];
	        deck[x][y] = -1;
	        break;
	    }
	}
}
void printPlayerhand(int player[50]) 
{
	for (int j = 0; j < 14; j++) 
	{
	    if (player[j] != -1) 
		{
	        int color = player[j] / 100;
	        int type = player[j] % 100;
	        int number = player[j] % 10;
	        if (color == 1) 
			{ 
	            setColor(BLACK, RED); 
	            cout << " ------- "; 
	        }
	        else if (color == 2) { 
	            setColor(BLACK, BLUE); 
	            cout << " ------- "; 
	        }
	        else if (color == 3) { 
	            setColor(BLACK, YELLOW); 
	            cout << " ------- "; 
	        }
	        else if (color == 4) { 
	            setColor(BLACK, GREEN); 
	            cout << " ------- "; 
	        } 
	        else
			{
	        	setColor(WHITE,BLACK);
	        	cout<<"         ";
			}               
	    }
		else
		{
	        setColor(WHITE,BLACK);
	        cout<<"         ";
		}        
	}	
	cout << endl;
	for (int j = 0; j < 14; j++) 
	{
	    if (player[j] != -1) 
		{
	        int color = player[j] / 100;
	        int type = player[j] % 100;
	        int number = player[j] % 10;
	        if (color == 1) 
			{
	            setColor(BLACK, RED); 
	            cout << " -     - ";
	        }
	        else if (color == 2) 
			{ 
	            setColor(BLACK, BLUE); 
	            cout << " -     - "; 
	        }
	        else if (color == 3) 
			{
	            setColor(BLACK, YELLOW); 
	            cout << " -     - "; 
	        }
	        else if (color == 4) 
			{
	            setColor(BLACK, GREEN); 
	            cout << " -     - "; 
	        } 
	        else
			{
	        	setColor(WHITE,BLACK);
	        	cout<<"         ";
			}
	    }        
		else
		{
	        setColor(WHITE,BLACK);
	        cout<<"         ";
		}
	}
	cout << endl;
	for (int j = 0; j < 14; j++) 
	{
	    if (player[j] != -1) 
		{
	        int color = player[j] / 100;
	        int type = player[j] % 100;
	        int number = player[j] % 10;
	        if (color == 1) 
			{ 
	            setColor(BLACK, RED); 
	            cout << " -  " ; 
				if (type == 10) 
				{ 
		            cout << "S"; 
		        } 
		        else if (type == 11) 
				{ 
		            cout << "R"; 
		        } 
		        else if (type == 12) 
				{ 
		            cout << "D"; 
		        } 
		        else if (type == 13 || type == 14) 
				{ 
		            cout << "W"; 
		        }
		        else
		        {
		        	cout<< number;	
				}
				cout<< "  - "; 
	        }
	        else if (color == 2) 
			{ 
	            setColor(BLACK, BLUE); 
	            cout << " -  " ; 
				if (type == 10) 
				{ 
		            cout << "S"; 
		        } 
		        else if (type == 11) 
				{ 
		            cout << "R"; 
		        } 
		        else if (type == 12) 
				{ 
		            cout << "D"; 
		        } 
		        else if (type == 13 || type == 14) 
				{ 
		            cout << "W"; 
		        }
		        else
		        {
		        	cout<< number;	
				}
				cout<< "  - "; 
	        }
	        else if (color == 3) 
			{ 
	            setColor(BLACK, YELLOW); 
	            cout << " -  " ; 
				if (type == 10) 
				{ 
		            cout << "S"; 
		        } 
		        else if (type == 11) 
				{ 
		            cout << "R"; 
		        } 
		        else if (type == 12) 
				{ 
		            cout << "D"; 
		        } 
		        else if (type == 13 || type == 14) 
				{ 
		            cout << "W"; 
		        }
		        else
		        {
		        	cout<< number;	
				}
				cout<< "  - "; 
	        }
	        else if (color == 4) 
			{ 
	            setColor(BLACK, GREEN); 
	            cout << " -  " ; 
				if (type == 10) 
				{ 
		            cout << "S"; 
		        } 
		        else if (type == 11) 
				{ 
		            cout << "R"; 
		        } 
		        else if (type == 12) 
				{ 
		            cout << "D"; 
		        } 
		        else if (type == 13 || type == 14) 
				{ 
		            cout << "W"; 
		        }
		        else
		        {
		        	cout<< number;	
				}
				cout<< "  - "; 
	        }
	        else
			{
	        	setColor(WHITE,BLACK);
	        	cout<<"         ";
			}
	    }        
		else
		{
	        setColor(WHITE,BLACK);
	        cout<<"         ";
		} 
	}
	cout << endl;
	for (int j = 0; j < 14; j++) 
	{
	    if (player[j] != -1) 
		{
	        int color = player[j] / 100;
	        if (color == 1) 
			{
	            setColor(BLACK, RED);
	            cout << " -     - ";
	        } else if (color == 2) 
			{
	            setColor(BLACK, BLUE);
	            cout << " -     - ";
	        } else if (color == 3) 
			{
	            setColor(BLACK, YELLOW);
	            cout << " -     - ";
	        } else if (color == 4) 
			{
	            setColor(BLACK, GREEN);
	            cout << " -     - ";
	        }
	        else
			{
	        	setColor(WHITE,BLACK);
	        	cout<<"         ";
			}
	    }
		else
		{
	        setColor(WHITE,BLACK);
	        cout<<"         ";
		}
	}
	cout << endl;
	for (int j = 0; j < 14; j++) 
	{
	    if (player[j] != -1) 
		{
	        int color = player[j] / 100;

	        if (color == 1) 
			{
	            setColor(BLACK, RED);
	            cout << " ------- ";
	        } 
			else if (color == 2) 
			{
	            setColor(BLACK, BLUE);
	            cout << " ------- ";
	        } 
			else if (color == 3) 
			{
	            setColor(BLACK, YELLOW);
	            cout << " ------- ";
	        } 
			else if (color == 4) 
			{
	            setColor(BLACK, GREEN);
	            cout << " ------- ";
	        }
	        else
			{
	        	setColor(WHITE,BLACK);
	        	cout<<"         ";
			}    
		}
		else
		{
	        setColor(WHITE,BLACK);
	        cout<<"         ";
		}
	}
	setColor(WHITE, BLACK); 
	cout << endl;
}
//latest commit
void callUNO(int& playerSize, bool& isUNOCalled, int turn,int& p1,int& p2)
{
	if (playerSize == 2)
	{
	    char choice;
	    cout << "You have only one card left! Do you want to call UNO? (U/u): ";
	    cin >> choice;
	    if (choice == 'U' || choice == 'u') 
		{
	        isUNOCalled = true;
	        cout << "UNO has been called!\n";
	        if(turn%2==0)
	        {
	            p1++;
			}
			else
			{
				p2++;
			}
	    } 
		else 
		{
	        isUNOCalled = false;
	        cout << "You chose not to call UNO.\n";
	    }
	}
}
void updateDiscardPile(int discardPile[120], int deck[8][15]) 
{
	int c=0;
	for(int i = 0 ; i <8 ; i++)
	{
		for(int j = 0 ; j<15 ; j++)
		{
			deck[i][j]= discardPile[c];
			discardPile[c]=-1;
			c++;
		}
	}
}

void mainMenu()
{
	int choice;
	cout<<"=== Welcome To Uno! ==="<< endl;
	cout<<"1. Play Uno"<< endl;
	cout<<"2. Check History" << endl;
	cout<<"3. Exit the game" << endl;
}
void shuffle(int deck[8][15])
{
	for (int i = 0; i < 8; ++i) 
	{
		for (int j = 0; j < 15; ++j) 
		{		
			int color_1 = rand() % (8 + 1);
		    int type_1 = rand() % 15;
		    int color_2=rand()%(8+1);
		    int type_2=rand()%15;	            
		    int swap=deck[color_1][type_1];
		    deck[color_1][type_1]=deck[color_2][type_2];
		    deck[color_2][type_2]=deck[color_1][type_1];
		}
	}
}
bool isHandEmpty(int player[50])
{
	int count=0;
	for(int i=0;i<50;i++)
	{
		if(player[i]!=-1)
		{
			count++;
		}
	}
	if(count==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void saveLoadGameResult(bool load, int &Wins_p1, int &Wins_p2, int winner) 
{
    if (load) 
	{
        ifstream inputFile("game_results.txt");
        if (inputFile.is_open()) 
		{
            inputFile >> Wins_p1 >> Wins_p2;
            inputFile.close();
            cout << "Game history loaded successfully!\n";
        }
		else 
		{
            cout << "No previous game history found. Starting fresh.\n";
            Wins_p1 = 0;
            Wins_p2 = 0;
        }

        cout << "Player 1 Wins: " << Wins_p1 << endl;
        cout << "Player 2 Wins: " << Wins_p2 << endl;

    } 
	else 
	{
        if (winner == 1) 
		{
            Wins_p1++;
        } 
		else if (winner == 2) 
		{
            Wins_p2++;
        }

        ofstream outputFile("game_results.txt");
        if (outputFile.is_open()) 
		{
            outputFile << Wins_p1 << " " << Wins_p2;
            outputFile.close();
        }

        cout << "\nUpdated Game Results:\n";
        cout << "Player 1 Wins: " << Wins_p1 << endl;
        cout << "Player 2 Wins: " << Wins_p2<< endl;
    }
}