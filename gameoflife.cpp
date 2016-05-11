#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <fstream>
#define DRAW_SIZE_X 80 //Width of area drawn.
#define DRAW_SIZE_Y 24 //Height of area drawn.
#define ARRAY_SIZE_X 500 //Width of area in memory.
#define ARRAY_SIZE_Y 500 //Height of area in memory.
using namespace std;
int oldarr[ARRAY_SIZE_X][ARRAY_SIZE_Y];
int newarr[ARRAY_SIZE_X][ARRAY_SIZE_Y];
int liveNeighbors(int x,int y,int arr[ARRAY_SIZE_X][ARRAY_SIZE_Y]) //Use Cartesian coordinate system.
{
	int neighbors=0;
	if (arr[x][y+1]==1) //Above.
	{
		neighbors++;
	}
	if (arr[x][y-1]==1) //Below.
	{
		neighbors++;
	}
	if (arr[x+1][y]==1) //Right.
	{
		neighbors++;
	}
	if (arr[x-1][y]==1) //Left.
	{
		neighbors++;
	}
	if (arr[x-1][y+1]==1) //Top-left.
	{
		neighbors++;
	}
	if (arr[x+1][y+1]==1) //Top-right.
	{
		neighbors++;
	}
	if (arr[x+1][y-1]==1) //Bottom-right.
	{
		neighbors++;
	}
	if (arr[x-1][y-1]==1) //Bottom-left.
	{
		neighbors++;
	}
	return neighbors;
}
int main()
{
	cout << "Conway's Game of Life by Oliver Trevor" << endl;
	cout << "Click to place/remove cells, up arrow to start simulation, down arrow to load a pattern file, and right arrow to save pattern." << endl;
	cout << "The game starts in 5 seconds..." << endl;
	system(("resize -s "+to_string(DRAW_SIZE_Y)+" "+to_string(DRAW_SIZE_X)).c_str());
	resizeterm(DRAW_SIZE_Y,DRAW_SIZE_X);
	sleep(5);
	initscr();
	start_color();
	init_pair(1,COLOR_BLACK,COLOR_BLACK);
	init_pair(2,COLOR_WHITE,COLOR_WHITE);
	init_pair(3,COLOR_BLACK,COLOR_WHITE);
	refresh();
	int countx;
	int county;
	int tick=0;
	for (countx=0;countx!=ARRAY_SIZE_X;countx++)
	{
		for (county=0;county!=ARRAY_SIZE_Y;county++)
		{
			oldarr[countx][county]=0;
		}
	}
	for (countx=0;countx!=ARRAY_SIZE_X;countx++)
	{
		for (county=0;county!=ARRAY_SIZE_Y;county++)
		{
			newarr[countx][county]=0;
		}
	}
	//Set up newarr between this line...
	keypad(stdscr,TRUE);
	mousemask(BUTTON1_CLICKED,NULL);
	MEVENT event;
	int ch;
	char input[100];
	char input2[100];
	char input3[100];
	fstream file;
	string line;
	int x;
	int y;
	int xoffset;
	int yoffset;
	while (1)
	{
		attron(COLOR_PAIR(3));
		for (countx=0;countx!=DRAW_SIZE_X;countx++)
		{
			for (county=0;county!=DRAW_SIZE_Y;county++)
			{
				//Draw.
				if (newarr[countx][county]==0)
				{
					mvprintw(county,countx,"+");
				}
			}
		}
		refresh();
		ch=getch();
		if (ch==KEY_MOUSE)
		{
			if (getmouse(&event)==OK)
			{
				if (newarr[event.x][event.y]==0)
				{
					newarr[event.x][event.y]=1;
				}
				else if (newarr[event.x][event.y]==1)
				{
					newarr[event.x][event.y]=0;
				}
			}
		}
		else if (ch==KEY_UP)
		{
			break;
		}
		else if (ch==KEY_DOWN) //Load pattern file.
		{
			attron(COLOR_PAIR(3));
			mvprintw(0,0,"Name of pattern file (to load): ");
			refresh();
			echo();
			mvgetstr(0,32,input);
			mvprintw(1,0,"X-offset to load at: ");
			mvgetstr(1,21,input2);
			mvprintw(2,0,"Y-offset to load at: ");
			mvgetstr(2,21,input3);
			noecho();
			xoffset=atoi(input2);
			yoffset=atoi(input3);
			file.open(input);
			getline(file,line); //Get rid of the initial comment line.
			while (getline(file,line))
			{
				sscanf(line.c_str(),"%d %d",&x,&y);
				newarr[x+xoffset][y+yoffset]=1;
			}
			file.close();
			mvprintw(1,0,"Info: Pattern loaded.");
			for (countx=0;countx!=DRAW_SIZE_X;countx++)
			{
				for (county=0;county!=DRAW_SIZE_Y;county++)
				{
					//Draw.
					if (newarr[countx][county]==0)
					{
						attron(COLOR_PAIR(2));
						mvprintw(county,countx," ");
					}
					else if (newarr[countx][county]==1)
					{
						attron(COLOR_PAIR(1));
						mvprintw(county,countx," ");
					}
				}
			}
			refresh();
			sleep(3);
			break;
		}
		else if (ch==KEY_RIGHT) //Save pattern file.
		{
			attron(COLOR_PAIR(3));
			mvprintw(0,0,"Name of pattern file (to save): ");
			refresh();
			echo();
			mvgetstr(0,32,input);
			noecho();
			refresh();
			file.open(input,fstream::out);
			file << "#Life 1.06" << endl;
			for (countx=0;countx!=DRAW_SIZE_X;countx++)
			{
				for (county=0;county!=DRAW_SIZE_Y;county++)
				{
					if (newarr[countx][county]==1)
					{
						file << countx << " " << county << endl;
					}
				}
			}
			file.close();
			mvprintw(1,0,"Info: Pattern saved to file.");
			refresh();
			sleep(3);
			break;
		}
		for (countx=0;countx!=DRAW_SIZE_X;countx++)
		{
			for (county=0;county!=DRAW_SIZE_Y;county++)
			{
				//Draw.
				if (newarr[countx][county]==0)
				{
					attron(COLOR_PAIR(2));
					mvprintw(county,countx," ");
				}
				else if (newarr[countx][county]==1)
				{
					attron(COLOR_PAIR(1));
					mvprintw(county,countx," ");
				}
			}
		}
	}
	//and this line.
	while (1)
	{
		for (countx=0;countx!=ARRAY_SIZE_X;countx++)
		{
			for (county=0;county!=ARRAY_SIZE_Y;county++)
			{
				oldarr[countx][county]=newarr[countx][county];
			}
		}
		for (countx=0;countx!=ARRAY_SIZE_X;countx++)
		{
			for (county=0;county!=ARRAY_SIZE_Y;county++)
			{
				newarr[countx][county]=0;
			}
		}
		for (countx=0;countx!=ARRAY_SIZE_X;countx++)
		{
			for (county=0;county!=ARRAY_SIZE_Y;county++)
			{
				//The rules go here.
				if (oldarr[countx][county]==1 && liveNeighbors(countx,county,oldarr)<2)
				{
					newarr[countx][county]=0;
				}
				else if (oldarr[countx][county]==1 && (liveNeighbors(countx,county,oldarr)==2 || liveNeighbors(countx,county,oldarr)==3))
				{
					newarr[countx][county]=1;
				}
				else if (oldarr[countx][county]==1 && liveNeighbors(countx,county,oldarr)>3)
				{
					newarr[countx][county]=0;
				}
				else if (oldarr[countx][county]==0 && liveNeighbors(countx,county,oldarr)==3)
				{
					newarr[countx][county]=1;
				}
			}
		}
		tick++;
		for (countx=0;countx!=DRAW_SIZE_X;countx++)
		{
			for (county=0;county!=DRAW_SIZE_Y;county++)
			{
				//Draw.
				if (newarr[countx][county]==0)
				{
					attron(COLOR_PAIR(2));
					mvprintw(county,countx," ");
				}
				else if (newarr[countx][county]==1)
				{
					attron(COLOR_PAIR(1));
					mvprintw(county,countx," ");
				}
			}
		}
		attron(COLOR_PAIR(3));
		mvprintw(0,0,"Tick: %i",tick);
		refresh();
		usleep(17000);
	}
	endwin();
	return 0;
}
