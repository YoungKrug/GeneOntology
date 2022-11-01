﻿#include "Ontology.h"

#include <chrono>
#include <corecrt_io.h>
#include <iostream>
#include <regex>

void Ontology::ReadFile(std::string filePath, DelimiterType dType, FileType fType)
{
    std::ifstream reader;
    std::string line;
    std::string demlimiter = "";
    std::string fileEnum = "";
    if (dType == NONE)
    {
        while (_demlimiterTypeStrings.find(demlimiter) == _demlimiterTypeStrings.end())
        {
            std::cout << "Please enter a 't' for tab delimiters or a 'c' for comma delimiters" << std::endl;
            std::cin >> demlimiter;
            demlimiter = std::string(1, toupper(demlimiter[0]));
        }
    }
    if (fType == NO)
    {
        while (_fileTypeStrings.find(fileEnum) == _fileTypeStrings.end())
        {
            std::cout << "Please enter 'P' for parent files, 'C' for children files, 'D' for definitions\n"
                << "'A' for Go Associations, 'G' for genes, and 'N' for Genes of interest" << std::endl;
            std::cin >> fileEnum;
            fileEnum = std::string(1, toupper(fileEnum[0]));
        }
    }
    std::string finalDelimiter = demlimiter == "" ? DetermineDelimited(dType) : DetermineDelimited(_demlimiterTypeStrings[demlimiter]);
    FileType finalFileType = fileEnum == "" ? fType : _fileTypeStrings[fileEnum];
    reader = OpenFile(filePath);
    while(std::getline(reader, line))
    {
        AddToDBBasedOnType(finalFileType, line, finalDelimiter);
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
                    if(_termidInfo.find(key) == _termidInfo.end()) // which means key is not there
                    {
                        _termidInfo.insert({key, info});
                    }
                }
                else if(i == 1)
                {
                    if(_goInformation.find(currentString) == _goInformation.end()) // which means key is not there
                    {
                        _goInformation.insert({currentString, goInfo});
                    }
                
                    _goInformation[currentString].termidId = key;
                    _termidInfo[key].goAccession = currentString;
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
                    _totalNumberOfGenes++;
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
                _genesOfIntersts.insert({key, (bool)num});
                if((bool)num)
                    _GOIS.emplace_back(key);
                //_termidInfo[key].isGOI = (bool)num;
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

void Ontology::CalculateTermidInformationForTest()
{
    double p_value = ((double)_genesOfIntersts.size()/3.5)/_totalNumberOfGenes;
    std::cout <<"P-Value: " << p_value << std::endl;
    std::cout <<"Below are the significant values in the Ontology: \n";
    double N_GOIs = 0;
    double totalGenesAsscoiated = 0;
    double totalGenesNotAssociated = 0;
    std::unordered_map<std::string, bool> duplicateList;
    for(auto i : _termidInfo)
    {
        double NGOI_GOI = 0;
        double genesAssociatedWithTerm = 0;
        double genesNot_GOI_NGOI = 0;
        for(auto genes : i.second.geneId)
        {
            if(duplicateList.find(genes) != duplicateList.end())
                continue;
            if(_genesOfIntersts.find(genes) != _genesOfIntersts.end())
            {
                //if(_genesOfIntersts[genes])
                NGOI_GOI++; //Only GOI
            }
            else
            {
                genesNot_GOI_NGOI++;
            }
            genesAssociatedWithTerm++;
            duplicateList.insert({genes, true});
            
        }
        for(auto children : i.second.childtermidId)
        {
            
            TermidInfo temp = _termidInfo[children];
            for(auto genes : temp.geneId)
            {
                if(duplicateList.find(genes) != duplicateList.end())
                    continue;
                if(_genesOfIntersts.find(genes) != _genesOfIntersts.end())
                {
                    //if(_genesOfIntersts[genes])
                        NGOI_GOI++;
                }
                else
                {
                    genesNot_GOI_NGOI++;
                }
                genesAssociatedWithTerm++;
                duplicateList.insert({genes, true});
            }
        }
        N_GOIs += NGOI_GOI;
        totalGenesAsscoiated += genesAssociatedWithTerm;
        totalGenesNotAssociated += genesNot_GOI_NGOI;
        if(NGOI_GOI <= 0) // GOI C GOIS+NGOI * TOTALGENES - GOI+NGOI C GOI +NGOI - GOIs / (Population / sample)
            continue;
      
        // double val = HyperGeometricDistrubition(_totalNumberOfGenes, static_cast<double>(_GOIS.size()),
        //     static_cast<double>(_genesOfIntersts.size()) , static_cast<double>(_genesOfIntersts.size()));
        //if(val > p_value)
           // std::cout << "Go Accession: " << i.second.goAccession << "  Value: " << val << std::endl;
    }
     double val = HyperGeometricDistrubition(_totalNumberOfGenes, N_GOIs,
        totalGenesAsscoiated , totalGenesNotAssociated);
    
}

void Ontology::DisplayValue(std::string goAccession)
{
    GoInfo info = _goInformation[goAccession];
    info.Print();
    _termidInfo[info.termidId].Print(_termidInfo, _genesOfIntersts);
}

double Ontology::Combination(int n, int r)
{

    double factorialOfN = n;
    for (int i = n - 1; i > n - r; i--)
    {
        factorialOfN *= i;
    }
    if(r > 500)
        return 0;
    double factorialOfR = Factorial(r);
    return (factorialOfN)/(factorialOfR);
}

void Ontology::GenerateRandomGenes()
{
        std::vector<std::string> genes;
        const int count = static_cast<int>(_GOIS.size());
        std::mt19937 generator (std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_real_distribution<double> dis(0, _genesOfIntersts.size());
        for(const auto i : _GOIS)
        {
            _genesOfIntersts[i] = false;
        }
    CalculateTermidInformationForTest();
        _GOIS.clear();
        for(int i = 0; i < count; i++)
        {
            int ranNum = dis(generator);
            auto val = std::unordered_map<std::string, bool>::iterator{_genesOfIntersts.begin()};
            std::advance(val, ranNum);
            val->second = true;
            _GOIS.emplace_back(val->first);
        }
        CalculateTermidInformationForTest();
}

/**
 * \brief 
 * \param population
 * \param successInInitialPopulation 
 * \param sampleSize 
 * \param initialPopulation 
 * \return 
 */
double Ontology::HyperGeometricDistrubition(double population, double successInInitialPopulation, double sampleSize, double initialPopulation)
{
    int otherPop = population - initialPopulation;
    double probOfInitial = Combination(initialPopulation, successInInitialPopulation);
    double probOfOther = Combination(otherPop, sampleSize - successInInitialPopulation);
    double probOfPopulation = Combination(population, sampleSize);
    return (probOfInitial * probOfOther)/probOfPopulation;
}

double Ontology::Factorial(int x)
{
    if(x == 0)
        return 1;
    return x * Factorial(x - 1);
}
