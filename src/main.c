// Entrypoint de la aplicación
// @author: Jonathan Samines
// Compiladores
// Universidad Mariano Galvez de Guatemala

#include <stdio.h>
#include "lector_archivos.h"
#include "utilidades_cadena.h"
#include "definicion_parser.h"

const char* nombre_archivo = "./definiciones/definicion.lang.test";

int main() {
  char* contenido_archivo = leer_contenido_archivo(nombre_archivo);
  analizar_definicion(contenido_archivo);

  // printf("El contenido: %s", lineas);

  return 0;
}
