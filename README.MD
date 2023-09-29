#**GESTOR DE INFORMACION TURISTICA EN C**


Esta aplicacion permite la gestion de puntos de interes turistico y de turistas en consola utilizando hash maps y listas.


##**COMO COMPILAR Y EJECUTAR EL PROGRAMA**


1. Clonar el repositorio:

   *git clone https://github.com/Totox01/Tarea-2-Estructura-de-datos-Gestion-Turistica*
   
2. Navegar hasta el directorio del protecto:

   *cd Tarea-2-Estructura-de-datos-Gestion-Turistica*
   
3. Compilar el codigo:

   *gcc main.c list.c hashmap.c -o GestorTuristico*

4. Ejecutar la aplicacion

   *./GestorTuristico*


##**FUNCIONALIDADES**


1. Registrar un punto de interés
2. Mostrar un punto de interes
3. Eliminar un punto de interes
4. Registrar un turista
5. Agregar un lugar favorito a un turista
6. Mostrar todos los turistas de un pais determinado
7. Mostrar lugares por tipo (Parque, Museo, Atraccion turistica, etc...)
8. Importar todos los puntos desde un archivo CSV
9. Exportar todos los puntos a un archivo CSV
10. Importar todos los turistas desde un archivo CSV
11. Exportar todos los turistas a un archivo CSV


###**PROBLEMAS CONOCIDOS CON LAS FUNCIONALIDADES**


*La aplicacion no verifica el tamaño de los strings ingresados por lo que ingresar strings de mayor largo que los indicados en la estructura lleva a errores de ejecucion.


###**FUNCIONES A MEJORAR**


* Automatizar el proceso de identificacion de los archivos en las funciones Importar y Exportar
* Verificar correctamente el tamaño de los strings ingresados en las funciones de registro para que no superen los 100 caracteres


##**CONTRIBUCIONES**


Javier Montoya:
-Diseño inicial de las funciones del codigo.
-Creación de la interfaz de usuario.
-Autoevaluacion: (3)Aporte excelente.

Ricardo Santana:
-Documentacion y comentarios del codigo.
-Correccion de la logica del codigo.
-Correccion de errores en el codigo.
-Diseño y redaccion del README.
-Autoevaluacion: (3)Aporte excelente.