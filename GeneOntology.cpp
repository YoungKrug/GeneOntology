// GeneOntology.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Ontology.h" // non gene of interest, 1 is gene of interest
int main()
{
    Ontology ontology;
    //ontology.ReadOncologyDataBase("flatfiles/GO_annot.txt", Ontology::TAB_DELINEATED);
   
    ontology.ReadDefinitions("flatfiles/GO_definitions.txt", Ontology::TAB_DELINEATED);
    ontology.ReadChildren("flatfiles/GO_tree_child.txt", Ontology::COMMA_DELINEATED);
    ontology.ReadParents("flatfiles/GO_tree_parent.txt", Ontology::COMMA_DELINEATED);
    ontology.ReadGenes("flatfiles/GO_ncbi_assoc_200507.txt", Ontology::COMMA_DELINEATED);
    Ontology::OntologyNode node = ontology.GetData("13666");
    
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
