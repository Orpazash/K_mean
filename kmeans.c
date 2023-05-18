#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EPSILON 0.001

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
                if (NULL != curr_vec->next) {
                    curr_vec = curr_vec->next;
                }
                curr_vec->cords = head_cord;
                curr_vec->next = malloc(sizeof(vector));
                curr_vec->next->next = NULL;
                curr_vec->next->cords = NULL;
                head_cord = malloc(sizeof(cord));
                curr_cord = head_cord;
                curr_cord->next = NULL;
                if(*D == 0)
                    *D = counterD+1;
                N++;
             }
        }
    }
    if(NULL == curr_vec->next->cords){
        free(curr_vec->next);
        curr_vec->next= NULL;
        free(head_cord);
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
 
double coumpute_vector_distance(vector *vector1, vector *vector2)
{
    double sum = 0;
    cord *curr_cord1,*curr_cord2;  //creating curr cordinates from vectors
    curr_cord1 = vector1->cords;
    curr_cord2 = vector2->cords;

    while (curr_cord1 != NULL) // going over all d cordinates
    {
        double cord1_data = curr_cord1->value;  //extracting values of cords 
        double cord2_data = curr_cord2->value;

        sum += pow(cord1_data - cord2_data, 2);

        curr_cord1 = curr_cord1->next; // going to the next coordinate in both vectors
        curr_cord2 = curr_cord2->next;
    }

    return sqrt(sum);
}

void add_to_cluster(vector *vec, cluster *curr_cluster)  //adds vector to the right cluster
{
    cluster *min_cluster;
    double min_dist = 10000.0;  //NEED TO CHANGE TO ACTUAL MAX

    while(NULL != curr_cluster){   
        double curr_dist = coumpute_vector_distance((curr_cluster->centroid), vec);
        if (curr_dist < min_dist){
            min_cluster = curr_cluster;
            min_dist = curr_dist;
        }
        curr_cluster = curr_cluster->next;
    }
    cluster_item * cluster_item = malloc(sizeof(cluster_item)); // creating new cluster item to insert cluster's list
    cluster_item->vector_item = vec;
    cluster_item->next = NULL;
    //now add vector to vector list of the min cluster:
    if (NULL == (min_cluster->first_item)) {  // if this is the first cluster item
        min_cluster->first_item = cluster_item;
        return;
    }
    
    if (NULL != min_cluster->first_item->next) { // if there are 2 items or more, append the secont item to the new item's next, and add the new after the first
        cluster_item->next = min_cluster->first_item->next;
    }
    min_cluster->first_item->next = cluster_item;
}

void add_all_to_clusters(vector *headvec, cluster *cluster) {
    vector *curr_vec = headvec;
    while(NULL != curr_vec){
        add_to_cluster(curr_vec, cluster);
        curr_vec = curr_vec->next;
    }
}

int check_epsilon(cluster *old_cluster, cluster *new_cluster) {  //returns 1 if all smaller than epsilon, 0 if not
    
    while (NULL != old_cluster){
        vector *curr_old_centroid = old_cluster->centroid;
        vector *curr_new_centroid = new_cluster->centroid;

        double curr_dist = coumpute_vector_distance(curr_old_centroid, curr_new_centroid);
        if (curr_dist > EPSILON){
            return 0;
        }
        old_cluster = old_cluster->next;
        new_cluster = new_cluster->next;
    
    }
    return 1;
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

void print_vector(vector *head, int d)
{
    while(head != NULL) {
        print_cords(head->cords, d);
        head = head->next;
    }
    printf("\n");
}

void print_cluster(cluster *head, int d)
{
    cluster_item *vec_in_cluster = head->first_item;
    while (NULL != vec_in_cluster) {
        print_cords(vec_in_cluster->vector_item->cords, d);
        vec_in_cluster = vec_in_cluster->next;
    }
}

void print_clusters(cluster *head, int d) {
    while (NULL !=head) {
        // print_cluster(head, d);
        print_cords(head->centroid->cords, d);
        head = head->next;
    }
    printf("\n");
}

vector* compute_centroid(cluster *old_cluster, int d) {
    vector * centroid = malloc(sizeof(vector));
    centroid->next = NULL;
    
    cord head;
    cord* curr = &head;
    for(int i = 0; i < d; i++){
        curr->next = malloc(sizeof(cord));
        curr = curr->next;
    }
    curr->next = NULL;
    centroid->cords = head.next;

    curr = centroid->cords;
    // d cords
    for(int i = 0; i<d; i++) {
        cluster_item *item = old_cluster->first_item;
        double total = 0;
        int counter = 0;
        // run over all the vector in the cluster
        while(NULL != item){
            vector *vec = item->vector_item;
            cord *curr_cord = vec->cords;
            // run to the relevant cord (i)
            for(int j = 0; j<i; j++){
                curr_cord = curr_cord ->next;
            }
            counter++;
            total += curr_cord->value; //update the total
            item = item->next; //moving to the next vector
        }

        //update the value of the i's cord of the centroid
        curr->value = total/counter;
        curr = curr->next;
    }

    return centroid;
}

int main(int argc, char **argv) {
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

    // get and check inputs
    int K = atoi(argv[1]);
    int iter = 200;
    if(argc==3){
        iter = atoi(argv[2]);
    }

    // if the inputs are valid 
    if(checkInput(K,iter,N)) {
        // create first k clusters (with empty vector list)
        vector *curr_vec = head_vec;
        cluster *old_cluster = malloc(sizeof(cluster)); //creating first cluster
        old_cluster->centroid = curr_vec;  //putting first vector in it
        cluster *curr_cluster = old_cluster;  //curr cluster is first cluster
        curr_cluster->first_item = NULL;
        for(int i = 0; i < K; ++i ) {
            curr_cluster->next = malloc(sizeof(cluster));  // creating new cluster at current cluster's next
            curr_cluster = curr_cluster->next;  // advancing to new cluster 
            curr_vec = curr_vec->next;  // advancing to next vector
            curr_cluster->centroid = curr_vec;  // puting next vector at new cluster
            curr_cluster->first_item = NULL;
        }
        curr_cluster->next = NULL;
        int iter_count = 0;
        while(1){
            //check if we finished the iterations
            if(iter_count == iter)
                break;

            // assign every dot to the closest cluster
            add_all_to_clusters(head_vec , old_cluster);
            //update the centroid
            cluster new_clusters;
            curr_cluster = &new_clusters;
            cluster* curr_old = old_cluster;
            for(int i = 0; i<K; i++) {
                curr_cluster->next = malloc(sizeof(cluster));
                curr_cluster = curr_cluster->next;
                curr_cluster->first_item = NULL;
                curr_cluster->centroid = compute_centroid(curr_old, D);
                curr_old = curr_old->next;
            }
            curr_cluster->next = NULL;
            cluster *new_cluster =  new_clusters.next;
            // if delta of all the dots smaller than epsilon
            if(check_epsilon(old_cluster,new_cluster))
                break;

            //update old centroids array
            cluster *temp = old_cluster;
            old_cluster = new_cluster;
            free(temp);
            iter_count++;
            print_clusters(old_cluster, D);
        }
        //printing the K centroids
        print_clusters(old_cluster, D);
    }

/*
    vector *vec1 = head_vec;
    vector *vec2 = head_vec->next;

    printf("%lf",coumpute_vector_distance(vec1,vec2));
    scanf("%lf");
*/
    return 0;
   
}
