#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include "catalog.h"
#include "table.h"
#include "record.h"

using namespace std;

int insertRecord(Table table, Record record){
	ofstream table_data;
	string table_data_path = getTableDataPath(CURRENT_DB, table.tname);
	// cout<<CURRENT_DB<<endl;
	table_data.open(table_data_path.c_str(), ios::app);// 打开文件

	for (int i = 0; i < record.length; i ++)
		table_data<<record.data[i]<<" ";
	table_data<<endl;
	table_data.flush();
	table_data.close();
	return 0;
}


vector<Record> selectAllRecords(Table table, vector<Attr> attrs){

}

vector<Record> selectRecords(Table table, vector<Attr> attrs, vector<Condition> conditions){
}

int deleteAllRecords(Table table){
}

int deleteRecords(Table table, vector<Condition> conditions){
}
