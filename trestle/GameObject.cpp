#include <GameObject.hpp>

GameObject::~GameObject()
{

}

GameObject::GameObject(sol::this_state ts, sol::this_environment te, EntityType& et) 
{
    lua_State* L = ts;

    if(!te) {
        std::cout << "function does not have an environment: exiting function early";
        return;
    }
    
    /*
        _solObject is the wrapper about the sol object that is this instantiated object in the lua stack.
	*/
    _solObject = std::shared_ptr<_sol_userdata_>(new _sol_userdata_);
    _solObject->selfobj = sol::userdata(L, -2);

    //sol::environment& env = te;
    //sol::optional<std::string> sp = env["_INTERNAL_SCRIPT_PATH_"];
}

sol::object GameObject::get_property_lua(const char* name, sol::this_state s) 
{
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
}

void GameObject::set_property_lua(const char* name, sol::stack_object object)
{
    _internalProperties[name] = object.as<sol::object>();
}

