#ifndef _BDBBOX_BDB_ENV_H_
#define _BDBBOX_BDB_ENV_H_

#include <string>
#include "types.h"

namespace bdbutil
{

	struct CFG_ENV
	{
		typedef void (*err_callback_t)(const DbEnv *, const char *, const char *);
		unsigned int    cacheSize;
		std::string     errPrefix;
		std::ostream   *pErrStream;
		std::string     envHome;
		std::string     envDataPath;
		err_callback_t  err_callback;

		CFG_ENV() : pErrStream(NULL), err_callback(NULL)
		{

		}
	};

	int DbEnvCreate(DbEnv *pEnvOut, CFG_ENV &cfg, int recover_flag)
	{
		int ret = DB_UNKNOWN;
		pEnvOut = NULL;
		try
		{
			if ((pEnvOut = ::new DbEnv(0)) == NULL)
			{
				return DB_BAD_PARAM;
			}

			pEnvOut->set_error_stream(cfg.pErrStream);
			pEnvOut->set_errpfx(cfg.errPrefix.c_str());
			pEnvOut->set_cachesize(0, cfg.cacheSize, 0);
			pEnvOut->set_data_dir(cfg.envDataPath.c_str());
			// ?????? err_callback [4/30/2015 liletian]

			auto flags = DB_CREATE | DB_INIT_LOCK | DB_INIT_LOG | DB_INIT_MPOOL | DB_INIT_TXN | DB_THREAD;
			ret = pEnvOut->open(cfg.envHome.c_str(), flags, 0);
			if (ret != DB_OK)
			{
				return ret;
			}
			return pEnvOut->set_flags(DB_ENV_TXN_WRITE_NOSYNC, 1);
		}
		catch (DbException &e)
		{
			pEnvOut->err(e.get_errno(), "DbEnvCreate() err");
			delete pEnvOut;
			pEnvOut = NULL;
			return e.get_errno();
		}
	}

	int DbEnvJoin(DbEnv *pEnvOut, CFG_ENV &cfg)
	{
		int ret = DB_UNKNOWN;
		pEnvOut = NULL;
		try
		{
			if ((pEnvOut = ::new DbEnv(0)) == NULL)
			{
				return DB_BAD_PARAM;
			}
			pEnvOut->set_error_stream(cfg.pErrStream);
			pEnvOut->set_errpfx(cfg.errPrefix.c_str());
			pEnvOut->set_data_dir(cfg.envDataPath.c_str());
			return pEnvOut->open(cfg.envHome.c_str(), DB_JOINENV, 0);
		}
		catch (DbException &e)
		{
			pEnvOut->err(e.get_errno(), "DbEnvCreate() err");
			delete pEnvOut;
			pEnvOut = NULL;
			return e.get_errno();
		}
	}

	int DbEnvClose(DbEnv *pEnv)
	{
		if (!pEnv)
		{
			return DB_OK;
		}
		int ret = DB_UNKNOWN;
		try
		{
			ret = pEnv->log_flush(NULL);
			ret = pEnv->close(0);
		}
		catch (DbException &e)
		{
			ret = e.get_errno();
			pEnv->err(e.get_errno(), "err, DbEnvClose()");
		}
		::delete pEnv;
		pEnv = NULL;
		return ret;
	}

	int DbEnvRemove(DbEnv *pEnv, CFG_ENV &cfg, int isForce=false)
	{
		int ret = DB_UNKNOWN;
		pEnv = NULL;
		try
		{
			if ((pEnv = ::new DbEnv(0)) == NULL)
			{
				return DB_BAD_PARAM;
			}
			pEnv->set_error_stream(cfg.pErrStream);
			pEnv->set_errpfx(cfg.errPrefix.c_str());
			pEnv->set_data_dir(cfg.envDataPath.c_str());
			return pEnv->remove(cfg.envHome.c_str(), isForce? DB_FORCE: 0);
		}
		catch (DbException &e)
		{
			ret = e.get_errno();
			pEnv->err(e.get_errno(), "DbEnvRemove() err");
		}
		delete pEnv;
		pEnv = NULL;
		return ret;
	}

	int DbEnvCheckPoint(DbEnv *pEnv)
	{
		assert(pEnv);
		if (!pEnv)
		{
			return DB_BAD_PARAM;
		}
		int ret = DB_UNKNOWN;
		try
		{
			return pEnv->txn_checkpoint(0, 0, 0);
		}
		catch (DbException &e)
		{
			ret = e.get_errno();
			pEnv->err(e.get_errno(), "DbEnvCheckPoint() err");
		}
		return ret;
	}

}// eof bdbutil
#endif // eof _BDBBOX_BDB_ENV_H_