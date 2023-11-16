#include "archivos.h"

str convertirString(float horario){
    int horas = static_cast <int>(horario);  //obtengo la parte entera
    int minutos = static_cast <int>((horario-horas)*60); //obtengo los minutos

    ostringstream ss; //creo un stringstream para formatear el horario

    if (horas < 10) {   //agrego las horas a la cadena
        ss << "0";      //agrego un cero si la hora es menor que 10
    }
    ss << ":";
    if(minutos < 10){   //agrego los minutos a la cadena
        ss <<"0";       // agrego cero si los minutos son menos que 10
    }
    ss << minutos;

    return ss.str();
}

string convertirIntAString(int estado) {
    return to_string(estado);
}

void leerArchivoClientes (ifstream&infileclientes)
{
    /*
    //MANERA QUE NOS ENSEÑARON EN CLASES
     str header;

    getline(infileclientes, header);

    while(infileclientes.good()){
        str line;
        getline (infileclientes,line);

        char delimiter= ',';
        str field;

        stringstream iss;
        iss<<line;

        while (getline (iss, field, delimiter))
        {
            cout << field << " ";
        }
        cout << endl;
    }
*/

    sCliente *misClientes = nullptr; //creo array dinamico
    int numClientes = 0;
    int i=0;
    string n;

    string linea;
    while (getline(infileclientes, linea)){    //lee el archivo CSV line ppor linea
        std :: istringstream ss(linea);
        string campo;

        sCliente cliente;                           //Divide la linea en campos utilizando comas como delimitadores
        getline (ss, campo, ',');
        cliente.idCliente = stoi(campo);
        getline (ss, cliente.nombre, ',');
        getline (ss, cliente.apellido, ',');
        getline (ss, cliente.email, ',');
        getline (ss, cliente.telefono, ',');
        getline (ss, cliente.fechaNac, ',');
        getline(ss, campo, ',');
        cliente.estado = stoi(campo);


        sCliente *tempArrayClientes = new sCliente[numClientes + 1];        // Aumenta el tamaño del array dinámico y agrega la clase
        std::copy(misClientes, misClientes + numClientes, tempArrayClientes);
        tempArrayClientes[numClientes] = cliente;

        delete[] misClientes;
        misClientes = tempArrayClientes;
        ++numClientes;

    }
    infileclientes.close();   // Cierra el archivo CSV

    for (int i = 0; i < numClientes; ++i) {              // Ahora puedes trabajar con el array dinámico, por ejemplo, imprimir los datos

        cout << "ID: " << misClientes[i].idCliente << ", Nombre: " << misClientes[i].nombre << ", Apellido: " << misClientes[i].apellido << ", Email: " << misClientes[i].email << ", Telefono: " << misClientes[i].telefono << ", Fecha de nacimiento: " << misClientes[i].fechaNac  << endl;
    }

    delete[] misClientes;   // Recuerda liberar la memoria cuando ya no la necesitas

    return;
}

void leerArchivoClases (ifstream &infileclases)
{
    //MANERA QUE NOS ENSEÑARON EN CLASES
    /*str header;

    getline(infileclases, header);

    while(infileclases.good()){
        str line;
        getline (infileclases,line);

        char delimiter= ',';
        str field;

        stringstream iss;
        iss<<line;

        while (getline (iss, field, delimiter))
        {
            cout << field << " ";
        }
        cout << endl;
    }*/

    sClases *misClases = nullptr; //creo array dinamico
    int numClases = 0;
    int i=0;
    string n;

    string linea;
    while (getline(infileclases, linea)){    //lee el archivo CSV line ppor linea
        std :: istringstream ss(linea);
        string campo;

        sClases clase;                           //Divide la linea en campos utilizando comas como delimitadores
        getline (ss, campo, ',');
        clase.idClase = stoi(campo);
        getline (ss, clase.nombre, ',');
        getline (ss, n, ',');
        clase.horario = stof(n);


        sClases *tempArrayClases = new sClases[numClases + 1];        // Aumenta el tamaño del array dinámico y agrega la clase
        std::copy(misClases, misClases + numClases, tempArrayClases);
        tempArrayClases[numClases] = clase;

        delete[] misClases;
        misClases = tempArrayClases;
        ++numClases;

    }
    infileclases.close();   // Cierra el archivo CSV

    for (int i = 0; i < numClases; ++i) {              // Ahora puedes trabajar con el array dinámico, por ejemplo, imprimir los datos

        cout << "ID: " << misClases[i].idClase << ", Nombre: " << misClases[i].nombre << ", Horario: " << misClases[i].horario << std::endl;
    }

    delete[] misClases;   // Recuerda liberar la memoria cuando ya no la necesitas

    return;
}

void leerArchivoAsistencias (ifstream infileasistencias)
{
   /* str header;

    getline(*infileasistencias, header);

    while(infileasistencias->good()){
        str line;
        getline (*infileasistencias,line);

        char delimiter= ',';
        str field;

        stringstream iss;
        iss<<line;

        while (getline (iss, field, delimiter))
        {
            cout << field << " ";
        }
        cout << endl;
    } */

    char buffer [1024];
    while (infileasistencias.good())
    {
        infileasistencias.read (buffer, sizeof(buffer));
    }
    infileasistencias.close ();

    ofstream outfileasistencias ("asistencias_1697673600000.dat", ios::binary);
    /*if (!outfileasistencias.is_open)
    {
        cout << "Error abriendo el archivo binario" << endl;
        return;
    }*/

    char data[] = "Estas es la data binaria.";
    outfileasistencias.write(data, sizeof (data));
    outfileasistencias.close();
    return ;
}

void resizeclientes(sCliente** misClientes, u_int *tam)
{
    (*tam) = *(tam)+1;  //incremento el contador de tamaño
    sCliente*aux = new sCliente[*(tam)]; // creo un auxiliar memoria dinamica

    for(u_int i=0; i< (*tam)-1; i++)
    {
        aux[i] = (*misClientes)[i]; //copio todas las cosas del array al nuevo array auxiliar
    }
    delete[]*misClientes; //borro el array
    *misClientes = aux; //asigno la nueva direccion al nuevo array
}



