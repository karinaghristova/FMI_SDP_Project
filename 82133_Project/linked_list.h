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
	LinkedList() :head(nullptr) {}
	LinkedList(LinkedList&& other) : head(other.head) {
		other.head = nullptr;
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
