#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define epsilon 0.001

typedef struct cord_s
{
    double value;
    struct cord_s *next;
} cord;

typedef struct vector_s   
{
    struct vector_s *next;
    cord *cords;
} vector;

typedef struct cluster_item_s
{
    vector *vector_item;
    struct cluster_item_s *next;
} cluster_item;

typedef struct cluster_s
{
    vector *centroid;
    cluster_item * first_item;
    struct cluster_s *next;
} cluster;


int readFile(FILE *f, vector *curr_vec, int *D){
    int dimention = 0;
    int counterD = 0;
    int N = 0;
    double num;
    cord *head_cord, *curr_cord;
    head_cord = malloc(sizeof(cord));
    curr_cord = head_cord;
    curr_cord->next = NULL;
    while (fscanf(f,"%lf",&num)== 1){
        char c;
        c = fgetc(f);
        if(EOF != c){
            //same point
             if(',' == c){
                curr_cord->value = num;
                curr_cord->next = malloc(sizeof(cord));
                curr_cord = curr_cord->next;
                curr_cord->next = NULL;
                if(*D == 0)
                    counterD++;
             }
             //moving to the next point
             else if('\n' == c){
                curr_cord->value = num;
                curr_vec->cords = head_cord;
                curr_vec->next = malloc(sizeof(vector));
                curr_vec = curr_vec->next;
                curr_vec->next = NULL;
                head_cord = malloc(sizeof(cord));
                curr_cord = head_cord;
                curr_cord->next = NULL;
                if(*D == 0)
                    *D = counterD+1;
                N++;
             }
        }
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
    if( K <= 1 || K >= N){
        printf("Invalid number of clusters!");
        valid_input = 0;
    }

    return valid_input;
}
 //struct cord *cord1;
 //struct vector vec1;

 
double coumpute_vector_distance(vector *vector1, vector *vector2)
{
    double sum;
    cord *curr_cord1,*curr_cord2;  //creating curr cordinates from vectors
    curr_cord1 = vector1->cords;
    curr_cord2 = vector2->cords;

    double cord1_data = curr_cord1->value;  //extracting values of first cords and adding to sum 
    double cord2_data = curr_cord2->value;
    sum += pow(cord1_data - cord2_data, 2);

    while (curr_cord1->next != NULL) // going over all d cordinates
    {
        curr_cord1 = curr_cord1->next; // going to the next coordinate in both vectors
        curr_cord2 = curr_cord2->next;

        double cord1_data = curr_cord1->value;  //extracting values of cords 
        double cord2_data = curr_cord2->value;

        sum += pow(cord1_data - cord2_data, 2);

    }

    return sqrt(sum);
}

void add_to_cluster(vector *vec, cluster *curr_cluster, int N)  //adds vector to the right cluster
{
    cluster *min_cluster;
    double min_dist = 10000.0;  //NEED TO CHANGE TO ACTUAL MAX
    while(curr_cluster->next != NULL)
    {
        double curr_dist = coumpute_vector_distance((curr_cluster->centroid), vec);
        if (curr_dist < min_dist)
        {
            min_cluster = curr_cluster;
            min_dist = curr_dist;
        }
    }
    cluster_item * cluster_item = malloc(sizeof(cluster_item));
    cluster_item->vector_item = vec;
    //now add vector to vector list of the min cluster
    if (NULL == min_cluster->first_item) {
        min_cluster->first_item = cluster_item;
        return;
    }
    
    if (NULL != min_cluster->first_item->next) {
        cluster_item->next = min_cluster->first_item->next;
    }
    min_cluster->first_item->next = cluster_item;
}



void print_cords(cord *head, int d)
{
    for(int i = 0; i<d-1; ++i){
        printf("%.4f, ", head->value);
        head = head->next;
    }
    printf("%.4f", head->value);
    printf("\n");
}

void print_vector(vector *head, int n, int d)
{
    for(int i = 0; i<n; ++i){
        print_cords(head->cords, d);
        head = head->next;
    }
    printf("\n");
}

void print_cluster(cluster *head, int n, int d)
{
    cluster_item *vec_in_cluster = head->first_item;
    while (NULL != vec_in_cluster) {
        print_vector(vec_in_cluster->vector_item, n , d);
        vec_in_cluster = vec_in_cluster->next;
    }
}


int main(int argc, char **argv){
    int D = 0;
    //read the file
    char file_name[100];
    scanf("%s", file_name);
    FILE *fileP;
    fileP = fopen(file_name,"r");
    vector *head_vec,*curr_vec;
    head_vec = malloc(sizeof(vector));
    curr_vec = head_vec;
    curr_vec->next = NULL;
    int N = readFile(fileP, curr_vec, &D);
    fclose(fileP);

    printf("%d\n", D);
    printf("%d\n", N);
    print_vector(head_vec, N, D);

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
    vector *vec1 = head_vec;
    vector *vec2 = head_vec->next;

    return 0;
   
}

