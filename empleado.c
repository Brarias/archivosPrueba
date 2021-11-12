#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "empleado.h"


int  mostrarEmpleado(eEmpleado* p)
{
    int todoOk = 0;
    int legajo;
    char nombre[20];
    char sexo;
    float sueldo;

    if(p != NULL && empleadoGetLegajo(p, &legajo)
            && empleadoGetNombre(p, nombre)
            && empleadoGetSexo(p, &sexo)
            && empleadoGetSueldo(p, &sueldo))
    {
        printf("%d  %10s  %c  %.2f\n\n",
               legajo,
               nombre,
               sexo,
               sueldo);
        todoOk = 1;
    }

    return todoOk;
}

eEmpleado* newEmpleado()
{

    eEmpleado* nuevoEmpleado = (eEmpleado*) malloc(sizeof(eEmpleado));
    if(nuevoEmpleado != NULL)
    {
        nuevoEmpleado->legajo = 0;
        strcpy(nuevoEmpleado->nombre, "");
        nuevoEmpleado->sexo = ' ';
        nuevoEmpleado->sueldo = 0;


    }
    return nuevoEmpleado;
}

void destroyEmpleado(eEmpleado* p)
{

    free(p);

}

eEmpleado* newEmpleadoParam(int legajo, char* nombre, char sexo, float sueldo)
{

    eEmpleado* nuevoEmpleado = newEmpleado();

    if(nuevoEmpleado != NULL)
    {
        /*nuevoEmpleado->legajo = legajo;
        strcpy(nuevoEmpleado->nombre, nombre);
        nuevoEmpleado->sexo = sexo;
        nuevoEmpleado->sueldo = sueldo;*/
        if(!(empleadoSetLegajo(nuevoEmpleado, legajo) &&
                empleadoSetNombre(nuevoEmpleado, nombre)&&
                empleadoSetSexo(nuevoEmpleado, sexo) &&
                empleadoSetSueldo(nuevoEmpleado, sueldo)))
        {
            destroyEmpleado(nuevoEmpleado);
            nuevoEmpleado = NULL;
        }
    }

    return nuevoEmpleado;

}

int empleadoSetLegajo(eEmpleado* e, int legajo)
{
    int todoOk = 0;

    if(e != NULL && legajo > 0)
    {
        e->legajo = legajo;
        todoOk = 1;
    }

    return todoOk;
}

int empleadoGetLegajo(eEmpleado* e, int* pLegajo)
{
    int todoOk = 0;

    if(e != NULL && pLegajo != NULL)
    {
        *pLegajo = e->legajo;
        todoOk = 1;
    }

    return todoOk;
}

int empleadoSetNombre(eEmpleado* e, char* nombre)
{

    int todoOk = 0;

    if(e != NULL && nombre != NULL && strlen(nombre)<20 && strlen(nombre) > 2)
    {
        strcpy(e->nombre, nombre);
        todoOk = 1;
    }

    return todoOk;
}

int empleadoSetSexo(eEmpleado* e, char sexo)
{

    int todoOk = 0;

    if(e != NULL && (sexo == 'f' || sexo == 'm'))
    {
        e->sexo = sexo;
        todoOk = 1;
    }

    return todoOk;
}

int empleadoSetSueldo(eEmpleado* e, float sueldo)
{

    int todoOk = 0;

    if(e != NULL && sueldo > 0)
    {
        e->sueldo = sueldo;
        todoOk = 1;
    }

    return todoOk;
}

int empleadoGetNombre(eEmpleado* e, char* pNombre)
{

    int todoOk = 0;

    if(e != NULL && pNombre != NULL)
    {
        strcpy(pNombre, e->nombre);
        todoOk = 1;
    }

    return todoOk;


}
int empleadoGetSexo(eEmpleado* e, char* pSexo)
{

    int todoOk = 0;

    if(e != NULL && pSexo != NULL)
    {
        *pSexo = e->sexo;
        todoOk = 1;
    }

    return todoOk;

}
int empleadoGetSueldo(eEmpleado* e, float* pSueldo)
{
    int todoOk = 0;

    if(e != NULL && pSueldo != NULL)
    {
        *pSueldo = e->sueldo;
        todoOk = 1;
    }

    return todoOk;
}

int  mostrarEmpleados(eEmpleado** lista, int tam)
{

    int todoOk = 0;

    if(lista != NULL && tam > 0)
    {
        printf(" Legajo  Nombre  Sexo  Sueldo\n");
        for(int i = 0; i < tam; i++)
        {
            mostrarEmpleado(*(lista + i));
        }
        printf("\n\n");
        todoOk = 1;
    }

    return todoOk;

}

int inicializarEmpleados(eEmpleado** vec, int tam)
{
    int todoOk = 0;

    if(vec != NULL && tam > 0)
    {
        for(int i = 0; i < tam; i++)
        {
            *(vec + i) = NULL;

        }
        todoOk = 1;
    }
    return todoOk;
}

int buscarLibreEmpleado(eEmpleado** vec, int tam, int* pIndice)
{
    int todoOk = 0;

    if(vec != NULL && pIndice != NULL && tam > 0 )
    {
        *pIndice = -1;
        for(int i = 0; i < tam; i++)
        {
            if(*(vec + i) == NULL)
            {
                *pIndice = i;
                break;
            }

        }
        todoOk = 1;
    }

    return todoOk;
}


int agrandarLista(eEmpleado*** vec, int* pTam)
{
    int todoOk = 0;
    eEmpleado** aux = NULL;

    if(vec != NULL && pTam != NULL)
    {
        int tam = *pTam + 1;
        aux = (eEmpleado**) realloc(*vec, sizeof(eEmpleado*)* tam);
        if(aux != NULL)
        {
            *vec = aux;
            aux = NULL;
            *pTam = tam;
            *(*vec + tam -1) = NULL;
            todoOk = 1;
        }
    }

    return todoOk;
}

int ordenarEmpleados(eEmpleado** vec, int tam)
{
    int todoOk = 0;
    eEmpleado* aux = NULL;

    if(vec != NULL && tam > 0)
    {
        for(int i = 0; i < tam-1; i++)
        {
            for(int j = i +1; j < tam; j++)
            {
                if(*(vec+i) != NULL && *(vec+j) != NULL)
                {
                    if(strcmp((*(vec+i))->nombre, (*(vec+j))->nombre) > 0)
                    {
                        aux = *(vec+i);
                        *(vec+i) = *(vec+j);
                        *(vec+j) = aux;
                    }
                }
            }
        }
        todoOk = 1;
    }


    return todoOk;
}

eEmpleado* newEmpleadoStr(char* strLegajo, char* strNombre, char* strSexo, char* strSueldo){
eEmpleado* nuevoEmpleado = newEmpleado();

    if(nuevoEmpleado != NULL)
    {
        /*nuevoEmpleado->legajo = legajo;
        strcpy(nuevoEmpleado->nombre, nombre);
        nuevoEmpleado->sexo = sexo;
        nuevoEmpleado->sueldo = sueldo;*/
        if(!(empleadoSetLegajo(nuevoEmpleado, atoi(strLegajo)) &&
                empleadoSetNombre(nuevoEmpleado, strNombre)&&
                empleadoSetSexo(nuevoEmpleado, strSexo[0]) &&
                empleadoSetSueldo(nuevoEmpleado, atof(strSueldo))))
        {
            destroyEmpleado(nuevoEmpleado);
            nuevoEmpleado = NULL;
        }
    }

    return nuevoEmpleado;


}



