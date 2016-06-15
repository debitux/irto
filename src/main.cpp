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


#include <iostream> 
#include <fstream>

#include "boost/date_time/posix_time/posix_time.hpp"

#include "version.hpp"
#include "typedef/exception.hpp"

#include "program_options.hpp"

namespace pt = boost::posix_time;

namespace{
const int SUCCESS =  0;
const int FAILURE = -1;
}


void
finish(void)
{

    std::cerr << "Unhandled Exception reached the top of main\n" 
    << "Exit cleanly" << std::endl;
    exit(EXIT_FAILURE);
}


int 
main(int argc, const char** argv) 
{

    std::set_terminate(finish);
    std::ios::sync_with_stdio(false);// on some platforms, stdout flushes on \n

    std::ofstream file("irto_error.log", std::ios::out | std::ios::app);

    try {
        if(file) {
            dbtx::Program_Options options(argc, argv);
            file.close();  
            return SUCCESS;
        }

        else { 
            std::cerr << "Error on open file irto_error.log ..." << std::endl;
            return FAILURE;
        }
    }
    catch(const dbtx::Exception& e ) { 
        std::string date = pt::to_iso_string(pt::second_clock::local_time());
        file << date << "|Version: " << VERSION << e.get_log();
        file.close();  
        std::cerr << "application will now exit" << std::endl; 
        return FAILURE;
    } 
    catch(std::exception& e) { 
        std::string date = pt::to_iso_string(pt::second_clock::local_time());
        file << date << "|Version: " << VERSION 
        << "Unhandled Exception reached the top of main: " << e.what() 
        << std::endl; 
        file.close();  
        std::cerr << "application will now exit" << std::endl; 
        return FAILURE;
    }

} // main 
