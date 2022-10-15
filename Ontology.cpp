#include "Ontology.h"

#include <iostream>
void Ontology::ReadOncologyDataBase(std::string path, Type delimiterType)
{
    std::ifstream reader;
    std::string line;
    std::string delimiter = DetermineDelimited(delimiterType);
    reader = OpenFile(path);
     while(std::getline(reader, line))
     {
         size_t pos = 0;
         std::string key;
         bool isFirst = true;
         while ((pos = line.find(delimiter)) != std::string::npos)
         {
             std::string token;
             token = line.substr(0, pos);
             if(isFirst) // will be used as the key
             {
                 if(_data.find(token) == _data.end())
                 {
                     key = token;
                     //doesnt contain key
                     _goData.insert({token, std::vector<std::string>()});
                     isFirst = false;
                 }
             }
             else
                 _goData[key].emplace_back(token);
             line.erase(0, pos + delimiter.length());
         }
         _goData[key].emplace_back(line);
    }
}

void Ontology::ReadGenes(std::string path, Type delimiterType)
{
    std::ifstream reader;
    std::string line;
    std::string delimiter = DetermineDelimited(delimiterType);
    reader = OpenFile(path);
    while(std::getline(reader, line))
    {
        size_t pos = 0;
        std::string gene;
        std::string token;
        bool isFirst = true;
        while ((pos = line.find(delimiter)) != std::string::npos)
        {
            token = line.substr(0, pos);
            if(isFirst) // will be used as the key
            {
                gene = token;
                isFirst = false;
            }
            else
                _data[token].genes.emplace_back(gene);
            line.erase(0, pos + delimiter.length());
        }
        _data[token].genes.emplace_back(line);
    }
}

void Ontology::ReadChildren(std::string path, Type delimiterType)
{
    std::ifstream reader;
    std::string line;
    std::string delimiter = DetermineDelimited(delimiterType);
    reader = OpenFile(path);
    while(std::getline(reader, line))
    {
        size_t pos = 0;
        std::string key;
        std::string token;
        bool isFirst = true;
        while ((pos = line.find(delimiter)) != std::string::npos)
        {
            token = line.substr(0, pos);
            if(isFirst) // will be used as the key
            {
                key = token;
                isFirst = false;
            }
            else
            {
                _data[key].children.emplace_back(token);
            }
            line.erase(0, pos + delimiter.length());
        }
        _data[key].children.emplace_back(line);
    }
}
void Ontology::ReadParents(std::string path, Type delimiterType)
{
    std::ifstream reader;
    std::string line;
    std::string delimiter = DetermineDelimited(delimiterType);
    reader = OpenFile(path);
    while(std::getline(reader, line))
    {
        size_t pos = 0;
        std::string key;
        std::string token;
        bool isFirst = true;
        while ((pos = line.find(delimiter)) != std::string::npos)
        {
            token = line.substr(0, pos);
            if(isFirst) // will be used as the key
            {
                key = token;
                isFirst = false;
            }
            else
            {
                _data[key].parent.emplace_back(token);
            }
            line.erase(0, pos + delimiter.length());
        }
        _data[key].parent.emplace_back(line);
    }
}

void Ontology::ReadDefinitions(std::string path, Type delimiterType)
{
    std::ifstream reader;
    std::string line;
    std::string delimiter = DetermineDelimited(delimiterType);
    reader = OpenFile(path);
    while(std::getline(reader, line))
    {
        size_t pos = 0;
        std::string key;
        std::string token;
        bool isFirst = true;
        while ((pos = line.find(delimiter)) != std::string::npos)
        {
            token = line.substr(0, pos);
            if(isFirst) // will be used as the key
            {
                key = token;
                isFirst = false;
            }
            line.erase(0, pos + delimiter.length());
        }
        _data[key].otherInformation.emplace_back(line);
    }
}

Ontology::OntologyNode Ontology::GetData(std::string key)
{
    return _data[key];   
}

std::ifstream Ontology::OpenFile(std::string path)
{
    std::ifstream reader;
    reader.open(path);
    while(!reader.is_open())
    {
        std::cin >> path;
        reader.open(path);
    }
    return reader;
}

std::string Ontology::DetermineDelimited(Type delimiterType)
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
