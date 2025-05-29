#include "ListaEmpleados.hpp"
#include "EmpleadoTiempoCompleto.hpp"
#include "EmpleadoPorHora.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>

Nodo::Nodo(std::shared_ptr<Empleado> empleado) : empleado(empleado), siguiente(nullptr) {}

ListaEmpleados::ListaEmpleados() : cabeza(nullptr) {}

ListaEmpleados::~ListaEmpleados() {
    while (cabeza) {
        Nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

void ListaEmpleados::agregar(std::shared_ptr<Empleado> empleado) {
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

void ListaEmpleados::mostrar() const {
    if (!cabeza) {
        std::cout << "No hay empleados en la lista\n";
        return;
    }
    Nodo* actual = cabeza;
    std::cout << "Lista de Empleados:\n";
    while (actual) {
        std::cout << "• " << actual->empleado->nombre << std::endl;
        actual = actual->siguiente;
    }
}

std::shared_ptr<Empleado> ListaEmpleados::buscarPorID(long long id) {
    Nodo* actual = cabeza;
    while (actual) {
        if (actual->empleado->id == id) {
            return actual->empleado;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

void ListaEmpleados::eliminar(std::shared_ptr<Empleado> empleado) {
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

void ListaEmpleados::guardarEnArchivo(const std::string& archivo) const {
    std::ofstream archivoSalida(archivo);
    if (!archivoSalida.is_open()) {
        std::cerr << "Error al abrir el archivo\n";
        return;
    }

    Nodo* actual = cabeza;
    while (actual) {
        auto empleado = actual->empleado;
        archivoSalida << empleado->tipoEmpleado() << std::endl;
        archivoSalida << empleado->nombre << std::endl;
        archivoSalida << empleado->id << std::endl;
        archivoSalida << empleado->puesto << std::endl;
        archivoSalida << empleado->fechaContratacion << std::endl;

        if (empleado->tipoEmpleado() == "TiempoCompleto") {
            auto tiempoCompleto = std::dynamic_pointer_cast<EmpleadoTiempoCompleto>(empleado);
            archivoSalida << tiempoCompleto->salarioFijo << std::endl;
        } else if (empleado->tipoEmpleado() == "PorHora") {
            auto porHora = std::dynamic_pointer_cast<EmpleadoPorHora>(empleado);
            archivoSalida << porHora->pagoPorHora << std::endl;
            archivoSalida << porHora->horasTrabajadas << std::endl;
        }
        actual = actual->siguiente;
    }

    archivoSalida.close();
}

void ListaEmpleados::cargarDesdeArchivo(const std::string& archivo) {
    std::ifstream archivoEntrada(archivo);
    if (!archivoEntrada.is_open()) {
        std::cerr << "Error al abrir el archivo\n";
        return;
    }

    std::string tipoEmpleado;
    while (getline(archivoEntrada, tipoEmpleado)) {
        std::string nombre, puesto, fechaContratacion;
        long long id;
        getline(archivoEntrada, nombre);
        archivoEntrada >> id;
        archivoEntrada.ignore();
        getline(archivoEntrada, puesto);
        getline(archivoEntrada, fechaContratacion);

        if (tipoEmpleado == "TiempoCompleto") {
            double salarioFijo;
            archivoEntrada >> salarioFijo;
            archivoEntrada.ignore();
            agregar(std::make_shared<EmpleadoTiempoCompleto>(nombre, id, puesto, fechaContratacion, salarioFijo));
        } else if (tipoEmpleado == "PorHora") {
            double tarifaPorHora;
            int horasTrabajadas;
            archivoEntrada >> tarifaPorHora >> horasTrabajadas;
            archivoEntrada.ignore();
            agregar(std::make_shared<EmpleadoPorHora>(nombre, id, puesto, fechaContratacion, tarifaPorHora, horasTrabajadas));
        }
    }

    archivoEntrada.close();
}

void ListaEmpleados::ordenarPorSalario() {
    if (!cabeza || !cabeza->siguiente) {
        std::cout << "No hay empleados suficientes para ordenar la lista.\n";
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
            std::swap(temp->empleado, min->empleado);
        }
        temp = temp->siguiente;
    }
}

double ListaEmpleados::calcularSalarioTotal() const {
    double total = 0.0;
    Nodo* actual = cabeza;
    while (actual) {
        total += actual->empleado->calcularSalario();
        actual = actual->siguiente;
    }
    return total;
}

bool ListaEmpleados::validarID(const std::string &id) {
    if (id.length() != 12) {
        return false;
    }
    for (char c : id) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

void ListaEmpleados::generarReporte() const {
    if (!cabeza) {
        std::cout << "No hay empleados para el reporte\n";
        return;
    }

    std::cout << "Reporte:\n";
    Nodo* actual = cabeza;
    while (actual) {
        actual->empleado->generarReporte();
        actual = actual->siguiente;
    }
}