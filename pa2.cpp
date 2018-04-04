#include <iostream>
#include <iomanip>
#include <climits>
#include <string>
#include "pa2.h"
using namespace std;

// function declaration
void addProgram(string, int);
void kill(string);
void printMemory();

// Declare variables
bool worstFit = false;
bool bestFit = false;
LinkedList * freeSpace;
LinkedList * usedSpace;
Node * free_Chunks;

int main(int argc, char ** argv)
{
	 freeSpace = new LinkedList;
	 usedSpace = new LinkedList;
	 freeSpace -> createNode(32, "FREE");
	 free_Chunks = freeSpace -> getIndex("FREE");
	 free_Chunks -> index = 1;
     string fitType;
     string argument; 
     int selection;
     
     argument = argv[1];
     
	if (argument == "best" || argument == "Best" || argument == "BEST")
	{
		fitType = "best";
	}
	else if (argument == "worst" || argument == "Worst" || argument == "WORST")
	{
		fitType = "worst";
	}
	else
	{
		cout << "ERROR: Invalid Argument" << endl;
		return 0;
	}
	
	if (fitType == "best")
	{
	      bestFit = true;
	}
	else if (fitType == "worst")
	{
	      worstFit = true;
	}

	cout << "Using " << fitType <<  " fit algorithm" << endl;
	cout << endl;

	cout << "	" << "1. Add program" << endl;
	cout << "	" << "2. Kill program" << endl;
	cout << "	" << "3. Fragmentation" << endl;
	cout << "	" << "4. Print memory" << endl;
	cout << "	" << "5. Exit" << endl;  
	cout << endl;
		
	while (selection != 5)
	{		
		cout << "choice - ";
		cin >> selection;
		if (selection != 1 && selection != 2 && selection != 3 && selection != 4 && selection != 5)
		{
			cout << endl;
			cout << "Error, invalid choice. Please try again." << endl;
			cout << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			continue;
		}
		
		switch (selection)
		{
			case 1: //Add program
			{
				string name;
				int size;
				int numPages;
				int i = 1;
				
				cout << "Program name - ";
				cin >> name;
				
				while (i == 1)
				{
					cout << "Program size (KB) - ";
					cin >> size;
				
					if (cin.good())
					{
						if (size <= 0)
						{
							cout << "Error, cannot have negative size." << endl;
							cout << endl;
							cin.clear();
							cin.ignore(INT_MAX, '\n');
						}
						else if (size > 0)
						{
							break;
						}
					}
					else
					{
						cout << "Error, not an integer." << endl;
						cout << endl;						
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						continue;
					}
				}
				
				if (usedSpace -> contains(name))
				{
					cout << endl;
					cout << "Error, Program " << name << " already running." << endl;
					cout << endl;
					i = 0;
					continue;
				}
				
				//Checks how much space is available
				int maxSize = freeSpace  ->  getMaxSize();
				
				if (size > maxSize * 4)
				{
					cout << endl;
					cout << "Error, Not enough memory for Program " << name << endl;
					cout << endl;
				}
				else
				{ 
					int numPages;
					if (size%4 == 0)
						numPages = size / 4;
					else
						numPages = size / 4 + 1;
					
					addProgram(name, size);
					
					cout << endl;
					cout << "Program " << name << " added successfully: " << numPages << " page(s) used." << endl;
					cout << endl;
				}
				break;
			}
			case 2: //Kill program
			{
				string name;
				
				cout << "Program name - ";
				cin >> name;
				
				if(usedSpace  ->  contains(name))
				{
					int numPages = usedSpace -> getNumPages(name);
					kill(name);
					cout << endl;
					cout << "Program " << name << " successfully killed, " << numPages << " page(s) reclaimed." << endl;
					cout << endl;
				}
				else
				{
					cout << endl;
					cout << "There is no program with that name." << endl;
					cout << endl;
				}
				break;
			}	
			case 3: //Fragmentation
			{
				int fragments = freeSpace  ->  getNumFragments();
				cout << endl;
				cout << "There are " << fragments << " fragment(s)." << endl;
				cout << endl;
				break;
			}
			case 4: //Print memory
			{
				cout << endl;
				printMemory();
				cout << endl;
				break;
			}				
			case 5: //Exit
			{
				selection = 5;
				return 0;
			}
		}			
	}
	
    return 0;
}

void kill(string name)
{
     if (usedSpace -> contains(name))
     {
     
          usedSpace -> moveTo(freeSpace, name);

          Node *temp = freeSpace -> getIndex(name);
          temp -> name = "FREE";

          int index = temp -> index;
     }
}

//Adds a program to the linked list
void addProgram(string name, int size)
{
	int numPages;
	if (size%4 == 0)
	{
		numPages = size / 4;
	}
	else
	{
		numPages = size / 4 + 1;
	}

	if (worstFit)
	{
		int memorySize = 0;
		int memoryAt = 0;
		Node * index = freeSpace -> head;

		if (memorySize < index -> value)
		{
			memorySize = index -> value;
			memoryAt = index -> index;
		}
		while (index -> next != NULL)
		{
			if (memorySize < index -> next -> value)
			{
				memorySize = index -> next -> value;
				memoryAt = index -> next -> index;
			}
			
			index = index -> next;
		}

		freeSpace -> splitAt(memoryAt, numPages, name);

		Node * temp = freeSpace -> getIndex(name);
		freeSpace -> indexIncrement(memoryAt);
		usedSpace -> indexIncrement(memoryAt);
		temp -> index = memoryAt;

		freeSpace -> moveTo(usedSpace, name);
	}
	
	else if (bestFit)
     {

		int memorySize = 0;
		int memoryAt = 0;
		Node * index = freeSpace -> head;

		if (index -> value >= numPages)
		{
			memorySize = index -> value;
			memoryAt = index -> index;
		}
		while (index -> next != NULL)
		{
			int tempval = index -> next -> value;
			if (tempval >= numPages && tempval < memorySize)
			{
				memorySize = index -> next -> value;
				memoryAt = index -> next -> index;
			}
			index = index -> next;
		}

		freeSpace -> splitAt(memoryAt, numPages, name);

		Node * temp = freeSpace -> getIndex(name);
		freeSpace -> indexIncrement(memoryAt);
		usedSpace -> indexIncrement(memoryAt);
		temp -> index = memoryAt;

		freeSpace -> moveTo(usedSpace, name);
    	}
}

void printMemory()
{
    int j = 0;
    int maxUsed = usedSpace -> getMaxIndex();
    int maxFree = freeSpace -> getMaxIndex();
    int maxPos = 0;
    
    if (maxUsed < maxFree)
    {
        maxPos = maxFree;
    }
    else
    {
        maxPos = maxUsed;
    }
    
	for (int i = 1; i <= maxPos; i++)
    {
        if (usedSpace -> getDataAtIndex(i) != -1)
		{
            int temp = usedSpace -> getDataAtIndex(i);
            string name = usedSpace -> getNameAtIndex(i);
			while (temp >= 1)
			{
	           	//Makes it print neatly if the name is less than 4 characters long, as in the 					examples
				if (name.length() == 1)
                    cout << name << "   " << " ";
                else if (name.length() == 2)
                    cout << name << "  " << " ";
                else if (name.length() == 3)
                    cout << name << " " << " ";
                else
                    cout << name << " ";
                temp--;
                j++;
                if (j >= 8)
                {
                    j = 0;
                    cout << endl;
                }
			}
		}
			
        else
        {
             int temp = freeSpace -> getDataAtIndex(i);
             string name = freeSpace -> getNameAtIndex(i);
             while (temp >= 1)
             {
             
				 if (name.length() == 1)
        	  	     cout << name << "   " << " ";
                 else if (name.length() == 2)
             	     cout << name << "  " << " ";
                 else if (name.length() == 3)
					 cout << name << " " << " ";
                 else
                     cout << name << " ";
                 temp--;
                 j++;
                 if (j >= 8)
                 {
                     j = 0;
                     cout << endl;
                 }
             }
         }
    }
}

