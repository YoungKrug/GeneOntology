// GeneOntology.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
	
	/*while(input != "n")
	{
		std::cout << "Please enter for file... (n to exit)"<< std::endl;
		std::string temp;
		std::cin >> temp;
		if(std::toupper(temp[0]) == 'N')
		{
			break;
		}
		path = temp;
		ontology.ReadFile(path);
	}*/
	// input = "";
	// while (input != "n")
	// {
	// 	std::cout << "Enter another GO AccessionNumber or enter 'n' to exit" << std::endl;
	// 	std::cin >> input;
	// 	ontology.DisplayValue(input);
	// }
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
