#ifndef _BDBBOX_BDB_DB_H_
#define _BDBBOX_BDB_DB_H_

#include "types.h"

namespace bdbutil
{

	// close a db handler
	int DbClose(Db *pDb)
	{
		assert(pDb);
		pDb->sync(0);
		pDb->close(0);
	}

}// eof bdbutil
#endif // eof _BDBBOX_BDB_DB_H_