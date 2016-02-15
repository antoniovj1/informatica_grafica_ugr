#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include "objetos.h"
#include "vertex.h"

//Variables para el cambio de objeto y visualizacion;
char modo;
char tipo;
//Las figuras son objetod globales para que no se
//tengan que construir continuamente
Cubo cubo(3);
Piramide piramide(3,4);
Monigote monigote;

// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//**************************************************************************
//
//***************************************************************************

void clear_window(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection(){

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
  //  Front_plane>0  Back_plane>PlanoDelantero)
  glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer(){
  // posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-Observer_distance);
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis(){
  glBegin(GL_LINES);
  // eje X, color rojo
  glColor3f(1,0,0);
  glVertex3f(-AXIS_SIZE,0,0);
  glVertex3f(AXIS_SIZE,0,0);
  // eje Y, color verde
  glColor3f(0,1,0);
  glVertex3f(0,-AXIS_SIZE,0);
  glVertex3f(0,AXIS_SIZE,0);
  // eje Z, color azul
  glColor3f(0,0,1);
  glVertex3f(0,0,-AXIS_SIZE);
  glVertex3f(0,0,AXIS_SIZE);
  glEnd();
}

//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects(){
//TODO: Añadir menu para cambiar entre visualizaciones
modo = toupper(modo);
tipo = toupper(tipo);

if(tipo == 'C'){
  switch (modo) {
    case  'A':
      cubo.draw_solido_ajedrez(0,0,1,1,0,0);
      break;
    case 'S':
      cubo.draw_solido(0,1,0);
      break;
    case 'R':
      cubo.draw_aristas(1,0,0,1);
      break;
    case 'U':
      cubo.draw_ConjuntoPuntos(1,0,0,2);
      break;
    default:
      cubo.draw_solido_ajedrez(0,0,1,1,0,0);
  }
} else if(tipo == 'P') {
  switch (modo) {
    case  'A':
      piramide.draw_solido_ajedrez(0,0,1,1,0,0);
      break;
    case 'S':
      piramide.draw_solido(0,1,0);
      break;
    case 'R':
      piramide.draw_aristas(1,0,0,1);
      break;
    case 'U':
      piramide.draw_ConjuntoPuntos(1,0,0,2);
      break;
    default:
      piramide.draw_solido_ajedrez(0,0,1,1,0,0);
    }
} else if(tipo == 'E'){
  glMatrixMode(GL_MODELVIEW);
  //glLoadIdentity();
  cubo.draw_solido(1.0,1.0,0.6);

  //Piramide Superior
    glTranslatef(0.0,3,0.0);        //Sube la piramide 3 unidades
    piramide.draw_solido(1.0,0.0,0.6);

  //Piramide izquierda
    glTranslatef(0.0,-3,0.0);       //Baja la piramide a su sitio original
    glRotatef(90,0,0,1);            //La rota 90º a la izquierda
    glTranslatef(0.0,3,0.0);        //La mueve 3 unidades a la izquierda
    piramide.draw_solido(1.0,0.0,0.6);

  //Pramide inferior
    glTranslatef(0.0,-3,0.0);       //Vuelve a poner la piramide en el centro
    glRotatef(90,0,0,1);            //La gira 90º mas (180º)
    glTranslatef(0.0,3,0.0);        //La mueve 3 unidades abajo
    piramide.draw_solido(1.0,0.0,0.6);

  //Piramide derecha
    glTranslatef(0.0,-3,0.0);       //La pone en el centro
    glRotatef(90,0,0,1);            //Gira 90 grados mas(270º)
    glTranslatef(0.0,3,0.0);        //La mueve 3 unidades a la derecha
    piramide.draw_solido(1.0,0.0,0.6);

    /*Usando glPushMatrix y glPopMatrix
    glPushMatrix(); //Guarda el estado actual de la matriz.
    glTranslatef(-3,0.0,0.0);
    glRotatef(90, 0, 0, 1);
    piramide.draw_solido_ajedrez(0.5,1,0.5,1,0.5,1);
    glPopMatrix(); //Recupera el estado anterior de la matriz.

    glPushMatrix();
    glTranslatef(3,0.0,0.0);
    glRotatef(-90, 0, 0, 1);
    piramide.draw_solido_ajedrez(0.5,1,0.5,1,0.5,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,3,0.0);
    glRotatef(0, 0, 1, 0);
    piramide.draw_solido_ajedrez(0.5,1,0.5,1,0.5,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,-3,0.0);
    glRotatef(180, 0, 0, 1);
    piramide.draw_solido_ajedrez(0.5,1,0.5,1,0.5,1);
    glPopMatrix();*/
  }
  else if(tipo == 'X'){
    cubo.draw_solido(1.0,1.0,0.4);

    glRotatef(90,0,1,0);
    glTranslatef(0.0,-3.0,3.01);
    glScalef(0.5,0.45,0.5);

    monigote.draw_monigote();
  }
glutPostRedisplay();
}

//**************************************************************************
//
//***************************************************************************

void draw_scene(void){
  clear_window();
  change_observer();
  draw_axis();
  draw_objects();
  glutSwapBuffers();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1){
  change_projection();
  glViewport(0,0,Ancho1,Alto1);
  glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y){
  Tecla1 = toupper(Tecla1);

  if (Tecla1=='Q') exit(0);
  else{
    if(Tecla1 == 'P' || Tecla1 == 'C'|| Tecla1 == 'E' || Tecla1 == 'X')
      tipo =Tecla1;
    else
      modo = Tecla1;
  }
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y){
  switch (Tecla1){
    case GLUT_KEY_LEFT:Observer_angle_y--;break;
    case GLUT_KEY_RIGHT:Observer_angle_y++;break;
    case GLUT_KEY_UP:Observer_angle_x--;break;
    case GLUT_KEY_DOWN:Observer_angle_x++;break;
    case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
    case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
  }
  glutPostRedisplay();
}

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void){
  // se inicalizan la ventana y los planos de corte
  Window_width=5;
  Window_height=5;
  Front_plane=10;
  Back_plane=1000;

  // se inicia la posicion del observador, en el eje z
  Observer_distance=2*Front_plane;
  Observer_angle_x=0;
  Observer_angle_y=0;

  // se indica cual sera el color para limpiar la ventana	(r,v,a,al)
  // blanco=(1,1,1,1) rojo=(1,0,0,1), ...
  glClearColor(1,1,1,1);

  // se habilita el z-bufer
  glEnable(GL_DEPTH_TEST);
  //
  change_projection();
  //
  glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv){

  cout << "\t\t****** TECLAS ******" << endl;
  cout << "\t\t**  P = Pirámide  **" << endl;
  cout << "\t\t**  C = Cubo      **" << endl;
  cout << "\t\t**  E = Estrella  **" << endl;
  cout << "\t\t**  X = Examen    **" << endl;
  cout << "\t\t**----------------**" << endl;
  cout << "\t\t** Solo con P y C **" << endl;
  cout << "\t\t**----------------**" << endl;
  cout << "\t\t**  A = Ajedrez   **" << endl;
  cout << "\t\t**  R = Aristas   **" << endl;
  cout << "\t\t**  U = Puntos    **" << endl;
  cout << "\t\t**  S = Sólido    **" << endl;
  cout << "\t\t********************" << endl;
  // se llama a la inicialización de glut
  glutInit(&argc, argv);

  // se indica las caracteristicas que se desean para la visualización con OpenGL
  // Las posibilidades son:
  // GLUT_SIMPLE -> memoria de imagen simple
  // GLUT_DOUBLE -> memoria de imagen doble
  // GLUT_INDEX -> memoria de imagen con color indizado
  // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
  // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
  // GLUT_DEPTH -> memoria de profundidad o z-bufer
  // GLUT_STENCIL -> memoria de estarcido
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

  // posicion de la esquina inferior izquierdad de la ventana
  glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

  // tamaño de la ventana (ancho y alto)
  glutInitWindowSize(UI_window_width,UI_window_height);

  // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
  // al bucle de eventos)
  glutCreateWindow("Practica 1");

  // asignación de la funcion llamada "dibujar" al evento de dibujo
  glutDisplayFunc(draw_scene);
  // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
  glutReshapeFunc(change_window_size);
  // asignación de la funcion llamada "tecla_normal" al evento correspondiente
  glutKeyboardFunc(normal_keys);
  // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
  glutSpecialFunc(special_keys);

  // funcion de inicialización
  initialize();

  // inicio del bucle de eventos
  glutMainLoop();
  return 0;
}
