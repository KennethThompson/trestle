#ifndef SETTING_DB_INCLUDE_
#define SETTING_DB_INCLUDE_
//#include "stdafx.hpp"
#include <rocksdb/db.h>
#include <rocksdb/options.h>
#include <rocksdb/slice.h>


using ROCKSDB_NAMESPACE::DB;
using ROCKSDB_NAMESPACE::Options;
using ROCKSDB_NAMESPACE::PinnableSlice;
using ROCKSDB_NAMESPACE::ReadOptions;
using ROCKSDB_NAMESPACE::Status;
using ROCKSDB_NAMESPACE::WriteBatch;
using ROCKSDB_NAMESPACE::WriteOptions;

using namespace std::placeholders;
struct SettingsDB
{
    SettingsDB(/* args */);
    ~SettingsDB();
    bool initialize();
    bool GetValue(std::string& key, std::string& result);
    bool PutValue(std::string& key, std::string& value);
    bool DeleteValue(std::string& key);

private:
    std::shared_ptr<rocksdb::DB> db;
    

};

#endif

