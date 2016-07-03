#ifndef __RECORD_H__
#define __RECORD_H__
#include "table.h"
#include <string>

extern string CURRENT_DB;

struct Record{
	vector<Attr> attrs;
	int length;
	vector<string> data;
	Record (){}
	Record (vector<Attr> _attrs, int _length, vector<string> _data){
		attrs = _attrs;
		length = _length;
		data = _data;
	}
};

int insertRecord(Table table, Record record);

vector<Record> selectAllRecords(Table table, vector<Attr> attrs);

int selectRecords(Table table, vector<string> attrs, vector<Condition> conditions, vector<Record>* records);

int deleteAllRecords(Table table);

int deleteRecords(Table table, vector<Condition> conditions);



#endif
