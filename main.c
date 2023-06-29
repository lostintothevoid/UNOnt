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

int is_equal_int(void *key1, void *key2) {
  if(*(int*)key1==*(int*)key2) return 1;
  return 0;
}

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
}

/*La función saca una carta al azar del mapa de cartas (El que contiene todas las cartas) y la devuelve, a su vez, baja el contador de dicha carta en el mapa, para que indique que esa carta ya está ocupada.*/
tipoMapa *repartir(Map *mapa, int *vectorClaves) {

  //Genera numero aleatorio
  int numeroAleatorio = rand() % 54;

  //Busca la clave de una carta con ese numero aletorio como indice en el vector  
  int claveCarta = vectorClaves[numeroAleatorio];
  //Busco la carta con esa clave
  tipoMapa *cartaEntregar = (tipoMapa *)searchMap(mapa, &claveCarta);
    
  while(true){
    //Verificar disponibilidad
    if(cartaEntregar->cont != 0) {
      cartaEntregar->cont--;
      return cartaEntregar;
    }
    //En este caso todas las cartas iguales a la obtenida estan en juego entonces se saca otra
    numeroAleatorio = rand() % 54;
    claveCarta = vectorClaves[numeroAleatorio];
    cartaEntregar = (tipoMapa *)searchMap(mapa, &claveCarta);
  }
  return cartaEntregar;
}

//Crear mazos iniciales 
void crearBaraja(List *listaJugadores, Map *mapa, int *contJugadores, int *vectorClaves){
  /*a función crear baraja llama a la función repartir 7 veces 
  por cada jugador, es decir que ingresa 7 cartas a cada listaJugadores de 
  jugador*/
  
  for(int i = 1 ; i <= *contJugadores ; i++) {
    //creo la listaJugadores de cartas del jugador i 
    tipoJugador *jugador=malloc(sizeof(tipoJugador));
    jugador->id=i;
    jugador->cartasJugador = createList();
    printf("Ingrese el nickname del jugador: ");
    scanf("%[^\n]s", jugador->jugador);
    getchar();
    //se reparten las cartas al la lista de cartas del jugador
    for(int j=0; j<=6;j++){
      pushFront(jugador->cartasJugador, repartir(mapa, vectorClaves));
    }
    //se ingresa el jugador con su baraja creada en la lista de jugadores
    pushBack(listaJugadores, jugador);
  } 
}

void theGame(List *listaJugadores, Map *mapa, int *contJugadores, int *vectorClaves,bool cargar) {
  //Si la dirección es hacia la derecha, que será al principio, valdrá 0, si es al otro lado, valdrá 1.
  int direccion = 0;
  //La sumaDeCartas es el control de las cartas que hay que ir sacando durante la partida
  int sumaDeCartas = 0;
  //El color será 100 rojo, 200 azul, 300 verde y 400 amarillo
  int color = 0;
  //turnoDe es el id del jugador al que le toca
  int turnoDe = 0;
  tipoMapa *CartaArribaMapa = malloc(sizeof(tipoMapa));
  
  //Se limpia la pantalla
  system("cls");
  
  //Si no se cargaron datos se llama a la funcion repartir para inicializar la "carta sobre la mesa"
  if(cargar==false){
    CartaArribaMapa = repartir(mapa, vectorClaves);
    //Si la carta es un +4 o un cambio de color se vuelve a repartir hasta que salga una carta de color
    while(CartaArribaMapa->carta.codigo==13 || CartaArribaMapa->carta.codigo==14){
      CartaArribaMapa = repartir(mapa, vectorClaves);
    }
  }
  tipoMapa *CartaAbajo = malloc(sizeof(tipoCarta));

  //Obtenemos el primer jugador
  tipoJugador *jugadorAct = firstList(listaJugadores);
   
  //Se comprueba si se estan cargando datos, en caso de que la carga de datos resulte fallida se retorna
  if(cargar==true){
   if(cargarDatos(listaJugadores, mapa, contJugadores, vectorClaves, &direccion, &sumaDeCartas, CartaArribaMapa, CartaAbajo, &turnoDe) == false) return;
    //Se vincula turnoDe con el jugador actual
    for(jugadorAct=firstList(listaJugadores); jugadorAct!=NULL ; jugadorAct=nextList(listaJugadores)){
      if(turnoDe==jugadorAct->id) break;
    }
  }

  //El color será igual al de la carta arriba si no es un +4 o un cambio color, ya que no nos interesa que tenga ese color
  if(CartaArribaMapa->carta.codigo!=13 && CartaArribaMapa->carta.codigo){
    color=CartaArribaMapa->carta.color;  
  }


void theGameBegins(List* listaJugadores, Map* mapa, int *contJugadores, int *vectorClaves){
  //mostrarMapa(mapa);
  crearBaraja(listaJugadores,mapa, contJugadores, vectorClaves);
  theGame(listaJugadores,mapa, contJugadores, vectorClaves,false);
  
  return;
}

//Función para seleccionar la cantidad de jugadores
void IniciarPartida(List *listaJugadores, Map *mapa, int *contJugadores, int *vectorClaves){
  int opcion = 1;
  while(opcion != 0){
    printf("\033[0;37m");

    printf("╔════════════════════════════•°🜧°•════════════════════════════╗\n");
    printf("║  Ingrese una cantidad de jugadores entre 2 y 4              ║\n");
    printf("║  Presione 0 para volver al menu inicial                     ║\n");
    printf("╚════════════════════════════•°🜥°•════════════════════════════╝\n\n");
    
    scanf("%d", contJugadores);
    opcion=(*contJugadores);
    getchar();
  
    if(opcion>=2 && opcion<=4){
      theGameBegins(listaJugadores,mapa, contJugadores,vectorClaves);
      return;
    } 
         
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