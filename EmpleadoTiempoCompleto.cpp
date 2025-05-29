#include "EmpleadoTiempoCompleto.hpp"
#include <sstream>

EmpleadoTiempoCompleto::EmpleadoTiempoCompleto(std::string nombre, long long id, std::string puesto, std::string fechaContratacion, double salarioFijo, bool disponible)
    : Empleado(nombre, id, puesto, fechaContratacion, disponible), salarioFijo(salarioFijo) {}

double EmpleadoTiempoCompleto::calcularSalario() const {
    return salarioFijo;
}

std::string EmpleadoTiempoCompleto::tipoEmpleado() const {
    return "TiempoCompleto";
}

std::string EmpleadoTiempoCompleto::toString() const {
    std::stringstream ss;
    ss << Empleado::toString() << ", Salario: " << salarioFijo;
    return ss.str();
}

void EmpleadoTiempoCompleto::modificarEmpleado(std::string nombre, std::string puesto, std::string fechaContratacion, bool disponible, double salarioFijo) {
    Empleado::modificarEmpleado(nombre, puesto, fechaContratacion, disponible);
    this->salarioFijo = salarioFijo;
}