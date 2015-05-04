#ifndef _BDBBOX_BDB_CNM_H_
#define _BDBBOX_BDB_CNM_H_

#include "db_base.h"

// NDK: non-duplicate-key_ptr
// DK: duplicate-key_ptr
namespace bdbutil
{
	// macros for err print
#if __PRINT_BDB_ERR_STR
#define DBD_ERR_PRINT(db_ptr,e_ref)    db_ptr->err(e_ref.get_errno(), "%s,%s", __FILE__, __LINE__);
#else
#define DBD_ERR_PRINT(E)
#endif

	template<typename PairT, typename KeyT>
	int GetByKey(Db *pdb_ptr, DbTxn *txnPtr, const KeyT *key_ptr, PairT *pair_out_ptr)
	{
		assert(pdb_ptr);
		assert(txnPtr);
		assert(pair_out_ptr);
		try
		{
			pair_out_ptr->key_ptr = *key_ptr;
			MAKEDBT_DBTMALLOC(QkEY, &(pair_out_ptr->_key), CLASS_MEMBER_SIZE(PairT, _key));
			MAKEDBT_DBTMALLOC(DATA, &(pair_out_ptr->_value), CLASS_MEMBER_SIZE(PairT, _value));
			return pdb_ptr->get(txnPtr, &QKEY, &DATA, 0);
		}
		catch (DbException &e)
		{
			DBD_ERR_PRINT(pdb_ptr,e);
			return e.get_errno();
		}
	}

	// update, create a pair
	template<typename PairT, typename KeyT>
	int Update(Db *pdb_ptr, DbTxn *txnPtr, PairT *pairPtr)
	{
		assert(pdb_ptr);
		assert(txnPtr);
		try
		{
			pairPtr->key_ptr = key_ptr;
			MAKEDBT_DBTMALLOC(QkEY, &(pairPtr->_key), CLASS_MEMBER_SIZE(PairT, _key));
			MAKEDBT_DBTMALLOC(DATA, &(pairPtr->_value), CLASS_MEMBER_SIZE(PairT, _value));
			return pdb_ptr->put(txnPtr, &QKEY, &DATA, 0);
		}
		catch (DbException &e)
		{
			DBD_ERR_PRINT(pdb_ptr,e);
			return e.get_errno();
		}
	}

	// delete
	template<typename KeyT>
	int Delete(Db *pdb_ptr, DbTxn *txnPtr, KeyT *key_ptr)
	{
		assert(pdb_ptr);
		assert(txnPtr);
		try
		{
			MAKEDBT_DBTMALLOC(QkEY, &(key_ptr), sizeof(key_ptr));
			return pdb_ptr->del(txnPtr, &QKEY, 0);
		}
		catch (DbException &e)
		{
			DBD_ERR_PRINT(pdb_ptr,e);
			return e.get_errno();
		}
	}

	template<typename KeyT>
	int KeyExists(Db *pdb_ptr, DbTxn *txnPtr, const void *key_ptr, int len)
	{
		assert(pdb_ptr);
		assert(txnPtr);
		assert(key_ptr);
		try
		{
			MAKEDBT_DBTMALLOC(QkEY, key_ptr, len);
			return pdb_ptr->exists(txnPtr, &QKEY, 0);
		}
		catch (DbException &e)
		{
			DBD_ERR_PRINT(pdb_ptr,e);
			return e.get_errno();
		}
	}

	template<typename KeyT>
	int SafeDelete(Db *pdb_ptr, DbTxn *txnPtr, KeyT *key_ptr)
	{
		assert(pdb_ptr);
		assert(txnPtr);
		assert(key_ptr);

		int ret = bdbutil::KeyExists(pdb_ptr, txnPtr, key_ptr);
		if (ret != DB_OK)
		{
			return ret;
		}

		try
		{
			MAKEDBT_DBTMALLOC(QkEY, &(key_ptr), sizeof(key_ptr));
			return pdb_ptr->del(txnPtr, &QKEY, 0);
		}
		catch (DbException &e)
		{
			DBD_ERR_PRINT(pdb_ptr,e);
			return e.get_errno();
		}
	}

	// get pairs from btree
	template<typename PairT, typename KeyT>
	int GetArrayByDupPKey(Db *dbPtr, DbTxn *txnPtr, KeyT *key_ptr, PairT *pair_array_ptr, unsigned int count_ptr)
	{
		assert(dbPtr);
		assert(txnPtr);
		assert(key_ptr);
		assert(pair_array_ptr);

		int ret = DB_UNKNOWN;
		Dbc* pdbc = NULL;
		unsigned int count = 0;
		int flag = DB_SET;

		try
		{
			if ((ret = (dbPtr->cursor(txnPtr, &pdbc, 0)) != DB_OK))
			{
				return ret;
			}

			SafeCursor sc(pdbc);

			for (; ; ++count)
			{
				if (count > *count_ptr)
				{
					return DB_BAD_PARAM;
				}
				auto pairPtr = pair_array_ptr[count];
				MAKEDBT_DBTMALLOC(QkEY, key_ptr, CLASS_MEMBER_SIZE(PairT, _key));
				MAKEDBT_DBTMALLOC(DATA, &(pairPtr->_value), CLASS_MEMBER_SIZE(PairT, _value));
				ret = sc->get(txnPtr, &QKEY, &DATA, count > 0 ? DB_NEXT_DUP: DB_SET);
				switch (ret)
				{
				case DB_OK:
					break;
				case DB_NOTFOUND:
					if (count > 0)
					{
						*count_ptr = count;
						return DB_OK;
					}
					return ret;
				default:
					return ret;
				}
			}
		}
		catch (DbException &e)
		{
			DBD_ERR_PRINT(dbPtr,e);
			return e.get_errno();
		}
	}

	// get pairs from btree
	template<typename PairT, typename SKeyT>
	int GetArrayByDupSKey(Db *dbPtr, DbTxn *txnPtr, SKeyT *skey_ptr, unsigned int skey_size, PairT *pair_array_ptr, unsigned int count_ptr)
	{
		assert(dbPtr);
		assert(txnPtr);
		assert(skey_ptr);
		assert(pair_array_ptr);

		int ret = DB_UNKNOWN;
		Dbc* pdbc = NULL;
		unsigned int count = 0;

		try
		{
			if ((ret = (dbPtr->cursor(txnPtr, &pdbc, 0)) != DB_OK))
			{
				return ret;
			}

			SafeCursor sc(pdbc);

			for (; ; ++count)
			{
				if (count > *count_ptr)
				{
					return DB_BAD_PARAM;
				}
				auto pairPtr = pair_array_ptr[count];

				MAKEDBT_DBTMALLOC(SkEY, skey_ptr, skey_size);
				MAKEDBT_DBTMALLOC(PkEY, &(pairPtr->_key), CLASS_MEMBER_SIZE(PairT, _key));
				MAKEDBT_DBTMALLOC(DATA, &(pairPtr->_value), CLASS_MEMBER_SIZE(PairT, _value));
				ret = sc->pget(txnPtr, &SkEY, &PkEY, &DATA, count > 0 ? DB_NEXT_DUP: DB_SET);
				switch (ret)
				{
				case DB_OK:
					break;
				case DB_NOTFOUND:
					if (count > 0)
					{
						*count_ptr = count;
						return DB_OK;
					}
					return ret;
				default:
					return ret;
				}
			}
		}
		catch (DbException &e)
		{
			DBD_ERR_PRINT(dbPtr,e);
			return e.get_errno();
		}
	}

	template<typename PairT, typename PKeyT, typename SKeyT>
	int ForEach(Db *dbPtr, DbTxn *txnPtr, int (*callback)(PairT&, Dbc*, void*), void *param)
	{
		assert(dbPtr);
		assert(txnPtr);
		assert(callback);

		int ret = DB_UNKNOWN;
		Dbc* pdbc = NULL;

		try
		{
			if ((ret = (dbPtr->cursor(txnPtr, &pdbc, 0)) != DB_OK))
			{
				return ret;
			}

			SafeCursor sc(pdbc);

			for (; ; ++count)
			{
				if (count > *count_ptr)
				{
					return DB_BAD_PARAM;
				}
				PairT pt;
				MAKEDBT_DBTMALLOC(PkEY, &(pt._key), CLASS_MEMBER_SIZE(PairT, _key));
				MAKEDBT_DBTMALLOC(DATA, &(pt._value), CLASS_MEMBER_SIZE(PairT, _value));
				ret = sc->get(txnPtr, &PkEY, &DATA, count > 0 ? DB_NEXT: DB_FIRST);
				switch (ret)
				{
				case DB_OK:
					if ((ret = callback(&pt, pdbc, param)) != DB_OK)
					{
						return ret;
					}
					break;
				case DB_NOTFOUND:
					return count > 0 ? DB_OK : DB_NOTFOUND;
				default:
					return ret;
				}
			}
		}
		catch (DbException &e)
		{
			DBD_ERR_PRINT(dbPtr,e);
			return e.get_errno();
		}
	}

	template<typename PairT, typename PKeyT, typename SKeyT>
	int ForEach(Db *dbPtr, DbTxn *txnPtr, std::function<int(PairT&,Dbc*)> callback_obj)
	{
		assert(dbPtr);
		assert(txnPtr);

		int ret = DB_UNKNOWN;
		Dbc* pdbc = NULL;

		try
		{
			if ((ret = (dbPtr->cursor(txnPtr, &pdbc, 0)) != DB_OK))
			{
				return ret;
			}

			SafeCursor sc(pdbc);

			for (; ; ++count)
			{
				if (count > *count_ptr)
				{
					return DB_BAD_PARAM;
				}
				PairT pt;
				MAKEDBT_DBTMALLOC(PkEY, &(pt._key), CLASS_MEMBER_SIZE(PairT, _key));
				MAKEDBT_DBTMALLOC(DATA, &(pt._value), CLASS_MEMBER_SIZE(PairT, _value));
				ret = sc->get(txnPtr, &PkEY, &DATA, count > 0 ? DB_NEXT: DB_FIRST);
				switch (ret)
				{
				case DB_OK:
					if ((ret = callback_obj(&pt, pdbc)) != DB_OK)
					{
						return ret;
					}
					break;
				case DB_NOTFOUND:
					return count > 0 ? DB_OK : DB_NOTFOUND;
				default:
					return ret;
				}
			}
		}
		catch (DbException &e)
		{
			DBD_ERR_PRINT(dbPtr,e);
			return e.get_errno();
		}
	}

	template<typename PairT, typename PKeyT, typename SKeyT>
	int LastPair(Db *dbPtr, DbTxn *txnPtr, PairT *pairPtr)
	{
		assert(dbPtr);
		assert(txnPtr);
		assert(pairPtr);

		int ret = DB_UNKNOWN;
		Dbc* pdbc = NULL;

		try
		{
			if ((ret = (dbPtr->cursor(txnPtr, &pdbc, 0)) != DB_OK))
			{
				return ret;
			}

			SafeCursor sc(pdbc);
			MAKEDBT_DBTMALLOC(PkEY, &(pairPtr->_key), CLASS_MEMBER_SIZE(PairT, _key));
			MAKEDBT_DBTMALLOC(DATA, &(pairPtr->_value), CLASS_MEMBER_SIZE(PairT, _value));
			return sc->get(txnPtr, &PkEY, &DATA, DB_LAST);
		}
		catch (DbException &e)
		{
			DBD_ERR_PRINT(dbPtr,e);
			return e.get_errno();
		}
	}

	// sequence [5/4/2015 liletian]
	template<typename PairT, typename PKeyT, typename SKeyT>
	int MakeAutoID(Db *dbPtr, DbTxn *txnPtr, PairT *pairPtr, int base_id=1, int step=1)
	{
		assert(dbPtr);
		assert(txnPtr);

		pairPtr->_key = base_id;
		ret = bdbutil::LastPair(dbPtr, txnPtr, pairPtr);
		switch (ret)
		{
		case DB_OK:
			pairPtr->_key += step;
			return DB_OK;
		case DB_NOTFOUND:
			pairPtr->_key = base_id;
			return DB_OK;
		default:
			return ret;
		}
	}
	
	template<typename KeyT>
	int GetPart(Db *dbPtr, DbTxn *txnPtr, KeyT *keyPtr, int from, int to, void *pOut, int *pSizeOut)
	{
		assert(dbPtr);
		assert(txnPtr);
		assert(pOut);
		assert(pSizeOut);
		assert(from<=to);
		if (from > to)
		{
			return DB_BAD_PARAM;
		}

		int ret = DB_UNKNOWN;

		try
		{
			MAKEDBT_USERMALLOC(queryKey, keyPtr, sizeof(KeyT));
			Dbt DATA;
			DATA.set_flags(DB_DBT_PARTIAL | DB_DBT_USERMEM);
			DATA.set_data(pOut);
			// desc part
			DATA.set_doff(from);
			DATA.set_dlen(to-from);
			// src data
			DATA.set_size(to-from);
			DATA.set_ulen(to-from);
			return dbPtr->get(txnPtr, &queryKey, &DATA, 0);
		}
		catch (DbException &e)
		{
			DBD_ERR_PRINT(dbPtr,e);
			return e.get_errno();
		}
	}

	template<typename KeyT>
	int Replace(Db *dbPtr, DbTxn *txnPtr, KeyT *keyPtr, int from, int to, void *pIn, int size)
	{
		assert(dbPtr);
		assert(txnPtr);
		assert(pOut);
		assert(pIn);
		assert(from<=to);
		if (from > to)
		{
			return DB_BAD_PARAM;
		}

		int ret = DB_UNKNOWN;

		try
		{
			MAKEDBT_USERMALLOC(queryKey, keyPtr, sizeof(KeyT));
			Dbt DATA;
			DATA.set_flags(DB_DBT_PARTIAL | DB_DBT_USERMEM);
			DATA.set_data(pOut);
			// desc part
			DATA.set_doff(from);
			DATA.set_dlen(to-from);
			// src data
			DATA.set_size(size);
			DATA.set_ulen(size);
			return dbPtr->get(txnPtr, &queryKey, &DATA, 0);
		}
		catch (DbException &e)
		{
			DBD_ERR_PRINT(dbPtr,e);
			return e.get_errno();
		}
	}

	// insert InsertionT, begin with "offset"
	template<typename KeyT, typename InsertionT>
	int Insert(Db *dbPtr, DbTxn *txnPtr, KeyT *keyPtr, int offset, InsertionT *pIn)
	{
		return bdbutil::Replace(dbPtr, txnPtr, keyPtr, offset, offset, pIn, sizeof(InsertionT));
	}

	// set/update InsertionT, begin with "offset"
	template<typename KeyT, typename InsertionT>
	int Set(Db *dbPtr, DbTxn *txnPtr, KeyT *keyPtr, int offset, InsertionT *pIn)
	{
		return bdbutil::Replace(dbPtr, txnPtr, keyPtr, offset, offset+sizeof(InsertionT), pIn, sizeof(InsertionT));
	}


}// eof bdbutil
#endif // eof _BDBBOX_BDB_CNM_H_