#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "empleado.h"

int main()
{
    int tam = 1;
    int cant;
    //int auxLegajo;
    int indice;
    int flag = 0;
    //char auxCadena[100];
   // char auxChar;
    char buffer[4][20];
    //float auxFloat;
    eEmpleado* auxEmpleado = NULL;

    eEmpleado** lista = (eEmpleado**) malloc(sizeof(eEmpleado*)*tam);


    if(lista == NULL)
    {
        printf("No se consiguio espacio para la lista\n");
        exit(1);
    }

    if(inicializarEmpleados(lista, tam))
    {
        printf("Inicializacion exitosa!!!\n\n");
    }
    else
    {
        printf("No se pudo inicializar\n\n");
    }


    FILE* f = fopen("listaEmpleados2.csv", "r");
    if(f == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }

    //Lectura fantasma para saltar el encabezado
    //fscanf(f, "%s\n", auxCadena);

    fscanf(f, "%[^,], %[^,], %[^,], %[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3]);

    //itero sobre cada renglon del archivo
    while(!feof(f))
    {

        buscarLibreEmpleado(lista, tam, &indice);

        if(indice == -1)
        {
            if(!agrandarLista(&lista, &tam))
            {
                flag = 1; // problema para conseguir lugar
                break;
            }
        }
        else
        {
            //leo y parseo una fila del archivo
            //cant = fscanf(f, "%d,%[^,],%c,%f", &auxLegajo, auxCadena, &auxChar, &auxFloat);
            cant = fscanf(f, "%[^,], %[^,], %[^,], %[^\n]", buffer[0], buffer[1], buffer[2], buffer[3]);

            if(cant == 4)
            {
                // si la lectura fue exitosa creo un empleado con el constructor
                //auxEmpleado = newEmpleadoParam(auxLegajo, auxCadena, tolower(auxChar), auxFloat);
                auxEmpleado = newEmpleadoStr(buffer[0], buffer[1], buffer[2], buffer[3]);
                if(auxEmpleado != NULL)
                {
                    *(lista + indice) = auxEmpleado;
                    auxEmpleado = NULL;
                }
                else
                {
                    flag = 2; //problema para crear el empleado
                    break;
                }
            }
            else{
                flag = 3; // problema al leer el empleado
                break;
            }
        }
    }

     if(flag == 0){
        printf("Empleados cargados correctamente!!!\n");
     }
     else if(flag == 1){
        printf("Problema para conseguir lugar!\n");
     }
     else if(flag == 2){
        printf("No se pudo crear el empleado!\n");
     }
     else if(flag == 2){
        printf("Problema al leer el empleado!\n");
     }





     fclose(f);
     mostrarEmpleados(lista, tam);

     // guardo los empleados en otro archivo

    /*f = fopen("listaEmpleados2.csv", "w");
    if(f == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }
    fprintf(f,"legajo,nombre,sexo,sueldo\n");
    for(int i = 0; i < tam; i++){
       auxEmpleado = *(lista + i);
            if(*(lista + i) != NULL){
                fprintf(f,"%d,%s,%c,%.2f\n", auxEmpleado->legajo,
                       auxEmpleado->nombre,
                       auxEmpleado->sexo,
                       auxEmpleado->sueldo);
            }
    auxEmpleado = NULL;

    }

     fclose(f);*/



     free(lista);
    return 0;
}
