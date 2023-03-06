# Registro de competidores en archivo binario

### Introducción
> La aplicación permitirá migrar los datos existentes de un archivo csv y realizar los nuevos registros en un archivo binario que se denominará "competidores.dat".

Este proyecto utiliza los siguientes conceptos:
- Structs
- Arrays
- Punteros
- Archivos texto
- Archivos binarios
- Ciclos
- Condicionales

## Funcionamiento

>Al ejecutar la aplicación aparecerá un menú de opciones

1. Listar txt: Emitir en pantalla en archivo de texto. Los datos de tiempo deben emitirse con 6 decimales en todos los casos.   
2. Crear: Crear un nuevo archivo binario.
3.  Migrar: Migra los datos del archivo csv al nuevo archivo agregando al campo "activo" = 1. 
4. Listar dat: Emitir en pantalla el contenido del archivo binario con sus respectivos títulos de columna, considerando:
    a. Dar a elegir al usuario listar todos. Listar todos (competidores activos e inactivos).
    b. Listar el campo de activos
    c. Ingresar por teclado de un país.
    d. Ingresar de un rango de tiempo (mínimo y máximo).
5. Generar alta: Registrar nuevos competidores, Se tiene que tener en cuenta que el número de orden siempre debe ser positivo e indicar la posición dónde se grabarán los datos en el archivo. 
6. Buscar: Los datos de un competidor: 
    a. Por el número de orden
    b. Por número de corredor
7. Modificar: La edad o el tiempo, buscando por el número de orden o número de corredor. 
8. Baja lógica: de un competidor buscando por su número de orden (acceso directo). Antes de dar 
la baja, el programa emite los datos y pedir confirmación.  
9. Baja física: elimina los competidores inactivos, para ello se construye un nuevo 
archivo binario ‘competidores_bajas_<fecha>.xyz’ en el que se grabarán sólo los datos de los 
que se han dado de baja, poniendo en 0 (cero) los campos de esos registros en el archivo 
original. El valor de fecha del nombre del archivo se construye y concatena con 
funciones de C que la obtengan del sistema.
10. Listar xyz: Listar el archivo construido en el paso anterior.
