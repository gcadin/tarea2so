#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <filesystem>

using namespace cv;
using namespace std;
using namespace filesystem;

//Aplicamos filtro a la imagen
void aplicar_filtro(Mat &imagen) {
    for (int y = 0; y < imagen.rows; ++y) {
        for (int x = 0; x < imagen.cols; ++x) {
            Vec3b pixel = imagen.at<Vec3b>(y, x);
            int gris = 0.21 * pixel[2] + 0.72 * pixel[1] + 0.07 * pixel[0];
            imagen.at<Vec3b>(y, x) = Vec3b(gris, gris, gris);
        }
    }
}

//Validamos que el archivo de imagen se encuentra en la ruta señalada
void validar_imagen(path ruta_imagen_entrada) {
    if (!exists(ruta_imagen_entrada)) {
        cout << "El archivo no se ha encontrado" << endl;
        exit(-1);
    }
}

//Guardamos la imagen en la ruta de salida
void guardar_imagen(path ruta_imagen_salida, Mat &imagen) {
    imwrite(ruta_imagen_salida.string(),imagen);
}


int main(int argc, char* argv[]) {
    //Declaramos variables
    Mat imagen;
    
    //Advertencia mal ingreso de parametros
    if (argc < 3) {
        cout << "Uso: ./secuencial imagen_entrada imagen_salida" << endl;
        return -1;
    }

    //Asignamos nombres de entrada y salida
    string nombre_imagen_entrada = argv[1];
    string nombre_imagen_salida = argv[2];

    //asignamos rutas de entrada y salida de la imagen
    path ruta_imagen_entrada = current_path() / nombre_imagen_entrada;
    path ruta_imagen_salida = current_path() / nombre_imagen_salida;

    //validamos que el archivo exista en la ruta señalada
    validar_imagen(ruta_imagen_entrada);

    //Cargamos la imagen en la matriz imagen
    imagen = imread(ruta_imagen_entrada.string());

    //Iniciamos cronometro para medir tiempo de conversión
    auto inicio = chrono::high_resolution_clock::now();
    cout << "Inicio conversión... " << endl;

    //Aplicamos filtro
    aplicar_filtro(imagen);

    cout << "Fin conversión... " << endl;
    //Finalizamos el cronometro
    auto fin = chrono::high_resolution_clock::now();

    //Calculamos tiempo empleado
    chrono::duration<double> tiempo = fin - inicio;
    cout << "Tiempo empleado " << tiempo.count() << " segundos" << endl;

    //Guardamos imagen generada en escala de grises
    guardar_imagen(ruta_imagen_salida, imagen);

    return 0;
}