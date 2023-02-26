#include <stdafx.hpp>
#include <GameObject.hpp>
using namespace std::placeholders;


#include <memory>
#include <iostream>



struct stone : public GameObject
{
	stone(sol::this_state ts, sol::this_environment te) : GameObject(ts, te)
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

	lua_State * lua_state()
	{
		return sol::state_view(this->lua);
	}
	

};

int main() {
	std::cout << "=== usertype_initializers ===" << std::endl;
	
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
	std::cout << std::endl;
}