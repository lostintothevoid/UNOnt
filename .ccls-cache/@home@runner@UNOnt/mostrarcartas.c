#include "mostrarcartas.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>

void mostrarMargen(int valor){
    if (valor==0) printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c ",201,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
    if (valor==1) printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c ",200,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
    if (valor>1) printf("                 ");
}

void colorCarta(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; // Color blanco por defecto

    switch (color) {
        case 0: // Blanco
            attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            break;
        case 1: // Rojo
            attributes = FOREGROUND_RED;
            break;
        case 2: // Azul
            attributes = FOREGROUND_BLUE;
            break;
        case 3: // Verde
            attributes = FOREGROUND_GREEN;
            break;
        case 4: // Amarillo
            attributes = FOREGROUND_RED | FOREGROUND_GREEN;
            break;
    }

    SetConsoleTextAttribute(hConsole, attributes);
}

void primeraLinea(int num){
    int b = (num / 100) % 10;  // Extraer centésima USAR ESTE NÚMERO PARA DAR COLOR
    int a = num % 100;         // Extraer decena y unidad
    switch (a)
    {
    case 0:
        printf("%c",186);colorCarta(b);printf("   %c%c%c%c%c%c%c   ",220,220,220,220,220,220,220);colorCarta(0);printf("%c ",186);
        break;
    case 1:
        printf("%c",186);colorCarta(b);printf("   %c%c%c%c%c     ",220,220,219,219,219);colorCarta(0);colorCarta(0);printf("%c ",186);
        break;
    case 2:
        printf("%c",186);colorCarta(b);printf("   %c%c%c%c%c%c%c   ",220,220,220,220,220,220,220);colorCarta(0);printf("%c ",186);
        break;
    case 3:
        printf("%c",186);colorCarta(b);printf("   %c%c%c%c%c%c%c   ",220,220,220,220,220,220,220);colorCarta(0);printf("%c ",186);
        break;
    case 4:
        printf("%c",186);colorCarta(b);printf("   %c%c   %c%c   ",220,220,220,220);colorCarta(0);colorCarta(0);printf("%c ",186);
        break;
    case 5:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",220,220,220,220,220,220,220,220,220);colorCarta(0);printf("%c ",186);
        break;
    case 6:
        printf("%c",186);colorCarta(b);printf("   %c%c%c%c%c%c%c   ",220,220,220,220,220,220,220);colorCarta(0);printf("%c ",186);
        break;
    case 7:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",220,220,220,220,220,220,220,220,220);colorCarta(0);printf("%c ",186);
        break;
    case 8:
        printf("%c",186);colorCarta(b);printf("   %c%c%c%c%c%c%c   ",220,220,220,220,220,220,220);colorCarta(0);printf("%c ",186);
        break;
    case 9:
        printf("%c",186);colorCarta(b);printf("   %c%c%c%c%c%c%c   ",220,220,220,220,220,220,220);colorCarta(0);printf("%c ",186);
        break;
    case 10:
        printf("%c",186);colorCarta(b);printf("   %c%c%c%c%c%c%c   ",220,220,220,220,220,220,220);colorCarta(0);printf("%c ",186);
        break;
    case 11:
        printf("%c",186);colorCarta(b);printf("  %c%c%c        ",220,220,220);colorCarta(0);printf("%c ",186);
        break;
    case 12:
        printf("%c",186);colorCarta(b);printf("    %c%c%c%c%c%c%c  ",220,220,220,220,220,220,220);colorCarta(0);printf("%c ",186);
        break;
    case 13:
        printf("%c",186);colorCarta(1);printf("      %c%c  %c%c ",220,220,220,220);colorCarta(0);printf("%c ",186);
        break;
    case 14:
        printf("%c",186);colorCarta(1);printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);colorCarta(2);printf("%c%c%c%c%c",219,219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    }
}

void segundaLinea(int num){
    int b = (num / 100) % 10;  // Extraer centésima USAR ESTE NÚMERO PARA DAR COLOR
    int a = num % 100;         // Extraer decena y unidad
    switch (a)
    {
    case 0:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",219,219,219,223,223,223,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 1:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c     ",223,223,223,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 2:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",219,219,219,223,223,223,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 3:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",219,219,219,223,223,223,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 4:
        printf("%c",186);colorCarta(b);printf("   %c%c   %c%c   ",219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 5:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",219,219,219,223,223,223,223,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 6:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",220,219,219,219,223,223,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 7:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",219,219,219,223,223,223,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 8:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",219,219,219,223,223,223,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 9:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",219,219,219,219,219,219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 10:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",219,219,219,223,223,219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 11:
        printf("%c",186);colorCarta(b);printf("%c%c%c%c%c  %c%c%c%c%c ",220,219,219,219,223,219,219,219,219,223);colorCarta(0);printf("%c ",186);
        break;
    case 12:
        printf("%c",186);colorCarta(b);printf("   %c%c%c%c%c%c%c%c%c ",219,219,219,223,223,223,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 13:
        printf("%c",186);colorCarta(1);printf("      %c%c  %c%c ",219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 14:
        printf("%c",186);colorCarta(1);printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);colorCarta(2);printf("%c%c%c%c%c",219,219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    }
}

void terceraLinea(int num){
    int b = (num / 100) % 10;  // Extraer centésima USAR ESTE NÚMERO PARA DAR COLOR
    int a = num % 100;         // Extraer decena y unidad
    switch (a)
    {
    case 0:
        printf("%c",186);colorCarta(b);printf("  %c%c     %c%c  ",219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 1:
        printf("%c",186);colorCarta(b);printf("     %c%c%c     ",219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 2:
        printf("%c",186);colorCarta(b);printf("       %c%c%c%c  ",220,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 3:
        printf("%c",186);colorCarta(b);printf("         %c%c  ",219,219);colorCarta(0);printf("%c ",186);
        break;
    case 4:
        printf("%c",186);colorCarta(b);printf("  %c%c%c   %c%c   ",220,219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 5:
        printf("%c",186);colorCarta(b);printf("  %c%c%c        ",219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 6:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c       ",219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 7:
        printf("%c",186);colorCarta(b);printf("       %c%c%c%c  ",219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 8:
        printf("%c",186);colorCarta(b);printf("  %c%c     %c%c  ",219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 9:
        printf("%c",186);colorCarta(b);printf("  %c%c%c   %c%c%c  ",219,219,219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 10:
        printf("%c",186);colorCarta(b);printf("  %c%c  %c%c%c%c%c  ",219,219,220,219,223,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 11:
        printf("%c",186);colorCarta(b);printf("%c%c%c    %c%c%c%c%c%c",219,219,223,219,223,223,219,219,220);colorCarta(0);printf("%c ",186);
        break;
    case 12:
        printf("%c",186);colorCarta(b);printf("  %c     %c%c%c%c ",220,220,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 13:
        printf("%c  %c",186,220);colorCarta(2);printf("   %c%c  %c%c ",219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 14:
        printf("%c",186);colorCarta(1);printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);colorCarta(2);printf("%c%c%c%c%c",219,219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    }
}

void cuartaLinea(int num){
    int b = (num / 100) % 10;  // Extraer centésima USAR ESTE NÚMERO PARA DAR COLOR
    int a = num % 100;         // Extraer decena y unidad
    switch (a)
    {
    case 0:
        printf("%c",186);colorCarta(b);printf("  %c%c     %c%c  ",219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 1:
        printf("%c",186);colorCarta(b);printf("     %c%c%c     ",219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 2:
        printf("%c",186);colorCarta(b);printf("      %c%c%c%c   ",220,219,219,223);colorCarta(0);printf("%c ",186);
        break;
    case 3:
        printf("%c",186);colorCarta(b);printf("      %c%c%c%c%c  ",220,220,219,219,223);colorCarta(0);printf("%c ",186);
        break;
    case 4:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c   ",219,219,219,220,220,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 5:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",223,219,219,219,219,219,219,219,220);colorCarta(0);printf("%c ",186);
        break;
    case 6:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",219,219,219,219,219,219,219,219,220);colorCarta(0);printf("%c ",186);
        break;
    case 7:
        printf("%c",186);colorCarta(b);printf("      %c%c%c%c   ",219,219,219,223);colorCarta(0);printf("%c ",186);
        break;
    case 8:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",223,219,219,220,220,220,219,219,223);colorCarta(0);printf("%c ",186);
        break;
    case 9:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",219,219,219,220,220,220,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 10:
        printf("%c",186);colorCarta(b);printf("  %c%c  %c%c %c%c  ",219,219,219,223,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 11:
        printf("%c",186);colorCarta(b);printf("%c%c        %c%c%c",219,219,223,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 12:
        printf("%c",186);colorCarta(b);printf("%c%c%c%c%c  %c%c%c%c  ",254,254,219,254,254,220,219,219,223);colorCarta(0);printf("%c ",186);
        break;
    case 13:
        printf("%c%c%c%c%c%c",186,254,254,219,254,254);colorCarta(2);printf(" %c%c%c%c%c%c ",219,219,220,220,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 14:
        printf("%c",186);colorCarta(4);printf("%c%c%c%c%c   ",219,219,219,219,219);colorCarta(2);printf("%c%c%c%c%c",219,219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    }
}

void quintaLinea(int num){
    int b = (num / 100) % 10;  // Extraer centésima USAR ESTE NÚMERO PARA DAR COLOR
    int a = num % 100;         // Extraer decena y unidad
    switch (a)
    {
    case 0:
        printf("%c",186);colorCarta(b);printf("  %c%c     %c%c  ",219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 1:
        printf("%c",186);colorCarta(b);printf("     %c%c%c     ",219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 2:
        printf("%c",186);colorCarta(b);printf("    %c%c%c%c     ",220,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 3:
        printf("%c",186);colorCarta(b);printf("      %c%c%c%c%c  ",223,223,219,219,220);colorCarta(0);printf("%c ",186);
        break;
    case 4:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c   ",223,223,223,223,223,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 5:
        printf("%c",186);colorCarta(b);printf("       %c%c%c%c  ",223,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 6:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",219,219,219,223,223,223,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 7:
        printf("%c",186);colorCarta(b);printf("     %c%c%c%c    ",220,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 8:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",220,219,219,223,223,223,219,219,220);colorCarta(0);printf("%c ",186);
        break;
    case 9:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",223,219,219,219,219,219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 10:
        printf("%c",186);colorCarta(b);printf("  %c%c %c%c  %c%c  ",219,219,220,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 11:
        printf("%c",186);colorCarta(b);printf("%c%c%c        %c%c",219,219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 12:
        printf("%c",186);colorCarta(b);printf("  %c  %c%c%c%c    ",223,220,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 13:
        printf("%c  %c",186,223);colorCarta(3);printf("   %c%c%c%c%c%c ",223,223,223,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 14:
        printf("%c",186);colorCarta(4);printf("%c%c%c%c%c   ",219,219,219,219,219);colorCarta(2);printf("%c%c%c%c%c",219,219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    }
}

void sextaLinea(int num){
    int b = (num / 100) % 10;  // Extraer centésima USAR ESTE NÚMERO PARA DAR COLOR
    int a = num % 100;         // Extraer decena y unidad
    switch (a)
    {
    case 0:
        printf("%c",186);colorCarta(b);printf("  %c%c     %c%c  ",219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 1:
        printf("%c",186);colorCarta(b);printf("     %c%c%c     ",219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 2:
        printf("%c",186);colorCarta(b);printf("   %c%c%c%c      ",219,219,219,223);colorCarta(0);printf("%c ",186);
        break;
    case 3:
        printf("%c",186);colorCarta(b);printf("         %c%c  ",219,219);colorCarta(0);printf("%c ",186);
        break;
    case 4:
        printf("%c",186);colorCarta(b);printf("       %c%c%c   ",219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 5:
        printf("%c",186);colorCarta(b);printf("        %c%c%c  ",219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 6:
        printf("%c",186);colorCarta(b);printf("  %c%c%c   %c%c%c  ",219,219,219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 7:
        printf("%c",186);colorCarta(b);printf("     %c%c%c%c    ",219,219,219,223);colorCarta(0);printf("%c ",186);
        break;
    case 8:
        printf("%c",186);colorCarta(b);printf("  %c%c     %c%c  ",219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 9:
        printf("%c",186);colorCarta(b);printf("       %c%c%c%c  ",219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 10:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c  %c%c  ",219,219,220,219,223,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 11:
        printf("%c",186);colorCarta(b);printf(" %c%c%c%c%c    %c%c%c",223,219,219,220,219,220,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 12:
        printf("%c",186);colorCarta(b);printf("    %c%c%c%c     ",219,219,219,223);colorCarta(0);printf("%c ",186);
        break;
    case 13:
        printf("%c",186);colorCarta(3);printf("         %c%c%c ",219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 14:
        printf("%c",186);colorCarta(4);printf("%c%c%c%c%c",219,219,219,219,219);colorCarta(3);printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    }
}

void septimaLinea(int num){
    int b = (num / 100) % 10;  // Extraer centésima USAR ESTE NÚMERO PARA DAR COLOR
    int a = num % 100;         // Extraer decena y unidad
    switch (a)
    {
    case 0:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",219,219,219,220,220,220,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 1:
        printf("%c",186);colorCarta(b);printf("     %c%c%c     ",219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 2:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",219,219,219,220,220,220,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 3:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",219,219,219,220,220,220,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 4:
        printf("%c",186);colorCarta(b);printf("       %c%c%c   ",219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 5:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",219,219,219,220,220,219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 6:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",219,219,219,219,219,219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 7:
        printf("%c",186);colorCarta(b);printf("    %c%c%c%c     ",219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 8:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",219,219,219,220,220,220,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 9:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",219,219,219,220,220,219,219,219,223);colorCarta(0);printf("%c ",186);
        break;
    case 10:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",219,219,219,219,220,220,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 11:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c  %c%c%c%c%c",220,219,219,219,220,219,219,219,223);colorCarta(0);printf("%c ",186);
        break;
    case 12:
        printf("%c",186);colorCarta(b);printf("   %c%c%c%c%c%c%c%c%c ",219,219,219,220,220,220,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 13:
        printf("%c",186);colorCarta(4);printf("         %c%c%c ",219,219,219);colorCarta(0);printf("%c ",186);
        break;
    case 14:
        printf("%c",186);colorCarta(4);printf("%c%c%c%c%c",219,219,219,219,219);colorCarta(3);printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    }
}

void octavaLinea(int num){
    int b = (num / 100) % 10;  // Extraer centésima USAR ESTE NÚMERO PARA DAR COLOR
    int a = num % 100;         // Extraer decena y unidad
    switch (a)
    {
    case 0:
        printf("%c",186);colorCarta(b);printf("   %c%c%c%c%c%c%c   ",223,223,223,223,223,223,223);colorCarta(0);printf("%c ",186);
        break;
    case 1:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",223,223,223,223,223,223,223,223,223);colorCarta(0);printf("%c ",186);
        break;
    case 2:
        printf("%c",186);colorCarta(b);printf("  %c%c%c%c%c%c%c%c%c  ",223,223,223,223,223,223,223,223,223);colorCarta(0);printf("%c ",186);
        break;
    case 3:
        printf("%c",186);colorCarta(b);printf("   %c%c%c%c%c%c%c   ",223,223,223,223,223,223,223);colorCarta(0);printf("%c ",186);
        break;
    case 4:
        printf("%c",186);colorCarta(b);printf("     %c%c%c%c%c%c  ",223,223,223,223,223,223);colorCarta(0);printf("%c ",186);
        break;
    case 5:
        printf("%c",186);colorCarta(b);printf("   %c%c%c%c%c%c%c   ",223,223,223,223,223,223,223);colorCarta(0);printf("%c ",186);
        break;
    case 6:
        printf("%c",186);colorCarta(b);printf("   %c%c%c%c%c%c%c   ",223,223,223,223,223,223,223);colorCarta(0);printf("%c ",186);
        break;
    case 7:
        printf("%c",186);colorCarta(b);printf("    %c%c%c%c     ",223,223,223,223);colorCarta(0);printf("%c ",186);
        break;
    case 8:
        printf("%c",186);colorCarta(b);printf("   %c%c%c%c%c%c%c   ",223,223,223,223,223,223,223);colorCarta(0);printf("%c ",186);
        break;
    case 9:
        printf("%c",186);colorCarta(b);printf("   %c%c%c%c%c%c%c   ",223,223,223,223,223,223,223);colorCarta(0);printf("%c ",186);
        break;
    case 10:
        printf("%c",186);colorCarta(b);printf("   %c%c%c%c%c%c%c   ",223,223,223,223,223,223,223);colorCarta(0);printf("%c ",186);
        break;
    case 11:
        printf("%c",186);colorCarta(b);printf("        %c%c%c  ",223,223,223);colorCarta(0);printf("%c ",186);
        break;
    case 12:
        printf("%c",186);colorCarta(b);printf("   %c%c%c%c%c%c%c%c%c ",223,223,223,223,223,223,223,223,223);colorCarta(0);printf("%c ",186);
        break;
    case 13:
        printf("%c",186);colorCarta(4);printf("       %c%c%c%c%c%c",223,223,223,223,223,223);colorCarta(0);printf("%c ",186);
        break;
    case 14:
        printf("%c",186);colorCarta(4);printf("%c%c%c%c%c",219,219,219,219,219);colorCarta(3);printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);colorCarta(0);printf("%c ",186);
        break;
    }
}

