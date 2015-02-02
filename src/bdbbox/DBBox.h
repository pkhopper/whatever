#ifndef _BDBBOX_BDBBOX_H_ 
#define _BDBBOX_BDBBOX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <db_cxx.h>
#include <assert.h>
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

class SafeDbTxn
{
public:
	SafeDbTxn(DbTxn* ptxn) : ptxn_(ptxn) {
	}

	~SafeDbTxn() {
		abort();
	}

	inline DbTxn* getTxn() {
		return ptxn_;
	}

	inline void abort() {
		if (ptxn_){
			ptxn_->abort();
			ptxn_ = NULL;
		}
	}
	
	inline void commit() {
		if (ptxn_){
			ptxn_->commit(0);
			ptxn_ = NULL;
		}
	}
protected:
	DbTxn* ptxn_;
};

inline int TxnBegin(DbEnv *pEnv, DbTxn **tid) {
	assert(pEnv);
	assert(tid);
	return pEnv->txn_begin(NULL, tid, 0);
}

inline int TxnBegin(DbEnv *pEnv) {
	assert(pEnv);
	DbTxn *tid = NULL;
	try{
		return TxnBegin(pEnv, &tid);
	}catch (DbException& e) {
		pEnv->err(e.get_errno(), "TxnBegin");
	}
}

class DBBox
{
public:
	DBBox(const char* path, const char* name)
		: name_(name), path_(path), pdb_(NULL), penv_(NULL)
	{}

	inline void init()
	{
		if (true){
			_createpdb_();
		}
	}
	inline Db *getDb(){return pdb_;}

	void put(int id, std::string name)
	{
		assert(pdb_);
		Dbt key(&id, sizeof(id));
		char tmp[100] = {0};
		strcpy(tmp, name.c_str());
		Dbt data(tmp, strlen(tmp)+1);
		pdb_->put(NULL, &key, &data, 0);
	}

	void get(int id, std::string name)
	{
		Dbt key(&id, sizeof(id));
		char tmp[100] = {0};
		strcpy(tmp, name.c_str());
		Dbt data(tmp, strlen(tmp)+1);
		pdb_->put(NULL, &key, &data, 0);
	}

private:

	void _createpdb_()
	{
		int ret = -1;
		try
		{
			pdb_->set_error_stream(&std::cerr);
			ret = pdb_->open(NULL, name_.c_str(), NULL, DB_BTREE, DB_CREATE, 0); 
			print_error(ret);
			if(!ret) {
				return ;
			}
			pdb_->close(0);
			return;
		}
		catch(DbException &e)
		{
			std::cerr << "db open err" << name_ << std::endl;
			std::cerr << e.what() << std::endl;
		}
	}

	Db     *pdb_;
	DbEnv  *penv_;
	std::string name_;
	std::string path_;
	u_int32_t   flags_;
};

#endif // eof _BDBBOX_BDBBOX_H_
