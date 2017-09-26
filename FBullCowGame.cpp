#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } //constructor

// these are the getters

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLenght() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const {	return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,5}, {5,5}, {6,5}, {7,10} };

	return WordLengthToMaxTries[MyHiddenWord.length()];
}


// this are the methods
void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) // if the guess isn't all lowercase
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

bool FBullCowGame::IsIsogram(FString Word) const
{
	// Treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // set up our map
	for (auto Letter : Word) // // loop trough all the letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) { // if the letter is in the map
			return false; // we do not have an isogran
		}
		else {
			LetterSeen[Letter] = true; // add the leter to the map as seen
		}
				
	}
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) // if not a lowercase letter
		return false;
	}
	return true;
}
