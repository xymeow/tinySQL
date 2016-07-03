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

vector<Record> selectRecords(Table table, vector<Attr> attrs, vector<Condition> conditions);

int deleteAllRecords(Table table);

int deleteRecords(Table table, vector<Condition> conditions);



#endif
