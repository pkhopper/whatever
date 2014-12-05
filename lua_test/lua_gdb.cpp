







static void call_stack_info(lua_State* L, int n)
{
    lua_Debug ar;
    if(lua_getstack(L, n, &ar) == 1)
    {
        lua_getinfo(L, "nSlu", &ar);
        const char* indent;
        if(n == 0)
        {
            indent = "->";
            lua_tinker::output_info("[LUA_DEBUG] |/t[[call stack]]/n");
        }
        else
        {
            indent = "  ";
        }
        if(ar.name)
            lua_tinker::output_info("[LUA_DEBUG] |%s [%s : line %d] : %s()/n", indent,ar.short_src ,ar.currentline, ar.name);
        else
            lua_tinker::output_info("[LUA_DEBUG] |%s [%s : line %d] : unkown/n", indent,ar.short_src,ar.currentline);
        int index = 0;
        do 
        {
            indent = lua_getlocal (L, &ar, ++index);
            if (indent)
            {
                switch(lua_type(L, -1))
                {
                case LUA_TNIL:
                    lua_tinker::output_info( "[LUA_DEBUG] |/t/t/t/t/t|-%s:%s", lua_typename(L, lua_type(L, -1)),indent);
                    break;
                case LUA_TBOOLEAN:
                    lua_tinker::output_info( "[LUA_DEBUG] |/t/t/t/t/t|-%s:%s    %s/n", lua_typename(L, lua_type(L, -1)),indent, lua_toboolean(L, -1)?"true":"false");
                    break;
                case LUA_TLIGHTUSERDATA:
                    lua_tinker::output_info( "[LUA_DEBUG] |/t/t/t/t/t|-%s:%s    0x%08p/n", lua_typename(L, lua_type(L, -1)),indent, lua_topointer(L, -1));
                    break;
                case LUA_TNUMBER:
                    lua_tinker::output_info( "[LUA_DEBUG] |/t/t/t/t/t|-%s:%s    %f/n", lua_typename(L, lua_type(L, -1)),indent, lua_tonumber(L, -1));
                    break;
                case LUA_TSTRING:
                    lua_tinker::output_info( "[LUA_DEBUG] |/t/t/t/t/t|-%s:%s    %s/n", lua_typename(L, lua_type(L, -1)),indent, lua_tostring(L, -1));                    
                    break;
                case LUA_TTABLE:
                    lua_tinker::output_info( "[LUA_DEBUG] |/t/t/t/t/t|-%s:%s    0x%08p/n", lua_typename(L, lua_type(L, -1)),indent, lua_topointer(L, -1));
                    break;
                case LUA_TFUNCTION:
                    lua_tinker::output_info( "[LUA_DEBUG] |/t/t/t/t/t|-%s:%s()    0x%08p/n", lua_typename(L, lua_type(L, -1)),indent, lua_topointer(L, -1));
                    break;
                case LUA_TUSERDATA:
                    lua_tinker::output_info( "[LUA_DEBUG] |/t/t/t/t/t|-%s:%s    0x%08p/n", lua_typename(L, lua_type(L, -1)),indent, lua_topointer(L, -1));
                    break;
                case LUA_TTHREAD:
                    lua_tinker::output_info( "[LUA_DEBUG] |/t/t/t/t/t|-%s:%s/n", lua_typename(L, lua_type(L, -1)),indent);
                    break;
                }
                lua_settop(L, -2);
            }            
        } while (indent);    
        call_stack_info(L, n+1);
    }
}


int lua_tinker::break_point(lua_State *L)
{
    output_info("/n[LUA_DEBUG] |/t>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   /n");
    call_stack_info(L, 0);
    output_info("[LUA_ERROR] |/t<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   /n/n");

    #ifdef _WIN32_WINNT 
    if (IsDebuggerPresent())
    {
        DebugBreak();
    }
    #endif
    return 0;
}
 


lua_pushstring(L, "dbg");
lua_pushcfunction(L, lua_tinker::break_point);
lua_settable(L, LUA_GLOBALSINDEX);


// 调试lua现有的几种方案:
//  1）luaedit  : 编辑断点和断点命中查看那些都让习惯用vs的人感到亲切，但是它只是在纯lua环境下的编辑器，也就是说和期望程序运行中能借用它来调试脚本可能性不大（至少我没有试验出来），能用上的需要给lua脚本做个main脚本函数，并提供一系列伪的c api(由lua实现的函数，只提供制定值的返回)。由luaedit启动脚本main函数进行调试
//  2）利用 lua debug 库中的 hook ，然后记录一张断点位置表，设置行模式的 hook ，每次进入 hook 都检查是否是断点处，若是就停下来等待交互调试。这个方法有效，但是很消耗 cpu 。因为每进入一个新的代码行，都需要回调一个函数。当这个函数本身又是用 lua 写的时候，效率更低。
//  3）利用lua脚本函数实现，在lua脚本中封装一个断点函数，这种方式结合debug库实现断点和栈信息，然后利用lua环境下的表对函数调用信息进行记录和打印，需要脚本使用者显式提供断点函数的调用。这个办法的优点自己可以组合出适合自己项目的断点调试方案。但缺点是相对繁琐，而且断点命中以后难以和现有方式融合
