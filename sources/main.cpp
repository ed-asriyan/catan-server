#include <iostream>

#include "logic/game.hpp"
// #include "translate/translate.hpp"

int main(int argc, char const *argv[])
{
	Game game;

	game.addPlayer();
	game.addPlayer();
	game.addPlayer();
	game.addPlayer();

	// for (int i = 0; i < 10; ++i)
	// {
	// 	game.nextStep();
	// }

	game.show();

	char color_c;
	char type_c;
	Coordinates crd;

	while (true)
	{
		game.nextStep();

		cin >> color_c >> type_c >> crd.x >> crd.y;

		Color color;
		switch (color_c)
		{
			case 'O':
				color = ORANGE;
				break;
			case 'B':
				color = BLUE;
				break;
			case 'W':
				color = WHITE;
				break;
			case 'R':
				color = RED;
				break;
			default:
				color = NO_COLOR;
		}

		BuildingType type;
		switch (type_c)
		{
			case 'R':
				type = ROAD;
				break;
			case 'S':
				type = SETTLEMENT;
				break;
			case 'C':
				type = CITY;
				break;
			default:
				type = NO_BUILDING;
		}

		cout << color_c << " " << type_c << " {" << crd.x << ", " << crd.y << "}" << endl << endl;

		game.build(type, color, crd);

		game.show();
	}

	return 0;
}