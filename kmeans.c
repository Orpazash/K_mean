#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define epsilon 0.001

struct cluster
{
    double *centroid;
    double **datapoints;
};


int readFile(){
    int N = 0;
    // Read the content and print it
    /* while(fgets(myString, 100, fptr)) {
        N += 1
    }
    */
    return N;
}

int checkInput(int K, int iter, int N){
    int valid_input = 1;
    //check iter
    if( iter <= 1 || iter >=1000 ){
        printf("Invalid maximum iteration!");
        valid_input = 0;
    }

    //check K
    if( iter <= 1 || iter >= N){
        printf("Invalid number of clusters!");
        valid_input = 0;
    }

    return valid_input;
}


int main(int argc, char **argv)
{
    //read the file
    FILE *fileP;
    fileP = fopen(argv[3],"r");
    int N = readFile(fileP);
    fclose(fileP);

    // get and check inputs
    int K = atoi(argv[1]);
    int iter = 200;
    if(argc==3){
        iter = atoi(argv[2]);
    }

    // if the inputs are valid 
    if(checkInput(K,iter,N)){

    }
    return 0;
}

