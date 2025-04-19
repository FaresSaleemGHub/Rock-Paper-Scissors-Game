#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
using namespace std;

enum enChoices { Stone = 1, Paper = 2, Scissor = 3 };
enum enPlayers { PC = 1, User = 2, NoOne = 3 };

struct stGameResults {
	short GameRounds = 0;
	short PlayerWonTimes = 0;
	short PCWonTimes = 0;
	short DrawTimes = 0;
	enPlayers Winner = enPlayers::PC;
};

void TimerSleep(int NumSec) {
	std::this_thread::sleep_for(std::chrono::seconds(NumSec));
}
short RandomNumber(int From, int To) {
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}
int ReadNumRounds() {
	short NumRounds = 0;
	cout << "How many rounds you want to play?\n";
	cin >> NumRounds;
	return NumRounds;
}
string NameOfChoice(enChoices Choice) {
	string arrChoiceName[3] = { "Stone", "Paper", "Scissor" };
	return arrChoiceName[Choice - 1];
}
string NameOfPlayer(enPlayers Player) {
	string arrPlayerName[3] = { "PC", "User", "No One" };
	return arrPlayerName[Player - 1];
}
void ResultScreenEffects(enPlayers Winner) {
	switch (Winner)
	{
	case PC:
		//cout << "\a";
		system("color 4F");//Red
		break;
	case User:
		system("color 2F");//Green
		break;
	default:
		system("color 7C");//Gray
		break;
	}
}
enPlayers WhosTheWinnerOfRound(enChoices enUserChoose, enChoices enPcChoose) {
	if (enPcChoose == enUserChoose)
		return enPlayers::NoOne;
	switch (enUserChoose)
	{
	case Stone:
		if (enPcChoose == enChoices::Scissor)
			return enPlayers::User;
	case Paper:
		if (enPcChoose == enChoices::Stone)
			return enPlayers::User;
	case Scissor:
		if (enPcChoose == enChoices::Paper)
			return enPlayers::User;
	default:
		return enPlayers::PC;
	}
}
void PrintDividingLine() {
	for (int i = 0; i <= 50; i++) {
		cout << "_";
	}
}
enPlayers FinalWinner(stGameResults GameResults) {
	if (GameResults.PCWonTimes > GameResults.PlayerWonTimes) {
		return enPlayers::PC;
	}
	else if (GameResults.PlayerWonTimes > GameResults.PCWonTimes) {
		return enPlayers::User;
	}
	else
		return enPlayers::NoOne;
}
string  Tabs(short NumberOfTabs) {
	string t = "";
	for (int i = 1; i < NumberOfTabs; i++) {
		t = t + "\t";
	}
	return t;
}
void ShowGameOverScreen() {
	cout << Tabs(4) << "__________________________________________________________\n\n";
	cout << Tabs(4) << "                 +++ G a m e  O v e r +++\n";
	cout << Tabs(4) << "__________________________________________________________\n\n";
}
void WaitingFinalResultColorScreen() {
	TimerSleep(1);
	for (int i = 0; i < 55; i++) {
		ResultScreenEffects((enPlayers)(i % 3));
	}
	TimerSleep(1);
}
void ShowFinalResults(stGameResults GameResult) {
	enPlayers Winner;
	Winner = FinalWinner(GameResult);
	ShowGameOverScreen();
	WaitingFinalResultColorScreen();
	ResultScreenEffects(Winner);
	cout << endl << endl;
	cout << Tabs(4) << "______________________ [Game Results ]_____________________\n\n";
	cout << Tabs(4) << "Game Rounds        : " << GameResult.GameRounds << endl;
	cout << Tabs(4) << "Player1 won times  : " << GameResult.PlayerWonTimes << endl;
	cout << Tabs(4) << "Computer won times : " << GameResult.PCWonTimes << endl;
	cout << Tabs(4) << "Draw times         : " << GameResult.DrawTimes << endl;
	cout << Tabs(4) << "Final Winner       : " << NameOfPlayer(Winner) << endl;
	cout << Tabs(4) << "____________________________________________________________\n";
	cout << endl;
	PrintDividingLine();
}
void ShowRounds(int NumRounds, stGameResults& GameResults) {
	short UserChoose, PcChoose;
	enPlayers WinnerOfRound;
	GameResults.GameRounds = NumRounds;

	for (int i = 1; i <= NumRounds; i++) {
		cout << "\nRound[" << (i) << "] begins:\n";
		cout << "Your choice: [1]:Stone, [2]:Paper, [3]:Scissor. ? ";
		cin >> UserChoose;
		PcChoose = RandomNumber(1, 3);

		cout << "\n__________Round[" << i << "]__________\n";
		cout << "Player1 Choice: " << NameOfChoice((enChoices)UserChoose) << endl;
		cout << "Pc Choice: " << NameOfChoice((enChoices)PcChoose) << endl;
		WinnerOfRound = WhosTheWinnerOfRound((enChoices)UserChoose, (enChoices)PcChoose);
		cout << "Round Winner: " << NameOfPlayer(WinnerOfRound) << endl;

		switch (WinnerOfRound)
		{
		case PC:
			GameResults.PCWonTimes++;
			break;
		case User:
			GameResults.PlayerWonTimes++;
			break;
		case NoOne:
			GameResults.DrawTimes++;
			break;
		}
		ResultScreenEffects(WinnerOfRound);
		PrintDividingLine();
		cout << endl;
	}
}
void PlayAgain(char& PlayAgainType) {
	cout << endl << "Do you want to play Aagain? Y/N? ";
	cin >> PlayAgainType;
}
void ResetScreen() {
	system("cls");
	system("color 0F");
}
void StartGame() {
	char PlayAgainType = 'Y';
	do {
		ResetScreen();
		stGameResults GameResults;
		ShowRounds(ReadNumRounds(), GameResults);
		ShowFinalResults(GameResults);
		PlayAgain(PlayAgainType);
	} while (PlayAgainType == 'Y' || PlayAgainType == 'y');
}
int main()
{
	StartGame();
}