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

#ifndef DEBITUX_PROGRAM_OPTIONS_HPP
#define DEBITUX_PROGRAM_OPTIONS_HPP

#include "typedef/memory.hpp"

#include "boost/program_options.hpp" 

namespace dbtx {

namespace po   =  boost::program_options;

/**
 * \brief manage programmes options.
 * \details parse and handle the programmes options
 */
class Program_Options
{
public:
    Program_Options();
    /**
     * \brief  Constructor
     * \details
     * \param[in]  argc  main argc transfer
     * \param[in]  argv  main argv transfer
     */
    Program_Options(int argc, const char** argv);
    ~Program_Options();

    using Commands =  std::map<std::string, pointer<po::options_description>>;

private:

    std::ostringstream   get_help(const std::string&,
                                  pointer<po::options_description>);
    void                 check_options();
    bool                 check_command();
    std::string          get_main_help();
    void                 init_main_description();
    int                  main_options();

    void                 init_new_description();
    void                 new_options();
    void                 init_build_description();
    void                 build_options();

    std::string app_name         =  "none";
    std::string command          =  "none";
    std::string subcommand       =  "none";

    std::string project_path     =  "none";
    std::string project_name     =  "none";
    std::string project_template =  "none";
    int         build_jobs       =  0;

    po::variables_map                    vm;
    pointer<Commands>                    command_container;
    pointer<po::parsed_options>          parsed;

    pointer<po::options_description>     main_desc;
    pointer<po::options_description>     new_desc;
    pointer<po::options_description>     build_desc;

    po::positional_options_description   pos_options;
};

} // namespace dbtx 

#endif // DEBITUX_PROGRAM_OPTIONS_HPP 

