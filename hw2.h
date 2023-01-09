#pragma once


#include <string>
#include <list>
#include <list>
#include <vector>
using namespace std;

#ifndef  ATLANTIS_H
#define ATLANTIS_H

class Atlantis {
	private:
		struct creatures {
			string name;
			int length;
			int width;
		};
		creatures creatureList[15];
		vector<creatures> collectedCards;
		list<string> collectedSayings;
		list<creatures> stackableCards;
		string creatureSayings[15];
	public:
		Atlantis();
		auto getCreatures();
		auto drawCard();
		string creatureSays();
		bool isStackable(creatures lhsCeat, creatures rhsCreat);
		list<creatures> collectCards();
		bool newCreature(creatures creat);
		void printCreatures();
		void printCreatureList();
		void printCollectedCards();
		bool stringComparison(string st1, string st2);
		void creaturePrinter(creatures creat);
		

};
#endif // ! ATLANTIS_H

 
