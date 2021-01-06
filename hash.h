#ifndef HASH_H
#define HASH_H
#include <stdbool.h> 
// #define DEBUG
struct HashTable {
    unsigned int capacity;
    unsigned int nel;
    void **data;
    int (*hash)( void *, int );
    int (*compar)(const void *, const void *);
};

struct Performance {
    unsigned int reads;
    unsigned int writes;
    unsigned int mallocs;
    unsigned int frees;
};

// basic functions
struct Performance *newPerformance();
struct HashTable *createTable( struct Performance *performance,unsigned int capacity,int (*hash)( void *, int ),int (*compar)(const void *, const void *) );
void addElement( struct Performance *performance, struct HashTable *table,void *src );
int getIdx( struct Performance *performance, struct HashTable *table,void *src );
void freeTable( struct Performance *performance, struct HashTable *table );

// derived functions 
void *getElement( struct Performance *performance, struct HashTable *table,void *src );
void removeElement( struct Performance *performance, struct HashTable *table,void *target );

// last 20%
int hashAccuracy( struct HashTable *table );
void rehash( struct HashTable *table );


#endif // HASH_H
