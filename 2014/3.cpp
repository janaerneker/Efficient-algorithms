#include <iostream>
#include <sstream> 
#include <string>
#include <stdint.h>
#include <stdlib.h> 

struct MyFIFO{
  
  MyFIFO(uint64_t sizeOfFIFO):m_sizeOfFIFO(sizeOfFIFO){
    m_actualCount = 0;
    m_positionToInsert = 0;
    m_positionToDelete = 0;
    m_arrFIFO = new int64_t[m_sizeOfFIFO];
  }

  ~MyFIFO(){
    delete [] m_arrFIFO;
  }

  bool isEmpty();
  void push(int64_t value);
  void pop();

  uint64_t m_actualCount;
  int64_t m_positionToInsert;
  int64_t m_positionToDelete;
  uint64_t m_sizeOfFIFO;
  int64_t *m_arrFIFO;
};

bool MyFIFO::isEmpty(){
  if(m_actualCount==0){
    return true;
  }
  return false;
}

//insert element
void MyFIFO::push(int64_t value){
  m_arrFIFO[m_positionToInsert] = value;
  m_positionToInsert++;
  m_actualCount++;
}

//remove top element
void MyFIFO::pop(){
  m_arrFIFO[m_positionToDelete] = -1;
  m_positionToDelete++;
  m_actualCount--;
}

struct MyNode{
	MyNode(int64_t neighbor):m_countOfActive(neighbor), m_countOfNeighbors(neighbor){
		m_neighbors = new int64_t[neighbor];
		m_processed = false;
		m_c1=0;
		m_c2=1;
	}


	int64_t m_countOfActive;
	int64_t m_countOfNeighbors;
	int64_t *m_neighbors;
	bool m_processed;
	//c1 = soucet c1 a c2 potomku
	int64_t m_c1;
	//c2 = c2(c2 potomka+1)
	int64_t m_c2;
};

struct MyTree
{
	MyTree(int64_t n):m_n(n){
		m_treeNodes = new MyNode*[n];
	}

	int64_t getParent(int64_t whose){
		int64_t parent, current;

		for (int64_t i = 0; i < m_treeNodes[whose]->m_countOfNeighbors; ++i){
			current = m_treeNodes[whose]->m_neighbors[i];
			if (m_treeNodes[current]->m_processed==false)
			{
				parent = current;
				break;
			}
		}

		return parent;
	}

	int64_t m_n;
	MyNode **m_treeNodes;
};
//modulit 536870909

int64_t modul(int64_t number){
	return number % 536870909;
}

using namespace std;

int main ( int argc, char * argv [] )
 {
 	//MyNode **treeNodes;
 	int64_t n, rowCount, tmpInt, current, i, j, solution = 0, parent;
 	string line;
 	stringstream tmpstream;
 	getline(cin, line);
 	n = atoi(line.c_str());
 	//treeNodes = new MyNode*[n];
 	
 	//cout << n << endl;

 	//pokud n=1 vrat 1, pokud 0, tak vratim 0 a dal vubec nezabiham
 	MyFIFO *values = new MyFIFO(n);
 	MyTree *tree = new MyTree(n);
 	for(i = 0; i < n; ++i)
 	{
 		getline(cin, line);
 		//cout << line <<  endl;
 		tmpstream << line;
		line.clear();
		tmpstream >> rowCount;
		MyNode * tmpNode = new MyNode(rowCount);
		if(rowCount==1) values->push(i);
		tree->m_treeNodes[i] = tmpNode;
		for (j = 0; j < rowCount; ++j)
		{
			tmpstream >> tmpInt;
			tree->m_treeNodes[i]->m_neighbors[j]=tmpInt;
		} 
		tmpstream.clear();
 	}

 	/*cout << endl;
 	for (int i = 0; i < n; ++i)
 	{
 		for (int j = 0; j < tree->m_treeNodes[i]->m_countOfActive; ++j)
 		{
 			cout << tree->m_treeNodes[i]->m_neighbors[j];
 			if(j!=tree->m_treeNodes[i]->m_countOfActive-1){
 				cout << ' '; 
 			}
 		}
 		cout << endl;
 	}
 	cout << endl;*/


 	//prochazim FIFO dokud neni prazdnej

 	//if nema uz zadnyho potomka - c1 + c2
 	if(n==0){
 		cout << 0 << endl;
 	}else if(n==1){
 		cout << 1 << endl;
 	}else{
 		while(values->isEmpty()==false){
 			current = values->m_arrFIFO[values->m_positionToDelete];
 			//cout << "current: " << current << endl;
 			values->pop();

 			if(tree->m_treeNodes[current]->m_countOfActive == 0){
 				//pak jsem koren a ukladam vysledek
 				solution = modul(modul(tree->m_treeNodes[current]->m_c1)+modul(tree->m_treeNodes[current]->m_c2));
 				break;

 			}else{
 				//najdi rodice
 				parent = tree->getParent(current);
 				//rodici pricitam/nasobim hodnoty
 				//c1 = soucet c1 a c2 potomku
 				tree->m_treeNodes[parent]->m_c1 = modul(tree->m_treeNodes[parent]->m_c1 + modul(modul(tree->m_treeNodes[current]->m_c1)+modul(tree->m_treeNodes[current]->m_c2)));
 				//cout << "C1: " << tree->m_treeNodes[parent]->m_c1 << endl;
 				//c2 = c2(c2 potomka+1)
 				tree->m_treeNodes[parent]->m_c2 = modul(tree->m_treeNodes[parent]->m_c2 *(modul(tree->m_treeNodes[current]->m_c2 + 1)));
 				//cout << "C2: " << tree->m_treeNodes[parent]->m_c2 << endl;
 				//odectu mu aktivni
 				tree->m_treeNodes[parent]->m_countOfActive--;
 				
 				//oznacim sam sebe za processed
 				tree->m_treeNodes[current]->m_processed = true;

 				//zkontroluju, zda rodic neni listem a pokud je, tak ho hodim na 
 				if(tree->m_treeNodes[parent]->m_countOfActive == 1) values->push(parent); //cout << "vkladam rodice: " << parent << endl;
 			}	
 		}

 		cout << solution << endl;
 	}

 	

 	return 0;
 }