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
    void ReadFile(std::string);
    void AddToDBBasedOnType(FileType, std::string, std::string);
    std::string DetermineDelimited(DelimiterType);
    std::ifstream OpenFile(std::string);
    void DisplayValue(std::string);
private:
    std::unordered_map<std::string, GoInfo> _goInformation;
    std::unordered_map<std::string, TermidInfo> _termidInfo;
  //  std::vector<std::string> _fileTypeStrings = {"P", "C", "D", "A", "G", "N"};
  //  std::vector<std::string> _demlimiterTypeStrings = {"T", "C"};
    std::unordered_map<std::string, FileType> _fileTypeStrings ={ {"P", PARENTS},{"C", CHILDS},{"D", DEFINITIONS},{"A", GOACCESSION},{"G", GENES},{"N", GOIORNGOI} };
    std::unordered_map<std::string, DelimiterType> _demlimiterTypeStrings ={ {"C", COMMA_DELINEATED},{"T", TAB_DELINEATED}};
    std::unordered_map<std::string, bool> _genesOfIntersts;
};
