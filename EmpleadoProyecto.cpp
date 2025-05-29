#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

//Clase principal
class Empleado {
public:
    string nombre;
    long long id;
    string puesto;
    string fechaContratacion;
    bool disponible;

    Empleado(string nombre, long long id, string puesto, string fechaContratacion, bool disponible = true)
        : nombre(nombre), id(id), puesto(puesto), fechaContratacion(fechaContratacion), disponible(disponible) {}

    virtual double calcularSalario() const = 0;
    virtual string tipoEmpleado() const = 0;
    virtual void generarReporte() const {
    cout << toString() << endl;
}

    virtual string toString() const {
        stringstream ss;
        ss << "Nombre: " << nombre << ", ID: " << id << ", Puesto: " << puesto << ", Fecha  de Contratacion: " << fechaContratacion   << ", Disponible: " << (disponible ? "Sí" : "No");;
        return ss.str();
    }

    //Modifica los detalles tipicos de un empleado
    virtual void modificarEmpleado(string nombre, string puesto, string fechaContratacion, bool disponible) {
        this->nombre = nombre;
        this->puesto = puesto;
        this->fechaContratacion = fechaContratacion;
        this->disponible = disponible;
    }
};

//Empleados a tiempo completo(Sub-clase)
class EmpleadoTiempoCompleto : public Empleado {
public:
    double salarioFijo;

    EmpleadoTiempoCompleto(string nombre, long long id, string puesto, string fechaContratacion, double salarioFijo, bool disponible = true)
        : Empleado(nombre, id, puesto, fechaContratacion, disponible), salarioFijo(salarioFijo) {}

    double calcularSalario() const override {
        return salarioFijo;
    }

    string tipoEmpleado() const override {
        return "TiempoCompleto";
    }

    string toString() const override {
        stringstream ss;
        ss << Empleado::toString() << ", Salario: " << salarioFijo;
        return ss.str();
    }

    // Modifica especificamente detalles de empleados a tiempo completo
  void modificarEmpleado(string nombre, string puesto, string fechaContratacion, bool disponible, double salarioFijo) {
    Empleado::modificarEmpleado(nombre, puesto, fechaContratacion, disponible);
    this->salarioFijo = salarioFijo;
}

};

//Empleados por hora(Sub-clase)
class EmpleadoPorHora : public Empleado {
public:
    double pagoPorHora;
    int horasTrabajadas;

    EmpleadoPorHora(string nombre, long long id, string puesto, string fechaContratacion, double pagoPorHora, int horasTrabajadas, bool disponible = true )
        : Empleado(nombre, id, puesto, fechaContratacion, disponible), pagoPorHora(pagoPorHora), horasTrabajadas(horasTrabajadas) {}

    double calcularSalario() const override {
        return pagoPorHora * horasTrabajadas;
    }

    string tipoEmpleado() const override {
        return "PorHora";
    }

    string toString() const override {
        stringstream ss;
        ss << Empleado::toString() << ", Pago por hora: " << pagoPorHora << ", Horas trabajadas: " << horasTrabajadas;
        return ss.str();
    }

    //Modifica especificamente deatlles de empleados por hora
    void modificarEmpleado(string nombre, string puesto, string fechaContratacion, bool disponible, double pagoPorHora, int horasTrabajadas) {
        Empleado::modificarEmpleado(nombre, puesto, fechaContratacion, disponible);
        this->pagoPorHora = pagoPorHora;
        this->horasTrabajadas = horasTrabajadas;
    }
};

//Nodo para lista enlazada
class Nodo {
public:
    shared_ptr<Empleado> empleado;
    Nodo* siguiente;

    Nodo(shared_ptr<Empleado> empleado) : empleado(empleado), siguiente(nullptr) {}
};

//Lista de empleados
class ListaEmpleados {
private:
    Nodo* cabeza;

public:
    ListaEmpleados() : cabeza(nullptr) {}

    void agregar(shared_ptr<Empleado> empleado) {
        Nodo* nuevo = new Nodo(empleado);
        if (!cabeza) {
            cabeza = nuevo;
        } else {
            Nodo* temp = cabeza;
            while (temp->siguiente) {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevo;
        }
    }
    

    void mostrar() const {
        if (!cabeza) {
            cout << "No hay empleados en la lista\n";
            return;
        }
        Nodo* actual = cabeza;
        cout << "Lista de Empleados:\n";
        while (actual) {
        cout << "• " << actual->empleado->nombre << endl; // Solo se imprime el nombre
        actual = actual->siguiente;
        }
    }


    shared_ptr<Empleado> buscarPorID(long long id) {
        Nodo* actual = cabeza;
        while (actual) {
            if (actual->empleado->id == id) {
                return actual->empleado;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

    void eliminar(shared_ptr<Empleado> empleado) {
        if (!cabeza) return;

        if (cabeza->empleado == empleado) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            return;
        }

        Nodo* actual = cabeza;
        while (actual->siguiente) {
            if (actual->siguiente->empleado == empleado) {
                Nodo* temp = actual->siguiente;
                actual->siguiente = actual->siguiente->siguiente;
                delete temp;
                return;
            }
            actual = actual->siguiente;
        }
    }
    
    
    //guarda los datos en un archivo txt
    void guardarEnArchivo(const string& archivo) const {
        ofstream archivoSalida(archivo);
        if (!archivoSalida.is_open()) {
            cerr << "Error al abrir el archivo\n";
            return;
        }

        Nodo* actual = cabeza;
        while (actual) {
            auto empleado = actual->empleado;
            archivoSalida << empleado->tipoEmpleado() << endl;
            archivoSalida << empleado->nombre << endl;
            archivoSalida << empleado->id << endl;
            archivoSalida << empleado->puesto << endl;
            archivoSalida << empleado->fechaContratacion << endl;

            if (empleado->tipoEmpleado() == "TiempoCompleto") {
                auto tiempoCompleto = dynamic_pointer_cast<EmpleadoTiempoCompleto>(empleado);
                archivoSalida << tiempoCompleto->salarioFijo << endl;
            } else if (empleado->tipoEmpleado() == "PorHora") {
                auto porHora = dynamic_pointer_cast<EmpleadoPorHora>(empleado);
                archivoSalida << porHora->pagoPorHora << endl;
                archivoSalida << porHora->horasTrabajadas << endl;
            }
            actual = actual->siguiente;
        }

        archivoSalida.close();
    }
    
    //carga los datos desde un archivo txt
    void cargarDesdeArchivo(const string& archivo) {
        ifstream archivoEntrada(archivo);
        if (!archivoEntrada.is_open()) {
            cerr << "Error al abrir el archivo\n";
            return;
        }

        string tipoEmpleado;
        while (getline(archivoEntrada, tipoEmpleado)) {
            string nombre, puesto, fechaContratacion;
            long long id;
            archivoEntrada >> nombre >> id >> puesto >> fechaContratacion;
            archivoEntrada.ignore();

            if (tipoEmpleado == "TiempoCompleto") {
                double salarioFijo;
                archivoEntrada >> salarioFijo;
                archivoEntrada.ignore();
                agregar(make_shared<EmpleadoTiempoCompleto>(nombre, id, puesto, fechaContratacion, salarioFijo));
            } else if (tipoEmpleado == "PorHora") {
                double tarifaPorHora;
                int horasTrabajadas;
                archivoEntrada >> tarifaPorHora >> horasTrabajadas;
                archivoEntrada.ignore();
                agregar(make_shared<EmpleadoPorHora>(nombre, id, puesto, fechaContratacion, tarifaPorHora, horasTrabajadas));
            }
        }

        archivoEntrada.close();
    }

    void ordenarPorSalario() {
    if (!cabeza || !cabeza->siguiente) {
        cout << "No hay empleados suficientes para ordenar la lista.\n";
        return;
    }

    Nodo* temp = cabeza;

    while (temp) {
        Nodo* min = temp;
        Nodo* r = temp->siguiente;

        while (r) {
            if (r->empleado->calcularSalario() < min->empleado->calcularSalario()) {
                min = r;
            }
            r = r->siguiente;
        }

        if (min != temp) {
            swap(temp->empleado, min->empleado);
        }
        temp = temp->siguiente;
    }
}


    //calcula el salario total entre todos los empleados
    double calcularSalarioTotal() const {
        double total = 0.0;
        Nodo* actual = cabeza;
        while (actual) {
            total += actual->empleado->calcularSalario();
            actual = actual->siguiente;
        }
        return total;
    }
    bool validarID(const string &id) {
        if (id.length()!= 12) {
            return false;
        }
        for (char c : id) {
            if (!isdigit(c)) {
                return false;
            }
        }
        return true;
    }

   void generarReporte() const {
    if (!cabeza) {
        cout << "No hay empleados para el reporte\n";
        return;
    }

    cout << "Reporte:\n";
    Nodo* actual = cabeza;
    while (actual) {
        actual->empleado->generarReporte();
        actual = actual->siguiente;
    }
}



};

//Menu
void menu() {
    ListaEmpleados lista;
    string archivo = "empleados.txt";
    lista.cargarDesdeArchivo(archivo);

    int opcion;
    do {
        cout << "\n   ------Gestión de Empleados------   \n";
        cout << "1. Agregar Empleado a Tiempo Completo\n";
        cout << "2. Agregar Empleado por Hora\n";
        cout << "3. Mostrar Empleados\n";
        cout << "4. Ordenar empleados por salario\n";
        cout << "5. Buscar Empleado por ID\n";
        cout << "6. Eliminar Empleado\n";
        cout << "7. Modificar Empleado\n";
        cout << "8. Calcular Salario Total\n";
        cout << "9. Generar Reporte de Empleados\n";
        cout << "10. Guardar Cambios\n";
        cout << "11. Salir\n";
        cout << "Elige una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                string nombre, puesto, fechaContratacion;
                double salarioFijo;
                long long id;
                cout << "Nombre: ";
                getline(cin, nombre);
                cout << "ID: ";
                cin >> id;
                if (id > 0) {
                    if (!lista.validarID(to_string(id))) {
                        cout << "ID invalido, asegurese que el ID esta escrito correctamente\n";
                        break;
                    }
                    if (lista.buscarPorID(id)) {
                        cout << "ID ya agregado, intentelo de nuevo\n";
                        break;
                    }
                } else {
                    cout << "ID invalido, asegurese que el ID esta escrito correctamente \n";
                    break;
                }
                cin.ignore();
                cout << "Puesto: ";
                getline(cin, puesto);
                cout << "Fecha de contratación: ";
                getline(cin, fechaContratacion);
                cout << "Salario Fijo: ";
                cin >> salarioFijo;
                lista.agregar(make_shared<EmpleadoTiempoCompleto>(nombre, id, puesto, fechaContratacion, salarioFijo));
                break;
            }
            case 2: {
                string nombre, puesto, fechaContratacion;
                long long id;
                double pagoPorHora;
                int horasTrabajadas;
                cout << "Nombre: ";
                getline(cin, nombre);
                cout << "ID: ";
                cin >> id;
                if (id > 0) {
                    if (!lista.validarID(to_string(id))) {
                        cout << "ID invalido, asegurese que el ID esta escrito correctamente\n";
                        break;
                    }
                    if (lista.buscarPorID(id)) {
                        cout << "ID ya agregado, intentelo de nuevo\n";
                        break;
                    }
                } else {
                    cout << "ID invalido, asegurese que el ID esta escrito correctamente\n";
                    break;
                }
                cin.ignore();
                cout << "Puesto: ";
                getline(cin, puesto);
                cout << "Fecha de contratación: ";
                getline(cin, fechaContratacion);
                cout << "Pago por hora: ";
                cin >> pagoPorHora;
                cout << "Horas trabajadas: ";
                cin >> horasTrabajadas;
                lista.agregar(make_shared<EmpleadoPorHora>(nombre, id, puesto, fechaContratacion, pagoPorHora, horasTrabajadas));
                break;
            }
            case 3:
                lista.mostrar();
                break;
            case 4:
                lista.ordenarPorSalario();
                lista.mostrar();
                break;
            case 5: {
                long long id;
                cout << "Ingresa ID del empleado a buscar: ";
                cin >> id;
                auto empleado = lista.buscarPorID(id);
                if (empleado) {
                    cout << empleado->toString() << endl;
                } else {
                    cout << "Empleado no encontrado\n";
                }
                break;
            }
            case 6: {
                long long id;
                cout << "Ingresa ID del empleado a eliminar: ";
                cin >> id;
                auto empleado = lista.buscarPorID(id);
                if (empleado) {
                    lista.eliminar(empleado);
                    cout << "Empleado eliminado\n";
                } else {
                    cout << "Empleado no encontrado\n";
                }
                break;
            }
            case 7: {
            long long id;
            cout << "Ingrese el ID del empleado que desea modificar: ";
            cin >> id;
            auto empleado = lista.buscarPorID(id);
                if (empleado) {
                string nombre, puesto, fechaContratacion;
                bool disponible;
                int opcionDisponible;
                cout << "Nuevo nombre: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Nuevo puesto: ";
                getline(cin, puesto);
                cout << "Nueva fecha de contratación: ";
                getline(cin, fechaContratacion);
                cout << "¿Empleado disponible? (1. Si, 2. No): ";
                cin >> opcionDisponible;
                disponible = (opcionDisponible == 1);
                    if (empleado->tipoEmpleado() == "TiempoCompleto") {
                    double salarioFijo;
                    cout << "Nuevo salario fijo: ";
                    cin >> salarioFijo;
                    dynamic_pointer_cast<EmpleadoTiempoCompleto>(empleado)->modificarEmpleado(nombre, puesto, fechaContratacion, disponible, salarioFijo);
                        } else if (empleado->tipoEmpleado() == "PorHora") {
                            double pagoPorHora;
                            int horasTrabajadas;
                            cout << "Nuevo pago por hora: ";
                            cin >> pagoPorHora;
                            cout << "Nuevas horas trabajadas: ";
                            cin >> horasTrabajadas;
                            dynamic_pointer_cast<EmpleadoPorHora>(empleado)->modificarEmpleado(nombre, puesto, fechaContratacion, disponible, pagoPorHora, horasTrabajadas);
                        }
                            cout << "Empleado actualizado\n";
                            } else {
                                cout << "Empleado no encontrado\n";
                            }
                             break;
            }
            case 8:
                cout << "Salario total de todos los empleados: " << lista.calcularSalarioTotal() << endl;
                break;
            case 9:
                lista.generarReporte();
                break;    
            case 10:
                lista.guardarEnArchivo(archivo);
                cout << "Cambios guardados\n";
                break;
            case 11:
                cout << "Ha salido del sistema correctamente\n";
                break;
            default:
                cout << "Opcion invalida, reintetelo por favor\n";
        }
    } while (opcion != 11);
}

int main() {
    menu();
    return 0;
}