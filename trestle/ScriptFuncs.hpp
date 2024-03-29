// ==========================================================================
// ScriptFuncs.hpp
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
#include <stdafx.hpp>
#if !defined(SCRIPT_FUNCS)
#define SCRIPT_FUNCS


namespace trestle {

    std::string get_str_between(const std::string &s,
        const std::string &start_delim,
        const std::string &stop_delim)
    {
        unsigned first_delim_pos = s.find(start_delim);
        unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
        unsigned last_delim_pos = s.find(stop_delim);

        return s.substr(end_pos_of_first_delim,
                last_delim_pos - end_pos_of_first_delim);
    }

    struct ScriptFuncs {
        static bool ParseScriptText(
            std::stringstream& buffer,
            std::string& script_path,
            std::string& script_text,
            EntityType& obj_type,
            std::string& reason)
        {
            std::string token;
            std::vector<std::string> file_tokens;
            std::vector<std::string> include_tokens;
            // PRE-PROCESSOR STUFF
            bool bFoundType = false;
            while (std::getline(buffer, token, '\n')) {
                trim(token);
                if (boost::starts_with(token, "#include"))
                {
                    std::string d1 = "<";
                    std::string d2 = ">";
                    std::string d3 = "\"";
                    std::string tinclude = get_str_between(token, d1, d2);
                    bool ifound = false;
                    if (!tinclude.empty())
                    {
                        include_tokens.push_back(tinclude);
                        ifound = true;
                    }
                    tinclude = get_str_between(token, d3, d3);
                    if (!tinclude.empty())
                    {
                        include_tokens.push_back(tinclude);
                        ifound = true;
                    }
                    if (!ifound)
                    {
                        reason = "Include directive is empty or malformed.";
                        return false;
                    }
                    token = "--" + token +" ";
                    file_tokens.push_back(token);
                }
                if (token.compare("inherit lib") == 0) {
                    if (bFoundType) // bad. only one type per script
                    {
                        reason = "Multiple inherit directives detected. Only one entity type is allowed per script.";
                        return false;
                        }
                    obj_type = EntityType::LIB;
                    token = "--" + token +" ";
                    //file_tokens.push_back(token);

                    bFoundType = true;
                }
                else if (token.compare("inherit daemon") == 0) {
                    if (bFoundType) // bad. only one type per script
                    {
                        reason = "Multiple inherit directives detected. Only one entity type is allowed per script.";
                        return false;
                    }
                    obj_type = EntityType::DAEMON;
                    token = "--" + token +" ";
                    file_tokens.push_back(token);

                    bFoundType = true;
                }
                else if (token.compare("inherit room") == 0) {
                    if (bFoundType) // bad. only one type per script
                    {
                        reason = "Multiple inherit directives detected. Only one entity type is allowed per script.";
                        return false;
                    }
                    obj_type = EntityType::ROOM;
                    token = "--" + token +" ";
                    file_tokens.push_back(token);

                    bFoundType = true;
                }
                else if (token.compare("inherit player") == 0) {
                    if (bFoundType) // bad. only one type per script
                    {
                        reason = "Multiple inherit directives detected. Only one entity type is allowed per script.";
                        return false;
                    }
                    obj_type = EntityType::PLAYER;
                    token = "--" + token  +" ";
                    file_tokens.push_back(token);
                    bFoundType = true;
                }
                else if (token.compare("inherit item") == 0) {
                    if (bFoundType) // bad. only one type per script
                    {
                        reason = "Multiple inherit directives detected. Only one entity type is allowed per script.";
                        return false;
                    }
                    obj_type = EntityType::ITEM;
                    token = "--" + token +" ";
                    file_tokens.push_back(token);
                    bFoundType = true;
                }
                else if (token.compare("inherit npc") == 0) {
                    if (bFoundType) // bad. only one type per script
                    {
                        reason = "Multiple inherit directives detected. Only one entity type is allowed per script.";
                        return false;
                    }
                    obj_type = EntityType::NPC;
                    token = "--" + token +" ";
                    file_tokens.push_back(token);

                    bFoundType = true;
                }
                else if (token.compare("inherit command") == 0) {
                    if (bFoundType) // bad. only one type per script
                    {
                        reason = "Multiple inherit directives detected. Only one entity type is allowed per script.";
                        return false;
                    }
                    obj_type = EntityType::COMMAND;
                    token = "--" + token  +" ";
                    file_tokens.push_back(token);

                    bFoundType = true;
                }
                else {
                    file_tokens.push_back(token);
                }
            }
            /*
            std::string ff = file_tokens[0];
            file_tokens[0] = "_INTERNAL_PHYSICAL_SCRIPT_PATH_ = '" +
                std::regex_replace(
                    script_path, std::regex(global_settings::Instance().GetSetting(DEFAULT_GAME_DATA_PATH)), "") + "'  ";
            file_tokens[0] += ff;
            script_text += vector_to_string(file_tokens, '\n');  
            */
            

            // std::cout << script_text << std::endl;
            if (bFoundType == false) {
                reason = "No inherit directive found in script.";
                return false;
            }
            return true;
        }
        /*
                static bool LoadScriptFromDisk(std::string& script_path,
                                            std::string& script_text,
                                            EntityType& obj_type,
                                            std::string& reason)
        {
            std::ifstream in(script_path);
            std::stringstream buffer;
            buffer << in.rdbuf();
            return ParseScriptText(buffer, script_path, script_text, obj_type, reason);
        }
        */


        bool GetEntityPathFromIDString(const std::string& entity_id, std::string& entity_script_path, unsigned int& instanceid)
        {
            unsigned int tmp = 0;
            entity_script_path = boost::to_lower_copy(entity_id);
            std::size_t found = entity_script_path.find("id=");

            if(found != std::string::npos) {
                // the id has a id= in it..

                sscanf(entity_script_path.c_str(), "%*[^=]=%u", &tmp);
                entity_script_path.erase(entity_script_path.begin() + found,
                                        entity_script_path.end()); // remove it from the string
            }
            if(entity_script_path[entity_script_path.size() - 1] == '/' ||
            entity_script_path[entity_script_path.size() - 1] == ':') // no need to have this.
            {
                entity_script_path.erase(entity_script_path.size() - 1);
            }

            return true;
        }

    }; //struct ScriptFuncs
} //namespace Trestle
#endif // SCRIPT_FUNCS
