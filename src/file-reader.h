// Utilidades para la lectura de archivos
// @author: Jonathan Samines
// Universidad Mariano Galvez de Guatemala

#include "stream.h";
#include "string.h";

const PERMISOS_ARCHIVO = "r";

string leerArchivo(string nombreArchivo) {
  int c;
  FILE *descriptorArchivo;
  descriptorArchivo = fopen(nombreArchivo, PERMISOS_ARCHIVO);

  if (descriptorArchivo) {
      while ((c = fget(file)) != EOF)
          putchar(c);
      fclose(file);
  }

}
