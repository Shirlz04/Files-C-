#include <iostream>
#include <string.h>
#include <vector>
#include <ctime>
#include "hw2.h"
#include <fstream>
using namespace std;

int power(int);
int randomIntGenerator();


int power(int num) {
	if (num == 0) {
		return 1;
	}
	else {
		return 10 * power(num - 1);
	}
}

/* This is the construct for the Atlantis class. 
Both the creatures file and the saying files are loaded in this constructor
and */
Atlantis::Atlantis()  {
	char temp[50];
	//list<string> creatureSayings;
	vector<creatures> collectedCards;
	for (int i = 0; i < 15; i++) {
		creatures c;
		c.name = "";
		c.length = 0;
		c.width = 0;
		creatureList[i]  = c;
	}
	ifstream fin;
	ifstream fin2;
	string input;
	bool nameFinder = false;
	bool lengthFinder = false;
	bool widthFinder = false; 
	int count = 0;
	int creatureListCounter = 0;
	fin.open("creatures.txt");
	while (getline(fin, input)) {
		input.copy(temp, input.size(), 0);
		temp[input.size()] = '\0';
		char tempName[20];
		int spaceCounter = 0;
		string nameHolder = "";
		//if (nameFinder == false) {
		for (int i = 0; ; i++) {
			if (temp[i] != ' ' && spaceCounter < 2 && temp[i] != '\t') {
				count++;
				nameHolder += temp[i];
			}
			else {
				spaceCounter++;
				if (spaceCounter == 1) {
					nameHolder += " ";
					continue;
				}
				//cout << nameHolder << endl;
				creatureList[creatureListCounter].name = nameHolder;
				break;
				//input.copy(tempName, count, 0);
				//nameFinder = true;
			}
		}
		//}
		//if (lengthFinder == false) {
		char num[4];
		int numCount = 0;
		int integerValue = 0;
		count += 3;
		for (int i = count; ; i++) {
			//cout << temp[i];
			if (temp[i] != 'x' && temp[i] != ' ') {
				count++;
				num[numCount++] = temp[i];
				//cout << num[--numCount] << endl;
			}
			else {
				for (int j = 0; j < numCount; j++) {
					//cout << num[j] << endl;
					integerValue += (((int)num[j] - 48) * power(numCount - 1 - j));
				}
				//cout << integerValue << endl;
				creatureList[creatureListCounter].length = integerValue;
				break;
				//input.copy(tempName, count, i);
				//lengthFinder = true;
			}
		}
		//char num[4];
		count +=3;
		numCount = 0;
		//cout << temp[count];
		integerValue = 0;
		for (int i = count; ; i++) {
			if (temp[i] != '\0') {
				count++;
				num[numCount++] = temp[i];
			}
			else {
				for (int j = 0; j < numCount; j++) {
					integerValue += (((int)num[j] - 48) * power(numCount - 1 - j));
				}
				//cout << integerValue << endl;
				creatureList[creatureListCounter].width = integerValue;
				break;
				//input.copy(tempName, count, i);
				//lengthFinder = true;
			}
		}
		creatureListCounter++;
		count = 0;
		nameFinder = false;
		lengthFinder = false;
		widthFinder = false;
		//cout << input << endl;
	}
	fin.close();
	fin2.open("sayings.txt");
	count = 0;
	while (getline(fin2, input)) {
		creatureSayings[count++] = input;
		//cout << creatureSayings[--count]<< endl;
	}
	fin2.close();
}

/* The randomIntGenerator() is used randomly generate an ineteger between 0-14 
because there are 14 creatures and 14 sayings. */
int randomIntGenerator() {
	srand(time(NULL));
	int num = rand() % 14;
	//cout << num;
	return num;
}

/* The drawCard() function uses the randomIntGenerator function to randomly
select a creature from an array of creatures. */
auto Atlantis::drawCard() {
	return creatureList[randomIntGenerator()];
}

/* The creatureSays() function uses the randomIntGenerator function to randomly
select a saying from an array of sayings for the creatures. */
string Atlantis::creatureSays() {
	return creatureSayings[randomIntGenerator()];
}

/* The isStackable() function takes 2 creatures and termine if they can be 
stacked with each other in any orienation regardless of who is on the top
or bottom. */
bool Atlantis::isStackable(creatures lhsCreat, creatures rhsCreat) {
	//cout << lhsCreat.name << endl;
	//cout << rhsCreat.name << endl;
	if (rhsCreat.length > lhsCreat.length && lhsCreat.width <= rhsCreat.width) {
		return true;
	} else if (rhsCreat.width > lhsCreat.width && lhsCreat.length <= rhsCreat.length) {
		return true;
	} else if (lhsCreat.length > rhsCreat.length && rhsCreat.width <= lhsCreat.width) {
		return true;
	}
	else if (lhsCreat.width > rhsCreat.width && rhsCreat.length <= lhsCreat.length) {
		return true;
	}
	return false;
}

/* The collectCards() function is the function that all the creaturs cards
are drawn and collected and the user will be prompted to press enter to draw
a card until either exit clause is triggered of collect 14 different creature
cards or 6 stackable creature cards. */
list<Atlantis::creatures> Atlantis::collectCards() {
	bool findAll = false;
	
	do{
		cout << "Press Enter to draw a new card " << endl;
		cin.get();
		creatures tempCreat = drawCard();
		string tempCreatSay = creatureSays();
		cout << "The card you drew is: " << endl;
		creaturePrinter(tempCreat);
		cout << "Creature said: " << tempCreatSay << endl;
		if (collectedCards.empty()) {
			collectedCards.push_back(tempCreat);
			stackableCards.push_back(tempCreat);
			collectedSayings.push_back(tempCreatSay);
		}
		else {
			//cout << "her" << endl;
			if (newCreature(tempCreat)) {
				//cout << "new" << endl;
				collectedCards.push_back(tempCreat);
				collectedSayings.push_back(tempCreatSay);
			}
			
			for (auto& vc : stackableCards) {
				
				if (isStackable(vc, tempCreat)) {
					//cout << "stackable" << endl;
					stackableCards.push_back(tempCreat);
					collectedSayings.push_back(tempCreatSay);
					//cout << "stackable completed" << endl;
				}
			}
			if (collectedCards.size() == 14) {
				cout << "Krusty collected 14 cards from different creatures";
				cout << " and they are as follows:" << endl;
				printCollectedCards();
				break;
			}
			else if (stackableCards.size() == 6) {
				cout << "Krusty collected 6 stackable cards";
				cout << " and they are as follows:" << endl;
				printCreatures();
				break;
			}
		}
		//cout << "trip completed" << endl;
	} while (1);
	return stackableCards;
}

/* The stringComparison() function takes 2 strings and compares them to see if
the content of each string is the same by converting both into an array of 
characters and comparing them individually. */
bool Atlantis::stringComparison(string st1, string st2) {
	char tempChar1[80];
	char tempChar2[80];
	//cout << st1.size() << endl;
	//cout << st2.size() << endl;
	st1.copy(tempChar1, st1.size(), 0);
	st2.copy(tempChar2, st2.size(), 0);
	if (st1.size() != st2.size()) {
		return false;
	}
	else {
		for (int i = 0; i < st1.size(); i++) {
			if (tempChar1[i] != tempChar2[i]) {
				return false;
			}
		}
	}
	return true;
}

/* The newCrature() function checks to see if the creature that is passed to
it is already drawn by searching through the variable collectedCards which is
a vectore of creatures cards that are already drawn. */
bool Atlantis::newCreature(creatures creat) {
	//cout << creat.name << endl;
	for (auto& vc : collectedCards) {
		if (stringComparison(vc.name, creat.name)) {
			return false;
		}
	}
	return true;
}

/* The getCreatures() function returns the array of creature list. */
auto Atlantis::getCreatures() {
	return creatureList;
}

/* The creaturePrinter() function prints a single creature that is passed to it.*/
void Atlantis::creaturePrinter(creatures creat) {
	cout << creat.name << " dimensions: ";
	cout << creat.length << " x ";
	cout << creat.width << endl;
}

/* The printCreatures() function prints out all the cards that are stacked 
together. */
void Atlantis::printCreatures() {
	for (auto& vc: stackableCards) {
		cout << vc.name << " dimensions: ";
		cout << vc.length << " x "; 
		cout << vc.width << endl;
	}
}

/* The printCollectedCards() prints out all the cards that were collected by
the user. */
void Atlantis::printCollectedCards() {
	for (auto& vc : collectedCards) {
		cout << vc.name << " dimensions: ";
		cout << vc.length << " x ";
		cout << vc.width << endl;
	}
}

/* The printCreatureList() prints out all creatures that has been loaded in
the creaturelist array. */
void Atlantis::printCreatureList() {
	for (int i = 0; i < 14; i++) {
		cout << creatureList[i].name << " dimensions: ";
		cout << creatureList[i].length << " x ";
		cout << creatureList[i].width << endl;
	}
}
