#include "EmpleadoPorHora.hpp"
#include <sstream>

EmpleadoPorHora::EmpleadoPorHora(std::string nombre, long long id, std::string puesto, std::string fechaContratacion, double pagoPorHora, int horasTrabajadas, bool disponible)
    : Empleado(nombre, id, puesto, fechaContratacion, disponible), pagoPorHora(pagoPorHora), horasTrabajadas(horasTrabajadas) {}

double EmpleadoPorHora::calcularSalario() const {
    return pagoPorHora * horasTrabajadas;
}

std::string EmpleadoPorHora::tipoEmpleado() const {
    return "PorHora";
}

std::string EmpleadoPorHora::toString() const {
    std::stringstream ss;
    ss << Empleado::toString() << ", Pago por hora: " << pagoPorHora << ", Horas trabajadas: " << horasTrabajadas;
    return ss.str();
}

void EmpleadoPorHora::modificarEmpleado(std::string nombre, std::string puesto, std::string fechaContratacion, bool disponible, double pagoPorHora, int horasTrabajadas) {
    Empleado::modificarEmpleado(nombre, puesto, fechaContratacion, disponible);
    this->pagoPorHora = pagoPorHora;
    this->horasTrabajadas = horasTrabajadas;
}