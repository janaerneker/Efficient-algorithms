#include <iostream>
//#include <iomanip>
#include <string.h>
#include <stdint.h>
#include <stdlib.h> //abs()

//#define SIZE_HASH_TABLE 20011;


using namespace std;

struct Dolly{

  Dolly(int64_t value):m_value(value){
    m_sumInside = 0;
  }

  int64_t m_value;
  int64_t m_sumInside;
};


struct MyStack{
  
  MyStack(uint64_t sizeOfStack):m_sizeOfStack(sizeOfStack){
    m_actualCount = 0;
    m_actualPosition = -1;
    m_arrStack = new Dolly*[m_sizeOfStack];
  }

  ~MyStack(){
    for (uint64_t i = 0; i < m_actualCount; i++){
      delete m_arrStack[i];
    } 
    delete [] m_arrStack;
  }

  bool isEmpty();
  uint64_t size();
  void push(uint64_t value);
  void pop();


  uint64_t m_actualCount;
  int64_t m_actualPosition;
  uint64_t m_sizeOfStack;
  Dolly **m_arrStack;

};

bool MyStack::isEmpty(){
  if(m_actualCount==0){
    return true;
  }
  return false;
}

uint64_t MyStack::size(){
  return m_actualCount;
}

//insert element
void MyStack::push(uint64_t value){
  Dolly * tmp = new Dolly(value);
  m_arrStack[m_actualCount] = tmp;
  m_actualCount++;
  m_actualPosition++;
}

//remove top element
void MyStack::pop(){
  delete(m_arrStack[m_actualPosition]);
  //m_arrStack[m_actualPosition] = NULL;
  m_actualCount--;
  m_actualPosition--;
}

struct Kid
{
  Kid(string name, uint64_t benefit):m_name(name), m_actualBenefit(benefit){
    prev=NULL;
    next=NULL;
  }

  string m_name;
  uint64_t m_actualBenefit;

  Kid * prev;
  Kid * next;
};

//a  ma byt drive v abecede nez b -> vrati <0
int compareStrings(const string & a, const string & b){
  return strcmp (a.c_str(), b.c_str());
}

struct FindWinner
 {

    FindWinner(){
      for (uint64_t i = 0; i < 1000003; ++i)
      {
        m_hashTable[i]=NULL;
      }
      m_actualMax = NULL;
      //m_countOfChildren = 0;
    }

    ~FindWinner(){
      for (uint64_t i = 0; i < 1000003; i++){
        delete m_hashTable[i];
      } 
      //delete m_actualMax;
    }

    uint64_t Hash ( const string & name );
    Kid * Find (const string & name, uint64_t & position);
    void   AddKid       ( const string    & name,
                          const uint64_t  & value );
    //jen vypis
    void   Print        ( ostream         & os ) const;

    //uint64_t m_countOfChildren;
    Kid * m_hashTable[1000003];
    Kid * m_actualMax;
 };

uint64_t FindWinner::Hash ( const string & name )
  {
    uint64_t position=0;
    for (unsigned int i = 0; i < name.length(); ++i)
    {
      int c = name[i];
      position += 31*position + c*(i+1);
    }
    return (position % 1000003);
  }

//nenajde-li, vrací NULL, jinak odkaz na tento prvek
Kid * FindWinner::Find (const string & name, uint64_t & position)
{
  position = Hash(name);
 
  if (m_hashTable[position]==NULL)
  {
    return NULL;
  }
  else
  {
    Kid *tmpNode = m_hashTable[position];
    while(tmpNode!=NULL)
    {
      if (tmpNode->m_name == name)
      {
        return tmpNode;
      }
      tmpNode=tmpNode->next;
    }
    return NULL;
  }
}

void FindWinner::AddKid( const string & name, const uint64_t & value )
 {
    uint64_t position;
    Kid * foundKid = Find(name, position);
    //cout << "vkladam dite #2" << endl;
    if (foundKid==NULL)
    {
      Kid *tmpKid = new Kid(name, value);
      //m_countOfChildren++;
      //cout << "vkladam dite #3" << endl;
      if(m_hashTable[position]==NULL)
      {
        m_hashTable[position] = tmpKid;
        //cout << "vkladam dite #4" << endl;
        
        //MAX
        if((m_actualMax==NULL) || (value > m_actualMax->m_actualBenefit)){
          //cout << "aktualizuju max #1" << endl;
          m_actualMax = tmpKid;
          //cout << "Maxovo jmeno: " << m_actualMax->m_name << endl;
          //cout << "Maxova hodnota: " << m_actualMax->m_actualBenefit << endl;
        }else if((value==m_actualMax->m_actualBenefit) && (compareStrings(name, m_actualMax->m_name)<0)){
          //cout << "aktualizuju max #2" << endl;
          m_actualMax = tmpKid;
          //cout << "Maxovo jmeno: " << m_actualMax->m_name << endl;
        }
      }
      else
      {
        Kid *tmpNode = m_hashTable[position];
        while(tmpNode->next!=NULL)
        {
          tmpNode=tmpNode->next;
        }
        tmpKid->prev=tmpNode;
        tmpNode->next=tmpKid;

        //MAX
        if(value>m_actualMax->m_actualBenefit){
          //cout << "aktualizuju max #3" << endl;
          m_actualMax = tmpKid;
          //cout << "Maxovo jmeno: " << m_actualMax->m_name << endl;
          //cout << "Maxova hodnota: " << m_actualMax->m_actualBenefit << endl;
        }else if((value==m_actualMax->m_actualBenefit) && (compareStrings(name, m_actualMax->m_name)<0)){
          //cout << "aktualizuju max #4" << endl;
          m_actualMax = tmpKid;
          //cout << "Maxovo jmeno: " << m_actualMax->m_name << endl;
        }
      }
    }
    else
    {
      //nasli jsme jiz dite v poli 
      foundKid->m_actualBenefit+=value;
      //cout << "actualBenefit: " << foundKid->m_actualBenefit << endl;

      //MAX
      if(foundKid->m_actualBenefit > m_actualMax->m_actualBenefit){
        //cout << "aktualizuju max #5" << endl;
        m_actualMax = foundKid;
        //cout << "Maxovo jmeno: " << m_actualMax->m_name << endl;
      }else if((foundKid->m_actualBenefit == m_actualMax->m_actualBenefit) && (compareStrings(name, m_actualMax->m_name)<0)){
        //cout << "aktualizuju max #6" << endl;
        m_actualMax = foundKid;
        //cout << "Maxovo jmeno: " << m_actualMax->m_name << endl;
      }
    }  
 }



//int abs(int j); vsechno, co hazim do hashTable - value v absolutni hodnote

int main ( int argc, char * argv [] )
{
  int64_t n, m;
  string name; 
  cin >> n;
  MyStack *values = new MyStack(n);
  FindWinner * finder = new FindWinner();
  
  bool isPossible=true;
  if (n%2==1){
    //cout << "nelze #1" << endl;
    isPossible=false;
  }

  for(int64_t i=0; i<n;i++){
    cin >> m;
    
    cin.get();
    getline(cin, name);

    //jen vypis
    //cout << "m: " << m << " name: " << name << endl;


    //pridavam na stack pouze zaporny hodnoty... kladny zaviraji panenku stejny velikosti...posledni na stacku, pokud nelze, 
    //na stack uz nehazim, vypisuju "Ne" a dal resim pouze max dite...
    if(isPossible == true){
      //pridavam na stack
      if((m<0)&&(((values->isEmpty()==false) || (i==0)))){
        values->push(abs(m));
      }else if(m>0){
        if((values->isEmpty()==false) && (values->m_arrStack[values->m_actualPosition])->m_value==m){
          //nejdrive koukam, jestli se vnitrni panenky vejdou do te, kterou prave zaviram
          if(values->m_arrStack[values->m_actualPosition]->m_sumInside>m){
            isPossible=false;
            //cout << "nelze #2" << endl;
          }else{
            //zaviram panenku a ukladam na predchozi hodnotu na stacku hodnotu vnitrnich
            values->pop();
            if(values->m_actualPosition>-1){
              values->m_arrStack[values->m_actualPosition]->m_sumInside+=m;
            }
          }
          /////////
        }else{
          isPossible = false;
          //cout << "nelze #3" << endl;
        }
      }else{
        //m<0 nekolik panenek vedle sebe!!!
        isPossible = false;
        //cout << "nelze #5" << endl;
      }
    }

    //cout << "vkladam dite #1" << endl;
    finder->AddKid(name, abs(m));





    name.clear();
  }

  if(values->isEmpty()==false){
    isPossible=false;
    //cout << "nelze #4" << endl;
  }

  /*for (uint64_t j = 0; j < values->m_actualCount; ++j)
  {
    cout << "j: "  << values->m_arrStack[j]->m_value << endl;
  }*/
  
  if(isPossible){
    cout << "Ano" << endl;
  }else{
    cout << "Ne" << endl;
  }
  //todo vypsat jmeno viteze...
  cout << finder->m_actualMax->m_name << endl;

  delete(values);
  delete(finder);
  return 0;
}
