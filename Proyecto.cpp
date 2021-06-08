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

#include "Cabecera.hpp"

using namespace std;
using namespace cv; // El espacio de nombres donde están definidas algunas funciones de OpenCV
//using namespace cv;

//Funcion para voltear frame
Mat EspacioColor::voltearHorizantalImagen(Mat frame, int ancho, int alto){
    cv::resize(frame, frame, Size(ancho, alto), 1, 1);
    return frame;
}

Mat EspacioColor::filtroBordeLaplace(Mat frame, int kernel){
    Mat imgLaplace;
    Mat laplaceEscala;
    if(kernel%2!=0 && kernel>0){
        Laplacian(frame, imgLaplace, CV_16S, kernel);
        convertScaleAbs(imgLaplace, laplaceEscala);
    }else{
        Laplacian(frame, imgLaplace, CV_16S, 5);
        convertScaleAbs(imgLaplace, laplaceEscala);
    }
    
    return laplaceEscala;
}
Mat EspacioColor::filtroBordeCanny(Mat frame, int thres, int kernel){
    Mat canny;
    if(kernel%2!=0 && kernel>0){
        Canny(frame, canny, thres, thres*3, kernel);
    }else{
        Canny(frame, canny, thres, thres*3, 5);
    }
    
    return canny;
}


//Funcion para aplicacion de media en una imagen
Mat EspacioColor::filtoMedianBlur(Mat image, int valorMascara){
    Mat desImage;
    if(valorMascara%2!=0 && valorMascara>0){
        medianBlur(image, desImage, valorMascara);
    }
    return desImage;
}

Mat EspacioColor::filtoBlur(Mat image, int valorMascara){
    Mat desImage;
    if(valorMascara%2!=0 && valorMascara>0){
        blur(image, desImage, Size(valorMascara, valorMascara), Point(-1,-1));
    }
    return desImage;
}

Mat EspacioColor::filtoGaussBlur(Mat image, int valorMascara, double sigmaDecimal){
    Mat desImage;
    if(valorMascara%2!=0 && valorMascara>0){
        GaussianBlur(image,desImage,Size(valorMascara, valorMascara), sigmaDecimal, sigmaDecimal);
    }
    return desImage;
}

//Funcion para erosionar una imagen
Mat EspacioColor::funErosion(Mat imagen, Mat elemento){
    Mat imgResultado;
    morphologyEx(imagen, imgResultado, MORPH_ERODE, elemento);
    return imgResultado;
}

//Funcion para dilatacion de imagen
Mat EspacioColor::funDilatacion(Mat imagen, Mat elemento){
    Mat imgResultado;
    morphologyEx(imagen, imgResultado, MORPH_DILATE, elemento);
    return imgResultado;
}

//FUncion para tophat en una imagen
Mat EspacioColor::funTophat(Mat imagen, Mat elemento){
    Mat imgResultado;
    morphologyEx(imagen, imgResultado, MORPH_DILATE, elemento);
    return imgResultado;
}

//FUncion para black hat en una imagen
Mat EspacioColor::funBlackhat(Mat imagen, Mat elemento){
    Mat imgResultado;
    morphologyEx(imagen, imgResultado, MORPH_DILATE, elemento);
    return imgResultado;
}

//FUncion para tophat y black hat en imagen
Mat EspacioColor::funCombinado(Mat imagen, Mat imagenTH, Mat imagenBH){
    Mat imgResultado = imagen +(imagenTH-imagenBH);
    return imgResultado;
}

//FUncion para tophat y black hat en imagen
Mat EspacioColor::funCierre(Mat imagen, Mat elemento){
    Mat imgResultado;
    morphologyEx(imagen, imgResultado, MORPH_CLOSE, elemento);
    return imgResultado;
}

//FUncion para tophat y black hat en imagen
Mat EspacioColor::funApertura(Mat imagen, Mat elemento){
    Mat imgResultado;
    morphologyEx(imagen, imgResultado, MORPH_OPEN, elemento);
    return imgResultado;
}

Mat EspacioColor::cambioEspacioColorGRAY(Mat frame){
    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    return gray;
}

Mat EspacioColor::cambioEspacioColorHSV(Mat frame){
    Mat hsv;
    cvtColor(frame, hsv, COLOR_BGR2HSV);
    return hsv;
}


Mat EspacioColor::cambioEspacioColorCielab(Mat frame){
    Mat cielab;
    cvtColor(frame, cielab, COLOR_BGR2Lab);
    return cielab;
}

Mat EspacioColor::cambioEspacioColorColorYCrCb(Mat frame){ 
    Mat YCrCb;
    cvtColor(frame, YCrCb, COLOR_BGR2YCrCb);
    return YCrCb;
}


Mat EspacioColor::maximosMinimosEspacioColor(Mat frame, int minCanal0, int minCanal1, int minCanal2, 
                                int maxCanal0, int maxCanal1, int maxCanal2)
{
    Mat umbralizada;
    cv::inRange(frame, Scalar(minCanal0, minCanal1, minCanal2), Scalar(maxCanal0, maxCanal1, maxCanal2), umbralizada);
    return umbralizada;
}

Mat EspacioColor::negadaDeFrame(Mat frame){
    Mat negada;
    bitwise_not(frame, negada);
    return negada;
}

Mat EspacioColor::colocarFondoPantallaSobreCamara(Mat negada, Mat fondo, Mat frame){
    Mat fondoConCamara = fondo;
    for(int i=0;i<negada.rows;i++){
        for(int j=0;j<negada.cols;j++){
            if((int)negada.at<uchar>(i,j) == 255) {
                fondoConCamara.at<Vec3b>(i,j) = fondo.at<Vec3b>(i,j);
            }else{
                fondoConCamara.at<Vec3b>(i,j) = frame.at<Vec3b>(i,j);
            }
        }
    }
    return fondoConCamara;
}

Mat EspacioColor::colocarFondoFrameSobreCamara(Mat umbralizada, Mat negada, Mat frame, Mat fondo){
    //Vectores tridimensionales para sobremontar imagen sobre videos
    Vec3b voxel;
    Vec3b voxel1;

    for(int i=0;i<frame.rows;i++){
        for(int j=0;j<frame.cols;j++){
            voxel = fondo.at<Vec3b>(i,j);
            voxel1 = frame.at<Vec3b>(i,j);
            voxel[0] *= (int)(umbralizada.at<uchar>(i,j))/255;
            voxel[1] *= (int)(umbralizada.at<uchar>(i,j))/255;
            voxel[2] *= (int)(umbralizada.at<uchar>(i,j))/255;


            voxel1[0] *= ((int)negada.at<uchar>(i,j))/255;
            voxel1[1] *= ((int)negada.at<uchar>(i,j))/255;
            voxel1[2] *= ((int)negada.at<uchar>(i,j))/255;
            if(voxel[0]==0 && voxel[1]==0 && voxel[2]==0) {
                voxel[0] = voxel1[0];
                voxel[1] = voxel1[1];
                voxel[2] = voxel1[2];
            }        			
            fondo.at<Vec3b>(i,j)=voxel;
        }        	
    }
    return fondo;
}