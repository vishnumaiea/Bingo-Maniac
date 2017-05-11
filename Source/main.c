

/***************************************************************

	Name: BINGO MANIAC
	Author: Aygent543 a.k.a Vishnu M Aiea
	Copyright (c) 2013, Vishnu M Aiea
	License : GNU GPL version 3
	Contact : vishnumaiea@gmail.com
	Website : http://www.vishnumaiea.in/projects/software/bingo-maniac-game
	Date: 17:51 IST, 13-04-2013 
	
	Description: 
	
	BINGO  game  written  in  C  of  99 standard. You are
	free  to  modify  and distribute  the program  if you
	want, as this program  is  distributed  under the GNU
	General  Public  License  version  3  or  any  higher
	version  you  may choose. You can  also translate the
	program into any other language. It'd  be appreciated
	if you send information about the modification you've
	done, to author via his email. You  may also send any
	improvement  notes, bug reports  etc  to  that email.
	
	
	Press '9' on start up for information.
	Press 's' or 'S' to disable audio.
	
	
	This program is distributed  in the hope that it will 
	be useful, but WITHOUT ANY WARRANTY; without even the 
	implied  warranty of MERCHANTABILITY or FITNESS FOR A 
	PARTICULAR PURPOSE.See the GNU General Public License 
	for more details.

	You should  have  received  a copy of the GNU General 
	Public License  along  with this program. If not, see 
	<http://www.gnu.org/licenses/>.
	
	
	12:50 IST, 31-05-2013 
	
**************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio2.h> //borland extension - http://old.devpaks.org/show.php?devpak=75
#include <string.h>
#include <time.h>

#define VERSION "2.3.1.510"

static int triplet = 0; //triple bingo counter
static int sound_on = 1; //sound option

void header(void); //prints the BINGO header
void refresh(int *); //refreshes the matrix window
void bingowin(int); //when one wins
void triple_bingo(void); //when one win for three times
void about(void); //prints about


//global structure
struct data{
		unsigned int user_square[5][5];
		unsigned int user_copy[5][5]; //backup copy of user square
		unsigned int computer_square[5][5];
		unsigned int computer_copy[5][5]; //backup copy of computer square
		char user_bingo[6]; //holds bingo of user/player
		char computer_bingo[6]; //holds bingo of computer
		char bingo[6]; //holds the 'BINGO' string
		int last_remain[4]; //holds the last,reamain values of both
	}access;


int main()
{
	char a; //option variable
	int final[25]; //final random filled output
	int left[25]; //integers left to fill
	int fill[25]; //integers that are filled
	int input[50]; //take inputs from user and computer
	int status = 0; // a status variable
	static int choice = 0; //decides who first
	static int initial = 0; //var for the welcome message
	register int i,j,k,m,n,p,u; //loop vars
	int row_count = 0; //count of zeros in a row of matrix
	int column_count = 0; //count of zeros in column of matrix
	
	
	if(initial==0) //welcome message
	{
		textcolor(YELLOW);
		printf("\n\n");
		
		printf("\n\t²²²²²²    ²²²   ²²     ²    ²²²²²     ²²²²²²   ");
		printf("\n\t²     ²    ²    ² ²    ²   ²         ²      ²  ");
		printf("\n\t²     ²    ²    ²  ²   ²   ²         ²      ²  ");
		printf("\n\t²²²²²²     ²    ²   ²  ²   ²         ²      ²  ");
		printf("\n\t²     ²    ²    ²    ² ²   ²   ²²²   ²      ²  ");
		printf("\n\t²     ²    ²    ²     ²²   ²     ²   ²      ²  ");
		printf("\n\t²²²²²²    ²²²   ²      ²    ²²²²²²    ²²²²²²   ");
		printf("\n\n\n\n");
		
		textcolor(LIGHTCYAN);
		printf("\n\t    ²²    ²²    ²²²²²    ²²     ²   ²²²    ²²²²²     ²²²²²²   ²  ");
		printf("\n\t    ² ²  ² ²   ²     ²   ² ²    ²    ²    ²     ²   ²         ²  ");
		printf("\n\t    ²  ²²  ²   ²     ²   ²  ²   ²    ²    ²     ²   ²         ²  ");
		printf("\n\t    ²      ²   ²²²²²²²   ²   ²  ²    ²    ²²²²²²²   ²         ²  ");
		printf("\n\t    ²      ²   ²     ²   ²    ² ²    ²    ²     ²   ²         ²  ");
		printf("\n\t    ²      ²   ²     ²   ²     ²²    ²    ²     ²   ²            ");
		printf("\n\t    ²      ²   ²     ²   ²      ²   ²²²   ²     ²    ²²²²²²   ²  ");
	
		textcolor(DARKGRAY);
		printf("\n\n\n\n");
		printf("\n\t\t\t    Developed by AYGENT543 ");
		textcolor(LIGHTGRAY);
		initial++;
		a = getch();
		
		if(a=='9' || a=='a' || a=='A')
		{
			about();
		}
		
		else if(a=='0')
		{
			exit(0);
		}
		
		else if(a=='s' || a=='S')
		{
			sound_on = 0;
		}
		
		else if(a=='~')
		{
			triple_bingo(); //just a test
		}
	}
	
	
	for(i=0;i<50;i++) //initialization
	{
		input[i] = 66; //fill with a junk value
	}
	
	for(i=0;i<25;i++) //initialization
	{
		for(j=0;j<25;j++)
		{
			access.user_square[i][j] = 66;
			access.computer_square[i][j] = 66;
		}
	}
	
	/* user square */
	
	srand(time(NULL)); //producing seed for rand() func
	
	for(i=0;i<25;i++) //first random seeding
	{
		final[i] = (rand()%25)+1; //between 1 and 25
	}
	
	
	for(m=0,n=0,i=1;i<=25;i++) //filtering
	{
		for(j=0;j<25;j++)
		{
			if(i==final[j])
			{
				status = 1; //if the number has been filled
				break;
			}
			else 
			{
				status = 0; //if the number has not been filled
			}
		}
		 
		if(status==1)
		{
			fill[m] = i; //collects filled
			m++;
		}
		
		else if(status==0)
		{
			left[n] = i; //collects unfilled
			n++;
		}
	}
	
		
	for(m=0,i=0;i<25;i++) // final seeding of random values
	{
		for(j=(i+1);j<25;j++)
		{
			if(final[i]==final[j])
			{
				final[j] = left[m]; //remove duplicates : filling with unfilled
				m++;
			}
		}
	}
	
	
	for(m=0,i=0;i<5;i++) //copying final values to matrix
	{
		for(j=0;j<5;j++)
		{
			access.user_square[i][j] = final[m];
			m++;
		}
	}
	
	for(m=0,i=0;i<5;i++) //creating a backup copy of matrix
	{
		for(j=0;j<5;j++)
		{
			access.user_copy[i][j] = final[m];
			m++;
		}
	}
	
	/* computer square */
	
	
	srand(time(NULL)+56793); //added a value to produce different values : important
	                         //otherwise, both matrices will have same values
	
	for(i=0;i<25;i++) //first seeding of random values
	{
		final[i] = (rand()%25)+1;
	}
	
	
	for(m=0,n=0,i=1;i<=25;i++) //filtering
	{
		for(j=0;j<25;j++)
		{
			if(i==final[j])
			{
				status = 1;
				break;
			}
			else 
			{
				status = 0;
			}
		}
		
		if(status==1)
		{
			fill[m] = i;
			m++;
		}
		
		else if(status==0)
		{
			left[n] = i;
			n++;
		}
	}
	
		
	for(m=0,i=0;i<25;i++) //final seeding of random values
	{
		for(j=(i+1);j<25;j++)
		{
			if(final[i]==final[j])
			{
				final[j] = left[m];
				m++;
			}
		}
	}
	
	
	for(m=0,i=0;i<5;i++) //copying final values to matrix
	{
		for(j=0;j<5;j++)
		{
			access.computer_square[i][j] = final[m];
			m++;
		}
	}
	
	for(m=0,i=0;i<5;i++) //creating a backup copy of matrix
	{
		for(j=0;j<5;j++)
		{
			access.computer_copy[i][j] = final[m];
			m++;
		}
	}
	
	//Game Starts !
		
	header();
	textcolor(LIGHTCYAN);
	printf("\n\t\t    YOU");
	textcolor(LIGHTRED);
	printf("\t\t\t\t      COMPUTER\n\n\n");
	textcolor(LIGHTGRAY);
	
	
	for(i=0;i<5;i++) //initial dispaly of matrices
	{
		printf("\t");
		
		for(j=0;j<5;j++)
		{
			if(access.user_square[i][j]>=1 && access.user_square[i][j]<=9)
			{
				printf("[0%d]  ",access.user_square[i][j]); //added '0' for a nice look
			}
			else
			{
				printf("[%d]  ",access.user_square[i][j]);
			}
			
		}
		
		printf("\t    ");
		
		for(j=0;j<5;j++)
		{
			printf("[  ]  ");		
		}
		
		printf("\n\n\n");
	}
	
	printf("\n\n\n");
	
	strcpy(access.bingo,"BINGO"); //initializing
	
	
	for(i=0;i<6;i++) //clears array
	{
		access.user_bingo[i] = '\0';
		access.computer_bingo[i] = '\0';
	}	
	
	
	//initialized with default values
	access.last_remain[0] = 0; //last value of user
	access.last_remain[1] = 25; //remaining chances of user
	access.last_remain[2] = 0; //last value of computer
	access.last_remain[3] = 25; //remaining chances of computer
	
	
	choice = (rand()%2)+1; //decides who first
	
	
	for(i=0;i<25;i++) //main loop starts : this one is huge
	{
		/* bingo counter */
		
		row_count = 0;
		column_count = 0;
		p = 0;
		
		for(m=0;m<5;m++) //count bingo in rows of user matrix
		{
			for(n=0;n<5;n++)
			{
				if(access.user_square[m][n]==0)
				{
					row_count++; //counter
				}
				
				if(n==4 && row_count==5 && (strlen(access.user_bingo)!=5))
				{
					access.user_bingo[p] = access.bingo[p];
					if(p<4)
					{
						p++;
					}
				}
				
				if(n==4)
				{
					row_count = 0; //local reset : important
				}
			}
		}
		
		row_count = 0; //reset : important
		column_count = 0; //do not reset 'p' here
		
		for(m=0;m<5;m++) //counts bingo in columns of user matrix
		{
			for(n=0;n<5;n++)
			{
				if(access.user_square[n][m]==0)
				{
					column_count++; //counter
				}
				
				if(n==4 && column_count==5 && (strlen(access.user_bingo)!=5))
				{
					access.user_bingo[p] = access.bingo[p];
					if(p<4)
					{
						p++;
					}
				}
				
				if(n==4)
				{
					column_count = 0; //local reset : important
				}
			}
		}
		
		row_count = 0; //next hand reset : important
		column_count = 0;
		p = 0; //reset 'p' here : important
		
		for(m=0;m<5;m++) //counts bingo in computer matrix
		{
			for(n=0;n<5;n++)
			{
				if(access.computer_square[m][n]==0)
				{
					row_count++; //counter
				}
				
				if(n==4 && row_count==5 && (strlen(access.computer_bingo)!=5))
				{
					access.computer_bingo[p] = access.bingo[p];
					if(p<4)
					{
						p++;
					}
				}
				
				if(n==4)
				{
					row_count = 0; // local reset : important
				}
			}
		}
		
		row_count = 0; //next hand reset
		column_count = 0; //do not reset 'p' here : important
		
		for(m=0;m<5;m++)
		{
			for(n=0;n<5;n++)
			{
				if(access.computer_square[n][m]==0)
				{
					column_count++; //counter
				}
				
				if(n==4 && column_count==5 && (strlen(access.computer_bingo)!=5))
				{
					access.computer_bingo[p] = access.bingo[p];
					if(p<4)
					{
						p++;
					}
				}
				
				if(n==4)
				{
					column_count = 0; //local reset : important
				}
			}
		}
		
		
		if(strlen(access.user_bingo)==5)
		{
			if(choice==1 && triplet!=3)
			{
				triplet++; //your triple bingo counter
			}
			
			if(triplet==3)
			{
				triple_bingo(); //if you win for three times
			}
			
			else
			{
				bingowin(1); //if you win
			}	
		}
		
		else if(strlen(access.computer_bingo)==5)
		{
			if(choice==1)
			{
				triplet = 0; //reset if you lose a game
			}
			
			bingowin(2); //if computer wins
		}
		
		if(choice==2 && i==0)
		{
			goto second; //it jumps the user chance
		}
		
		printf("\tInput : ");
		scanf("%d",&input[i]); //scan next input from player
		access.last_remain[0] = input[i]; //tells refresh() the last used and remain
		access.last_remain[1] = 25-(i+1);
		refresh(input);
		
		second: //label for jumping
		
		/* bingo counter */
		
		row_count = 0; //initialization : important
		column_count = 0;
		p = 0;
		
		for(m=0;m<5;m++) //see the previous counter
		{
			for(n=0;n<5;n++)
			{
				if(access.user_square[m][n]==0)
				{
					row_count++;
				}
				
				if(n==4 && row_count==5 && (strlen(access.user_bingo)!=5))
				{
					access.user_bingo[p] = access.bingo[p];
					if(p<4)
					{
						p++;
					}
				}
				
				if(n==4)
				{
					row_count = 0;
				}
			}
		}
		
		row_count = 0;
		column_count = 0;
		
		for(m=0;m<5;m++)
		{
			for(n=0;n<5;n++)
			{
				if(access.user_square[n][m]==0)
				{
					column_count++;
				}
				
				if(n==4 && column_count==5 && (strlen(access.user_bingo)!=5))
				{
					access.user_bingo[p] = access.bingo[p];
					if(p<4)
					{
						p++;
					}
				}
				
				if(n==4)
				{
					column_count = 0;
				}
			}
		}
		
		row_count = 0;
		column_count = 0;
		p = 0;
		
		for(m=0;m<5;m++)
		{
			for(n=0;n<5;n++)
			{
				if(access.computer_square[m][n]==0)
				{
					row_count++;
				}
				
				if(n==4 && row_count==5 && (strlen(access.computer_bingo)!=5))
				{
					access.computer_bingo[p] = access.bingo[p];
					if(p<4)
					{
						p++;
					}
				}
				
				if(n==4)
				{
					row_count = 0;
				}
			}
		}
		
		row_count = 0;
		column_count = 0;
		
		for(m=0;m<5;m++)
		{
			for(n=0;n<5;n++)
			{
				if(access.computer_square[n][m]==0)
				{
					column_count++;
				}
				
				if(n==4 && column_count==5 && (strlen(access.computer_bingo)!=5))
				{
					access.computer_bingo[p] = access.bingo[p];
					if(p<4)
					{
						p++;
					}
				}
				
				if(n==4)
				{
					column_count = 0;
				}
			}
		}
		
		
		if(strlen(access.user_bingo)==5)
		{
			if(choice==1 && triplet!=3)
			{
				triplet++;
			}
			
			if(triplet==3)
			{
				triple_bingo();
			}
			
			else
			{
				bingowin(1); //if you win
			}
		}
		
		else if(strlen(access.computer_bingo)==5)
		{
			if(choice==1)
			{
				triplet = 0;
			}
			
			bingowin(2); //if computer wins
		}
		
		
		//intelligence
		//where computer decides next move
		
		row_count = 0;
		column_count = 0;
		
		for(u=4;u>0;u--)
		{
			for(m=0;m<5;m++)
			{
				for(n=0;n<5;n++)
				{
					if(access.computer_square[m][n]==0)
					{
						row_count++; //counts no. of zeros in rows
					}
					
					if(n==4)
					{
						if(row_count==u)
						{
							for(p=0;p<5;p++)
							{
								if(access.computer_square[m][p]!=0)
								{
									input[i+25] = access.computer_square[m][p];
									goto out; //jump :)
								}
							}
						}
						
						row_count = 0; //reset anyway!
					}
				}
			}
			
			
			for(m=0;m<5;m++)
			{
				for(n=0;n<5;n++)
				{
					if(access.computer_square[n][m]==0)
					{
						column_count++; //counts no. of zeros in columns
					}
					
					if(n==4)
					{
						if(column_count==u)
						{
							for(p=0;p<5;p++)
							{
								if(access.computer_square[p][m]!=0)
								{
									input[i+25] = access.computer_square[p][m];
									goto out; //jump!
								}
							}
						}
						
						column_count = 0;
					}
				}
			}
			
		}
		
		
		status = 66; //crap happens, you know
		
		
		//random value selector
		//used by the computer if it starts the game
		do{
			input[i+25] = (rand()%25)+1; //produce a random value
			for(k=0;k<50;k++)
			{
				if(k!=(i+25))
				{
					if(input[i+25]==input[k]) //check if that value is already called or not
					{
						status = 1; //if not called
						break;
					}
					else if(k==49)
					{
						status = 0; //if already called
					}
				}
			}
		}while(status!=0); //repeat it again!
		
		
		out: //label for jump
		printf("\t\t\t\t\t    Input : %d",input[i+25]); //prints the computer's suggestion
		access.last_remain[2] = input[i+25];
		access.last_remain[3] = 25-(i+1);
		getch();
		refresh(input);
		
		/* bingo counter */
		
		row_count = 0;
		column_count = 0;
		p = 0;
		
		for(m=0;m<5;m++)
		{
			for(n=0;n<5;n++)
			{
				if(access.user_square[m][n]==0)
				{
					row_count++;
				}
				
				if(n==4 && row_count==5 && (strlen(access.user_bingo)!=5))
				{
					access.user_bingo[p] = access.bingo[p];
					if(p<4)
					{
						p++;
					}
				}
				
				if(n==4)
				{
					row_count = 0;
				}
			}
		}
		
		row_count = 0;
		column_count = 0;
		
		for(m=0;m<5;m++)
		{
			for(n=0;n<5;n++)
			{
				if(access.user_square[n][m]==0)
				{
					column_count++;
				}
				
				if(n==4 && column_count==5 && (strlen(access.user_bingo)!=5))
				{
					access.user_bingo[p] = access.bingo[p];
					if(p<4)
					{
						p++;
					}
				}
				
				if(n==4)
				{
					column_count = 0;
				}
			}
		}
		
		row_count = 0;
		column_count = 0;
		p = 0;
		
		for(m=0;m<5;m++)
		{
			for(n=0;n<5;n++)
			{
				if(access.computer_square[m][n]==0)
				{
					row_count++;
				}
				
				if(n==4 && row_count==5 && (strlen(access.computer_bingo)!=5))
				{
					access.computer_bingo[p] = access.bingo[p];
					if(p<4)
					{
						p++;
					}
				}
				
				if(n==4)
				{
					row_count = 0;
				}
			}
		}
		
		row_count = 0;
		column_count = 0;
		
		for(m=0;m<5;m++)
		{
			for(n=0;n<5;n++)
			{
				if(access.computer_square[n][m]==0)
				{
					column_count++;
				}
				
				if(n==4 && column_count==5 && (strlen(access.computer_bingo)!=5))
				{
					access.computer_bingo[p] = access.bingo[p];
					if(p<4)
					{
						p++;
					}
				}
				
				if(n==4)
				{
					column_count = 0;
				}
			}
		}
		
		if(strlen(access.computer_bingo)==5)
		{
			if(choice==1)
			{
				triplet = 0;
			}
			
			bingowin(2); //if computer wins
		}
		
		else if(strlen(access.user_bingo)==5)
		{		
			if(choice==1 && triplet!=3)
			{
				triplet++;
			}
			
			if(triplet==3)
			{
				triple_bingo(); //if you win for three times
			}
			
			else
			{
				bingowin(1); //if you win
			}
		}
	} //main loop ends
		
	getch();
	return 0;
} //main ends



/*############################################################################*/
void header() //prints BINGO header
{
	system("cls");
	textcolor(LIGHTCYAN); //change color for following text
	printf("--------------------------------------------------------------------------------");
	textcolor(YELLOW);
	printf("||                  >>>>>   B I N G O   M A N I A C   <<<<<                   ||");
	textcolor(LIGHTCYAN);
	printf("--------------------------------------------------------------------------------");
	textcolor(LIGHTGRAY); //do not forget to set the default back
}
/*############################################################################*/




/*############################################################################*/
void refresh(int *input) //imports the pointer
{
	register unsigned int i,j,k;
	int status = 0;
	
	header(); //prints header
	
	textcolor(LIGHTCYAN);
	printf("\n\t\t    YOU");
	textcolor(LIGHTRED);
	printf("\t\t\t\t      COMPUTER\n\n");
	textcolor(LIGHTGRAY);
	printf("\tLast : %d\t  Remain :%d\t    ",access.last_remain[0],access.last_remain[1]);
	printf("Last : %d\t      Remain :%d\n\n\n",access.last_remain[2],access.last_remain[3]);
	
	
	for(i=0;i<5;i++)
	{
		printf("\t");
		
		for(j=0;j<5;j++) //prints player matrix
		{
			if(access.user_square[i][j]>=1 && access.user_square[i][j]<=9)
			{
				for(k=0;k<50;k++)
				{
					if(access.user_square[i][j]==input[k] || access.user_square[i][j]==0)
					{
						textcolor(LIGHTGREEN);
						printf("[$$]  "); //for marking called values
						textcolor(LIGHTGRAY);
						access.user_square[i][j] = 0; //marks by setting zero
						break; //important
					}
					
					else if(k==49) //as usual
					{
						printf("[0%d]  ",access.user_square[i][j]);
					}
				}						
			}
			
			else
			{
				for(k=0;k<50;k++)
				{
					if(access.user_square[i][j]==input[k] || access.user_square[i][j]==0)
					{
						textcolor(LIGHTGREEN);
						printf("[$$]  ");
						textcolor(LIGHTGRAY);
						access.user_square[i][j] = 0;
						break;
					}
					
					else if(k==49)
					{
						printf("[%d]  ",access.user_square[i][j]);
					}
				}						
			}			
		}
		
		printf("\t    ");
		
		for(j=0;j<5;j++) //prints computer matrix
		{
			if(access.computer_square[i][j]>=1 && access.computer_square[i][j]<=9)
			{
				for(k=0;k<50;k++)
				{
					if(access.computer_square[i][j]==input[k] || access.computer_square[i][j]==0)
					{
						textcolor(LIGHTGREEN);
						printf("[$$]  ");
						textcolor(LIGHTGRAY);
						access.computer_square[i][j] = 0;
						break;
					}
					
					else if(k==49)
					{
						printf("[  ]  ");
					}
				}			
			}
			else
			{
				for(k=0;k<50;k++)
				{
					if(access.computer_square[i][j]==input[k] || access.computer_square[i][j]==0)
					{
						textcolor(LIGHTGREEN);
						printf("[$$]  ");
						textcolor(LIGHTGRAY);
						access.computer_square[i][j] = 0;
						break;
					}
					
					else if(k==49)
					{
						printf("[  ]  ");
					}
				}				
			}			
		}
		
		if(i==4)
		{
			printf("\n\n");
		}
		
		else
		{
			printf("\n\n\n");
		}		
	}
	
	textcolor(LIGHTCYAN);
	printf("\t\t   %s",access.user_bingo);
	textcolor(LIGHTRED);
	printf("\t\t\t\t       %s\n\n",access.computer_bingo);
	textcolor(LIGHTGRAY);
	
	if(i==4)
	{
		getch();
		exit(0);
	}
}
/*############################################################################*/




/*############################################################################*/
void bingowin(int pm)
{
	int i,j,k;
	system("cls");
	
	if(sound_on==1) //if option is yes
	{
		if(pm==1)
		{
			PlaySound (TEXT ("youwin.wav"), NULL, SND_FILENAME | SND_ASYNC) ;
		}
	
		else if(pm==2)
		{
			PlaySound (TEXT ("computerwins.wav"), NULL, SND_FILENAME | SND_ASYNC) ;
		}
	}
	
	
	textcolor(YELLOW);
	printf("\n\n\n\n\n");
	
	printf("\n\t\t²²²²²²    ²²²   ²²     ²    ²²²²²     ²²²²²²    ²");
	printf("\n\t\t²     ²    ²    ² ²    ²   ²         ²      ²   ²");
	printf("\n\t\t²     ²    ²    ²  ²   ²   ²         ²      ²   ²");
	printf("\n\t\t²²²²²²     ²    ²   ²  ²   ²         ²      ²   ²");
	printf("\n\t\t²     ²    ²    ²    ² ²   ²   ²²²   ²      ²   ²");
	printf("\n\t\t²     ²    ²    ²     ²²   ²     ²   ²      ²    ");
	printf("\n\t\t²²²²²²    ²²²   ²      ²    ²²²²²²    ²²²²²²    ²");
	
	if(pm==1) //if you win
	{
		textcolor(LIGHTCYAN);
		printf("\n\n\n\n\n\n\n\t\t\t\tY O U   W I N ! ");
		textcolor(LIGHTGRAY);
	}
	else if(pm==2) //if computer wins
	{
		textcolor(LIGHTRED);
		printf("\n\n\n\n\n\n\n\t\t\t  C O M P U T E R   W I N S ! ");
		textcolor(LIGHTGRAY);
	}
	getch();
	
	header();
	
	textcolor(LIGHTCYAN);
	printf("\n\t\t    YOU");
	textcolor(LIGHTRED);
	printf("\t\t\t\t      COMPUTER\n\n\n");
	textcolor(LIGHTGRAY);
	
	for(i=0;i<5;i++) //print both the squares
	{
		printf("\t");
		
		for(j=0;j<5;j++)
		{
			if(access.user_copy[i][j]>=0 && access.user_copy[i][j]<=9)
			{
				printf("[0%d]  ",access.user_copy[i][j]); //added '0' for nice look
			}
			else
			{
				printf("[%d]  ",access.user_copy[i][j]);
			}
			
		}
		
		printf("\t    ");
		
		for(j=0;j<5;j++)
		{
			if(access.computer_copy[i][j]>=0 && access.computer_copy[i][j]<=9)
			{
				printf("[0%d]  ",access.computer_copy[i][j]);
			}
			else
			{
				printf("[%d]  ",access.computer_copy[i][j]);
			}
			
		}
		
		printf("\n\n\n");
	}
	
	printf("\n\n\tThese were the previous squares. Press any key to continue ");
	getch();
	
	main(); //return to main
}
/*############################################################################*/




/*############################################################################*/
void triple_bingo()
{
	int i,j,k;
	system("cls");
	
	if(sound_on==1) //if option is yes
	{
		PlaySound (TEXT ("triplewin.wav"), NULL, SND_FILENAME | SND_ASYNC) ;
	}
	
	printf("\n\n\n\n");
	textcolor(LIGHTCYAN);
	printf("\t\t\t     > > > ");
	textcolor(YELLOW);
	printf("T R I P L E ");
	textcolor(LIGHTCYAN);
	printf("< < <\n\n\n");
	textcolor(YELLOW);
	printf("\n\t\t²²²²²²    ²²²   ²²     ²    ²²²²²     ²²²²²²    ²");
	textcolor(LIGHTMAGENTA);
	printf("\n\t\t²     ²    ²    ² ²    ²   ²         ²      ²   ²");
	textcolor(LIGHTGREEN);
	printf("\n\t\t²     ²    ²    ²  ²   ²   ²         ²      ²   ²");
	printf("\n\t\t²²²²²²     ²    ²   ²  ²   ²         ²      ²   ²");
	textcolor(LIGHTRED);
	printf("\n\t\t²     ²    ²    ²    ² ²   ²   ²²²   ²      ²   ²");
	printf("\n\t\t²     ²    ²    ²     ²²   ²     ²   ²      ²    ");
	textcolor(YELLOW);
	printf("\n\t\t²²²²²²    ²²²   ²      ²    ²²²²²²    ²²²²²²    ²");
	
	textcolor(LIGHTCYAN);
	printf("\n\n\n\n\n\n\n\t\t\t\t Y O U   W I N ! ");
	textcolor(LIGHTGRAY);

	getch();
	
	triplet = 0; //reset the triple bingo counter
	
	header();
	textcolor(LIGHTCYAN);
	printf("\n\t\t    YOU");
	textcolor(LIGHTRED);
	printf("\t\t\t\t      COMPUTER\n\n\n");
	textcolor(LIGHTGRAY);
	
	for(i=0;i<5;i++) //print both the squares
	{
		printf("\t");
		
		for(j=0;j<5;j++)
		{
			if(access.user_copy[i][j]>=0 && access.user_copy[i][j]<=9)
			{
				printf("[0%d]  ",access.user_copy[i][j]); //added '0' for nice look
			}
			else
			{
				printf("[%d]  ",access.user_copy[i][j]);
			}
			
		}
		
		printf("\t    ");
		
		for(j=0;j<5;j++)
		{
			if(access.computer_copy[i][j]>=0 && access.computer_copy[i][j]<=9)
			{
				printf("[0%d]  ",access.computer_copy[i][j]);
			}
			else
			{
				printf("[%d]  ",access.computer_copy[i][j]);
			}
			
		}
		
		printf("\n\n\n");
	}
	
	printf("\n\n\tThese were the previous squares. Press any key to continue ");
	getch();
	
	main(); //return to main
}
/*############################################################################*/




/*############################################################################*/
void about()
{
	system("cls");
	textcolor(YELLOW);
	printf("\n\n\n\n\n\n\n\t\t\t     B I N G O");
	textcolor(LIGHTCYAN);
	printf("   M A N I A C");
	textcolor(LIGHTGRAY);
	printf("\n\t\t\t     -----------------------");
	printf("\n\n\t\t\t     Bingo game written in C");
	printf("\n\n\t\t\t\tVersion %s",VERSION);
	printf("\n\n\n\t\t       Copyright (c) 2013 by Vishnu M Aiea");
	printf("\n\n\n\t\t\t       aygent543@gmail.com ");
	getch();
	main();
}
/*############################################################################*/

