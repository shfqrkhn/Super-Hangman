#include "stdafx.h"
#include "FHangman.h"

// Starts a new game
void FHangman::NewGame(int Life, int Level)
{
	// Set initial life to 6 = number of appendages on hangman
	this->Life = Life;

	// Set initial level to 1
	this->Level = Level;

	// Clear Misses vector
	Misses.clear();
}

// Returns the name of the file according to the level of difficulty
std::string FHangman::GetFileName(int level)
{
	std::string FilePath = "hdb_00.txt";
	std::vector<std::string> words;
	FileToVector(FilePath, words, level);

	return words[level - 1];
}

// Returns a random number to choose a random word from a vector given initial and final values
int FHangman::RandomNumber(int Initial, int Final)
{
	srand((unsigned int)time(NULL));
	return Initial + rand() % Final;
}

// Stores a given file in a pass-by-reference vector based on given level of difficulty
int FHangman::FileToVector(std::string FilePath, std::vector<std::string> &words, int level)
{
	std::ifstream file(FilePath);

	if (!file)
	{
		printf("Error opening the file");
		return 1;
	}

	std::string word;
	while (file >> word)
	{
		words.push_back(word);
	}

	file.close();

	return 0;
}

// Chooses a word randomly according to difficulty level
std::string FHangman::ChooseWord(int level)
{
	std::string FilePath = GetFileName(level);
	std::vector<std::string> words;
	FileToVector(FilePath, words, level);

	int randomIndex = RandomNumber(0, words.size());
	return words[randomIndex];
}

// Draws the hangman art based on number of turns left
void FHangman::HangmanArt(int Life)
{
	std::string Zero[] = { "  __________" , " |         |" , " |         0" , " |        /|\\" , " |        / \\" , " |" , " |" };
	std::string One[] = { "  __________" , " |         |" , " |         0" , " |        /|\\" , " |          \\" , " |" , " |" };
	std::string Two[] = { "  __________" , " |         |" , " |         0" , " |        /|\\" , " |" , " |" , " |" };
	std::string Three[] = { "  __________" , " |         |" , " |         0" , " |        /|" , " |" , " |" , " |" };
	std::string Four[] = { "  __________" , " |         |" , " |         0" , " |         |" , " |" , " |" , " |" };
	std::string Five[] = { "  __________" , " |         |" , " |         0" , " |" , " |" , " |" , " |" };
	std::string Six[] = { "  __________" , " |         |" , " |          " , " |" , " |" , " |" , " |" };

	switch (Life) {
	case 0:
		DrawHangmanArt(Zero);
		break;
	case 1:
		DrawHangmanArt(One);
		break;
	case 2:
		DrawHangmanArt(Two);
		break;
	case 3:
		DrawHangmanArt(Three);
		break;
	case 4:
		DrawHangmanArt(Four);
		break;
	case 5:
		DrawHangmanArt(Five);
		break;
	case 6:
		DrawHangmanArt(Six);
		break;
	default:
		std::cout << "You start with 20 lives.\nCorrect guess gains you a life.\nWrong guess makes you lose a life.\n" << std::endl;
	}
}

// Output string array elements one-by-one in new lines to draw hangman
void FHangman::DrawHangmanArt(std::string *Hangman)
{
	for (int i = 0; i < 7; i++)
	{
		std::cout << Hangman[i] << std::endl;
	}
}

// Shows game stats: Turns Left, Player Level, Spent Letters
void FHangman::DrawStats(int Life, int Level)
{
	std::cout << "=========== STATS ===========" << std::endl;
	std::cout << " Life: " << Life << "\n Level: " << Level << std::endl;
	std::cout << "=============================" << std::endl;

	int VectorMissesSize = Misses.size();
	std::cout << "You have guesses these letters already: ";
	for (int i = 0; i < VectorMissesSize; i++)
	{
		std::cout << Misses[i] << ", ";
	}
	std::cout << std::endl;
}

// This is the game UI coming together
void FHangman::GameUI(int Life, int Level, std::string& TempWord)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hConsole);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

	system("cls");

	DrawIntro();

	HangmanArt(Life);

	DrawStats(Life, Level);

	std::cout << "Word: " << TempWord << std::endl;

	SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
}

// Show game intro
void FHangman::DrawIntro()
{
	std::cout << "------------- SUPER HANGMAN -------------" << std::endl;
	std::cout << "Guess the word before your man gets hung!" << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
}

// Shows game rules and tips
void FHangman::DrawHelp()
{
	system("cls");

	DrawIntro();

	std::cout << "----------------------- WHAT IS HANGMAN? ------------------------" << std::endl;
	std::cout << "Hangman is a simple word guessing game." << std::endl;
	std::cout << "Players try to figure out an unknown word by guessing letters." << std::endl;
	std::cout << "If too many letters which do not appear in the word are guessed, " << std::endl;
	std::cout << "the player is hanged (and loses)." << std::endl;
	std::cout << "-----------------------------------------------------------------\n" << std::endl;
	std::cout << "------------------------------- TIPS & TRICKS -------------------------------" << std::endl;
	std::cout << "A good acronym to commit to memory is: ETAOIN SHRDLU." << std::endl;
	std::cout << "It denotes the most commonly used letters (in order) in the English language." << std::endl;
	std::cout << "-----------------------------------------------------------------------------\n" << std::endl;

	system("pause");
	MainMenu();
}

// The main menu of the game
int FHangman::MainMenu()
{
	system("cls");

	DrawIntro();

	std::cout << " [1] Start Game\n";
	std::cout << " [2] Help\n";
	std::cout << " [3] Quit\n";

	int Choice = 0;

	while (Choice < 1 || Choice > 3)
	{
		std::cout << "\n Enter a valid choice [1, 2, or 3]: ";

		std::cin >> Choice;

		if (Choice > 0 && Choice < 5)
		{
			switch (Choice)
			{
			case 1:
				// start a new game
				NewGame(20, Level);
				GameUI(20, Level, TempWord);
				PlayGame();
				break;
			case 2:
				DrawHelp();
				break;
			case 3:
				exit(1);
				break;
			default:
				std::cout << "invalid case\n";
			}
		}
		else {
			std::cout << "\n You entered an invalid choice.\n";
			break;
		}
	}

	return 0;
}

// Converts a string to a pass-by-ref char array
void FHangman::StringToCharArray(std::string &Word, char* CharArray)
{
	int n = Word.length() + 1;
	strcpy_s(CharArray, n, Word.c_str());
}

// Converts a pass-by-ref char array to string
std::string FHangman::CharArrayToString(char *CharArray)
{
	std::string Word(CharArray);
	return Word;
}

// Gets char input from user
char FHangman::GetGuess()
{
	char c;
	do
	{
		std::cout << "Guess a letter (lower-case, a-z) in the word: ";
		std::cin >> c;
		if (!isalpha(c))
		{
			std::cout << "Enter a lower-case letter between a and z only. Let's try again." << std::endl;
		}
	} while (!isalpha(c));
	return c;
}

// TODO Clean up the code
// Like a true professional I am releasing an unpolished product
// This is the game coming together
void FHangman::PlayGame()
{
	// Computer chooses a word based on current level
	std::string ChosenWord = ChooseWord(Level);

	// Finding the length of the word for later use
	// By default, the word length depends on difficulty level, but it can be changed -> See level editor comment above
	int ChosenWordLength = ChosenWord.length();

	// Showing the word as dashes
	std::string TempWord(ChosenWordLength, '_');

	bool bWin = false;
	bool bLose = false;

	while (!bWin && !bLose)
	{
		char Guess = GetGuess();

		for (int i = 0; i < ChosenWordLength; i++)
		{
			if (Guess == ChosenWord[i])
			{
				this->Life++;
				TempWord[i] = Guess;
			}
		}

		bool bIsMiss = false;
		for (int i = 0; i < ChosenWordLength; i++)
		{
			if (Guess != ChosenWord[i])
			{
				bIsMiss = true;
			}
			else
			{
				bIsMiss = false;
			}
		}

		if (bIsMiss)
		{
			Misses.push_back(Guess);
		}

		if (TempWord == ChosenWord)
		{
			bWin = true;
			Level++;
			if (Level == 21)
			{
				std::cout << "You broke my game. Let's start from Level 1!\n";
				this->Level = 1;
			}
			GameUI(Life, Level, TempWord);
			std::cout << "\nYou got it! The word is: " << ChosenWord << std::endl;

			HANDLE  hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			FlushConsoleInputBuffer(hConsole);
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			std::cout << "\nChoose [1] in the next screen to continue to the NEXT level\n\n";
			SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);

			system("PAUSE");
		}
		else
		{
			Life--;
		}

		if (Life == 0)
		{
			bLose = true;
			std::cout << "You ran out of lives. The word was: " << ChosenWord << ". Let's try again :)" << std::endl;
			system("PAUSE");
		}

		if (bWin || bLose)
		{
			MainMenu();
		}

		GameUI(Life, Level, TempWord);
	}
}

// Tests various functions of the program
void FHangman::CodeTesting()
{
	
}
