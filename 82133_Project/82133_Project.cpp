#include <iostream>
#include <string>
#include "skip_list.h"

int main()
{
	//Initiating the cities
	SkipList<std::string> sl = SkipList<std::string>();
	sl.insertEnd("Sofia");
	sl.insertEnd("Pazardzhik");
	sl.insertEnd("Plovdiv");
	sl.insertEnd("Dimitrovgrad");
	sl.insertEnd("StaraZagora");
	sl.insertEnd("NovaZagora");
	sl.insertEnd("Yambol");
	sl.insertEnd("Karnobat");
	sl.insertEnd("Burgas");
	//sl.printList();

	//1: Setting expresses
	sl.setExpressToNode(sl.getNodeWithValue("Sofia"), sl.getNodeWithValue("Plovdiv"));
	sl.setExpressToNode(sl.getNodeWithValue("Plovdiv"), sl.getNodeWithValue("NovaZagora"));
	sl.setExpressToNode(sl.getNodeWithValue("Dimitrovgrad"), sl.getNodeWithValue("NovaZagora"));
	sl.setExpressToNode(sl.getNodeWithValue("StaraZagora"), sl.getNodeWithValue("Yambol"));
	sl.setExpressToNode(sl.getNodeWithValue("NovaZagora"), sl.getNodeWithValue("Burgas"));

	//1.1: initiating a list of the cities we want to visit
	LinkedList<std::string> wantToVisit = LinkedList<std::string>();
	wantToVisit.insertEnd("Plovdiv");
	wantToVisit.insertEnd("StaraZagora");
	wantToVisit.insertEnd("Yambol");

	////1.2: Initiating a list of the cities we want to visit
	//LinkedList<std::string> wantToVisit = LinkedList<std::string>();
	//wantToVisit.insertEnd("Pazardzhik");
	//wantToVisit.insertEnd("Dimitrovgrad");
	//wantToVisit.insertEnd("Yambol");
	////Expected: Sofia, Pazardzhik, Plovdiv, Dimitrovgrad, NovaZagora, Yambol, Karnobat, Burgas

	//////2: Setting expresses
	////sl.setExpressToNode(sl.getNodeWithValue("Sofia"), sl.getNodeWithValue("Dimitrovgrad"));
	////sl.setExpressToNode(sl.getNodeWithValue("Pazardzhik"), sl.getNodeWithValue("Dimitrovgrad"));
	////sl.setExpressToNode(sl.getNodeWithValue("Dimitrovgrad"), sl.getNodeWithValue("NovaZagora"));
	////sl.setExpressToNode(sl.getNodeWithValue("StaraZagora"), sl.getNodeWithValue("Yambol"));
	////sl.setExpressToNode(sl.getNodeWithValue("NovaZagora"), sl.getNodeWithValue("Burgas"));

	//////2.1: Initiating a list of the cities we want to visit
	////LinkedList<std::string> wantToVisit = LinkedList<std::string>();
	////wantToVisit.insertEnd("Plovdiv");
	////wantToVisit.insertEnd("StaraZagora");
	////wantToVisit.insertEnd("Yambol");
	//////Expected: Sofia, Pazardzhik, Plovdiv, Dimitrovgrad, StaraZagora, Yambol, Karnobat, Burgas

	//////2.2: Initiating a list of the cities we want to visit
	////LinkedList<std::string> wantToVisit = LinkedList<std::string>();
	////wantToVisit.insertEnd("Dimitrovgrad");
	////wantToVisit.insertEnd("NovaZagora");
	////wantToVisit.insertEnd("Karnobat");
	//////Expected: Sofia, Dimitrovgrad, NovaZagora, Yambol, Karnobat, Burgas

	LinkedList<std::string> result = sl.createRoute(&wantToVisit);
	result.printList();

	return 0;
}

