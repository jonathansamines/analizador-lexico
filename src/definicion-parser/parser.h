// Utilidades para el parseo del archivo de definición de lenguajes
// @author: Jonathan Samines
// Universidad Mariano Galvez de Guatemala

#include <string.h>
#include "./analizador_rango.h"
#include "./analizador_expresion.h"
#include "./../utilidades_cadena.h"

char* SEPARADOR_ESPECIFICACION_GENERAL = "[%%]";
char* SEPARADOR_VALIDACIONES = "[&&]";

char* analizar_definicion(char* cadena) {
  char* linea = leer_siguiente_linea(cadena);

  printf("%s%s [BLOQUE] Especificacion general", CARACTER_SALTO_LINEA, CARACTER_SALTO_LINEA);
  fflush(stdout);

  if (cadena_nula(linea) ||
    !cadenas_iguales(linea, SEPARADOR_ESPECIFICACION_GENERAL)) {
    printf("%sERROR: Especificacion general no definida", CARACTER_SALTO_LINEA);
    fflush(stdout);
    return NULL;
  }

  // mientras no llegue a la especificación regular
  // se analiza la especificacion general
  do {
    linea = leer_siguiente_linea(NULL);
    printf("%s  (L%d) - %s", CARACTER_SALTO_LINEA, __numero_linea, linea);
    fflush(stdout);

    if (!cadenas_iguales(linea, SEPARADOR_ESPECIFICACION_GENERAL)) {
      struct Expresion* expresion = crear_definicion_expresion(linea);

      if (expresion != NULL) {
        struct ExpresionValor* valor = expresion->valor;
        printf("%s   + Identificador token: %s", CARACTER_SALTO_LINEA, expresion->identificador);
        fflush(stdout);
        printf("%s", CARACTER_SALTO_LINEA);
        fflush(stdout);

        // if (valor->cadena != NULL) {
        //   printf("%s   + Valor token: %s", CARACTER_SALTO_LINEA, expresion->valor->cadena);
        // }
        //
        // if (valor->rango != NULL) {
        //   struct ExpansionRango* rango = valor->rango;
        //
        //   while (rango != NULL) {
        //     printf("%s   + Valor token: (desde=%c) (hasta=%c)", CARACTER_SALTO_LINEA, rango->desde, rango->hasta);
        //     rango = rango->siguienteNodo;
        //   }
        // }
      }

    } else {
      printf("%s   + Separador ignorado", CARACTER_SALTO_LINEA);
      fflush(stdout);
    }
  } while (
    !cadena_nula(linea) &&
    !cadenas_iguales(linea, SEPARADOR_ESPECIFICACION_GENERAL)
  );

  if (cadena_nula(linea)) {
    printf("%sERROR: Especificacion regular no definida", CARACTER_SALTO_LINEA);
    fflush(stdout);
    return NULL;
  }

  printf("%s%s [BLOQUE] Especificacion regular", CARACTER_SALTO_LINEA, CARACTER_SALTO_LINEA);
  fflush(stdout);

  // mientras no llegue a la seccion de validaciones
  // se analiza la especificacion regular
  do {
    linea = leer_siguiente_linea(NULL);
    printf("%s  (L%d) - %s", CARACTER_SALTO_LINEA, __numero_linea, linea);
    fflush(stdout);

    if (!cadenas_iguales(linea, SEPARADOR_VALIDACIONES)) {
      struct Expresion* expresion = crear_definicion_expresion(linea);

      if (expresion != NULL) {
        printf("%s   + Identificador token: %s", CARACTER_SALTO_LINEA, expresion->identificador);
        fflush(stdout);
        printf("%s", CARACTER_SALTO_LINEA);
        fflush(stdout);
      }
    } else {
     printf("%s   + Separador ignorado", CARACTER_SALTO_LINEA);
     fflush(stdout);
    }
  } while (
    !cadena_nula(linea) &&
    !cadenas_iguales(linea, SEPARADOR_VALIDACIONES)
  );

  if (cadena_nula(linea)) {
    printf("%sERROR: Validaciones no definidas", CARACTER_SALTO_LINEA);
    fflush(stdout);
    return NULL;
  }

  printf("%s%s [BLOQUE] Seccion de Validaciones", CARACTER_SALTO_LINEA, CARACTER_SALTO_LINEA);
  fflush(stdout);

  // mientras no llegue al cierre de la sección de validaciones
  // se analiza la seccion de validaciones
  do {
    linea = leer_siguiente_linea(NULL);
    printf("%s  (L%d) - %s", CARACTER_SALTO_LINEA, __numero_linea, linea);
    fflush(stdout);

    if (!cadenas_iguales(linea, SEPARADOR_VALIDACIONES)) {
      struct Expresion* expresion = crear_definicion_expresion(linea);

      if (expresion != NULL) {
        printf("%s   + Identificador token: %s", CARACTER_SALTO_LINEA, expresion->identificador);
        fflush(stdout);
        printf("%s", CARACTER_SALTO_LINEA);
        fflush(stdout);
      }

    } else {
      printf("%s   + Separador ignorado", CARACTER_SALTO_LINEA);
      fflush(stdout);
    }
  } while (
    !cadena_nula(linea) &&
    !cadenas_iguales(linea, SEPARADOR_VALIDACIONES)
  );

  if (cadena_nula(linea)) {
    printf("%sERROR: Cierre de seccion de Validaciones no definida", CARACTER_SALTO_LINEA);
    fflush(stdout);
    return NULL;
  }

  printf("%s%s", CARACTER_SALTO_LINEA, CARACTER_SALTO_LINEA);
  fflush(stdout);

  return linea;
}
