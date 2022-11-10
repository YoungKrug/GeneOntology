#pragma once
#include <iostream>
#include <string.h>
#include <vector>
#include <unordered_map>
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
		std::string goAccession;
		bool isGOI = false;
		double p_value = 0;
		void Print(std::unordered_map<std::string ,TermidInfo> _info, std::unordered_map<std::string, bool> _genesOfInterest)
		{
			int GOIs = 0;
			int nGOIs = 0;
			int totalGenes = 0;
			for(auto i : childtermidId)
			{
				totalGenes += (int)_info[i].geneId.size();
				for(auto genes :_info[i].geneId)
				{
					 if(_genesOfInterest.find(genes) == _genesOfInterest.end())
					 	continue;
					if(_genesOfInterest[genes])
					{
						GOIs++;
					}
					else
					{
						nGOIs++;
					}
				}
			}
			for(auto i : geneId)
			{
				if(_genesOfInterest.find(i) == _genesOfInterest.end())
					continue;
				if(_genesOfInterest[i])
				{
					GOIs++;
				}
				else
				{
					nGOIs++;
				}
			}
			totalGenes += (int)geneId.size();
			std::cout << "TermidID: " << termidId << "\nChildren: " << childtermidId.size() <<
				"\nGOIs: " << GOIs << "\nNGOIs: " << nGOIs << 
				"\nNumber of Genes: " << totalGenes <<std::endl;
		}
	};

};