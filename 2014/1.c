#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h> 	/* malloc, free, rand */  

/*tvořím haldu*/
void makeheap(unsigned long int *array, unsigned long int n){
    unsigned long int i, value, s, f ;
    for (i=1; i<n ; i++){
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
void heapsort(unsigned long int *array, unsigned long int n){
    unsigned long int i, s, f, ivalue;
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

/*komparator, pokud je prvni vetsi nez druhy, vrati 1, v opacnem pripade -1, pokud jsou stejne 0*/
int cmp(const unsigned long int a, const unsigned long int b){
    if (a>b) return 1;
    else if (b>a) return -1;
    else return 0;
}

/*najde prislusny index, pokud tato hodnota je v tabulce; jinak najde index nejblizsiho vyssiho prvku = index pro vlozeni teto hodnoty*/
int find(const unsigned long int numberOfStakes, const unsigned long int array[], const unsigned long int value, unsigned long int *indexFound, unsigned long int *positionToInsert, int flag){
    unsigned long int leftIndex = 0, rightIndex = numberOfStakes - 1, pivot;
    int compareValue;
    (*indexFound) = 0;
    (*positionToInsert)=0;
    if(value<array[0])
    {
        /*printf("positionToInsert: %lu \n", (*positionToInsert));*/
        positionToInsert=0;
        return 0;
    }

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
            if(flag==0){
                while(pivot>0 && array[(pivot-1)%numberOfStakes]==value){pivot--;}
            }else{
                while(pivot<numberOfStakes && array[(pivot+1)%numberOfStakes]==value){pivot++;}
            }
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

/*vrátí počet bodů na zadaném intervalu*/
unsigned long int countOfStakesI(long unsigned int min, long unsigned int max, long unsigned int numberOfStakes){

    if(max>min){
        /*printf("min: %lu max:%lu max-min: %lu\n", min, max, max-min);*/
        return max-min;
    }else if(min>=max){
        /*printf("min: %lu max:%lu (max+numberOfStakes-min)numberOfStakes: %lu\n", min, max, (max+numberOfStakes-min)%numberOfStakes);*/
        return (max+numberOfStakes-min)%numberOfStakes;
    }
    return 0;
}

/*vrati pocet kombinaci n nad k*/
unsigned long int combine(unsigned long int n, unsigned long int k){
    if(n<k) return 0;
    if((n==k)||(k==0)) return 1;
    if((n==k+1)||(k==1)) return n;
    return combine(n-1, k-1) + combine(n-1, k);
}

int main ( int argc, char * argv [] )
{
	unsigned long int *stakes, c, numberOfStakes, perimeter, halfOfPerimeter, numberOfSuccess=0, indexFound=0, positionToInsert=0, i, k, l, odcitam=0;
	scanf("%lu %lu", &numberOfStakes, &perimeter);
    stakes = (unsigned long int*) calloc (numberOfStakes, sizeof(unsigned long int));
    for (l = 0; l < numberOfStakes; l++) stakes[l]=0;
    
	
	for(k=0; k<numberOfStakes; k++){
		scanf("%lu", &stakes[k]);
	}

	if(perimeter%2==1){
        halfOfPerimeter = (perimeter-1)/2;
    }else{
        halfOfPerimeter = perimeter/2;
    }
            
    /*printf("Počet stromů: %lu Obvod pozemku: %lu \n", numberOfStakes, perimeter);*/

    /*numberOfSuccess=combine(numberOfStakes, 3);*/
    numberOfSuccess=(numberOfStakes*(numberOfStakes-1)*(numberOfStakes-2))/6;

    /*printf("numberOfSuccess: %lu\n", numberOfSuccess);*/

    makeheap(stakes,numberOfStakes);
    heapsort(stakes,numberOfStakes);

    /*printf("\n");
    for(i=0; i<numberOfStakes; i++){printf("%lu ", stakes[i]);}
    printf("\n");*/


    for(i=0; i<numberOfStakes; i++){ 
            /*printf("\n numberOfStakes: %lu i: %lu stakes[i]: %lu halfOfPerimeter: %lu\n", numberOfStakes, i, stakes[i], halfOfPerimeter);*/
            
            if(find(numberOfStakes, stakes, (stakes[i]+halfOfPerimeter)%perimeter, &indexFound, &positionToInsert, perimeter%2)==0)
            {
                /*nenajdu partaka*/
                if(positionToInsert==0){
                    /*odcitam=combine(countOfStakesI(i, numberOfStakes-1, numberOfStakes), 2);*/
                    if((c=countOfStakesI(i, numberOfStakes-1, numberOfStakes))>1){
                        /*printf("1.c: %lu\n", c);*/
                        odcitam=(c*(c-1))/2;
                    }
                    /*printf("1.vetev-odcitam: %lu\n", odcitam);*/
                }else{
                    /*odcitam=combine(countOfStakesI(i, positionToInsert-1, numberOfStakes), 2);*/
                    if((c=countOfStakesI(i, positionToInsert-1, numberOfStakes))>1){
                        /*printf("2.c: %lu\n", c);*/
                        odcitam=(c*(c-1))/2;
                    }
                    /*printf("1.vetev-odcitam: %lu\n", odcitam);*/
                }
            }
            else
            {   
                if(perimeter%2==1){
                    /*odcitam=combine(countOfStakesI(i, indexFound, numberOfStakes), 2);*/
                    if((c=countOfStakesI(i, indexFound, numberOfStakes))>1){
                        /*printf("3.c: %lu\n", c);*/
                        odcitam=(c*(c-1))/2;
                    }
                    /*printf("2a.vetev-odcitam: %lu\n", odcitam);*/
                }else{

                    if(indexFound==0){
                        /*odcitam=combine(countOfStakesI(i, numberOfStakes-1, numberOfStakes), 2);*/
                        if((c=countOfStakesI(i, numberOfStakes-1, numberOfStakes))>1){
                            /*printf("4.c: %lu\n", c);*/
                            odcitam=(c*(c-1))/2;
                        }
                        /*printf("2ba.vetev-odcitam: %lu\n", odcitam);*/
                    }else{
                        /*odcitam=combine(countOfStakesI(i, indexFound-1, numberOfStakes), 2);*/
                        if((c=countOfStakesI(i, indexFound-1, numberOfStakes))>1){
                            /*printf("5.c: %lu\n", c);*/
                            odcitam=(c*(c-1))/2;
                        }
                        /*printf("2b.vetev-odcitam: %lu\n", odcitam);*/
                    }
                }
            }
            numberOfSuccess-=odcitam;
            odcitam=0;
            /*printf("aktualni stav: %lu\n", numberOfSuccess);*/
    }

	printf("%lu\n", numberOfSuccess);
	free(stakes);
	return 0;
}