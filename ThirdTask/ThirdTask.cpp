#include <iostream>
#include <vector>
#include <fstream>
#include "box_list.h"

//Third task functions:
std::vector<std::string> splitLine(std::string line) {
	std::vector<std::string> words;
	std::string word;

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
		std::cerr << "Coul not open the file." << std::endl;
	}

	return boxList;
}

void runThirdTask(std::string fileName) {
	BoxList boxList = createBoxList(fileName);
	std::cout << "Initial boxes count: " << boxList.getNumberOfBoxes() << std::endl;
	std::cout << boxList.printList() << std::endl;

	std::cout << "------Optimizing boxes------\n" << std::endl;

	boxList.removeAllUnneccessaryBoxes();
	std::cout << "Boxes count after optimization: " << boxList.getNumberOfBoxes() << std::endl;
	std::cout << boxList.printList() << std::endl;
}


int main()
{
	runThirdTask("boxesInput.txt");
	return 0;
}

