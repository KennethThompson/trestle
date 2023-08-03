#include <stdafx.hpp>
#include <GameObject.hpp>
#include <ScriptFuncs.hpp>

using namespace std::placeholders;
#include <memory>
#include <iostream>
#include <unqlite.h>

void main2()
{
	int i,rc;
	unqlite *pDb;

	// Open our database;
	rc = unqlite_open(&pDb,"test.db",UNQLITE_OPEN_CREATE);
	if( rc != UNQLITE_OK ){ return; }

	// Store some records
	rc = unqlite_kv_store(pDb,"test",-1,"Hello World",11); //test => 'Hello World'
	if( rc != UNQLITE_OK ){
	//Insertion fail, Hande error (See below)
	return;
	}
	// A small formatted string
	rc = unqlite_kv_store_fmt(pDb,"date",-1,"Current date: %d:%d:%d",2013,06,07);
	if( rc != UNQLITE_OK ){
	//Insertion fail, Hande error (See below)
	return;
	}

	//Switch to the append interface
	rc = unqlite_kv_append(pDb,"msg",-1,"Hello, ",7); //msg => 'Hello, '
	if( rc == UNQLITE_OK ){
	//The second chunk
	rc = unqlite_kv_append(pDb,"msg",-1,"Current time is: ",17); //msg => 'Hello, Current time is: '
	if( rc == UNQLITE_OK ){
		//The last formatted chunk
		rc = unqlite_kv_append_fmt(pDb,"msg",-1,"%d:%d:%d",10,16,53); //msg => 'Hello, Current time is: 10:16:53'
	}
	}

	//Delete a record
	unqlite_kv_delete(pDb,"test",-1);

	//Store 20 random records.
	for(i = 0 ; i < 20 ; ++i ){
	char zKey[12]; //Random generated key
	char zData[34]; //Dummy data

	// generate the random key
	unqlite_util_random_string(pDb,zKey,sizeof(zKey));
	
	// Perform the insertion
	rc = unqlite_kv_store(pDb,zKey,sizeof(zKey),zData,sizeof(zData));
	if( rc != UNQLITE_OK ){
	break;
	}
	}

	if( rc != UNQLITE_OK ){
	//Insertion fail, Handle error
	const char *zBuf;
	int iLen;
	/* Something goes wrong, extract the database error log */
	unqlite_config(pDb,UNQLITE_CONFIG_ERR_LOG,&zBuf,&iLen);
	if( iLen > 0 ){
		puts(zBuf);
	}
	if( rc != UNQLITE_BUSY && rc != UNQLITE_NOTIMPLEMENTED ){
		/* Rollback */
	unqlite_rollback(pDb);
	}
	}

	//Auto-commit the transaction and close our handle.
	unqlite_close(pDb);
}



struct luaSubsystem
{
	luaSubsystem()
	{
		lua.open_libraries();
	}

	sol::state lua;

	lua_State * lua_state()
	{
		return sol::state_view(this->lua);
	}
	

};

int main() {
std::cout << "=== usertype_initializers ===" << std::endl;
	main2();
	/*
	{ // additional scope to make usertype destroy earlier
	

		luaSubsystem l;

		l.lua.new_usertype<GameObject>("baseObject", 
			//sol::constructors<baseObject(sol::this_state, sol::this_environment)>(),
			sol::meta_function::new_index,
			&GameObject::set_property_lua,
			sol::meta_function::index,
			&GameObject::get_property_lua);
		//auto fp = 
		l.lua.new_usertype<stone>("holy",
		 	sol::constructors<stone(sol::this_state, sol::this_environment)>(),
			sol::meta_function::new_index,
			&stone::set_property_lua,
			sol::meta_function::index,
			&stone::get_property_lua,
		     //"new",
		     //sol::initializers([&l](auto a){ return l.initialize(a);}),
		    ///"create",
		     //sol::factories(&stone::create),
		     //sol::meta_function::garbage_collect,
		     //sol::destructor(&stone::destroy),
		     //"data",
		    // &stone::data, 
			sol::base_classes,
            sol::bases<GameObject>()
			);

		l.lua.script(R"(
        
        h2 = holy.new()

		function h2:GetCommand2()
			return "OK"
		end

		print(h2:GetCommand2())
       
        )");
		//holy& h1 = lua["h1"];
		//holy& h2 = lua["h2"];
		//sol_c_assert(h1.data == 50);
		//sol_c_assert(h2.data == 0);
	}
	*/
	std::cout << std::endl;
}