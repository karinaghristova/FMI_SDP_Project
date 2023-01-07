#ifndef BOX
#define BOX
#include <string>
#include "linked_list.h"

struct Souvenir {
	std::string souvenirName;
	Souvenir(std::string name) {
		souvenirName = souvenirName;
	}
};

class Box {
private:
	LinkedList<Souvenir> souvenirs = LinkedList<Souvenir>();
	LinkedList<Box> innerBoxes = LinkedList<Box>();
	std::string name;

	Box(std::string name) : name(name) {}


	void addSouvenir(std::string souvenirName) {
		Souvenir souvenir = Souvenir(souvenirName);
		souvenirs.insertEnd(souvenir);
	}

	void addBox(std::string boxName, LinkedList<Box> allBoxes) {
		//If the box is not present we add it to the list of boxes
		if (!allBoxes.checkForElementWithValue(boxName)) {
			Box newBox = Box(boxName);
			allBoxes.insertEnd(newBox);
		}

		innerBoxes.insertEnd(allBoxes.getElementWithValue(boxName));
	}

	bool hasSouvenirs() {
		return souvenirs.getFirstElement() != nullptr;
	}

	bool hasBoxes() {
		return innerBoxes.getFirstElement() != nullptr;
	}

	bool isEmpty() {
		return (!hasSouvenirs() && !hasBoxes());
	}

	bool hasOnlyOneBox() {
		if (!hasBoxes())
			return false;
		bool hasOnlyOneBox = innerBoxes.getFirstElement()->next == nullptr;
		return hasOnlyOneBox;
	}

	bool canBeReplacedWithInnerBox() {
		return (!hasSouvenirs() && hasOnlyOneBox())
	}
};

#endif // !BOX
