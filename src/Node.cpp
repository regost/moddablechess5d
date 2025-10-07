#pragma once

#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include <stack>
#include <iostream>
#include "HelperStructs.h"

using namespace std;

template <typename T>  struct ActionAndString;

template <typename T> class Node
{
public:
	Node<T>* p_previous = nullptr;
	vector<ActionAndString<T>> data;
	vector<Node<T>*> vectorOfNodes;

	Node() = default;
	Node(Node<T>* last);
	Node<T>* Find(Node<T>& tofind);
	bool isFirst();
	bool isLast();
	void SetLast(vector<ActionAndString<T>>*& moveset);
	void SetNext(vector<ActionAndString<T>>*& moveset);
	void AddAndSetLast(Node<T>* node);
	void WriteOrFollow(Node<T>*& toadd);
	void Save(string& path);
	void Load(string& path, Game& chess);
	void Print();
	void Delete(size_t ind);
private:
	void Delete();
	static bool IsVectorEqual(vector<ActionAndString<T>>& l, vector<ActionAndString<T>>& r);
	static void PrintVector(vector<ActionAndString<T>>& vec);

};

#include <iterator>
template <typename T>

struct FunctionData {
	Node<T>* node;
	typename vector<Node<T>*>::iterator current;
};


template<typename T>
void Node<T>::Delete()
{
	/*
	for (auto it : this->data) {
		TODO if has delete go throu all element and delete them
	}
	*/
	this->data.clear();

	for (auto it : this->vectorOfNodes) {
		(*it).Delete();
	}
}

template<typename T> bool Node<T>::IsVectorEqual(vector<ActionAndString<T>>& l, vector<ActionAndString<T>>& r)
{
	if (l.size() != r.size()) { return false; }
	auto it1 = r.begin(); auto it2 = l.begin();
	while (it1 != r.end()) {
		if (!((*it1) == (*it2))) { return false; }
		++it1; ++it2;
	}
	return true;
}

template<typename T>
void Node<T>::PrintVector(vector<ActionAndString<T>>& vec)
{
	cout << "[";
	if (vec.empty()) { return; }
	auto it = vec.begin();
	for (; it != std::prev(vec.end()); ++it) {
		(*it).Print();
		cout << "/";
	}
	(*it).Print();
	cout << "]";
}
template<typename T>
Node<T>::Node(Node<T>* last)
{
	p_previous = last;
}

template <typename T> Node<T>* Node<T>::Find(Node<T>& tofind) {
	for (size_t i = 0; i < this->vectorOfNodes.size(); ++i) {
		if (Node<T>::IsVectorEqual(tofind.data, vectorOfNodes[i]->data)) {
			return vectorOfNodes[i];
		}

	}
	return nullptr;
}

template<typename T> bool Node<T>::isFirst()
{
	return this->p_previous == nullptr;
}

template<typename T> bool Node<T>::isLast()
{
	return vectorOfNodes.empty();
}

template<typename T> void Node<T>::Print()
{
	if (!data.empty()) {
		PrintVector(data);
	}
	if (vectorOfNodes.empty()) {
		return;
	}
	vectorOfNodes[0]->Print();
	for (size_t i = 1; i < vectorOfNodes.size(); ++i) {
		cout << "{";
		vectorOfNodes[i]->Print();
		cout << "}";
	}
}

template<typename T>
void Node<T>::Delete(size_t ind)
{
	vectorOfNodes[ind]->Delete();
	this->vectorOfNodes.erase(std::next(this->vectorOfNodes.begin(), ind));
}





template<typename T> void Node<T>::AddAndSetLast(Node<T>* node)
{
	node->p_previous = this;
	this->vectorOfNodes.push_back(node);
}

template<typename T>
void Node<T>::WriteOrFollow(Node<T>*& toadd)
{
	for (auto it = this->vectorOfNodes.begin(); it != this->vectorOfNodes.end(); ++it) {
		if (!Node<T>::IsVectorEqual((*it)->data, toadd->data)) {
			continue;
		}
		delete toadd;//since it was a temporary storage we dont need it anymore
		Node<T>* temp = *it;
		toadd = temp;//
		toadd->p_previous = this;
		return;//toadd is a current node
	}
	toadd->p_previous = this;
	this->vectorOfNodes.push_back(toadd);
}


template<typename T> void Node<T>::SetLast(vector<ActionAndString<T>>*& data) {
	data = &p_previous->data;
}

template<typename T> void Node<T>::SetNext(vector<ActionAndString<T>>*& data) {

	data = &(vectorOfNodes[0]->data);
}


template<typename T>
void Node<T>::Save(string& path)
{
	stack<FunctionData<T>> Stack;
	FunctionData<T> firstElement;
	Stack.push(firstElement);
	Stack.top().node = this;
	Stack.top().current = this->vectorOfNodes.begin();
	uint32_t stepsback = 0;
	bool isFirst = true;


	ofstream file;
	file.open(path);
	if (!file.is_open()) { cout << "error opening file!"; return; }
	file.clear();
	while (!Stack.empty()) {
		if (Stack.top().current == Stack.top().node->vectorOfNodes.end()) {
			Stack.pop(); ++stepsback; continue;
		}
		////////////////////////////////////rewrite it without flag 
		if (isFirst) {
			isFirst = false;
		}
		else {
			file << std::to_string(stepsback) << "\n";
		}
		////////////////////////////////////
		FunctionData<T> Element;
		Element.node = (*Stack.top().current);
		Element.current = Element.node->vectorOfNodes.begin();
		for (auto it = Element.node->data.begin(); it != Element.node->data.end(); ++it) {
			file << (*it).str << "/";
		}
		stepsback = 0;
		++Stack.top().current;
		Stack.push(Element);
	}
	file << "0\n";

}
//struct TurnString;
template<typename T>
void Node<T>::Load(string& path, Game& chess)
{

	fstream file; string line;
	file.open(path, std::ios::in);

	if (!file.is_open()) { cout << "error opening file!"; return; }
	file.clear();

	Node<T>* currentnode = this;
	Node<T>* toadd;
	bool color = chess.state.Move;

	while (std::getline(file, line)) {
		if (line.empty()) { continue; }

		// needs to take a slice of a string
		size_t start = 0;

		toadd = new Node<T>();
		for (size_t i = 0; i < line.size(); ++i) {
			if (line[i] == '/') {

				Node<T>* current = toadd;

				//cout << line.substr(start, i - start);
				ActionAndString<T> add(line.substr(start, i - start), chess.state.PrimeTimeline, chess.state.NumberOfNegativeTurns, uint16_t(color));
				(*current).data.push_back(add);
				start = i + 1;
			}
		}

		currentnode->WriteOrFollow(toadd);
		//climbing up a tree
		currentnode = toadd;

		//"Nf3/0" ~ (done)"Nf3/" ~ TODO "Nf3"
		int movesback = 0;
		const std::string movesbackstr = line.substr(start, line.size() - start);

		if(movesbackstr != "" && movesbackstr != " " && movesbackstr != "  "){
			movesback = std::stoi(line.substr(start, line.size() - start));
		}
		
		//who moves
		if (!(movesback & 1)) { color = !color; }

		//climbing down a tree N moves back
		for (int i = 0; i < movesback; ++i) {
			currentnode = currentnode->p_previous;
		}
	}
}

#endif