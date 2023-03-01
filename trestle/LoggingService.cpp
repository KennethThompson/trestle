#include <stdafx.hpp>
#include <LoggingService.hpp>
//#include "io/log_interface.h"
//#include "io/db_interface.h"
//#include "entity_manager.h"
//#include "script_entities/playerobj.h"
/*
void log_interface::log(LOGLEVEL log_level, std::string script_path, std::string msg)
{
	auto main_log = spd::get("main");
	switch( log_level )
	{
		case LOGLEVEL::LOGLEVEL_ERROR:
		{
			main_log->error(msg);
			break;
		}
		case LOGLEVEL::LOGLEVEL_CRITICAL:
		{
			main_log->critical(msg);
			break;
		}
		case LOGLEVEL::LOGLEVEL_INFO:
		{
			main_log->info(msg);
			break;
		}
		case LOGLEVEL::LOGLEVEL_DEBUG:
		{
			main_log->debug(msg);
			break;
		}
	}
	db_interface::Instance().log_event(log_level, script_path, msg);

	 //Concept idea.. find registered creators for a particular script and blast the output to them 
	// TODO : Inside entity manager have a call that returns all player_objs registered to receive debug for the script, or wildcard (i.e., all)
	// put this into a daemon.
	std::vector<playerobj *> pos = entity_manager::Instance().get_online_creators();
	for (auto p : pos)
	{
		char * tab = "_internal_debug_action_table";
		sol::object ot = p->get_property_lua(tab, NULL);
		if (ot != sol::nil)
		{
			if (auto c = ot.as<sol::table>())
			{

				bool bFindObject = false;
				auto fx = [&c](auto& f, auto& tbl) -> void {
					// You can iterate through a table: it has
					// begin() and end()
					// like standard containers

					for (auto key_value_pair : tbl) {
						const sol::object& key = key_value_pair.first;
						const sol::object& value = key_value_pair.second;
						sol::type t = value.get_type();
						sol::type t1 = value.get_type();
						if (value.is<std::string>())
						{
							
							//std::cout << "value " << value.as<std::string>() << std::endl;
						}


						
						

					}
				};
				fx(fx, c);
			}
		}


	}
}
void log_interface::log(LOGLEVEL log_level, std::string msg)
{
	log(log_level, "", msg);
}
void log_interface::log_error(std::string msg)
{
	log(LOGLEVEL::LOGLEVEL_ERROR, "", msg);
}
*/