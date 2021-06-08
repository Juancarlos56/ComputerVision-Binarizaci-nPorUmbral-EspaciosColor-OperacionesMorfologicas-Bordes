

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "Cabecera.hpp"

// Librerías de OpenCV

//#include <opencv2/opencv.hpp>


using namespace std;

using namespace cv; // El espacio de nombres donde están definidas algunas funciones de OpenCV

//variable para opcion de tipo de filtro de suavizado
int opcionFiltro = 2;
//variable para opcion de tipo de filtro de bordes
int opcionFiltroBordes = 2;
//variable para opcion de tipo de operacion morfologica
int opcionFiltroMorfologico = 7;
//Varible para verificacion  de frame
int opcionModificacionFrame = 0;
//Varible para eleccion de video
int opcionVideoFondo = 0;


//Variable para eleccion de espacio de color
int centro = 0;
//Varaible para valor de mascara por defecto 11
int valorMascara = 11;
//Varaible para valor de mascara para operaciones morfologicas por defecto 11
int valorMascaraMorfologica = 37;
//Variable para mascara de deteccion de bordes
int valorMascaraBorde = 3;
//Variable para filtro gaussino
double sigmaDecimal = 0.1;

//Variable para filtro canny
int thres = 150;

//Valores para barras de desplazamiento, con valores por defecto
int min0 = 61, min1 = 54, min2 = 77;
int max0 = 101, max1 = 138, max2 = 182;



int main(int argc, char *argv[]){
    
    //Llamada a la clase EspacioColor
    EspacioColor espacioColorProyecto;
    Mat frameSinNada;

    //Video para la parte trasera 
    Mat fondo;
    //Llamada para guardar las iamgenes en espacio de color seleccionado
    Mat frame;
    Mat gray;
    Mat hsv;
    Mat cielab;
    Mat YCrCb;

    //Frame para cambios realizados sobre original
    Mat frameMejoradoImagen;
    //Video despues de aplicar mejoras en el video original
    Mat imgFinal;

    //Imagenes para deteccion umbralizacion y su opuesta 
    Mat umbralizada;
    Mat negada;

    //video almacenado aplicando filtro de la mediana
    Mat frameMedian;
    //video almacenado aplicando filtro de gauss
    Mat frameGauss;
    //video almacenado aplicando filtro de suavizado
    Mat frameSuavizado;
    
    
    //Videos para almacenar los distintos tipos de deteccion de bordes 
    //Deteccion de bordes mediante Laplace
    Mat imgLaplace;
    Mat laplaceEscala;
    
    //Deteccion de bordes mediante Canny
    Mat canny;

    //Frame para deteccion de bordes
    Mat frameDeteccionBordes;

    //Elemento para aplicacion de erocion o dilatacion con mascara
    Mat elemento0;

    //FRame para aplicacion de operaciones morfologicas
    Mat frameOperacionesMorfologicas;
    
    const char *videosSRC[3] = {"./MovingCar.mp4", "./VideoAutoGenial.mp4", "./canada.mp4"};

    //Captura de webcam
    VideoCapture videoWebCam(0);
    

    if (videoWebCam.isOpened()){

        //Ventana para mostrar video original
        namedWindow("Video Original", WINDOW_NORMAL);
        //Ventana para mostrar video original
        namedWindow("Video sin fondo", WINDOW_AUTOSIZE);
        //Ventana con imagen posicionada
        namedWindow("Video con Fondo", WINDOW_AUTOSIZE);
        //Ventana para imagen Umbralizada
        //namedWindow("Umbralizada", WINDOW_AUTOSIZE);
        //Ventana con cambios en la imagen original
        namedWindow("Imagen Con Mejoras", WINDOW_AUTOSIZE);
        
        
        //Barra de desplazamiento para eleccion de espacio de color
        createTrackbar("0.RGB, 1.HSV, 2.LAB, 3.YCrCb","Video Original",&centro, 3, NULL);
        //Barra de desplzamiento para modificacion de imagen
        createTrackbar("0.Sin modificar, 1.Modificar Frame","Video Original",&opcionModificacionFrame, 1, NULL);
        //Barra de desplazamiento para eleccion de espacio de color
        createTrackbar("0.Filtro Mediana, 1.Filtro Gauss, 2.Nada","Video Original",&opcionFiltro, 2, NULL);
        //Trackbar para tamanio de mascara del 1-30 para filtro de la mediana
        createTrackbar("Mascara para tipo de filtro de Suavizado","Video Original",&valorMascara, 30, NULL);
        //Trackbar para filtro de deteccion de bordes
        createTrackbar("0.Laplace, 1.Canny, 2.Nada","Video Original",&opcionFiltroBordes, 2, NULL);
        //Trackbar para filtro de deteccion de bordes
        createTrackbar("Mascara para tipo de filtro de bordes","Video Original",&valorMascaraBorde, 8, NULL);
        //Trackbar para filtro de deteccion de bordes
        createTrackbar("0.Erosion, 1.Dilatacion, 2.Top Hat, 3.Black Hat \n4.Combinado, 5.Cierre, 6.Apertura, 7.Nada","Video Original",&opcionFiltroMorfologico, 7, NULL);
        //Trackbar para tamanio de mascara del 1-30 para operacion morfologicas
        createTrackbar("Mascara para operaciones morfologicas","Video Original",&valorMascaraMorfologica, 50, NULL);
        //Trackbar para eleccion de muestra de video
        createTrackbar("0.Seguir, 1.Terminar","Video Original",&opcionVideoFondo, 1, NULL);

        //Barras de desplazmamiento para eleccion de colores maximos y minimos de cada canal o espacio de color
        createTrackbar("Min-0","Video Original", &min0, 180, NULL);
        createTrackbar("Min-1","Video Original",&min1, 255, NULL);
        createTrackbar("Min-2","Video Original",&min2, 255, NULL);

        createTrackbar("Max-0","Video Original", &max0, 180, NULL);
        createTrackbar("Max-1","Video Original", &max1, 255, NULL);
        createTrackbar("Max-2","Video Original", &max2, 255, NULL);
        
        //Lectura de video almacenado
        //VideoCapture videoFondo("./MovingCar.mp4");
        int contador = 0;
        while(5==5){
            
            //Contador para reinicio de videos
            if(contador > 2){
                contador = 0;
            }

            if(opcionVideoFondo == 1){
                break;
            }
            //Apertura de videos
            VideoCapture videoFondo(videosSRC[contador]);
            contador++;

            while(3==3){
            
                videoWebCam >> frame;
                videoFondo >> fondo;

                if(opcionVideoFondo == 1){
                    break;
                }
                

                if(frame.empty()){
                    break;
                }

                //Verificacion de que el video se mantenga reproduciendo
                if(fondo.empty()||frame.rows==0 || frame.cols==0){
                    break;
                    
                }else{
                    //Voltear imagen
                    flip(frame, frame, 1);

                    //Redimencionamiento de videos 
                    frame = espacioColorProyecto.voltearHorizantalImagen(frame, 640, 480);
                    fondo = espacioColorProyecto.voltearHorizantalImagen(fondo, 640, 480);
                    //cv::resize(frame, frame, Size(640, 480), 1, 1);
                    //cv::resize(fondo, fondo, Size(640, 480), 1, 1);
                    
                    if(opcionModificacionFrame == 1){

                    
                        //Cambio de espacio de color a grises
                        gray = espacioColorProyecto.cambioEspacioColorGRAY(frame);
                        //cvtColor(frame, gray, COLOR_BGR2GRAY);

                        if(opcionFiltro == 1){

                            if(valorMascara%2!=0 && valorMascara>0){
                                frameGauss = espacioColorProyecto.filtoGaussBlur(gray, valorMascara, sigmaDecimal);
                                frameSuavizado = frameGauss;
                            }else{
                                frameGauss = espacioColorProyecto.filtoGaussBlur(gray, 11, sigmaDecimal);
                                frameSuavizado = frameGauss;
                            }

                        }else if(opcionFiltro == 0){
                            
                            if(valorMascara%2!=0 && valorMascara>0){
                                frameMedian = espacioColorProyecto.filtoMedianBlur(gray, valorMascara);
                                frameSuavizado = frameMedian;
                            }else{
                                frameMedian = espacioColorProyecto.filtoMedianBlur(gray, 11);
                                frameSuavizado = frameMedian;
                            }

                        }else{
                            frameSuavizado = gray;
                        }

                        //FIltros para deteccion de bordes
                        if(opcionFiltroBordes == 0){
                            
                            laplaceEscala = espacioColorProyecto.filtroBordeLaplace(frameSuavizado, valorMascaraBorde);
                            cv::absdiff( laplaceEscala, gray, frameDeteccionBordes );
                        
                        }else if(opcionFiltroBordes == 1){ 

                            canny = espacioColorProyecto.filtroBordeCanny(frameSuavizado, thres, valorMascaraBorde);
                            cv::absdiff( canny, gray, frameDeteccionBordes );
                        
                        }else{
                            cv::absdiff( gray, gray, frameDeteccionBordes );
                            
                        }

                        //Retornar a imagen RGB
                        cvtColor(frameDeteccionBordes, frameDeteccionBordes, COLOR_GRAY2BGR);
                        //Se suma las imagenes para ver las diferencias de aplicacion de los filtros
                        cv::absdiff( frame, frameDeteccionBordes, frameMejoradoImagen);

                        //Actualizacion del elemento para funciones morfologicas
                        elemento0 = getStructuringElement(MORPH_CROSS, Size(valorMascaraMorfologica, valorMascaraMorfologica));

                        if(opcionFiltroMorfologico == 0){
                            
                            frameOperacionesMorfologicas = espacioColorProyecto.funErosion(frameMejoradoImagen, elemento0);

                        }else if(opcionFiltroMorfologico ==1){
                            
                            frameOperacionesMorfologicas = espacioColorProyecto.funDilatacion(frameMejoradoImagen, elemento0);
                        
                        }else if(opcionFiltroMorfologico ==2){
                            
                            frameOperacionesMorfologicas = espacioColorProyecto.funTophat(frameMejoradoImagen, elemento0);
                        
                        }else if(opcionFiltroMorfologico ==3){
                            
                            frameOperacionesMorfologicas = espacioColorProyecto.funBlackhat(frameMejoradoImagen, elemento0);
                        
                        }else if(opcionFiltroMorfologico ==4){
                            
                            Mat topHAT = espacioColorProyecto.funTophat(frameMejoradoImagen, elemento0);
                            Mat blackHAT = espacioColorProyecto.funBlackhat(frameMejoradoImagen, elemento0);
                            frameOperacionesMorfologicas = espacioColorProyecto.funCombinado(frameMejoradoImagen, topHAT, blackHAT);
                        
                        }else if(opcionFiltroMorfologico ==5){
                            
                            frameOperacionesMorfologicas = espacioColorProyecto.funCierre(frameMejoradoImagen, elemento0);
                        
                        }else if(opcionFiltroMorfologico ==6){
                            
                            frameOperacionesMorfologicas = espacioColorProyecto.funApertura(frameMejoradoImagen, elemento0);
                        
                        }else{
                            frameOperacionesMorfologicas = frameMejoradoImagen;
                        }
                        imgFinal = frameOperacionesMorfologicas;
                        cv::imshow("Imagen Con Mejoras", imgFinal);
                    }else{
                        imgFinal = frame;
                    }

                    
                    
                

                    if (centro == 0){
                        umbralizada = espacioColorProyecto.maximosMinimosEspacioColor(imgFinal, min0, min1, min2, max0, max1, max2);

                    }else if (centro == 1){
                        
                        hsv = espacioColorProyecto.cambioEspacioColorHSV(imgFinal);
                        umbralizada = espacioColorProyecto.maximosMinimosEspacioColor(hsv, min0, min1, min2, max0, max1, max2);
                        //cv::inRange(hsv, Scalar(min0, min1, min2), Scalar(max0, max1, max2), umbralizada);
                    
                    }else if (centro == 2){
                        
                        cielab = espacioColorProyecto.cambioEspacioColorCielab(imgFinal);
                        umbralizada = espacioColorProyecto.maximosMinimosEspacioColor(cielab, min0, min1, min2, max0, max1, max2);
                        //cv::inRange(cielab, Scalar(min0, min1, min2), Scalar(max0, max1, max2), umbralizada);
                    
                    }else if (centro == 3){
                        
                        YCrCb = espacioColorProyecto.cambioEspacioColorColorYCrCb(imgFinal);
                        umbralizada = espacioColorProyecto.maximosMinimosEspacioColor(YCrCb, min0, min1, min2, max0, max1, max2);
                        //cv::inRange(YCrCb, Scalar(min0, min1, min2), Scalar(max0, max1, max2), umbralizada);
                    }

                    negada = espacioColorProyecto.negadaDeFrame(umbralizada);
                    //fondo = espacioColorProyecto.colocarFondoFrameSobreCamara(umbralizada, negada, frame, fondo);
                    fondo = espacioColorProyecto.colocarFondoPantallaSobreCamara(negada, fondo, frame);
                    //cv::imshow("Video Original", frameSinNada);
                    cv::imshow("Video sin fondo", frame);
                    //cv::imshow("Umbralizada", umbralizada);
                    cv::imshow("Video Negado", negada);
                    cv::imshow("Video con Fondo", fondo);

                    if (waitKey(23)==27){
                        break;
                    }
                }
                
                

            
            }

            
        }
        
        
        videoWebCam.release();

        cv::destroyAllWindows();
    }

    return 0;
}





