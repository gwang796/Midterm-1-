//
//  main.cpp
//  COMSC-210 | Midterm #1 | Guo An Wang
//  IDE: Xcode
//  Created by Guo An Wang on 10/16/25.
//

#include <iostream>
using namespace std;
//declaring const int variables in order to not hard code
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList { //declare a class named DoubleLinkedList
private: //private variables to class DoubleLinkedList, unaccessible outside of class
    struct Node { //declare a struct Node
        int data;// int variable data
        Node* prev; //Node pointer prev points to previous Node in linked list
        Node* next; //Node pointer next points to the next Node in linked list
        //Node constructor that initializes struct Node data members
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; //data initialized to val
            prev = p; //prev initialized to nullptr
            next = n; //next initialized to nullptr
        }
    };

    Node* head; // declaring Node head of linked list
    Node* tail; // declaring Node tail of linked list

public: //public means accessible from outside the class
    //DoubleLinkedList constructor that initializes head and tail to nullptr
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    //function insert_after has user insert an int value in the next node of linked list
    //arguments : int value, int position
    //return: none
    void insert_after(int value, int position) {
        if (position < 0) { //makes sure position is within bounds
            cout << "Position must be >= 0." << endl; //error message
            return; //end of function execution
        }
        //declaring newNode pointer to new Node object with 'value'
        Node* newNode = new Node(value);
        if (!head) { //if the linked list is empty
            head = tail = newNode; //head is the same as tail set newNode pointer to head/tail
            return; //end function execution
        }
        //declare temp pointer to head of linked list
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i) //traversing through linked list until before position
            temp = temp->next; //through each loop temp is set to the next Nodes

        if (!temp) { // if outside of linked list length
            cout << "Position exceeds list size. Node not inserted.\n"; //error message
            delete newNode; //free memory for Node we tried to create
            return; //end function executuion
        }

        newNode->next = temp->next; //newNode next is same as temp next
        newNode->prev = temp; //newNode prev is same as temp current value
        if (temp->next) //if temp is not the tail
            temp->next->prev = newNode; //connect temp next node previous pointer to new Node
        else
            tail = newNode; //when inserting at the tail
        temp->next = newNode; //temp next is set to new Node
    }

    //function delete_val deletes a selected value within the linked list
    //arguments: int value
    // return: none
    void delete_val(int value) {
        if (!head) return; //linked list is empty so end function execution
        //declare temp pointer to head of linked list
        Node* temp = head;
        //traverse through linked list until finding same value as parameter
        while (temp && temp->data != value)
            temp = temp->next; //value of temp moving to next Nodes

        if (!temp) return; //value is not found

        if (temp->prev) //
            temp->prev->next = temp->next;
        else
            head = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() { //destructor of DoublyLinkedList
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    //function print every element in linked list in order
    //arguments: none
    //return: none
    void print() {
        Node* current = head; //declare current pointer to head of linked list
        if (!current) { //if list is empty
            cout << "List is empty." << endl; //error message
            return; // end function execution
        }
        while (current) { //traverse through linked list until current points to nullptr
            cout << current->data << " "; //printing Node element, current=pointer, -> dereference to print data value not memory address
            current = current->next; //moving to next node
        }
        cout << endl;
    }

    //function print_reverse prints linked list in reverse
    //arguments: none
    //return: none
    void print_reverse() {
        Node* current = tail; //declare current pointer to tail of linked list
        if (!current) { //if list is empty
            cout << "List is empty." << endl; //error message
            return; // end function execution
        }
        while (current) { //traverse through linked list until current points to nullptr
            cout << current->data << " "; //printing Node element, current=pointer, -> dereference to print data value not memory address
            current = current->prev; //moving to next node
        }
        cout << endl;
    }
    //function every_other_element prints every other element of linked list
    //arguments: none
    //return: none
    void every_other_element(){
        Node* current = head; //declare current pointer to head of linked list
        if (!current) { //if list is empty
            cout << "List is empty." << endl; //error message
            return; // end function execution
        }
        int position = 0; //int count to track Node position
        while (current) { //traverse through linked list until current points to nullptr
            if (position % 2 ==0) { //position division by 2 has no remaining value (0, 2, 4...)
                cout << current->data << " "; //printing Node element, current=pointer, -> dereference to print data value not memory address
                current = current->next; //moving to next node
            }
            position++; //add one every loop
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}
