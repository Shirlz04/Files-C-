#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string.h>
#include "hw2.h"
#include <vector>
using namespace std;





/*vector<creatures> test() {
	vector<creatures> vc;
	creatures c;
	c.length = 9;
	c.width = 10;
	c.name = "Snake";
	cout << c.name;
	vc.push_back(c);
	return vc;
}

int randomIntGenerator() {
	srand(time(NULL));
	int num = rand() % 10;
	cout << num;
	return num;
}
*/


int main() {
	Atlantis a1;
	cout << "WELCOME TO ATLANTIS!" << endl;
	//a1.printCreatureList();
	a1.collectCards();
	//a1.printCreatures();
	//a1.printCollectedCards();
	return 0;
}