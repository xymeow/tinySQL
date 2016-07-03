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

int deleteAllRecords(Table table){ //删除表中全部数据，只要不以追加模式打开文件就好了
	ofstream table_data;
	string table_data_path = getTableDataPath(CURRENT_DB, table.tname);
	table_data.open(table_data_path.c_str());
	table_data.close();
}

int deleteRecords(Table table, vector<Condition> conditions){
	Buffer buffer = getData(CURRENT_DB, table.tname);
	vector<string> data;
	vector<string> tmp;
	stringstream ss;
	bool delMark[buffer.data.size()];
	for (int i = 0; i < buffer.data.size(); i ++)
		delMark[i] = true;
	for (int i = 0; i < conditions.size(); i++) {
		int iattr;
		string stmp = conditions[i].value;
		data.clear();
		for (int j = 0; j < table.attr_num; j ++)
			if (table.attrs[j].attr_name == conditions[i].attr_name)
				iattr = j;
		for(int j = 0; j < buffer.data.size(); j ++) {
			tmp.clear();
			string bl = " ";
			split(buffer.data[j], bl, &tmp);
			int itmp = atoi(tmp[iattr].c_str());
			int itmp2 = atoi(conditions[i].value.c_str());
			if (delMark[j]){
				switch(conditions[i].op) {
					case 0: // =
						if (tmp[iattr] == conditions[i].value) 
							delMark[j] = true;
						else
							delMark[j] = false;
						break;
					case 1: // <>
						if (tmp[iattr] != conditions[i].value)
							delMark[j] = true;
						else
							delMark[j] = false;
						break;
					case 2: // <
						if (itmp < itmp2)
							delMark[j] = true;
						else
							delMark[j] = false;
						break;
					case 3: //>
						if (itmp > itmp2)
							delMark[j] = true;
						else
							delMark[j] = false;
						break;
					case 4://<=
						if (itmp <= itmp2)
							delMark[j] = true;
						else
							delMark[j] = false;
						break;
					case 5: // >=
						if (itmp >= itmp2)
							delMark[j] = true;
						else
							delMark[j] = false;
						break;
					default: //undefined
						cout<<"undefined operation!"<<endl;
						return -1;
				}
			}
			

			// int j;
		}
		// buffer.data = data;
	}
	for (int i = 0; i < buffer.data.size(); i ++) {
		if (!delMark[i])
			data.push_back(buffer.data[i]);
	}
	buffer.data = data;

	ofstream table_data;
	string table_data_path = getTableDataPath(CURRENT_DB, table.tname);
	// cout<<CURRENT_DB<<endl;
	table_data.open(table_data_path.c_str());// 打开文件

	for (int i = 0; i < buffer.data.size(); i ++){
		// cout<<buffer.data[i]<<endl;
		table_data<<buffer.data[i]<<endl;
	}
	table_data.flush();
	table_data.close();
	return 0;
}
