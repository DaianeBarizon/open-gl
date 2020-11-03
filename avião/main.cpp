#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

//Prototipos
void display(void);
void eventoTeclado(unsigned char tecla, int x, int y); 
void SolidCirculo(float raio, float cx, float cy);
void WireCirculo(float raio, float cx, float cy);
void reshape(int w, int h);
void projecao(int w, int h);
//void eixos();
void glRotatef( GLfloat angulo, GLfloat x, GLfloat y, GLfloat z );
void glTranslatef( GLfloat dx, GLfloat dy, GLfloat dz );

float escalaX;
float escalaY;
float escalaW;
float escalaF;

//Função principal
int main(int argc, char *argv[])
{   
    escalaX = 0.5;
    escalaY = 0.5;
    escalaW = 0.5;
    escalaF = 0.5;
    //Escopo de criação de janela
    glutInit(&argc, argv);
    glutInitWindowSize(500,500);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Avião - Daiane");
    //evento do teclado
    glutKeyboardFunc(eventoTeclado);
    
    //Escopo de registro de callbacks
    glutDisplayFunc(display);  
    glutReshapeFunc(reshape);
    
    //Demais funções
    glutMainLoop();
    return 0;
}


//Desenha circulo wire
void WireCirculo(float raio, float cx, float cy){
     glLineWidth(2);
     float ang, x, y;
     
     glColor3f(1,1,1);
     glBegin(GL_LINE_LOOP);
     for(int i=0; i<360; i++){
         ang = (i * M_PI) / 180.0;
         x = cx + (cos(ang) * raio);
         y = cy + (sin(ang) * raio);
         glVertex2f(x,y);
     }
     glEnd();
}


//Desenha circulo solid
void SolidCirculo(float raio, float cx, float cy){
     float ang, x, y;
     
     glColor3f(0,1,2);
     glBegin(GL_POLYGON);
     for(int i=0; i<360; i++){
         ang = (i * M_PI) / 180.0;
         x = cx + (cos(ang) * raio);
         y = cy + (sin(ang) * raio);
         glVertex2f(x,y);
     }
     glEnd();
}

//*********************************************

void reshape(int w, int h){
     glViewport(0,0,w,h);
     projecao(w,h);
}


//*********************************************

void projecao(int w, int h){
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     
     if(w<=h)
         glOrtho(-8, 8, -8*h/w,8*h/w,-1,1);
     else
         glOrtho(-8*w/h, 8*w/h, -8, 8, -1, 1);
         
     //gluOrtho2D (0.0f, 255.0f, 0.0f, 255.0f);
         
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
}

//*********************************************

/*void eixos(){
     glBegin(GL_LINES);
         glColor3f(1, 0, 0);
         glVertex2f(-5,0);
         glVertex2f(5,0);
         glColor3f(0,1,0);
         glVertex2f(0,-5);
         glVertex2f(0,5);
     glEnd();
}*/
     
//********************************************


void eventoTeclado(unsigned char tecla, int x, int y)
{
          switch(tecla){
            case '+': escalaX += 0.1; 
                   escalaY += 0.1; 
                   break;
            case '-':  escalaX -= 0.1;
                   escalaY -= 0.1; 
                   break;
            case 'a': escalaW += 10.0;
                  break;
            case 's': escalaW -= 10.0;
                  break;
            case 'z': escalaF += 5.0;
                  break;
            case 'x': escalaF -= 5.0;
                  break;
            case 27: exit(0);
                   break;
          }
          glutPostRedisplay();
}

void display(void){
     glPushMatrix();
     glClear(GL_COLOR_BUFFER_BIT);
     
     glScalef(escalaX, escalaY, 0.5);
     glRotatef ((GLfloat) escalaW, 0.0, 0.0, 1.0);
     glTranslatef (escalaF, 0.0, 0.0);
     
     //eixos();
     
     glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.2f, 0.3f); 
        glVertex2f(3.3,-3);
        glColor3f(0.0f, 0.3f, 0.6f);
        glVertex2f(5,-8);
        glColor3f(0.0f, 0.3f, 0.6f);
        glVertex2f(-7, -2);
        
        glColor3f(0.0f, 0.2f, 0.3f);
        glVertex2f(3, -3);
        glColor3f(0.0f, 0.3f, 0.6f);
        glVertex2f(-2, -1);
        glColor3f(0.0f, 0.3f, 0.6f);
        glVertex2f(3, 1);
        
        glColor3f(0.0f, 0.8f, 0.6f);
        glVertex2f(6, 2);
        glColor3f(0.0f, 0.8f, 0.6f);
        glVertex2f(2, -2);
        glColor3f(0.0f, 0.2f, 0.3f);
        glVertex2f(6, -3);
    glEnd();
    
      glBegin(GL_QUADS);
        glColor3f(0.0f, 0.2f, 0.5f);
        glVertex2f(-10,-3);
        glColor3f(0.0f, 0.2f, 0.3f);
        glVertex2f(6,-3);
        glColor3f(0.0f, 0.2f, 0.5f); 
        glVertex2f( -6, 0);
        glColor3f(0.0f, 0.2f, 0.5f); 
        glVertex2f(-6, 0);
      glEnd();
    
    //janelas 
    SolidCirculo(0.5, -6.8, -1.5);
    SolidCirculo(0.3, -5, -1.5);
    SolidCirculo(0.3, -4, -1.5);
    SolidCirculo(0.3, -3, -1.5);
    
    //Lua
     glPopMatrix(); 
     SolidCirculo(1, 3, 3);
     WireCirculo(1, 3, 3);
     glFlush();
     glutSwapBuffers();
}

