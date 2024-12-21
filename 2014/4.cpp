#include <iostream>
#include <sstream> 
#include <string>
#include <stdint.h>
#include <stdlib.h> 
#include <math.h>

double eps = 0.00000001;

using namespace std;

/*vrátí počet bodů na zadaném intervalu*/
int64_t countOfAnglesI(int64_t min, int64_t max, int64_t numberOfAngles){

    if(max>min){
        /*printf("min: %lu max:%lu max-min: %lu\n", min, max, max-min);*/
        return max-min;
    }else if(min>=max){
        /*printf("min: %lu max:%lu (max+numberOfStakes-min)numberOfStakes: %lu\n", min, max, (max+numberOfStakes-min)%numberOfStakes);*/
        return (max+numberOfAngles-min)%numberOfAngles;
    }
    return 0;
}

/*komparator, pokud je prvni vetsi nez druhy, vrati 1, v opacnem pripade -1, pokud jsou stejne 0*/
int cmp(const double a, const double b){
    /*if (a>b) return 1;
    else if (b>a) return -1;
    else return 0;*/

    if (a>b+eps) return 1;
    else if (a<b-eps) return -1;
    else return 0;
}

/*najde prislusny index, pokud tato hodnota je v tabulce; jinak najde index nejblizsiho vyssiho prvku = index pro vlozeni teto hodnoty*/
int find(int64_t numberOfAngles, double array[], double value, int64_t *indexFound, int64_t *positionToInsert){
    int64_t leftIndex = 0, rightIndex = numberOfAngles - 1, pivot;
    int compareValue;
    (*indexFound) = 0;
    (*positionToInsert)=0;
    //if(value<array[numberOfAngles-1])
    //{
        /*printf("positionToInsert: %lu \n", (*positionToInsert));*/
        //positionToInsert=0;
        //return 0;
    //}

    while(leftIndex <= rightIndex){
        pivot = (leftIndex + rightIndex) / 2;

        /*printf("PO ZMENE PIVOTA pivot: %lu leftIndex: %lu rightIndex: %lu \n", pivot, leftIndex, rightIndex);*/

        compareValue = cmp(value, array[pivot]); 

        /*printf("compareValue: %d\n", compareValue);*/
        if(compareValue < 0){
            rightIndex = pivot - 1;
            /*printf("MOZNOST 1 pivot: %lu leftIndex: %lu rightIndex: %lu\n", pivot, leftIndex, rightIndex);*/
        } else if(compareValue > 0){
            leftIndex = pivot + 1;
            /*printf("MOZNOST 2 pivot: %lu leftIndex: %lu rightIndex: %lu \n", pivot, leftIndex, rightIndex);*/
        } else {
            while(pivot<numberOfAngles && array[(pivot+1)%numberOfAngles]==value){pivot++;}
            (*indexFound) = pivot;
            /*printf("indexFound: %lu\n", (*indexFound));
            printf("\n");*/
            return 1;    
        }
    }
    (*positionToInsert) = leftIndex;
    /*printf("positionToInsert: %lu\n", (*positionToInsert));
    printf("\n");*/
    return 0;
}

/*tvořím haldu*/
void makeheap(double *array, unsigned long int n){
    unsigned long int i, s, f;
    double value;

    for (i=1; i<n; i++){
        value = array[i];
        s = i;
        f = (s-1)/2;
        while ((s > 0) && (array[f] < value)){
            array[s] = array[f];
            s = f;
            f = (s-1)/2;}
        array[s] = value;}
}

/*řadím*/
void heapsort(double *array, unsigned long int n){
    unsigned long int i, s, f;
    double ivalue;
    for(i=(n-1); i>0; i--){
        ivalue = array[i];
        array[i] = array[0];
        f = 0;

        if(i==1)s=-1;
        else s=1;

        if(i>2 && array[2]>array[1])s=2;

        while ((s>=0) && (s<n) && (ivalue < array[s])){
            array[f]=array[s];
            f=s;
            s=2*f+1;
            if(s+1<=(i-1) && array[s] < array[s+1])
                s++;
            if (s>(i-1))
                s =-1;}
        array[f]=ivalue;}
}


struct myVec2{
	int m_x;
	int m_y;
};   

// fixed, tmpVec
double countAngle(myVec2 a, myVec2 b){
	double ret;

	if(b.m_y < 0){
		// 3. a 4. kvadrant
		ret = acos((b.m_x)/sqrt((b.m_x*b.m_x)+(b.m_y*b.m_y))); 
		//cout << "ret: " << ret << endl;
	}else{
		// 1. a 2. kvadrant
		ret = 2*M_PI - acos((b.m_x)/sqrt((b.m_x*b.m_x)+(b.m_y*b.m_y))); 
		//cout << "ret: " << ret << endl;
	}

	return ret;
}

struct Airport{
	Airport(int x, int y): m_x(x), m_y(y){}
	void printAirport();

	int m_x;
	int m_y;
};

void Airport::printAirport(){
	cout << "X: " <<this->m_x << " Y: "<< this->m_y << endl;
}

void printAllAirports(Airport ** airports, unsigned int n){
	for (unsigned int i = 0; i < n; ++i)
	{
		cout << "letiste #" << i << " " ;
		airports[i]->printAirport();
	}
}

int main ( int argc, char * argv [] )
 {
 	int64_t n, tmpX, tmpY, i, j;
 	int64_t indexFound=0, positionToInsert=0, start, end, distance=0;
	string line;
 	stringstream tmpstream;
 	//double tmpAngle;
 	getline(cin, line);
 	n = atoi(line.c_str());
 	int64_t solutions = n*(n-1)*(n-2)/6;
 	//cout << "solutions: " << solutions << endl;
 	//uint64_t solutions = 0;
 	Airport ** airports = new Airport*[n];
 	double * angles;
 	angles = new double[2*n]; 

 	for(i = 0; i < n; ++i)
 	{
 		getline(cin, line);
 		tmpstream << line;
		line.clear();
		tmpstream >> tmpX >> tmpY;
		Airport * tmpAirport = new Airport(tmpX, tmpY);
		airports[i] = tmpAirport;
		tmpstream.clear();
 	}
 	//printAllAirports(airports, n);

 	int anglesPosition;
 	myVec2 fixed;
 	fixed.m_x=1;
 	fixed.m_y=0;
 	myVec2 tmpVec;
 	
 	// spocitat vektory, spocitat uhly
 	for (i = 0; i < n; ++i)
 	{
 		anglesPosition = 0;
 		//beru bod na pozici i jako stred...
 		for (j = i+1; j < n; ++j)
 		{
 			// spocitam jejich vektor
 			tmpVec.m_x = airports[j]->m_x - airports[i]->m_x;
 			tmpVec.m_y = airports[j]->m_y - airports[i]->m_y;

 			// dopocitavam uhel ktery svira s fixni primkou a ulozim do angles
 			//if(tmpAngle=countAngle(fixed, tmpVec) > M_PI/2 && tmpAngle < 3*M_PI/4) solutions--;
 			//cout << "odcitam, zbyde: " << solutions << endl;
 			angles[anglesPosition]=countAngle(fixed, tmpVec);
 			anglesPosition++;
 		}

 		if (i>=1)
 		{
	 		for (j = i-1; j >= 0; --j)
	 		{
	 			//cout << "jsem v druhym cyklu i: " << i << " j: " << j << endl;
	 			// spocitam jejich vektor
	 			tmpVec.m_x = airports[j]->m_x - airports[i]->m_x;
	 			tmpVec.m_y = airports[j]->m_y - airports[i]->m_y;

	 			// dopocitavam uhel ktery svira s fixni primkou a ulozim do angles
	 			//if(tmpAngle=countAngle(fixed, tmpVec) > M_PI/2 && tmpAngle < 3*M_PI/4) solutions--;
	 			//cout << "odcitam, zbyde: " << solutions << endl;
	 			angles[anglesPosition]=countAngle(fixed, tmpVec);
	 			anglesPosition++;
	 		}
	 	}

		//cout << "navysuji i" << endl;
 		//seradim angles
		makeheap(angles, anglesPosition);
    	heapsort(angles, anglesPosition);
    	/*for(j=0; j<anglesPosition; j++){
    		cout << "angles j: " << j << " : "<< angles[j]*180/M_PI << endl;
    	}
    	cout << endl;*/

    	for(j=0; j<anglesPosition; j++){
    		angles[anglesPosition+j]=(angles[j]+2*M_PI);
    	}
    	angles[(2*n-2)]=(angles[0]+4*M_PI);

    	/*for(j=0; j<2*n-1; j++){
    		cout << "angles j: " << j << " : "<< angles[j]*180/M_PI << endl;
    	}*/
    	//cout << endl;


 		//prochazim a pocitam vyhovujici...odcitam tupouhle
 		for (j = 0; j < anglesPosition; ++j)
    	{
    		//cout << (angles[j]+M_PI/2)*180/M_PI << endl;
			if(find(2*n-1, angles, angles[j]+M_PI/2, &indexFound, &positionToInsert)){
				start = indexFound-1;
				//cout << "1 indexFound: " << indexFound << endl;
			}else{
				//cout << "1 positionToInsert: " << positionToInsert << endl;
				start = positionToInsert-1;
			}

			//cout << (angles[j]+3*M_PI/2)*180/M_PI << endl;
			if(find(2*n-1, angles, angles[j]+3*M_PI/2, &indexFound, &positionToInsert)){
				end = indexFound+1;
				//cout << "indexFound: " << indexFound << endl;

			}else{
				end = positionToInsert;
				//cout << "positionToInsert: " << positionToInsert << endl;
			}

			if(end>start){
				distance+= end-start-1;
				//cout << "distance: " << distance << endl;
			}	

		}

 	}
 	
 	solutions = solutions - distance/2;
 	//vypsat vysledek
 	cout << solutions << endl;

 	for (int i = 0; i < n; ++i)
 	{
 		delete airports[i];
 	}
 	delete [] airports;
 	delete [] angles;

 	return 0;
 }