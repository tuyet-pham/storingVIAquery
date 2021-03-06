/*
*	potion_game.cpp
*	Written by : Pedro Sanchez, Trevor Kerchner, Tuyet Pham
*	Group Memebers : Pedro Sanchez, Trevor Kerchner, Tuyet Pham
*	Project 2 - 2110 ISLAM
*/



#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "table.h"
#include "resource.h"
#include <sstream>
using namespace std;


string filename = "ingredients.txt";
string filename2 = "potions.txt";
table * mytable[5] = { NULL, NULL, NULL, NULL, NULL };

string menu2();
bool fileReader(fstream&, string);
vector<string> headercutter(string);
vector<string> attributecutter(string);
Record * makeRecord(vector<string> rec);
vector<string> actionCutter(string att);
table * makeTable(fstream&, string);


void INSERT(vector<string>, string, int);
void DELETE(vector<string>, string, int);
void SELECT(vector<string>, string, int);
void UPDATE(vector<string>, string, int);
void WRITE();
void DISPLAY();



int main() 
{
	
	fstream FILE_;
	string filename = menu2();
	fileReader(FILE_, filename);


	return 0;
}


/*
* _func_ : menu2()
* return type : string
* param : none
* task : prompt user to type in there own input file
*/
string menu2() {
	string name;
	cout << "\nPut the file locally and enter the name of .txt file with \".txt\" at the end." << endl;
	cout << " > ";
	cin >> name;
	return name;
}




/*
* _func_ : fileReader()
* return type : bool
* param : fstream, string
* task : take in the file and filename, if fail to open then return.
*		if it doesnt fail to open then continue reading in the tables to 
*		update, select, delete, insert, display & write.
*/
bool fileReader(fstream & file, string filename)
{
	//Testing if input file opens
	file.open(filename.c_str());
	if (file.is_open() == false) {
		return false;
	}

	//potion table
	string tablename1;
	string title1;
	fstream file1;

	//ingred table
	string tablename2;
	string title2;
	fstream file2;
	table table2;			

	string temp;

	file >> title1;
	file >> tablename1;
	file >> title2;
	file >> tablename2;

	//Testing if file1 open
	file1.open(title1.c_str());
	if (file1.is_open() == false) {
		cout << "Fail to open file 1";
		return false;
	}

	//Testing if file2 open
	file2.open(title2.c_str());
	if (file2.is_open() == false) {
		cout << "Fail to open file 2";
		return false;
	}


	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	*
	*	AT THIS POINT : 
	*	We will make the tables with the information given using the function makeTable(), 
	*	then we will store it in a table array name mytable.
	*	After we store it in my table will will then be able to - UPDATE, DELETE, SELECT, etc...
	*
	*//* * * * * * * * * * * * * * * * ** * * * * * * * * * * * * * * * ** * * * * * * * * * * * * * * * ** * * */


	mytable[0] = makeTable(file1, tablename1);
	mytable[1] = makeTable(file2, tablename2);

	getline(file, temp);
	getline(file, temp);
	
	vector<string> actionstring;

	while (getline(file, temp))							
	{
		//Getting a vector of string for each line from actionCutter();
		actionstring = actionCutter(temp);

		if (actionstring[0] == "INSERT") 
		{
			if (actionstring[actionstring.size() - 1] == "," + tablename1) 
			{
				INSERT(actionstring, tablename1, 0);
				actionstring.clear();
			}
			else if (actionstring[actionstring.size() - 1] == "," + tablename2) 
			{
				INSERT(actionstring, tablename2, 1);
				actionstring.clear();
			}
		}
		else if (actionstring[0] == "UPDATE") 
		{
			if (actionstring[actionstring.size() - 1] == "," + tablename1) 
			{
				UPDATE(actionstring, tablename1, 0);
				actionstring.clear();

			}
			else if (actionstring[actionstring.size() - 1] == "," + tablename2) 
			{
				UPDATE(actionstring, tablename2, 1);
				actionstring.clear();
			}
		}
		else if (actionstring[0] == "SELECT") 
		{
			if (actionstring[actionstring.size() - 1] == "," + tablename1)
			{
				SELECT(actionstring, tablename1, 0);
				actionstring.clear();
			}
			else if (actionstring[actionstring.size() - 1] == "," + tablename2)
			{
				SELECT(actionstring, tablename2, 1);
				actionstring.clear();
			}
		}
		else if (actionstring[0] == "DELETE") {
			if (actionstring[actionstring.size() - 1] == "," + tablename1)
			{
				DELETE(actionstring, tablename1, 0);
				actionstring.clear();
			}
			else if (actionstring[actionstring.size() - 1] == "," + tablename2)
			{
				DELETE(actionstring, tablename2, 1);
				actionstring.clear();
			}
		}
		else if (actionstring[0] == "WRITE") 
		{
			WRITE();
		}
		else if (actionstring[0] == "DISPLAY") 
		{
			DISPLAY();
		}
	}


	file.close();
	file1.close();
	file2.close();

	return true;
}






/*
* _func_ : makeTable()
* return type : table * 
* param : file, string
* task : Takes in the table name, and the file of the table that we want to make stuff with. 
*/
table * makeTable(fstream & file, string tablename) {
	
	table * TABLE = new table;
	int count = 0;								//To keep track of what line we are on in the files, will be reused.
	vector<string> attributes_header;			//To store the headers of each table 
	vector<string> attributes_;					//To store the attributes(columns) of each record. 
	TABLE->setTableName(tablename);				//Setting table name
	string temp;

	//MAKING TABLE FROM FILE1 - I.E. INGREDIENT TABLE OR POTION TABLE
	while (getline(file, temp))
	{
		if (count == 0)
		{
			TABLE->setRelation_attr(temp);						//index [0] of each file is the key, so will will do that first.						
		}
		else if (count == 1)									//index [1] of each file is the column name/header/attribute of each table.
		{
			attributes_header = headercutter(temp);				//function call to headercutter() to cut up the string. Vector in return.
			for (int i = 0; i < attributes_header.size(); i++)
			{
				TABLE->addAttribute(attributes_header[i], i);	//Set each index i of attribute_header at the same index i of the table.
			}
		}
		else if (count > 1)										//The rest of the indexes are the information for the table - rows/elements.
		{
			attributes_ = attributecutter(temp);				//function call to attributecutter() to cut up the string. Vector in return.
			Record * item = makeRecord(attributes_);			//Once we got the vector from attributecutter() we will then send it to makeRecord() 
			TABLE->makeRecord(*item);							//and get a record in return to store it in thr table.
			attributes_.clear();								//Clear because it will be resused for the rest of the file. 
		}
		count++;
	}
	return TABLE;
}




/*
* _func_ : headercutter()
* return type : vector<string>
* param : string 
* task : Take in a string. The strings that is being sent in are the headers i.e. COLUMNS for each table.
*		example -----> "ID,NAME,TYPE,EFFECT,COST,INGREDIENT1,INGREDIENT2" <-------
*		It will then return a vector of the header to later to add to the table.
*/
vector<string> headercutter(string header)
{
	vector<string> vec_attrrib;
	string::iterator it = header.begin();

	//Take out ',' and replace with ' '
	for (; it != header.end(); it++) {
		if ((*it) == ',') {
			(*it) = ' ';
		}
	}
	int count = 0;
	istringstream stringd(header);
	string temp;
	while (getline(stringd, temp, ' ')) {

		//We do not take in the KEY which is index [0] of header.
		if (count == 0) {
		}
		else {
			vec_attrrib.push_back(temp);
		}
		count++;
	}
	return vec_attrrib;

}


/*
* _func_ : attributecutter()
* return type : vector<string>
* param : string
* task : Take in a string. The strings that is being sent in are the following lines after line 2 of each table.
*		example -----> "23|Cure Disease|Cure|Cures all diseases.|79|Vampire Dust|Charred Skeever Hide" <-------
*		It will then return a vector of the attributes to later make the record for the table.
*/
vector<string> attributecutter(string att)
{
	vector<string> vec_attrrib;
	string::iterator it = att.begin();

	//Take out '|' and replace with '~'
	for (; it != att.end(); it++) {
		if ((*it) == '|') {
			(*it) = '~';
		}
	}

	istringstream stringd(att);
	string temp;
	while (getline(stringd, temp, '~')) {
		vec_attrrib.push_back(temp);
	}
	return vec_attrrib;
}

/*
* _func_ : makeRecord()
* return type : Record
* param : vector<string> rec
* task : Take in a vector that contains the attribute of the Record -> Make the Record -> Send the record back.
*/
Record * makeRecord(vector<string> rec)
{
	//Allocating memory for new record
	Record * item = new Record();

	for (int i = 0; i < rec.size(); i++)
	{
		if (i == 0) {		
			//The first index is always going to be the key
			item->KEY = rec[i];
		}
		else if(i > 0) {
			item->attribute[i-1] = rec[i];
		}
	}
	return item;
}


/*
* _func_ : actionCutter()
* return type : vector<string>
* param : string
* task : To cut up the strings that contains the manipulations(SELECT, INSERT, DELETE, ETC...) of the tables.
		Then put each string into a vector and send the vector back.
*/
vector<string> actionCutter(string att)
{
	vector<string> vec_attrrib;
	string::iterator it = att.begin();

	//Replacing characters with '~'
	for (; it != att.end(); it++) 
	{
		if ((*it) == '(') {
			(*it) = '~';
		}
		else if ((*it) == '|') {
			(*it) = '~';					
		}
		else if ((*it) == ')'){
			(*it) = '~';
		}
	}

	istringstream stringd(att);
	string temp;

	//Storing string by deliminator '~'
	//If the size of the string is 0 then don't store.
	while (getline(stringd, temp, '~')) {

		if(temp.size() == 0){
		}
		else {
			vec_attrrib.push_back(temp);
		}
	}

	return vec_attrrib;
}


/*
* _func_ : display()
* task : To display both tables.
*/
void DISPLAY() {

	cout << "\n\n";
	mytable[1]->displayTable(9);
	cout << "\n\n";
	mytable[0]->displayTable(9);
}


/*
* _func_ : INSERT()
* param : vector<string>, string, tableindex
* task : Insert new record to table from actionstring vector.
*/
void INSERT(vector<string> actionstring, string tablename, int tableindex)
{
	actionstring.erase(actionstring.begin());
	actionstring.erase(actionstring.end() - 1);

	Record * item = makeRecord(actionstring);

	if (mytable[tableindex]->makeRecord(*item) == -3)
	{
		cout << item->KEY << " failed to insert into " << tablename << "." << endl;
	}
	else if (mytable[tableindex]->makeRecord(*item) != -3 || mytable[tableindex]->makeRecord(*item) != -1)
	{
		cout << item->KEY << " inserted into " << tablename << "." << endl;
	}
}


/*
* _func_ : DELETE()
* param : vector<string>, ,tablename, tableindex
* task : Delete record from table from actionstring vector.
*/
void DELETE(vector<string> actionstring, string tablename, int tableindex)
{
	bool deleted;
	actionstring.erase(actionstring.begin());
	actionstring.erase(actionstring.end() - 1);
	deleted = mytable[tableindex]->deleteRecord(actionstring[0]);
	if (deleted == true)
	{
		cout << actionstring[0] << " deleted from " << tablename << "." << endl;
	}
	else if (deleted == false)
	{
		cout << actionstring[0] << " fail to delete from " << tablename << "." << endl;
	}
}



/*
* _func_ : SELECT()
* param : vector<string>, string, tableindex
* task : Select record to table from actionstring vector and then console out the record.
*
*/
void SELECT(vector<string> actionstring, string tablename, int tableindex)
{
	actionstring.erase(actionstring.begin());
	actionstring.erase(actionstring.end() - 1);

	if (mytable[tableindex]->searchfor(actionstring[0]) == false) {
		cout << actionstring[0] << " failed to be selected in " << tablename << ", doesn't exist. " << endl;
	}
	else {
		mytable[tableindex]->displayRow(actionstring[0], actionstring.size());
	}
}


/*
* _func_ : UPDATE()
* param : vector<string>, string, tableindex
* task : Update record with actionstring vector. If exist. 
*
*/
void UPDATE(vector<string> actionstring, string tablename, int tableindex)
{
	bool update;
	actionstring.erase(actionstring.begin());
	actionstring.erase(actionstring.end() - 1);

	for (int i = 1; i < actionstring.size(); i++)
	{
		update = mytable[tableindex]->updateAttribute(actionstring[0], i - 1, actionstring[i]);
	}

	if (update == true)
	{
		cout << actionstring[0] << " updated in " << tablename << "." << endl;
	}
	else if (update == false)
	{
		cout << actionstring[0] << " failed to update in " << tablename << "." << endl;
	}

}


/*
* _func_ : WRITE()
* task :	Write out to 2 .txt files.
*/
void WRITE()
{
	string fileout1 = "potionOUT.txt";
	string fileout2 = "ingredientOUT.txt";
	ofstream outFILE_1;
	ofstream outFILE_2;
	vector<string> info;


	outFILE_1.open(fileout1.c_str());
	outFILE_1 << mytable[0]->getRelation_attr() << endl;
	outFILE_1 << mytable[0]->getdisplayOfattr() << endl;
	info = mytable[0]->getdisplayOftable();
	
	for (auto g : info) {
		outFILE_1 << g << "\n";
	}

	info.clear();

	outFILE_2.open(fileout2.c_str());
	outFILE_2 << mytable[1]->getRelation_attr() << endl;
	outFILE_2 << mytable[1]->getdisplayOfattr() << endl;
	info = mytable[1]->getdisplayOftable();

	for (auto g : info) {
		outFILE_2 << g << "\n";
	}
	info.clear();

	outFILE_2.close();
	outFILE_1.close();
}
