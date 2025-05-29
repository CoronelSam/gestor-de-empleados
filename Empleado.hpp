#pragma once
#include <string>
#include <sstream>
#include <iostream>

class Empleado {
public:
    std::string nombre;
    long long id;
    std::string puesto;
    std::string fechaContratacion;
    bool disponible;

    Empleado(std::string nombre, long long id, std::string puesto, std::string fechaContratacion, bool disponible = true);
    virtual ~Empleado() = default;

    virtual double calcularSalario() const = 0;
    virtual std::string tipoEmpleado() const = 0;
    virtual void generarReporte() const;
    virtual std::string toString() const;
    virtual void modificarEmpleado(std::string nombre, std::string puesto, std::string fechaContratacion, bool disponible);
};