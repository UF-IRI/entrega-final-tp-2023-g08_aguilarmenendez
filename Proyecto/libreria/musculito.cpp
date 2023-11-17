#include <fstream>
#include <sstream>
#include "musculito.h"
#include <iostream>


eBusCliente BuscarCliente (std:: fstream& infileclientes, const sCliente ClienteBuscado )
{
        infileclientes.seekg(0, std::ios::end);  // Mover el puntero al final del archivo
        std::streampos length = infileclientes.tellg();  // Obtener la posición actual del puntero (tamaño del archivo)
        infileclientes.seekg(0, std::ios::beg);  // Mover el puntero al principio del archivo

        // Verificar si el archivo está vacío
        if (length == 0) {
            return eBusCliente::NoExisteCliente;
        }

        sCliente clienteActual;

        // Recorre el archivo leyendo los datos de cada cliente
        while (infileclientes >> clienteActual.idCliente >> clienteActual.nombre >> clienteActual.apellido >> clienteActual.email
          >> clienteActual.telefono >> clienteActual.fechaNac >> clienteActual.estado) {
            if ((clienteActual.nombre == ClienteBuscado.nombre && clienteActual.apellido == ClienteBuscado.apellido) || clienteActual.email == ClienteBuscado.email) {
                // El cliente buscado existe en el archivo
                return eBusCliente::ExisteCliente;
            }
        }

        // Cliente no encontrado en el archivo
        return eBusCliente::NoExisteCliente;
    }

int idCliente(std:: fstream& infileclientes, const sCliente ClienteBuscado)
    {
        eBusCliente resultadoBusqueda = BuscarCliente(infileclientes, ClienteBuscado);

        if (resultadoBusqueda == eBusCliente::ExisteCliente) {
            sCliente clienteActual;
            while (infileclientes >> clienteActual.email >> clienteActual.idCliente >> clienteActual.nombre >> clienteActual.apellido
                   >> clienteActual.telefono >> clienteActual.fechaNac >> clienteActual.estado) {
                if ((clienteActual.nombre == ClienteBuscado.nombre && clienteActual.apellido == ClienteBuscado.apellido) ||
                    clienteActual.email == ClienteBuscado.email) {
                    return clienteActual.idCliente;
                }
            }
        } else if (resultadoBusqueda == eBusCliente::NoExisteCliente) {
            return 0;
        }

        return 0;  // Por si no se cumple ninguna condición.
}


eEstado estadoCuota (std:: fstream& infileclientes, sCliente ClienteBuscado)
{
        sCliente clienteActual;
        int posicion = -1;

        while (infileclientes >> clienteActual.email >> clienteActual.idCliente >> clienteActual.nombre >> clienteActual.apellido
               >> clienteActual.telefono >> clienteActual.fechaNac >> clienteActual.estado) {
            if (clienteActual.idCliente == ClienteBuscado.idCliente) {
                posicion = 0;
                break;  // No necesitas seguir leyendo el archivo si encontraste el cliente
            }
        }

        if (posicion != -1) {
            if (clienteActual.estado == 0) {
                return eEstado::alDia;
            } else if (clienteActual.estado < 0) {
                return eEstado::Deuda;
            } else {
                return eEstado::aFavor;
            }
        } else {
            // Cliente no encontrado
            return eEstado::alDia;
        }
}

int verificarClase(std::fstream& infileclases, const sClases& claseBuscada) {
        sClases claseActual;
        int posicion = -1;

        infileclases.clear();  // Reiniciar el estado del archivo
        infileclases.seekg(0, std::ios::beg);  // Mover el puntero al principio del archivo

        std::string line;
        while (std::getline(infileclases, line)) {
            std::istringstream iss(line);
            if (iss >> claseActual.nombre >> claseActual.horario >> claseActual.idClase) {
                if (claseActual.nombre == claseBuscada.nombre && claseActual.horario == claseBuscada.horario) {
                    posicion = claseActual.idClase;
                    break;  // No necesitas seguir leyendo el archivo si encontraste la clase
                }
            }
        }

        if (posicion != -1) {
            return posicion;
        } else {
            // Clase no encontrada
            return NoExisteClase;
        }
}

int idClase(std::fstream& infileclases, const sClases& claseBuscada)
{
        int resultadoBusquedaClase = verificarClase(infileclases, claseBuscada);

        if (resultadoBusquedaClase != NoExisteClase)
        {
            return resultadoBusquedaClase;
        } else
        {
            return 0;
        }
}

// aas

int verificarSuperposicion(std::fstream& infileasistencias, const sClases& claseBuscada, unsigned int idCliente) {
        sAsistencia asistenciaActual;

        infileasistencias.clear();  // Reiniciar el estado del archivo
        infileasistencias.seekg(0, std::ios::beg);  // Mover el puntero al principio del archivo

        std::string line;
        while (getline(infileasistencias, line)) {
            std::istringstream iss(line);
            if (iss >> asistenciaActual.idCliente >> asistenciaActual.cantInscriptos) {
                asistenciaActual.CursosInscriptos = new sInscripcion[asistenciaActual.cantInscriptos];
                for (unsigned int i = 0; i < asistenciaActual.cantInscriptos; ++i) {
                    if (!(iss >> asistenciaActual.CursosInscriptos[i].idCurso >> asistenciaActual.CursosInscriptos[i].fechaInscripcion)) {
                        // Manejar un formato de archivo incorrecto
                        std::cout << "Error en el formato del archivo de asistencias.\n";
                        delete[] asistenciaActual.CursosInscriptos;  // Liberar la memoria asignada
                        return -1;
                    }
                }

                if (asistenciaActual.idCliente == idCliente) {
                    // Verificar superposición de horarios
                    for (unsigned int i = 0; i < asistenciaActual.cantInscriptos; ++i) {
                        const auto& inscripcion = asistenciaActual.CursosInscriptos[i];

                        // Modificar la llamada a verificarClase para pasar un objeto sClases
                        int idClaseExistente = verificarClase(infileasistencias, claseBuscada);

                        if (idClaseExistente != NoExisteClase && ExisteClase == inscripcion.idCurso) {
                            // Superposición de horarios
                            delete[] asistenciaActual.CursosInscriptos;  // Liberar la memoria asignada
                            return idClaseExistente;
                        }
                    }
                }

                delete[] asistenciaActual.CursosInscriptos;  // Liberar la memoria asignada
            }
        }

        // No hay superposición de horarios
        return NoExisteClase;
}

/* eAgrCliente agregarCliente ()
{

}
*/

int CantInscriptos(sAsistencia *AsistenciasGym, int idClase, int cantAsistencias) //cantAsistencias, contador del archivo binario
{
        int cantAsistencias=10;
        int cont=0;
        for(int i=0; i<cantAsistencias; i++)
        {
            for(int j=0; j<AsistenciasGym[i].cantInscriptos; j++)
            {
                if(AsistenciasGym[i].CursosInscriptos[j].idCurso == idClase)
                    cont++;
            }
        }
        return cont;
}


eCupos verificarCupos(sClases*misClases, int idClase, sAsistencia*AsistenciasGym, int cantClases)
{
        int cantClases = 10;
        str nombre;
        int contador = CantInscriptos(AsistenciasGym, idClase, cantAsistencias);
        for(int i=0; i<cantClases; i++)
        {
            if(misClases[i].idClase == idClase)
            {
                nombre = misClases[i].nombre;
            }
        }

        if(nombre=="Zumba"){
            if(contador<CupoMaxZumba)
                return eCupos::HayCupos;
            else
                return eCupos::NoHayCupos;
        }
        if(nombre=="Pilates"){
            if(contador<CupoMaxPilates)
                return eCupos::HayCupos;
            else
                return eCupos::NoHayCupos;
        }
        if(nombre=="Spinning"){
            if(contador<CupoMaxSpinning)
                return eCupos::HayCupos;
            else
                return eCupos::NoHayCupos;
        }
        if(nombre=="Yoga"){
            if(contador<CupoMaxYoga)
                return eCupos::HayCupos;
            else
                return eCupos::NoHayCupos;
        }
        if(nombre=="Boxeo"){
            if(contador<CupoMaxBoxeo)
                return eCupos::HayCupos;
            else
                return eCupos::NoHayCupos;
        }
        if(nombre=="Stretching"){
            if(contador<CupoMaxStretching)
                return eCupos::HayCupos;
            else
                return eCupos::NoHayCupos;
        }
}


