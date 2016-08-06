#include <lua.hpp>
#include <iostream>



std::string luastring = "function echo()\
                            print(\"hellowode\")\
                         end";

void test()
{
    lua_State * pLua = NULL;
    pLua = lua_open();
    luaL_openlibs(pLua);

    int ret = luaL_loadfile(pLua, "D:/github/whatever/src/lua101/script/lua101.lua");
    lua_getglobal(pLua, "echo");
    //lua_pushnumber(pLua, 1);
    ret = lua_pcall(pLua, 0, 0, NULL);
    std::cout << ret << std::endl;
}


int main(int argc, char* argv[])
{
    test();
    return 0;
}

