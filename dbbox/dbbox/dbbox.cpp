// dbbox.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "db.h"
#include "DBBox.h"

int _tmain(int argc, _TCHAR* argv[])
{
	DBBox db("a", "test.db");
	db.init();
	db.put(11, "lllll");
	db.getDb().close(0);
	return 0;
}

