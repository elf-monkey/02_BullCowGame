#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// all values initializsed to cero, this is the declaration and inisialization of a type or class
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus // it's a value list, 
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Lenght,
	Not_Lowercase
	};

class FBullCowGame {

public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLenght() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; //TODO make richer

	void Reset();
	
	// provide a method for counting bulls and cows and increasing try # assuming valid guess
	// writting the signature? for our method
	// SubmitGuess is the name of the method and asking a BullCowCount from it
	FBullCowCount SubmitValidGuess(FString);

	// initialize properties o variables
private:
	// see contructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};
