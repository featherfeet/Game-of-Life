#!/usr/bin/python
ARRAY_SIZE=201
import pygame
import numpy as np
import time
pygame.init()
pygame.font.init()
screen=pygame.display.set_mode((1000,1000))
pygame.display.set_caption("Conway's Game of Life")
oldarr=np.zeros((ARRAY_SIZE,ARRAY_SIZE))
newarr=np.zeros((ARRAY_SIZE,ARRAY_SIZE))
def liveNeighbors(x,y,arr):
	returnme=0
	if arr[x,y-1]==1: #Above. Certified correct.
		returnme=returnme+1
	if arr[x+1,y]==1: #Right. Certified correct.
		returnme=returnme+1
	if arr[x,y+1]==1: #Below. Certified correct.
		returnme=returnme+1
	if arr[x-1,y]==1: #Left. Certified correct.
		returnme=returnme+1
	if arr[x-1,y-1]==1: #Top-left. Certified correct.
		returnme=returnme+1
	if arr[x+1,y-1]==1: #Top-right. Certified correct.
		returnme=returnme+1
	if arr[x+1,y+1]==1: #Bottom-right. Certified correct.
		returnme=returnme+1
	if arr[x-1,y+1]==1: #Bottom-left. Certified correct.
		returnme=returnme+1
	return returnme
def drawGame(arr):
	screen.fill(pygame.Color(255,255,255,255))
	for x in range(0,ARRAY_SIZE-1):
		for y in range(0,ARRAY_SIZE-1):
			if arr[x,y]==0:
				pygame.draw.rect(screen,pygame.Color(255,255,255,255),(x*5,y*5,5,5))
			elif arr[x,y]==1:
				pygame.draw.rect(screen,pygame.Color(0,0,0,255),(x*5,y*5,5,5))
#Set up the game.
#Glider:
"""
newarr[3,4]=1
newarr[4,4]=1
newarr[5,4]=1
newarr[5,3]=1
newarr[4,2]=1
"""
#R-pentomino:
"""
newarr[2+50,1+50]=1
newarr[2+50,2+50]=1
newarr[2+50,3+50]=1
newarr[1+50,2+50]=1
newarr[3+50,1+50]=1
"""
#End game set up.
drawGame(newarr)
pygame.display.flip()
state=0
#Create the message font object.
font=pygame.font.Font(None,20)
fontsurface=font.render("Left-click to place/remove cells. Press any key to start the simulation.",1,(255,0,0))
breakornot=False
while True: #Pre-game setup.
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			pygame.font.quit()
			pygame.quit()
			exit()
		if event.type == pygame.MOUSEBUTTONDOWN:
			(clickx,clicky)=pygame.mouse.get_pos()
			if newarr[int(clickx)/5][int(clicky)/5]==1:
				newarr[int(clickx)/5][int(clicky)/5]=0
			elif newarr[int(clickx)/5][int(clicky)/5]==0:
				newarr[int(clickx)/5][int(clicky)/5]=1
		if event.type == pygame.KEYDOWN:
			breakornot=True
	if breakornot==True:
		break
	drawGame(newarr)
	screen.blit(fontsurface,(10,10))
	pygame.display.flip()
	time.sleep(1/60)
tick=0
while True:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			pygame.font.quit()
			pygame.quit()
			exit()
	oldarr=np.copy(newarr)
	newarr=np.zeros((ARRAY_SIZE,ARRAY_SIZE))
	for x in range(0,ARRAY_SIZE-1):
		for y in range(0,ARRAY_SIZE-1):
			#Loop over each cell in oldarr and process it into a cell for newarr.
			state=oldarr[x,y]
			if state==1 and liveNeighbors(x,y,oldarr)<2:
				newarr[x,y]=0
			elif (state==1) and (liveNeighbors(x,y,oldarr)==2 or liveNeighbors(x,y,oldarr)==3):
				newarr[x,y]=1
			elif state==1 and liveNeighbors(x,y,oldarr)>3:
				newarr[x,y]=0
			elif state==0 and liveNeighbors(x,y,oldarr)==3:
				newarr[x,y]=1
	drawGame(newarr)
	tick=tick+1
	screen.blit(font.render("Tick: "+str(tick),1,(255,0,0)),(10,10))
	pygame.display.flip()
