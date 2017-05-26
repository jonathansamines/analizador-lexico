// Analiza expresiones simples de la forma:
// IDENTIFICADOR := [VALOR] | 'VALOR'
// En donde IDENTIFICADOR es una secuencia de caracteres simple
// y VALOR puede ser una cadena simple o un rango(s)
// @author: Jonathan Samines
// Universidad Mariano Galvez de Guatemala

#ifndef _ANALIZADOR_EXPRESION_
  #define _ANALIZADOR_EXPRESION_

  char* CARACTER_ASIGNACION_EXPRESION = ":=";
  char* CARACTER_CADENA_SIMPLE = "'";
  char* CARACTER_RANGO_INICIO = "[";
  char* CARACTER_RANGO_FIN = "]";

  struct ExpresionValor {
    char* cadena;
    struct ExpansionRango* rango;
  };

  struct Expresion {
    char* identificador;
    struct ExpresionValor* valor;
  };

  struct ExpresionValor* crear_valor_expresion(char* valor_cadena) {
    struct ExpresionValor* valor_expresion;
    int indice_inicio;
    int indice_fin;

    // cadenas simples
    indice_inicio = indiceDe(valor_cadena, CARACTER_CADENA_SIMPLE, 0);

    if (indice_inicio == 0) {
      indice_fin = indiceDe(valor_cadena, CARACTER_CADENA_SIMPLE, indice_inicio + 1);

      if (indice_fin != -1) {

        // es una cadena simple
        char cadena[indice_fin - indice_inicio];
        substraer(valor_cadena, indice_inicio + 1, indice_fin - indice_inicio - 1, cadena);

        valor_expresion->cadena = cadena;

        return valor_expresion;
      }

      return NULL;
    }

    // rangos
    indice_inicio = indiceDe(valor_cadena, CARACTER_RANGO_INICIO, 0);

    if (indice_inicio == 0) {
      indice_fin = indiceDe(valor_cadena, CARACTER_RANGO_FIN, indice_inicio + 1);

      if (indice_fin != -1) {
        // es una cadena simple
        char cadena[indice_fin - indice_inicio];
        substraer(valor_cadena, indice_inicio + 1, indice_fin - indice_inicio - 1, cadena);

        struct ExpansionRango* expansion = crear_rangos(cadena);

        valor_expresion->rango = expansion;

        return valor_expresion;
      }

      return NULL;
    }

    return NULL;
  }

  struct Expresion* crear_definicion_expresion(char* linea) {
    char* final_expresion;
    char* identificador_expresion = strtok_r(linea, CARACTER_ASIGNACION_EXPRESION, &final_expresion);
    char* valor_cadena = strtok_r(NULL, CARACTER_ASIGNACION_EXPRESION, &final_expresion);

    if (cadena_nula(valor_cadena)) return NULL;

    struct ExpresionValor* valor_expresion = crear_valor_expresion(eliminar_espacios(valor_cadena));

    if (valor_expresion != NULL) {
      struct Expresion* expresion;

      expresion->identificador = eliminar_espacios(identificador_expresion);
      expresion->valor = valor_expresion;

      return expresion;
    }

    return NULL;
  }
#endif
