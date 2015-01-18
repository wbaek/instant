#include <iostream>
#include <vector>

#include "utils/string.hpp"

#include "benchmark.hpp"

#include <getopt.h>
void help(char* execute) {
    std::cout << "usage: " << execute << " [-h] -i INPUT_STRING -d DELIMITER" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "\t-h, --help                       show this help mesage and exit" << std::endl;
    std::cout << "\t-i, --input      INPUT_STRING    set input string" << std::endl;
    std::cout << "\t-d, --delimiter  DELIMITER       set delimiter string" << std::endl;
    exit(-1);
}

int main(int argc, char* argv[]) {
    static struct option long_options[] = {
        {"help",       no_argument,       0, 'h'},
        {"input",      required_argument, 0, 'i'},
        {"delimiter",  required_argument, 0, 'd'},
    };

    benchmark("entire") {
        std::string inputString;
        std::string delimiter;

        benchmark("parse arguments") {
            int argopt, option_index=0;
            while( (argopt = getopt_long(argc, argv, "hi:d:", long_options, &option_index)) != -1 ) {
                switch(argopt) {
                    case 'h':
                        help(argv[0]);
                        break;
                    case 'i':
                        inputString = std::string(optarg);
                        break;
                    case 'd':
                        delimiter = std::string(optarg);
                        break;
                    default:
                        help(argv[0]);
                        break;
                }
            }

            if( inputString.size() == 0 || delimiter.size() == 0 ) {
                help(argv[0]);
                return -1;
            }
        }

        std::vector<std::string> splitedList;
        benchmark("split string") {
            splitedList = instant::Utils::String::Split(inputString, delimiter);
        }

        benchmark("print results") {
            std::cout << instant::Utils::String::Join(splitedList, "\n") << std::endl;
        }
    }

    return 0;
}
