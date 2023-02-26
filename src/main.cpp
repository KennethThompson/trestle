#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include <functional>
using namespace std::placeholders;


#include <memory>
#include <iostream>


struct baseObject {
public:
	baseObject(sol::this_state ts, sol::this_environment te) : data()
	{

	}
	baseObject() : data() {
	}
	baseObject(int value) : data(value) {
	}
	~baseObject() {
	}

	/*
		Lua Accessors to allow for arbitrary property definitions
	*/
	sol::object get_property_lua(const char* name, sol::this_state s)
	{
		
		auto search = _internalProperties.find(name);

		if (search == _internalProperties.end()) {
			return sol::nil;
		}
		else
		{
			return search->second;
		}
	
	}
	void set_property_lua(const char* name, sol::stack_object object)
	{
		   _internalProperties[name] = object.as<sol::object>();
	}
        

public:

	const int data;

private:
	std::unordered_map<std::string, sol::object> _internalProperties;
};

struct stone : baseObject
{
	stone(sol::this_state ts, sol::this_environment te) : baseObject(ts, te)
	{

	}
	stone()
	{

	}
	~stone()
	{
		std::cout << "time to melt" << std::endl;
	}

};

struct luaSubsystem
{
	luaSubsystem()
	{
		lua.open_libraries();
	}

	sol::state lua;

	struct deleter {
		void operator()(baseObject* p) const {
			destroy(*p);
		}
	};

	std::unique_ptr<baseObject, deleter> create2() {
		std::cout << "creating 'holy' unique_ptr directly and "
		             "letting sol/Lua handle it"
		          << std::endl;
		return std::unique_ptr<baseObject, deleter>(new baseObject(50));
	}

	lua_State * lua_state()
	{
		return sol::state_view(this->lua);
	}
	
	void initialize(baseObject& uninitialized_memory) {
		std::cout << "initializing 'holy' userdata at "
		          << static_cast<void*>(&uninitialized_memory)
		          << std::endl;
		//auto s = sol::get_environment(uninitialized_memory);
		// receive uninitialized memory from Lua:
		// properly set it by calling a constructor
		// on it
		// "placement new"
        
		new (&uninitialized_memory) baseObject();
		//auto s = sol::get_environment(uninitialized_memory);
		
		//auto t = sol::state_view()
		std::cout << "OK" << std::endl;
	}

	static void destroy(baseObject& memory_from_lua) {
		std::cout << "destroying 'holy' userdata at "
		          << static_cast<void*>(&memory_from_lua)
		          << std::endl;
		memory_from_lua.~baseObject();
	}

};

int main() {
	std::cout << "=== usertype_initializers ===" << std::endl;
	
	{ // additional scope to make usertype destroy earlier
	

		luaSubsystem l;

		l.lua.new_usertype<baseObject>("baseObject", 
			sol::meta_function::new_index,
			&baseObject::set_property_lua,
			sol::meta_function::index,
			&baseObject::get_property_lua);
		//auto fp = 
		l.lua.new_usertype<stone>("holy",
		 	 sol::constructors<stone(sol::this_state, sol::this_environment)>(),
		     //"new",
		     //sol::initializers([&l](auto a){ return l.initialize(a);}),
		    ///"create",
		     //sol::factories(&stone::create),
		     //sol::meta_function::garbage_collect,
		     //sol::destructor(&stone::destroy),
		     //"data",
		    // &stone::data, 
			sol::base_classes,
            sol::bases<baseObject>()
			);

		l.lua.script(R"(
        
        h2 = holy.new()
		
       
        )");
		//holy& h1 = lua["h1"];
		//holy& h2 = lua["h2"];
		//sol_c_assert(h1.data == 50);
		//sol_c_assert(h2.data == 0);
	}
	std::cout << std::endl;
}