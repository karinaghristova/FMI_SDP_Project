#ifndef SKIP_LIST
#define SKIP_LIST

#include "linked_list.h"
template <typename T>
struct Node {
	T data;
	struct Node<T>* next;
	struct Node<T>* express;

	Node(T value) {
		data = value;
		next = nullptr;
		express = nullptr;
	}
};

template <typename T>
class SkipList
{
private:
	Node<T>* head;
public:
	SkipList() : head(nullptr) {}

	SkipList(SkipList&& other) : head(other.head) {
		other.head = nullptr;
	}

	void insertFront(T data) {
		Node<T>* newNode = new Node<T>(data);
		newNode->next = head;
		head = newNode;
	}

	void insertEnd(T data) {
		if (head == nullptr) {
			head = new Node<T>(data);
			return;
		}

		Node<T>* current = head;
		while (current->next != nullptr)
			current = current->next;
		current->next = new Node<T>(data);
	}

	void insertAfter(Node<T>* prevNode, T data) {
		if (head == nullptr) {
			insertFront(data);
			return;
		}

		Node<T>* newNode = new Node<T>(data);
		newNode->next = prevNode->next;
		prevNode->next = newNode;
	}

	void deleteNode(Node<T>* nodeToDelete) {
		if (head == nullptr || nodeToDelete == nullptr)
			return;

		Node<T>* temp = head;

		if (head == nodeToDelete) {
			head = head->next;
			delete temp;
		}
		else {
			while (temp->next != nodeToDelete)
				temp = temp->next;
			temp->next = nodeToDelete->next;
			delete nodeToDelete;
		}
	}

	void printList() {
		Node<T>* current = head;
		while (current != nullptr) {
			std::cout << current->data << "->";
			current = current->next;
		}
		std::cout << std::endl;
	}

	void printWithExpressOnly() {
		Node<T>* current = head;
		while (current != nullptr) {
			if (current->express != nullptr)
				std::cout << current->data << "->" << current->express->data << " | ";
			current = current->next;
		}
		std::cout << std::endl;
	}

	Node<T>* getNodeWithValue(T value) {
		Node<T>* current = head;

		while (current->data != value && current->next != nullptr)
			current = current->next;

		if (current->data == value)
			return current;

		return nullptr;
	}

	bool checkForNodeWithValue(T value) {
		Node<T>* current = head;

		while (current->data != value && current->next != nullptr)
			current = current->next;

		if (current->data == value)
			return true;

		return false;
	}

	void setExpressToNode(Node<T>* node, Node<T>* expressNode) {
		if (node != nullptr && expressNode != nullptr)
			node->express = expressNode;
	}

	Node<T>* takeExpressFromNode(Node<T>* node) {
		return node->express;
	}

	bool canTakeExpress(Node<T>* startPoint, Node<T>* endPoint) {
		Node<T>* currentNode = startPoint->express;
		if (currentNode == nullptr) return false;

		while (currentNode->next != nullptr and currentNode != endPoint)
			currentNode = currentNode->next;
		if (currentNode == endPoint)
			return true;
		return false;
	}

	//!!! Important to notice here is that we expect the cities 
	//to be in the order they are in the original list of cities
	//as the skip list is implemented as a forward list and we 
	//accept that we don't want to go back the road only forward
	LinkedList<T>* createRoute(LinkedList<T>* wantToVisit) {
		Node<T>* currentCity = head;
		LinkedList<T> resultRoute = LinkedList<T>();
		SimpleNode<T>* currentCityFromList = (*wantToVisit).getFirstElement();

		while (currentCityFromList != nullptr) {
			Node<T>* nextCity = getNodeWithValue(currentCityFromList->data);

			if (currentCity->next == nextCity) { //If the next city is the next we want to visit
				resultRoute.insertEnd(currentCity->data);
				currentCity = currentCity->next;
				currentCityFromList = currentCityFromList->next;
			}
			else { //If the next city is not the next we want to visit
				if (canTakeExpress(currentCity, nextCity)) { //Check for express
					resultRoute.insertEnd(currentCity->data);
					currentCity = takeExpressFromNode(currentCity);
					currentCityFromList = currentCityFromList->next;
				}
				else { //Continue to the next city
					resultRoute.insertEnd(currentCity->data);
					currentCity = currentCity->next;
				}
			}
		}

		//If we have visited all the cities we wanted but we're still not at the final stop
		while (currentCity != nullptr) {
			resultRoute.insertEnd(currentCity->data);
			currentCity = currentCity->next;
		}

		return &resultRoute;
	}

};


#endif // !SKIP_LIST
