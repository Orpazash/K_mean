#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define epsilon 0.001

struct cord
{
    double value;
    struct cord *next;
};

struct vector   
{
    struct vector *next;
    struct cord *cords;
};

struct cluster
{
    struct vector *centroid;
    struct vector *vector_list;
    struct cluster *next;
};


int readFile(FILE *f){
    int N = 0;
    double num;
    while (fscanf(f,"%f",&num)!= EOF){
        char c;
        c = fgetc(f);
        if(EOF != c){
            //same point
             if(',' == c){

             }
             //moving to the next point
             else if('\n' == c){
                
                N+=1;
             }
        }
        else
            break;
    }
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
 //struct cord *cord1;
 //struct vector vec1;

 
double coumpute_vector_distance(struct vector *vector1, struct vector *vector2)
{
    double sum;
    struct cord *curr_cord1,*curr_cord2;  //creating curr cordinates from vectors
    curr_cord1 = vector1->cords;
    curr_cord2 = vector2->cords;
    while (curr_cord1->next != NULL) // going over all d cordinates
    {
        double cord1_data = curr_cord1->value;  //extracting values of cords 
        double cord2_data = curr_cord2->value;

        sum += pow(cord1_data - cord2_data, 2);

        curr_cord1 = curr_cord1->next; // going to the next coordinate in both vectors
        curr_cord2 = curr_cord2->next;
    }

    return sqrt(sum);
}

int add_to_cluster(struct vector *vec, struct cluster *currcluster, int N)  //adds vector to the right cluster
{
    struct cluster *curr_min_cluster;
    struct cluster *curr_cluster;
    while(curr_cluster->next != NULL)
    {
        double dist = coumpute_vector_distance(&(curr_cluster->centroid), vec);


    }







}

int main(int argc, char **argv)
{
    //read the file
    FILE *fileP;
    fileP = fopen(argv[-1],"r");
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
        //enter the code
    }
    return 0;
}

