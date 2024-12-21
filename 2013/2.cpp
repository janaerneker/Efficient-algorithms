#ifndef __PROGTEST__

#include <fstream>

#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;   
   
struct TPhone
 {
   unsigned int    m_TimeFrom;
   unsigned int    m_TimeTo;
   unsigned int    m_Channel;
 };
#endif /* __PROGTEST__ */ 

void heapify(TPhone ** array, int position, int heapsize, int argument)
{
  //cout << "I am in heapify function..." << endl;
  int l = 2*position+1, r = 2*position+2, largest = position;
  //cout << "position: " << position << endl;

  if(argument==1)
  {
    /*for (int i = 0; i < heapsize; ++i)
    {
      cout << "i: " << i << endl;
      cout << "array: " << array[i]->m_TimeFrom << " " << array[i]->m_TimeTo << endl;
    }*/
    if (l < heapsize && array[l]->m_TimeFrom > array[position]->m_TimeFrom)
    {
      //cout << array[l]->m_TimeFrom << " " << array[position]->m_TimeFrom << endl;
      largest = l;
    }
    if (r < heapsize && array[r]->m_TimeFrom > array[position]->m_TimeFrom)
    {
      //cout << array[r]->m_TimeFrom << " " << array[position]->m_TimeFrom << endl;
      largest = r;
    }

  }
  else if(argument==2)
  {
    /*for (int i = 0; i < heapsize; ++i)
    {
      cout << "i: " << i << endl;
      cout << "array: " << array[i]->m_TimeFrom << " " << array[i]->m_TimeTo << endl;
    }*/
    if (l < heapsize && array[l]->m_TimeTo > array[position]->m_TimeTo)
    {
      largest = l;
    }
    if (r < heapsize && array[r]->m_TimeTo > array[position]->m_TimeTo)
    {
      largest = r;
    }
  }

  if(largest!=position)
  {
    if(l<heapsize && r<heapsize)
    {
      if(argument==1)
      {
        if (array[l]->m_TimeFrom > array[r]->m_TimeFrom)
        {
          //cout << "largest = l " << l << endl;
          largest=l;
        }
        if (array[r]->m_TimeFrom >= array[l]->m_TimeFrom)
        {
          largest=r;
        }
      }
      else if(argument==2)
      {
        if (array[l]->m_TimeTo > array[r]->m_TimeTo)
        {
          largest=l;
        }
        if (array[r]->m_TimeTo >= array[l]->m_TimeTo)
        {
          largest=r;
        }
      }
    }
    
    //cout << "menim hodnoty " << "position: " << position << " largest: " << largest << endl << endl;

    TPhone * tmp = array[position];
    array[position] = array[largest];
    array[largest] = tmp;

    //for (int i = 0; i < heapsize; ++i)
    //{
      //cout << "i: " << i << endl;
      //cout << /*"array: " << */array[i]->m_TimeFrom << /*" " << array[i]->m_TimeTo << */endl;
    //}
    //cout <<  endl;

    heapify(array, largest, heapsize, argument);
  }

}

void buildheap(TPhone ** array, int reqNr, int argument)
{
  //cout << "I am in buildheap function..." << endl;
  for(int i = (reqNr-1)/2; i>=0; i--)
  {
    heapify(array, i, reqNr, argument);
    //cout << endl;
  }
  //heapify(array, (reqNr-1)/2, reqNr, argument);
  //cout << endl;
  //heapify(array, (reqNr-1)/2-1, reqNr, argument);

}

void heapsort(TPhone ** array, int reqNr, int argument)
{
  //cout << "I am in heapsort function..." << endl;
  int heapsize = reqNr-1;

  /*for (int i = 0; i < reqNr; ++i)
  {
    cout << "i: " << i << endl;
    cout << "array: " << array[i]->m_TimeFrom << " " << array[i]->m_TimeTo << endl;
  }*/

  buildheap(array, reqNr, argument);
  //cout << endl;
  for (int i = reqNr; i >=1 ; i--)
  {
    TPhone *tmp = array[heapsize];
    array[heapsize] = array[0];
    array[0] = tmp;
    heapify(array, 0, heapsize, argument);
    heapsize--;
  }

  /*for (int i = 0; i < reqNr; ++i)
  {
    cout << "i: " << i << endl;
    cout << "array: " << array[i]->m_TimeFrom << " " << array[i]->m_TimeTo << endl;
  }*/

  if ((argument==1 && array[0]->m_TimeFrom > array[1]->m_TimeFrom)
    ||(argument==2 && array[0]->m_TimeTo > array[1]->m_TimeTo))
  {
    TPhone * tmp = array[0];
    array[0] = array[1];
    array[1] = tmp;
  }

}

int AllocChannels ( TPhone * const * req, int reqNr )
{ 
  if (reqNr <= 0) {
      return 0;
  }

  TPhone ** arrayFrom = new TPhone*[reqNr];
  TPhone ** arrayTo = new TPhone*[reqNr];

  for (int i = 0; i < reqNr; ++i)
  {
    arrayFrom[i] = req[i];
    arrayTo[i] = req[i];
  }

  //seradit pole
  heapsort(arrayFrom, reqNr, 1);
  heapsort(arrayTo, reqNr, 2);

  //cout << "arrayFrom: " << endl;
  //for (int i = 0; i < reqNr; ++i)
  //{
    //cout << "i: " << i << endl;
  //  cout /*<< "arrayFrom: " */<< arrayFrom[i]->m_TimeFrom << " " << arrayFrom[i]->m_TimeTo << endl;
    //cout << "arrayTo: " /*<< arrayTo[i]->m_TimeFrom << " "*/ << arrayTo[i]->m_TimeTo << endl << endl;
  //}
  //cout << endl << "arrayTo: " << endl;
  //for (int i = 0; i < reqNr; ++i)
  //{
    //cout << "i: " << i << endl;
    //cout << "arrayFrom: " << arrayFrom[i]->m_TimeFrom /*<< " " << arrayFrom[i]->m_TimeTo*/ << endl;
  //  cout /*<< "arrayTo: " */<< arrayTo[i]->m_TimeFrom << " " << arrayTo[i]->m_TimeTo << endl;
  //}
  //cout << endl;

  TPhone **pointerFrom = arrayFrom;
  TPhone **pointerTo = arrayTo;

  int countOfChannels = 1;
  int shiftOfPointerTo = 1;
  (*pointerFrom)->m_Channel = 0;
  *pointerFrom = *(pointerFrom+1);

  for (int i = 1; i < reqNr; ++i)
  {
    if ((*pointerFrom)->m_TimeFrom > (*pointerTo)->m_TimeTo)
    {
      cout << i << " PRVNI VETEV" << endl;
      cout << "pointerFrom->m_TimeFrom: " << (*pointerFrom)->m_TimeFrom << endl;
      //cout << "pointerTo->m_TimeFrom: " << (*pointerTo)->m_TimeFrom << endl;
      cout << "pointerTo->m_TimeTo: " << (*pointerTo)->m_TimeTo << endl;
      //cout << "pointerTo->m_Channel: " << (*pointerTo)->m_Channel << endl;
      //cout << "pointerFrom->m_Channel: " << (*pointerFrom)->m_Channel << endl;
      (*pointerFrom)->m_Channel = (*pointerTo)->m_Channel;
      cout << "pointerFrom->m_Channel: " << (*pointerFrom)->m_Channel << endl;
      *pointerTo = *(pointerTo+shiftOfPointerTo);
      shiftOfPointerTo++;
    }
    else
    {
      cout << i << " DRUHA VETEV" << endl;
      cout << "pointerFrom->m_TimeFrom: " << (*pointerFrom)->m_TimeFrom << endl;
      cout << "pointerTo->m_TimeTo: " << (*pointerTo)->m_TimeTo << endl;
      (*pointerFrom)->m_Channel = countOfChannels;
      cout << "pointerFrom->m_Channel: " << (*pointerFrom)->m_Channel << endl;
      countOfChannels++;
    }
    *pointerFrom = *(pointerFrom+i+1);
  }
  
  delete [] arrayFrom;
  delete [] arrayTo;

  return countOfChannels;
  //return 1;
}
                                                           

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
 {
   TPhone ** ptr;
   int cnt, chnl;
   ifstream inf("0004_in.txt");

   if ( ! (inf >> cnt) ) return 1;
   
   ptr = new TPhone * [ cnt ];
   for ( int i = 0; i < cnt; i ++ )
    {
      TPhone * n = new TPhone;
      if ( ! (inf >> n -> m_TimeFrom >> n -> m_TimeTo) ) return 1;
      ptr[i] = n;
    }

   chnl = AllocChannels ( ptr, cnt );

   //cout << endl;
   cout << chnl << endl;
   for ( int i = 0; i < cnt; i ++ )
    {
      cout << ptr[i] -> m_Channel << endl;
      delete ptr[i];
    }
   delete [] ptr; 
   return 0;
 }
#endif  /* __PROGTEST__ */
