#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

/**
PMI 3 - GRUPO 3
INTEGRANTES:
 Rio, Sofia
 Montenegro, Juan Bautista

Conclusión: En general, el RS fue el que menores costos maximos y medios obtuvo para las
evocaciones exitosas como las no exitosas. Por otra parte, vemos que en las estructuras
RAL Y RAC los maximos de las evocaciones exitosas fueron menos costosas que los maximos de
las evocaciones no exitosas, mientras que en RS la situacion fue inversa, el maximo de la
evocacion exitosa fue mayor que el maximo de la evocacion no exitosa.
Por lo tanto, concluimos que el RS es el mejor de las 3 estructuras para las evocaciones.

Esta conclusión esta respaldada por los resultados obtenidos en el siguiente cuadro:
##============================================================================##
||                      COMPARACION DE ESTRUCTURAS                            ||
##============================================================================##
||                      ||  COSTOS RAL   ||   COSTOS RAC   ||   COSTOS RS     ||
##============================================================================##
|| MAX. EVOC. EX.       ||     71.000     ||     26.000     ||      4.000     ||
|| MED. EVOC. EX.       ||     3.172      ||     2.005      ||     1.491      ||
|| MAX. EVOC. NO EX.    ||     111.000    ||     132.000    ||      4.000     ||
|| MED. EVOC. NO EX.    ||     50.450     ||     14.352     ||     1.180      ||
||============================================================================||

CAMBIO REALIZADO (3era entrega):
-Se cambio el lugar en donde se suma "el primer balde" de RAC y RAL, para corregir
en los fracasos cuando salia por i<factor.

-Se corrigio el nombre de la variable usada en RAC (es 'iteraciones', antes estaba 'i').
*/

//  110/0.83 = 133
#define FACTOR_RAL 133

//PRIMO MAYOR MAS CERCANO A 110/0.86 = 131
#define FACTOR_RAC 131

//  110/1.74 = 64
#define FACTOR_RS 64

typedef struct
{
    int DNI;
    char nombreApellido[81];
    char servicios[121];
    char domicilio[81];
    char mail[51];
    char telefono[31];
} Prestadores;

typedef struct
{
    Prestadores dato;
    int estado;     //-1 = virgen, 1 = ocupado, 0 = disponible
} CeldaRAL;

typedef struct
{
    CeldaRAL T[FACTOR_RAL];
    int cantidad;
} RAL;

typedef struct celdaRS
{
    Prestadores dato;
    struct celdaRS* sig;
} celdaRS;

typedef struct RS
{
    celdaRS T[FACTOR_RS];
    celdaRS* anterior;
    celdaRS* actual;
    int cantidad;
} RS;

typedef struct celdaRAC
{
    Prestadores dato;
    int estado; //-1 = virgen, 1 = ocupado, 0 = disponible
} celdaRAC;

typedef struct RAC
{
    celdaRAC T[FACTOR_RAC];
    int cantidad;
} RAC;

/**VARIABLES PARA COSTOS*/
/**EVOCACIONES*/
float maxevEral=0;
float maxevErac=0;
float maxevErs=0;

float maxevNEral=0;
float maxevNErac=0;
float maxevNErs=0;

float sumaEvEral=0;
float sumaEvErac=0;
float sumaEvErs=0;

float sumaEvNEral=0;
float sumaEvNErac=0;
float sumaEvNErs=0;

float cantEvEral=0;
float cantEvErac=0;
float cantEvErs=0;

float cantEvNEral=0;
float cantEvNErac=0;
float cantEvNErs=0;


/**PROTOTIPOS*/
int localizarRAL();
int localizarRAC ();
int localizarRS();

int altaRAL();
int altaRAC();
int altaRS();

int eliminarRAL();
int eliminarRAC();
int eliminarRS();

Prestadores evocarRAL();
Prestadores evocarRAC();
Prestadores evocarRS();

celdaRS* crearCeldaRS(Prestadores p);
void mostrarPrestador(Prestadores p);
int hashing(int dni,int M);
RAL nuevoRAL();
RAC nuevoRAC();
RS nuevoRS();

void mostrarRAC();
void mostrarRAL();
void mostrarRS();

void cuadroComp();

int main()
{
    RAL ral = nuevoRAL();
    RAC rac = nuevoRAC();
    RS rs = nuevoRS();

    int op;
    do
    {
        system("cls");
        system("color F");
        printf("##==========================================================================##\n");
        printf("||                PM3 - ESTRUCTURA DE DATOS Y ALGORITMOS 1                  ||\n");
        printf("||==========================================================================||\n");
        printf("||     1 - COMPARAR ESTRUCTURAS                                             ||\n");
        printf("||                                                                          ||\n");
        printf("||     2 - MOSTRAR REBALSE ABIERTO LINEAL                                   ||\n");
        printf("||                                                                          ||\n");
        printf("||     3 - MOSTRAR REBALSE ABIERTO CUADRATICO                               ||\n");
        printf("||                                                                          ||\n");
        printf("||     4 - MOSTRAR REBALSE SEPARADO                                         ||\n");
        printf("||                                                                          ||\n");
        printf("||     5 - SALIR                                                            ||\n");
        printf("##==========================================================================##\n");
        printf("Seleccione una opcion (1-5): ");

        scanf("%d", &op);

        switch(op)
        {
        case 1:
            vaciarRAL(&ral);
            vaciarRS(&rs);
            vaciarRAC(&rac);

            maxevEral=0;
            maxevErac=0;
            maxevErs=0;

            maxevNEral=0;
            maxevNErac=0;
            maxevNErs=0;

            sumaEvEral=0;
            sumaEvErac=0;
            sumaEvErs=0;

            sumaEvNEral=0;
            sumaEvNErac=0;
            sumaEvNErs=0;

            cantEvEral=0;
            cantEvErac=0;
            cantEvErs=0;

            cantEvNEral=0;
            cantEvNErac=0;
            cantEvNErs=0;

            leerArchivoOperaciones(&ral,&rac,&rs);
            cuadroComp();
            break;
        case 2:
            if(ral.cantidad < 1)
            {
                printf("Rebalse Abierto Lineal vacio\n");
                system("pause");
            }
            else
            {
                mostrarRAL(ral);
            }
            break;
        case 3:
            if(rac.cantidad <1)
            {
                printf("Rebalse Abierto Cuadratico vacio\n");
                system("pause");
            }
            else
            {
                mostrarRAC(rac);
            }
            break;
        case 4:
            if(rs.cantidad > 0)
            {
                mostrarRS(&rs);
            }
            else
            {
                printf("Rebalse Separado vacio\n");
                system("pause");
            }
            break;
        case 5:
            printf("Saliendo del programa...\n");
            exit(0);
        default:
            printf("Opcion invalida. Por favor, intente de nuevo.\n");
            getch();
            break;
        }/**FIN SWITCH*/

    }
    while(op!=5);
    return 0;
}

int hashing (int dni, int M)
{
    char x[10];
    int longitud, i ;
    int contador =0;
    sprintf (x,"%d", dni );
    longitud=strlen (x);
    for ( i =0; i< longitud ; i++)
        contador +=(( int )x[ i ]) * ( i +1);

    return (contador % M);
}


/*----------------------------FUNCIONES DE RAL------------------------------*/

RAL nuevoRAL()
{
    RAL ral;
    int i;
    Prestadores p = {0,"","","","",""};

    for (i = 0; i < FACTOR_RAL; i++)
    {
        ral.T[i].estado = -1;
        copiarPrestador(p,&(ral.T[i].dato));
    }
    ral.cantidad = 0;
    return ral;
}

//RETORNA -1 SI ESTA LLENO , 0 SI TUVO FRACASO, 1 SI TUVO EXITO
int localizarRAL(RAL ral,int *M,int dni, float* costo)
{
    int i=0,MAux=-1;
    *M=hashing(dni,FACTOR_RAL);
    *costo = 0;                     //inicializo costo

    while( (i<FACTOR_RAL) && (ral.T[*M].estado!=-1) && ((ral.T[*M].dato.DNI!=dni)||(ral.T[*M].estado==0)) )
    {
        if(ral.T[*M].estado==0&&MAux==-1){
            MAux=(*M);
        }
        (*M)=((*M)+1)%FACTOR_RAL;
        i++;

        *costo = (*costo) + 1;  //Siguiente balde
    }

    if(ral.T[*M].estado == 1 && ral.T[*M].dato.DNI==dni)
    {
        *costo = (*costo) + 1;
        return 1;                               //exito, se encontro el elemento
    }
    else if ((i>=FACTOR_RAL) && MAux == -1)
    {
        return -1;                              //No esta el elemento y Estructura llena
    }
    else
    {
        *costo = (*costo) + 1;
        if(ral.T[i].estado == -1)
        {
            *M = i;  //celda virgen
        }
        if(MAux!=-1)
        {
            (*M)=MAux; //celda libre
        }
        return 0;                               //No esta el elemento.
    }
}

int altaRAL(RAL *ral,Prestadores p)
{
    int posicion;
    float a=0;
    int exito = localizarRAL(*ral,&posicion,p.DNI, &a);
    if(exito == 1 || exito == -1)
    {
        return 0;       //elemento ya existe o estructura llena
    }
    else
    {
        ral->T[posicion].dato=p;
        ral->T[posicion].estado=1; //ocupado
        ral->cantidad++;
        return 1;
    }
}

int eliminarRAL(RAL *ral, Prestadores elim)
{
    int posicion;
    float a=0;
    if(localizarRAL(*ral,&posicion,elim.DNI, &a)==1)
    {
        if(compararPrestador(ral->T[posicion].dato,elim))
        {
            ral->T[posicion].estado=0;
            ral->cantidad--;
            return 1;
        }
    }
    return 0;
}

Prestadores evocarRAL(RAL ral,int dni)
{
    Prestadores p = {0};
    int posicion;
    float costo;
    int exito = localizarRAL(ral,&posicion,dni, &costo);
    if(exito==1)
    {
        if(maxevEral<costo)
        {
            maxevEral=costo;
        }
        sumaEvEral+=costo;
        cantEvEral++;
        p = ral.T[posicion].dato;
    } else {
        if(maxevNEral<costo)
        {
            maxevNEral=costo;
        }
        sumaEvNEral+=costo;
        cantEvNEral++;
    }
    return p;
}

void mostrarRAL(RAL ral)
{
    system("cls");
    int i;
    for(i=0; i<FACTOR_RAL; i++)
    {
        switch(ral.T[i].estado)
        {
        case 0:
            printf("\nPOSICION #%d de %d\nESTADO: LIBRE\n",i+1,FACTOR_RAL);
            if((i+1)%5==0)
            {
                printf("\n\nPresione Enter para continuar");
                getchar();
            }
            break;
        case -1:
            printf("\nPOSICION #%d de %d\nESTADO: VIRGEN\n",i+1,FACTOR_RAL);
            if((i+1)%5==0)
            {
                printf("\n\nPresione Enter para continuar");
                getchar();
            }
            break;
        case 1:
            printf("\nPOSICION #%d de %d\nESTADO: OCUPADO\n",i+1,FACTOR_RAL);
            mostrarPrestador(ral.T[i].dato);
            if((i+1)%5==0)
            {
                printf("\n\nPresione Enter para continuar");
                getchar();
            }
            break;
        }
    }
    printf("\n");
    system("pause");
}

void vaciarRAL(RAL* ral)
{
    int i;

    for (i = 0; i < FACTOR_RAL; i++)
    {
        ral->T[i].dato.DNI = 0;
        ral->T[i].estado = -1;
    }

    ral->cantidad = 0;
}

/*---------------------------------FUNCIONES DE RAC---------------------------*/

RAC nuevoRAC()
{
    RAC rac;
    int i;
    Prestadores p = {0,"","","","",""};

    for (i = 0; i < FACTOR_RAC; i++)
    {
        rac.T[i].estado = -1;
        copiarPrestador(p,&(rac.T[i].dato));
    }
    rac.cantidad = 0;
    return rac;
}

//RETORNA -1 SI FRACASA Y LA ESTRUCTURA ESTA LLENA, 0 SI FRACASA PERO HAY ESPACIO EN LA ESTRUCTURA, 1 SI TIENE EXITO
int localizarRAC(RAC rac, int dni, int* posicion, float* costo)
{
    int i = hashing(dni,FACTOR_RAC);
    int iAux = -1;
    int k = 1;
    int iteraciones = 0;
    *costo = 0;             //inicializo costo

    while( (iteraciones < FACTOR_RAC) && (rac.T[i].estado != -1) && ( (rac.T[i].dato.DNI != dni) || (rac.T[i].estado == 0) ) )
    {
        if(rac.T[i].estado == 0 && iAux == -1){
            iAux = i;
        }
        i = (i+k) % FACTOR_RAC;
        k++;
        iteraciones++;

        *costo= *costo + 1;  //Siguiente balde
    }
    if(rac.T[i].dato.DNI == dni && rac.T[i].estado == 1)
    {
        *costo = *costo + 1;
        *posicion = i;
        return 1;   //exito
    }

    else if (iteraciones>=FACTOR_RAC && iAux == -1)
    {
        return -1;                              //No se encontro el elemento y Estructura llena
    }

    else
    {
        *costo = *costo + 1;
        if(rac.T[i].estado == -1)
        {
            *posicion = i;  //celda virgen
        }
        if(iAux != -1)
        {
            *posicion = iAux;   //Asigno celda libre en el caso de haber encontrado una previamente.
        }

        return 0;           //Fracaso en la localizacion
    }
}

Prestadores evocarRAC(RAC rac, int dni)
{
    int posicion;
    float costo=0;
    int exito = localizarRAC(rac, dni, &posicion, &costo);

    if(exito == 1)
    {
        if(maxevErac<costo)
        {
            maxevErac=costo;
        }
        sumaEvErac=sumaEvErac+costo;
        cantEvErac++;
        return rac.T[posicion].dato;
    }
    else
    {
        if(maxevNErac<costo)
        {
            maxevNErac=costo;
        }
        sumaEvNErac = sumaEvNErac+costo;
        cantEvNErac++;
        Prestadores p = {0};
        return p; //prestador invalido
    }
}

int altaRAC(RAC* rac, Prestadores p)
{
    int posicion;
    float a=0;
    int exito = localizarRAC(*rac, p.DNI, &posicion, &a);
    if(exito == 1 || exito == -1)
    {
        return 0;   //el prestador ya existe o la estructura esta llena
    }
    else
    {
        copiarPrestador(p, &(rac->T[posicion].dato));
        rac->T[posicion].estado = 1; //ocupado
        rac->cantidad = rac->cantidad + 1;
    }
    return 1;
}

int eliminarRAC(RAC* rac, Prestadores p)
{
    int posicion;
    float a=0;
    if(localizarRAC(*rac, p.DNI, &posicion, &a))
    {
        if(compararPrestador(p, rac->T[posicion].dato))
        {
            rac->T[posicion].estado = 0; //desocupado
            rac->cantidad = rac->cantidad - 1;
            return 1;
        }
    }
    return 0;
}

void mostrarRAC(RAC rac)
{
    system("cls");
    int i;

    for(i=0; i<FACTOR_RAC; i++)
    {
        printf("\n");
        switch(rac.T[i].estado)
        {
        case -1:
            printf("POSICION #%d de %d\n", i+1, FACTOR_RAC);
            printf("ESTADO: VIRGEN\n");
            if((i+1)%5==0)
            {
                printf("\n\nPresione Enter para continuar");
                getchar();
            }
            break;

        case 0:
            printf("POSICION #%d de %d\n", i+1, FACTOR_RAC);
            printf("ESTADO: DISPONIBLE\n");
            if((i+1)%5==0)
            {
                printf("\n\nPresione Enter para continuar");
                getchar();
            }
            break;

        case 1:
            printf("POSICION #%d de %d\n", i+1, FACTOR_RAC);
            printf("ESTADO: OCUPADO\n");
            mostrarPrestador(rac.T[i].dato);
            if((i+1)%5==0)
            {
                printf("\n\nPresione Enter para continuar");
                getchar();
            }

            printf("\n");
            break;
        }
    }
    system("pause");
}

void vaciarRAC(RAC* rac)
{
    int i;

    for (i = 0; i < FACTOR_RAC; i++)
    {
        rac->T[i].dato.DNI = 0;
        rac->T[i].estado = -1;
    }

    rac->cantidad = 0;
}


/*---------------------------------FUNCIONES DE RS---------------------------*/

celdaRS* crearCeldaRS(Prestadores p)
{
    celdaRS* n = (celdaRS*)malloc(sizeof(celdaRS));
    if(n == NULL)
        return n;

    n->dato = p;
    n->sig = NULL;

    return n;
}

RS nuevoRS()
{
    RS rs;
    int i;
    Prestadores p = {0,"","","","",""};

    for(i = 0; i < FACTOR_RS; i++)
    {
        rs.T[i].dato = p;
        rs.T[i].sig = NULL;
    }

    rs.actual = NULL;
    rs.anterior = NULL;
    rs.cantidad = 0;

    return rs;
}

//RETORNA 1 SI TUVO EXITO, 0 SI NO.
int localizarRS(RS* rs, int dni, float* costo)
{
    int i = hashing(dni, FACTOR_RS);
    rs->anterior = &(rs->T[i]);
    rs->actual = &(rs->T[i]);

    *costo+=1;  //Primer balde

    if(rs->actual->sig == NULL && rs->actual->dato.DNI == 0)
    {
        return 0;   //Caso: Dar de alta en cabecera
    }

    while(rs->actual != NULL && (dni != rs->actual->dato.DNI))
    {
        rs->anterior = rs->actual;
        rs->actual = rs->actual->sig;

        if(rs->actual!=NULL)
            *costo+=1;  //siguiente balde
    }

    if(rs->actual != NULL)
    {
        return 1;
    }
    return 0;
}

Prestadores evocarRS(RS rs, int dni)
{
    float costo=0;
    if(localizarRS(&rs, dni, &costo))
    {
        if(maxevErs < costo)
        {
            maxevErs = costo;
        }
        sumaEvErs+=costo;
        cantEvErs++;
        return rs.actual->dato;
    }
    else
    {
        if(maxevNErs < costo)
        {
            maxevNErs = costo;
        }
        sumaEvNErs+=costo;
        cantEvNErs++;
        Prestadores p = {0};
        return p; //Prestador invalido
    }
}

int altaRS(RS *rs,Prestadores p)
{
    float costo=0;
    if(localizarRS(rs,p.DNI, &costo)==1)
    {
        return 0;
    }
    else
    {
        int i = hashing(p.DNI,FACTOR_RS);
        celdaRS *Baux = crearCeldaRS(p);
        if(Baux==NULL)
            return -1;
        else
        {
            if(rs->actual==rs->anterior)        //dar de alta en cabecera
            {
                rs->T[i] = *Baux;
                rs->actual=Baux;
                rs->anterior=Baux;

                free((void*)Baux);
            }
            else
            {
                rs->anterior->sig = Baux;
                rs->actual = rs->anterior->sig;
            }
            rs->cantidad = rs->cantidad + 1;
            return 1;
        }
    }
}

int eliminarRS(RS* rs, Prestadores p)
{
    float costo = 0;

    if(localizarRS(rs, p.DNI, &costo) == 1)
    {
        if(compararPrestador(p, rs->actual->dato) == 1)
        {
            // si el nodo a eliminar esta en la cabecera
            if(rs->actual == &(rs->T[hashing(p.DNI, FACTOR_RS)]))
            {
                if(rs->actual->sig == NULL)
                {
                    Prestadores prestadorVacio = {0,"","","","",""};
                    rs->actual->dato = prestadorVacio;  // Dejamos la celda vacía
                }
                else
                {
                    // si hay celdas enlazadas; copiamos los datos de la siguiente a la cabecera
                    celdaRS* temp = rs->actual->sig;
                    rs->actual->dato = temp->dato;
                    rs->actual->sig = temp->sig;
                    free(temp);
                }
            }
            else
            {
                // cuando el nodo a eliminar no es el primero
                rs->anterior->sig = rs->actual->sig;
                free(rs->actual);
            }

            rs->cantidad--;
            return 1;        // Eliminacion exitosa
        }
    }

    return 0;  // Fracaso
}


void mostrarRS(RS *rs)
{
    system("cls");
    int i=0;
    for(i=0; i<FACTOR_RS; i++)
    {
        rs->actual = &(rs->T[i]);
        rs->anterior = &(rs->T[i]);

        while(rs->actual!=NULL)
        {
            if(rs->actual->dato.DNI == 0)
            {
                printf("\nPOSICION #%d de %d\nESTADO: LIBRE\n",i+1,FACTOR_RS);
                if((i+1)%5==0)
                {
                    printf("\n\nPresione Enter para continuar");
                    getchar();
                }
            }
            else
            {
                printf("\nPOSICION #%d de %d\nESTADO: OCUPADO\n",i+1,FACTOR_RS);
                mostrarPrestador(rs->actual->dato);
                if((i+1)%5==0)
                {
                    printf("\n\nPresione Enter para continuar");
                    getchar();
                }
            }
            rs->anterior = rs->actual;
            rs->actual = rs->actual->sig;
        }
    }
    printf("\n\n");
    system("pause");
}

void vaciarRS(RS* rs)
{
    int i;
    Prestadores p = {0,"","","","",""};

    for(i = 0; i < FACTOR_RS; i++)
    {
        rs->anterior = &(rs->T[i]);
        rs->actual = rs->anterior->sig;

        while(rs->actual != NULL)
        {
            rs->anterior = rs->actual;
            rs->actual = rs->actual->sig;
            free((void*)rs->anterior);
        }
    }

    for(i = 0; i < FACTOR_RS; i++)
    {
        rs->T[i].dato = p;
        rs->T[i].sig = NULL;
    }
    rs->cantidad = 0;
}

/*-----------------FUNCIONES APARTE--------------------*/

void copiarPrestador(Prestadores p, Prestadores *p2)
{
    (*p2).DNI = p.DNI;
    strcpy((*p2).domicilio, p.domicilio);
    strcpy((*p2).mail, p.mail);
    strcpy((*p2).servicios, p.servicios);
    strcpy((*p2).nombreApellido, p.nombreApellido);
    strcpy((*p2).telefono, p.telefono);
}

void mostrarPrestador(Prestadores p)
{
    printf("DNI: %d\n", p.DNI);
    printf("Nombre y Apellido: %s\n", p.nombreApellido);
    printf("Servicio: %s\n", p.servicios);
    printf("Domicilio: %s\n", p.domicilio);
    printf("Correo electronico: %s\n", p.mail);
    printf("Telefono: %s\n", p.telefono);
}

void leerArchivoOperaciones(RAL *ral,RAC *rac, RS *rs)
{
    FILE* archivo;
    archivo = fopen("Operaciones-Prestadores.txt", "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo\n");
        system("pause");
        return;
    }
    int codigoOperacion;
    Prestadores prestador;
    int dni, al=0, baj=0, ev=0;

    while (!feof(archivo))
    {
        fscanf(archivo, "%d", &codigoOperacion);
        switch (codigoOperacion)
        {
        case 1: // Alta de prestador
            fscanf(archivo, "%d",&prestador.DNI);
            fscanf(archivo, " %[^\n]", prestador.nombreApellido);
            fscanf(archivo, " %[^\n]", prestador.servicios);
            fscanf(archivo, " %[^\n]", prestador.domicilio);
            fscanf(archivo, " %[^\n]", prestador.mail);
            fscanf(archivo, " %[^\n]", prestador.telefono);

            if(prestador.DNI>0)
            {
                altaRAL(ral, prestador);
                altaRAC(rac, prestador);
                altaRS(rs,prestador);
            }
            break;
        case 2: // Baja de prestador
            fscanf(archivo, "%d",&prestador.DNI);
            fscanf(archivo, " %[^\n]", prestador.nombreApellido);
            fscanf(archivo, " %[^\n]", prestador.servicios);
            fscanf(archivo, " %[^\n]", prestador.domicilio);
            fscanf(archivo, " %[^\n]", prestador.mail);
            fscanf(archivo, " %[^\n]", prestador.telefono);

            eliminarRAL(ral,prestador);
            eliminarRAC(rac,prestador);
            eliminarRS(rs,prestador);
            break;
        case 3: // Evocar prestador
            fscanf(archivo, "%d", &dni);

            evocarRAL((*ral),dni);
            evocarRAC((*rac),dni);
            evocarRS((*rs),dni);
            break;
        default:
            printf("Codigo de operacion no reconocido: %d\n", codigoOperacion);
            break;
        }
    }
    printf("\nArchivo de operaciones leido con exito\n");
    system("pause");
    fclose(archivo);
}

int compararPrestador(Prestadores a, Prestadores b)
{
    if (a.DNI == b.DNI && strcasecmp(a.domicilio,b.domicilio)==0 && strcasecmp(a.mail,b.mail)==0 && strcasecmp(a.nombreApellido,b.nombreApellido)==0 && strcasecmp(a.servicios,b.servicios)==0 && strcasecmp(a.telefono,b.telefono)==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void cuadroComp(void)
{
    system("cls");
    system("color 03");
    printf("##============================================================================##\n");
    printf("||                      COMPARACION DE ESTRUCTURAS                            ||\n");
    printf("##============================================================================##\n");
    printf("||                      ||  COSTOS RAL   ||   COSTOS RAC   ||   COSTOS RS     ||\n");
    printf("##============================================================================##\n");

    printf("|| MAX. EVOC. EX.       ||     %.3f     ||     %.3f     ||      %.3f     ||\n", maxevEral, maxevErac, maxevErs);

    printf("|| MED. EVOC. EX.       ||");

    if (cantEvEral == 0)
    {
        printf("     0.000     ||");
    }
    else
    {
        printf("     %.3f      ||", (sumaEvEral / cantEvEral));
    }

    if (cantEvErac == 0)
    {
        printf("     0.000     ||");
    }
    else
    {
        printf("     %.3f      ||", (sumaEvErac / cantEvErac));
    }

    if (cantEvErs == 0)
    {
        printf("     0.000     ||\n");
    }
    else
    {
        printf("     %.3f      ||\n", (sumaEvErs / cantEvErs));
    }


    printf("|| MAX. EVOC. NO EX.    ||     %.3f    ||     %.3f    ||      %.3f     ||\n", maxevNEral, maxevNErac, maxevNErs);

    printf("|| MED. EVOC. NO EX.    ||");

    if (cantEvNEral == 0)
    {
        printf("     0.000     ||");
    }
    else
    {
        printf("     %.3f     ||", (sumaEvNEral / cantEvNEral));
    }

    if (cantEvNErac == 0)
    {
        printf("     0.000     ||");
    }
    else
    {
        printf("     %.3f     ||", (sumaEvNErac / cantEvNErac));
    }

    if (cantEvNErs == 0)
    {
        printf("     0.000     ||\n");
    }
    else
    {
        printf("     %.3f      ||\n", (sumaEvNErs / cantEvNErs));
    }

    printf("||============================================================================||\n");
    system("pause");
    system("cls");
}

