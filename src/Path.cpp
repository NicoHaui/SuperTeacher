#include "Path.h"

#ifdef WIN32
    const std::string PATH_SEP = "\\";
#else
    const std::string PATH_SEP = "/";
#endif

Path::Path(const char * path): buff(path){}

Path Path::operator=(const char* path){
    return Path(path);
}


Path Path::operator+=(const char* path){
    buff += PATH_SEP;
    buff += path;
}

