#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "list.h"

typedef struct {
  char nombre[52];
  char pasaporte[52];
  char pais[52];
  char favorito[52]; 
} Turista;

typedef struct{
char nombre[52];
char tipo[52];
char direccion[52];
char horario[52];
char descripcion[52];
}Punto;

void registrarPunto(HashMap* mapa, HashMap* mapaTipo){
  Punto* nuevo = (Punto*)malloc(sizeof(Punto));
  if (nuevo == NULL) {
    printf("No se pudo reservar memoria para el punto\n");
    return;
  }

  printf("\nIngrese el nombre del punto de interes: ");
  scanf(" %[^\n]", nuevo->nombre);

  Pair* auxiliar = searchMap(mapa, nuevo->nombre);
  if (auxiliar != NULL) {
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

  Pair* aux = searchMap(mapaTipo, nuevo->tipo);
  if (aux == NULL){
    List* nuevoTipo = createList();
    pushFront(nuevoTipo, nuevo);
    insertMap(mapaTipo, nuevo->tipo, nuevoTipo);
  } else {
    Pair* aux = searchMap(mapaTipo, nuevo->tipo);
    List* nuevoTipo = aux->value;
    pushBack(nuevoTipo, nuevo);
  }
}

void mostrarPunto(HashMap* mapa){
  char nombre[51];
  printf("\nIngrese el nombre del punto: ");
  scanf(" %[^\n]", nombre);
  
  Pair* aux = searchMap(mapa, nombre);
  if (aux != NULL) {
    Punto* auxiliar = aux->value;
    printf("\n————  ꒰ Datos del punto de interes ꒱  ————\n");
    printf("Nombre: %s\n", auxiliar->nombre);
    printf("Tipo: %s\n", auxiliar->tipo);
    printf("Dirección: %s\n", auxiliar->direccion);
    printf("Horario: %s\n", auxiliar->horario);
    printf("Descripción: %s\n\n", auxiliar->descripcion);
    
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

  eraseMap(mapa,nombre);
  Pair* aux = searchMap(mapaPorTipo, tipo);
  if (aux != NULL){
    List* lista = aux->value;
    Node* current = lista->head;
    Punto* auxiliar = current->data;
    while (current != NULL && auxiliar->nombre != nombre){
      current = nextList(lista);
      auxiliar = current->data;
    }
    popCurrent(lista);
    free(current);
    printf("\n***El punto ha sido eliminado correctamente***\n\n");
  } else {
    printf("\nNo se encontró ningún punto que coincidencia con su busqueda\n\n");
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

  Pair* auxiliar = searchMap(mapa, nuevo->nombre);
  if (auxiliar != NULL) {
    printf("Este turista ya ha sido se");
    free(nuevo); 
    return;
  }
  printf("Ingrese el pasaporte del turista: ");
  scanf(" %[^\n]", nuevo->pasaporte);
  printf("Ingrese el país del turista: ");
  scanf(" %[^\n]", nuevo->pais);
  strcpy(nuevo->favorito, "No tiene punto favorito");

  insertMap(mapa, nuevo->pasaporte, nuevo);
  
  Pair* aux = searchMap(mapaPais, nuevo->pais);
  if (aux == NULL) {
    List* listaPorPais = createList();
    pushFront(listaPorPais, nuevo);
    insertMap(mapaPais, nuevo->pais, listaPorPais);
  }else{
    Pair* aux = searchMap(mapaPais, nuevo->pais);
    List* listaPorPais = aux->value;
    pushBack(listaPorPais, nuevo);
  }
}

void agregarFavorito(HashMap* mapaTuristas, HashMap* mapaPuntos){ 
  char pasaporte[21];
  printf("\nIngrese el pasaporte del turista: ");
  scanf(" %[^\n]", pasaporte);

  Pair* auxiliar = searchMap(mapaTuristas, pasaporte);
  Turista* aux = auxiliar->value;
  if (aux != NULL) {
    char respuesta[1];
    if (strcmp(aux->favorito, "No tiene punto favorito")==0) {
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

    Pair* par = searchMap(mapaPuntos, nombre); 
    if (par != NULL) {
      strcpy(aux->favorito, nombre);
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

  Pair* auxiliar = searchMap(mapaPais, pais);
  if (auxiliar != NULL) {
    printf("\n————  ꒰ Turistas del país %s ꒱  ————\n", pais);
    List* aux = auxiliar->value;
    Turista* iterador = aux->head->data;
    while (iterador != NULL) {
      printf("\nNombre: %s\n", iterador->nombre);
      printf("Pasaporte: %s\n", iterador->pasaporte);
      if (strcmp(iterador->favorito, "No tiene punto favorito")==0) {
        printf("Lugar favorito: %s\n", iterador->favorito);
      }
      iterador = nextList(aux);
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

  Pair* auxiliar = searchMap(mapaTipo, tipo);
  if (auxiliar != NULL) {
    printf("\n————  ꒰ Puntos del tipo %s ꒱  ————\n", tipo);
    List* aux = auxiliar->value;
    Punto* iterador = aux->head->data;
    while (iterador != NULL) {
      printf("\nNombre: %s\n", iterador->nombre);
      printf("Dirección: %s\n", iterador->direccion);
      printf("Horario: %s\n", iterador->horario);
      printf("Descripción: %s\n", iterador->descripcion);
      iterador = nextList(aux);
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

void importarCSV_puntos(HashMap* mapaPuntos,HashMap* mapaTipo) { 
  FILE *fp = fopen ("puntos_interes.csv", "r");
  
  char linea[1024];

  fgets (linea, 1023, fp);

  while (fgets (linea, 1023, fp) != NULL) { 
    Punto *punto = (Punto *) malloc(sizeof(Punto));
    strcpy(punto->nombre, get_csv_field(linea, 0));
    strcpy(punto->tipo, get_csv_field(linea, 1)); 
    strcpy(punto->direccion, get_csv_field(linea, 2)); 
    strcpy(punto->horario, get_csv_field(linea, 3)); 
    strcpy(punto->descripcion, get_csv_field(linea, 4)); 
    insertMap(mapaPuntos, punto->nombre, punto);

    Pair* aux = searchMap(mapaTipo, punto->tipo);
    if (aux == NULL){
      List* nuevoTipo = createList();
      pushFront(nuevoTipo, punto);
      insertMap(mapaTipo, punto->tipo, nuevoTipo);
    } else {
      Pair* aux = searchMap(mapaTipo, punto->tipo);
      List* nuevoTipo = aux->value;
      pushBack(nuevoTipo, punto);
    }
  }

  fclose(fp);
}

void exportarCSV_puntos(HashMap* mapa) {
    FILE* archivo = fopen("puntos_interes.csv", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fprintf(archivo, "Nombre,Tipo,Direccion,Horario,Descripcion\n");

    Pair* par = firstMap(mapa);
    while (par != NULL) {
        Punto* punto = (Punto*)par->value;
        fprintf(archivo, "%s,%s,%s,%s,%s\n", punto->nombre, punto->tipo, punto->direccion, punto->horario, punto->descripcion);
        par = nextMap(mapa);
    }

    fclose(archivo);
    printf("Datos exportados con éxito a puntos_interes.csv\n");
}


void importarCSV_turistas(HashMap* mapaTuristas, HashMap* mapaPais) {
  FILE *fp = fopen ("turistas.csv", "r");
  char linea[1024];
  fgets (linea, 1023, fp);
  
  while (fgets (linea, 1023, fp) != NULL) { 
    Turista *turista = (Turista *) malloc(sizeof(Turista));
    strcpy(turista->nombre, get_csv_field(linea, 0)); 
    strcpy(turista->pasaporte, get_csv_field(linea, 1)); 
    strcpy(turista->pais, get_csv_field(linea, 2)); 
    strcpy(turista->favorito, get_csv_field(linea, 3));
    insertMap(mapaTuristas, turista->pasaporte, turista);

    Pair* aux = searchMap(mapaPais, turista->pais);
    if (aux == NULL) {
      List* listaPorPais = createList();
      pushFront(listaPorPais, turista);
      insertMap(mapaPais, turista->pais, listaPorPais);
    }else{
      Pair* aux = searchMap(mapaPais, turista->pais);
      List* listaPorPais = aux->value;
      pushBack(listaPorPais, turista);
    }
  }
  fclose(fp);
}

void exportarCSV_turistas(HashMap* mapa) {
    FILE* archivo = fopen("turistas.csv", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fprintf(archivo, "Nombre,Pasaporte,País,Lugares Favoritos\n");

    Pair* par = firstMap(mapa);
    while (par != NULL) {
        Turista* turista = (Turista*)par->value;
        fprintf(archivo, "%s,%s,%s,%s\n", turista->nombre, turista->pasaporte, turista->pais, turista->favorito);
        par = nextMap(mapa);
    }

    fclose(archivo);
    printf("Datos exportados con éxito a turistas.csv\n");
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
    printf("1.  [Registrar un punto de interes]\n");
    printf("2.  [Mostrar un punto de interes]\n");
    printf("3.  [Eliminar un punto de interes]\n");
    printf("4.  [Registrar turista]\n");
    printf("5.  [Agregar lugar favorito]\n");
    printf("6.  [Mostrar turistas filtrados por país]\n");
    printf("7.  [Mostrar lugares por tipo]\n");
    printf("8.  [Importar datos de puntos desde un archivo CSV]\n");
    printf("9.  [Exportar datos de puntos a un archivo CSV]\n");
    printf("10. [Importar datos de turistas desde un archivo CSV]\n");
    printf("11. [Exportar datos de turistas a un archivo CSV]\n");
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
        importarCSV_puntos(mapaPuntos,mapaTipo);
        break;
      case 9:
        exportarCSV_puntos(mapaPuntos);
        break;
      case 10:
        importarCSV_turistas(mapaTuristas,mapaPais);
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