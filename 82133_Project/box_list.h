#ifndef BOX_LIST
#define BOX_LIST

#include <string>
#include <vector>
struct BoxNode {
	std::string name;
	std::vector<std::string> souvenirs;
	std::vector<BoxNode*> boxes;
	BoxNode* next;

	BoxNode(std::string name) {
		this->name = name;
		next = nullptr;
	}
};

class BoxList {
private:
	BoxNode* head;
	size_t listElements = 0;
public:
	BoxList() : head(nullptr), listElements(0) {}

	////copy ctor
	//BoxList(const BoxList& other) {
	//	head = nullptr;
	//	BoxNode* currentBoxNode = other.head;
	//	while (currentBoxNode != nullptr) {
	//		insert(currentBoxNode->name);
	//		//for (size_t i = 0; i < currentBoxNode.souvenirs; i++){

	//		//}
	//		currentBoxNode = currentBoxNode->next;
	//	}
	//}

	//move ctor
	BoxList(BoxList&& other) : head(other.head), listElements(other.listElements) {
		other.head = nullptr;
		other.listElements = 0;
	}

	BoxList& operator=(BoxList other) {
		std::swap(head, other.head);
		std::swap(listElements, other.listElements);
		return *this;
	}

	BoxList& operator=(BoxList&& other) {
		head = other.head;
		listElements = other.listElements;
		other.head = nullptr;
		other.listElements = 0;
		return *this;
	}

	~BoxList() {
		BoxNode* curentBoxNode = head;
		while (curentBoxNode != nullptr) {
			BoxNode* nextBoxNode = curentBoxNode->next;
			curentBoxNode->souvenirs.clear();
			curentBoxNode->boxes.clear();
			delete curentBoxNode;
			curentBoxNode = nextBoxNode;
		}
	}
	void insert(std::string boxName) {
		if (checkForBoxWithName(boxName))
			return;

		if (head == nullptr) {
			head = new BoxNode(boxName);
			listElements++;
			return;
		}

		BoxNode* current = head;
		while (current->next != nullptr)
			current = current->next;
		current->next = new BoxNode(boxName);
		listElements++;
	 }

	void deleteBoxNode(BoxNode* nodeToDelete) {
		if (head == nullptr || nodeToDelete == nullptr)
			return;
		BoxNode* temp = head;
		if (head == nodeToDelete) {
			head = head->next;
			temp->souvenirs.clear();
			temp->boxes.clear();
			delete temp;
			listElements--;
		}
		else {
			while (temp->next != nodeToDelete)
				temp = temp->next;
			temp->next = nodeToDelete->next;
			nodeToDelete->souvenirs.clear();
			nodeToDelete->boxes.clear();
			delete nodeToDelete;
			listElements--;
		}
	}

	bool checkForBoxWithName(std::string name) {
		BoxNode* current = head;
		while (current != nullptr) {
			if (current->name == name)
				return true;
			current = current->next;
		}

		return current != nullptr;
	}

	void addSouvenirsToBoxWithName(std::string name, std::string souvenirName) {
		BoxNode* current = head;
		while (current != nullptr) {
			if (current->name == name)
				current->souvenirs.push_back(souvenirName);
			current = current->next;
		}
	}

	void addInnerBoxToBoxWithName(std::string name, BoxNode* innerBox) {
		BoxNode* current = head;
		while (current != nullptr) {
			if (current->name == name && checkForBoxWithName(innerBox->name))
				current->boxes.push_back(innerBox);
			current = current->next;
		}
	}

	BoxNode* getBoxWithName(std::string name) {
		BoxNode* current = head;
		while (current != nullptr) {
			if (current->name == name)
				return current;
			current = current->next;
		}

		return nullptr;
	}

	bool canBeReplacedWithInnerBox(BoxNode* box) {
		return ((*box).souvenirs.size() == 0 && (*box).boxes.size() == 1);
	}

	size_t getNumberOfBoxes() {
		return listElements;
	}

	std::string printList() {
		BoxNode* current = head;
		std::string result = "";
		while (current != nullptr) {
			result += (*current).name;
			result += "\n	Souvenirs: ";
			for (size_t i = 0; i < (*current).souvenirs.size(); i++)
				result += (*current).souvenirs[i] + " | ";
			result += "\n	Inner boxes: ";
			for (size_t j = 0; j < (*current).boxes.size(); j++)
				result += (*current).boxes[j]->name + " | ";
			
			result += "\n";
			current = current->next;
		}

		return result;
	}
};
#endif // !BOX_LIST
