#pragma once
#include <memory>
#include "JSON.h"
#include "ResourceManager.h"

class Config{
public:
	void Read(void);
private:
	struct param
	{
		std::string categorie;
		std::string name;
		int type;		//0:Bool,1:Int,2:Char,3:String
	};
	const param pTab[]=
	{
		{"video","fullscreen",0}
	};
};