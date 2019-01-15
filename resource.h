/*
*	resource.h
*	Written by : Tuyet Pham
*	Group Memebers : Pedro Sanchez, Trevor Kerchner, Tuyet Pham
*	Project 2 - 2110 ISLAM
*/


#ifndef _RECORD_
#define _RECORD_

typedef struct Record {
	static const int MAXCOLUMNSIZE = 15;
	std::string KEY;
	std::string attribute[MAXCOLUMNSIZE];
} Record;

#endif