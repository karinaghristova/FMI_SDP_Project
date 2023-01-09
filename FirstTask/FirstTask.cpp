#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "skip_list.h"

void setExpresses(SkipList<std::string>& sl, std::string first, std::string second) {
	sl.setExpressToNode(sl.getNodeWithValue(first), sl.getNodeWithValue(second));
}

void initiateCitiesThatMustBeVisited(LinkedList<std::string>& wantToVisit, std::vector<std::string> cities) {
	size_t numberOfCities = cities.size();
	for (size_t i = 0; i < numberOfCities; i++)
		wantToVisit.insertEnd(cities[i]);
}

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

void runFirstTask() {
	//1. Initiating the cities
	SkipList<std::string> sl = SkipList<std::string>();
	std::cout << "Enter number of cities: ";
	int numberOfCities = 0;
	std::cin >> numberOfCities;
	std::cout << "Please enter the names of " << numberOfCities << " cities separated by whitespaces in one line.\n";
	std::cout << "------------------------------------------------------\n";
	std::string city;
	for (size_t i = 0; i < numberOfCities; i++) {
		std::cin >> city;
		sl.insertEnd(city);
	}

	std::cout << "------------------------------------------------------\n";
	//std::cout << "All train stations:\n";
	//sl.printList();
	//std::cout << "------------------------------------------------------\n";

	//2. Setting expresses
	std::cout << "Please enter information about all express trains in the following format: {Start point city} {End point city}\n";
	std::cout << "When you are done please write \'EXIT\'\n";
	std::cout << "------------------------------------------------------\n";

	std::string firstCity, secondCity;
	while (true) {
		std::cin >> firstCity;
		std::string firstCityLowercase = firstCity;
		std::transform(firstCityLowercase.begin(), firstCityLowercase.end(),
			firstCityLowercase.begin(), ::tolower);
		if (firstCityLowercase == "exit")
			break;
		std::cin >> secondCity;
		setExpresses(sl, firstCity, secondCity);
	}
	std::cout << "------------------------------------------------------\n";
	//std::cout << "Express train stations only:\n";
	//sl.printWithExpressOnly();
	//std::cout << "------------------------------------------------------\n";

	//3. Initiating a list of the cities we want to visit
	LinkedList<std::string> wantToVisit = LinkedList<std::string>();
	std::cout << "Please enter the names of the cities you want to visit separated by whitespaces.\n";
	std::cout << "------------------------------------------------------\n";
	std::vector<std::string> citiesToBeVisited;
	std::string line;
	std::cin.ignore();
	std::getline(std::cin, line);
	citiesToBeVisited = splitLine(line);
	initiateCitiesThatMustBeVisited(wantToVisit, citiesToBeVisited);
	std::cout << "------------------------------------------------------\n";
	//std::cout << "List of the cities you want to visit:\n";
	//wantToVisit.printList();
	//std::cout << "------------------------------------------------------\n";

	//4. Creating the route
	LinkedList<std::string> result = sl.createRoute(&wantToVisit);
	std::cout << "Calculated route:\n";
	result.printList();
	std::cout << "------------------------------------------------------\n";

}
int main()
{
	//First task should read from the input
	std::cout << "First task:\n";
	runFirstTask();
	return 0;
}
