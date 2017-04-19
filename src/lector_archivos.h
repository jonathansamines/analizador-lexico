// Utilidades para la lectura de archivos
// @author: Jonathan Samines
// Universidad Mariano Galvez de Guatemala

#include <stdio.h>
#include <stdlib.h>

const char* PERMISOS_ARCHIVO = "r";

char* leer_contenido_archivo(const char *nombre_archivo)
{
   char *buffer = NULL;
   int espacio_cadena, espacio_esperado_buffer;
   FILE *descriptor_archivo = fopen(nombre_archivo, PERMISOS_ARCHIVO);

   if (descriptor_archivo)
   {
       // mover al ultimo byte del archivo
       fseek(descriptor_archivo, 0, SEEK_END);

       // obtener el tamaño de la cadena
       espacio_cadena = ftell(descriptor_archivo);

       // mover el puntero del descriptor al inicio de la cadena
       rewind(descriptor_archivo);

       // crear un buffer en memoria con el espacio en memoria suficiente para contener la cadena
       buffer = (char*) malloc(sizeof(char) * (espacio_cadena + 1) );

       // obtener el tamaño de la cadena en memoria
       espacio_esperado_buffer = fread(buffer, sizeof(char), espacio_cadena, descriptor_archivo);

       // serializar buffer, agregando un \0 al final de la cadena
       buffer[espacio_cadena] = '\0';

       if (espacio_cadena != espacio_esperado_buffer)
       {
           // liberar memoria en caso de error
           free(buffer);
           buffer = NULL;
       }

       fclose(descriptor_archivo);
    }

    return buffer;
}
