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

#define BOOST_TEST_DYN_LINK          
#define BOOST_TEST_MODULE Program_Options_Test    

#include <boost/test/unit_test.hpp>
#include "../src/program_options.hpp" 

BOOST_AUTO_TEST_CASE(Object_creation0)
{
        dbtx::Program_Options* obj = new dbtx::Program_Options();
        BOOST_CHECK( obj != nullptr );

        delete obj;
}

BOOST_AUTO_TEST_CASE(Object_creation1)
{
    const int argc = 3;
    const char *argv[argc] = {"0", "build", "-j22" };

        dbtx::Program_Options* obj = new dbtx::Program_Options(argc, argv);
        BOOST_CHECK( obj != nullptr );

        delete obj;
}

BOOST_AUTO_TEST_CASE(Object_creation2)
{
    const int argc = 3;
    const char *argv[argc] = { "0", "help", "new" };

        dbtx::Program_Options* obj = new dbtx::Program_Options(argc, argv);
        BOOST_CHECK( obj != nullptr );

        delete obj;
}


BOOST_AUTO_TEST_CASE(Object_creation3)
{
    const int argc = 6;
    const char *argv[argc] = { "0", "new", "-n=name", "-G", "-W", "-O" };

        dbtx::Program_Options* obj = new dbtx::Program_Options(argc, argv);
        BOOST_CHECK( obj != nullptr );

        delete obj;
}

BOOST_AUTO_TEST_CASE(Object_creation4)
{
    const int argc = 2;
    const char *argv[argc] = { "0", "--list"};

        dbtx::Program_Options* obj = new dbtx::Program_Options(argc, argv);
        BOOST_CHECK( obj != nullptr );

        delete obj;
}
