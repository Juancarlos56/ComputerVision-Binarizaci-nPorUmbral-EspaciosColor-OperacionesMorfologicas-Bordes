
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <opencv2/core/core.hpp> // Contiene los elementos base de OpenCV (matrices, arreglos, etc.)
#include <opencv2/highgui/highgui.hpp> // Contiene estructuras para crear la interfaz gráfica
#include <opencv2/imgproc/imgproc.hpp> // Procesamiento de imágenes
#include <opencv2/imgcodecs/imgcodecs.hpp> // Códecs para leer determinados formatos de imágenes
#include <opencv2/video/video.hpp> // Procesamiento y escritura
#include <opencv2/videoio/videoio.hpp> // de video
using namespace std;
using namespace cv; // El espacio de nombres donde están definidas algunas funciones de OpenCV

class EspacioColor
{
private:
    int minCanal1 = 44, minCanal2 = 50, minCanal3 = 57;
    int maxCanal1 = 98, maxCanal2 = 255, maxCanal3 = 255;
    int tipoEspacioColor = 1;


public:

    //Funcion para voltear frame
    Mat voltearHorizantalImagen(Mat frame, int ancho, int alto);
    
    //Funciones para deteccion de bordes
    Mat filtroBordeCanny(Mat frame, int thres, int kernel);
    Mat filtroBordeLaplace(Mat frame, int kernel);

    //Funciones para aplicar filtros filtros de suavizado
    Mat filtoMedianBlur(Mat image, int valorMascara);
    Mat filtoBlur(Mat image, int valorMascara);
    Mat filtoGaussBlur(Mat image, int valorMascara, double sigmaDecimal);

    //Fucniones para aplicar funciones morfologicas
    Mat funErosion(Mat imagen, Mat elemento);
    Mat funDilatacion(Mat imagen, Mat elemento);
    Mat funTophat(Mat imagen, Mat elemento);
    Mat funBlackhat(Mat imagen, Mat elemento);
    Mat funCombinado(Mat imagen, Mat imagenTH, Mat imagenBH);
    Mat funCierre(Mat imagen, Mat elemento);
    Mat funApertura(Mat imagen, Mat elemento);

    //FUnciones para cambio de espacio de color
    Mat cambioEspacioColorGRAY(Mat frame);
    Mat cambioEspacioColorHSV(Mat frame);
    Mat cambioEspacioColorCielab(Mat frame);
    Mat cambioEspacioColorColorYCrCb(Mat frame);

    //Funcion para maximos-minimos de los espacios de color
    Mat maximosMinimosEspacioColor(Mat frame, int minCanal1, int minCanal2, int minCanal3, int maxCanal1, int maxCanal2, int maxCanal3);

    //Funcion para obtener la degada de una imagen
    Mat negadaDeFrame(Mat frame);

    //Funcion para colocar fondo dentro de una imagen
    Mat colocarFondoFrameSobreCamara(Mat umbralizada, Mat negada, Mat frame, Mat fondo);
    Mat colocarFondoPantallaSobreCamara(Mat negada, Mat fondo, Mat frame);
    
    int getMinCanal1() const{ return minCanal1;};
    int getMinCanal2() const{ return minCanal2;};
    int getMinCanal3() const{ return minCanal3;};
    int getMaxCanal1() const{ return maxCanal1;};
    int getMaxCanal2() const{ return maxCanal2;};
    int getMaxCanal3() const{ return maxCanal3;};

    void setMinCanal1(int* valor){ minCanal1 = *valor;};
    void setMinCanal2(int* valor) { minCanal2 = *valor;};
    void setMinCanal3(int* valor) { minCanal3 = *valor;};
    void setMaxCanal1(int* valor) { maxCanal1 = *valor;};
    void setMaxCanal2(int* valor) { maxCanal2 = *valor;};
    void setMaxCanal3(int* valor) { maxCanal3 = *valor;};
    
    int getTipoEspacioColor() const{ return tipoEspacioColor;};
    void setTipoEspacioColor(int valor) { tipoEspacioColor = valor;};


};


