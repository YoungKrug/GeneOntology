#pragma once
#include <iostream>
#include <string.h>
#include <vector>
namespace DataTypes
{
	struct GoInfo
	{
		std::string goAccessionId;
		std::string termidId;
		std::string goSection;
		std::string name;
	};
	struct TermidInfo
	{
		std::string termidId;
		std::vector<std::string> childtermidId;
		std::vector<std::string> parentTermidId;
		std::vector<std::string> geneId;
		std::string definition;
		bool isGOI = false;
	};

};