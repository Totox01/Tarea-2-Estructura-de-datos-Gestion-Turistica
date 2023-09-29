#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "list.h"

typedef struct {
  char *nombre;
  char* pasaporte;
  char* pais;
  char* favorito; 
} Turista;

void printMap(HashMap * map) {
  if (map == NULL || map->size == 0) {
    printf("El mapa está vacío\n");
    return;
  }
  printf("El mapa tiene %ld elementos:\n", map->size);
  Pair *par = firstMap(map);
  while (par != NULL) {
    printf("Clave: %s, Valor: %p\n", par->key, par->value);
    par = nextMap(map);
  }
}

void eraseMap(HashMap * map, char * key) {    
  Pair* par = searchMap(map,key);
  if(par!=NULL){
    free(par->key);
    free(par); 
    map->size--;
  }
}

List* getValues(HashMap* mapa) {
  List* lista = createList();
  if (mapa == NULL || mapa->size == 0) {
    return lista;
  }
  Pair* par = firstMap(mapa);
  while (par != NULL) {
    pushBack(lista, par->value);
    par = nextMap(mapa);
  }
  return lista;
}


void registrarPunto(HashMap* mapa, HashMap* mapaTipo){
  Punto* nuevo = (Punto*)malloc(sizeof(Punto));
  if (nuevo == NULL) {
    printf("No se pudo reservar memoria para el punto\n");
    return;
  }

  printf("\nIngrese el nombre del punto de interes: ");
  scanf(" %[^\n]", nuevo->nombre);

  if (searchMap(mapa, nuevo->nombre) != NULL) {
    printf("El nombre del punto ya está ocupado. Intente con otro nombre.\n");
    free(nuevo); 
    return;
  }

  printf("Ingrese el tipo de lugar: ");
  scanf(" %[^\n]", nuevo->tipo);

  printf("Ingrese la dirección del lugar: ");
  scanf(" %[^\n]", nuevo->direccion);

  printf("Ingrese el horario del lugar: ");
  scanf(" %[^\n]", nuevo->horario);

  printf("Ingrese la descripción del lugar: ");
  scanf(" %[^\n]", nuevo->descripcion);

  printf("\n***El punto ha sido registrado correctamente***\n\n");
  insertMap(mapa, nuevo->nombre, nuevo);

  List* listaPorTipo = (List *) searchMap(mapaTipo, nuevo->tipo);
  if (listaPorTipo == NULL) {
    listaPorTipo = createList();
    insertMap(mapaTipo, nuevo->tipo, listaPorTipo);
  }
  pushBack(listaPorTipo, nuevo);
}

void mostrarPunto(HashMap* mapa){
  char nombre[51];
  printf("\nIngrese el nombre del punto: ");
  scanf(" %[^\n]", nombre);

  printf("\nContenido del mapa:\n");
  printMap(mapa);
  
  Punto* aux = searchMap(mapa, nombre);
  if (aux != NULL) {
      
    printf("\n————  ꒰ Datos del punto de interes ꒱  ————\n");
    printf("Nombre: %s\n", aux->nombre);
    printf("Tipo: %s\n", aux->tipo);
    printf("Dirección: %s\n", aux->direccion);
    printf("Horario: %s\n", aux->horario);
    printf("Descripción: %s\n\n", aux->descripcion);
    
  } else {
    printf("\nNo se encontró ningún punto que coincidencia con su busqueda\n");
  }
}



void eliminarPunto(HashMap* mapa, HashMap* mapaPorTipo){
  char nombre[51];
  char tipo[21];
  printf("\nIngrese el nombre del punto: ");
  scanf(" %[^\n]", nombre);
  printf("Ingrese el tipo de punto: ");
  scanf(" %[^\n]", tipo);

  Punto* aux = (Punto *) searchMap(mapa, nombre);
  if (aux != NULL && strcmp(tipo, aux->tipo) == 0) {
    List* lista = getValues(mapa);
    Punto* current = firstList(lista);
    while (current != NULL && current != aux) {
      current = nextList(lista);
    }
    if (current == aux) {
      popCurrent(lista);
      printf("\n***El punto seleccionado ha sido eliminado***\n\n");
    }

    List* listaPorTipo = (List *) searchMap(mapaPorTipo, tipo);
    if (listaPorTipo != NULL) {
      current = firstList(listaPorTipo);
      while (current != NULL && current != aux) {
        current = nextList(listaPorTipo);
      }
      if (current == aux) {
        popCurrent(listaPorTipo);
      }
    }
    
  } else {
    printf("\nNo se encontró ningún punto que coincidencia con su busqueda\n");
  }
}




void registrarTurista(HashMap* mapa, HashMap* mapaPais){
  Turista* nuevo = (Turista*) malloc(sizeof(Turista));
  if (nuevo == NULL) {
    printf("No se pudo reservar memoria para el turista\n");
    return;
  }

  printf("\nIngrese el nombre del turista: ");
  scanf(" %[^\n]", nuevo->nombre);
  printf("Ingrese el pasaporte del turista: ");
  scanf(" %[^\n]", nuevo->pasaporte);
  printf("Ingrese el país del turista: ");
  scanf(" %[^\n]", nuevo->pais);

  insertMap(mapa, nuevo->pasaporte, nuevo);

  List* listaPorPais = (List *)searchMap(mapaPais, nuevo->pais);
  if (listaPorPais == NULL) {
    listaPorPais = createList();
    insertMap(mapaPais, nuevo->pais, listaPorPais);
  }
  pushBack(listaPorPais, nuevo);
}


void agregarFavorito(HashMap* mapaTuristas, HashMap* mapaPuntos){ 
  char pasaporte[21];
  printf("\nIngrese el pasaporte del turista: ");
  scanf(" %[^\n]", pasaporte);

  Turista* aux = (Turista *) searchMap(mapaTuristas, pasaporte);
  if (aux != NULL) {
    char respuesta[1];
    if (aux->favorito != NULL) {
      printf("El turista ya tiene un lugar favorito: %s\n", aux->favorito);
      printf("¿Desea cambiarlo por otro? (S/N): ");
      scanf(" %[^\n]", respuesta);
      if (strcmp(respuesta, "N") == 0 || strcmp(respuesta, "n") == 0) {
        return; 
      }
    }
    char nombre[51];
    printf("Ingrese el nombre del nuevo lugar favorito: ");
    scanf(" %[^\n]", nombre);

    Punto* punto = (Punto *) searchMap(mapaPuntos, nombre); 
    if (punto != NULL) {
      aux->favorito = punto->nombre;
      printf("\n***El lugar favorito ha sido agregado correctamente***\n\n");
    } else {
      printf("\nNo se encontró ningún lugar con ese nombre\n");
    }
    
  } else {
    printf("\nNo se encontró ningún turista con ese pasaporte\n");
  }
}



void mostrarTuristasPais(HashMap* mapaPais){
  char pais[21];
  printf("\nIngrese el nombre del país: ");
  scanf(" %[^\n]", pais);

  List* listaPorPais = (List *) searchMap(mapaPais, pais);
  if (listaPorPais != NULL) {
    printf("\n————  ꒰ Turistas del país %s ꒱  ————\n", pais);
    Turista* aux = firstList(listaPorPais);
    while (aux != NULL) {
      printf("\nNombre: %s\n", aux->nombre);
      printf("Pasaporte: %s\n", aux->pasaporte);
      if (aux->favorito != NULL) {
        printf("Lugar favorito: %s\n", aux->favorito);
      }
      aux = nextList(listaPorPais);
    }
    printf("\n");
  } else {
    printf("\nNo hay turistas del país %s\n", pais);
  }
}


void mostrarPuntosTipo(HashMap* mapaTipo){
  char tipo[21];
  printf("\nIngrese el nombre del tipo: ");
  scanf(" %[^\n]", tipo);

  List* listaPorTipo = (List *) searchMap(mapaTipo, tipo);
  if (listaPorTipo != NULL) {
    printf("\n————  ꒰ Puntos del tipo %s ꒱  ————\n", tipo);
    Punto* aux = firstList(listaPorTipo);
    while (aux != NULL) {
      printf("\nNombre: %s\n", aux->nombre);
      printf("Dirección: %s\n", aux->direccion);
      printf("Horario: %s\n", aux->horario);
      printf("Descripción: %s\n", aux->descripcion);
      aux = nextList(listaPorTipo);
    }
    printf("\n");
  } else {
    printf("\nNo hay puntos del tipo %s\n", tipo);
  }
}


const char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}


HashMap *importarCSV_puntos() {
    FILE *fp = fopen ("puntos_de_interes.csv", "r");

    char linea[1024];

    HashMap *puntos = createMap(100);

    fgets (linea, 1023, fp);

    while (fgets (linea, 1023, fp) != NULL) { 
        Punto *punto = (Punto *) malloc(sizeof(Punto));

        strcpy(punto->nombre, get_csv_field(linea, 0));
        strcpy(punto->tipo, get_csv_field(linea, 1)); 
        strcpy(punto->direccion, get_csv_field(linea, 2)); 
        strcpy(punto->horario, get_csv_field(linea, 3)); 
        strcpy(punto->descripcion, get_csv_field(linea, 4)); 

        insertMap(puntos, punto->nombre, punto);
    }

    fclose(fp);

    return puntos;
}

void exportarCSV_puntos(HashMap *puntos) {

    FILE *fp = fopen ("puntos_de_interes_exportados.csv", "w");

    fprintf(fp, "Nombre,Tipo,Direccion,Horario,Descripcion\n");

    Punto *punto = (Punto *) firstMap(puntos);
    
    while (punto != NULL) { 
        fprintf(fp, "%s,%s,%s,%s,%s\n", punto->nombre, punto->tipo,
                punto->direccion, punto->horario, punto->descripcion);
        punto = (Punto *) nextMap(puntos);
    }
    fclose(fp);
}

HashMap *importarCSV_turistas() {
    FILE *fp = fopen ("turistas.csv", "r");
    char linea[1024];
    HashMap *turistas = createMap(100);
    fgets (linea, 1023, fp);

    while (fgets (linea, 1023, fp) != NULL) { 

        Turista *turista = (Turista *) malloc(sizeof(Turista));
      
        strcpy(turista->pasaporte, get_csv_field(linea, 0)); 
        strcpy(turista->nombre, get_csv_field(linea, 1)); 
        strcpy(turista->pais, get_csv_field(linea, 2)); 
        insertMap(turistas, turista->pasaporte, turista);
    }
    fclose(fp);
    return turistas;
}

void exportarCSV_turistas(HashMap *turistas) {
    FILE *fp = fopen ("turistas_exportados.csv", "w");

    fprintf(fp, "Pasaporte,Nombre,Pais\n");

    Turista *turista = (Turista *)firstMap(turistas);
    
    while (turista != NULL) { 

        fprintf(fp, "%s,%s,%s\n", turista->pasaporte, turista->nombre,
                turista->pais);

        turista = (Turista *)nextMap(turistas);
    }

    fclose(fp);
}




int main(void) {
  
  HashMap* mapaPuntos = createMap(100);
  HashMap* mapaTipo = createMap(100);
  HashMap* mapaTuristas = createMap(100);
  HashMap* mapaPais = createMap(100);
  int opcion;
  printf("                        Menú Principal                   \n");
  printf("-=============================================================-\n");
  printf("  Bienvenido al programa de gestión de información turistica.\n");
  do {
    printf("-=============================================================-\n");
    printf("Por favor, elija una opción:\n");
    printf("1. [Registrar un punto]\n");
    printf("2. [Mostrar un punto de interes]\n");
    printf("3. [Eliminar un punto de interes]\n");
    printf("4. [Registrar usuario]\n");
    printf("5. [Agregar lugar favorito]\n");
    printf("6. [Mostrar clientes filtrados por país]\n");
    printf("7. [Mostrar lugares por tipo]\n");
    printf("8. [Importar puntos desde un archivo CSV]\n");
    printf("9. [Exportar puntos desde un archivo CSV]\n");
    printf("10. [Importar turistas desde un archivo CSV]\n");
    printf("11. [Exportar turistas desde un archivo CSV]\n");
    printf("12. [Salir]\n\n");
    printf("Seleccione una opcion: ");
    scanf("%i", &opcion);

    switch (opcion) {
      case 1:
        registrarPunto(mapaPuntos,mapaTipo);
        break;

      case 2:
        mostrarPunto(mapaPuntos);
        break;

      case 3:
        eliminarPunto(mapaPuntos,mapaTipo);
        break;

      case 4:
        registrarTurista(mapaTuristas,mapaPais);
        break;
      case 5:
        agregarFavorito(mapaTuristas,mapaPuntos);
        break;
      case 6:
        mostrarTuristasPais(mapaPais);
        break;
      case 7:
        mostrarPuntosTipo(mapaTipo);
        break;
      case 8:
        importarCSV_puntos();
        break;
      case 9:
        exportarCSV_puntos(mapaPuntos);
        break;
      case 10:
        importarCSV_turistas();
        break;
      case 11:
        exportarCSV_turistas(mapaTuristas);
        break;
      default:
        if (opcion<1 && opcion>12){
          printf("Opción inválida. Por favor, ingrese una opción válida.\n");
        }
    }
  } while (opcion != 12);
  printf("*** Saliendo del programa ***");

  return 0;
}