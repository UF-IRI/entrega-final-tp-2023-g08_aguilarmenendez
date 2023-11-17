#ifndef MUSCULITO_H
#define MUSCULITO_H

#include "clientes.h"
#include "clases.h"
#include "musculacion.h"
#define CupoMaxZumba 50
#define CupoMaxYoga 25
#define CupoMaxSpinning 45
#define CupoMaxStretching 40
#define CupoMaxBoxeo 30
#define CupoMaxPilates 15

const sCliente ClienteNulo = { 0 , " ", " ", " ", " ", {0,0,0}, 0};

enum busCliente {ExisteCliente =1, NoExisteCliente =-1};
typedef busCliente eBusCliente;

enum agrCliente {ErrAgrCliente = -1, ExitoAgrCliente = 1};
typedef agrCliente eAgrCliente;

enum estado {Deuda = -1, alDia = 0 , aFavor = 1};
typedef estado eEstado;

enum Superposicion {HaySuperposicion = 1, NoHaySuperposicion = -1};
typedef Superposicion eSuperposicion;

enum Cupos {HayCupos = 1, NoHayCupos = -1};
typedef Cupos eCupos;

enum tipoClase {Spinning = 1, Yoga, Pilates, Stretching, Zumba, Boxeo, Musculacion};
typedef tipoClase eTipoClase;


typedef struct
{
    u_int idCurso;
    time_t fechaInscripcion;
} sInscripcion;

typedef struct
{
    u_int idCliente, cantInscriptos;
    sInscripcion* CursosInscriptos;
} sAsistencia;

/*OTRAS FUNCIONES*/

/*FUNCIONES DE CLASES*/
eTipoClase nombreClase(std:: fstream& infileclases);
int verificarClase(std::fstream& infileclases, const sClases& claseBuscada);
int idClase(std::fstream& infileclases, const sClases& claseBuscada);
const int NoExisteClase = -1;
const int ExisteClase= 1;

/*FUNCIONES DE CLIENTES*/
eBusCliente BuscarCliente (std:: fstream& infileclientes, const sCliente ClienteBuscado);
int idCliente(std:: fstream& infileclientes, const sCliente ClienteBuscado);
eEstado estadoCuota (std:: fstream& infileclientes, sCliente ClienteBuscado);
int verificarSuperposicion(std::fstream& asistenciasFile, const sClases& claseBuscada, unsigned int idCliente);
int CantInscriptos(sAsistencia*AsistenciasGym, int idClase, int cantAsistencias);
eCupos verificarCupos(sClase*misClases, int idClase, sAsistencia*AsistenciasGym, int cantClases);











#endif // MUSCULITO_H
