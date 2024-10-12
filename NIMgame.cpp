#include "NIMgame.h"

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>

using namespace std;

enum STATUS { OUT_OF_BOUNDS = -1, SUCCESS, EMPTY, TOO_MANY_ITEMS_TAKEN, ZERO_ITEMS_TAKEN };
enum GAMEMODE { PVP = 1, PVC, CVC };

Game::Game() {
	srand(time(NULL));
	init(gamemode());
	generate();
	start();
}

int Game::take(int bunchNum, int items) {
	if (bunchNum < 0 || bunchNum >= numberOfBunches) return OUT_OF_BOUNDS;
	if (bunches[bunchNum] < 1) return EMPTY;
	if (bunches[bunchNum] < items) return TOO_MANY_ITEMS_TAKEN;
	if (items < 1) return ZERO_ITEMS_TAKEN;
	else {
		bunches[bunchNum] -= items;
		if (bunches[bunchNum] == 0)
			notEmpty_iterator--;
		return SUCCESS;
	}
}

void Game::show() {
	system("cls");
	cout << "There's next items in bunches:\n";
	for (int i = 0; i < numberOfBunches; i++) {
		if (bunches[i] > 0)
			printf("Bunch #%d: %d items\n", i, bunches[i]);
	}
	cout << endl;
}

void Game::generate() {
	cout << "Insert count of bunches: ";
	cin >> numberOfBunches;
	bunches = new int[numberOfBunches];
	for (int i = 0; i < numberOfBunches; i++)
		bunches[i] = rand() % (max - min + 1) + min;
	notEmpty_iterator = numberOfBunches;
}

int Game::gamemode() {
	system("cls");
	cout << "[[[THE NIM GAME]]]   --->   Igromania: 8/10 | StopGame: 9/10 | PC Gamer: 8/10 \n\n";
	cout << "Choose gamemode:\n1) Player vs Player\n2) Player vs Computer\n3) Computer vs Computer\n";
	while (1)
		switch (_getch() - '0') {
		case PVP: return PVP;
		case PVC: return PVC;
		case CVC: return CVC;
		default: break;
		}
}

void Game::init(int gm) {
	switch (gm) {
	case PVP:
		Players[0] = new Human("Player 1");
		Players[1] = new Human("Player 2");
		return;
	case PVC:
		Players[0] = new Human("Player");
		Players[1] = new Computer("Computer");
		return;
	case CVC:
		Players[0] = new Computer("Computer 1");
		Players[1] = new Computer("Computer 2");
		return;
	}
}

void Game::start() {
	Player* currentPlayer = Players[0];
	pair pair;
	while (notEmpty_iterator) {
		currentPlayer = Players[step % 2];
		show();
		//cout << currentPlayer->name << ", insert number of bunch and count of items: ";
		pair = currentPlayer->move(bunches, numberOfBunches);
		if (take(pair.bunch, pair.items) == SUCCESS) {
			step++;
		}
		else {
			cout << "Wrong move, try again";
			Sleep(2000);
		}
	}
	cout << currentPlayer->name << " wins!\n";
}

Game::Human::Human(const char* name) {
	this->name = name;
}
Game::pair Game::Human::move(int* array, int size) {
	int bunch, items;
	cout << name << ", insert number of bunch and count of items: ";
	cin >> bunch >> items;
	return { bunch, items };
}

Game::Computer::Computer(const char* name) {
	this->name = name;
}
Game::pair Game::Computer::move(int* array, int size) {
	cout << name << ", insert number of bunch and count of items: ";
	for (int i = 0; i < size; i++) {
		if (array[i] > 0) {
			for (int j = array[i]; j > 0; j--) {
				int xorSum = array[0];
				for (int k = 1; k < size; k++)
					xorSum = xorSum ^ (k != i ? array[k] : array[k] - j);
				if (!xorSum) {
					Sleep(1000);
					cout << i << " " << j << endl;
					Sleep(2000);
					return { i,j };
				}
			}
		}
	}
	for (int i = 0; i < size; i++) {
		if (array[i] > 0) {
			int j = rand() % array[i] + 1;
			Sleep(1000);
			cout << i << " " << j << endl;
			Sleep(2000);
			return { i,j };
		}
	}
}