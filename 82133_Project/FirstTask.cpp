#include <iostream>
#include <string>
#include <vector>
#include "skip_list.h"


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
	std::cout << "All train stations:\n";
	sl.printList();

	std::cout << "\n------------------\n\n";

	//2. Setting expresses
	setExpresses(sl);
	std::cout << "Express train stations only:\n";
	sl.printWithExpressOnly();

	std::cout << "\n------------------\n\n";

	//3. Initiating a list of the cities we want to visit
	LinkedList<std::string> wantToVisit = LinkedList<std::string>();
	initiateCitiesThatMustBeVisited(wantToVisit);

	//4. Creating the route
	LinkedList<std::string> result = sl.createRoute(&wantToVisit);
	std::cout << "Calculated route:\n";
	result.printList();
}


int main()
{
	//First task should read from the input
	std::cout << "First task:\n";
	runFirstTask();
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
