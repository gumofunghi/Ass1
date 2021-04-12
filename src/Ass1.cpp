#include<GL/glut.h>
#include<iostream>

bool* keyStates = new bool[256](); // Create an array of boolean values of length 256 (0-255)  

float yRotationAngle = 0.0f;

int currentSelection = 1;

// Cube
void renderObject1() {

	float f1[4][3] = { {-1.0f, -1.0f, 0.0f}, {-1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, -1.0f, 0.0f} };
	float f2[4][3];
	
	for (int i = 0; i < 4; i++) {
	
		for (int j = 0; j < 3; j++) {
		
			f2[i][j] = f1[i][j];

			if (j == 2) {
			
				f2[i][j] += 2;
					
			}

		}

	}

	// face 1
	glBegin(GL_QUADS);
	for (int a = 0; a < 4; a++) {

		glVertex3f(f1[a][0], f1[a][1], f1[a][2]);

	}
	glEnd();


	//face 2
	glBegin(GL_QUADS);
	for (int a = 0; a < 4; a++) {

		glVertex3f(f2[a][0], f2[a][1], f2[a][2]); 

	}
	glEnd();

	//sides 
	for (int a = 0; a < 4; a++) {

		glBegin(GL_QUADS);

		glVertex3f(f1[a][0], f1[a][1], f1[a][2]);
		glVertex3f(f2[a][0], f2[a][1], f2[a][2]);
		glVertex3f(f2[(a + 1) % 4][0], f2[(a + 1) % 4][1], f2[(a + 1) % 4][2]);
		glVertex3f(f1[(a + 1) % 4][0], f1[(a + 1) % 4][1], f1[(a + 1) % 4][2]);

		glEnd();

	}
}

void renderObject2() {}

void renderObject3() {}

//
void renderObject4() {
	float f1[4][3] = { {-1.0f, -1.0f, 0.0f}, {-1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, -1.0f, 0.0f} };
	float f2[4][3];

	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 3; j++) {

			f2[i][j] = f1[i][j];

			if (j == 2) {

				f2[i][j] += 2;

			}

		}

	}
	
	//sides 
	
	for (int t = 0; t < 360; t++) {
		for (int a = 0; a < 4; a++) {

			glBegin(GL_QUADS);

			glVertex3f(f1[a][0], f1[a][1], f1[a][2]);
			glVertex3f(f1[a][0] * cos(t), f1[a][1], f1[a][0] * sin(t));
			glVertex3f(f1[(a + 1) % 4][0] * cos(t), f1[(a + 1) % 4][1], f1[(a + 1) % 4][0] * sin(t));
			glVertex3f(f1[(a + 1) % 4][0], f1[(a + 1) % 4][1], f1[(a + 1) % 4][2]);

			glEnd();

		}
	}
	

}

void display() {

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Clear the background of our window to black  
	glClear(GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)  
	glPushMatrix();
	
	glTranslatef(0.0f, 0.0f, -5.0f); // Push eveything 5 units back into the scene, otherwise we won't see the primitive  

	glRotatef(yRotationAngle, 0.0f, 1.0f, 0.0f); // Rotate our object around the y axis  

	switch (currentSelection) {
		case 1:
			renderObject4();
			break;
		case 2:
			renderObject2();
			break;
		case 3:
			renderObject3();
			break;
		case 4:
			renderObject1();
			break;
	}


	glPopMatrix();
	glutSwapBuffers();
	glFlush();
}

void reshape(int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window  
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed  
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)  
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes  
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly  

}

void keyPressed(unsigned char key, int x, int y) {

	if (key == 'q' ) { // If the 'a' key has been pressed  
		yRotationAngle += 10;
	}
	else if (key == 'w') { // If the 'a' key has been pressed  
		yRotationAngle -= 10;
	}
	glutPostRedisplay();

}

void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = false; // Set the state of the current key to not pressed  
}

// Menu handling function definition
void menu(int item)
{
	switch (item) {
	case 1: 
		currentSelection = 1;
		std::cout << "1" << std::endl;
		break;

	case 2:
		currentSelection = 2;
		std::cout << "2" << std::endl;
		break;

	case 3:
		currentSelection = 3;
		std::cout << "3" << std::endl;
		break;

	case 4:
		currentSelection = 4;
		std::cout << "4" << std::endl;
		break;

	default:
		currentSelection = 1;
		std::cout << "1" << std::endl;
		break;
	}

	glutPostRedisplay();

	return;
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Assignment 1");

	glutDisplayFunc(display);

	glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping  

	std::fill_n(keyStates, 256, false);
	glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses  
	glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events  

	// Create a menu
	glutCreateMenu(menu);
	// Add menu items
	glutAddMenuEntry("Object 1", 1);
	glutAddMenuEntry("Object 2", 2);
	glutAddMenuEntry("Object 3", 3);
	glutAddMenuEntry("Object 4", 4);
	// Associate a mouse button with menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}