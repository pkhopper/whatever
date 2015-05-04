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

}// eof bdbutil
#endif // eof _BDBBOX_BDB_ENV_H_