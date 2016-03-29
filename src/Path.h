#pragma once
#include <string>
class Path{
public:
    Path(const char * path);
    Path operator=(const char* path);
    Path operator+=(const char* path);
private:
    std::string buff;
};

const Path PATH_INSTALL_DIR = _INSTALL_PREFIX;



const std::string FONT_INDIE_FLOWER = "/usr/local/share/superteacher/fonts/ThirdParty/IndieFlower/IndieFlower.ttf";
const std::string SONG_1 = "/usr/local/share/superteacher/audio/ThirdParty/hold-the-line-orchestral-remix/hold the line_0.flac";


