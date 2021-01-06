#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

struct Performance *newPerformance(){
   struct Performance *perf; 
   perf = (struct Performance*) malloc(sizeof(struct Performance));
   // check if array is not empty, set reads, write, mallocd and frees to zero 
   if(perf != 0){
       perf->reads = 0;
       perf->writes = 0;
       perf->mallocs = 0;
       perf->frees = 0;
   }
   else {
       printf("Make newPreformance Error! Malloc Fail!\n");
       exit(0);
   }
    return perf;
}
struct HashTable *createTable( struct Performance *performance,unsigned int capacity,int (*hash)( void *, int ),int (*compar)(const void *, const void *) ){
    struct HashTable *array = (struct HashTable*)malloc(sizeof(struct HashTable));
    int index = 0;
    
    if(array != 0){
        array->capacity = capacity;
        array->data = malloc(sizeof(void*) * array->capacity);
        array->hash = hash;
        array->compar = compar;
        array->nel = 0;
        performance->mallocs++;
        for (index = 0; index < array->capacity; index++){
            (array->data)[index] = NULL;
            performance->reads++;
        }
    }
    
    else {
       printf("Make newArray Error! malloc fail!\n");
        exit(0); 
    }
    return array;
}
void addElement( struct Performance *performance, struct HashTable *table,void *src ){
    int bucket = 0;
  

    if(table->capacity == table->nel){
        printf("addElement Error! table->nel = %d cannot be equal to capacity = %d\n",table->nel,table->capacity);
        exit(0);
    }
    bucket = table->hash(src, table->capacity);
    void* data = table->data[bucket];
        // printf("number of elements = %d < capacity = %d\n",table->nel,table->capacity);
   
        while( data != NULL){
            //increment bucket index 
            bucket++;
            if(bucket == table->capacity){
                bucket = 0;
            }
            data = table->data[bucket];

            //increment number of buckets probed 
            performance->reads++;
        }
        if(data == NULL){
            table->data[bucket] = src;
            table->nel++;
        }
    
    performance->writes++;
}

int getIdx( struct Performance *performance, struct HashTable *table,void *src ){
    int bucket = 0;
    int direction = 0;
    int index = 0;
    int j = 0;
    bucket = table->hash(src, table->capacity);

    // i points to the index and j counts how many entries in table 
    for (index = bucket, j = 0;j < table->capacity;index++,j++){
       // exceeded the capacity allowed
        if(index == table->capacity){
            index = 0;
        } 
        if(table->data[index] != NULL){
            performance->reads++;
        
            direction = table->compar(src,table->data[index]);
            // found match!
            if(direction == 0){
                return index;
            }
            
        }
       
    }
    return -1;
}
void freeTable( struct Performance *performance, struct HashTable *table ){
    free(table->data);
    free(table);
    performance->frees++;
}
void *getElement( struct Performance *performance, struct HashTable *table,void *src ){
    int index = getIdx(performance,table,src);
    if(index == -1){
        return NULL;
    }
    return table->data[index];
}
void removeElement( struct Performance *performance, struct HashTable *table,void *target ){
    int index = getIdx(performance,table,target);
    if( index != -1){
        table->data[index] = NULL;
        performance->writes++;
        table->nel--;
    }
    
}
// get number of collisions
int hashAccuracy(struct HashTable *table ){
    int index = 0;
    int bucket = 0;
    int difference = 0;
    for(index = 0; index < table->capacity;index++){
        if(table->data[index] != NULL){
            bucket = table->hash(table->data[index],table->capacity);
            if(index < bucket){
                difference = difference + index + (table->capacity-bucket);
            }
            else {
                difference = difference + index - bucket;
            }
        }    
    }
    return difference;
}
void rehash( struct HashTable *table){
   struct Performance *performance = newPerformance();
    struct HashTable *array = (struct HashTable*)malloc(sizeof(struct HashTable));
    int index = 0;
    int index2 = 0;
    int rehash = 0;
    int i = 0;
    // make new table
    if(array != 0){
        array->capacity = table->capacity;
        array->data = malloc(sizeof(void*) * array->capacity);
        array->nel = 0;
        array->compar = table->compar;
        array->hash = table->hash;
        for (index = 0; index < array->capacity; index++){
            (array->data)[index] = NULL;
        }  
    }
    // get info into new table
    for ( index2 = 0; index2 < table->capacity; index2++){
        if(table->data[index2]!=NULL){
            addElement(performance,array,table->data[index2]);
        }
        rehash = hashAccuracy(array);    
    } 
    // transfer back to original
    for ( i = 0; i < array->capacity; i++){
        table->data[i]=array->data[i];
    }
}
