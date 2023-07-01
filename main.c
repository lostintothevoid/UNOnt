#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "Map.h"
#include <time.h>
#include <conio.h>
#include <math.h>
#include <stdbool.h>
#include "gotoxy.h"
#include "mostrarcartas.h"

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


//Funciones

//Función para el mapa
int is_equal_int(void *key1, void *key2) {
  if(*(int*)key1==*(int*)key2) return 1;
  return 0;
}

//Función de admin para mostrar todo el mapa con las cartas
void mostrarMapa(Map* mapa) {
    // Obtener el primer elemento del mapa
    void* elemento = firstMap(mapa);

    // Recorrer el mapa e imprimir cada elemento
    while (elemento != NULL) {
        tipoMapa* cartaMapa = (tipoMapa*)elemento;
        tipoCarta carta = cartaMapa->carta;

        // Obtener el siguiente elemento del mapa
        elemento = nextMap(mapa);
    }
}

//Función de admin para mostrar todas las cartas de todos los jugadores
void mostrarListasJugadores(List* listaJugadores) {
    List* jugadorNode = firstList(listaJugadores);

    while (jugadorNode != NULL) {
        tipoJugador* jugador = (tipoJugador*)jugadorNode;

        printf("Jugador: %s\n", jugador->jugador);
        printf("Cartas:\n");

       if(firstList(jugador->cartasJugador) == NULL) printf("CARTAS NULL\n");
        tipoMapa* cartaNode = firstList(jugador->cartasJugador);
      
        while (cartaNode != NULL) {
            tipoMapa* cartaMapa = (tipoMapa*)cartaNode;
            tipoCarta carta = cartaMapa->carta;
            printf("Color: %d, Codigo: %d, Numero: %d\n", carta.color, carta.codigo, carta.numero);
            cartaNode = nextList(jugador->cartasJugador);
        }
        jugadorNode = nextList(listaJugadores);
        
    }
}

//Función para crear todas las cartas del juego e insertarlas en el mapa
void rellenarMapaCartas(Map *mapa, int *vectorClaves) {
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

  //Lo mismo que con las cartas anteriores pero con el +4 y cambio color, que no poseen ni número ni color.
  for(int i=13; i<=14; i++){
    cartaAux.numero=-1;
    cartaAux.codigo=i;
    cartaAux.clave = cartaAux.codigo;
    cartaAux.color=0;
    tipoMapa *cartaMapa = malloc(sizeof(tipoMapa));;
    cartaMapa->carta = cartaAux;
    cartaMapa->cont = 4;
    vectorClaves[posicion]=cartaAux.clave;
    posicion++;
    
    int *clave = malloc(sizeof(int));
      *clave = cartaAux.clave;
    insertMap(mapa, clave, cartaMapa);
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
void crearBaraja(List *listaJugadores, Map *mapa, int *contJugadores, int *vectorClaves) {
  /*a función crear baraja llama a la función repartir 7 veces 
  por cada jugador, es decir que ingresa 7 cartas a cada listaJugadores de 
  jugador*/
  gotoxy(15,6);colorCarta(4);printf("JUGADORES");
  gotoxy(10,7);colorCarta(2);printf("============================================================");
  for(int i = 1 ; i <= *contJugadores ; i++) {
    
    //creo la listaJugadores de cartas del jugador i 
    tipoJugador *jugador=malloc(sizeof(tipoJugador));
    jugador->id=i;
    jugador->cartasJugador = createList();
    gotoxy(15,i + 7);colorCarta(4);printf("Ingrese el nickname del jugador %i: ", i);
    scanf("%[^\n]s", jugador->jugador);
    getchar();
    //se reparten las cartas al la lista de cartas del jugador
    for(int j=0; j<=6;j++){
      pushFront(jugador->cartasJugador, repartir(mapa, vectorClaves));
    }
    //se ingresa el jugador con su baraja creada en la lista de jugadores
    pushBack(listaJugadores, jugador);
    
  }
  system("cls"); 
}

//Función para imprimir un mensaje de felicitaciones al jugador que ganó
void theGameEnd(char *nombreJugador) {
  system("cls");

  gotoxy(88,7);colorCarta(2);printf("=======================================");
  gotoxy(95,8);colorCarta(4);printf("GANADOR: %s\n\n", nombreJugador);
  gotoxy(88,9);colorCarta(2);printf("=======================================");
  return;
}

//Función para obtener la carta central
tipoMapa *puntocentral(List *barajajugador) {
  //Se inicializa un contador que nos ayudará a saber el total de cartas para luego sacar la mitad
  int contcentro = 0;
  //Tomamos la primera carta de la baraja
  tipoMapa *aux = firstList(barajajugador);

  //Recorremos toda la baraja y vamos sumando al contador del total
  while(aux!=NULL){
    aux = nextList(barajajugador);
    contcentro++;
  }

  //Obtenemos la mitad del contador
  int centro = trunc(contcentro/2);

  //inicializamos la variable auxiliar con la primera carta
  aux = firstList(barajajugador);
  //Recorremos nuevamente toda la baraja pero solo hasta llegar al centro
  while(centro!=0){
    aux=nextList(barajajugador);
    centro--;
  }
  //Devolvemos la carta que está en el centro
  return aux;
}

//Función que muestra la baraja del jugador y le perimte desplazarse a través de ella retornando la que escoja
tipoMapa *turnojugador(List *barajajugador, tipoCarta CartaArriba, int sumaDeCartas, int *color) {

  //Se inicializan las variables que indican las carta carta central, la anterior y la siguiente
  tipoMapa *centro = puntocentral(barajajugador);
  tipoMapa *next = nextList(barajajugador);
  centro = puntocentral(barajajugador);
  tipoMapa *prev = prevList(barajajugador); 
  tipoMapa *aux;

  //se reestablece la central para asegurarse que esta bien centrada
  centro = puntocentral(barajajugador);
  
  char uno = 0;
  int tecla=0;
  gotoxy(74,13);colorCarta(4);printf  ("Presione la tecla izquierda o derecha para ver tus cartas\n");
  
  while(tecla != 75 && tecla != 77)
  {
    kbhit();
    tecla = getch();
    gotoxy(74,13);colorCarta(0);printf("                                                         \n");
  }

  //Se comienza el ciclo para mostrar la baraja que se rompe una vez el usuario selecciona una carta válida
  while(true){
    printf("\033[?25l");
    gotoxy(92,19);mostrarMargen(0);printf("\n");
    gotoxy(92,20);primeraLinea(CartaArriba.clave);printf("\n");
    gotoxy(92,21);segundaLinea(CartaArriba.clave);printf("\n");
    gotoxy(92,22);terceraLinea(CartaArriba.clave);printf("\n");
    gotoxy(92,23);cuartaLinea(CartaArriba.clave);printf("\n");
    gotoxy(92,24);quintaLinea(CartaArriba.clave);printf("\n");
    gotoxy(92,25);sextaLinea(CartaArriba.clave);printf("\n");
    gotoxy(92,26);septimaLinea(CartaArriba.clave);printf("\n");
    gotoxy(92,27);octavaLinea(CartaArriba.clave);printf("\n");
    gotoxy(92,28);mostrarMargen(1);printf("\n");
    if(next!=NULL || prev!=NULL){
      gotoxy(92,37);mostrarMargen(0);printf("\n");
      gotoxy(92,38);primeraLinea(centro->carta.clave);printf("\n");
      gotoxy(92,39);segundaLinea(centro->carta.clave);printf("\n");
      gotoxy(92,40);terceraLinea(centro->carta.clave);printf("\n");
      gotoxy(92,41);cuartaLinea(centro->carta.clave);
      gotoxy(92,42);quintaLinea(centro->carta.clave);
      gotoxy(92,43);sextaLinea(centro->carta.clave);
      gotoxy(92,44);septimaLinea(centro->carta.clave);
      gotoxy(92,45);octavaLinea(centro->carta.clave);
      gotoxy(92,46);mostrarMargen(1);
    }
    else if (next==NULL && prev==NULL)
    {
      gotoxy(92,37);mostrarMargen(0);printf("\n");
      gotoxy(92,38);primeraLinea(centro->carta.clave);printf("\n");
      gotoxy(92,39);segundaLinea(centro->carta.clave);printf("\n");
      gotoxy(92,40);terceraLinea(centro->carta.clave);printf("\n");
      gotoxy(92,41);cuartaLinea(centro->carta.clave);
      gotoxy(92,42);quintaLinea(centro->carta.clave);
      gotoxy(92,43);sextaLinea(centro->carta.clave);
      gotoxy(92,44);septimaLinea(centro->carta.clave);
      gotoxy(92,45);octavaLinea(centro->carta.clave);
      gotoxy(92,46);mostrarMargen(1);
      
      gotoxy(30,19);printf(" _    _  _   _   ____   _  _  _\n");
      gotoxy(30,20);printf("| |  | || \\ | | / __ \\ | || || |\n");
      gotoxy(30,21);printf("| |  | ||  \\| || |  | || || || |\n");
      gotoxy(30,22);printf("| |  | || . ` || |  | || || || |\n");
      gotoxy(30,23);printf("| |__| || |\\  || |__| ||_||_||_|\n");
      gotoxy(30,24);printf(" \\____/ |_| \\_| \\____/ (_)(_)(_)\n");  
    }

    if(prev != NULL){
      gotoxy(75,41);mostrarMargen(0);
      gotoxy(75,42);primeraLinea(prev->carta.clave);
      gotoxy(75,43);segundaLinea(prev->carta.clave);
      gotoxy(75,44);terceraLinea(prev->carta.clave);
      gotoxy(75,45);cuartaLinea(prev->carta.clave);
      gotoxy(75,46);quintaLinea(prev->carta.clave);
      gotoxy(75,47);sextaLinea(prev->carta.clave);
      gotoxy(75,48);septimaLinea(prev->carta.clave);
      gotoxy(75,49);octavaLinea(prev->carta.clave);
      gotoxy(75,50);mostrarMargen(1);
    }
    else {
      gotoxy(75,41);mostrarMargen(2);
      gotoxy(75,42);mostrarMargen(2);
      gotoxy(75,43);mostrarMargen(2);
      gotoxy(75,44);mostrarMargen(2);
      gotoxy(75,45);mostrarMargen(2);
      gotoxy(75,46);mostrarMargen(2);
      gotoxy(75,47);mostrarMargen(2);
      gotoxy(75,48);mostrarMargen(2);
      gotoxy(75,49);mostrarMargen(2);
      gotoxy(75,50);mostrarMargen(2);
    }

    if(next!=NULL){
      gotoxy(109,41);mostrarMargen(0);printf("\n");
      gotoxy(109,42);primeraLinea(next->carta.clave);printf("\n");
      gotoxy(109,43);segundaLinea(next->carta.clave);printf("\n");
      gotoxy(109,44);terceraLinea(next->carta.clave);printf("\n");
      gotoxy(109,45);cuartaLinea(next->carta.clave);printf("\n");
      gotoxy(109,46);quintaLinea(next->carta.clave);printf("\n");
      gotoxy(109,47);sextaLinea(next->carta.clave);printf("\n");
      gotoxy(109,48);septimaLinea(next->carta.clave);printf("\n");
      gotoxy(109,49);octavaLinea(next->carta.clave);printf("\n");
      gotoxy(109,50);mostrarMargen(1);printf("\n");
    }
    else {
      gotoxy(109,41);mostrarMargen(2);printf("\n");
      gotoxy(109,42);mostrarMargen(2);printf("\n");
      gotoxy(109,43);mostrarMargen(2);printf("\n");
      gotoxy(109,44);mostrarMargen(2);printf("\n");
      gotoxy(109,45);mostrarMargen(2);printf("\n");
      gotoxy(109,46);mostrarMargen(2);printf("\n");
      gotoxy(109,47);mostrarMargen(2);printf("\n");
      gotoxy(109,48);mostrarMargen(2);printf("\n");
      gotoxy(109,49);mostrarMargen(2);printf("\n");
      gotoxy(109,50);mostrarMargen(2);printf("\n");
    }
    if(kbhit()){
      gotoxy(30,30);tecla = getch();
      

      switch(tecla){
    
        case 77:{//derecha
          if(next==NULL){
            break;
          }
          prev = centro;
          centro = nextList(barajajugador);
          next = nextList(barajajugador);
          if(next != NULL){
            aux = prevList(barajajugador);  
          }
          break;
        }
        
        case 75:{//izquierda
          if(prev == NULL){
            break;
          }
          next = centro;
          centro = prevList(barajajugador);
          prev =  prevList(barajajugador);
          if(prev != NULL){
            aux = nextList(barajajugador);
          }
          break;
        }
        
        case 32:{
          //Comprobar si puede tirar la carta
        
          //comprobar si tiro un mas algo teniendo una suma pendiente
          if(sumaDeCartas > 0 ){
            if(centro->carta.codigo == 13 || centro->carta.codigo == 12){
              if(centro->carta.codigo == 13){
                gotoxy(2,51);printf("¿A que color quieres cambiar?\n");
                gotoxy(2,52);colorCarta(1);printf("1. Rojo\n");
                gotoxy(2,53);colorCarta(2);printf("2. Azul\n");
                gotoxy(2,54);colorCarta(3);printf("3. Verde\n");
                gotoxy(2,55);colorCarta(4);printf("4. Amarillo\n");
                
                int flecha = 1;
                int tecla;
                while (true){
                  printf("\033[?25l");
                  gotoxy(1, flecha + 51);
                  printf(">");
                  tecla = getch();
                  gotoxy(1, flecha + 51);
                  printf(" ");

                  if (tecla == 32) {
                    break;  // Presionar Enter para seleccionar la opción
                  } else if (tecla == 224) {
                    tecla = getch();  // Leer la tecla de flecha
                    if (tecla == 72) {
                      // Flecha hacia arriba
                      if (flecha > 1) {
                        flecha--;
                      }
                    } else if (tecla == 80) {
                      // Flecha hacia abajo
                      if (flecha < 4) {
                        flecha++;
                      }
                    }
                  }
                }

                switch(flecha){
                  case 1: *color=100;
                          break;
                  case 2: *color=200;
                          break;
                  case 3: *color=300;
                          break;
                  case 4: *color=400;
                          break;
                }
                return centro;
              } 
              return centro;
            }

            gotoxy(1,51);printf("            \n");
            gotoxy(1,52);printf("             \n");
            gotoxy(1,53);printf("              \n");
            gotoxy(1,54);printf("                \n");
            gotoxy(1,55);printf("                 \n");
          }

          //comprobar si coincide el color
          if(centro->carta.color == *color && sumaDeCartas == 0){
            return centro;
          }
        
          //comprobar si coincide el numero/simbolo
          if(centro->carta.codigo == CartaArriba.codigo && sumaDeCartas == 0){
            return centro;
          }

          if(sumaDeCartas==0 && (centro->carta.codigo==14 || centro->carta.codigo==13)){
            gotoxy(2,51);printf("¿A que color quieres cambiar?\n");
            gotoxy(2,52);colorCarta(1);printf("1. Rojo\n");
            gotoxy(2,53);colorCarta(2);printf("2. Azul\n");
            gotoxy(2,54);colorCarta(3);printf("3. Verde\n");
            gotoxy(2,55);colorCarta(4);printf("4. Amarillo\n");

            int flecha = 1;
            int tecla;
            while (true){
              printf("\033[?25l");
              gotoxy(1, flecha + 51);
              printf(">");
              tecla = getch();
              gotoxy(1, flecha + 51);
              printf(" ");

              if (tecla == 32) {
                break;  // Presionar Enter para seleccionar la opción
              } else if (tecla == 224) {
                tecla = getch();  // Leer la tecla de flecha
                if (tecla == 72) {
                  // Flecha hacia arriba
                  if (flecha > 1) {
                    flecha--;
                  }
                } else if (tecla == 80) {
                  // Flecha hacia abajo
                  if (flecha < 4) {
                    flecha++;
                  }
                }
              }
            }

            switch(flecha){
              case 1: *color=100;
                      break;
              case 2: *color=200;
                      break;
              case 3: *color=300;
                      break;
              case 4: *color=400;
                      break;
            }
            gotoxy(1,51);printf("                             \n");
            gotoxy(1,52);printf("              \n");
            gotoxy(1,53);printf("              \n");
            gotoxy(1,54);printf("                \n");
            gotoxy(1,55);printf("                 \n");
            return centro;
          }
          colorCarta(4);
          gotoxy(52,11);
          printf("  _______   _                            _                                            _           \n");
          gotoxy(52,12);
          printf(" |__   __| (_)                          | |                                          | |          \n");
          gotoxy(52,13);
          printf("    | |     _   _ __    __ _      ___   | |_   _ __    __ _      ___    __ _   _ __  | |_    __ _ \n");
          gotoxy(52,14);
          printf("    | |    | | | '__|  / _` |    / _ \\  | __| | '__|  / _` |    / __|  / _` | | '__| | __|  / _` |\n");
          gotoxy(52,15);
          printf("    | |    | | | |    | (_| |   | (_) | | |_  | |    | (_| |   | (__  | (_| | | |    | |_  | (_| |\n");
          gotoxy(52,16);
          printf("    |_|    |_| |_|     \\__,_|    \\___/   \\__| |_|     \\__,_|    \\___|  \\__,_| |_|     \\__|  \\__,_|\n");
          colorCarta(0);
          break;
        }

        case 122:{
          return NULL;
        }
        case 120:{
          tipoMapa* cartaBool = malloc(sizeof(tipoMapa));
          cartaBool->carta.clave=999;
          return cartaBool;
        }
      }
    }
    //A estas alturas ya tenemos la carta que jugó el jugador y la devolvimos
  }
}

//Función que guarda una partida
void exportarDatos(List *listaJugadores, Map *mapa, int *contJugadores, int *vectorClaves, int direccion, int sumaDeCartas, tipoMapa *CartaArribaMapa, tipoMapa *CartaAbajo, tipoJugador *jugadorAct) {
  //Se crea una string estática para dar un nombre al archivo qsue exportará a los jugadores
  system("cls");
  char archivo[100];
  gotoxy(80,25);
  colorCarta(2);
  printf("===================================================");
  gotoxy(80, 26);
  colorCarta(4);
  printf("Escribe el nombre con el que guardaras tu partida:\n");
  gotoxy(80,28);
  colorCarta(2);
  printf("===================================================");
  colorCarta(0);
  gotoxy(80, 27);scanf("%[^\n]s",archivo);
  getchar();
  FILE *fp = fopen(archivo, "w");

  //En la primera linea, para ordenarnos indicaremos las variables que guardaremos
  fprintf(fp, "Datos de partida: contJugadores, Direccion, sumDeCartas, CartaArribaMapa.numero, CartaArribaMapa.codigo, CartaArribaMapa.color, CartaArribaMapa.clave, CartaArribaMapa.cont, CartaAbajo.numero, CartaAbajo.codigo, CartaAbajo.color, CartaAbajo.clave, CartaAbajo.cont, jugadorAct.id\n");

  //En la segunda linea son todos los parámetros indicados en la primera
  fprintf(fp, "%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i\n", *contJugadores, direccion, sumaDeCartas, CartaArribaMapa->carta.numero, CartaArribaMapa->carta.codigo, CartaArribaMapa->carta.color, CartaArribaMapa->carta.clave, CartaArribaMapa->cont, CartaAbajo->carta.numero, CartaAbajo->carta.codigo, CartaAbajo->carta.color, CartaAbajo->carta.clave, CartaAbajo->cont, jugadorAct->id);
  
  //En la tercera linea será para indicar que harán las siguientes lineas, las cuales serán los jugadores
  fprintf(fp, "NombreJugador,ID jugador,Carta 1,numero, codigo, color, clave,Carta 2,Carta 3,Carta 4,Carta 5,Carta 6,Carta 7,Carta ...\n");
  //Se comienza a recorrer la lista jugaadores para imprimir los datos al archivo que se exportará todo
  for (tipoJugador *player = firstList(listaJugadores) ; player != NULL ; player = nextList(listaJugadores)){
    fprintf(fp, "%s,%d,", player->jugador, player->id);
    
    //Dentro de la iteración "for", se entra a otra, ya que puede existir el caso de que hayan más de un item
    for(tipoMapa* carta=firstList(player->cartasJugador) ; carta!=NULL; carta=nextList(player->cartasJugador)){
      
      fprintf(fp, "%i,%i,%i,%i,%i,", carta->cont, carta->carta.numero, carta->carta.codigo, carta->carta.color, carta->carta.clave);
    }
    fprintf(fp, "\n");
  }

  //La siguiente linea ya cuando se terminó de registrar a los jugadores, es para indicar las siguientes lineas
  //las cuales se tratan de las cartas guardadas en el mapa
  fprintf(fp, "Map: contador,numero, codigo, color, clave\n");
  
  void* elemento = firstMap(mapa);

  //Se guardan todas las cartas del mapa en el archivo linea por linea
  while (elemento != NULL) {
      tipoMapa* cartaMapa = (tipoMapa*)elemento;
      
       fprintf(fp, "%i,%i,%i,%i,%i,", cartaMapa->cont, cartaMapa->carta.numero, cartaMapa->carta.codigo, cartaMapa->carta.color, cartaMapa->carta.clave);
       fprintf(fp, "\n");
    
      elemento = nextMap(mapa);
  }
  
  system("cls");
  //De no haber errores, se muestra el siguiente mensaje por pantalla 
  gotoxy(90,25);printf("==========================\n");
  gotoxy(90,26);printf("Partida guardada con exito\n");
  gotoxy(90,28);printf("==========================\n");
  fclose(fp);
  
}

bool cargarDatos(List *listaJugadores, Map *mapa, int *contJugadores, int *vectorClaves, int *direccion, int *sumaDeCartas, tipoMapa *CartaArribaMapa, tipoMapa *CartaAbajo, int *turnoDe) {
  char archivo[100];
  //Se le pide al usuario que ingrese el nombre del archivo de donde desea importar las tareas
  gotoxy(67,20);
  printf("Ingresa el nombre de la partida que quieras cargar:\n");
  //fflush(stdin);
  gotoxy(67,21);
  scanf("%[^\n]s",archivo);
  getchar();
  system("cls");

  //Se abre el archivo
  FILE *fp=fopen(archivo, "r");
  while(fp==NULL){
    gotoxy(67,21);printf("===============================================================\n");
    gotoxy(75,22);printf("                   Error al cargar Partida...\n");
    gotoxy(70,23);printf("        Asegurese de cargar al juego con el mismo nombre\n");
    gotoxy(67,24);printf("===============================================================\n\n");

    gotoxy(90,27);printf("\nPresione una tecla para continuar...");
    int tecla = 0;
    if(kbhit){
      tecla=getch();
    }
    system("cls");

    gotoxy(67,20);
    printf("Ingresa el nombre de la partida que quieras cargar:\n");
    gotoxy(67,21);
    scanf("%[^\n]s",archivo);
    getchar();
    fp=fopen(archivo, "r");
    system("cls");
  }

  char linea[300];
  //Se obtiene la primera línea (Que no nos sirve porque son las descripciones de las columnas)
  fgets(linea,301,fp);

  int j=0;
  //A partir de aqui las lineas son importante porque tienen la información que necesitamos
  while(fgets(linea,301,fp)!=NULL){
    
    tipoJugador *player;
    player=malloc(sizeof(tipoJugador));
    //Se empieza a obtener cada parámetro a través de strtok, asi guardandose en sus variables correspondientes
    linea[strlen(linea)-1] = 0;
    
    char *ch = strtok(linea, ",");

    //Aqui se obtiene todo lo relacionado con la partida, es decir, el turno, la carta que está arriba, dirección, etc.
    if(j==0){
      
      *contJugadores = atoi(ch);

      ch = strtok(NULL,",");
      *direccion= atoi(ch);

      ch = strtok(NULL,",");
      *sumaDeCartas= atoi(ch);
    
      ch = strtok(NULL,",");
      CartaArribaMapa->carta.numero = atoi(ch);
        
      ch = strtok(NULL,",");
      CartaArribaMapa->carta.codigo = atoi(ch);

      ch = strtok(NULL,",");
      CartaArribaMapa->carta.color = atoi(ch);

      ch = strtok(NULL,",");
      CartaArribaMapa->carta.clave = atoi(ch);

      ch = strtok(NULL,",");
      CartaArribaMapa->cont = atoi(ch);

      ch = strtok(NULL,",");
      CartaAbajo->carta.numero = atoi(ch);
        
      ch = strtok(NULL,",");
      CartaAbajo->carta.codigo = atoi(ch);

      ch = strtok(NULL,",");
      CartaAbajo->carta.color = atoi(ch);

      ch = strtok(NULL,",");
      CartaAbajo->carta.clave = atoi(ch);

      ch = strtok(NULL,",");
      CartaAbajo->cont = atoi(ch);

      ch = strtok(NULL,",");
      *turnoDe = atoi(ch);
      j++;
    }

    if(j==1){
      fgets(linea,301,fp);
      fgets(linea,301,fp);  
      linea[strlen(linea)-1] = 0;
    }

    
    //Se obtienen los datos de los jugadores con todas sus cartas.
    if(j<=*contJugadores){
      tipoMapa *carta = malloc(sizeof(tipoMapa));
      if(j<2){
        ch = strtok(linea,",");  
      }
      strcpy(player->jugador,ch);        

      ch = strtok(NULL,",");
      player->id = atoi(ch);

      player->cartasJugador=createList();
    
      ch = strtok(NULL,",");

      while(ch != NULL){

      tipoMapa* carta = malloc(sizeof(tipoCarta));
      carta->cont = atoi(ch);   

      ch = strtok(NULL,",");
      carta->carta.numero = atoi(ch);   
      
      ch = strtok(NULL,",");
      carta->carta.codigo =atoi(ch);   
      
      ch = strtok(NULL,",");
      carta->carta.color = atoi(ch);   
        
      ch = strtok(NULL,",");
      carta->carta.clave = atoi(ch);
      
      pushBack(player->cartasJugador, carta);
      
      ch = strtok(NULL,",");
      }
      pushBack(listaJugadores, player);
    }
    
    if(j==*contJugadores){
      fgets(linea,301,fp);
      linea[strlen(linea)-1] = 0;
    }

    //Se guardan las cartas en el mapa de cartas
    if(j>*contJugadores){
      tipoMapa *carta = malloc(sizeof(tipoMapa));
    
      //ch = strtok(NULL,",");
      carta->cont = atoi(ch);   
  
      ch = strtok(NULL,",");
      carta->carta.numero = atoi(ch);   
        
      ch = strtok(NULL,",");
      carta->carta.codigo =atoi(ch);   
        
      ch = strtok(NULL,",");
      carta->carta.color = atoi(ch);   
          
      ch = strtok(NULL,",");
      carta->carta.clave = atoi(ch);
        
      int *clave = malloc(sizeof(int));
        *clave = carta->carta.clave;
      insertMap(mapa, clave, carta);
    }
    j++;
  }

    gotoxy(30,1);printf("                                                                \n");
    gotoxy(30,2);printf("                                                               \n");
    gotoxy(30,3);printf("                                                                 \n\n");
    gotoxy(30,4);printf("                                                               \n");
    gotoxy(30,5);printf("                                                                \n");
    gotoxy(30,6);printf("                                                               \n");
    gotoxy(30,7);printf("                                                                \n");
    gotoxy(30,8);printf("                                                                \n\n");
  
  gotoxy(70,1);printf("===============================================================\n");
  gotoxy(80,2);printf("        La partida fue cargada con exito\n");
  gotoxy(70,3);printf("===============================================================\n\n");
  fclose(fp);
  gotoxy(90,27);printf("\nPresione una tecla para continuar...");
  int tecla = 0;
  if(kbhit){
    tecla=getch();
  }

  return true;
}

void theGame(List *listaJugadores, Map *mapa, int *contJugadores, int *vectorClaves,bool cargar) {
  //Si la dirección es hacia la derecha, que será al principio, valdrá 0, si es al otro lado, valdrá 1.
  int direccion = 0;
  int sumaDeCartas = 0;
  int color = 0;
  int turnoDe = 0;
  tipoMapa *CartaArribaMapa = malloc(sizeof(tipoMapa));
  
  if(cargar==false){
    CartaArribaMapa = repartir(mapa, vectorClaves);
    while(CartaArribaMapa->carta.codigo==13 || CartaArribaMapa->carta.codigo==14){
      CartaArribaMapa = repartir(mapa, vectorClaves);
    }
  }
  tipoMapa *CartaAbajo = malloc(sizeof(tipoCarta));
   
  tipoJugador *jugadorAct = firstList(listaJugadores);
  
  if(cargar==true){
   if(cargarDatos(listaJugadores, mapa, contJugadores, vectorClaves, &direccion, &sumaDeCartas, CartaArribaMapa, CartaAbajo, &turnoDe) == false) return;
    //hay que vincular turnoDe con el jugador actual
    for(jugadorAct=firstList(listaJugadores); jugadorAct!=NULL ; jugadorAct=nextList(listaJugadores)){
      if(turnoDe==jugadorAct->id) break;
    }
  }
  //mostrarListasJugadores(listaJugadores);
  if(CartaArribaMapa->carta.codigo!=13 && CartaArribaMapa->carta.codigo){
    color=CartaArribaMapa->carta.color;  
  }
  
  while(true){//(true)
    system("cls");
    printf("\033[?25l");
    //mostrarListasJugadores(listaJugadores);
    gotoxy(84,8);colorCarta(2);printf("==============================\n");
    gotoxy(84,9);colorCarta(4);printf("       TURNO DE: %s \n", jugadorAct->jugador);
    gotoxy(84,10);colorCarta(2);printf("==============================\n"); 
    tipoMapa *cartaJugada = turnojugador(jugadorAct->cartasJugador, CartaArribaMapa->carta, sumaDeCartas, &color); //aspecto: se muestran las cartas del jugador y la cartaArriba

    //Retornará la carta jugada, en caso de que el jugador no tenga una carta para jugar o
    //salte su turno, se retornará NULL.
    
    if(cartaJugada == NULL && sumaDeCartas == 0){
      pushFront(jugadorAct->cartasJugador, repartir(mapa, vectorClaves));
    }

    if(cartaJugada == NULL && sumaDeCartas > 0){
        while(sumaDeCartas != 0){
          pushFront(jugadorAct->cartasJugador, repartir(mapa, vectorClaves));
          sumaDeCartas--;
        }
    }

    if(cartaJugada != NULL){

      if(cartaJugada->carta.clave == 999){
        exportarDatos(listaJugadores, mapa, contJugadores, vectorClaves, direccion, sumaDeCartas, CartaArribaMapa, CartaAbajo,  jugadorAct);
        return;
      }
      
      if(cartaJugada->carta.codigo==12){
        sumaDeCartas=sumaDeCartas+2;
      }
      if(cartaJugada->carta.codigo==13){
        sumaDeCartas=sumaDeCartas+4;
      }
      if(cartaJugada->carta.codigo!=13 && cartaJugada->carta.codigo!=14){
        color=cartaJugada->carta.color;  
      }
      
      CartaAbajo = CartaArribaMapa;
      CartaArribaMapa = cartaJugada;

      tipoMapa* cartaNode = firstList(jugadorAct->cartasJugador);
      while (cartaNode != cartaJugada) {
          cartaNode = nextList(jugadorAct->cartasJugador);
      }
      popCurrent(jugadorAct->cartasJugador);

      if(firstList(jugadorAct->cartasJugador) == NULL) {
        theGameEnd(jugadorAct->jugador);
      return;
      }
      
      if(cartaJugada->carta.codigo==11){
        if(direccion==0) direccion=1;
        else{
          direccion=0;
        }
        if(*contJugadores == 2){
          if(direccion==0){
            jugadorAct = nextList(listaJugadores);
            if(jugadorAct == NULL){
              jugadorAct = firstList(listaJugadores);
            }
          }
          else{
            jugadorAct = prevList(listaJugadores);
            if(jugadorAct == NULL){
              jugadorAct = lastList(listaJugadores);
            }
          }
        }
      }
      
      if(cartaJugada->carta.codigo==10){
        if(direccion==0){
          jugadorAct = nextList(listaJugadores);
          if(jugadorAct == NULL){
            jugadorAct = firstList(listaJugadores);
          }
        }
        else{
          jugadorAct = prevList(listaJugadores);
          if(jugadorAct == NULL){
            jugadorAct = lastList(listaJugadores);
          }
        }
      }      
      CartaAbajo->cont++;
    }
    
    if(direccion==0){
      jugadorAct = nextList(listaJugadores);
      if(jugadorAct == NULL){
        jugadorAct = firstList(listaJugadores);
      }
    }
    else{
      jugadorAct = prevList(listaJugadores);
      if(jugadorAct == NULL){
        jugadorAct = lastList(listaJugadores);
      }
    }  
  }
}

void theGameBegins(List* listaJugadores, Map* mapa, int *contJugadores, int *vectorClaves) {
  //mostrarMapa(mapa);
  crearBaraja(listaJugadores,mapa, contJugadores, vectorClaves);
  theGame(listaJugadores,mapa, contJugadores, vectorClaves,false);
  
  return;
}

void IniciarPartida(List *listaJugadores, Map *mapa, int *contJugadores, int *vectorClaves) {
  int opcion = 1;
  system("cls");
  while (opcion != 0) {
    system("cls");
    printf("\033[?25l");
    gotoxy(80, 10);
    colorCarta(4);printf("Ingrese una cantidad de jugadores entre 2 y 4 \n");
    gotoxy(80, 11);
    colorCarta(3);printf("2 jugadores\n");
    gotoxy(80, 12);
    colorCarta(2);printf("3 jugadores\n");    
    gotoxy(80, 13);
    colorCarta(1);printf("4 jugadores\n\n");

    int flecha = 1;
    int tecla;
    while (true) {
      gotoxy(79, flecha + 10);
      printf(">");
      tecla = getch();
      gotoxy(79, flecha + 10);
      printf(" ");

      if (tecla == 32) {
        break;  // Presionar Enter para seleccionar la opción
      } else if (tecla == 224) {
        tecla = getch();  // Leer la tecla de flecha
        if (tecla == 72) {
          // Flecha hacia arriba
          if (flecha > 1) {
            flecha--;
          }
        } else if (tecla == 80) {
          // Flecha hacia abajo
          if (flecha < 3) {
            flecha++;
          }
        }
      }
    }

    system("cls");  // Limpiar la pantalla

    switch (flecha) {
      case 1:
        *contJugadores = 2;
        break;
      case 2:
        *contJugadores = 3;
        break;
      case 3:
        *contJugadores = 4;
        break;
    }

    if (*contJugadores >= 2 && *contJugadores <= 4) {
      theGameBegins(listaJugadores, mapa, contJugadores, vectorClaves);
      return;
    }
    
    gotoxy(90,27);printf("\nPresione una tecla para continuar...");
    if(kbhit){
      tecla=getch();
    }
  }
}

void menu(List * listaJugadores, Map* mapa, int *contJugadores,int*vectorClaves) {
  int opcion = 1;
  while (opcion != 0) {
    system("cls");  // Limpiar la pantalla
    
    gotoxy(55, 10);
    printf(" .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.\n");
    gotoxy(55, 11);
    printf("| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n");
    gotoxy(55, 12);
    printf("| | _____  _____ | || | ____  _____  | || |     ____     | || | ____  _____  | || |      _       | || |  _________   | |\n");
    gotoxy(55, 13);
    printf("| ||_   _||_   _|| || ||_   \\|_   _| | || |   .'    `.   | || ||_   \\|_   _| | || |     | |      | || | |  _   _  |  | |\n");
    gotoxy(55, 14);
    printf("| |  | |    | |  | || |  |   \\ | |   | || |  /  .--.  \\  | || |  |   \\ | |   | || |     |_|      | || | |_/ | | \\_|  | |\n");
    gotoxy(55, 15);
    printf("| |  | '    ' |  | || |  | |\\ \\| |   | || |  | |    | |  | || |  | |\\ \\| |   | || |              | || |     | |      | |\n");
    gotoxy(55, 16);
    printf("| |  |  `--'  |  | || | _| |_\\   |_  | || |  \\  `--'  /  | || | _| |_\\   |_  | || |              | || |    _| |_     | |\n");
    gotoxy(55, 17);
    printf("| |  '\\______/   | || ||_____|\\____| | || |   `.____.'   | || ||_____|\\____| | || |              | || |   |_____|    | |\n");
    gotoxy(55, 18);
    printf("| |              | || |              | || |              | || |              | || |              | || |              | |\n");
    gotoxy(55, 19);
    printf("| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n");
    gotoxy(55, 20);
    printf(" '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'\n");
    
    gotoxy(86, 25);
    printf("\n");
    gotoxy(105, 26);
    printf("\033[1;33mINICIAR PARTIDA\033[0m\n");
    gotoxy(105, 27);
    printf("\033[1;33mCARGAR PARTIDA\033[0m\n");
    gotoxy(105, 28);
    printf("\033[1;33mSALIR DEL JUEGO\033[0m\n");



    int flecha = 1;
    int tecla;
    while (true) {
      printf("\033[?25l");
      gotoxy(104, flecha + 25);
      printf(">");
      tecla = getch();
      gotoxy(104, flecha + 25);
      printf(" ");

      if (tecla == 32) {
        break;  // Presionar Enter para seleccionar la opción
      } else if (tecla == 224) {
        tecla = getch();  // Leer la tecla de flecha
        if (tecla == 72) {
          // Flecha hacia arriba
          if (flecha > 1) {
            flecha--;
          }
        } else if (tecla == 80) {
          // Flecha hacia abajo
          if (flecha < 3) {
            flecha++;
          }
        }
      }
    }

    system("cls");  // Limpiar la pantalla

    switch (flecha) {
      case 1:
        IniciarPartida(listaJugadores,mapa, contJugadores,vectorClaves);
        gotoxy(90,27);printf("\nPresione una tecla para continuar...");
        if(kbhit){
        tecla=getch();
        }
        return;
      case 2:{
        bool cargar = true;
        theGame(listaJugadores, mapa, contJugadores, vectorClaves, cargar);      
        |gotoxy(90,27);printf("\nPresione una tecla para continuar...");
        if(kbhit){
        tecla=getch();
    }
      }
      case 3:
        printf("         by GG WP//");
        return;  
    }
    
    gotoxy(90,27);printf("\nPresione una tecla para continuar...");
    if(kbhit){
      tecla=getch();
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
  HWND hwnd = GetConsoleWindow(); // Obtener el identificador de la ventana de la consola
  ShowWindow(hwnd, SW_MAXIMIZE);
  
  menu(listaJugadores, mapa, &contJugadores,vectorClaves);
  free(vectorClaves);
  free(listaJugadores);
  free(mapa);
  return 0;
} 