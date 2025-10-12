#include "LoadPgn.h"
#include "Node.cpp"

#define none -1
//TODO make a template
void LoadPgn::ParsePNGfile(Node<Move>* prime,const string& path, uint16_t primeTimeline, uint16_t numberOfnegativeT)
{
	static const string dividingElements = "(T)";

	//todo use string_view 

	fstream file; string line;

	file.open(path, std::ios::in);

	//TODO return error
	if (!file.is_open()) { cout << "error opening file!"; return; }

	Node<Move>* currentMove = prime;
	Node<Move>* toadd;

	//todo use string_view but i dont care about speed there
	while (std::getline(file, line)) {
		if (line.empty() || line[0] == '[') { continue; }

		cout << line << "\n";

		bool blacksmove = 0;
		size_t firstPart = none;

		toadd = new Node<Move>();

		for (size_t j = 0; j < line.size(); ++j) {
			if (line[j] == '/' && blacksmove == 0) {
				currentMove->WriteOrFollow(toadd);
				currentMove = toadd;

				toadd = new Node<Move>();
				blacksmove = 1;
			}

			else if (line[j] == '(' && firstPart == none) { firstPart = j; }

			else if (((line[j] == ' ') || (line[j] == '\n') || (j == line.size() - 1)) && firstPart != none) {

				ActionAndString<Move> turn(line.substr(firstPart, (j - firstPart)), primeTimeline, numberOfnegativeT, blacksmove);
				firstPart = none;
				toadd->data.push_back(turn);
			}
		}
		//currentMove->AddAndSetLast(toadd);
		//currentMove = toadd;
		currentMove->WriteOrFollow(toadd);
		currentMove = toadd;
	}
	file.close();
}

void LoadPgn::SetPosition(list<MoveSet>& listOfMoves, Game& multiverse)
{
	for (auto it = listOfMoves.begin(); it != listOfMoves.end(); ++it) {
		for (auto it2 = it->vectorOfTurns.begin(); it2 != it->vectorOfTurns.end(); ++it2) {
			Move temp = *it2;
			multiverse.MakeMove(temp);
		}
		multiverse.state.Move = !multiverse.state.Move;
	}

	// if state.Move doesnt affect on travel moves then uncomment this and delete 
	// multiverse.state.Move = !multiverse.state.Move;
	/*
	if (listOfMoves.size() % 2 == 1) {
		multiverse.state.Move = !multiverse.state.Move;
	}
	*/
}
