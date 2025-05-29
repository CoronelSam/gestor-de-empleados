#pragma once
#include "Empleado.hpp"

class EmpleadoPorHora : public Empleado {
public:
    double pagoPorHora;
    int horasTrabajadas;

    EmpleadoPorHora(std::string nombre, long long id, std::string puesto, std::string fechaContratacion, double pagoPorHora, int horasTrabajadas, bool disponible = true);

    double calcularSalario() const override;
    std::string tipoEmpleado() const override;
    std::string toString() const override;
    void modificarEmpleado(std::string nombre, std::string puesto, std::string fechaContratacion, bool disponible, double pagoPorHora, int horasTrabajadas);
};