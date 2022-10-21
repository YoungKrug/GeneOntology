#include "Ontology.h"

#include <iostream>
#include <regex>

void Ontology::ReadFile(std::string filePath)
{
    std::ifstream reader;
    std::string line;
    std::string demlimiter;
    std::string fileEnum;
    std::cout << _demlimiterTypeStrings.size() <<std::endl;
    while(_demlimiterTypeStrings.find(demlimiter) == _demlimiterTypeStrings.end())
    {
        std::cout << "Please enter a 't' for tab delimiters or a 'c' for comma delimiters" << std::endl;
        std::cin >> demlimiter;
        demlimiter = std::string(1,toupper(demlimiter[0]));
    }
    while(_fileTypeStrings.find(fileEnum) == _fileTypeStrings.end())
    {
        std::cout << "Please enter 'P' for parent files, 'C' for children files, 'D' for definitions\n"
        << "'A' for Go Associations, 'G' for genes, and 'N' for Genes of interest" << std::endl;
        std::cin >> fileEnum;
        fileEnum = std::string(1,toupper(fileEnum[0]));
    }
    std::string delimiter = DetermineDelimited(_demlimiterTypeStrings[demlimiter]);
    reader = OpenFile(filePath);
    while(std::getline(reader, line))
    {
        AddToDBBasedOnType(_fileTypeStrings[fileEnum], line, delimiter);
    }
}
void Ontology::AddToDBBasedOnType(FileType fileType, std::string line, std::string delimiter)
{
    std::string key;
    std::string a;
    a.append("[^").append(delimiter).append("]+");
    std::regex e (a);   // matches delimiters or consecutive non-delimiters
    std::regex_iterator<std::string::iterator> rit ( line.begin(), line.end(), e );
    std::regex_iterator<std::string::iterator> rend;
    int i = 0;
    while (rit!=rend)
    {
        std::string currentString = rit->str();
        TermidInfo info;
        GoInfo goInfo;
        switch(fileType)
        {
            case PARENTS:
                if(i == 0) // the first key is the termid
                {
                    key = currentString;
                    if(_termidInfo.find(key) == _termidInfo.end()) // which means key is
                    {
                        _termidInfo.insert({key, info});
                    }
                    _termidInfo[key].termidId = key;
                }
                else
                {
                    _termidInfo[key].parentTermidId.emplace_back(currentString);
                }
                break;
            case CHILDS:
            if(i == 0) // the first key is the termid
            {
                key = currentString;
                if(_termidInfo.find(key) == _termidInfo.end()) // which means key is
                {
                    _termidInfo.insert({key, info});
                }
                _termidInfo[key].termidId = key;
            }
            else
            {
                _termidInfo[key].childtermidId.emplace_back(currentString);
            }
                break;
            case DEFINITIONS:
                if(i == 0) // the first key is the termid
                {
                    key = currentString;
                    if(_termidInfo.find(key) == _termidInfo.end()) // which means key is
                    {
                        _termidInfo.insert({key, info});
                    }
                    _termidInfo[key].termidId = key;
                }
            else
            {
                _termidInfo[key].definition = currentString;
            }
                break;
            case GOACCESSION:
                if(i == 0)
                {
                    //termid Id
                    key = currentString;
                    if(_termidInfo.find(key) == _termidInfo.end()) // which means key is
                    {
                        _termidInfo.insert({key, info});
                    }
                }
                else if(i == 1)
                {
                    if(_goInformation.find(currentString) == _goInformation.end()) // which means key is
                    {
                        _goInformation.insert({currentString, goInfo});
                    }
                
                    _goInformation[currentString].termidId = key;
                    key = currentString;
                }
                else if(i == 2)
                {
                    _goInformation[key].goSection = currentString;
                }
                else if(i == 3)
                {
                    _goInformation[key].name = currentString;
                }
                break;
            
            case GENES:
                if(i == 0) // the first key is the termid
                {
                    key = currentString; // key is gene
                    _termidInfo[currentString].termidId = currentString;
                }
                else
                {
                    _termidInfo[currentString].geneId.emplace_back(key);
                }
            break;
            case GOIORNGOI:
            if(i == 0) // the first key is the termid
            {
                key = currentString; // key is gene
            }
            else
            {
                int num = std::stoi(currentString);
                _termidInfo[key].isGOI = (bool)num;
            }
                
            break;
        }
        ++rit;
        i++;
    }
}
std::string Ontology::DetermineDelimited(DelimiterType delimiterType)
{
    switch (delimiterType)
    {
    case TAB_DELINEATED:
        return"\t";
    case COMMA_DELINEATED:
        return ",";
    }
    return "";
    
}
std::ifstream Ontology::OpenFile(std::string path)
{
    std::ifstream reader;
    reader.open(path);
    while(!reader.is_open())
    {
        std::cout <<"Please re-enter your path" << std::endl;
        std::cin >> path;
        reader.open(path);
    }
    return reader;
}

void Ontology::DisplayValue(std::string goAccession)
{
    GoInfo info = _goInformation[goAccession];
    info.Print();
    _termidInfo[info.termidId].Print();
}
