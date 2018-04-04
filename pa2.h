#ifndef PA2_H
#define PA2_H
#include <iostream>
#include <string>

using namespace std;

struct Node
{
    int index;
	string name;
    int value;
    Node *next;
    void createNode(int value);
    void createNode(int value, string n);
    void add(Node n);
    Node(int value);
    Node();
};

class LinkedList
{
public:
    Node *head;
    int getNumFragments();
    void createNode(int value, string n);
    void add(Node n);
    Node * getIndex(string n);
    Node * getIndexAt(int n);
    int getMaxIndex();
    int getMaxSize();
    Node getCopy(string n);
    void moveTo(LinkedList *b, string n);
    void remove(string n);
    bool contains(string n);
    bool contains(int n);
    int getNumPages(string);
    void splitAt(int index, int amount, string name);
    int getDataAtIndex(int x);
    string getNameAtIndex(int x);
    void indexIncrement(int x);
};

#endif

// Node
// Constructors
Node::Node()
{
    value = 0;
}

Node::Node(int value)
{
	this -> value = value;
    next = NULL;
}

void Node::createNode(int value)
{
    if (next == NULL)
    {
         next = new Node(value);
         return;
    }
    next -> createNode(value);
}

void Node::createNode(int value, string name)
{
    if (next == NULL)
    {      
         next = new Node(value);
         name = name;
         return;
    }
    next -> createNode(value, name);
}

void Node::add(Node n)
{
    if (next == NULL)
    {
         next = new Node;
         *next = n;
         next  ->  next = NULL;
         return;
    }
    next  ->  add(n);
}

//LinkedList

//Gets number of fragments
int LinkedList::getNumFragments()
{
    int j = 0;
    Node *index;
    index = head;
    while (index != NULL)
    {
         j++;
         index = index  ->  next;
    }
    return j;
}

int LinkedList::getMaxIndex()
{
    int maximum = 0;
    Node *index;
    index = head;
    while (index != NULL)
    {
         if (index  ->  index > maximum)
         {
              maximum = index -> index;
         }
         index = index -> next;
    }
    return maximum;
}

//Checks maximum space available to add programs
int LinkedList::getMaxSize()
{
    int value = 0;
    Node *index;
    index = head;
    while (index != NULL)
    {
         if (index -> value > value)
         {
              value = index -> value;
         }
         index = index -> next;
    }
    return value;
}

void LinkedList::indexIncrement(int x)
{
    Node *index;
    index = head;
    while (index != NULL)
    {
         if (index -> index >= x)
         {
              index -> index++;
         }
         index = index -> next;
    }
}

void LinkedList::createNode(int value, string n)
{
    if (head == NULL)
    {      
         head = new Node(value);
         head -> name = n;
         return;
    }
    head -> createNode(value, n);
}

void LinkedList::remove(string name)
{
    Node *index = new Node;
    index = head;

    if (index -> name == name)
    {          
         Node *temp = index -> next;
         delete head;
         head = temp;
         return;
    }
    while (index -> next != NULL)
    {          
         if (index -> next -> name == name)
         {      
              Node *temp = index -> next -> next;
              delete index -> next;
              index -> next = temp;
              return;
         }
         index = index -> next;
    }
    if (index -> name == name)
    {                
         delete index;
         index = NULL;
    }
}

//Checks if the linked list contains a particular element
bool LinkedList::contains(string n)
{
    bool contains = false;
    Node *index;
    index = head;
    while (index != NULL)
    {
         if (index -> name == n)
         {
              contains = true;
              return contains;
         }
         index = index -> next;
    }
    return contains;
}

bool LinkedList::contains(int n) {
    bool contains = false;
    Node *index;
    index = head;
    while (index != NULL) {
         if (index -> index == n) {
              contains = true;
              return contains;
         }
         index = index -> next;
    }
    return contains;
}

//Returns the number of pages used by a program
int LinkedList::getNumPages(string name)
{
    Node *index = head;
    int t = 1;
    while (index != NULL)
    {
         int numPages = index -> value;
         string Name = index -> name;
         index = index -> next;
         if (Name == name)
         	 return numPages;
         else 
         	 t++;
    }
}

void LinkedList::splitAt(int index, int amount, string n)
{
    if (contains(index))
    {
         Node *node = getIndexAt(index);
         node -> value -= amount;
         Node *temp = node -> next;
         node -> next = 0;
         node -> next = new Node(amount);
         node -> next -> name = n;
         node -> next -> next = temp;
    }
}

void LinkedList::moveTo(LinkedList *b, string name)
{

    if (this -> contains(name))
    {
         Node temp = this -> getCopy(name);
         b -> add(temp);
         this -> remove(name);
    }

}

void LinkedList::add(Node n)
{
    if (head == NULL)
    {
         head = new Node;
         *head = n;
         head -> next = NULL;
         return;
    }
    head -> add(n);
}

Node LinkedList::getCopy(string name)
{
    Node *index;
    index = head;
    while (index != NULL)
    {
         if (index -> name == name)
         {
              return *index;
         }
         index = index -> next;
    }
    return 0;
}

Node * LinkedList::getIndex(string name)
{
    Node *index;
    index = head;
    while (index != NULL)
    {
         if (index -> name == name)
         {
              return index;

         }
         index = index -> next;
    }
    return 0;
}

Node * LinkedList::getIndexAt(int n)
{
    Node *index;
    index = head;
    while (index != NULL)
    {
         if (index -> index == n)
              return index;
              
         index = index -> next;
    }
    return 0;
}

int LinkedList::getDataAtIndex(int n)
{
    Node * index = head;
    while (index != NULL)
    {
         if (index -> index == n)
         {
              return index -> value;
         }
         index = index -> next;
    }
    return -1;
}

string LinkedList::getNameAtIndex(int n)
{
    Node * index = head;
    while (index != NULL)
    {
         if (index -> index == n)
         {
              return index -> name;
         }
         index = index -> next;
    }
    return 0;
}
