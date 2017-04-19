// Utilidades para el tratamiento de cadenas
// @author: Jonathan Samines
// Universidad Mariano Galvez de Guatemala

#ifndef _UTILIDADES_CADENA_INCLUDED_
  #define _UTILIDADES_CADENA_INCLUDED_
  #include <string.h>
  #include <stdbool.h>
  #include <ctype.h>

  const char* CARACTER_SALTO_LINEA = "\n";
  const char* CARACTER_TABULACION = "\t";

  /**
   * Determina si dos cadenas son iguales
   * @param  cadenaA [description]
   * @param  cadenaB [description]
   * @return true si lo son, de lo contrario false
   */
  bool cadenas_iguales(char* cadenaA, char* cadenaB) {
    return strcmp(cadenaA, cadenaB) == 0;
  }

  /**
   * Determina si una cadena es nula
   */
  bool cadena_nula(char* cadena) {
    return cadena == NULL;
  }

  int indiceDe(char* cadena, char* subcadena, int desde) {
    char* encontrado = strstr(cadena+desde, subcadena);

    if (encontrado != NULL) {
      return encontrado - cadena;
    }

    return -1;
  }

  char* substraer(char* cadena, int desde, int hasta, char* subcadena) {
    int longitud_cadena = strlen(cadena);

    if (desde + hasta > longitud_cadena)
    {
       return NULL;
    }

    strncpy (subcadena, cadena + desde, hasta);

    return subcadena;
  }

  char* eliminar_espacios(char *cadena) {
    char *final_cadena;

    // eliminar espacios al inicio de la cadena
    while(isspace((unsigned char)*cadena)) cadena++;

    // si todos los caracteres eran espacios
    if(*cadena == 0)
      return cadena;

    // eliminar espacios al final de la cadena
    final_cadena = cadena + strlen(cadena) - 1;
    while(final_cadena > cadena && isspace((unsigned char)*final_cadena)) final_cadena--;

    // terminal la cadena con NULL
    *(final_cadena + 1) = 0;

    return cadena;
  }

  int __numero_linea = 0;

  /**
   * Lee la siguiente linea de una cadena separada por saltos de linea
   * Si es llamado con una cadena (char*) el punter es inicializado
   * LLamadas consecuentes con NULL, invocan la siguiente linea desde la ultima llamada con la cadena valida
   * @param  cadena
   * @return La siguiente linea
   */
  char* leer_siguiente_linea(char* cadena) {
    if (cadena == NULL) {
      __numero_linea++;
      return strtok(NULL, CARACTER_SALTO_LINEA);
    }

    __numero_linea = 0;

    return strtok(cadena, CARACTER_SALTO_LINEA);
  }
#endif
