#include <stdafx.hpp>
#include <GameObject.hpp>
#include <ScriptFuncs.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>

#include <uv.h>
#include <amqpcpp.h>
#include <amqpcpp/libuv.h>

#include <RabbitHandler.hpp>
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

int main(int argc, char const * const argv[]) {
//std::cout << "=== usertype_initializers ===" << std::endl;
	//int result = Catch::Session().run( argc, argv );
	//libuv_main();
	//main2();
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


    // access to the event loop
    auto *loop = uv_default_loop();
    
    // handler for libev
    MyHandler handler(loop);
    
    // make a connection
    AMQP::TcpConnection connection(&handler, AMQP::Address("amqp://guest:guest@localhost/"));
    
    // we need a channel too
    AMQP::TcpChannel channel(&connection);
    
    // create a temporary queue
    channel.declareQueue(AMQP::exclusive).onSuccess([&connection](const std::string &name, uint32_t messagecount, uint32_t consumercount) {
        // report the name of the temporary queue
        std::cout << "declared queue " << name << std::endl;
    })
   .onError([](const char *message) {
        // something went wrong creating the exchange
		std::cout << "ERROR! " << message << std::endl;
    });
		// declare an exchange, and install callbacks for success and failure
	channel.declareExchange("my-exchange")

    .onSuccess([]() {
        // by now the exchange is created
		 std::cout << "declared exchange " << "my-exchange" << std::endl;
    })

    .onError([](const char *message) {
        // something went wrong creating the exchange
		std::cout << "ERROR! " << message << std::endl;
    });
    

	//channel.publish()
    
    // run the loop
	while(true)
	{
		// start a transaction
		channel.startTransaction();

		// publish a number of messages
		for( int x = 0; x < 100; x++ )
			channel.publish("my-exchange", "my-key", "my first message");
			channel.publish("my-exchange", "my-key", "another message");

		// commit the transactions, and set up callbacks that are called when
		// the transaction was successful or not
		channel.commitTransaction()
			.onSuccess([]() {
				std::cout << "SUCCESS!" << std::endl;
				// all messages were successfully published
			})
			.onError([](const char *message) {
				std::cout << "ERROR! " << message << std::endl;
				// none of the messages were published
				// now we have to do it all over again
			});
    	uv_run(loop, UV_RUN_NOWAIT);
		//break;
		sleep(.1);
	}

    // done
    //return 0;

	std::cout << std::endl;
    return 0;
}

