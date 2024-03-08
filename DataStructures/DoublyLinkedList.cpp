#include <bits/stdc++.h>

template <typename T>
class DoublyLinkedList {
private:
    int listSize = 0;

    class Node {
    private:
        T data;
        Node* prev;
        Node* next;

    public:
        Node(T data, Node* prev, Node* next) {
            this->data = data;
            this->prev = prev;
            this->next = next;
        }

        std::string to_string() {
            return std::to_string(this->data);
        }

        T getData() const {
            return data;
        }

        void setData(T newData) {
            data = newData;
        }

        void setData(std::nullptr_t) {
            setData(T()); 
        }

        Node* getPrev() const {
            return prev;
        }

        void setPrev(Node* newPrev) {
            prev = newPrev;
        }

        Node* getNext() const {
            return next;
        }

        void setNext(Node* newNext) {
            next = newNext;
        }
    };

    Node* head = nullptr;
    Node* tail = nullptr;

public:
    void clear() {
        Node* traversePointer = head;
        while (traversePointer != nullptr) {
            Node* next = traversePointer->getNext();
            traversePointer->setPrev(nullptr);
            traversePointer->setNext(nullptr);
            traversePointer->setData(nullptr);
            traversePointer = next;
        }

        this->head = this->tail = traversePointer = nullptr;
        this->listSize = 0;
    }

    int size() {
        return this->listSize;
    }

    bool isEmpty() {
        return this->size() == 0;
    }

    void add(T element) {
        this->addLast(element);
    }

    void addLast(T element) {
        if (this->isEmpty()) {
            this->head = this->tail = new Node(element, nullptr, nullptr);
        } else {
            this->tail->setNext(new Node(element, this->tail, nullptr));
            this->tail = this->tail->getNext();
        }

        this->listSize++;
    }

    void addFirst(T element) {
        if (this->isEmpty()) {
            this->head = this->tail = new Node(element, nullptr, nullptr);
        } else {
            this->head->setPrev(new Node(element, nullptr, this->head));
            this->head = this->head->getPrev();
        }

        this->listSize++;
    }

    T peekFirst() {
        if (this->isEmpty()) {
            throw std::invalid_argument("The list is empty.");
        }

        return this->head->getData();
    }

    T peekLast() {
        if (this->isEmpty()) {
            throw std::invalid_argument("The list is empty.");
        }

        return this->tail->getData();
    }

    void removeFirst() {
        if (this->isEmpty()) {
            throw std::invalid_argument("The list is empty.");
        }

        Node* temp = head;
        this->head = this->head->getNext();
        this->listSize--;

        if (this->isEmpty()) {
            this->tail = nullptr;
        } else {
            this->head->setPrev(nullptr);
        }

        temp->setData(nullptr);
        temp->setNext(nullptr);
        temp->setPrev(nullptr);
        delete temp;
    }

    void removeLast() {
        if (this->isEmpty()) {
            throw std::invalid_argument("The list is empty.");
        }

        Node* temp = tail;
        this->tail = this->tail->getPrev();
        this->listSize--;

        if (this->isEmpty()) {
            this->head = nullptr;
        } else {
            this->tail->setNext(nullptr);
        }

        temp->setData(nullptr);
        temp->setNext(nullptr);
        temp->setPrev(nullptr);
        delete temp;
    }

    void remove(Node* node) {
        if (node->getPrev() == nullptr){
            this->removeFirst();
            return;
        }
        if (node->getNext() == nullptr){
            this->removeLast();
            return;
        } 

        node->getNext()->setPrev(node->getPrev());
        node->getPrev()->setNext(node->getNext());
        node->setData(nullptr);
        node->setNext(nullptr);
        node->setPrev(nullptr);
        delete node;
        this->listSize--;
    }

    void removeAt(int index) {
        if (index < 0 || index >= this->size) {
            throw std::invalid_argument("The given index is out of bound : " + std::to_string(index));
        }

        int i;
        Node* traversePointer;
        if (index < this->size() / 2) {
            for (i = 0, traversePointer = this->head; i != index; i++) {
                traversePointer = traversePointer->getNext();
            }
        } else {
            for (i = this->size - 1, traversePointer = this->tail; i != index; i--) {
                traversePointer = traversePointer->getPrev();
            }
        }

        this->remove(traversePointer);
    }

    void remove(T data) {
        for (Node* traversePointer = this->head; traversePointer != nullptr; traversePointer = traversePointer->getNext()) {
            if (traversePointer->getData() == data) {
                this->remove(traversePointer);
                return;
            }
        }
    }

    int indexOf(T data) {
        int index;
        Node* traversePointer;
        for (index = 0, traversePointer = this->head; traversePointer != nullptr; traversePointer = traversePointer->getNext()) {
            if (traversePointer->getData() == data) {
                return index;
            }
            index++;
        }

        return -1;
    }

    bool contains(T data) {
        return this->indexOf(data) != -1;
    }

    class Iterator {
    private:
        Node* iterator = this->head;

    public:
        bool hasNext() {
            return iterator != nullptr;
        }

        T next() {
            T data = iterator->getData();
            this->iterator = this->iterator->getNext();
            return data;
        }
    };

    Iterator iterator() {
        return Iterator();
    }

    std::string to_string() {
        if (this->isEmpty()) {
            return "[]";
        }

        std::string result = "[";
        for (Node* traversePointer = this->head; traversePointer != this->tail; traversePointer = traversePointer->getNext()) {
            result += std::to_string(traversePointer->getData()) + ", ";
        }

        result += std::to_string(this->tail->getData()) + "]";
        return result;
    }
};

int main() {
    std::cout << "Welcome to Doubly Linked List" << '\n';
    DoublyLinkedList<int> myList;
    myList.add(1);
    myList.add(2);
    std::cout << myList.contains(1) << '\n';
    std::cout << myList.contains(11) << '\n';
    std::cout << myList.indexOf(2) << '\n';
    std::cout << myList.size() << '\n';
    std::cout << myList.to_string() << '\n';
    myList.remove(1);
    std::cout<<myList.peekFirst();
    std::cout << '\n';
    std::cout << myList.to_string() << '\n';
    return 0;
}
