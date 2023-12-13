Compilación

Opción 1) Ejecutando el comando make, se ejecutará las instrucciones 
señaladas en el archivo Makefile que se encuentra en esta carpeta

Opcion 2) g++ secuencial.cpp -o secuencial `pkg-config --cflags --libs opencv4`

Utilización
El programa recibe 2 argumentos de entrada, siendo el nombre de la imagen a procesar, 
y el nombre con el que se guardará la imagen en blanco y negro, el archivo de imagen 
debe encontrarse en esta misma carpeta

Ejemplo de ejecución:

./secuencial imagen.jpg imagen_gris.jpg