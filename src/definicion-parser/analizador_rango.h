// Analiza expresiones definidas mediante rangos
// definidos mediante expresiones del tipo: [a-z, A-Z]
// @author: Jonathan Samines
// Universidad Mariano Galvez de Guatemala

char* SEPARADOR_CADENA_RANGO_LISTA = ",";
char* SEPARADOR_CADENA_RANGO_EXPANSION = "-";

struct ExpansionRango {
  char desde;
  char hasta;

  struct ExpansionRango* siguienteNodo;
};

struct ExpansionRango* expandir_rango(char* rango) {
  char* final_expansion;
  char* desde = strtok_r(rango, SEPARADOR_CADENA_RANGO_EXPANSION, &final_expansion);
  char* hasta = strtok_r(NULL, SEPARADOR_CADENA_RANGO_EXPANSION, &final_expansion);
  char* restante = strtok_r(NULL, SEPARADOR_CADENA_RANGO_EXPANSION, &final_expansion);

  if (!cadena_nula(restante) || cadena_nula(desde) || cadena_nula(hasta)) {
    return NULL;
  }

  struct ExpansionRango* expansion;

  expansion->desde = *desde;
  expansion->hasta = *hasta;
  expansion->siguienteNodo = NULL;

  return expansion;
}

struct ExpansionRango* crear_rangos(char* rangos) {
  char* final_lista;
  struct ExpansionRango* raiz_expansion;
  char* rango = strtok_r(rangos, SEPARADOR_CADENA_RANGO_LISTA, &final_lista);

  while (!cadena_nula(rango)){
    struct ExpansionRango* expansion = expandir_rango(rango);

    if (expansion == NULL) {
      return NULL;
    }

    raiz_expansion = expansion;
    raiz_expansion->siguienteNodo = expansion;

    rango = strtok_r(NULL, SEPARADOR_CADENA_RANGO_LISTA, &final_lista);
  }

  raiz_expansion->siguienteNodo = NULL;

  return raiz_expansion;
}
