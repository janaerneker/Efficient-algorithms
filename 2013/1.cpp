#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
#endif /* __PROGTEST__ */
 
struct Bug
{
    Bug(const string & name, const string & area): name(name), area(area)
    {
      this->unknown = false;
      this->prev = NULL;
      this->next = NULL;
    }
 
    string name;
    string area;
    Bug * prev;
    Bug * next;
    bool unknown;
 
};
 
class CDatabase
 {
   public:
    // default constructor, destructor (if needed)
    CDatabase();
    ~CDatabase();
    int Hash ( const string & name );
    Bug * Find (const string & name, int & position);
    void   AddBug       ( const string    & name,
                          const string    & area );
    void   DelBug       ( const string    & name );
    void   Print        ( ostream         & os ) const;
   private:
    // implementation
    int areaArray[26][26][26];
    int unknown;
    Bug * hashTable[20011];
 };
 
 CDatabase::CDatabase()
 {
    for (int i = 0; i < 26; ++i)
      {
        for (int j = 0; j < 26; ++j)
        {
          for (int k = 0; k < 26; ++k)
          {
            this->areaArray[i][j][k]=0;
          }
        }
      }
      this->unknown=0;
      for (int i = 0; i < 20011; ++i)
      {
        hashTable[i]=NULL;
      }
 }
 CDatabase::~CDatabase()
 {
    for (int i = 0; i < 20011; ++i)
    {
        delete hashTable[i];
    }
 }
 
 
int CDatabase::Hash ( const string & name )
  {
    unsigned int position=0;
    for (unsigned int i = 0; i < name.length(); ++i)
    {
      int c = name[i];
      position += 31*position + c*(i+1);
    }
    return (position % 20011);
  }
 
Bug * CDatabase::Find (const string & name, int & position)
{
  position = Hash(name);
 
  if (hashTable[position]==NULL)
  {
    return NULL;
  }
  else
  {
    Bug *tmpNode = hashTable[position];
    while(tmpNode!=NULL)
    {
      if (tmpNode->name == name)
      {
        return tmpNode;
      }
      tmpNode=tmpNode->next;
    }
    return NULL;
  }
}
 
 void CDatabase::AddBug( const string & name, const string & area )
 {
    int position;
    Bug * foundBug = Find(name, position);
   
    if (foundBug==NULL)
    {
      //int position = Hash(name);
      Bug *tmpBug = new Bug(name, area);
 
      if (hashTable[position]==NULL)
      {
        hashTable[position] = tmpBug;
        areaArray[(int)(area[0]-65)][(int)(area[1]-65)][(int)(area[2]-65)]++;
      }
      else
      {
        Bug *tmpNode = hashTable[position];
        while(tmpNode->next!=NULL)
        {
          tmpNode=tmpNode->next;
        }
        tmpBug->prev=tmpNode;
        tmpNode->next=tmpBug;
        areaArray[(int)(area[0]-65)][(int)(area[1]-65)][(int)(area[2]-65)]++;
      }
    }
    else
    {
      if (foundBug->unknown!=true && foundBug->area!=area)
      {
        areaArray[(int)(foundBug->area[0]-65)][(int)(foundBug->area[1]-65)][(int)(foundBug->area[2]-65)]--;
        foundBug->area="";
        unknown++;
        foundBug->unknown = true;
      }
    }  
 }
 
 void CDatabase::DelBug( const string & name )
 {
    int position;
    Bug * foundBug = Find(name, position);
 
    if(foundBug!=NULL)
    {
      // cout << "------" << endl;
      // cout << foundBug -> name << endl;
      // cout << foundBug -> area << endl;
      // cout << "------" << endl;
 
      if(foundBug->next!=NULL)
      {
        foundBug->next->prev=foundBug->prev;
      }
      if (foundBug->prev!=NULL)
      {
        foundBug->prev->next=foundBug->next;
      }
 
      if(foundBug->prev == NULL)
      {
        hashTable[position] = foundBug->next;
      }
 
      if(foundBug->unknown==true)
      {
        unknown--;
      }
      else
      {
        areaArray[(int)(foundBug->area[0]-65)][(int)(foundBug->area[1]-65)][(int)(foundBug->area[2]-65)]--;
      }
 
      delete foundBug;
    }
 }
 
  void CDatabase::Print( ostream & os ) const
 {
    for (int i = 0; i < 26; ++i)
    {
        for (int j = 0; j < 26; ++j)
        {
            for (int k = 0; k < 26; ++k)
            {
              if (areaArray[i][j][k] != 0)
              {
                  os << char(i + 65) << char(j + 65) << char(k + 65) << " " << areaArray[i][j][k] << endl;
              }
            }
        }
    }
    if (unknown != 0)
    {
      os << "unknown " << unknown << endl;
    }
 }
 
#ifndef __PROGTEST__
// sample code to read extra test data
int main ( void )
 {
  CDatabase db;
   char op;
   string name, area;
   
   while ( cin >> op >> name )
    {
      if ( op == '+' )  
       {
         cin >> area;
         db . AddBug ( name, area );
       }
      if ( op == '-' )   
       db . DelBug ( name );
    }
   db . Print ( cout );
 
 return 0;
 }
#endif /* __PROGTEST__ */