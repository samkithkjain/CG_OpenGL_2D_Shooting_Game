#include<stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//#include<iostream>
#include<stdlib.h>
#include<GL/glut.h>
#include<string.h>
#include<math.h>
//#include<cstdio>
//#include<windows.h>
//#include <mmsystem.h>
// Data Definition for all except Image Texture
GLfloat body1[4][3] = {{295, 525, -610},{295, 575, -610},{395, 575, -610},{395, 525, -610}};
GLfloat head1[4][3] = {{325, 575, -610},{325, 615, -610},{365, 615, -610},{365, 575, -610}};
GLfloat hat1[4][3] = {{320, 615, -610},{320, 625, -610},{370, 625, -610},{370, 615, -610}};

GLfloat body0[4][3] = { {295, 525, -611},{295, 575, -611},{395, 575, -611},{395, 525, -611} };
GLfloat head0[4][3] = { {325, 575, -611},{325, 615, -611},{365, 615, -611},{365, 575, -611} };
GLfloat hat0[4][3] = { {320, 615, -611},{320, 625, -611},{370, 625, -611},{370, 615, -611} };

GLfloat treebase[4][3] = { {40, 530, -615},{40, 560, -615},{60, 560, -615},{60, 530, -615} };
GLfloat treep1[4][3] = { {10, 560, -615},{30, 590, -615},{70, 590, -615},{90, 560, -615} };

GLfloat background[4][3] = {{0, 0, -749},{0, 750, -749},{750, 750, -749},{750, 0, -749}};
GLfloat wall1t[4][3] = {{0, 200, -25},{700, 200, -25},{750, 250, -25},{50, 250,-25}};
GLfloat wall1s[4][3] = {{750, 50, -25},{700, 0, -25},{700, 200, -25},{750, 250, -25}};
GLfloat wall1f[4][3] = {{0, 0, -25},{0, 200, -25},{700, 200, -25},{700, 0, -25}};

GLfloat wall2t[4][3] = {{10, 500, -600},{700, 500, -600},{740, 525, -600},{50, 525, -600}};
GLfloat wall2s[4][3] = {{740, 425, -600},{700, 400, -600},{700, 500, -600},{740, 525, -600}};
GLfloat wall2f[4][3] = {{10, 400, -600},{10, 500, -600},{700, 500, -600},{700, 400, -600}};

GLfloat wall2tb[4][3] = {{10, 400, -600},{700, 400, -600},{740, 425, -600},{50, 425, -600} };
GLfloat wall2fb[4][3] = {{50, 425, -600},{50, 525, -600},{740, 525, -600},{740, 425, -600} };

GLfloat wall1tb[4][3] = { {0, 0, -25},{700, 0, -25},{750, 50, -25},{50, 50,-25} };
GLfloat wall1fb[4][3] = { {50, 50, -25},{50, 250, -25},{750, 250, -25},{750, 50, -25} };

GLfloat infobar[4][3] = {{0, 700, -60},{0, 750, -60},{750, 750, -60},{750, 700, -60}};

GLfloat infopoly[4][3] = { {0,250,0},{0,750,0},{750,750,0},{750,250,0} };

GLfloat lrpos[6] = { 95,195,295,395,495,595 };
GLfloat tdpos[2] = { 420,525 };

GLfloat bullets[4][3] = {{5,20,-20},{5,23,-20},{20,23,-20},{20,20,-20}};

int tdp[2] = { 1,1 };
int lrcp[2] = { 5,1 };
int lrmv[2] = { 1,-1 };
int tdmv[2] = { 1,1 };
int limit[2] = { -1,-1 };
int model = 1;//0 for Texture 1 for Plane
int diff = 0;
int motion[2] = { 0,0 }; // 0 Horizontal 1 Vertical

char msg[50] = "Start, Time is Running Out!";
int menuid=-1;
int score = 0;
int t3 = 0;
int t2 = 0;
int scene = 1;
int mm = 0;
int ss = 100;
int endgame = 0;
int wscore;

//bullet and reload
int gbullets;
int sbullets;
int reload;


// Texture Data Defintion
unsigned char* data[13];//data value for texture
int w[13], h[13], n[13];//texture w and h
unsigned int text[13];//texture id
char fnames[13][20] = {"hat.jpg","head.jpg","body.jpg","wall1f.jpg","wall1s.jpg","wall1t.jpg","wall2f.jpg","wall2s.jpg","wall2t.jpg","bg.jpg","img1.jpg","img2.jpg","img3.jpg"};



void setImage(int index, unsigned int* text, unsigned char* d)
{
	//	unsigned int texture;
	glGenTextures(1, text);
	glBindTexture(GL_TEXTURE_2D, *text);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (d) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w[index], h[index], 0, GL_RGB, GL_UNSIGNED_BYTE, d);
		//glGeneratedMipmap(GL_TEXTURE_2D);
	}
	else
		printf("ERROR\n");
}
//Loading Function
void setImageData()
{
	int i = 0;
	for (i = 0;i < 13;i++)
	{
		data[i] = stbi_load(fnames[i], &w[i], &h[i], &n[i], 0);
		setImage(i,&text[i],data[i]);
	}

}
////////////////////////////////////////////////////////////////////

void menuInputProcess(int value)
{
	if (scene == 3)
	{
		model = value;
	}
	else
	{
		if(value==0)
			sprintf(msg, "Current Difficulty Level : EASY");
		else if(value==1)
			sprintf(msg, "Current Difficulty Level : MEDIUM");
		else
			sprintf(msg, "Current Difficulty Level : HARD");
		diff = value;
	}
	glutPostRedisplay();
}

//Menu Creation
void createMenu()
{
	menuid = glutCreateMenu(menuInputProcess);
	if (scene == 3)
	{
		glutAddMenuEntry("Wire Frame", 2);
		glutAddMenuEntry("Solid Fill", 1);
		glutAddMenuEntry("Image Texture", 0);
	}
	else
	{
		glutAddMenuEntry("Easy", 0);
		glutAddMenuEntry("Medium", 1);
		glutAddMenuEntry("Hard", 2);
	}
	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void drawText(float x, float y, float z, void* font, int r, int g, int b, const char *string)
{
	int j = strlen(string);
	glColor3f(r, g, b);
	glRasterPos3f(x, y, z);
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(font, string[i]);
	}
}

//End Of Game Win or Loss
void end(int w)
{
	if (w == 0)
		sprintf(msg, "Game Over - You Lost!");
	else
		sprintf(msg, "You Won!");
	endgame = 1;
	scene = 4;
	glutPostRedisplay();
}

//To Restart the Game
void reset()
{
	sprintf(msg, "Start, Time is Running Out!");
	t3 = 0;
	t2=0;
	endgame = 0;
	score = 0;
	reload = 0;
	gbullets = 6;
	sbullets = 42;
	if (diff == 0)
	{
		mm = 0;
		ss = 30;
		wscore = 150;
	}
	else if (diff == 1)
	{
		mm = 0;
		ss = 25;
		wscore = 175;
	}
	else
	{
		mm = 0;
		ss = 15;
		wscore = 200;
	}
}

//Gun Pointer Function
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		int rem = 6 - gbullets;
		if (sbullets < rem)
			rem = sbullets;
		sbullets -= rem;
		gbullets += rem;
		sprintf(msg, "Loaded!");
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (gbullets==0)
		{
			//PlaySound("reload.wav", NULL, SND_ASYNC | SND_FILENAME);
			sprintf(msg, "Reload!");
			return;
		}
		//PlaySound("bullet.wav", NULL, SND_ASYNC | SND_FILENAME);
		y = 750 - y;
		if (y >= 525)
		{
			if (x <= hat1[2][0] && x >= hat1[0][0] && y <= hat1[1][1] && y >= hat1[0][1])
			{
				score += 1;
				sprintf(msg, "Last : Hat Shot 1 Point!");
			}
			else if (x <= head1[2][0] && x >= head1[0][0] && y <= head1[1][1] && y >= head1[0][1])
			{
				score += 5;
				sprintf(msg, "Last : Head Shot 5 Points!");
			}
			else if (x <= body1[2][0] && x >= body1[0][0] && y <= body1[1][1] && y >= body1[0][1])
			{
				score += 2;
				sprintf(msg, "Last : Body Shot 2 Points!");
			}
			else if (x <= hat0[2][0] && x >= hat0[0][0] && y <= hat0[1][1] && y >= hat0[0][1])
			{
				score += 1;
				sprintf(msg, "Last : Hat Shot 1 Point!");
			}
			else if (x <= head0[2][0] && x >= head0[0][0] && y <= head0[1][1] && y >= head0[0][1])
			{
				score += 5;
				sprintf(msg, "Last : Head Shot 5 Points!");
			}
			else if (x <= body0[2][0] && x >= body0[0][0] && y <= body0[1][1] && y >= body0[0][1])
			{
				score += 2;
				sprintf(msg, "Last : Body Shot 2 Points!");
			}
			else
			{
				sprintf(msg, "Last : Missed!");
			}
		}
		if (score >= wscore)
		{
			end(1);
			return;
		}
		if (gbullets >= 1)
		{
			gbullets--;
		}
		if (sbullets == 0 && gbullets == 0)
		{
			end(0);
			return;
		}
		if (gbullets == 0)
		{
			sprintf(msg, "Reload!");
		}
	}
	glutPostRedisplay();
}
/*void mousePassive(int x, int y)
{
	y = 750 - y;
	float lightPos[] = { 375.0, 375.0,600.0, 1.0 };
	lightPos[0] = x;
	lightPos[1] = y;
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	if (y <= 555)
		glDisable(GL_LIGHT0);
	else
		glEnable(GL_LIGHT0);
}*/


//Keyboard input for Scene1 - Main Screen
void keyboard1(unsigned char key,int x, int y)
{
	if (key == 'S' || key=='s')
	{
		if (scene == 1)
			scene = 2;
		else
			scene = 3;
		glutPostRedisplay();
	}
	else if (key == 'Q' || key=='q')
	{
		glutDestroyWindow(0);
		exit(0);
	}
}

//Keyboard input for Scene3 - Last Screen
void keyboard2(unsigned char key, int x, int y)
{
    if (key == 'Q' || key == 'q')
	{
		glutDestroyWindow(0);
		exit(0);
	}
	else if (key == 'M' || key == 'm')
	{
		reset();
		scene = 1;
		glutPostRedisplay();
	}
}

//String Process and Output on Scene3 - Game
void printBullets()
{
	char t[20];
	sprintf(t, "LEFT:%d", sbullets);
	drawText(0, 1, 0, GLUT_BITMAP_HELVETICA_18, 0, 0, 0, t);
	sprintf(t, "LOADED:%d", gbullets);
	drawText(100, 1, 0, GLUT_BITMAP_HELVETICA_18, 0, 0, 0, t);
}
void printMsg()
{
	drawText(200, 720, 0, GLUT_BITMAP_HELVETICA_18, 1, 1, 1, msg);
}
void printScore()
{
	char t[20];
	sprintf(t, "Score : %d",score);
	drawText(650, 720, 0, GLUT_BITMAP_HELVETICA_18, 1, 1, 1, t);
}
void printTime()
{
	char t[20];
	if(ss<10)
		sprintf(t, "Time Left : %d:0%d", mm, ss);
	else
		sprintf(t, "Time Left : %d:%d", mm, ss);
	drawText(10, 720, 0, GLUT_BITMAP_HELVETICA_18, 1, 1, 1, t);
}


//To Set Targets next immediate Position - Translate Manual Function
void setTarget(int m,int target)
{
	int i;
	if(m==0)//For horizontal Motion
		if(target==0)
			for (i = 0;i < 4;i++)
			{
				body0[i][0] += lrmv[target];
				head0[i][0] += lrmv[target];
				hat0[i][0] += lrmv[target];
			}
		else
			for (i = 0;i < 4;i++)
			{
				body1[i][0] += lrmv[target];
				head1[i][0] += lrmv[target];
				hat1[i][0] += lrmv[target];
			}
	else if (m == 1)//For vertical Motion
		if(target==0)
			for (i = 0;i < 4;i++)
			{
				body0[i][1] += tdmv[target];
				head0[i][1] += tdmv[target];
				hat0[i][1] += tdmv[target];
			}
		else
			for (i = 0;i < 4;i++)
			{
				body1[i][1] += tdmv[target];
				head1[i][1] += tdmv[target];
				hat1[i][1] += tdmv[target];
			}
}

//Once Traslation is complete -- Find the Next Position
void newPos(int tar)
{
	int mov = ((rand() % 10)*rand())%10;
	int mov1 = ((rand() % 10)*rand()) % 10;
	mov = mov1 * mov;
	mov = mov % 10;
	if ((mov <= 6 || limit[tar]==1) && limit[tar]!=2)
	{
		motion[tar] = 0;
		if (limit[tar] == 1)
			limit[tar]++;
		int col = rand() % 6;
		while (col == lrcp[tar])
			col = rand() % 6;
		if (col < lrcp[tar])
			lrmv[tar] = -1;
		else
			lrmv[tar] = +1;
		printf("LRCP %d LRMV %d\n", lrcp[tar], lrmv[tar]);
		lrcp[tar] = col;
		setTarget(0,tar);
	}
	else
	{
		motion[tar] = 1;
		if (tdp[tar] == 1)
			tdp[tar] = 0;
		else
			tdp[tar] = 1;
		if (tdp[tar] == 0)
		{
			limit[tar] = 1;
			tdmv[tar] = -1;
		}
		else
		{
			tdmv[tar] = 1;
			limit[tar] = -1;
		}
		setTarget(1,tar);
	}
}

//Timer Function to process Target and to decrease the Time
void Timer(int value)
{
	if (value == 2 && !endgame)
	{
		if (ss == 0)
		{
			ss = 59;
			mm--;
		}
		else
			ss--;
		if (mm == 0 && ss == 0)
		{
			end(0);
			return;
		}
		glutTimerFunc(1000, Timer, 2);
	}
	else if (value == 3 && !endgame)
	{
		if (motion[0] == 0)//Horizontal
		{
			if (body0[0][0] != lrpos[lrcp[0]])
				setTarget(0,0);
			else
				newPos(0);	
		}
		else//Vertical
		{
			if (body0[0][1] != tdpos[tdp[0]])
				setTarget(1,0);
			else
				newPos(0);
		}
		if (motion[1] == 0)//Horizontal
		{
			if (body1[0][0] != lrpos[lrcp[1]])
				setTarget(0, 1);
			else
				newPos(1);
		}
		else//Vertical
		{
			if (body1[0][1] != tdpos[tdp[1]])
				setTarget(1, 1);
			else
				newPos(1);
		}
		glutTimerFunc(10, Timer, 3);
	}
	if(t3==1)
		glutPostRedisplay();
}

void drawPolygon(float r,float g,float b,int index,GLfloat poly[4][3])
{
	if ((model == 0 && index!=-1) || scene!=3)//model=0 texture
	{
		glEnable(GL_TEXTURE_2D);
		glColor3f(1.0, 1.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, text[index]);
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 0);
		glVertex3fv(poly[0]);
		glTexCoord2f(0, 1);
		glVertex3fv(poly[1]);
		glTexCoord2f(1, 1);
		glVertex3fv(poly[2]);
		glTexCoord2f(1, 0);
		glVertex3fv(poly[3]);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	else if(model==1 || index==-1)//solid fill
	{
		glDisable(GL_TEXTURE_2D);
		glColor3f(r, g, b);
		glBegin(GL_POLYGON);
			glVertex3fv(poly[0]);
			glVertex3fv(poly[1]);
			glVertex3fv(poly[2]);
			glVertex3fv(poly[3]);
		glEnd();
	}
	else//WireFrame
	{
		//printf("HH\n");
		glDisable(GL_TEXTURE_2D);
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
			glVertex3fv(poly[0]);
			glVertex3fv(poly[1]);
			glVertex3fv(poly[2]);
			glVertex3fv(poly[3]);
		glEnd();
	}
}

//Scene1 - Main Menu
void sc1()
{
	glutSetCursor(GLUT_CURSOR_NONE);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawPolygon(0.0, 0.5, 0.0, 10, infopoly);
	drawText(200, 230, 0, GLUT_BITMAP_HELVETICA_12, 1, 1, 1, "BANGALORE INSTITUTE OF TECHNOLOGY");
	drawText(200, 210, 0, GLUT_BITMAP_HELVETICA_12, 1, 1, 1, "DEPARTMENT OF CS & E");
	drawText(200, 190, 0, GLUT_BITMAP_HELVETICA_12, 1, 1, 1, "COMPUTER GRAPHICS & VISUALIZATION 15CSL68");
	drawText(200, 170.0, 0, GLUT_BITMAP_HELVETICA_12, 1, 1, 1, "ASSOCIATE PROF. B N SHANKAR GOWDA & ASSISTANT PROF. SHRUTHI B R");
	drawText(200, 150, 0, GLUT_BITMAP_HELVETICA_12, 1, 1, 1, "SAMKITH K JAIN-1BI16CS130----BHUNESH NARAYAN SINGH-1BI16CS192");
	drawText(200, 130, 0, GLUT_BITMAP_HELVETICA_12, 1, 1, 1, "PRESS --S-- TO START");
	drawText(200, 110, 0, GLUT_BITMAP_HELVETICA_12, 1, 1, 1, "PRESS --Q-- TO QUIT");
	glFlush();
}

void drawTree(int type)
{
	drawPolygon(40 / 255.0, 26 / 255.0, 13 / 255.0, 10, treebase);
	drawPolygon(6 / 255.0, 70 / 255.0, 11 / 255.0, 10, treep1);
	glPushMatrix();
	glTranslated(0, 30, 0);
	drawPolygon(6 / 255.0, 70 / 255.0, 11 / 255.0, 10, treep1);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 60, 0);
	drawPolygon(6 / 255.0, 70 / 255.0, 11 / 255.0, 10, treep1);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 90, 0);
	glBegin(type);
	glVertex3f(30.0,560.0,-615.0);
	glVertex3f(50.0,590.0,-615.0);
	glVertex3f(70.0,560.0,-615.0);
	glEnd();
	glPopMatrix();
}

void drawTreeInt(float tx,float ty,float sx,float sy,int k)
{
	glPushMatrix();
	if(k!=2)
		glScaled(sx, sy, 1.0);
	glTranslated(tx, ty, 0.0);
	if (model == 1)
		drawTree(GL_POLYGON);
	else if (model == 2)
		drawTree(GL_LINE_LOOP);
	glPopMatrix();
}

void sc3_static()
{	
	int i;
	glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawPolygon(0.0, 0.5, 0.0, 9, background);

	drawPolygon(1.0, 0.0, 0.0, 5, wall1t);
	drawPolygon(0.5, 0.0, 0.0, 4, wall1s);
	drawPolygon(1.0, 1.0, 0.0, 3, wall1f);

	drawPolygon(1.0, 0.0, 0.0, 8, wall2t);
	drawPolygon(0.5, 0.0, 0.0, 7, wall2s);
	drawPolygon(1.0, 1.0, 0.0, 6, wall2f);

	drawTreeInt(0.0, 0.0, 1.0, 1.0,1);
	drawTreeInt(105.0, 175.0, 0.8, 0.8,1);
	drawTreeInt(150.0,0.0, 0.0, 0.0, 2);
	drawTreeInt(300.0, 175.0, 0.8, 0.8, 1);
	drawTreeInt(305.0, 0.0, 0.0, 0.0, 2);
	drawTreeInt(490.0, 175.0, 0.8, 0.8, 1);
	drawTreeInt(455.0, 0.0, 0.0, 0.0, 2);
	drawTreeInt(675.0, 175.0, 0.8, 0.8, 1);
	drawTreeInt(605.0, 0.0, 0.0, 0.0, 2);

	if (model == 2)
	{
		drawPolygon(1.0, 1.0, 0.0, -6, wall2fb);
		drawPolygon(1.0, 1.0, 0.0, -6, wall2tb);
		drawPolygon(1.0, 1.0, 0.0, -6, wall1fb);
		drawPolygon(1.0, 1.0, 0.0, -6, wall1tb);
	}

	
	drawPolygon(0.0, 0.0, 0.0, -1, infobar);
	glPushMatrix();
	for (i = 0; i < sbullets; i++)
	{
		glTranslated(0.0,4.0,0.0);
		drawPolygon(0.0, 0.0, 0.0, -1, bullets);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslated(100.0, 0.0, 0.0);
	for (i = 0; i < gbullets; i++)
	{
		glTranslated(0.0, 4.0, 0.0);
		drawPolygon(0.0, 0.0, 0.0, -1, bullets);
	}
	glPopMatrix();
	
	/*glColor3f(0.0, 0.5, 0.0);
	glBegin(GL_POLYGON);//Background
		glVertex3i(0, 0, -749);
		glVertex3i(0, 750, -749);
		glVertex3i(750, 750, -749);
		glVertex3i(750, 0, -749);		
	glEnd();
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);//Wall1 Top
		glVertex3i(0, 200, -25);
		glVertex3i(700, 200, -25);
		glVertex3i(750, 250, -25);
		glVertex3i(50, 250,-25);
	glEnd();
	glColor3f(0.5, 0.0, 0.0);
	glBegin(GL_POLYGON);//Wall1 Side
		glVertex3i(750, 50, -25);
		glVertex3i(700, 0, -25);
		glVertex3i(700, 200, -25);
		glVertex3i(750, 250, -25);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	//data1 = stbi_load("wall2.jpg", &width, &height, &nrc, 0);
	//setImage("wall2.jpg", &text,data1,width1,height1);
	glBegin(GL_POLYGON);//Wall2
	glTexCoord2f(0, 0);
		glVertex3i(10, 400, -600);
		glTexCoord2f(0, 1);
		glVertex3i(10, 500, -600);
		glTexCoord2f(1, 1);
		glVertex3i(700, 500, -600);
		glTexCoord2f(1, 0);
		glVertex3i(700, 400, -600);
	glEnd();
	glDeleteTextures(1, &text);
	//stbi_image_free(data1);

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);//Wall2 Top
	glVertex3i(10, 500, -600);
	glVertex3i(700, 500, -600);
	glVertex3i(740, 525, -600);
	glVertex3i(50, 525, -600);
	glEnd();

	glColor3f(1.0, 1.0, 0.0);
	//setImage("wall2.jpg",&text);
	glBegin(GL_POLYGON);//Wall1
		glTexCoord2f(0, 0);
		glVertex3i(0, 0, -25);
		glTexCoord2f(0, 1);
		glVertex3i(0, 200, -25);
		glTexCoord2f(1, 1);
		glVertex3i(700, 200, -25);
		glTexCoord2f(1, 0);
		glVertex3i(700, 0, -25);
	glEnd();

	glColor3f(0.5, 0.0, 0.0);
	glBegin(GL_POLYGON);//Wall2 Side
		glVertex3i(740, 425, -600);
		glVertex3i(700, 400, -600);
		glVertex3i(700, 500, -600);
		glVertex3i(740, 525, -600);
	glEnd();
	*/
	/*glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);//Info Bar
	glVertex3i(0, 700, -60);
	glVertex3i(0, 750, -60);
	glVertex3i(750, 750, -60);
	glVertex3i(750, 700, -60);
	glEnd();*/
	glDisable(GL_TEXTURE_2D);
	printTime();
	printScore();
	printMsg();
	printBullets();
	glEnable(GL_TEXTURE_2D);

}
void target()
{
	/*glColor3f(1.0, 0.5, 1.0);
	setImage("body.jpg",&text,data[2],width,height);
	glBegin(GL_POLYGON);//Body
		glTexCoord2f(0, 0);
		glVertex3fv(body[0]);
		glTexCoord2f(0, 1);
		glVertex3fv(body[1]);
		glTexCoord2f(1, 1);
		glVertex3fv(body[2]);
		glTexCoord2f(1, 0);
		glVertex3fv(body[3]);
	glEnd();
	glDeleteTextures(1, &text);*/
	//stbi_image_free(data);

	drawPolygon(1.0, 0.5, 1.0, 2, body0);
	drawPolygon(1.0, 1.0, 0.5, 0, hat0);
	drawPolygon(1.0,0.5,0.5,1,head0);

	drawPolygon(1.0, 0.5, 1.0, 2, body1);
	drawPolygon(1.0, 1.0, 0.5, 0, hat1);
	drawPolygon(1.0, 0.5, 0.5, 1, head1);
/*
	glColor3f(1.0, 1.0, 0.5);
	//data = stbi_load("hat.jpg", &width, &height, &nrc, 0);
	//setImage("hat.jpg", &text,data);
	glBegin(GL_POLYGON);//Hat
		glTexCoord2f(0, 0);
		glVertex3fv(hat[0]);
		glTexCoord2f(0, 1);
		glVertex3fv(hat[1]);
		glTexCoord2f(1, 1);
		glVertex3fv(hat[2]);
		glTexCoord2f(1, 0);
		glVertex3fv(hat[3]);
	glEnd();
	//glDeleteTextures(1, &text);
	

	glColor3f(1.0, 0.5, 0.5);
	//data = stbi_load("head.jpg", &width, &height, &nrc, 0);
	//setImage("head.jpg", &text,data);

	glBegin(GL_POLYGON);//Head
		glTexCoord2f(0, 0);
		glVertex3fv(head[0]);
		glTexCoord2f(0, 1);
		glVertex3fv(head[1]);
		glTexCoord2f(1, 1);
		glVertex3fv(head[2]);
		glTexCoord2f(1, 0);
		glVertex3fv(head[3]);
	glEnd();
	//glDeleteTextures(1, &text);
	//stbi_image_free(data);*/
	
}
void sc3()
{
	if (t3 == 0)
	{
		reset();
		createMenu();
		glutTimerFunc(1000, Timer, 2);
		glutTimerFunc(10, Timer, 3);//for calling timer function only once
		//sc2_static();
		t3 = 1;
	}
	sc3_static();
	target();
	glFlush();
}
void sc4()
{
	glutSetCursor(GLUT_CURSOR_NONE);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	drawPolygon(0.0, 0.5, 0.0, 12, infopoly);
	drawText(200, 170, 0, GLUT_BITMAP_HELVETICA_12, 1, 1, 1, msg);
	drawText(200, 150, 0, GLUT_BITMAP_HELVETICA_12, 1, 1, 1, "PRESS --M-- TO MAIN MENU");
	drawText(200, 130, 0, GLUT_BITMAP_HELVETICA_12, 1, 1, 1, "PRESS --Q-- TO QUIT");
	glFlush();
}

void sc2()
{
	if (t2 == 0)
	{
		sprintf(msg, "Current Difficulty Level : EASY");
		createMenu();
		t2 = 1;
	}
	glutSetCursor(GLUT_CURSOR_INHERIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawPolygon(0.0, 0.5, 0.0, 11, infopoly);
	drawText(200, 190.0, 0, GLUT_BITMAP_HELVETICA_12, 1, 1, 1, msg);
	drawText(200, 170, 0, GLUT_BITMAP_HELVETICA_12, 1, 1, 1, "USE MENU TO CHOOSE DIFFICULTY LEVEL");
	drawText(200, 150, 0, GLUT_BITMAP_HELVETICA_12, 1, 1, 1, "PRESS --S-- TO START");
	drawText(200, 130, 0, GLUT_BITMAP_HELVETICA_12, 1, 1, 1, "PRESS --Q-- TO QUIT");
	glFlush();
}

//Display Function
void display() 
{
	switch (scene)
	{
	case 1:	
		glDisable(GL_LIGHTING);
		glutDestroyMenu(menuid);
		sc1();//Start Screen
		glutKeyboardFunc(keyboard1);
		glutMouseFunc(NULL);
		break;
	case 2:
		glDisable(GL_LIGHTING);
		sc2();
		break;
	case 3: 
		//glEnable(GL_LIGHTING);
		//glutPassiveMotionFunc(mousePassive);
		sc3();//Game
		glutMouseFunc(mouse);
		glutKeyboardFunc(NULL);
		break;
	case 4:
		glDisable(GL_LIGHTING);
		glutDestroyMenu(menuid);
		sc4();//Game Over - LOSS OR WIN
		glutKeyboardFunc(keyboard2);
		glutMouseFunc(NULL);
		break;
	}
}

void init()
{
	/*float lightPos[] = { 375.0, 375.0,-590.0, 1.0 }; // Spotlight position.
	float spotDirection[] = { 0.0, 0.0, -1.0 }; // Spotlight direction.   
	float spotAngle = 3.0;
	float spotExponent = 2.0;

	// Light property vectors.
	float lightAmb[] = { 0.5, 0.5, 0.5, 1.0 };
	float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	float globAmb[] = { 0.5, 0.5, 0.5, 1.0 };

	// Light properties.
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);

	glEnable(GL_LIGHT0); // Enable particular light source.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Enable local viewpoint.

	// Material property vectors.
	float matSpec[] = { 0.5, 0.5, 0.5, 1.0 };
	float matShine[] = { 25.0 };

	// Material properties shared by all the spheres.
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotAngle);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);*/
	
	t2 = 0;
}
int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_SINGLE);
	glutInitWindowSize(750, 750);
	glutCreateWindow("War Over Peace");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	init();
	glOrtho(0,750, 0,750,-1,750);
	glEnable(GL_TEXTURE_2D);
	setImageData();

	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}
