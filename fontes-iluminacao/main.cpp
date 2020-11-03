#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>

GLfloat angle, fAspect, rotX, rotY;
GLdouble obsX, obsY, obsZ;
GLfloat r, g, b;
GLint especMaterial;
GLdouble posluz;

float escalaX;
float escalaY;
float escalaW;
float escalaF;
float escalaZ;

// Função responsável pela especificação dos parâmetros de iluminação
void DefineIluminacao (void)
{
        GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
        GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};     
        GLfloat posicaoLuz[4]={0.0, 50.0, 150.0, 1.0};

        // Capacidade de brilho do material
        GLfloat especularidade[4]={1.0,1.0,1.0,1.0};

        // Ativa o uso da luz ambiente
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

        // Define os parâmetros da luz de número 0
        glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
        glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
}

// Função responsável pela especificação dos parâmetros de iluminação
void DefineIluminacao2 (void)
{
        GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
        GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};   
        GLfloat posicaoLuz[4]={60.0, 50.0, 50.0, 1.0};
        GLfloat especularidade[4]={1.0,1.0,1.0,1.0};

        // luz ambiente
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

        // Define os parâmetros da luz
        glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa );
        glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz );
}

// Função callback chamada para fazer o desenho
void Desenha(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;
    
	// Limpa a janela de visualização com a cor
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DefineIluminacao();
	DefineIluminacao2();

	// Desenha objetos
	glPushMatrix();
	  glColor3f(0.6f, 0.0f, 0.0f);
	  glTranslatef(escalaW,0,-10),
	  glutSolidTeapot(10.0f);
	glPopMatrix();

	glPushMatrix();
	  glColor3f(0.0f, 1.0f, 0.0f);
	  glRotated(a,0,0,1);
	  glTranslatef(escalaX,0,-20),
	  glutSolidSphere(30, 250, 250);
	glPopMatrix();
	
	glPushMatrix();
	  glColor3f(0.9f, 1.0f, 0.0f);
	  glTranslatef(escalaF,0,-10),
	  glutSolidCube(50);
	glPopMatrix();
	
	glutSwapBuffers();
}


// Inicialização
void Inicializa(void)
{
        // Define a cor de fundo da janela de visualização como branca
        // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        // Habilita a definição da cor do material a partir da cor corrente
        glEnable(GL_COLOR_MATERIAL);
        //Habilita o uso de iluminação
        glEnable(GL_LIGHTING);
        // Habilita a luz de número 0
        glEnable(GL_LIGHT0);
		// habilita a luz de número 1
        glEnable(GL_LIGHT1);
        // Habilita o depth-buffering
        glEnable(GL_DEPTH_TEST);

        // Habilita o modelo de colorização de Gouraud
        glShadeModel(GL_FLAT);

        // Inicializa a variável que especifica o ângulo da projeção
        // perspectiva
        angle=100;

        // Inicializa as variáveis usadas para alterar a posição do
        // observador virtual
        rotX = 30;
        rotY = 0;
        obsZ = 180;
        r, g, b = 1.0;
        especMaterial = 90;
}


// Função usada para especificar a posição do observador virtual
void PosicionaObservador(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	DefineIluminacao();
	// Especifica posição do observador e do alvo
	glTranslatef(0,0,-obsZ);
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
}


// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);

	PosicionaObservador();
}


// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	if ( h == 0 ) h = 1;
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}


// Callback para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {
			// Zoom-in
			if (angle >= 10)
				angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {
			// Zoom-out
			if (angle <= 130)
				angle += 5;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

void TeclasEspeciais (int tecla, int x, int y)
{
	switch (tecla)
	{
		case GLUT_KEY_LEFT:	rotY--;
							break;
		case GLUT_KEY_RIGHT:rotY++;
							break;
		case GLUT_KEY_UP:	rotX++;
							break;
		case GLUT_KEY_DOWN:	rotX--;
							break;
		case GLUT_KEY_HOME:	obsZ++;
							break;
		case GLUT_KEY_END:	obsZ--;
							break;
		case GLUT_KEY_F2: glDisable(GL_LIGHT0);
                            break;     
		case GLUT_KEY_F1: glEnable(GL_LIGHT0);
                            break;
        case GLUT_KEY_F4: glDisable(GL_LIGHT1);
                            break;    
        case GLUT_KEY_F3: glEnable(GL_LIGHT1);
                            break;                                                                    				
	}
	PosicionaObservador();
	glutPostRedisplay();
}

// Programa Principal
int main()
{
    
    escalaX = 0;
    escalaY = 0;
    escalaW = 50;
    escalaF = 100;
    escalaZ = 0;
	int argc = 0;
	char *argv[] = { (char *)"gl", 0 };

	glutInit(&argc,argv);

	// Define do modo de operacao da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Especifica a posição inicial da janela GLUT
    glutInitWindowPosition(10,10);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(640,800);

	// Cria a janela passando como argumento o titulo da mesma
	glutCreateWindow("Desenho de um teapot com iluminação");

	// Registra a funcao callback de redesenho da janela de visualizacao
	glutDisplayFunc(Desenha);
	// Registra a funcao callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais);
	// Registra a funcao callback para tratamento do redimensionamento da janela
    glutReshapeFunc(AlteraTamanhoJanela);
	// Registra a funcao callback para tratamento do mouse
	glutMouseFunc(GerenciaMouse);

	Inicializa();
	glutMainLoop();
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
  case 27:
	exit(0);
	break;
  }
}

