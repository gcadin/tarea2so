#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <filesystem>
#include <thread>

using namespace cv;
using namespace std;
using namespace filesystem;

// Función que aplica el filtro a una sección de la imagen
void aplicar_filtro_paralelo(Mat &imagen, int inicio_y, int fin_y) {
    for (int y = inicio_y; y < fin_y; ++y) {
        for (int x = 0; x < imagen.cols; ++x) {
            Vec3b pixel = imagen.at<Vec3b>(y, x);
            // Convertimos el pixel a escala de grises
            int gris = 0.21 * pixel[2] + 0.72 * pixel[1] + 0.07 * pixel[0];
            imagen.at<Vec3b>(y, x) = Vec3b(gris, gris, gris);
        }
    }
}

int main(int argc, char* argv[]) {
    Mat imagen;
    int numero_hebras = 0;

    // Verificamos si se han proporcionado los argumentos necesarios
    if (argc < 4) {
        cout << "Uso: ./proceso_paralelo imagen_entrada.jpg imagen_salida.png numero_hebras" << endl;
        return -1;
    }

    // Nombre de los archivos de entrada y salida y número de hebras
    string nombre_imagen_entrada = argv[1];
    string nombre_imagen_salida = argv[2];
    numero_hebras = atoi(argv[3]);

    

    // Rutas de los archivos de entrada y salida
    path ruta_imagen_entrada = current_path() / nombre_imagen_entrada;
    path ruta_imagen_salida = current_path() / nombre_imagen_salida;

    // Validamos que el archivo de entrada exista
    if (!exists(ruta_imagen_entrada)) {
        cout << "El archivo de entrada no se ha encontrado" << endl;
        return -1;
    }

    // Cargamos la imagen
    imagen = imread(ruta_imagen_entrada.string());

    //Declaración hebras
    thread hebras[numero_hebras];

    auto inicio = chrono::high_resolution_clock::now();
    cout << "Inicio de la conversión en paralelo... " << endl;

    // División de la imagen por hebras
    int filas_por_hebra = imagen.rows/numero_hebras;
    int inicio_y = 0;

    for (int i = 0; i < numero_hebras; ++i) {
        int fin_y;
        if (i == numero_hebras - 1) {
            fin_y = imagen.rows;
        } else {
            fin_y = inicio_y + filas_por_hebra;
        }

        hebras[i] = thread(aplicar_filtro_paralelo, ref(imagen), inicio_y, fin_y);
        inicio_y = fin_y;
    }

    // Esperar a que todas las hebras terminen su trabajo
    for (int i = 0; i < numero_hebras; ++i) {
        hebras[i].join();
    }

    cout << "Fin de la conversión en paralelo... " << endl;
    auto fin = chrono::high_resolution_clock::now();

    // Medición del tiempo transcurrido
    chrono::duration<double> tiempo = fin - inicio;
    cout << "Tiempo empleado: " << tiempo.count() << " segundos" << endl;

    // Guardar imagen en escala de grises
    imwrite(ruta_imagen_salida.string(), imagen);

    return 0;
}