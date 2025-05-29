#pragma once
#include "Empleado.hpp"

class EmpleadoTiempoCompleto : public Empleado {
public:
    double salarioFijo;

    EmpleadoTiempoCompleto(std::string nombre, long long id, std::string puesto, std::string fechaContratacion, double salarioFijo, bool disponible = true);

    double calcularSalario() const override;
    std::string tipoEmpleado() const override;
    std::string toString() const override;
    void modificarEmpleado(std::string nombre, std::string puesto, std::string fechaContratacion, bool disponible, double salarioFijo);
};