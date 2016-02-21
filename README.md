# Game-of-Life
A command-line ncurses version of Conway's Game of Life, written in C++.
This program will compile and run on all POSIX-compatible systems with C++ compilers.
To change the area drawn in the terminal, change the macros DRAW_SIZE_X and DRAW_SIZE_Y, then recompile.
To change the area represented in memory, change the macros ARRAY_SIZE_X and ARRAY_SIZE_Y, then recompile.
When the screen full of plus signs appears, click to place/remove cells, press the up arrow key to start the simulation, press the right arrow key to save a pattern, and press the down arrow key to load a pattern.
So far, only Life 1.06 files (*.LIF/*.LIFE) are supported.
