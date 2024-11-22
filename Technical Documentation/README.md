# Notas

En esta prueba se planteaban crear 3 módulos.

Los 3 módulos deben implementar una interfaz única IModule.

Cuando se crea un proyecto de varias librerías y módulos cada uno debe ser independiente por lo que plantea el ejercicio es una pésima idea de arquitectura inclusive para una prueba técnica.

IModule debería ser al módulo centrar que use otros módulos como tal.


En es implementación se ha creado 3 librerías de principales:

- Data Generator:  Módulo que genera los datos de forma aleatoria.
- Search Engine:   Módulo que busca los datos dados.
- Printing Engine: Módulo que muestra por pantalla la los datos.

Luego de eso se ha crear el Módulo planteado por el ejecicio `IModule`.

`IModule` hace uso de los 3 módulos principales y gestiona toda la generación de datos de forma asincrona en base a los Hilos soportados por el sistema operativo de forma paralela si es posible.

# Compiladores Soportados

- GCC 11.2.0 como mínimo usando C++20
- Clang una versión que soporte C++20
- CL.exe una versión que soporte C++20
- CMake 3.22 como mínimo
