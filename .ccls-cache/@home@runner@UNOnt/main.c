#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "Map.h"
#include <time.h>
#include <math.h>
#include <stdbool.h>

//Estructuras
typedef struct{
  int numero; //En caso de que la carta sea numérica, llevará su número, en de que no, será -1;
  int codigo; //Es el código específico para las cartas en general
  int color; //El color de la carta va de 100 en 100. En caso de que no tenga color, este será 0.
  int clave;
}tipoCarta;

typedef struct{
  int id;//NÚMERO QUE LE CORRESPONDE AL ORDEN DE INGRESO DE NOMBRE
  char jugador[100]; //NOMBRE DEL JUGADOR
  List* cartasJugador; // DE LA BARAJA DEL JUGADOR
}tipoJugador;

typedef struct{
  tipoCarta carta;
  int cont; //Contador de veces que la carta está en el mapa de cartas
}tipoMapa;

void rellenarMapaCartas(Map *mapa, int *vectorClaves){
  //Se define una carta auxiliar, el color que será 100 y se irá multiplicando y la posición del vector que 
  //se llenará que partirá en 0.
  tipoCarta cartaAux;
  int color=100;
  int posicion=0;

  /*Aquí se asignarán todas las cartas que tengan un color asignado, es decir, 
  si la carta tiene número, se le asignará y si no se le asigna -1, su código se le asigna por
  el tipo de carta que es, también se le asignará los colores correspondientes.
  */
  for(int i=0; i<=12; i++){
    if(i>=0 && i<=9) cartaAux.numero=i;
    else{
      cartaAux.numero=-1;
    }
    cartaAux.codigo=i;
    //Asignando colores
    for(int j=1; j<=4; j++){
      cartaAux.color=color*j;
      //Asignando la clave para el mapa de cartas.
      cartaAux.clave=cartaAux.color+cartaAux.codigo;
      tipoMapa *cartaMapa = malloc(sizeof(tipoMapa));
      cartaMapa->carta = cartaAux;

      int *clave = malloc(sizeof(int));
      *clave = cartaAux.clave;
      
      //Hay 2 cartas de cada una de estas en el mapa
      cartaMapa->cont = 2;
      //Se guarda la clave única en un vector para luego buscar estas cartas de manera random.
      vectorClaves[posicion]=cartaAux.clave;
      posicion++;

      //Se inserta la carta al mapa
      insertMap(mapa, clave, cartaMapa);
    }
  }

void menu(List * listaJugadores, Map* mapa, int *contJugadores,int*vectorClaves){
  //Se crea una variable "opcion" la cual será una condicionante para el ciclo "while" base de nuestro programa
  int opcion = 1;
  while(opcion != 0){
printf("\033[0;31m");
    printf("╔════════════════════════════•°🜧°•════════════════════════════╗\n");
    printf("║                  DEFINITIVAMENTE UNON'T :D                 ║\n");
    printf("╚════════════════════════════•°🜥°•════════════════════════════╝\n\n");
    printf("╔════════════════════════════•°🜧°•════════════════════════════╗\n");
    printf("║  Presione 1 para iniciar partida                            ║\n");
    printf("║  Presione 2 para cargar partida                             ║\n");
    printf("║  Presione 0 para salir del juego                            ║\n");
    printf("╚════════════════════════════•°🜥°•════════════════════════════╝\n\n");
    //Se cambia el valor de la variable "opcion" con un valor que desee el usuario realizar
    scanf("%d", &opcion);
    getchar();
    //Se utiliza un switch para acceder a las opciones de cada función
    switch(opcion){
      case 1: IniciarPartida(listaJugadores,mapa, contJugadores,vectorClaves);
      break; 
      case 2:{
        bool cargar = true;
        theGame(listaJugadores, mapa, contJugadores, vectorClaves, cargar);
      } 
      //en caso de ser cero se imprime lo sgte. Para finalizar el programa
      case 0:
        printf("         by GG WP//");
        break;
    }
  }
}


int main(void) {
  List *listaJugadores = createList();
  Map *mapa = createMap(is_equal_int);
  int contJugadores;
  int *vectorClaves =(int*) malloc(54*sizeof(int));
  rellenarMapaCartas(mapa,vectorClaves);
  srand(time(NULL));
  
  menu(listaJugadores, mapa, &contJugadores,vectorClaves);
  free(vectorClaves);
  free(listaJugadores);
  free(mapa);
  return 0;
} 