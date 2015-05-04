#ifndef _BDBBOX_BDB_BASE_H_
#define _BDBBOX_BDB_BASE_H_

#include "bdbenv.h"
#include "bdbtxn.h"
#include "bdbcursor.h"

namespace bdbutil
{
	#pragma pack(push) 
	#pragma pack(1) 

	typedef  unsigned char default_version_t;

	template<typename _VersionT = default_version_t>
	struct DBValue
	{
		DataValue(_VersionT version) : _version(version) 
		{

		}

		_VersionT  _version;
	};

	template<typename _KeyT, typename _ValueT, typename _VersionT = default_version_t>
	struct DataPair
	{
		_KeyT     _key;
		_ValueT   _value;

		DBValue(_VersionT version) : _value(version) 
		{

		}
	};


	template<typename _AdaptionT, unsigned int _AdaptionNumber, typename _KeyT, typename _ValueT, typename _VersionT = default_version_t>
	struct AdaptionDataPair : public DataPair<_KeyT, _ValueT, _VersionT>
	{
		DBValue(_VersionT version) : DataPair<_KeyT, _ValueT, _VersionT>(version), _count(0)
		{
			memset(_adaption, 0, _AdaptionNumber);
		}

		int count() const 
		{
			return _count;
		}

		unsigned int size() const 
		{
			return _count * sizeof(_AdaptionT) + sizeof(this->_key) + sizeof(this->_value._version);
		}

		_AdaptionT *add()
		{
			return _adaption + _count++;
		}

		_AdaptionT const *get(int index)
		{
			if (index > -1 && index < _count)
			{
				return _adaption + index;
			}
			assert(index > -1 && index < _count);
			return NULL;
		}

		void set(int index, const _AdaptionT &adaption)
		{
			assert(index > -1 && index < _count);
			if (index > -1 && index < _AdaptionNumber)
			{
				_adaption[index] = adaption;
				if (_count < index + 1)
				{
					_count  = index + 1;
				}
			}
		}

	protected:
		_AdaptionT    _adaption[_AdaptionNumber];
		int           _count;
	};
 
#pragma pack(pop) 

}// eof bdbutil
#endif // eof _BDBBOX_BDB_CNM_H_