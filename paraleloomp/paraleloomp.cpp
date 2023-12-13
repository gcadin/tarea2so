#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <omp.h>

using namespace cv;
using namespace std;

// Función que aplica el filtro a una sección de la imagen
void aplicar_filtro_paralelo(Mat &imagen, int numero_hebras) {
    int filas_por_hebra = imagen.rows/numero_hebras;

    #pragma omp parallel num_threads(numero_hebras)
    {
        //Asignación de filas a procesar por "thread"
        int thread_id = omp_get_thread_num();
        int inicio_y = thread_id * filas_por_hebra;
        int fin_y = (thread_id + 1) * filas_por_hebra;

        //Comprobación ultimo hilo
        if (thread_id == numero_hebras - 1) {
            fin_y = imagen.rows; 
        }

        //Aplicación del filtro
        for (int y = inicio_y; y < fin_y; ++y) {
            for (int x = 0; x < imagen.cols; ++x) {
                Vec3b pixel = imagen.at<Vec3b>(y, x);
                int gris = 0.21 * pixel[2] + 0.72 * pixel[1] + 0.07 * pixel[0];
                imagen.at<Vec3b>(y, x) = Vec3b(gris, gris, gris);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    Mat imagen;
    int numero_hebras;

    // Verificamos si se han proporcionado los argumentos necesarios
    if (argc < 4) {
        cout << "Uso: ./proceso_paralelo imagen_entrada.jpg imagen_salida.png numero_hebras" << endl;
        return -1;
    }

    // Nombre de los archivos de entrada y salida y número de hebras
    string nombre_imagen_entrada = argv[1];
    string nombre_imagen_salida = argv[2];
    numero_hebras = atoi(argv[3]);

    // Cargamos la imagen
    imagen = imread(nombre_imagen_entrada);

    if (imagen.empty()) {
        cout << "No se pudo cargar la imagen." << endl;
        return -1;
    }

    //Inicio cronometro
    auto inicio = chrono::high_resolution_clock::now();
    cout << "Inicio de la conversión en paralelo... " << endl;

    aplicar_filtro_paralelo(imagen, numero_hebras);
    
    //Fin cronometro
    cout << "Fin de la conversión en paralelo... " << endl;
    auto fin = chrono::high_resolution_clock::now();

    // Medición del tiempo transcurrido
    chrono::duration<double> tiempo = fin - inicio;
    cout << "Tiempo empleado: " << tiempo.count() << " segundos" << endl;

    // Guardar imagen en escala de grises
    imwrite(nombre_imagen_salida, imagen);

    return 0;
}