#include <iostream>
#include <cstdlib>

using namespace std;

/*
Requirements:
	-Ask For How Many Rounds The Game Will Be .
	-Start Each round Player VS Computer .
	-Show The Results With Each Round .
	-If Computer Wins The Round Ring a Bill , and Screen Red "4F" .
	-If Player Won The Round Show Green Screen "2F" .
	-After All Rounds Show Game Over The Print Game Results ..
	 Then Ask The User If s/he Want To Play Again ?
*/
	 
	


enum enGame_Choice{ stone = 1 , paper = 2 , scissor = 3 };
enum enWinner { Player = 1, computer = 2, Draw = 3 };


struct stRoundInfo {
	short RoundNumber = 0;
	enGame_Choice Player_One_Choice;
	enGame_Choice Computer_Choice;
	enWinner winner;
	string WinnerName;
	 
};

struct stGameResults {
	short GameRounds = 0;
	short Player_WinTimes = 0;
	short Computer_WinTimes = 0;
	short DrawTime = 0;
	enWinner GameWinner;
	string WinnerName = "";
};

int RandomeNamber(int From,int To) {
	int Number = 0;
	Number = rand() % (To - From + 1) + From;
	return Number;
}
enWinner WhoWonTheGame(short PlayerWinTimes,short Computerwintimes) 
{
	if (PlayerWinTimes > Computerwintimes)
		return enWinner::Player;
	else if (Computerwintimes > PlayerWinTimes)
		return enWinner::computer;
	else
		return enWinner::Draw;
}
string WinnerName(enWinner Winner) {
	string arrWinnerName[3] = { "Player","Computer","No Winner" };
	return arrWinnerName[Winner - 1];
}
stGameResults FillGameResults(int GameRounds, short PlayerWinTime, short ComputerWinTimes, short DrawTimes) {
	stGameResults GameResults;
	GameResults.GameRounds = GameRounds;
	GameResults.Player_WinTimes = PlayerWinTime;
	GameResults.Computer_WinTimes = ComputerWinTimes;
	GameResults.DrawTime = DrawTimes;
	GameResults.GameWinner = WhoWonTheGame(PlayerWinTime, ComputerWinTimes)
		; GameResults.WinnerName = WinnerName(GameResults.GameWinner);
	return GameResults;
}



enWinner WhoWonTheRound(stRoundInfo RoundInfo) {
	if (RoundInfo.Player_One_Choice == RoundInfo.Computer_Choice) {
		return enWinner::Draw;
	}
	switch (RoundInfo.Player_One_Choice) {

	case enGame_Choice::stone:
		if (RoundInfo.Computer_Choice == enGame_Choice::paper) {
			return enWinner::computer;
			}

		break;

	case enGame_Choice::paper:
		if (RoundInfo.Computer_Choice == enGame_Choice::scissor) {
			return enWinner::computer;
		}

		break;

	case enGame_Choice::scissor:
		if (RoundInfo.Computer_Choice == enGame_Choice::stone) {
			return enWinner::computer;
		}

		break;

	}
	return enWinner::Player;
		
}
string ChoiceName(enGame_Choice choice) {
	string arrGameChoice[3] = { "stone","Paper","Scissors" };
	return arrGameChoice[choice - 1];
}
void SetWinnerScreenColor(enWinner Winner) {
	switch (Winner) {
	case enWinner::Player:

			system("color 2F");//Green
			break;

	case enWinner::computer:

		    system("color 4F");//Red

			cout << "\a";

			break;
    default:
		    system("color 6F");//Yellow

			break;

	}
}



enGame_Choice ReadPlayer_oneChoice() {

	short Choice = 1;

	do {
		cout<<"\n Your Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";

		cin >> Choice;

	} while (Choice < 1 || Choice > 3);

	return enGame_Choice(Choice);

}


enGame_Choice GetComputerChoice() {

		return (enGame_Choice)RandomeNamber(1, 3);
}
void Print_Round_Results(stRoundInfo Roundinfo) {
	cout << "\n__________Round [" << Roundinfo.RoundNumber<<"]______________\n\n";

	cout << "Player Choice  : " << ChoiceName(Roundinfo.Player_One_Choice) << endl;

	cout << "Computer Choice:" << ChoiceName(Roundinfo.Computer_Choice) << endl;

	cout << "Round Winner   :["<< Roundinfo.WinnerName<<"]\n";
	cout << "______________________________________\n" << endl;
	SetWinnerScreenColor(Roundinfo.winner);
	
}


short ReadHowManyRounds() {
	short Game_Rounds = 1 ;
	do {
		printf("How Many Rounds %d to %d ?\n", 1, 10);
		cin >> Game_Rounds;
	} while (Game_Rounds < 1 || Game_Rounds > 10);
	return Game_Rounds;
}

stGameResults PlayrRoundes(short HowManyRounds) {

	stRoundInfo RoundInfo;
	short PlayerWinTime = 0, ComputerWinTime = 0, DrawTime = 0;
	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++) {
		cout<<"\nRound ["<<GameRound<<"]Begins: \n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player_One_Choice = ReadPlayer_oneChoice();
		RoundInfo.Computer_Choice = GetComputerChoice();
		RoundInfo.winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName =WinnerName( RoundInfo.winner);

		//counters
		if (RoundInfo.winner == enWinner::Player)
			PlayerWinTime++;
		else if (RoundInfo.winner == enWinner::computer)
			ComputerWinTime++;
		else
			DrawTime++;
		Print_Round_Results(RoundInfo);
	
   }
	return FillGameResults(HowManyRounds,PlayerWinTime,ComputerWinTime,DrawTime);
}
string Tabs(short NumberOfTabs) {
	string t = "";
	for (short i = 1; i < NumberOfTabs; i++) {
		t = t + "\t";
		cout << t;
	}
	return t;
}

void ShowGameOverScreen() {
cout<<Tabs(2)<<"________________________________________________________________________\n\n";
cout<<Tabs(2)<<"                         +++ G a m e  O v e r  +++                      \n";
cout <<Tabs(2)<<"________________________________________________________________________\n\n";
}
void ShowFinakGameResults(stGameResults GameResults) {
	cout << Tabs(2) << "_________________[ Game Results ]___________________\n\n";
	cout << Tabs(2) << "Game Rounds         : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player won Times    : " << GameResults.Player_WinTimes << endl;
	cout << Tabs(2) << "Computer won Times  : " << GameResults.Computer_WinTimes << endl;
	cout << Tabs(2) << "Draw Times          : " << GameResults.DrawTime << endl;
	cout << Tabs(2) << "Final Winner        : " << GameResults.WinnerName << endl;
	cout << Tabs(2) << "____________________________________________________\n\n";
	SetWinnerScreenColor(GameResults.GameWinner);
}

void ResetScreen() {
	system("cls");
	system("color 0F");
}
void Start_Game() {
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		stGameResults GameResults = PlayrRoundes(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinakGameResults(GameResults);

		cout<<"\n  Do You Want To Play Again? Y/N?",Tabs(3);
		cin >> PlayAgain;
	} while ( PlayAgain == 'y' || PlayAgain == 'Y' );
}



int main() {

	srand((unsigned)time(NULL));
	Start_Game();

	return 0;
}
