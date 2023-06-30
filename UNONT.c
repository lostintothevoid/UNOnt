#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define ID_CLICK1 10000
#define ID_BTOMOUT 10002


LRESULT CALLBACK ProcediementoVentana(HWND hwnd,UINT msg, WPARAM wParam,LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstanciaActual,HINSTANCE hInstanciaPrevia,LPSTR lpCmdLinea,int nCmdShow){

    HWND ventana; //manejador de ventana
    MSG mensaje; //intermediario para comunicar los mensajes de la aplicacion    WNDCLASSEX clase;
    WNDCLASSEX clase; //estructura que contienen un conjunto de elementos que caracterizan a una ventana
    clase.cbSize = sizeof(WNDCLASSEX); //tama�o de la clase es igual al tama�o de la estructura    clase.cbClsExtra = 0;
    clase.cbClsExtra = 0; //El n�mero de bytes adicionales para asignar (El sistema inicializa los bytes a cero.)
    clase.style = CS_HREDRAW | CS_VREDRAW;  //se puede dibujar horizontalmente y verticalmente
    clase.lpfnWndProc = ProcediementoVentana;
    /* lpfnWndProc:
    Es la responsable de todo lo relativo al aspecto y al comportamiento de una ventana.
    Puntero a una funci�n de este tipo, esa funci�n es la que se encargar� de procesar
    todos los mensajes para esa clase de ventana. Cuando registremos nuestra clase de
    ventana, tendremos que asignar a ese miembro el puntero a nuestro procedimiento de ventana.*/
    clase.hInstance = hInstanciaActual;
    clase.hIcon = LoadIcon(NULL,0);//Identificador de icono
    clase.hIconSm =LoadIcon(NULL,IDI_WINLOGO);//Elegimos que icono queremos
    clase.hCursor = LoadCursor(NULL,IDC_CROSS);//Identificador de cursor, elegimos la forma en que se mostrar�
    clase.lpszClassName = "IdentificadorVentana"; //este es el identificador para pasarlo a CreateWindowsEx();
    clase.hbrBackground =CreateSolidBrush( RGB(0,0,0)); //color de la ventana
    if(!RegisterClassEx(&clase)){ //si no esta registrada la clase
        MessageBox( NULL,"No se pudo ejecutar la aplicacion","Error",MB_ICONERROR);
        return EXIT_FAILURE;
    }

    //WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU (para que no se maximice)
    ventana = CreateWindowEx(0,"IdentificadorVentana","Unon't.exe",WS_OVERLAPPEDWINDOW| WS_MINIMIZEBOX |WS_SYSMENU,400,80,560,630,HWND_DESKTOP,NULL,hInstanciaActual,NULL);
    // controladores de ventana
    CreateWindowEx(0,"BUTTON","Iniciar partida", WS_VISIBLE |WS_CHILD| SS_NOTIFY , 250,400,100,20,ventana,(HMENU)ID_CLICK1 ,hInstanciaActual,NULL);
    CreateWindowEx(0,"BUTTON","Salir del Unon't",BS_CENTER|WS_VISIBLE|WS_CHILD,400,550,140,30,ventana,(HMENU)ID_BTOMOUT,NULL,NULL);


    ShowWindow(ventana,nCmdShow); //mostramos la ventana
    UpdateWindow(ventana);//actualizamos la ventana en caso hagamos algunos eventos

    //creamos el bucle para saber si nuestro mensaje esta interactuando con el usuario, si ser� cero significa que acabo el programa
    while(GetMessage(&mensaje,NULL,0,0)>0){
            TranslateMessage(&mensaje);
            DispatchMessage(&mensaje);
    }

}
/*LRESULT : utiliza para representar el valor
 de retorno de los procedimientos de ventana.
 Suele ser un LARGO (de ah� la L ).
 Par�metros del procedimiento de ventana :
        hwnd es el manipulador de la ventana a la que est� destinado el mensaje.
        msg es el c�digo del mensaje.
        wParam es el par�metro de tipo palabra asociado al mensaje.
        lParam es el par�metro de tipo doble palabra asociado al mensaje.
 */
LRESULT CALLBACK ProcediementoVentana(HWND hwnd,UINT msg, WPARAM wParam,LPARAM lParam){
    HWND himg;
    HBITMAP cargar_img;
    cargar_img= (HBITMAP)LoadImageW(NULL,L"Unon't_Logo.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    static HINSTANCE Instancia; //no se destruye por ser estatica

    switch(msg){
        case WM_CREATE:{
            Instancia =((LPCREATESTRUCT)lParam)->hInstance; //cassting para convertir en una structura que lleva almacenada la info de la ventana.

            himg = CreateWindowW(L"Static",NULL,WS_VISIBLE | WS_CHILD | SS_BITMAP, 60,80,0,0,hwnd,NULL,Instancia,NULL);
            SendMessageW(himg,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM) cargar_img);

            break;
        }
        case WM_COMMAND:{
            switch (LOWORD(wParam))
            {
                case ID_BTOMOUT:{
                    if(MessageBox(hwnd,"¿Desea salir del juego?","Salir.",MB_OKCANCEL|MB_ICONQUESTION)==IDOK){
                        SendMessage(hwnd,WM_DESTROY,0,0);
                    }
                    break;
                }

                case ID_CLICK1:{
                    system("UNONTGAME");
                    break;
                }
            
                default:{
                    break;
                }
                    
            }
            break;
        }

        case WM_DESTROY:{
            PostQuitMessage(0); //este cero pasar� al bucle while para que acabe el programa
            break;
        }

        case WM_CTLCOLORSTATIC:{
            HDC hdcStatic = (HDC) wParam;
            SetTextColor(hdcStatic, RGB(233,250,1));
            SetBkColor(hdcStatic,RGB(0,0,0));
            return (INT_PTR)CreateSolidBrush(RGB(0,0,0));
            break;
        }

        default:{
            return DefWindowProc(hwnd, msg,wParam,lParam);
        }

    }
    return 0;
}
