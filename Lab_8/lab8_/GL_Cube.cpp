/*

Задача: Построить 3D модель кубика-рубика используя графическую библиотеку OpenGL.

Кубик рубик размера 3*3*3 состоит из 27 мелких кубиков. 
Будет удобно создать класс мелкого кубика (Small_Cube).
В нём будет хранится цвета шести граней и размер.
Методы: 
1) нарисовать (draw);
2) повернуть на угол 90 градусов вдоль координатной оси (rotateX, rotateY, rotateZ);
3) установить цвет грани с конкретным номером от 0 до 5 (setColor).

Следующий класс - класс самого кубика-рубика (Cube).
В нём хранится размер, 6 цветов, массив 3*3*3 объектов Small_Cube, углы поворота каждой грани.
Методы:
1) Повернуть грань с конкретным номером на угол 90 градусов. Для этого просто будем менять местами элементы 3-х мерного массива, и при этом поварачивать сами части тоже на 90 градусов.
2) Повернуть грань с конкретным номером на угол A градусов (A < 90). Для каждой грани будем хранить угол, на который она сейчас повёрнута. Если он становится кратным 90, то вызываем метод под пунктом 1. 
3) Нарисовать. Рисуем грань которая повёрнута на угол не кратный 90, затем все остальные.

Клавиши в промежутке ['0', '5'] - команды поворота грани.
Правая кнопка мыши - смена режима (автоматическая прокрутка и управление вручную).
Клавиши вверх, вниз, влево, вправо - вращение.
Home, End - приближение/отдаление

*/

#include "GL_Cube.h"
#include <ctime>
#include <cstdlib>
#include <GL/glew.h>
#include <GL/freeglut_std.h>
#include <GL/glu.h>


#define GLUT_PROGRAM
#include "../lab8_/Source.cpp"
#include <queue>
#define ANGLE_ROT 30
Cube cube{};
std::queue<int> queue_of_rotations;
void auto_solve();
void generate();



#define CUBE_SIZE 13
#define TIMER 30
// обозначаем цвета:
//                    (верх,      низ,   впереди,   сзади,    лево,      право)
unsigned int c[9] = {0xFFFFFF, 0xFFFF00, 0x0000FF, 0x00FF00, 0xFF0000, 0xFF5600};//белый, желтый, синий, зеленый, красный, рыжий CD853F

// координаты источника света
GLfloat lightPos[] = {0, 100, 200, 0}; 
// проекции угла поворота на оси
int xRot = 24, yRot = 34, zRot = 0;
// отдаление
double translateZ = -35.0;
// кубик-рубик
GL_Cube cube_3d;
// флаг того, крутится куб сам, или нет (будет переключаться правой кнопкой мыши)
int timerOn = 1;

void display()
{
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glTranslatef(0, 0, translateZ);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    glTranslatef(CUBE_SIZE / -2.0, CUBE_SIZE / -2.0, CUBE_SIZE / -2.0);
    cube_3d.draw();
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat fAspect = (GLfloat)w/(GLfloat)h;
    gluPerspective(60, fAspect, 1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init()
{
    glClearColor(0.546875, 0.89453125, 0.92578125, 0.00390625);
    // инициализируем случайные числа
    srand(time(0));

    // освещение
    float mat_specular[] = {0.3, 0.3, 0.3, 0};
    float diffuseLight[] = {0.2, 0.2, 0.2, 1};
    float ambientLight[] = {0.9, 0.9, 0.9, 1.0};
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMateriali(GL_FRONT, GL_SHININESS, 128);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    // инициализируем куб
    cube_3d.clear(CUBE_SIZE, c);
}

void specialKeys(int key, int, int)
{
    // клавиши влево/вправо вращают по Y
    // клавиши вверх/вниз вращают по X
    // F1 - возвращает в начальное положение
    if (key == GLUT_KEY_DOWN)
    {
        xRot += 3;
        if (xRot >= 360)
            xRot -= 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_UP)
    {
        xRot -= 3;
        if (xRot < 0)
            xRot += 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_RIGHT)
    {
        yRot += 3;
        if (yRot >= 360)
            yRot -= 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_LEFT)
    {
        yRot -= 3;
        if (yRot < 0)
            yRot += 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_HOME)
    {
        translateZ += 5;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_END)
    {
        translateZ -= 5;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_F1)
    {
        cube_3d.clear(CUBE_SIZE, c);
        cube.clear();
        glutPostRedisplay();
    }

}

void keys(unsigned char key, int, int)
{
    // если нажали клавишу от 0 до 5 - начинаем поворот на ANGLE_ROT градуса
    if (cube_3d.current == -1 && key >= '0' && key < '6')
    {
        cube_3d.Rotate(key - '0', ANGLE_ROT);

        switch (key - '0') {
            case 0:
                cube.B();
                break;
            case 1:
                cube.F_();
                break;
            case 2:
                cube.D();
                break;
            case 3:
                cube.U_();
                break;
            case 4:
                cube.L();
                break;
            case 5:
				cube.R_();
				break;
            default:
                cube.R_();
                break;
        }

        display();
    }

    if (key == 'g' || key == 'G') {
        generate();
    }

    if (key == 's' || key == 'S') {
        auto_solve();
    }
}

void mouse(int key, int state, int, int)
{
    if (key == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        // переключаем флаг
        timerOn = 1 - timerOn;
    }
}

void timer(int)
{
    glutTimerFunc(TIMER, timer, 0);
    if (timerOn)
    {
        // если включен автоматический поворот, и смотрим
        // если сейчас никакая грань не крутится, то начинаем крутить по очереди поворотов,
        // иначе крутим текущую
        if (cube_3d.current == -1) {
            if (!queue_of_rotations.empty()) {
                int q = queue_of_rotations.front();
                queue_of_rotations.pop();
                switch (q) {
                    case 0:
                        cube_3d.Rotate(2, ANGLE_ROT);
						//cout << "(0)";
                        break;
                    case 1:
                        cube_3d.Rotate(1, ANGLE_ROT);
						//cout << "(1)";
                        break;
                    case 2:
                        cube_3d.Rotate(5, ANGLE_ROT);
						//cout << "(2)";
                        break;
                    case 3:
                        cube_3d.Rotate(0, ANGLE_ROT);
						//cout << "(3)";
                        break;
                    case 4:
                        cube_3d.Rotate(4, ANGLE_ROT);
						//cout << "(4)";
                        break;
                    case 5:
                        cube_3d.Rotate(3, ANGLE_ROT);
						//cout << "(5)";
                        break;
                    default:
                        break;
                }
            }
        }
        else
            cube_3d.Rotate(cube_3d.current, ANGLE_ROT);
    }
    else
    {
        if (cube_3d.current != -1)
            cube_3d.Rotate(cube_3d.current, ANGLE_ROT);
    }
    
    display();
}

void auto_solve() 
{

    std::cout << "Called solve" << std::endl;


	cube.moves.clear();

	cube.print_current();
    cout << "Solution\n" << cube.solve();
	cube.print_current();
	
	for (int i : cube.moves)
	{
		switch (i)
		{
		case 0:
			queue_of_rotations.push(0);
			break;
		case 1:
			queue_of_rotations.push(1);
			queue_of_rotations.push(1);
			queue_of_rotations.push(1);
			break;
		case 2:
			queue_of_rotations.push(2);
			queue_of_rotations.push(2);
			queue_of_rotations.push(2);
			break;
		case 3:
			queue_of_rotations.push(3);
			break;
		case 4:
			queue_of_rotations.push(4);
			break;
		case 5:
			queue_of_rotations.push(5);
			queue_of_rotations.push(5);
			queue_of_rotations.push(5);
			break;
		default:
			queue_of_rotations.push(5);
			queue_of_rotations.push(5);
			queue_of_rotations.push(5);
			break;
		}
	}

    cube.clear();
}

/*
 GL - m
 0 - 3
 1 - 1
 2 - 0
 3 - 5
 4 - 4
 5 - 2

 */

void generate() 
{
    std::cout << "Called generate" << std::endl;

    std::srand(unsigned(std::time(nullptr)));
    int random_length = 1 + std::rand() % 20;
	
    for (int i = 0; i < random_length; ++i) 
	{
        int rand_int_ = std::rand();
        bool direction = std::rand() % 2 == 0;
		
        switch (rand_int_ % 6) 
		{
            case 0:
                cube.D();
				queue_of_rotations.push(0);
                break;
            case 1:
                cube.F();
				queue_of_rotations.push(1);
				queue_of_rotations.push(1);
				queue_of_rotations.push(1);
                break;
            case 2:
                cube.R();
				queue_of_rotations.push(2);
				queue_of_rotations.push(2);
				queue_of_rotations.push(2);
                break;
            case 3:
                cube.B();
				queue_of_rotations.push(3);
                break;
            case 4:
                cube.L();
				queue_of_rotations.push(4);
                break;
            case 5:
				cube.U();
				queue_of_rotations.push(5);
				queue_of_rotations.push(5);
				queue_of_rotations.push(5);
				break;
            default:
                cube.U();
				queue_of_rotations.push(5);
                break;
        }

    }
}


int main(int argc, char **argv)
{
	std::cout << "Commands:\ng - generate\ns - solve\n<-,->,^, - move\n0 - B, 1 - F, 2 - D, 3 - U, 5 - L, 5 - R\nF1 - clear\n\n";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 500);
    glutInitWindowPosition(1, 1);
    glutCreateWindow("Rubik's cube");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keys);
    glutMouseFunc(mouse);
    glutTimerFunc(TIMER, timer, 0);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}
