#ifndef LINKED_LIST
#define LINKED_LIST
template <typename T>
struct SimpleNode {
	T data;
	struct SimpleNode<T>* next;

	SimpleNode(T value) {
		data = value;
		next = nullptr;
	}
};

template <typename T>
class LinkedList {
private:
	SimpleNode<T>* head;
public:
	//default constructor
	LinkedList() :head(nullptr) {}

	//copy constructor
	LinkedList(const LinkedList<T>& other) {
		head = nullptr;
		SimpleNode<T>* currentNode = other.head;
		while (currentNode != nullptr) {
			insertEnd(currentNode->data);
			currentNode = currentNode->next;
		}
	}

	//move constructor
	LinkedList(LinkedList<T>&& other) : head(other.head) {
		other.head = nullptr;
	}

	LinkedList<T>& operator=(LinkedList<T> other) {
		std::swap(head, other.head);
		return *this;
	}

	LinkedList<T>& operator=(LinkedList<T>&& other) {
		head = other.head;
		other.head = nullptr;
		return *this;
	}

	~LinkedList() {
		SimpleNode<T>* currentNode = head;
		while (currentNode != nullptr) {
			SimpleNode<T>* nextNode = currentNode->next;
			delete currentNode;
			currentNode = nextNode;
		}
	}

	void insertFront(T data) {
		SimpleNode<T>* newNode = new SimpleNode<T>(data);
		newNode->next = head;
		head = newNode;
	}

	void insertEnd(T data) {
		if (head == nullptr) {
			head = new SimpleNode<T>(data);
			return;
		}

		SimpleNode<T>* current = head;
		while (current->next != nullptr)
			current = current->next;
		current->next = new SimpleNode<T>(data);
	}

	void insertAfter(SimpleNode<T>* prevNode, T data) {
		if (head == nullptr) {
			insertFront(data);
			return;
		}

		SimpleNode<T>* newNode = new SimpleNode<T>(data);
		newNode->next = prevNode->next;
		prevNode->next = newNode;
	}

	void deleteNode(SimpleNode<T>* nodeToDelete) {
		if (head == nullptr || nodeToDelete == nullptr)
			return;

		SimpleNode<T>* temp = head;

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

	SimpleNode<T>* getFirstElement() {
		return head;
	}

	SimpleNode<T>* getElementWithValue(T value) {
		SimpleNode<T>* current = head;
		while (current != nullptr){
			if (current->data == value)
				return current;
			current = current->next;
		}

		return current;
	}

	bool checkForElementWithValue(T value) {
		SimpleNode<T>* current = head;
		while (current != nullptr) {
			if (current->data == value)
				return true;
			current = current->next;
		}

		return current != nullptr;
	}

	void printList() {
		SimpleNode<T>* current = head;
		while (current != nullptr) {
			std::cout << current->data << "->";
			current = current->next;
		}
		std::cout << std::endl;
	}
};

#endif // !LINKED_LIST
