#pragma once
#include <string>
#include <fstream>
#include <unordered_map>
#include <random>
#include <ctime>
#include "DataBaseTypes.h"
using namespace DataTypes;

class Ontology
{
public:
    enum DelimiterType
    {
        TAB_DELINEATED,
        COMMA_DELINEATED,
        NONE
    };
    enum FileType
    {
        PARENTS,
        CHILDS,
        DEFINITIONS,
        GOACCESSION,
        GENES,
        GOIORNGOI,
        NO
    };
    void ReadFile(std::string, DelimiterType dType = DelimiterType::NONE, FileType fType = FileType::NO);
    void AddToDBBasedOnType(FileType, std::string, std::string);
    std::string DetermineDelimited(DelimiterType);
    std::ifstream OpenFile(std::string);
    double CalculateTermidInformationForTest();
    void DisplayValue(std::string);
    double Combination(int,int);
    void PrintToOutFile() const;
    void GenerateRandomGenes();
    /**
     * \brief
     * Population
     * SuccessInPop
     * sampleSize
     * initialPopulation
     * \return 
     */
    double HyperGeometricDistrubition(double,double,double,double);//is our pvalue the number of genes of interest divided by the number of
    double Factorial(int); //termids? The significants of a gene being significant in this context?
private:
    std::unordered_map<std::string, GoInfo> _goInformation;
    std::unordered_map<std::string, TermidInfo> _termidInfo;
    std::unordered_map<std::string, FileType> _fileTypeStrings ={ {"P", PARENTS},{"C", CHILDS},{"D", DEFINITIONS},{"A", GOACCESSION},{"G", GENES},{"N", GOIORNGOI} };
    std::unordered_map<std::string, DelimiterType> _demlimiterTypeStrings ={ {"C", COMMA_DELINEATED},{"T", TAB_DELINEATED}};
    std::vector<std::string> _GOIS;
    std::unordered_map<std::string, bool> _genesOfIntersts;
    std::vector<std::string> _outputfileInformation;
    double _totalNumberOfGenes = 0;
    double persistantTime;
    double currentTime;
    double stampedTime;
};
