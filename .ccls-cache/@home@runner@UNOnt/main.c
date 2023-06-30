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

/*Estructura del tipoCarta
- Int Numero //
- int codigo: Cada carta tendrá un código específico asociado. En caso de que sea
una carta de tipo numérica, será del 0 al 9, el cambio color valdrá 10, +4 valdrá 11,
bloqueo valdrá 12, reversa 13 y +2 14.
- Int color: Se utilizara un numero para identificar el color que le corresponde a la carta
100 rojo, 200 azul, 300 verde, 400 amarillo y 500 especial.
Estructura del tipoMapa
- tipoCarta carta
- Int Contador: Se contendrá un contador para ver cuantas cartas hay de esta misma
en el mapa.
*/

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

void theGameEnd(char *nombreJugador)
{
  printf("GANADOR: %s\n\n", nombreJugador);
  return;
}

tipoMapa *puntocentral(List *barajajugador){
  int contcentro = 0;
  tipoMapa *aux = firstList(barajajugador);

  while(aux!=NULL){
    aux = nextList(barajajugador);
    contcentro++;
  }
  
  int centro = trunc(contcentro/2);
  
  aux = firstList(barajajugador);
  while(centro!=0){
    aux=nextList(barajajugador);
    centro--;
  }
  return aux;
}

tipoMapa *turnojugador(List *barajajugador, tipoCarta CartaArriba, int sumaDeCartas, int *color) {

  tipoMapa *centro = puntocentral(barajajugador);
  tipoMapa *next = nextList(barajajugador);
  centro = puntocentral(barajajugador);
  tipoMapa *prev = prevList(barajajugador); 
  tipoMapa *aux;

  //Se deja la baraja centrada
  centro = puntocentral(barajajugador);
  
  char uno = 0;
  int tecla=0;
  gotoxy(74,13);colorCarta(4);printf  ("Presiona la tecla izquierda o derecha para ver tus cartas\n");
  
  while(tecla != 75 && tecla != 77)
  {
    kbhit();
    tecla = getch();
    gotoxy(84,13);colorCarta(0);printf("                                                         \n");
  }



  while(true){
    //El pato ve los prints
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
          //Verificar si la carta es apta para ser tirada, en caso de no coincidir se devolvería a la seleccion de cartas
          //Comprobar si puede tirar la carta
        
          //Comprobar si tiro un mas algo teniendo una suma pendiente
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

          //Comprobar si es un +4 o un cambio color
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

          //Si la carta no es apta, se muestra por pantalla que tire otra carta
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

        //Significa que sacó cartas o que le tiraron un +2 o +4 y no tenía nada para devolver
        case 122:{
          return NULL;
        }

        //Significa que quiere guardar su partida, por lo que se retorna una carta con una clave especial que se revisará en la función theGame
        case 120:{
          tipoMapa* cartaBool = malloc(sizeof(tipoMapa));
          cartaBool->carta.clave=999;
          return cartaBool;
        }
      }
    }
    //A estas alturas ya tenemos la carta que jugó el jugador
  }
  
}

void exportarDatos(List *listaJugadores, Map *mapa, int *contJugadores, int *vectorClaves, int direccion, int sumaDeCartas, tipoMapa *CartaArribaMapa, tipoMapa *CartaAbajo, tipoJugador *jugadorAct){
  //Se crea una string estática para dar un nombre al archivo qsue exportará a los jugadores
  
  char archivo[100];
  printf("Escribe el nombre con el que guardarás tu partida:\n");
  getchar();
  //scanf("%s",archivo);
  scanf("%[^\n]s",archivo);
  getchar();
  FILE *fp = fopen(archivo, "w");


  fprintf(fp, "Datos de partida: contJugadores, Direccion, sumDeCartas, CartaArribaMapa.numero, CartaArribaMapa.codigo, CartaArribaMapa.color, CartaArribaMapa.clave, CartaArribaMapa.cont, CartaAbajo.numero, CartaAbajo.codigo, CartaAbajo.color, CartaAbajo.clave, CartaAbajo.cont, jugadorAct.id\n");

  fprintf(fp, "%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i\n", *contJugadores, direccion, sumaDeCartas, CartaArribaMapa->carta.numero, CartaArribaMapa->carta.codigo, CartaArribaMapa->carta.color, CartaArribaMapa->carta.clave, CartaArribaMapa->cont, CartaAbajo->carta.numero, CartaAbajo->carta.codigo, CartaAbajo->carta.color, CartaAbajo->carta.clave, CartaAbajo->cont, jugadorAct->id);
  
  
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
  fprintf(fp, "Map: contador,numero, codigo, color, clave\n");
  
  void* elemento = firstMap(mapa);

  while (elemento != NULL) {
      tipoMapa* cartaMapa = (tipoMapa*)elemento;
      
       fprintf(fp, "%i,%i,%i,%i,%i,", cartaMapa->cont, cartaMapa->carta.numero, cartaMapa->carta.codigo, cartaMapa->carta.color, cartaMapa->carta.clave);
       fprintf(fp, "\n");
    
      elemento = nextMap(mapa);
  }
  
  
  //De no haber errores, se muestra el siguiente mensaje por pantalla 
  printf("===============================================================\n");
  printf("                  Partida guardada con éxito\n");
  printf("===============================================================\n");
  fclose(fp);
  
}

bool cargarDatos(List *listaJugadores, Map *mapa, int *contJugadores, int *vectorClaves, int *direccion, int *sumaDeCartas, tipoMapa *CartaArribaMapa, tipoMapa *CartaAbajo, int *turnoDe){
  char archivo[100];
  //Se le pide al usuario que ingrese el nombre del archivo de donde desea importar las tareas
  printf("Ingresa el nombre de la partida que quieras cargar:\n");
  //fflush(stdin);
  scanf("%[^\n]s",archivo);
  getchar();
  
  //Se abre el archivo
  FILE *fp=fopen(archivo, "r");
  if(fp==NULL){
    printf("\n===============================================================\n");
    printf("                   Error al importar archivo...\n");
    printf("     Asegúrese de importar al programa con el mismo nombre\n");
    printf("===============================================================\n\n");
    return false;
  }
  char linea[300];
  //Se obtiene la primera línea (Que no nos sirve porque son las descripciones de las columnas)
  fgets(linea,301,fp);

  int j=0;
  //A partir de aqui las lineas son importante porque tienen la información que necesitamos
  while(fgets(linea,301,fp)!=NULL){
    //Es una tarea por linea, por lo que aquí se crea
    tipoJugador *player;
    player=malloc(sizeof(tipoJugador));
    //Se empieza a obtener cada parámetro a través de strtok, asi guardandose en sus variables correspondientes
    linea[strlen(linea)-1] = 0;
    
    char *ch = strtok(linea, ",");
    
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
  
  
  printf("\n===============================================================\n");
  printf("        La importación de tareas fue hecha con éxito\n");
  printf("===============================================================\n\n");
  fclose(fp);

  return true;
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

    //Se comienza el ciclo del juego
  while(true){//(true), en efecto (true)
    system("cls");
    printf("\033[?25l");
    //mostrarListasJugadores(listaJugadores);
    gotoxy(84,8);colorCarta(2);printf("==============================\n");
    gotoxy(84,9);colorCarta(4);printf("       TURNO DE: %s \n", jugadorAct->jugador);
    gotoxy(84,10);colorCarta(2);printf("==============================\n"); 
    //Se obtiene la carta que desea jugar el jugador actual al llamar a la función turnojugador
    tipoMapa *cartaJugada = turnojugador(jugadorAct->cartasJugador, CartaArribaMapa->carta, sumaDeCartas, &color);
    //En caso de que el jugador no tenga una carta para jugar o salte su turno, se retornará NULL.

    //Si la carta es nula y la suma de cartas es 0 entonces el jugador roba solo una carta
    if(cartaJugada == NULL && sumaDeCartas == 0){
      pushFront(jugadorAct->cartasJugador, repartir(mapa, vectorClaves));
    }

    //Si la carta es nula y la suma de cartas es mayor a 0 el jugador deberá robar la cantidad de cartas indicada por la suma de cartas
    if(cartaJugada == NULL && sumaDeCartas > 0){
        while(sumaDeCartas != 0){
          pushFront(jugadorAct->cartasJugador, repartir(mapa, vectorClaves));
          sumaDeCartas--;
        }
    }

    //Si el jugador si tiró una carta, entra al siguiente if para confirmar el efecto de su carta
    if(cartaJugada != NULL){

      //En este caso quiere decir que quiere guardar la partida, entonces llama a la función exportarDatos
      if(cartaJugada->carta.clave == 999){
        exportarDatos(listaJugadores, mapa, contJugadores, vectorClaves, direccion, sumaDeCartas, CartaArribaMapa, CartaAbajo,  jugadorAct);
        return;
      }

      //En este caso quiere decir que tiró un +2, por lo que la sumaDeCartas se le tiene que sumar 2.
      if(cartaJugada->carta.codigo==12){
        sumaDeCartas=sumaDeCartas+2;
      }
      //En este caso quiere decir que tiró un +4, por lo que la sumaDeCartas se le tiene que sumar 4.
      if(cartaJugada->carta.codigo==13){
        sumaDeCartas=sumaDeCartas+4;
      }

      //En este caso en el que la carta no sea ni un cambio color o un +4, el color se actualizará.
      //En el caso contrario el color se actualiza en la función turnoJugador().
      if(cartaJugada->carta.codigo!=13 && cartaJugada->carta.codigo!=14){
        color=cartaJugada->carta.color;  
      }

      //Ahora la cartaAbajo será la actual cartaArriba y la cartaArriba ahora será la carta que se jugó
      //Entonces el siguiente jugador tendrá que jugar con las condiciones de la cartaJugada, que ahora es cartaArriba
      CartaAbajo = CartaArribaMapa;
      CartaArribaMapa = cartaJugada;

      //Procedemos a buscar la cartaJugada para luego eliminarla de la baraja del jugador
      tipoMapa* cartaNode = firstList(jugadorAct->cartasJugador);
      while (cartaNode != cartaJugada) {
          cartaNode = nextList(jugadorAct->cartasJugador);
      }
      popCurrent(jugadorAct->cartasJugador);

      /*Tras eliminar la carta de la baraja del jugador se comprueba si se qeudó sin cartas, en caso de 
      que no posea mas se llamará a la función theGameEnd para terminar el juego*/
      if(firstList(jugadorAct->cartasJugador) == NULL) {
        theGameEnd(jugadorAct->jugador);
      return;
      }

      //Si la carta es un cambio de dirección, cambiará de valor 0 a 1 o viceversa.
      //Además implementamos para que cuando se juege de a 2, cuando un jugador tire un cambio de dirección,
      //le tocará nuevamente su turno
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

      //Si la carta es un bloqueo se avanzará al siguiente
      if(cartaJugada->carta.codigo==10){
        //si la dirección es hacia la derecha se avanza un jugador en la lista
        if(direccion==0){
          jugadorAct = nextList(listaJugadores);
          //Si se llegó al final de la lista de jugadores se devolverá al inicio
          if(jugadorAct == NULL){
            jugadorAct = firstList(listaJugadores);
          }
        }
        else{
          //Si la dirección es hacia la izquierda se retrocede un jugador 
          jugadorAct = prevList(listaJugadores);
          /*Si estamos en el primer jugador y por lo tanto el anterior es nulo 
          entonces se va al último de la lista*/
          if(jugadorAct == NULL){
            jugadorAct = lastList(listaJugadores);
          }
        }
      }      
      CartaAbajo->cont++;
    }

    //Ahora dependiendo de la dirección, se asignará al siguiente jugador
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

void theGameBegins(List* listaJugadores, Map* mapa, int *contJugadores, int *vectorClaves){
  //mostrarMapa(mapa);
  crearBaraja(listaJugadores,mapa, contJugadores, vectorClaves);
  theGame(listaJugadores,mapa, contJugadores, vectorClaves,false);
  
  return;
}

//Función para seleccionar la cantidad de jugadores
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
        break;  // Presionar [space] para seleccionar la opción
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

    /*
    por medio de la funcnion getch se va dando un menu interactivo en el cual se va detectando si el usuario preciona una flecha hacia arriba o abajo para seleccionar su opcion
    */

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
        break;  // Presionar [space] para seleccionar la opción
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
        break;
      case 2:{
        bool cargar = true;
        theGame(listaJugadores, mapa, contJugadores, vectorClaves, cargar);      
        break;
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