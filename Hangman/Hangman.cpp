// Hangman.cpp : Defines the entry point for the console application.

// *** Game Description ***
// This is a Hangman game with variable level of difficulties
// As the player progresses, the difficulties goes up

#include "stdafx.h"
#include "FHangman.h"

int main()
{
	FHangman Hangman;
	Hangman.MainMenu();

	//std::cin.get();
	system("PAUSE");
	return 0;
}