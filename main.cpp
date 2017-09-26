/*
This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user ineraction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;  //intantiate new object

// the entry point for the application
int main ()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		// ADD A GAME SUMMARY
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0; // exit app
}

// ****** introduce the game
void PrintIntro()
{
	std::cout << "\n\n\welcome to Bulls & Cows\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLenght();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << MaxTries << std::endl;

	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) 
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

	
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
				// get guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try number: " << CurrentTry << " of " <<  BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";		
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Lenght:
			std::cout << "NO you idiot! enter a " << BCGame.GetHiddenWordLenght() << " letter word as you where told! \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// asume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep loopoing until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same word (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');

	// std::cout << "Is it y? " << (Response[0] == 'y') || (Response[0] == 'Y');
	std::cout << std::endl;
}
void PrintGameSummary() {
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE!\n";
	}
	else
	{
		std::cout << "YOU LOOSE!\n";
	}
}
