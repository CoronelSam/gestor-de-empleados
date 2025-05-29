# Sistema de Gestión de Empleados en C++

Este proyecto es una aplicación de consola en C++ para la gestión de empleados, permitiendo agregar, modificar, eliminar, buscar y listar empleados a tiempo completo y por hora. Los datos se guardan y cargan desde un archivo de texto.

## Estructura del proyecto

- `Empleado.hpp` / `Empleado.cpp`: Clase base abstracta para empleados.
- `EmpleadoTiempoCompleto.hpp` / `EmpleadoTiempoCompleto.cpp`: Clase para empleados a tiempo completo.
- `EmpleadoPorHora.hpp` / `EmpleadoPorHora.cpp`: Clase para empleados por hora.
- `ListaEmpleados.hpp` / `ListaEmpleados.cpp`: Lista enlazada para gestionar empleados.
- `main.cpp`: Contiene el menú principal y la función `main`.
- `empleados.txt`: Archivo donde se guardan los datos de los empleados (se crea automáticamente).
- `README.md`: Este archivo.

## Cómo compilar

Abre una terminal en la carpeta del proyecto y ejecuta:

```sh
g++ -std=c++17 main.cpp Empleado.cpp EmpleadoTiempoCompleto.cpp EmpleadoPorHora.cpp ListaEmpleados.cpp -o empleados
```

## Cómo ejecutar

En la terminal, ejecuta:

```sh
./empleados
```

## Uso

Sigue el menú interactivo para agregar, modificar, eliminar, buscar y listar empleados.  
Los datos se guardan automáticamente en `empleados.txt` cuando eliges la opción de guardar.

## Notas

- Puedes modificar y mejorar el código según tus necesidades.
- Si tienes dudas, revisa los comentarios en el código fuente.

---
