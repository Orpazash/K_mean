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


int readFile(FILE *f, struct vector *curr_vec, int *D){
    int dimention = 0;
    int counterD = 0;
    int N = 0;
    double num;
    struct cord *head_cord, *curr_cord;
    head_cord = malloc(sizeof(struct cord));
    curr_cord = head_cord;
    curr_cord->next = NULL;
    while (fscanf(f,"%lf",&num)== 1){
        char c;
        c = fgetc(f);
        if(EOF != c){
            //same point
             if(',' == c){
                curr_cord->value = num;
                curr_cord->next = malloc(sizeof(struct cord));
                curr_cord = curr_cord->next;
                curr_cord->next = NULL;
                if(*D == 0)
                    counterD++;
             }
             //moving to the next point
             else if('\n' == c){
                curr_cord->value = num;
                curr_vec->cords = head_cord;
                curr_vec->next = malloc(sizeof(struct vector));
                curr_vec = curr_vec->next;
                curr_vec->next = NULL;
                head_cord = malloc(sizeof(struct cord));
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

void print_cords(struct cord *head, int d)
{
    for(int i = 0; i<d-1; ++i){
        printf("%.4f, ", head->value);
        head = head->next;
    }
    printf("%.4f", head->value);
    printf("\n");
}

void print_vector(struct vector *head, int n, int d)
{
    for(int i = 0; i<n; ++i){
        print_cords(head->cords, d);
        head = head->next;
    }
    printf("\n");
}

void print_cluster(struct cluster *head, int k, int d)
{
    for(int i = 0; i<k; ++i){
        print_cords(head->centroid->cords,d);
        head = head->next;
    }
}


struct cluster *compute_centroid(struct cluster *old_cluster){

}


int main(int argc, char **argv){
    int D = 0;
    //read the file
    char file_name[100];
    scanf("%s", file_name);
    FILE *fileP;
    fileP = fopen(file_name,"r");
    struct vector *head_vec,*curr_vec;
    head_vec = malloc(sizeof(struct vector));
    curr_vec = head_vec;
    curr_vec->next = NULL;
    int N = readFile(fileP, curr_vec, &D);
    fclose(fileP);

    printf("%d\n", D);
    printf("%d\n", N);
    //print_vector(head_vec, N, D);
    

    // get and check inputs
    int K = atoi(argv[1]);
    int iter = 200;
    if(argc==3){
        iter = atoi(argv[2]);
    }

    // if the inputs are valid 
    if(checkInput(K,iter,N)){

        //create initial cluster (the first K points)
        struct cluster *head_clust,*curr_clust;
        head_clust = malloc(sizeof(struct cluster));
        curr_clust = head_clust;
        curr_clust->next = NULL;
        curr_vec = head_vec;
        for(int i = 0; i < K; ++i){
            curr_clust->centroid = malloc(sizeof(struct vector));
            curr_clust->centroid->cords= curr_vec->cords;
            curr_clust->vector_list = NULL;
            curr_clust->next = malloc(sizeof(struct cluster));
            curr_clust = curr_clust->next;
            curr_clust->next = NULL;
            curr_vec = curr_vec -> next;
        }
        print_vector(head_vec, N, D);
        printf("clasters:\n");
        print_cluster(head_clust, K, D);
        scanf("%s", file_name);
    }
    return 0;
}

