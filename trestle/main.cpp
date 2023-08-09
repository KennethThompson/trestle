#include <stdafx.hpp>
#include <GameObject.hpp>
#include <ScriptFuncs.hpp>

#include "rocksdb/db.h"
#include "rocksdb/options.h"
#include "rocksdb/slice.h"

using namespace std::placeholders;
#include <memory>
#include <iostream>

using ROCKSDB_NAMESPACE::DB;
using ROCKSDB_NAMESPACE::Options;
using ROCKSDB_NAMESPACE::PinnableSlice;
using ROCKSDB_NAMESPACE::ReadOptions;
using ROCKSDB_NAMESPACE::Status;
using ROCKSDB_NAMESPACE::WriteBatch;
using ROCKSDB_NAMESPACE::WriteOptions;

#if defined(OS_WIN)
std::string kDBPath = "C:\\Windows\\TEMP\\rocksdb_simple_example";
#else
std::string kDBPath = "/tmp/rocksdb_simple_example";
#endif


int main2()
{
  std::cout << "OK!" << std::endl;
  DB* db;
  Options options;
  // Optimize RocksDB. This is the easiest way to get RocksDB to perform well
  options.IncreaseParallelism();
  options.OptimizeLevelStyleCompaction();
  // create the DB if it's not already present
  options.create_if_missing = true;

  // open DB
  Status s = DB::Open(options, kDBPath, &db);
  assert(s.ok());

  // Put key-value
  s = db->Put(WriteOptions(), "key1", "value");
  assert(s.ok());
  std::string value;
  // get value
  s = db->Get(ReadOptions(), "key1", &value);
  assert(s.ok());
  assert(value == "value");

  // atomically apply a set of updates
  {
    WriteBatch batch;
    batch.Delete("key1");
    batch.Put("key2", value);
    s = db->Write(WriteOptions(), &batch);
  }

  s = db->Get(ReadOptions(), "key1", &value);
  assert(s.IsNotFound());

  db->Get(ReadOptions(), "key2", &value);
  assert(value == "value");

  {
    PinnableSlice pinnable_val;
    db->Get(ReadOptions(), db->DefaultColumnFamily(), "key2", &pinnable_val);
    assert(pinnable_val == "value");
  }

  {
    std::string string_val;
    // If it cannot pin the value, it copies the value to its internal buffer.
    // The intenral buffer could be set during construction.
    PinnableSlice pinnable_val(&string_val);
    db->Get(ReadOptions(), db->DefaultColumnFamily(), "key2", &pinnable_val);
    assert(pinnable_val == "value");
    // If the value is not pinned, the internal buffer must have the value.
    assert(pinnable_val.IsPinned() || string_val == "value");
  }

  PinnableSlice pinnable_val;
  s = db->Get(ReadOptions(), db->DefaultColumnFamily(), "key1", &pinnable_val);
  assert(s.IsNotFound());
  // Reset PinnableSlice after each use and before each reuse
  pinnable_val.Reset();
  db->Get(ReadOptions(), db->DefaultColumnFamily(), "key2", &pinnable_val);
  assert(pinnable_val == "value");
  pinnable_val.Reset();
  // The Slice pointed by pinnable_val is not valid after this point

  delete db;

  return 0;
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