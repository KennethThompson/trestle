#include <stdafx.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <cstdint>

TEST_CASE("Settings Database", "[speedb]") {
    SettingsDB db;
    REQUIRE(db.initialize() == true);
    std::string key("key1");
    SECTION( "writing value to database" ) {
        std::string val("value1");
        bool b = db.PutValue(key, val);
        REQUIRE( b == true);
    }
    SECTION( "reading value to database" ) {
        std::string res("");
        bool b = db.GetValue(key, res);
        REQUIRE(b == true);
        REQUIRE(res.compare("value1")== 0);
    }
    SECTION( "delete value to database" ) {
        bool b = db.DeleteValue(key);
        REQUIRE(b == true);
    }
}

