#ifndef _BDBBOX_BDB_DB_H_
#define _BDBBOX_BDB_DB_H_

#include "types.h"

namespace bdbutil
{

	// for dbt memory set
#define MAKEDBT(dbt,var)                    Dbt dbt(&(var), sizeof(var));
#define MAKEDBT_DBTMALLOC (dbt,ptr,size)    Dbt dbt(ptr,size);dbt.set_flags(DB_DBT_MALLOC);
#define MAKEDBT_USERMALLOC(dbt,ptr,size)    Dbt dbt;dbt.set_flags(DB_DBT_USERMEM);dbt.set_data(ptr);dbt.set_ulen(size);

	// for member offset
#if LINUX
#define CLASS_OFFSET(S,M) (unsigned int)((ptrdiff_t)&(((S*)0)->M))
#define CLASS_MEMBER_SIZE(S,M) sizeof(((S*)0)->M)
#else
#define CLASS_OFFSET(S,M) (unsigned int)((ptrdiff_t)&(((S*)0)->M))
#define CLASS_MEMBER_SIZE(S,M) sizeof(((S*)0)->M)
#endif 

	// for error print
	inline char *BDBErrStr(int bdb_errno)
	{
		return DbEnv::strerror(bdb_errno);
	}

	// close a db handler
	int DbClose(Db *pDb)
	{
		assert(pDb);
		pDb->sync(0);
		pDb->close(0);
	}

}// eof bdbutil
#endif // eof _BDBBOX_BDB_DB_H_