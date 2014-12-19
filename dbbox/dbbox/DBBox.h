#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <db_cxx.h>
//#pragma comment(lib, "libdb61.lib")


void print_error(int ret)
{
	if(ret != 0)
		printf("ERROR: %s\n",db_strerror(ret));
}

void initpdb_T(DBT * key, DBT * data)
{
	memset(key, 0, sizeof(DBT));
	memset(data, 0, sizeof(DBT));
}

typedef struct MyData
{
	int  value;
	char name[256];
} CUSTOMER;

class DBBox
{
public:
	DBBox(const char* path, const char* name)
		: name_(name), path_(path), db_(NULL, 0)
	{}

	inline void init()
	{
		if (true){
			_createpdb_();
		}
	}
	inline Db &getDb(){return db_;}

	void put(int id, std::string name)
	{
		Dbt key(&id, sizeof(id));
		char tmp[100] = {0};
		strcpy(tmp, name.c_str());
		Dbt data(tmp, strlen(tmp)+1);
		db_.put(NULL, &key, &data, 0);
	}

	void get(int id, std::string name)
	{
		Dbt key(&id, sizeof(id));
		char tmp[100] = {0};
		strcpy(tmp, name.c_str());
		Dbt data(tmp, strlen(tmp)+1);
		db_.put(NULL, &key, &data, 0);
	}

private:

	void _createpdb_()
	{
		int ret = -1;
		try
		{
			db_.set_error_stream(&std::cerr);
			ret = db_.open(NULL, name_.c_str(), NULL, DB_BTREE, DB_CREATE, 0); 
			print_error(ret);
			if(!ret) {
				return ;
			}
			db_.close(0);
			return;
		}
		catch(DbException &e)
		{
			std::cerr << "db open err" << name_ << std::endl;
			std::cerr << e.what() << std::endl;
		}
	}

	Db db_;
	std::string name_;
	std::string path_;
	u_int32_t   flags_;
};
