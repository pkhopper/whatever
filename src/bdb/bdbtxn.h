#ifndef _BDBBOX_BDB_TXN_H_
#define _BDBBOX_BDB_TXN_H_

#include <db_cxx.h>

namespace bdbutil
{


	inline DbTxn *MakeTxn(DbEnv *pEnv)
	{
		DbTxn *tid = NULL;
		try
		{
			int ret = pEnv->txn_begin(NULL, &tid, 0);
			if(ret != 0)
			{
				pEnv->err(ret, "MakeTxn()");
				return NULL;
			}
		}
		catch(DbException &dbe)
		{
			pEnv->err(dbe.get_errno(), "MakeTxn()");
		}
		return tid;
	}


	class SafeDbTxn
	{
	private:
		DbTxn  *m_tid;
	public:
		explicit SafeDbTxn(DbTxn *tid) : m_tid(tid) {}
		
		~SafeDbTxn()
		{
			abort();
		}
		DbTxn *GetTxn()
		{
			return m_tid;
		}
		operator DbTxn *()
		{
			return GetTxn();
		}
		bool operator !()
		{
			return GetTxn() == NULL;
		}
		void abort()
		{
			if(m_tid)
			{
				m_tid->abort();
				m_tid = NULL;
			}
		}
		void commit()
		{
			if(m_tid)
			{
				m_tid->commit(0);
				m_tid = NULL;
			}
		}
	};








}// eof bdbutil
#endif // eof _BDBBOX_BDB_TXN_H_