#if !defined(BASE_OBJECT)
#define BASE_OBJECT
#include <stdafx.hpp>

 class GameObject
 {
 private:
    /* data */
    std::unordered_map<std::string, sol::object> _internalProperties;
 public:
    GameObject(/* args */);
    ~GameObject();

   GameObject(sol::this_state ts, sol::this_environment te)
   {

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
 };
 


#endif // BASE_OBJECT
