#include "Empleado.hpp"

Empleado::Empleado(std::string nombre, long long id, std::string puesto, std::string fechaContratacion, bool disponible)
    : nombre(nombre), id(id), puesto(puesto), fechaContratacion(fechaContratacion), disponible(disponible) {}

void Empleado::generarReporte() const {
    std::cout << toString() << std::endl;
}

std::string Empleado::toString() const {
    std::stringstream ss;
    ss << "Nombre: " << nombre << ", ID: " << id << ", Puesto: " << puesto
       << ", Fecha  de Contratacion: " << fechaContratacion
       << ", Disponible: " << (disponible ? "Sí" : "No");
    return ss.str();
}

void Empleado::modificarEmpleado(std::string nombre, std::string puesto, std::string fechaContratacion, bool disponible) {
    this->nombre = nombre;
    this->puesto = puesto;
    this->fechaContratacion = fechaContratacion;
    this->disponible = disponible;
}