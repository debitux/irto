/*
 *    Copyright 2016 Grégory Muller
 * 
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 * 
 *        http://www.apache.org/licenses/LICENSE-2.0
 * 
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#ifndef DEBITUX_EXCEPTIONS_HPP
#define DEBITUX_EXCEPTIONS_HPP

#include <sstream>
#include <exception>


namespace dbtx {

enum error_lvl {
    LOW, 
    MEDIUM, 
    HIGH, 
    CRITICAL
};

class Exception : public std::exception
{
public:
    Exception(error_lvl level           =  LOW,
              std::string const& except =  "",
              int number                =  0,
              int line                  =  0,
              std::string const& file   =  "",
              std::string const& func   =  "")
    throw() : 
        m_level(level), 
        m_except(except), 
        m_error_number(number), 
        m_line(line),  
        m_file(file),
        m_func(func)
    {}

    virtual const char* 
    what() const throw() {
        return m_except.c_str();
    }

    std::string 
    get_log() const throw() {
        std::string str ;
        std::ostringstream oss ;
        oss << "|lvl: " << m_level  
        << "|Desc: " << m_except  
        << "|Func: " << m_func  
        << "|File: " << m_file  
        << "|Line: " << m_line  
        << "|Num: " << m_error_number << std::endl;

        const std::string& tmp = oss.str(); 

        return tmp;
    }

    error_lvl 
    get_level() const throw() {
        return m_level;
    }

    const char* 
    get_file() const throw() {
        return m_file.c_str();
    }

    int 
    get_line() const throw() {
        return m_line;
    }

    int 
    get_number() const throw() {
        return m_error_number;
    }

    const char * 
    get_func() const throw() {
        return m_func.c_str();
    }

    virtual ~Exception() throw()
    {}

private:
    int           m_error_number;
    std::string   m_except;
    std::string   m_file;
    std::string   m_func;
    error_lvl     m_level;
    int           m_line;
};

} // namespace dbtx

#endif // DEBITUX_EXCEPTIONS_HPP
