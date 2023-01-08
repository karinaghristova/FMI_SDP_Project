#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "skip_list.h"
#include "box_list.h"


//First task functions
void initializeCitiesInSkipList(SkipList<std::string>& sl) {
	sl.insertEnd("Sofia");
	sl.insertEnd("Pazardzhik");
	sl.insertEnd("Plovdiv");
	sl.insertEnd("Dimitrovgrad");
	sl.insertEnd("StaraZagora");
	sl.insertEnd("NovaZagora");
	sl.insertEnd("Yambol");
	sl.insertEnd("Karnobat");
	sl.insertEnd("Burgas");
}

void setExpresses(SkipList<std::string>& sl) {
	sl.setExpressToNode(sl.getNodeWithValue("Sofia"), sl.getNodeWithValue("Plovdiv"));
	sl.setExpressToNode(sl.getNodeWithValue("Plovdiv"), sl.getNodeWithValue("NovaZagora"));
	sl.setExpressToNode(sl.getNodeWithValue("Dimitrovgrad"), sl.getNodeWithValue("NovaZagora"));
	sl.setExpressToNode(sl.getNodeWithValue("StaraZagora"), sl.getNodeWithValue("Yambol"));
	sl.setExpressToNode(sl.getNodeWithValue("NovaZagora"), sl.getNodeWithValue("Burgas"));
}

void setExpressesSecondOption(SkipList<std::string>& sl) {
	sl.setExpressToNode(sl.getNodeWithValue("Sofia"), sl.getNodeWithValue("Dimitrovgrad"));
	sl.setExpressToNode(sl.getNodeWithValue("Pazardzhik"), sl.getNodeWithValue("Dimitrovgrad"));
	sl.setExpressToNode(sl.getNodeWithValue("Dimitrovgrad"), sl.getNodeWithValue("NovaZagora"));
	sl.setExpressToNode(sl.getNodeWithValue("StaraZagora"), sl.getNodeWithValue("Yambol"));
	sl.setExpressToNode(sl.getNodeWithValue("NovaZagora"), sl.getNodeWithValue("Burgas"));
}

void initiateCitiesThatMustBeVisited(LinkedList<std::string>& wantToVisit) {
	wantToVisit.insertEnd("Plovdiv");
	wantToVisit.insertEnd("StaraZagora");
	wantToVisit.insertEnd("Yambol");
}

void initiateCitiesThatMustBeVisitedSecondOption(LinkedList<std::string>& wantToVisit) {
	wantToVisit.insertEnd("Pazardzhik");
	wantToVisit.insertEnd("Dimitrovgrad");
	wantToVisit.insertEnd("Yambol");
}

void initiateCitiesThatMustBeVisitedThirdOption(LinkedList<std::string>& wantToVisit) {
	wantToVisit.insertEnd("Plovdiv");
	wantToVisit.insertEnd("StaraZagora");
	wantToVisit.insertEnd("Yambol");
}

void initiateCitiesThatMustBeVisitedFourthOption(LinkedList<std::string>& wantToVisit) {
	wantToVisit.insertEnd("Dimitrovgrad");
	wantToVisit.insertEnd("NovaZagora");
	wantToVisit.insertEnd("Karnobat");
}

void runFirstTask() {
	//1. Initiating the cities
	SkipList<std::string> sl = SkipList<std::string>();
	initializeCitiesInSkipList(sl);

	//2. Setting expresses
	setExpresses(sl);

	//3. Initiating a list of the cities we want to visit
	LinkedList<std::string> wantToVisit = LinkedList<std::string>();
	initiateCitiesThatMustBeVisited(wantToVisit);

	//4. Creating the route
	LinkedList<std::string> result = sl.createRoute(&wantToVisit);
	result.printList();
}

//Third task functions:

std::vector<std::string> splitLine(std::string line) {
	std::vector<std::string> words;

	// Declare a string to store the current word
	std::string word;

	// Split the input string by the comma character
	size_t pos = 0;
	while ((pos = line.find(' ')) != std::string::npos) {
		word = line.substr(0, pos);
		line.erase(0, pos + 1);
		words.push_back(word);
	}
	words.push_back(line);

	return words;
}

BoxList createBoxList(std::string fileName) {
	std::ifstream file(fileName);
	BoxList boxList = BoxList();

	if (file.is_open()) {
		std::string line;

		getline(file, line);
		int numberOfAllBoxes = std::stoi(line);

		for (size_t i = 0; i < numberOfAllBoxes; i++) {
			getline(file, line);
			std::vector<std::string> words = splitLine(line);
			int currentPos = 0;
			BoxNode currentBox = BoxNode(words[currentPos++]);
			boxList.insert(currentBox.name);

			int numberOfSouvenirs = std::stoi(words[currentPos++]);
			for (size_t i = 0; i < numberOfSouvenirs; i++) {
				std::string currentSouvenirName = words[currentPos++];
				boxList.addSouvenirsToBoxWithName(currentBox.name, currentSouvenirName);
			}

			int numberOfInnerBoxes = std::stoi(words[currentPos++]);
			for (size_t i = 0; i < numberOfInnerBoxes; i++) {
				std::string currentBoxName = words[currentPos++];
				boxList.insert(currentBoxName);
				BoxNode* currentInnerBox = boxList.getBoxWithName(currentBoxName);
				boxList.addInnerBoxToBoxWithName(currentBox.name, currentInnerBox);
			}

		}

		file.close();
	}
	else {
		// Print an error message if the file could not be opened
		std::cerr << "Error: Unable to open file." << std::endl;
	}

	return boxList;
}

void runThirdTask() {
	BoxList boxList = createBoxList("boxesInput.txt");
	std::cout << boxList.printList() << std::endl;
	std::cout << boxList.getNumberOfBoxes() << std::endl;
}

int main()
{
	//First task should read from the input
	std::cout << "First task:\n";
	runFirstTask();
	std::cout << "Third task:\n";
	runThirdTask();
	
	return 0;

}

//First express and first cities option expected output:
//Sofia, Plovdiv, Dimitrovgrad, StaraZagora, Yambol, Karnobat, Burgas,
//First express and second cities option expected output: 
//Sofia, Pazardzhik, Plovdiv, Dimitrovgrad, NovaZagora, Yambol, Karnobat, Burgas
//Second express option and third cities expected output: 
//Sofia, Pazardzhik, Plovdiv, Dimitrovgrad, StaraZagora, Yambol, Karnobat, Burgas
//Second express and fourth cities option expected output: 
//Sofia, Dimitrovgrad, NovaZagora, Yambol, Karnobat, Burgas
