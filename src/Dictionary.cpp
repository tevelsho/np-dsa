#include "Dictionary.h"

Dictionary::Dictionary()
{
	size = 0;
	for (int i = 0; i < MAX_SIZE; i++) {
		items[i] = nullptr;
	}
}

Dictionary::~Dictionary() {
	for (int i = 0; i < MAX_SIZE; i++) {
		Node* current = items[i];
		while (current != nullptr) {
			Node* toDelete = current;
			current = current->next;
			delete toDelete;
		}
	}
}

int Dictionary::hash(KeyType key) {
	return key % MAX_SIZE;
}

bool Dictionary::add(KeyType newKey, ItemType newItem) {
	int index = hash(newKey);
	Node* current = items[index];

	//Check for duplicate keys
	while (current != nullptr) {
		if (current->key == newKey) {
			return false;
		}
		current = current->next;
	}
	
	Node* newNode = new Node();
	newNode->item = newItem;
	newNode->key = newKey;
	newNode->next = items[index];
	items[index] = newNode;
	size++;
	return true;
}


void Dictionary::remove(KeyType key) {
	int index = hash(key);

	Node* previous = nullptr;
	Node* current = items[index];

	while (current != nullptr) {
		if (current->key == key) {
			if (previous == nullptr) {
				items[index] = current->next; //FIRST NODE
			}
			else {
				previous->next = current->next;
			}
			delete current;
			size--;
			return;
		}
		previous = current;
		current = current->next;
	}
}

ItemType Dictionary::get(KeyType key) {
	int index = hash(key);
	Node* current = items[index];
	while (current != nullptr) {
		if (current->key == key) {
			return current->item;
		}
		current = current->next;
	}
	return nullptr;
}

bool Dictionary::contains(KeyType key) {
	int index = hash(key);
	Node* current = items[index];
	while (current != nullptr) {
		if (current->key == key) {
			return true;
		}
		current = current->next;
	}
	return false;
}

bool Dictionary::isEmpty() {
	return size == 0;
}

int Dictionary::getLength() {
	return size;
}

void Dictionary::print() {
	for (int i = 0; i < MAX_SIZE; i++) {
		Node* current = items[i];
		if (current != nullptr) {
			cout << "Index " << i << ": ";
			while (current != nullptr) {
				cout << "[" << current->key << ": " << current->item << "] -> ";
				current = current->next;
			}
			cout << "nullptr" << endl;
		}
	}
}