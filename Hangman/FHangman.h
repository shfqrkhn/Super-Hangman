// *** Level Editing ***
// It uses a predefined library of words. Higher difficulty would use a list of isograms (words without repeating letters)
// hdb_00.txt is the list of available word lists. The word lists are arranged in order of increasing difficulty
// hbd_xx.txt are the word lists containint xx-lettered words, e.g., hbd_03.txt contains 3-lettered words
// hdb_iso_10.txt contains 10-lettered isograms

// *** TODO List ***
// Computer chooses a secret word from a list of words
//	1. Store all words in a vector
//	2. Get length of vector
//	3. Choose a random word from the vector

// Draw game interface
// 1. Computer draws a blank line for each letter in the word
// 2. Show stats
// 3. Create a main menu: new game, help, quit

// Player starts guessing letters: accept upper or lower case letters only
//	1. Get user input
//	2. Use isalpha() http://www.cplusplus.com/reference/cctype/isalpha/

// Computer fills the letter in the blanks if the players guess correctly

// Computer shows the player a list of letters already used -- taken out of scope, increased initial life to 20

// Computer draws part of the "hangman" when the players guess wrong

// Player wins when they guess the correct word

/* Stock image
6 tries
_________
|         |
|         0
|        /|\
|        / \
|
|
*/

#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>
#include <windows.h> 

class FHangman
{
public:
	// The main menu of the game
	int MainMenu();

	// Life Getters and Setters
	int GetLife() { return Life; }
	void SetLife(int Life) { this->Life = Life; }

	// Level Getters and Setters
	int GetLevel() { return Level; }
	void SetLevel(int Level) { this->Level = Level; }

private:
	// Stores the number of lives (0-6)
	int Life = 20;

	// Stores difficulty level (1-20)
	int Level = 1;

	// A temporary string
	std::string TempWord = "";

	// This vector stores the incorrect guesses
	std::vector<char> Misses;

	// Starts a new game
	void NewGame(int Life, int Level);

	// Returns the name of the file according to the level of difficulty
	std::string GetFileName(int level);

	// Returns a random number to choose a random word from a vector given initial and final values
	int RandomNumber(int start, int end);

	// Stores a given file in a pass-by-reference vector based on given level of difficulty
	int FileToVector(std::string FilePath, std::vector<std::string> &words, int level = 1);

	// Chooses a word randomly according to difficulty level
	std::string ChooseWord(int level);

	// Stores hangman arts at different states
	void HangmanArt(int Life);

	// Output string array elements one-by-one in new lines to draw hangman
	void DrawHangmanArt(std::string *Hangman);

	// Show game intro
	void DrawIntro();

	// Shows game rules and tips
	void DrawHelp();

	// Gets and returns char input from user
	char GetGuess();

	// Converts a string to a pass-by-ref char array
	void StringToCharArray(std::string &Word, char *CharArray);

	// Converts a pass-by-ref char array to string
	std::string CharArrayToString(char *CharArray);

	// This is the game UI coming together
	void GameUI(int Life, int Level, std::string& TempWord);

	// Shows game stats: Turns Left, Player Level, Spent Letters
	void DrawStats(int Life, int Level);

	// This is the game coming together
	void PlayGame();

	// Tests various functions of the program
	void CodeTesting();
};