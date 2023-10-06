#include <boost/program_options.hpp>
#include <iostream>

using namespace std;

namespace po = boost::program_options;
namespace postyle = boost::program_options::command_line_style;

int main(int argc, char *argv[]){

    // boost::program_options::options_description desc("Options");
    
    po::options_description desc("Options");

    cout << "Test boost options" << endl;

    desc.add_options()
        ("unified,U", po::value<unsigned int>()->default_value(3),
                "Print in unified form with specified number of  "
                "lines from the surrounding context")
        ("print,p", "Print names of C functions "
                " containing the difference")
        ("notexist,N", "When comparing two directories, if a file exists in"
                " only one directory, assume it to be present but "
                " blank in the other directory")
        ("help,h", "Print the help message");

    int unix_style = postyle::unix_style
            | postyle::short_allow_next;

    int windows_style = postyle::allow_long
            | postyle::allow_short
            | postyle::allow_slash_for_short
            // | postyle::allow_slash_for_long
            | postyle::case_insensitive
            | postyle::short_allow_next
            | postyle::long_allow_next;

    po::variables_map vm;
    try{
        po::store(
            po::command_line_parser(argc, argv)
                .options(desc)
                .style(unix_style)
                .run(),
            vm
        );
        po::notify(vm);

        if(argc == 1 || vm.count("help")){
            cout << "Usage: " << argv[0] << endl 
                << desc << endl;
            return 0;
        }

        // cout << "p.count: " << vm.count("print") << endl; 

        if(vm.count("unified")){
            unsigned int context = vm["unified"].as<unsigned int>();
            cout << "unified:" << context << endl;
        }
        if(vm.count("print") > 0){
            cout << "p " << "selected" << endl;
        }
        if(vm.count("notexist") > 0){
            cout << "N " << "selected" << endl;
        }
    }catch(po::error& poe){
        cerr << poe.what() << endl
            << "Usage: " << argv[0] << endl 
            << desc << endl;

        return EXIT_FAILURE;
    }

    return 0;
}