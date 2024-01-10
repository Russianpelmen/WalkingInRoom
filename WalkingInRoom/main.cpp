#include <iostream>
#include <conio.h>
#include <random>

const int Width = 19;
const int Height = 19;

const char HealRegen = '+';
const char Coin = '*';
const char Ship = '^';
const char wall = '#';

const char Player = 3; // '♥'
const char HealIcon = 219; // '█'

int Random(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(gen);
}

char map[Width][Height] = {
	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', '+', ' ', ' ', '^', ' ', ' ', ' ', ' ', ' ', '^', ' ', ' ', '+', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', '#', '#', '^', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '^', '#', '#', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', '^', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '^', '?', '^', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', '^', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', '#', '#', '^', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '^', '#', '#', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', '+', ' ', ' ', '^', ' ', ' ', ' ', ' ', ' ', '^', ' ', ' ', '+', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#' },
	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' }
};

int FullHeal = Random(15, 25);
int HealPublic = Random(5, FullHeal);

int BlendTimer = Random(5, 10);
int Blend = Random(5, 11);

int CoinCount = Random(0, 8);
int ShipCount = Random(1, 10);
int RegenCount = Random(1, 3);

int InventoryCoins = 0;

std::string HealBar = "";

int	Player_X = Random(1, 8);
int Player_Y = Random(1, 16);

namespace Game
{
	void ShipSpawn(int Count) {
		for (int i = 1; i <= Count; i++) {
			int ShipCoord_X = Random(1, Width);
			int ShipCoord_Y = Random(1, Height);

			if (map[ShipCoord_X][ShipCoord_Y] == ' ') { map[ShipCoord_X][ShipCoord_Y] = '^'; }
		}

	}

	void RegenSpawn(int Count) {
		for (int i = 1; i <= Count; i++) {
			int ShipCoord_X = Random(1, Width);
			int ShipCoord_Y = Random(1, Height);

			if (map[ShipCoord_X][ShipCoord_Y] == ' ') { map[ShipCoord_X][ShipCoord_Y] = '+'; }
		}

	}

	void CoinSpawn(int CoinCount)
	{
		for (int i = 1; i <= CoinCount; i++)
		{
			int CoinCoord_X = Random(1, Width);
			int CoinCoord_Y = Random(1, Height);

			if (map[CoinCoord_X][CoinCoord_Y] == ' ') { map[CoinCoord_X][CoinCoord_Y] = Coin; }
		}
	}

	void PrintHealBar(const int FullHeal, int Heal) {
		std::cout << "HealBar " << '[';

		for (int i = 1; i <= Heal; i++) { std::cout << HealIcon; }
		for (int i = 1; i <= FullHeal - Heal; i++) { std::cout << '.'; }

		std::cout << "] - " << Heal << '\\' << FullHeal << ' ';
		if (Heal < 5)
		{
			Blend--;
			if (Blend <= 1)
			{
				Blend = BlendTimer;
				HealPublic--;
			}
			std::cout << " - Blending " << Blend << '\\' << BlendTimer << "\n";

		}
	}
}

int main()
{
	Game::ShipSpawn(ShipCount);
	Game::CoinSpawn(CoinCount);
	Game::RegenSpawn(RegenCount);

	while (true) {

		if (HealPublic > FullHeal) HealPublic = FullHeal;

		if (map[Player_X][Player_Y] == ' ') map[Player_X][Player_Y] = Player;

		for (int Line = 0; Line <= Width; Line++) {
			for (int j = 0; j <= Height; j++) { 
				std::cout << map[Line][j];
			}
			std::cout << std::endl;
		}

		Game::PrintHealBar(FullHeal, HealPublic);

		std::cout << "\nPlayerCoord_X -\t" << Player_Y << " " << std::endl;
		std::cout << "PlayerCoord_Y -\t" << Player_X << "\n" << std::endl;

		char KeyChar = _getch();

		switch (KeyChar)
		{
		case 'w':
			map[Player_X][Player_Y] = ' ';
			Player_X--;

			if (map[Player_X][Player_Y] == Ship) { HealPublic--; ShipCount--; }
			else if (map[Player_X][Player_Y] == Coin) { CoinCount--; InventoryCoins++; }
			else if (map[Player_X][Player_Y] == HealRegen) { RegenCount--; HealPublic += Random(1, 2); }
			else if (map[Player_X][Player_Y] == wall) { map[Player_X++][Player_Y]; }

			map[Player_X][Player_Y] = ' ';
			break;
		case 's':
			map[Player_X][Player_Y] = ' ';
			Player_X++;

			if (map[Player_X][Player_Y] == Ship) { HealPublic--; ShipCount--;}
			else if (map[Player_X][Player_Y] == Coin) { CoinCount--; InventoryCoins++; }
			else if (map[Player_X][Player_Y] == HealRegen) { RegenCount--; HealPublic += Random(1, 2); }
			else if (map[Player_X][Player_Y] == wall) { map[Player_X--][Player_Y]; }

			map[Player_X][Player_Y] = ' ';
			break;
		case 'a':
			map[Player_X][Player_Y] = ' ';
			Player_Y--;

			if (map[Player_X][Player_Y] == Ship) { HealPublic--; ShipCount--; }
			else if (map[Player_X][Player_Y] == Coin) { CoinCount--; InventoryCoins++; }
			else if (map[Player_X][Player_Y] == HealRegen) { RegenCount--; HealPublic += Random(1, 2); }
			else if (map[Player_X][Player_Y] == wall) { map[Player_X][Player_Y++]; }

			map[Player_X][Player_Y] = ' ';
			break;
		case 'd':
			map[Player_X][Player_Y] = ' ';
			Player_Y++;

			if (map[Player_X][Player_Y] == Ship) { HealPublic--; ShipCount--; }
			else if (map[Player_X][Player_Y] == Coin) { CoinCount--; InventoryCoins++; }
			else if (map[Player_X][Player_Y] == HealRegen) { RegenCount--; HealPublic += Random(1, 2); }
			else if (map[Player_X][Player_Y] == wall) { map[Player_X][Player_Y--]; }

			map[Player_X][Player_Y] = ' ';
			break;
		default: break;
		}

		if (HealPublic <= 0) { break; }
		system("cls");
	}

	system("cls");
	std::cout << "GameOver\n" << std::endl;
	std::cout << "Coins - " << InventoryCoins << std::endl;
	_getch();

	return 0;
}