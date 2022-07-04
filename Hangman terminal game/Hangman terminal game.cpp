#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <random>
#include <chrono>
#include <unordered_set>

using namespace std;

void drawBoard(string ans, vector<bool> letters, unordered_set<char> guessedLetters, int wrongGuesses) {
	switch (wrongGuesses) {
	case 1:
		cout << "   _____" << endl;
		cout << "  |     |" << endl;
		cout << "  |     0" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "===========" << endl;
		break;
	case 2:
		cout << "   _____" << endl;
		cout << "  |     |" << endl;
		cout << "  |     0" << endl;
		cout << "  |     |" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "===========" << endl;
		break;
	case 3:
		cout << "   _____" << endl;
		cout << "  |     |" << endl;
		cout << "  |     0" << endl;
		cout << "  |    \\|" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "===========" << endl;
		break;
	case 4:
		cout << "   _____" << endl;
		cout << "  |     |" << endl;
		cout << "  |     0" << endl;
		cout << "  |    \\|/" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "===========" << endl;
		break;
	case 5:
		cout << "   _____" << endl;
		cout << "  |     |" << endl;
		cout << "  |     0" << endl;
		cout << "  |    \\|/" << endl;
		cout << "  |     |" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "===========" << endl;
		break;
	case 6:
		cout << "   _____" << endl;
		cout << "  |     |" << endl;
		cout << "  |     0" << endl;
		cout << "  |    \\|/" << endl;
		cout << "  |     |" << endl;
		cout << "  |    /" << endl;
		cout << "  |" << endl;
		cout << "===========" << endl;
		break;
	case 7:
		cout << "   _____" << endl;
		cout << "  |     |" << endl;
		cout << "  |     0" << endl;
		cout << "  |    \\|/" << endl;
		cout << "  |     |" << endl;
		cout << "  |    / \\" << endl;
		cout << "  |" << endl;
		cout << "===========" << endl;
		break;
	default:
		cout << "   _____" << endl;
		cout << "  |     |" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "  |" << endl;
		cout << "===========" << endl;
		break;
	}
	for (int i = 0; i < letters.size(); i++) {
		if (letters[i] == false) {
			cout << "_ ";
		}
		else {
			cout << ans[i] << " ";
		}
	}

	cout << endl;

	cout << "Guessed Letters: ";
	for (auto j : guessedLetters) {
		cout << j << ", ";
	}
	cout << endl;
}

bool guessLetter(vector<bool> &letters, unordered_set<char> &guessedLetters, string ans) {
	char guess;
	bool correct = false;
	cout << "Guess a letter: ";
	cin >> guess;
	if (guessedLetters.find(guess) == guessedLetters.end())
		guessedLetters.insert(guess);

	for (int i = 0; i < ans.size(); i++) {
		if (ans[i] == guess) {
			letters[i] = true;
			correct = true;
		}
	}
	return correct;
}

bool guessWord(vector<bool>& letters, string ans) {
	string guess;
	bool correct = false;
	cout << "Guess a word: ";
	cin >> guess;
	if (ans == guess) {
		correct = true;
	}

	if (correct) {
		cout << "YOU WIN!" << endl;
		exit(0);
	}
	return correct;
}

void game(string ans) {
	bool done = false;
	bool lose = false;
	bool guess = false;
	vector<bool> letters(ans.size(), false);
	unordered_set<char> guessedLetters;
	int input;
	int wrongGuesses = 0;

	while (!done || !lose) {
		drawBoard(ans, letters, guessedLetters, wrongGuesses);
		cout << "Would you like to guess a letter (type 1), or the whole word (type 2)?" << endl;
		cin >> input;
		
		switch (input) {
		case 1:
			guess = guessLetter(letters, guessedLetters, ans);
			if (guess) {
				system("CLS");
				cout << "Correct!" << endl;
			}
			else {
				system("CLS");
				cout << "Nice try! But sadly wrong. Try again!" << endl;
				wrongGuesses++;
			}
			break;
		case 2:
			guess = guessWord(letters, ans);
			if (guess) {
				system("CLS");
				cout << "Correct!" << endl;
			}
			else {
				system("CLS");
				cout << "Nice try! But sadly wrong. Try again!" << endl;
				wrongGuesses++;
			}
			break;
		default:
			cout << "Im gonna assume you meant to type 1" << endl;
			guess = guessLetter(letters, guessedLetters, ans);
			if (guess) {
				system("CLS");
				cout << "Correct!" << endl;
			}
			else {
				system("CLS");
				cout << "Nice try! But sadly wrong. Try again!" << endl;
				wrongGuesses++;
			}
			break;
		}
		if (wrongGuesses > 6) {
			drawBoard(ans, letters, guessedLetters, wrongGuesses);
			cout << "YOU LOOSE" << endl;
			cout << "THE ANSWER WAS " << ans << endl;
			lose = true;
			exit(0);
		}
	}
	cout << "done" << endl;
}

// create a function called getWords to parse a text file and return a vector of strings
string getWord() {
	vector<string> words;
	string word;
	ifstream file("words_alpha.txt");
	while (file >> word) {
		words.push_back(word);
	}
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	string newWord = words[uniform_int_distribution<int>(0, words.size())(rng)];

	return newWord;
}

void startGame() {

	cout << "WELCOME TO MY HANGMAN GAME!" << endl;

	cout << "Ready to start? (y to start, n to quit)" << endl;
	string input;
	cin >> input;

	if (input[0] == 'n') {
		exit(0);
	}
	else if (input[0] != 'y') {
		cout << "Close enough!" << endl;
	}

	string word = getWord();

	game(word);
	
}

int main()
{	
    startGame();

	return 0;
}