#pragma once
#include <memory>
#include <string>
#include "Empleado.hpp"

class Nodo {
public:
    std::shared_ptr<Empleado> empleado;
    Nodo* siguiente;

    Nodo(std::shared_ptr<Empleado> empleado);
};

class ListaEmpleados {
private:
    Nodo* cabeza;

public:
    ListaEmpleados();
    ~ListaEmpleados();

    void agregar(std::shared_ptr<Empleado> empleado);
    void mostrar() const;
    std::shared_ptr<Empleado> buscarPorID(long long id);
    void eliminar(std::shared_ptr<Empleado> empleado);
    void guardarEnArchivo(const std::string& archivo) const;
    void cargarDesdeArchivo(const std::string& archivo);
    void ordenarPorSalario();
    double calcularSalarioTotal() const;
    bool validarID(const std::string &id);
    void generarReporte() const;
};