#ifndef __BUFFER_H__
#define __BUFFER_H__
#include <iostream>
#include <string>
#include "table.h"
// #include "database.h"
using namespace std;

// class Buffer {
// 	Buffer(vector<Attr> attrs, int alength, string dbname, string tname, vector<string> data){
// 		this.attrs = attrs;
// 		this.alength = alength;
// 		this.tname = tname;
// 		this.data = data;
// 		this.dbname = dbname;
// 	}
// public:
// 	vector<Attr> attrs;
// 	int alength;
// 	string tname;
// 	vector<string> data;
// 	string dbname;
// 	int totalLen;
// 	// Buffer(){}
	
// };
struct Buffer{
	vector<Attr> attrs;
	int alength;
	string tname;
	vector<string> data;
	string dbname;
	int totalLen;
	Buffer(){};
	Buffer(vector<Attr> attrs, int alength, vector<string> data){
		attrs = attrs;
		alength = alength;
		data = data;
	};
};

#endif