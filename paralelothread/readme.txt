Compilación

Opción 1) Ejecutando el comando make, se ejecutará las instrucciones 
señaladas en el archivo Makefile que se encuentra en esta carpeta

Opcion 2) g++ paralelothread.cpp -o paralelothread `pkg-config --cflags --libs opencv4` -pthread

Utilización
El programa recibe 3 argumentos de entrada, siendo el nombre de la imagen a procesar, 
el nombre con el que se guardará la imagen en blanco y negro, y el número de hebras para la conversión, 
el archivo de imagen debe encontrarse en esta misma carpeta

Ejemplo de ejecución:

./paralelothread imagen.jpg imagen_gris.jpg 8