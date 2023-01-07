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

};

#endif // !BOX
