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
		void Print()
		{
			std::cout << "Accession Number: " << goAccessionId << "\nTermidID: " << termidId << "\nGoSection: " << goSection << std::endl;
		}
	};
	struct TermidInfo
	{
		std::string termidId;
		std::vector<std::string> childtermidId;
		std::vector<std::string> parentTermidId;
		std::vector<std::string> geneId;
		std::string definition;
		bool isGOI = false;
		void Print()
		{
			std::string children;
			std::string parents;
			std::string genes;
			for(auto i : childtermidId)
			{
				children.append(i + " : ");
			}
			for(auto i : parentTermidId)
			{
				parents.append(i + " : ");
			}
			for(auto i : geneId)
			{
				genes.append(i + " : ");
			}
			std::cout << "TermidID: " << termidId << "\nChildren: " << children << "\n Parents: "
			<< parents << "\nGenes: " << genes << "\nisGOI: " << isGOI << std::endl;
		}
	};

};