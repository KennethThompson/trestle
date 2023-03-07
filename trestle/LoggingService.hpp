// ==========================================================================
// LoggingService.hpp
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
#ifndef _LOG_INTERFACE_HPP_
#define _LOG_INTERFACE_HPP_

namespace trestle
{
    enum class LOGLEVEL : int { LOGLEVEL_INFO, LOGLEVEL_ERROR, LOGLEVEL_CRITICAL, LOGLEVEL_DEBUG };
    struct LoggingService
    {
        
    public:
        static LoggingService & Instance()
        {
            // Since it's a static variable, if the class has already been created,
            // It won't be created again.
            // And it **is** thread-safe in C++11.

            static LoggingService myInstance;

            // Return a reference to our instance.
            return myInstance;
        }

        // delete copy and move constructors and assign operators
        LoggingService(LoggingService const&) = delete;             // Copy construct
        LoggingService(LoggingService&&) = delete;                  // Move construct
        LoggingService& operator=(LoggingService const&) = delete;  // Copy assign
        LoggingService& operator=(LoggingService &&) = delete;      // Move assign
        

        void log_error(std::string msg);
        void log(LOGLEVEL log_level, std::string msg);
        void log(LOGLEVEL log_level, std::string script_path, std::string msg);
        
        
    protected:
        LoggingService()
        {
        
        }

        ~LoggingService()
        {
            // Destructor code goes here.
        }    
        
    private:
    
        
    };
}
#endif