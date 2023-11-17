#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "clientes.h"
#include "clases.h"

using namespace std;

typedef enum codArchivos{ErrorApertura=-1, ErrorEscritura=0, ExitoOperacion=1} eCodArchivos;

enum ArchivoA { Error = -1, Exito = 1 };
typedef ArchivoA eArchivoA;

void leerArchivoClientes (ifstream &infileclientes);
void leerArchivoClases (ifstream &infileclases);
void leerArchivoAsistencias (ifstream*infileasistencias);
int tamArrayClientes(sCliente*misClientes);
void resizeclientes(sCliente **misClientes, u_int *tam);
eArchivoA leerArchivoAsistencias(ifstream &infileasistencias, Asistencia *asistencias);

str convertirString (float horario);
// hola hello bonjour

#endif // ARCHIVOS_H
