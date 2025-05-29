#include "ListaEmpleados.hpp"
#include "EmpleadoTiempoCompleto.hpp"
#include "EmpleadoPorHora.hpp"
#include <iostream>
#include <memory>
#include <limits>

using namespace std;

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