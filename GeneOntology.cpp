// GeneOntology.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Ontology.h" // non gene of interest, 1 is gene of interest
int main()
{
	Ontology ontology;
	std::string path;
	std::cout << "Please enter the path for you go_definitions";
	std::cin >> path;
	ontology.ReadFile(path, Ontology::TAB_DELINEATED, Ontology::DEFINITIONS);
	std::cout << "Please enter the path for you go_tree_children";
	std::cin >> path;
	ontology.ReadFile(path, Ontology::COMMA_DELINEATED, Ontology::CHILDS);
	
	std::cout << "Please enter the path for you go_tree_parents";
	std::cin >> path;
	ontology.ReadFile(path, Ontology::COMMA_DELINEATED, Ontology::PARENTS);
	
	std::cout << "Please enter the path for you go_associations";
	std::cin >> path;
	ontology.ReadFile(path, Ontology::COMMA_DELINEATED, Ontology::GENES);
	
	std::cout << "Please enter the path for you go_genes";
	std::cin >> path;
	ontology.ReadFile(path, Ontology::TAB_DELINEATED, Ontology::GOACCESSION);
	
	std::cout << "Please enter the path for you GOI file";
	std::cin >> path;
	ontology.ReadFile(path, Ontology::TAB_DELINEATED, Ontology::GOIORNGOI);
	std::string input;
	std::cout << "Please enter a Go Accession Number for lookup" << std::endl;
	while (input != "n")
	{
		if (input == "n")
			break;
		std::cin >> input;
		ontology.DisplayValue(input);
		std::cout << "Enter another GO AccessionNumber or enter 'n' to exit" << std::endl;
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
