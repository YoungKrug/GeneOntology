#pragma once
#include <string>
#include <fstream>
#include <unordered_map>
#include "DataBaseTypes.h"
using namespace DataTypes;

class Ontology
{
public:
    enum DelimiterType
    {
        TAB_DELINEATED,
        COMMA_DELINEATED
    };
    enum FileType
    {
        PARENTS,
        CHILDS,
        DEFINITIONS,
        GOACCESSION,
        GENES,
        GOIORNGOI
    };
    void ReadFile(std::string, DelimiterType, FileType);
    void AddToDBBasedOnType(FileType, std::string, std::string);
    std::string DetermineDelimited(DelimiterType);
    std::ifstream OpenFile(std::string);
    std::string GetData(std::string);
private:
    std::unordered_map<std::string, GoInfo> _goInformation;
    std::unordered_map<std::string, TermidInfo> _termidInfo;
};
