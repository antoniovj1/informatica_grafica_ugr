/****************/
/*  PRACTICA 3  */
/****************/

#include "objetos.h"

//*************************************************************************
// clase Punto
//*************************************************************************
void ConjuntoPuntos3D::draw_ConjuntoPuntos(float r, float g, float b, int grosor){
  glColor3f(r,g,b);
  glPointSize(grosor);
  glBegin(GL_POINTS);
  for (unsigned int i = 0 ; i < vertices.size(); i++) {
    glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
  }
  glEnd();
};


//*************************************************************************
// clase triángulo
//*************************************************************************
void ConjuntoTriangulos3D::draw_aristas(float r, float g, float b, int grosor){
  glColor3f(r,g,b);
  glLineWidth(grosor);
  glBegin(GL_LINES);
  for(unsigned int i = 0 ; i < caras.size() ; i++){
    glVertex3f(vertices[caras[i]._0].x,vertices[caras[i]._0].y,vertices[caras[i]._0].z);
    glVertex3f(vertices[caras[i]._1].x,vertices[caras[i]._1].y,vertices[caras[i]._1].z);

    glVertex3f(vertices[caras[i]._1].x,vertices[caras[i]._1].y,vertices[caras[i]._1].z);
    glVertex3f(vertices[caras[i]._2].x,vertices[caras[i]._2].y,vertices[caras[i]._2].z);

    glVertex3f(vertices[caras[i]._2].x,vertices[caras[i]._2].y,vertices[caras[i]._2].z);
    glVertex3f(vertices[caras[i]._0].x,vertices[caras[i]._0].y,vertices[caras[i]._0].z);
  }
  glEnd();
};
//Se supone que los vertices estan guardados en sentido antihorario
void ConjuntoTriangulos3D::draw_solido(float r, float g, float b){
  glColor3f(r,g,b);
  glBegin(GL_TRIANGLES);
  for(unsigned int i = 0 ; i < caras.size(); i++){
    glVertex3f(vertices[caras[i]._0].x,vertices[caras[i]._0].y,vertices[caras[i]._0].z);
    glVertex3f(vertices[caras[i]._1].x,vertices[caras[i]._1].y,vertices[caras[i]._1].z);
    glVertex3f(vertices[caras[i]._2].x,vertices[caras[i]._2].y,vertices[caras[i]._2].z);
  }
  glEnd();
};
void ConjuntoTriangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2){

  glBegin(GL_TRIANGLES);
  for(unsigned int i = 0 ; i < caras.size(); i++){
    //Si la cara es par -> color 1, si es impar -> color 2
    i%2==0 ? glColor3f(r1,g1,b1): glColor3f(r2,g2,b2);
    glVertex3f(vertices[caras[i]._0].x,vertices[caras[i]._0].y,vertices[caras[i]._0].z);
    glVertex3f(vertices[caras[i]._1].x,vertices[caras[i]._1].y,vertices[caras[i]._1].z);
    glVertex3f(vertices[caras[i]._2].x,vertices[caras[i]._2].y,vertices[caras[i]._2].z);
  }

  glEnd();
};

void ConjuntoTriangulos3D::draw(int mod,float r1, float g1, float b1, float r2, float g2, float b2,int grosor){
  switch (mod) {
  case  AJEDREZ:
    draw_solido_ajedrez( r1,  g1,  b1,  r2,  g2,  b2);
    break;
  case SOLIDO:
    draw_solido( r1,  g1,  b2);
    break;
  case ARISTAS:
    draw_aristas( r1,  g1,  b1,  grosor);
    break;
  case PUNTOS:
    draw_ConjuntoPuntos( r1,  g1,  b1,  grosor);
    break;
  default:
    draw_solido_ajedrez( r1,  g1,  b1,  r2,  g2,  b2);
  }
};

//*************************************************************************
// clase Cubo
//*************************************************************************
Cubo::Cubo(float tam){

//    v6----- v5
//   /|      /|
//  v0------v3|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v1------v2

  vertices.push_back(_vertex3f(-tam,tam,tam));   //0
  vertices.push_back(_vertex3f(-tam,-tam,tam));  //1
  vertices.push_back(_vertex3f(tam,-tam,tam));   //2
  vertices.push_back(_vertex3f(tam,tam,tam));    //3
  /*
  La segunda mitad de los vertices son inversos a la primera mitad
  for( unsigned int i = 0 ; i < 4 ; i++)
    vertices.push_back(vertices[i]*-1)
  */
  vertices.push_back(_vertex3f(tam,-tam,-tam));  //4
  vertices.push_back(_vertex3f(tam,tam,-tam));   //5
  vertices.push_back(_vertex3f(-tam,tam,-tam));  //6
  vertices.push_back(_vertex3f(-tam,-tam,-tam)); //7

  caras.push_back(_vertex3i(0,1,3));
  caras.push_back(_vertex3i(1,2,3));
  caras.push_back(_vertex3i(3,2,5));
  caras.push_back(_vertex3i(2,4,5));
  caras.push_back(_vertex3i(5,4,6));
  caras.push_back(_vertex3i(4,7,6));
  caras.push_back(_vertex3i(6,7,0));
  caras.push_back(_vertex3i(7,1,0));
  caras.push_back(_vertex3i(6,0,5));
  caras.push_back(_vertex3i(0,3,5));
  caras.push_back(_vertex3i(1,7,2));
  caras.push_back(_vertex3i(7,4,2));
};


//*************************************************************************
// clase Piramide
//*************************************************************************
Piramide::Piramide(float tam, float al){
  vertices.push_back(_vertex3f(-tam,0,-tam)); //0
  vertices.push_back(_vertex3f(-tam,0,tam));  //1
  vertices.push_back(_vertex3f(tam,0,tam));   //2
  vertices.push_back(_vertex3f(tam,0,-tam));  //3
  vertices.push_back(_vertex3f(0,al,0));      //4 Punta

  caras.push_back(_vertex3i(0,2,1));
  caras.push_back(_vertex3i(0,3,2));
  caras.push_back(_vertex3i(1,2,4));
  caras.push_back(_vertex3i(2,3,4));
  caras.push_back(_vertex3i(3,0,4));
  caras.push_back(_vertex3i(0,1,4));
};

//*************************************************************************
// clase ObjetoPLY
//*************************************************************************
void ObjetoPLY::crearObjetoPly(char* ArchivoPly){

  _file_ply fp;
  fp.open(ArchivoPly);

  vector<float> ver;
  vector<int> car;

  fp.read(ver,car);

  _vertex3f vertice_aux;
  _vertex3i cara_aux;

//Convertimos de la representación en el archivo a la nuestra.
  for(unsigned int i = 0; i < ver.size()/3; i++){
    vertice_aux.x=ver[i*3];
    vertice_aux.y=ver[i*3 + 1];
    vertice_aux.z=ver[i*3 + 2];

    vertices.push_back(vertice_aux);
  }

//Convertimos de la representación en el archivo a la nuestra.
  for(unsigned int i = 0; i < car.size()/3; i++){
    cara_aux._0=car[i*3];
    cara_aux._1=car[i*3 + 1];
    cara_aux._2=car[i*3 + 2];

    caras.push_back(cara_aux);
  }
};

int ObjetoPLY::getNumCaras(){
    return caras.size();
}

int ObjetoPLY::getNumVertices(){
    return vertices.size();
}

//*************************************************************************
// clase Objeto Revolucion
//*************************************************************************

void Revolucion::crearObjetoRev(char *ArchivoPly, int n, bool tapas){
    _file_ply fp;
    fp.open(ArchivoPly);

    vector<float> ver;
    vector<int> car;

    fp.read(ver,car); //Se guardan los vertices y las caras en los vectores.

    vector<_vertex3f> perfil; //Vector auxiliar para guardar los vertices que hay en el fichero.
    _vertex3f vertice_aux;
    _vertex3i cara_aux;

//Paso de puntos del fichero a _vertex3f y los guardo en ver_aux
    for(unsigned int i = 0; i < ver.size()/3; i++){
      vertice_aux.x=ver[i*3];
      vertice_aux.y=ver[i*3 + 1];
      vertice_aux.z=ver[i*3 + 2];

      perfil.push_back(vertice_aux);
    }

    int num_aux = perfil.size();
    //El tamaño será el nuemro de puntos del perfil multiplicado por el número de veces que se van a mover esos vertices.
    vertices.resize(num_aux*n);


/*
Explicación:
En álgebra lineal, una matriz de rotación es la matriz que representa una rotación en
el espacio euclídeo. Por ejemplo, la matriz

       |¯¯            ¯¯ |
       | cos(O)   -sin(O)|
R(O) = | sin(O)   cos(O) |
       |_               _|

representa la rotación de θ grados del plano en sentido antihorario.
 En tres dimensiones, las matrices de rotación representan las rotaciones
 de manera concisa y se usan frecuentemente en geometría, física e informática.

Aunque en la mayoría de las aplicaciones se consideran rotaciones en dos o
tres dimensiones, las matrices de rotación pueden definirse en espacios de
cualquier dimensión. Algebraicamente, una matriz de rotación es una matriz
ortogonal de determinante uno:

R^T = R^-1 y det R = 1.

Las matrices de rotación son cuadradas y con valores reales. Sin embargo,
se pueden definir sobre otros cuerpos. El conjunto de todas las matrices de
rotación de dimensión n × n forma un grupo que se conoce como grupo de
rotaciones (o grupo ortogonal especial).


Matriz para rotar sobre el eje y:
        |¯¯               ¯¯ |
        | cos(O)   0   sin(O)|
Ry(O) = |  0       1      0  |
        | -sin(O)  0  cos(O) |
        |_                  _|

*/

//Creación vertices
    double divisor = 1/(1.0*n); //Mejora la eficiencia ( evita hacer muchas divisiones)
    for (int j = 0; j < n; j++) {
        double angulo = 2*M_PI*j*divisor;  //Vamos dividiendo la vuelta en gajos (ángulos equidistantes) , en radianes para poder calcular coseno y seno
        for (int i = 0; i < num_aux; i++) {
            vertice_aux.x = perfil[i].x*cos(angulo) + perfil[i].z*sin(angulo);
            vertice_aux.y = perfil[i].y;
            vertice_aux.z = -1*perfil[i].x*sin(angulo) + perfil[i].z*cos(angulo);

            //guardo los vertices en el vector consecutivamente
            vertices[i+j*num_aux] = vertice_aux;
        }
    }

//Creación caras
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < num_aux-1; i++) {
            cara_aux._0 = i+((j+1)%n)*num_aux;
            cara_aux._1 = i+1+((j+1)%n)*num_aux;
            cara_aux._2 = i+1+j*num_aux;
            caras.push_back(cara_aux);

            cara_aux._0 = i+1+j*num_aux;
            cara_aux._1 = i+j*num_aux;
            cara_aux._2 = i+((j+1)%n)*num_aux;
            caras.push_back(cara_aux);
        }
    }


    if(tapas){
//Creación tapa inferior
//Miramos si el vertice esta separado del eje y , si no, no hay nada que tapar.
    if(fabs(perfil[0].x) > 0.0){
        vertice_aux.y = perfil[0].y;
        vertice_aux.x = 0.0;
        vertice_aux.z = 0.0;
        vertices.push_back(vertice_aux);

        cara_aux._0 = num_aux*n;

        for (int i = 0; i < n; i++){
            cara_aux._1 = ((i+1)%n)*num_aux;
            cara_aux._2 = i*num_aux;
            caras.push_back(cara_aux);
        }
    }

//Creación tapa superior
//Miramos si el vertice esta separado del eje y , si no, no hay nada que tapar.
    if(fabs(perfil[num_aux-1].x) > 0.0){
        vertice_aux.y = perfil[num_aux-1].y;
        vertice_aux.x = 0.0;
        vertice_aux.z = 0.0;
        vertices.push_back(vertice_aux);

        cara_aux._0 = num_aux*n+1;

        for (int i = 0; i < n; i++){
            cara_aux._1 = (i+1)*num_aux-1;
            cara_aux._2 = ((i+1)%n)*num_aux+n;
            caras.push_back(cara_aux);
        }
    }
  }
};

int Revolucion::getNumCaras(){
    return caras.size();
}

int Revolucion::getNumVertices(){
    return vertices.size();
}

/* Práctica 3 */
//*************************************************************************
// clase Objeto Cabeza
//*************************************************************************
Cabeza::Cabeza(){
  char ruta[] = "./data/Droide/cabeza.ply";
  crearObjetoPly(ruta);
  };
//*************************************************************************
// clase Objeto Brazo Izquierda
//*************************************************************************
BrazoIZQ::BrazoIZQ(){
  char ruta[] = "./data/Droide/brazo_izq.ply";
  crearObjetoPly(ruta);
};
//*************************************************************************
// clase Objeto Brazo Derecha
//*************************************************************************
BrazoDER::BrazoDER(){
  char ruta[] = "./data/Droide/brazo_der.ply";
  crearObjetoPly(ruta);
};

//*************************************************************************
  // clase Pierna Izquierda
  //*************************************************************************
PiernaIZQ::PiernaIZQ(){
    char ruta[] = "./data/Droide/pierna_izq.ply";
    crearObjetoPly(ruta);
  };
//*************************************************************************
// clase Pierna Izquierda
//*************************************************************************
PiernaDER::PiernaDER(){
  char ruta[] = "./data/Droide/pierna_der.ply";
  crearObjetoPly(ruta);
};
//*************************************************************************
// clase Cuerpo
//*************************************************************************
Cuerpo::Cuerpo(){
  char ruta[] = "./data/Droide/cuerpo.ply";
  crearObjetoPly(ruta);
};

void Droide::draw(int mod,float r1, float g1, float b1, float r2, float g2, float b2,int grosor,int rotCabeza,int rotCu,int rotPi){
  glScalef(2,2,2); //Se hace que sea más grande.
  glRotatef(180,0,1,0); // Se pone mirando hacia delante
  glRotatef(90,0,0,1); //Se pone derecho , estaba tumbado

  glPushMatrix();
  glRotatef(rotCabeza,1.0,0.0,0.0);
    cabeza.draw(mod,r1,g1,b1,r2,g2,b2,grosor);
  glPopMatrix();

  glPushMatrix();
    glRotatef(rotCu,1.0,0.0,0.0);
    cuerpo.draw(mod,r1,g1,b1,r2,g2,b2,grosor);
    brazoI.draw(mod,r1,g1,b1,r2,g2,b2,grosor);
    brazoD.draw(mod,r1,g1,b1,r2,g2,b2,grosor);
  glPopMatrix();

  piernaI.draw(mod,r1,g1,b1,r2,g2,b2,grosor);

  glPushMatrix();
  glTranslatef(2,0.0,0.0); // 3. Translate to the object's position.
  glRotatef(rotPi,0.0,1.0,0.0); // 2. Rotate the object.
  glTranslatef(-2,0.0,0.0);
    piernaD.draw(mod,r1,g1,b1,r2,g2,b2,grosor);
  glPopMatrix();

}
