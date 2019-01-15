/*
*	table.h
*	Written by : Tuyet Pham 
*	Group Memebers : Pedro Sanchez, Trevor Kerchner, Tuyet Pham
*	Project 2 - 2110 ISLAM
*
*	table.h : Acts like any other table with rows and columns. 
*	The max size of the rows is 50 and the max size of columns is 15. The sizees are currently non expandable. 
*	
*
*/



#ifndef TABLE_
#define TABLE_

#include <iostream>
#include <iomanip>
#include <string>
#include "resource.h"
#include <vector>
using namespace std;


class table
{	
private:
	static const int MAXROWSIZE = 50;						//Max row size
	static const int MAXCOLUMNSIZE = 15;					//Max column size
	string relation_attr;									//What column will represent the 'KEY'
	string tablename;										//Store the name of Table
	Record * HASHTABLE[MAXROWSIZE];							//An Array of Record pointers. The contents of our table. 
	int hashbrowns(string KEY);								//Hash Function
	bool KEY_SET = false;									//This is to ensure the relation_attr is only set once.
	string att[MAXCOLUMNSIZE];								//A string array that holds the attributes/column title of each table.
	 
public:
	// Constructors
	table();
	table(string tableName);
	table(string tableName, string key);

	// To Set/Get the "key" value
	bool setRelation_attr(string key);
	string getRelation_attr();

	//To set and get the attribute
	bool addAttribute(string attribute, int index);
	bool deleteAttribute(string attribute);


	// To Set/Get the tablename
	void setTableName(string tablename);
	string getTableName();

	//To make and delete a record.
	int makeRecord(Record &newRec);
	bool deleteRecord(string KEY);

	//To set the attribute values or getting the attribute value.
	bool updateAttribute(string KEY, int columnIndex, string VALUE);

	//displays functions
	void displayTable(int attributeamount);
	void displayRow(string KEY, int attributeamount);
	void displayColumn(int columnName);

	//Display for output files.
	string getdisplayOfattr();
	vector<string> getdisplayOftable();

	//Return the table size
	int tablesize();

	//Search for key
	bool searchfor(string KEY);
	
};

#endif // !TABLE_
