#ifndef _BDBBOX_BDB_TYPES_H_
#define _BDBBOX_BDB_TYPES_H_

#include <assert.h>
#include <db_cxx.h>


namespace bdbutil
{

// return values
#define DB_OK         0
#define DB_UNKNOWN    -1
#define DB_BAD_PARAM  -2



	inline char *BDBErrStr(int bdb_errno)
	{
		return DbEnv::strerror(bdb_errno);
	}

}// eof bdbutil
#endif // eof _BDBBOX_BDB_ENV_H_