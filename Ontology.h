#pragma once
#include <string>
#include <fstream>
#include <unordered_map>

class Ontology
{
public:
    enum Type
    {
        TAB_DELINEATED,
        COMMA_DELINEATED
    };
    struct OntologyNode
    {
        std::vector<std::string> children;
        std::vector<std::string> parent;
        std::vector<std::string> otherInformation;
        std::vector<std::string> genes;
    };
    void ReadOncologyDataBase(std::string, Type);
    void ReadGenes(std::string, Type);
    void ReadChildren(std::string, Type);
    void ReadParents(std::string, Type);
    void ReadDefinitions(std::string, Type);
    OntologyNode GetData(std::string);
    std::ifstream OpenFile(std::string);
    std::string DetermineDelimited(Type);
  
private:
    std::unordered_map<std::string, OntologyNode> _data;
    std::unordered_map<std::string,std::unordered_map<std::string, std::vector<std::string>>> _goData;
};
