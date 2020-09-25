// Algo_Assignment_Q7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "List.h"
using namespace std;

void MakeGraph(int NoOfVertices,List<int>& Adj_List) {
	
	for (int i = 0; i < NoOfVertices; i++) {
		Adj_List.InsertNode(i+1);
	}

}

int FindVertix(int Vertice, List<int> Adj_list) {
	Node<int>* temp = Adj_list.Head;
	int counter = 0;

	for (int i = 0; temp != NULL; i++) {
		if (Vertice == temp->data)
			return counter;

		counter++;
		temp = temp->down;
	}

	return -1;

}

void MakeEdge(int Vertice1, int Vertice2, List<int>& Adj_list) {

	int index = FindVertix(Vertice1, Adj_list);

	if (index != -1) {

		if (Adj_list[index]->next == NULL) {
			Adj_list[index]->next = new Node<int>(Vertice2);
		}
		else {
			Node<int>* temp = Adj_list[index]->next;

			while (temp->next != NULL)
				temp = temp->next;

			temp->next = new Node<int>(Vertice2);
		}
	}

	int index1 = FindVertix(Vertice2, Adj_list);

	if (index1 != -1) {

		if (Adj_list[index1]->next == NULL) {
			Adj_list[index1]->next = new Node<int>(Vertice1);
		}
		else {
			Node<int>* temp = Adj_list[index1]->next;

			while (temp->next != NULL)
				temp = temp->next;

			temp->next = new Node<int>(Vertice1);
		}
	}
}

void MinimumNoOfCities(int city2,List<int> Adj_List,int& min ,int& counter,vector<int> Visited,Node<int>* temp) {
	
	if (temp == NULL)
		return;

	Node<int>* temp2 = temp;

	while (temp2 != NULL) {
		if (temp2->data == city2) {
			min = counter;
			return;
		}
		temp2 = temp2->next;
	}

	if (Visited[temp->data - 1] == 0) {
		Visited[temp->data - 1] = 1;
		MinimumNoOfCities(city2, Adj_List, min, ++counter, Visited, Adj_List[temp->data - 1]->next);
	}
	else
		MinimumNoOfCities(city2, Adj_List, min, counter, Visited, temp->next);
}

void ReadFromFile(string name,List<int>& Adj_List) {
	
	ifstream read;
	read.open(name);

	if (read)
	{
		int NoOfTests=0,NoOfVertices=0,NoOfEdges=0;
		string lineInfo;
		
		getline(read, lineInfo, '\n');

		NoOfTests = stoi(lineInfo);

		cout << "No of Tests to be conducted: " << NoOfTests << endl;

		for (int i = 0; i < NoOfTests; i++) {
			
			cout <<endl<< "This is Test No: " << i + 1 << endl<<endl;

			getline(read, lineInfo, ' ');

			NoOfVertices = stoi(lineInfo);

			getline(read, lineInfo, '\n');

			NoOfEdges = stoi(lineInfo);

			cout << "No of Vertices: " << NoOfVertices << " And No of Edges between them: " << NoOfEdges << endl;

			MakeGraph(NoOfVertices, Adj_List);

			for (int i = 0; i < NoOfEdges; i++) {
				string SVertice1 = "", SVertice2 = "";
				getline(read, SVertice1, ' ');
				getline(read, SVertice2, '\n');
				int Vertice1 = stoi(SVertice1);
				int Vertice2 = stoi(SVertice2);
				MakeEdge(Vertice1, Vertice2, Adj_List);
			}
			

			cout << "Adjacency List of Graph: " << i + 1 << endl;

			Adj_List.Display();

			int City1 = 0, City2 = 0;
			cout << "Enter the Cities you want to travel from and to respectivly: " << endl;
			cin >> City1 >> City2;

			int min = -1, counter = 1;
			vector<int> Visited(NoOfVertices);

			for (int i = 0; i < NoOfVertices; i++)
				Visited[i] = 0;

			Visited[City1 - 1] = 1;
			MinimumNoOfCities(City2, Adj_List, min,counter, Visited,Adj_List[City1-1]->next);	// sending city - 1 because while make adj list the order of indexing starts from 0 and city identifiers are 1 number greater then index

			cout << "Minimum number of cities required to travel: " << min << endl;

			Adj_List.destroyEdges();
			Adj_List.destroyVertices(Adj_List.Head);
			
			cout << "After destroying List: " << endl;

			Adj_List.Display();
		}
	}
	else {
		cout << "File couldnot be opened :( " << endl;
	}
}
int main()
{
	List<int> Adj_list;
	ReadFromFile("Test.txt",Adj_list);

	
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
