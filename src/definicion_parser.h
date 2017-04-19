// Utilidades para el parseo del archivo de definición de lenguajes
// @author: Jonathan Samines
// Universidad Mariano Galvez de Guatemala

#include <string.h>
#include "utilidades_cadena.h"

char* SEPARADOR_ESPECIFICACION_GENERAL = "[%%]";
char* SEPARADOR_VALIDACIONES = "[&&]";
char* SEPARADOR_EXPRESION = ":=";

char* SEPARADOR_CADENA_SIMPLE = "'";
char* SEPARADOR_CADENA_RANGO_INICIO = "[";
char* SEPARADOR_CADENA_RANGO_FIN = "]";
char* SEPARADOR_CADENA_RANGO_LISTA = ",";
char* SEPARADOR_CADENA_RANGO_EXPANSION = "-";

char* crear_rangos(char* rangos) {
  char *end_lista;
  char *rango = strtok_r(rangos, SEPARADOR_CADENA_RANGO_LISTA, &end_lista);

  while (rango != NULL){
    rango = strtok_r(NULL, SEPARADOR_CADENA_RANGO_LISTA, &end_lista);
    printf("%sgeneracion de rangos: %s para %s", CARACTER_SALTO_LINEA, rango, rangos);
  }

  return NULL;
}

char* analizar_valor_expresion(char* valor_expresion) {
  // un valor de expresion valido, puede ser una cadena simple o un rango(s)
  // caracter individual = 'CARACTER'
  // rango (s) = [b, A-Z]
  int indice_inicio;
  int indice_fin;

  // cadenas simples
  indice_inicio = indiceDe(valor_expresion, SEPARADOR_CADENA_SIMPLE, 0);

  if (indice_inicio == 0) {
    indice_fin = indiceDe(valor_expresion, SEPARADOR_CADENA_SIMPLE, indice_inicio + 1);

    if (indice_fin != -1) {
      // es una cadena simple
      char cadena[indice_fin - indice_inicio];
      substraer(valor_expresion, indice_inicio + 1, indice_fin - 1, cadena);
      // printf("cadena encontrada!!!  %s", valor_expresion);

      return NULL;
    }

    printf("Cadena no terminada correctamente ....");
    return NULL;
  }

  // rangos
  indice_inicio = indiceDe(valor_expresion, SEPARADOR_CADENA_RANGO_INICIO, 0);

  if (indice_inicio == 0) {
    indice_fin = indiceDe(valor_expresion, SEPARADOR_CADENA_RANGO_FIN, indice_inicio + 1);

    if (indice_fin != -1) {
      // es una cadena simple
      char cadena[indice_fin - indice_inicio];
      substraer(valor_expresion, indice_inicio + 1, indice_fin - 1, cadena);
      printf("rango encontrado!!!  %s", cadena);
      valor_expresion = crear_rangos(cadena);

      return NULL;
    }

    printf("Rango no terminado correctamente ....");
    return NULL;
  }

  return valor_expresion;
}

char* analizar_definicion_expresion(char* linea) {
  char* final_expresion;
  char* identificador_expresion = strtok_r(linea, SEPARADOR_EXPRESION, &final_expresion);
  char* valor_expresion = strtok_r(NULL, SEPARADOR_EXPRESION, &final_expresion);

  if (cadena_nula(valor_expresion)) return NULL;

  identificador_expresion = eliminar_espacios(identificador_expresion);
  valor_expresion = eliminar_espacios(valor_expresion);
  valor_expresion = analizar_valor_expresion(valor_expresion);

  printf("%s%sToken: %s := %s", CARACTER_SALTO_LINEA, CARACTER_TABULACION, identificador_expresion, valor_expresion);

  return NULL;
}

char* analizar_definicion(char* cadena) {
  char* linea = leer_siguiente_linea(cadena);

  printf("%s [BLOQUE] Especificacion general", CARACTER_SALTO_LINEA);

  if (cadena_nula(linea) ||
    !cadenas_iguales(linea, SEPARADOR_ESPECIFICACION_GENERAL)) {
    printf("%sERROR: Especificacion general no definida", CARACTER_SALTO_LINEA);
    return NULL;
  }

  // mientras no llegue a la especificación regular
  // se analiza la especificacion general
  do {
    printf("%sL%d - %s", CARACTER_SALTO_LINEA, __numero_linea, linea);

    linea = leer_siguiente_linea(NULL);
    analizar_definicion_expresion(linea);
  } while (
    !cadena_nula(linea) &&
    !cadenas_iguales(linea, SEPARADOR_ESPECIFICACION_GENERAL)
  );

  if (cadena_nula(linea)) {
    printf("%sERROR: Especificacion regular no definida", CARACTER_SALTO_LINEA);
    return NULL;
  }

  printf("%s [BLOQUE] Especificacion regular", CARACTER_SALTO_LINEA);

  // mientras no llegue a la seccion de validaciones
  // se analiza la especificacion regular
  do {
    printf("%sL%d - %s", CARACTER_SALTO_LINEA, __numero_linea, linea);
    linea = leer_siguiente_linea(NULL);
    analizar_definicion_expresion(linea);
  } while (
    !cadena_nula(linea) &&
    !cadenas_iguales(linea, SEPARADOR_VALIDACIONES)
  );

  if (cadena_nula(linea)) {
    printf("%sERROR: Validaciones no definidas", CARACTER_SALTO_LINEA);
    return NULL;
  }

  printf("%s [BLOQUE] Seccion de Validaciones", CARACTER_SALTO_LINEA);

  // mientras no llegue al cierre de la sección de validaciones
  // se analiza la seccion de validaciones
  do {
    printf("%sL%d - %s", CARACTER_SALTO_LINEA, __numero_linea, linea);
    linea = leer_siguiente_linea(NULL);
    analizar_definicion_expresion(linea);
  } while (
    !cadena_nula(linea) &&
    !cadenas_iguales(linea, SEPARADOR_VALIDACIONES)
  );

  if (cadena_nula(linea)) {
    printf("%sERROR: Validaciones no definidas", CARACTER_SALTO_LINEA);
    return NULL;
  }

  return linea;
}
