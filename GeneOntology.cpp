// GeneOntology.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<ctime>
#include <iostream>
#include <string>
#include "Ontology.h" // non gene of interest, 1 is gene of interest
void ReadDefault(Ontology ontology)
{
	ontology.ReadFile("flatfiles/GO_annot.txt", Ontology::TAB_DELINEATED, Ontology::GOACCESSION);
	ontology.ReadFile("flatfiles/GO_definitions.txt", Ontology::TAB_DELINEATED, Ontology::DEFINITIONS);
	ontology.ReadFile("flatfiles/GO_tree_child.txt", Ontology::COMMA_DELINEATED, Ontology::CHILDS);
	ontology.ReadFile("flatfiles/GO_tree_parent.txt", Ontology::COMMA_DELINEATED, Ontology::PARENTS);
	ontology.ReadFile("flatfiles/GO_ncbi_assoc_200507.txt", Ontology::COMMA_DELINEATED, Ontology::GENES);
	ontology.ReadFile("flatfiles/analyze_me_unique.txt", Ontology::TAB_DELINEATED, Ontology::GOIORNGOI);
	ontology.GenerateRandomGenes();
}


int main()
{
	bool useDefault = true;
	Ontology ontology;
	std::string path;
	std::string input;
	std::clock_t start;
	double duration;
	start = std::clock();
	if(!useDefault)
	{
		std::cout << "Please enter your primary gene Annot file\n";
		std::cin >> path;
		ontology.ReadFile(path, Ontology::TAB_DELINEATED, Ontology::GOACCESSION);
		std::cout << "Please enter the path for you go_definitions\n";
		std::cin >> path;
		ontology.ReadFile(path, Ontology::TAB_DELINEATED, Ontology::DEFINITIONS);
		std::cout << "Please enter the path for you go_tree_children\n";
		std::cin >> path;
		ontology.ReadFile(path, Ontology::COMMA_DELINEATED, Ontology::CHILDS);

		std::cout << "Please enter the path for you go_tree_parents\n";
		std::cin >> path;
		ontology.ReadFile(path, Ontology::COMMA_DELINEATED, Ontology::PARENTS);

		std::cout << "Please enter the path for you go_genes\n";
		std::cin >> path;
		ontology.ReadFile(path, Ontology::COMMA_DELINEATED, Ontology::GENES);

		std::cout << "Please enter the path for you GOI file\n";
		std::cin >> path;
		ontology.ReadFile(path, Ontology::TAB_DELINEATED, Ontology::GOIORNGOI);
		ontology.GenerateRandomGenes();
	}
	else
	{
		ReadDefault(ontology);
	}

	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	std::cout<<"The duration of the entire program(including user input): "<< duration << std::endl;
	return 0;
}