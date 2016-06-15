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
#include <sstream> 
#include <string> 

#include "boost/filesystem.hpp" 

#include "version.hpp"

#include "typedef/exception.hpp"
#include "program_options.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;

namespace po = boost::program_options; 
namespace fs = boost::filesystem; 

namespace dbtx {


Program_Options::Program_Options()
{}


Program_Options::Program_Options(int argc, const char** argv)
{
    try { 
        app_name          =  fs::basename(argv[0]);

        main_desc         =  new_ptr<po::options_description>("Options");
        new_desc          =  new_ptr<po::options_description>("Options");
        build_desc        =  new_ptr<po::options_description>("Options");

        command_container =  new_ptr<Commands>( Commands {
                                                {"new"   , new_desc}, 
                                                {"build" , build_desc}
                                                });
        init_main_description();
        init_new_description();
        init_build_description();

        try { 
            parsed  = 
            new_ptr<po::parsed_options>( po::command_line_parser(argc, argv).
                                         options(*main_desc).
                                         positional(pos_options).
                                         allow_unregistered().
                                         run());

            po::store(*parsed, vm);

            check_options();
        } 
        catch(boost::program_options::required_option& e) { 
            throw Exception(LOW, e.what(), 
                            2, __LINE__, fs::basename(__FILE__), __func__);
        } 
        catch(boost::program_options::error& e) { 
            throw Exception(LOW, e.what(), 
                            2, __LINE__, fs::basename(__FILE__), __func__);
        } 
    } 
    catch(const Exception& e ) { 
        if (e.get_level() == LOW) {
            cout << get_main_help() << endl ;
        }
    } 
}



Program_Options::~Program_Options()
{}



std::ostringstream 
Program_Options::get_help(const string& commande, 
                          pointer<po::options_description> od )
{
    std::ostringstream oss;

    oss << "Usage:\n"
    << "   app_name " << commande <<" [options]\n\n" << *od << endl;

    return oss;
}



void
Program_Options::check_options()
{
    bool loop = true;

    int verify = main_options();
    if(verify != 0) {
        while(loop) {
            if (command == "help") {
                for (auto c : *command_container) {
                    if ( subcommand == c.first) { 
                        cout << get_help(c.first, c.second).str();
                        loop = false;
                    }
                }
                if(loop){
                    cout << get_main_help() << endl ;
                    loop = false;
                }
            }
            else if (check_command() == true && loop == true) {
                loop = false;
            }

            if(loop){
                cout << get_main_help() << endl ;
                loop = false;
            }
        }
    }
}



bool
Program_Options::check_command()
{
    string com_name;
    pointer<po::options_description> com_desc;

    for (auto com : *command_container) {
        com_name = com.first;
        com_desc = com.second;
        if (command == com_name) {
            vector<string> opts = 
            po::collect_unrecognized(parsed->options, 
                                     po::include_positional);
            opts.erase(opts.begin());
            po::store(po::command_line_parser(opts).
                      options(*com_desc).
                      run(), vm);

            po::notify(vm);

            if ( com_name == "new") {
                new_options();
            }
            else if ( com_name == "build") {
                build_options();

            }

            return true;
        }
    }

    return false;
}

/*
 *  Commandes
 */

// Main Options

string
Program_Options::get_main_help()
{
    std::ostringstream main_help ;

    main_help << app_name << "\n" 
    << "C++ package manager\n\n"
    << "Usage:\n"
    << "   " << app_name << " <command> [<args>...]\n" 
    << "   " << app_name << " [options]\n\n" 
    << *main_desc << "\n\n"
    << "Some common " << app_name << " commands are:\n"
    << "    new          create a new project\n"
    << "    build        Compile the current project\n\n"
    << "See '" << app_name << " help <command>' for more information on a specific command." 
    << endl ;

    return main_help.str();
}



void
Program_Options::init_main_description()
{

    main_desc->add_options() 
    ("help,h",      "Display this message") 
    ("version,V",   "Print version info and exit") 
    ("verbose,v",   "Use verbose output") 
    ("list,l",      "List installed commands") 
    ("command",     po::value<string>(&command), "commands  : help, new, build ...") 
    ("subcommand",  po::value<string>(&subcommand), "subcommands") 
    ("subargs",     po::value<vector<string> >(), "Arguments for command");

    pos_options.add("command", 1). 
    add("subcommand", 2). 
    add("subargs", -1);
}



int 
Program_Options::main_options()
{
    int var = 1;
    if ( vm.count("help") ) { 
        cout << get_main_help();
        var = 0;
    } 
    else if ( vm.count("version")  ) { 
        cout << app_name << " " << VERSION << " build at " << BUILD_DATE << endl;
        var = 0;
    }
    else if ( vm.count("list")  ) { 
        cout << "list of commands :" << endl;
        for (auto c : *command_container) {
            cout << "    " << c.first << endl;
        }
        var = 0;
    }
    else if ( vm.count("verbose") ) { 
        std::cout << "VERBOSE PRINTING" << std::endl; 
        var = 0;
    } 

    po::notify(vm);  

    return var;
}

// new

void
Program_Options::init_new_description()
{   

    new_desc->add_options()
    ("name,n",              po::value<string>(&project_name), 
     "project name (default proj)")

    ("here,H",                "create project in courant directory")
    ("path,p",              po::value<string>(&project_path), 
     "directory for create project")
    ("use-template,t",      po::value<string>(&project_template), 
     "template to use for create project default : cpp")
    ("list-template,L",     "List template available")

    ("makefile_gcc,G",      "Project for Gnu/Gcc (default)")
    ("makefile_visual,W",   "Project for visual studio")
    ("makefile_osx,O",      "Project for Xcode");
}



void 
Program_Options::new_options()
{

    if ( vm.count("here")  ) { 
        cout << "here\n"
        << "name :" << project_name << "\n"
        << "gnu :" << vm.count("makefile_gcc") << "\n"
        << "visual :"  << vm.count("makefile_visual") << "\n"
        << "osx :"  << vm.count("makefile_osx") << endl ;
    }
    else if ( vm.count("path")  ) { 
        cout << "path to create : " << project_path << "\n"
        << "name :" << project_name << "\n"
        << "gnu :" << vm.count("makefile_gcc") << "\n"
        << "visual :"  << vm.count("makefile_visual") << "\n"
        << "osx :"  << vm.count("makefile_osx") << endl ;
    }
    else if ( vm.count("list-template")  ) { 
        cout << "Template available : \n" 
        << "cpp       :   c++ app project\n" 
        << "cpplib    :   c++ lib project\n" << endl ;

    }
}

// build

void
Program_Options::init_build_description()
{

    build_desc->add_options() 
    ("verbose,v",   "verbose mode") 
    ("jobs,j",      po::value<int>(&build_jobs), 
     "The number of jobs to run in parallel");
}



void 
Program_Options::build_options()
{

    if ( vm.count("jobs")  ) { 
        cout << "jobs : " << build_jobs << endl ;
    }
}

} // namespace dbtx 
