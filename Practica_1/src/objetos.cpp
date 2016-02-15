/****************/
/*  PRACTICA 1  */
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

Monigote::Monigote(){};

void Monigote::Circle (GLfloat radio, GLfloat cx, GLfloat cy,GLfloat cz, GLint n, GLenum modo){
int i;
if (modo==GL_LINE) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
else if (modo==GL_FILL) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
else glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
glBegin( GL_POLYGON );
for (i=0;i<n;i++)
  glVertex3f( cx+radio*cos(2.0*M_PI*i/n), cy+radio*sin(2.0*M_PI*i/n),cz);
  glEnd();
}

void Monigote::draw_monigote(){
  //********MUÑECO*************//
//Copa
glColor3f(0.0,0.0,0.0);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_POLYGON);
	glVertex3f(-3,8,0);
	glVertex3f(3,8,0);
	glVertex3f(3,13,0);
	glVertex3f(-3,13,0);
glEnd();

//Ala
glBegin(GL_POLYGON);
	glVertex3f(-4,8,0);
	glVertex3f(4,8,0);
	glVertex3f(4,10,0);
	glVertex3f(-4,10,0);
glEnd();

//Cara
glColor3f(1.0,0.8,0.6);
glBegin(GL_POLYGON);
	glVertex3f(-3,0,0);
	glVertex3f(3,0,0);
	glVertex3f(3,8,0);
	glVertex3f(-3,8,0);
glEnd();

//oreja1
glBegin(GL_POLYGON);
	glVertex3f(-4,3,0);
	glVertex3f(-3,3,0);
	glVertex3f(-3,6,0);
	glVertex3f(-4,6,0);
glEnd();

//oreja2
glBegin(GL_POLYGON);
	glVertex3f(3,3,0);
	glVertex3f(4,3,0);
	glVertex3f(4,6,0);
	glVertex3f(3,6,0);
glEnd();

glColor3f(1.0,0.0,0.0);
glBegin(GL_POLYGON);//nariz
	glVertex3f(-1,2.5,0.1);
	glVertex3f(1,2.5,0.1);
	glVertex3f(0,4,0.1);
glEnd();

//Ojos
glColor3f(0.0,0.0,1.0);
Circle(0.6,-1.5,5,0.1,30,GL_FILL);
Circle(0.6,1.5,5,0.1,30,GL_FILL);

//Boca
glColor3f(0.0,1.0,1.0);
Circle(0.6,-1.5,1,0.1,30,GL_FILL);
Circle(0.6,1.5,1,0.1,30,GL_FILL);
glBegin(GL_POLYGON);
	glVertex3f(-1.5,1.6,0.1);
	glVertex3f(-1.5,0.4,0.1);
	glVertex3f(1.5,0.4,0.1);
	glVertex3f(1.5,1.6,0.1);
glEnd();

//Bordes
glColor3f(0.0,0.0,0.0);
glLineWidth(2);
//oreja1
glBegin(GL_LINES);
	glVertex3f(-4,3,0.1);
	glVertex3f(-3,3,0.1);

	glVertex3f(-3,3,0.1);
	glVertex3f(-3,6,0.1);

	glVertex3f(-3,6,0.1);
	glVertex3f(-4,6,0.1);

	glVertex3f(-4,6,0.1);
	glVertex3f(-4,3,0.1);
glEnd();

//oreja2
glBegin(GL_LINES);
	glVertex3f(4,3,0.1);
	glVertex3f(3,3,0.1);

	glVertex3f(3,3,0.1);
	glVertex3f(3,6,0.1);

	glVertex3f(3,6,0.1);
	glVertex3f(4,6,0.1);

	glVertex3f(4,6,0.1);
	glVertex3f(4,3,0.1);
glEnd();

//Cara
glBegin(GL_LINES);
	glVertex3f(-3,0,0.1);
	glVertex3f(3,0,0.1);

	glVertex3f(3,0,0.1);
	glVertex3f(3,8,0.1);

	glVertex3f(3,8,0.1);
	glVertex3f(-3,8,0.1);

	glVertex3f(-3,8,0.1);
	glVertex3f(-3,0,0.1);
glEnd();
};
