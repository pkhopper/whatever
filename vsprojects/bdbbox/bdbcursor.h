#ifndef _BDBBOX_BDB_CURSOR_H_
#define _BDBBOX_BDB_CURSOR_H_

#include "types.h"

namespace bdbutil
{

	// safe dbd
	class SafeCursor
	{
	public:
		explicit SafeCursor(Dbc *dbc) : _pDbc(dbc)
		{
			assert(dbc);
		}

		~SafeCursor()
		{
			if (_pDbc)
			{
				_pDbc->close();
				_pDbc = NULL;
			}
		}

		Dbc *GetDbc() 
		{
			return _pDbc; 
		}

		Dbc operator *() 
		{ 
			return GetDbc(); 
		}

		Dbc* operator ->() 
		{ 
			return GetDbc(); 
		}

		operator Dbc* operator !() 
		{ 
			return GetDbc() == NULL; 
		}

	private:
		Dbc *_pDbc;
	};

}// eof bdbutil
#endif // eof _BDBBOX_BDB_CURSOR_H_