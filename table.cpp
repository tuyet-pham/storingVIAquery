/*
*	table.cpp
*	Written by : Tuyet Pham
*	Group Memebers : Pedro Sanchez, Trevor Kerchner, Tuyet Pham
*	Project 2 - 2110 ISLAM
*/



#include "pch.h"
#include "table.h"
#include "resource.h"



/*
* _func_ : hashbrowns
* param : string
* return :	int
* task : HASH FUNCTION. The hash function takes in a string -KEY- then it adds up each
*		value in key by turning it into an integer, if it is not already. 
*		It will then return a squared hashvalue that's modulo by the size of the table.
*/
int table::hashbrowns(string KEY) {

	int hashvalue = 0;
	for (auto i = 0; i < KEY.length(); i++) {
		hashvalue = hashvalue + int(KEY[i]);
	}
	return hashvalue*hashvalue % MAXROWSIZE;	
}

/*
* _func_ : table - CONSTRUCTOR
* task : Set all values of the to NULL
*/
table::table() {

	for (int i = 0; i < MAXROWSIZE; i++) {
		HASHTABLE[i] = NULL;
	}
}


/*
* _func_ : table - CONSTRUCTOR 2
* param : string
* task : Set all values of the to NULL. Set the table name that was passed in.
*/
table::table(string tableName) : tablename(tableName)
{
	for (int i = 0; i < MAXROWSIZE; i++) {
		HASHTABLE[i] = NULL;
	
	}
	this->tablename = tableName;
}


/*
* _func_ : table - CONSTRUCTOR 3
* param : string, string
* task : Set all values of the to NULL. Set the table name that was passed in. Set the relational attribute - KEY -
*/
table::table(string tableName, string key) : tablename(tableName), relation_attr(key)
{
	for (int i = 0; i < MAXROWSIZE; i++) {
		HASHTABLE[i] = NULL;
	}
	this->tablename = tableName;

	//The relation_attr - KEY - can only be set once for every table and this KEY_SET will ensure that.
	if (KEY_SET == false) {
		this->relation_attr = key;
		this->KEY_SET = true;
	}
}


/*
* _func_ : setRelation_attr
* param : string
* return : bool
* task : Set the relational attribute - KEY -
*/
bool table::setRelation_attr(string key)
{
	//The relation_attr - KEY - can only be set once for every table and this KEY_SET will ensure that.
	if (KEY_SET == false) {
		this->relation_attr = key;
		this->KEY_SET = true;
		return true;
	}
	return false;
}


/*
* _func_ : getRelation_attr
* return : string
* task : Get the relational attribute - KEY -
*/
string table::getRelation_attr()
{
	return this->relation_attr;
}



/*
* _func_ : addAttribute
* param : string, int 
* return : bool
* task : Add an attribute to the list, at a specific index.
*/
bool table::addAttribute(string attribute, int index)
{
	att[index] = attribute;
	return true;
}



/*
* _func_ : deleteAttribute
* param : string
* return : bool
* task : Delete an attribute from the list. return false, if not in list, true true if in list.
*/
bool table::deleteAttribute(string attribute)
{
	for (auto i : att) {
		if (i == attribute) {
			i.clear();
			return true;
		}
	}

	return false;
}



/*
* _func_ : setTableName
* param : string
* task : setting the table name
*/
void table::setTableName(string tablename)
{
	this->tablename = tablename;
}



/*
* _func_ : getting the table name
* return : string
* task : getting the table name
*/
string table::getTableName()
{
	return this->tablename;
}


/*
* _func_ : makeRecord
* param : Record
* return : int
* task : This function will take in a Record and add it to the hashtable. 
*		It then returns the index of the item.
*/
int table::makeRecord(Record &newRec)
{
	//To check if the hashtable have already have this key. return -3
	for (int i = 0; i < MAXROWSIZE; i++) {
		if (HASHTABLE[i] != NULL) {
			if (HASHTABLE[i]->KEY == newRec.KEY) {
				return -3;
			}
		}
	}
	
	int index = hashbrowns(newRec.KEY);			//make an index for the Record depending on it's key value.
	int prober = 0;								//A prober to increment through the hashtable if the index was not free.

	while (prober < MAXROWSIZE) {
		if (HASHTABLE[index] == NULL) {
			HASHTABLE[index] = &newRec;
			return index;						//return index of the newly stored record
		}
		else {
			index = (index + 1) % MAXROWSIZE;
			prober++;
		}
	}
	return -1;									//This case is if the table is full.
}


/*
* _func_ : deleteRecord
* param : string
* return : bool
* task : Given the key the funtion will delete the record from the table.
*/
bool table::deleteRecord(string KEY)
{
	
		int index = hashbrowns(KEY);				//make what could be the Records index for the Record depending on it's key value.

		//A prober to increment through the hashtable if the record's key in the index isn't the same as the one given
		int prober = 0;								


		while (prober < MAXROWSIZE) {
			if (HASHTABLE[index]->KEY == KEY || HASHTABLE[index] != NULL) {
				HASHTABLE[index] = NULL;
				return true;
			}
			else {
				index = (index + 1) % MAXROWSIZE;
				prober++;
			}

		}
		return false;
}



/*
* _func_ : updateAttribute
* param : string, int, string
* return :	bool
* task : The function will take in the KEY of the Recored, What column we would like to update/change, and the VALUE
*		that we want to change it to
*/
bool table::updateAttribute(string KEY, int columnindex, string VALUE)
{
	for (auto i : HASHTABLE) {

		//If we can find it right away with the hash function.
		if (HASHTABLE[hashbrowns(KEY)]->KEY == KEY) {
			HASHTABLE[hashbrowns(KEY)]->attribute[columnindex] = VALUE;
			return true;
		}
		else {
			//else we will incremnet through the hashtable.
			if (i != NULL) {
				if (i->KEY == KEY) {
					i->attribute[columnindex] = VALUE;
					return true;
				}
			}
		}
	}
	return false;
}



/*
* _func_ : displayTable
* param : int
* task : Display the whole table.
*/
void table::displayTable(int attributeamount)
{
	//Display the headers - ATTRIBUTES/COLUMNS -
	cout << setw(25) << left << tablename << endl;
	cout << setw(25) << left << relation_attr;
	for (int i = 0; i < attributeamount; i++) {

		if (i == 0) {
			cout << setw(20) << left << att[i];
		}
		else if (i == 1 || i == 3) {
			cout << setw(10) << left << att[i];
		}
		else if (i == 2){
			cout << setw(48) << left << att[i];
		}
		else {
			cout << setw(25) << left << att[i];
		}
		
	}
	cout << endl;


	//Display the content table.
	for (auto g : HASHTABLE) {
		if (g != NULL) {
			cout << setw(25) << left << g->KEY;
			for (int i = 0; i < attributeamount; i++) {
				
				if (&g->attribute[i] != NULL) {
					if(i == 0) {
						cout << setw(20) << left << g->attribute[i];
					}
					else if (i == 1 || i == 3) {
						cout << setw(10) << left << g->attribute[i];
					}
					else if (i == 2) {
						cout << setw(48) << left << g->attribute[i];
					}
					else{
						cout << setw(25) << left << g->attribute[i];
					}
				}	
				else {
					cout << setw(25) << left << " ";
				}

			}
			cout << endl;
		}
	}
}


/*
* _func_ : displayRow
* param : string, int
* task : This function display each row depending on key and amount of attributes it contains.
*/
void table::displayRow(string KEY, int attributeamount)
{
	int index = hashbrowns(KEY);
	int prober = 0;

	while (prober < MAXROWSIZE) {
		if (HASHTABLE[index] != NULL) {
			if (HASHTABLE[index]->KEY == KEY) {
				cout << HASHTABLE[index]->KEY;
				for (int i = 0; i < attributeamount; i++) {

					if (&HASHTABLE[index]->attribute[i] != NULL) {
						cout << "|" << HASHTABLE[index]->attribute[i];
					}
					else {
						cout << " ";
					}
				}
			}
			break;
		}
		else {
			index = (index + 1) % MAXROWSIZE;
			prober++;
		}
	}
	cout << endl;
}



/*
* _func_ : displayColumn
* param : int
* task : Display a column of table specified by user
*/
void table::displayColumn(int columnName)
{

	cout << setw(10) << left << tablename << endl;
	cout << setw(10) << left << relation_attr << endl;

	for (auto g : HASHTABLE) {
		if (g != NULL) {
			cout << setw(10) << left << g->KEY;
			if (&g->attribute[columnName] != NULL) {
				cout << setw(10) << left << g->attribute[columnName];
			}
			else {
				cout << setw(10) << left << "			";
			}
			cout << endl;
		}
	}

}



/*
* _func_ : searchfor
* param : string
* return : bool
* task : search the table to see if the Record with the key given is in the HASHTABLE
*/
bool table::searchfor(string KEY) {
	for (auto g : HASHTABLE) {
		if (g != NULL) {
			if (g->KEY == KEY) {
				return true;
			}
		}
	}
	return false;
}



/*
* _func_ : getdisplayOfattr
* return : string
* task : Return a string that is the header for the output file.
*/
string table::getdisplayOfattr() {

	//key first + ','
	string header = this->getRelation_attr() + ",";

	//Go through the attributes list and add it to header  + ","
	for (auto i : att) {
		if (!i.empty()) {
			header = header + i + ",";
		}
	}

	//erase the last ','
	header.erase(header.size() - 1);
	return header;
}



/*
* _func_ : getdisplayOftable
* return : vector<string>  
* task : Return a vector<string> where each index is a Record formatted for output files.
*/
vector<string> table::getdisplayOftable() {
	vector<string> infoTable;
	string temp;

	for (auto g : HASHTABLE) {
		if (g != NULL) {
			temp = g->KEY + "|";
			for (int i = 0; i < 9; i++) {
				if (!g->attribute[i].empty()) {
					temp = temp + g->attribute[i] + "|";	//add '|'
				}

			}
			
			temp.erase(temp.size() - 1);					//erase the last '|'
			infoTable.push_back(temp);
			temp.clear();
		}
	}

	return infoTable;
}



/*
* _func_ : tablesize
* return : int
* task : returns the size of the elements in table.
*/
int table::tablesize() {
	int count = 0;

	for (auto e : HASHTABLE) {
		if (e != NULL) {
			count++;
		}
	}
	return count;
}