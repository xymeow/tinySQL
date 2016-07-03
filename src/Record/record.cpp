#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include "catalog.h"
#include "table.h"
#include "record.h"
#include "buffer.h"
#include "interpreter.h"

using namespace std;

int insertRecord(Table table, Record record){
	Buffer buffer = getData(CURRENT_DB, table.tname);
	if (table.primarykey_column != "") { //检查主键约束
		int ikey = -1;
		for (int i = 0; i < table.attr_num; i ++)
			if (table.attrs[i].attr_name == table.primarykey_column)
				ikey = i;
		vector<string> tmp;
		for(int i = 0; i < buffer.data.size(); i ++) {
			tmp.clear();
			string bl = " ";
			split(buffer.data[i], bl, &tmp);
			// int j;
			if (record.data[ikey] == tmp[ikey]) {
				cout<<"primary key can not be duplicate!"<<endl;
				return -1;
			}
		}
	}
	string tmp;
	for (int i = 0; i < record.length; i++){
		tmp += record.data[i];
		tmp += " ";
	}
	trim(tmp);
	for (int i = 0; i < buffer.data.size(); i ++) {
		if (buffer.data[i] == tmp) {
			cout<<"record has existed!"<<endl;
			return -1;
		}
	}
	
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


// vector<Record> selectAllRecords(Table table, vector<Attr> attrs){

// }

int selectRecords(Table table, vector<string> attrs, vector<Condition> conditions, vector<Record>* records){
	Buffer buffer = getData(CURRENT_DB, table.tname);
	vector<int> mask;
	bool find = false;
	for (int i = 0; i < attrs.size(); i ++) { //获取attrs中属性在table.attrs中的下标
		for (int j = 0; j < table.attrs.size(); j ++) {
			if (attrs[i] == table.attrs[j].attr_name) {
				mask.push_back(j);
				find = true;
				break;
			}

		}
		if (!find) {
			cout<<"attribute "<<attrs[i]<<" not exists in this table!"<<endl;
			return -1;
		}
		find = false;
	}
	int cnum = 0;
	for (int i = 0; i < attrs.size(); i ++){
		cnum += attrs[i].size();
		cnum += 8;
	}
	for (int i = 0; i < mask.size(); i ++){
		cout<<"\t"<<table.attrs[mask[i]].attr_name;
	}
	cout<<endl;
	for (int i = 0; i < cnum; i++)
		cout<<"-";
	cout<<endl;
	vector<string> tmp;
	if (conditions.size() == 0) { // 无条件

		for(int i = 0; i < buffer.data.size(); i ++) {
			tmp.clear();
			string bl = " ";
			split(buffer.data[i], bl, &tmp);
			for (int j = 0; j < mask.size(); j ++) {
				cout<<"\t"<<tmp[j];
			}
			cout<<endl;
			// int j;
		}
	}
	return 0;
}

// int deleteAllRecords(Table table){
// }

int deleteRecords(Table table, vector<Condition> conditions){
}
