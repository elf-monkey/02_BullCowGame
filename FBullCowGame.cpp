#include "FBullCowGame.h"
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } //constructor

// these are the getters
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLenght() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const {	return bGameIsWon; }

// this are the methods
void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 5;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (false) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram; // TODO Write function
	}
	else if (false) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase; // TODO Write function
	}
	else if (Guess.length() != GetHiddenWordLenght()) // if the guess lenght is wrong
	{
		return EGuessStatus::Wrong_Lenght;
	}
	else
	{
		return EGuessStatus::OK;
	}
		// return error
	// otherwise
		// return ok
}

// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount; // set up a return variable
	int32 WordLenght = MyHiddenWord.length(); // Assuming same length as GUESS, loop trough all the letters in the word

	for (int32 MHWChar = 0; MHWChar < WordLenght; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLenght; GChar++)	{
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) 	{
				if (MHWChar == GChar)	{ // if in the same place
					BullCowCount.Bulls++; // increment bulls
				}
				else {
					BullCowCount.Cows++; // must be a cow	
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLenght) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
		return BullCowCount;
}
