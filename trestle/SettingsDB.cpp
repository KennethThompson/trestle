#include "SettingsDB.hpp"


#include <memory>
#include <iostream>
#include <string>

#if defined(OS_WIN)
std::string kDBPath = "C:\\Windows\\TEMP\\trestle_db";
#else
std::string kDBPath = "/tmp/trestle_db";
#endif



SettingsDB::SettingsDB(/* args */)
{

}

SettingsDB::~SettingsDB()
{
    if( this->db ) this->db.reset();
}

bool SettingsDB::initialize()
{
    DB* db;
    Options options;
    options.IncreaseParallelism();
    options.OptimizeLevelStyleCompaction();
    options.create_if_missing = true;

    // open DB
    Status s = DB::Open(options, kDBPath, &db);
    auto pathNotFound = s.IsPathNotFound();
    if(!s.ok()) {
      delete db;
      return false;
    }
      
    this->db.reset(db);
    return true;
}

bool SettingsDB::GetValue(std::string &key, std::string &result)
{
  if (!this->db)
    return false;
  auto status = this->db.get()->Get(ReadOptions(), key.c_str(), &result);
  return status.ok();
}

bool SettingsDB::PutValue(std::string &key, std::string &value)
{
  if (!this->db)
    return false;
  auto status = this->db.get()->Put(WriteOptions(), key.c_str(), value.c_str());
  return status.ok();
}

bool SettingsDB::DeleteValue(std::string &key)
{
  if (!this->db)
    return false;
  auto status = this->db.get()->Delete(WriteOptions(), key);
  return status.ok();
}

