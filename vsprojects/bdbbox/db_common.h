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
	int GetByKey(Db *pdb_ptr, DbTxn *txn_ptr, const KeyT *key_ptr, PairT *pair_out_ptr)
	{
		assert(pdb_ptr);
		assert(txn_ptr);
		assert(pair_out_ptr);
		try
		{
			pair_out_ptr->key_ptr = *key_ptr;
			MAKEDBT_DBTMALLOC(QkEY, &(pair_out_ptr->_key), CLASS_MEMBER_SIZE(PairT, _key));
			MAKEDBT_DBTMALLOC(DATA, &(pair_out_ptr->_value), CLASS_MEMBER_SIZE(PairT, _value));
			return pdb_ptr->get(txn_ptr, &QKEY, &DATA, 0);
		}
		catch (DbException &e)
		{
			DBD_ERR_PRINT(pdb_ptr,e);
			return e.get_errno();
		}
	}

	// update, create a pair
	template<typename PairT, typename KeyT>
	int Update(Db *pdb_ptr, DbTxn *txn_ptr, PairT *pair_ptr)
	{
		assert(pdb_ptr);
		assert(txn_ptr);
		try
		{
			pair_ptr->key_ptr = key_ptr;
			MAKEDBT_DBTMALLOC(QkEY, &(pair_ptr->_key), CLASS_MEMBER_SIZE(PairT, _key));
			MAKEDBT_DBTMALLOC(DATA, &(pair_ptr->_value), CLASS_MEMBER_SIZE(PairT, _value));
			return pdb_ptr->put(txn_ptr, &QKEY, &DATA, 0);
		}
		catch (DbException &e)
		{
			DBD_ERR_PRINT(pdb_ptr,e);
			return e.get_errno();
		}
	}

	// delete
	template<typename KeyT>
	int Delete(Db *pdb_ptr, DbTxn *txn_ptr, KeyT *key_ptr)
	{
		assert(pdb_ptr);
		assert(txn_ptr);
		try
		{
			MAKEDBT_DBTMALLOC(QkEY, &(key_ptr), sizeof(key_ptr));
			return pdb_ptr->del(txn_ptr, &QKEY, 0);
		}
		catch (DbException &e)
		{
			DBD_ERR_PRINT(pdb_ptr,e);
			return e.get_errno();
		}
	}

	template<typename KeyT>
	int KeyExists(Db *pdb_ptr, DbTxn *txn_ptr, const void *key_ptr, int len)
	{
		assert(pdb_ptr);
		assert(txn_ptr);
		assert(key_ptr);
		try
		{
			MAKEDBT_DBTMALLOC(QkEY, key_ptr, len);
			return pdb_ptr->exists(txn_ptr, &QKEY, 0);
		}
		catch (DbException &e)
		{
			DBD_ERR_PRINT(pdb_ptr,e);
			return e.get_errno();
		}
	}

	template<typename KeyT>
	int SafeDelete(Db *pdb_ptr, DbTxn *txn_ptr, KeyT *key_ptr)
	{
		assert(pdb_ptr);
		assert(txn_ptr);
		assert(key_ptr);

		int ret = bdbutil::KeyExists(pdb_ptr, txn_ptr, key_ptr);
		if (ret != DB_OK)
		{
			return ret;
		}

		try
		{
			MAKEDBT_DBTMALLOC(QkEY, &(key_ptr), sizeof(key_ptr));
			return pdb_ptr->del(txn_ptr, &QKEY, 0);
		}
		catch (DbException &e)
		{
			DBD_ERR_PRINT(pdb_ptr,e);
			return e.get_errno();
		}
	}

	// get pairs from btree
	template<typename PairT, typename KeyT>
	int GetArrayByDupPKey(Db *pddb_ptr, DbTxn *txn_ptr, KeyT *key_ptr, PairT *pair_array_ptr, unsigned int count_ptr)
	{
		assert(pddb_ptr);
		assert(txn_ptr);
		assert(key_ptr);
		assert(pair_array_ptr);

		int ret = DB_UNKNOWN;
		Dbc* pdbc = NULL;
		unsigned int count = 0;
		int flag = DB_SET;

		try
		{
			if ((ret = (pddb_ptr->cursor(txn_ptr, &pdbc, 0)) != DB_OK))
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
				auto pair_ptr = pair_array_ptr[count];
				MAKEDBT_DBTMALLOC(QkEY, key_ptr, CLASS_MEMBER_SIZE(PairT, _key));
				MAKEDBT_DBTMALLOC(DATA, &(pair_ptr->_value), CLASS_MEMBER_SIZE(PairT, _value));
				ret = sc->get(txn_ptr, &QKEY, &DATA, count > 0 ? DB_NEXT_DUP: DB_SET);
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
			DBD_ERR_PRINT(pddb_ptr,e);
			return e.get_errno();
		}
	}

	// get pairs from btree
	template<typename PairT, typename SKeyT>
	int GetArrayByDupSKey(Db *pddb_ptr, DbTxn *txn_ptr, SKeyT *skey_ptr, unsigned int skey_size, PairT *pair_array_ptr, unsigned int count_ptr)
	{
		assert(pddb_ptr);
		assert(txn_ptr);
		assert(skey_ptr);
		assert(pair_array_ptr);

		int ret = DB_UNKNOWN;
		Dbc* pdbc = NULL;
		unsigned int count = 0;

		try
		{
			if ((ret = (pddb_ptr->cursor(txn_ptr, &pdbc, 0)) != DB_OK))
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
				auto pair_ptr = pair_array_ptr[count];

				MAKEDBT_DBTMALLOC(SkEY, skey_ptr, skey_size);
				MAKEDBT_DBTMALLOC(PkEY, &(pair_ptr->_key), CLASS_MEMBER_SIZE(PairT, _key));
				MAKEDBT_DBTMALLOC(DATA, &(pair_ptr->_value), CLASS_MEMBER_SIZE(PairT, _value));
				ret = sc->pget(txn_ptr, &SkEY, &PkEY, &DATA, count > 0 ? DB_NEXT_DUP: DB_SET);
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
			DBD_ERR_PRINT(pddb_ptr,e);
			return e.get_errno();
		}
	}

	template<typename PairT, typename PKeyT, typename SKeyT>
	int ForEach(Db *pddb_ptr, DbTxn *txn_ptr, int (*callback)(PairT&, Dbc*, void*), void *param)
	{
		assert(pddb_ptr);
		assert(txn_ptr);
		assert(callback);

		int ret = DB_UNKNOWN;
		Dbc* pdbc = NULL;

		try
		{
			if ((ret = (pddb_ptr->cursor(txn_ptr, &pdbc, 0)) != DB_OK))
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
				ret = sc->get(txn_ptr, &PkEY, &DATA, count > 0 ? DB_NEXT: DB_FIRST);
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
			DBD_ERR_PRINT(pddb_ptr,e);
			return e.get_errno();
		}
	}

	template<typename PairT, typename PKeyT, typename SKeyT>
	int ForEach(Db *pddb_ptr, DbTxn *txn_ptr, std::function<int(PairT&,Dbc*)> callback_obj)
	{
		assert(pddb_ptr);
		assert(txn_ptr);

		int ret = DB_UNKNOWN;
		Dbc* pdbc = NULL;

		try
		{
			if ((ret = (pddb_ptr->cursor(txn_ptr, &pdbc, 0)) != DB_OK))
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
				ret = sc->get(txn_ptr, &PkEY, &DATA, count > 0 ? DB_NEXT: DB_FIRST);
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
			DBD_ERR_PRINT(pddb_ptr,e);
			return e.get_errno();
		}
	}

	template<typename PairT, typename PKeyT, typename SKeyT>
	int LastPair(Db *pddb_ptr, DbTxn *txn_ptr, PairT *pair_ptr)
	{
		assert(pddb_ptr);
		assert(txn_ptr);
		assert(pair_ptr);

		int ret = DB_UNKNOWN;
		Dbc* pdbc = NULL;

		try
		{
			if ((ret = (pddb_ptr->cursor(txn_ptr, &pdbc, 0)) != DB_OK))
			{
				return ret;
			}

			SafeCursor sc(pdbc);
			MAKEDBT_DBTMALLOC(PkEY, &(pair_ptr->_key), CLASS_MEMBER_SIZE(PairT, _key));
			MAKEDBT_DBTMALLOC(DATA, &(pair_ptr->_value), CLASS_MEMBER_SIZE(PairT, _value));
			return sc->get(txn_ptr, &PkEY, &DATA, DB_LAST);
		}
		catch (DbException &e)
		{
			DBD_ERR_PRINT(pddb_ptr,e);
			return e.get_errno();
		}
	}

	// sequence [5/4/2015 liletian]
	template<typename PairT, typename PKeyT, typename SKeyT>
	int MakeAutoID(Db *pddb_ptr, DbTxn *txn_ptr, PairT *pair_ptr, int base_id=1, int step=1)
	{
		assert(pddb_ptr);
		assert(txn_ptr);

		pair_ptr->_key = base_id;
		ret = bdbutil::LastPair(pddb_ptr, txn_ptr, pair_ptr);
		switch (ret)
		{
		case DB_OK:
			pair_ptr->_key += step;
			return DB_OK;
		case DB_NOTFOUND:
			pair_ptr->_key = base_id;
			return DB_OK;
		default:
			return ret;
		}
	}





}// eof bdbutil
#endif // eof _BDBBOX_BDB_CNM_H_