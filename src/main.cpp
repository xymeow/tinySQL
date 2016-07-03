#include <iostream>
#include <string>
#include "interpreter.h"
#include "catalog.h"
using namespace std;
string CURRENT_DB;

void initDb(){
	CURRENT_DB = "default";
	if(!isDatabaseExist(CURRENT_DB)){
		createDatabase(CURRENT_DB);
	}
}

int main(){

	string query;
	string line;//一行输入
	
	//init db
	initDb();
	

	cout<<"tiniSql>";//命令行提示
	getline(cin,line);
	query = "";

	while(true){
		trim(line);//去除首尾空白符
		int terminate_pos = line.find_first_of(';');
		if(terminate_pos==-1){ //多行输入
			query += " ";
			query += line;	
			cout<<"      ->";
			getline(cin,line);
		}else{
			query += line.substr(0,terminate_pos);//生成query
			line = line.substr(terminate_pos+1);
			//cout<<"This query:"<<query<<endl;
			//cout<<"Left:"<<line<<endl;
			trim(query);
			doOneQuery(query); //执行query
			if(line==""){//若line=""则语句已被解析完
				cout<<"MiniSql>";
				getline(cin,line);
			}
			query="";//循环
		}

	}
	return 0;

}


