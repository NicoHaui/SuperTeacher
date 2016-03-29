#include "Path.h"
#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>

using namespace std;

#ifdef WIN32
    const std::string SEP = "\\";
#else
    const std::string SEP = "/";
#endif

Path::Path(const char * path): buff(path){}

Path Path::operator=(const char* path){
    return Path(path);
}


Path& Path::operator+=(const char* path){
    buff += SEP;
    buff += path;
    return *this;
}


std::string get_file(std::string file) {

    for(auto i = SEARCH_PATHS_PREFIX.begin(); i != SEARCH_PATHS_PREFIX.end(); ++i) {
        string prefix = *i;

        for(auto y = SEARCH_PATHS_SUFFIX.begin(); y != SEARCH_PATHS_SUFFIX.end(); ++y) {
            string path = prefix + SEP + *y + SEP + file;

            if(boost::filesystem::exists(path)){
                return path;
            }
        }
    }


    return file;
}

