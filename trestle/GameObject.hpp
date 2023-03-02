// ==========================================================================
// GameObject.hpp
//
// Copyright (C) 2023 Kenneth Thompson, All Rights Reserved.
// This file is covered by the MIT Licence:
//
// Permission is hereby granted, free of charge, to any person obtaining a 
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation 
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the 
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
// DEALINGS IN THE SOFTWARE.
// ==========================================================================
#if !defined(GAME_OBJECT)
#define GAME_OBJECT
#include <stdafx.hpp>

namespace trestle
{
	enum class EntityType { UNKNOWN=0, ROOM, ITEM, NPC, PLAYER, COMMAND, DAEMON, LIB, HAND };
	struct _sol_userdata_
	{
		~_sol_userdata_()
		{
		// LOG_DEBUG << "sol_userdata destroyed.." << std::endl;
		}
		sol::userdata selfobj;
	};


	struct GameObject
	{
	private:
		/* data */
		std::unordered_map<std::string, sol::object> _internalProperties;
		std::string _baseScriptPath;
		std::string _virtualScriptPath;
		std::shared_ptr<GameObject> _owner; // Object that owns this one
		EntityType _entityType;
		unsigned int _instanceID; // used to discriminate between multiple objects created by a single script
		std::shared_ptr< _sol_userdata_ > _solObject; // used to keep track of the lua stack object
		
	public:
		GameObject(const GameObject&) = delete;
		void operator=(const GameObject&) = delete;
		~GameObject();

	GameObject(sol::this_state ts, sol::this_environment te, EntityType& et);

	/// @brief Returns owning entity
	/// @return shared_ptr to owning entity
	std::shared_ptr<GameObject> GetOwner() { return _owner; }

		/*
			Lua Accessors to allow for arbitrary property definitions
		*/
		sol::object get_property_lua(const char* name, sol::this_state s);
		void set_property_lua(const char* name, sol::stack_object object);
		EntityType& GetEntityType() { return _entityType; };
		std::string GetEntityTypeString();
	};
	


	#endif // GAME_OBJECT

}

