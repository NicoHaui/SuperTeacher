#include "Config.h"

void Config::Read(void)
{
	ResourceManager resource = {};
	auto file_conf = resource.get_json("conf.json");

	if ((bool)(*file_conf)["video"]["fullscreen"]) {
}