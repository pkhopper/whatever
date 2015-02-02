#include "db.h"
#include "DBBox.h"

int main(int argc, char* argv[])
{
	DBBox db("a", "test.db");
	db.init();
	db.put(11, "lllll");
	//db.getDb().close(0);
	return 0;
}

