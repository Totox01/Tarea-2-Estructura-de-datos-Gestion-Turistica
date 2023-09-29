#ifndef HashMap_h
#define HashMap_h


typedef struct HashMap HashMap;

typedef struct Pair {
     char * key;
     void * value;
     struct Pair* next;
} Pair;

typedef struct{
char nombre[52];
char tipo[52];
char direccion[52];
char horario[52];
char descripcion[52];
}Punto;

struct HashMap {
    Pair ** buckets;
    long size; 
    long capacity; 
    long current; 
};

HashMap * createMap(long capacity);

void insertMap(HashMap * table, char * key, void * value);

void eraseMap(HashMap * table, char * key);

Pair * searchMap(HashMap * table, char * key);

Pair * firstMap(HashMap * table);

Pair * nextMap(HashMap * table);

void enlarge(HashMap * map);

#endif /* HashMap_h */