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

void leerArchivoClientes (ifstream &infileclientes);
void leerArchivoClases (ifstream &infileclases);
void leerArchivoAsistencias (ifstream*infileasistencias);
int tamArrayClientes(sCliente*misClientes);
void resizeclientes(sCliente **misClientes, u_int *tam);

str convertirString (float horario);

#endif // ARCHIVOS_H
