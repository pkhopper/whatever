#ifndef _BDBBOX_BDB_DB_INTERFACE_H_
#define _BDBBOX_BDB_DB_INTERFACE_H_

#include "types.h"

namespace bdbutil
{

	class DBInterface
	{
	public:
		DBInterface(void);
		virtual ~DBInterface(void);
		virtual int Setup(std::string name, DbEnv *pEnv=NULL)
		{
			_pEnv = pEnv;
			_name = name;
			++_initialized;
		}
		virtual int Open();
		virtual int Close();
		bool isInitialized()
		{
			return _initialized > 0;
		}
	protected:
		Db          *_pDb;
		DbEnv       *_pEnv;
		std::string  _name;
		int          _initialized;
	};

	DBInterface::DBInterface() : _pDb(NULL), _pEnv(NULL), _initialized(-1)
	{

	}

	DBInterface::~DBInterface()
	{
		Close();
	}

}// eof bdbutil
#endif // eof _BDBBOX_BDB_DB_INTERFACE_H_