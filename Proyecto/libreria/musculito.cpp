#include <fstream>
#include <sstream>
#include "musculito.h"

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


/* eAgrCliente agregarCliente ()
{

}

eSuperposicion verificarSuperposicion()
{

}

eCupos verificarCupos()
{

}

*/
