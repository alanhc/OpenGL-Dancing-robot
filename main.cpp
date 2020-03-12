#include <GL/glut.h>
#include <stdio.h>
#include "glm.h"
#include "CMP3_MCI.h"
#include <opencv/highgui.h> ///for cvLoadImage()
#include <opencv/cv.h> ///for cvCvtColor()
#include "CMP3_MCI.h"

CMP3_MCI myMP3;///(2) 宣告一個我們要用的物件

GLMmodel * pmodel1 = NULL;
GLMmodel * pmodel2 = NULL;
GLMmodel * pmodel3 = NULL;
FILE * fout = NULL;
FILE * fin = NULL;
FILE * fin2 = NULL;
FILE * fin3 = NULL;



float angle[100];
int angleID;
int mode=0;
int select=0;
int axis=1;



const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

float newAngle[100];
float oldAngle[100];
int time=0;;




void prepareModel()
{
    if (!pmodel1) {
        pmodel1 = glmReadOBJ("./models/joint.obj");
        if (!pmodel1) exit(0);///讀不到離開
        glmUnitize(pmodel1); ///調整大小
        glmFacetNormals(pmodel1);///調法向量
        glmVertexNormals(pmodel1, 90.0);///調法向量
    }
    if (!pmodel2) {
        pmodel2 = glmReadOBJ("./models/joint2.obj");

        if (!pmodel2) exit(0);///讀不到離開
        glmUnitize(pmodel2); ///調整大小
        glmFacetNormals(pmodel2);///調法向量
        glmVertexNormals(pmodel2, 90.0);///調法向量
    }
    if (!pmodel3) {
        pmodel3 = glmReadOBJ("./models/Limb.obj");

        if (!pmodel3) exit(0);///讀不到離開
        glmUnitize(pmodel3); ///調整大小
        glmFacetNormals(pmodel3);///調法向量
        glmVertexNormals(pmodel3, 90.0);///調法向量
    }
}
GLUquadric * quad;
GLuint id1, id2;
void up()
{
    /// joint center down--------------------------------------

    glPushMatrix();

            glRotatef(angle[0], 1,0,0);
            glRotatef(angle[1], 0,1,0);
            glRotatef(angle[2], 0,0,1);
        glTranslatef(0,2,0);

        ///texture

        int size=1;

        glDisable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        glColor3f(1,1,1);



        glBindTexture(GL_TEXTURE_2D, id2);
        glmDraw(pmodel1, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
        ///matrix mode



        glDisable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
        ///texture



        if (select==0) {

        }
        /*
        /// joint down right
        glPushMatrix();
            glRotatef(angle[9], 0,0,1);
            glTranslatef(2, 0,0);
            glmDraw(pmodel2, GLM_SMOOTH | GLM_MATERIAL);
            ///limb down right
            glPushMatrix();
            glRotatef(angle[10], 0,0,1);
            glTranslatef(2, 0,0);

            glScalef(5,5,5);
            glmDraw(pmodel3, GLM_SMOOTH | GLM_MATERIAL);
            glPopMatrix();
        glPopMatrix();
        */
        /*
        /// joint down left
        glPushMatrix();
            glColor3f(1,0,0);
            glRotatef(angle[11], 0,0,1);
            glTranslatef(-2, 0,0);


            glmDraw(pmodel2, GLM_SMOOTH | GLM_MATERIAL);

            ///limb down left
            glPushMatrix();
            glRotatef(angle[12], 0,0,1);
            glTranslatef(-2, 0,0);


            glRotatef(180, 0,1,0);
            glScalef(5,5,5);
            glmDraw(pmodel3, GLM_SMOOTH | GLM_MATERIAL);
            glPopMatrix();

        glPopMatrix();
        */
    glPopMatrix();
    /// joint center down--------------------------------------

}
void center()
{
    ///center---------------------------------------------------
    glPushMatrix();



            glRotatef(angle[3], 1,0,0);
            glRotatef(angle[4], 0,1,0);
            glRotatef(angle[5], 0,0,1);
        glTranslatef(0,2,0);


        glmDraw(pmodel1, GLM_SMOOTH | GLM_MATERIAL);


        /// joint center right
        glPushMatrix();

                glRotatef(angle[15], 1,0,0);
                glRotatef(angle[16], 0,1,0);
                glRotatef(angle[17], 0,0,1);

            glTranslatef(2, 0,0);

            glmDraw(pmodel2, GLM_SMOOTH | GLM_MATERIAL);
            ///limb center right
            glPushMatrix();

                glRotatef(angle[27], 1,0,0);
                glRotatef(angle[28], 0,1,0);
                glRotatef(angle[29], 0,0,1);

            glTranslatef(2, 0,0);

            glScalef(5,5,5);
            glmDraw(pmodel3, GLM_SMOOTH | GLM_MATERIAL);
            glPopMatrix();
            ///limb center right
        glPopMatrix();
        /// joint center left
        glPushMatrix();
            glColor3f(1,0,0);

                glRotatef(angle[9], 1,0,0);
                glRotatef(angle[10], 0,1,0);
                glRotatef(angle[11], 0,0,1);


            glTranslatef(-2, 0,0);

            glmDraw(pmodel2, GLM_SMOOTH | GLM_MATERIAL);
            ///limb center left
            glPushMatrix();

                glRotatef(angle[21], 1,0,0);
                glRotatef(angle[22], 0,1,0);
                glRotatef(angle[23], 0,0,1);

            glTranslatef(-2, 0,0);

            glRotatef(180, 0,1,0);
            glScalef(5,5,5);
            glmDraw(pmodel3, GLM_SMOOTH | GLM_MATERIAL);
            glPopMatrix();
        glPopMatrix();
        ///down body--------------------------------------
        //down();
        ///down body--------------------------------------

        ///up body--------------------------------------
        //up();
        ///up body--------------------------------------
        /// center ***************************************
        glPushMatrix();
            up();
        glPopMatrix();
        /// center ***************************************

    glPopMatrix();
    ///center---------------------------------------------------


}

void down()
{
    /// joint center down--------------------------------------
    glPushMatrix();


            glRotatef(angle[6], 1,0,0);
            glRotatef(angle[7], 0,1,0);
            glRotatef(angle[8], 0,0,1);

        glmDraw(pmodel1, GLM_SMOOTH | GLM_MATERIAL);
        /// joint down right--------------------------------------
        glPushMatrix();

                glRotatef(angle[18], 1,0,0);
                glRotatef(angle[19], 0,1,0);
                glRotatef(angle[20], 0,0,1);

            glTranslatef(2, 0,0);


            glmDraw(pmodel2, GLM_SMOOTH | GLM_MATERIAL);
            /// limb down right--------------------------------------
            glPushMatrix();

                glRotatef(angle[30], 1,0,0);
                glRotatef(angle[31], 0,1,0);
                glRotatef(angle[32], 0,0,1);

            glTranslatef(2, 0,0);

            glScalef(5,5,5);
            glmDraw(pmodel3, GLM_SMOOTH | GLM_MATERIAL);
            glPopMatrix();
            /// limb down right--------------------------------------
        glPopMatrix();
        /// joint down right--------------------------------------

        /// joint down left--------------------------------------
        glPushMatrix();
            glColor3f(1,0,0);

                glRotatef(angle[12], 1,0,0);
                glRotatef(angle[13], 0,1,0);
                glRotatef(angle[14], 0,0,1);

            glTranslatef(-2, 0,0);


            glmDraw(pmodel2, GLM_SMOOTH | GLM_MATERIAL);

            /// limb down left--------------------------------------
            glPushMatrix();

                glRotatef(angle[24], 1,0,0);
                glRotatef(angle[25], 0,1,0);
                glRotatef(angle[26], 0,0,1);

            glTranslatef(-2, 0,0);


            glRotatef(180, 0,1,0);
            glScalef(5,5,5);

            glmDraw(pmodel3, GLM_SMOOTH | GLM_MATERIAL);
            glPopMatrix();
            /// limb down left--------------------------------------
        glPopMatrix();
        /// joint down left--------------------------------------

        /// center ***************************************
        glPushMatrix();
            center();
        glPopMatrix();
        /// center ***************************************
    glPopMatrix();
    /// joint center down--------------------------------------

}


int myTexture(char *filename)
{
    IplImage * img = cvLoadImage(filename); ///OpenCV讀圖
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV轉色彩 (需要cv.h)
    glEnable(GL_TEXTURE_2D); ///1. 開啟貼圖功能
    GLuint id; ///準備一個 unsigned int 整數, 叫 貼圖ID
    glGenTextures(1, &id); /// 產生Generate 貼圖ID
    glBindTexture(GL_TEXTURE_2D, id); ///綁定bind 貼圖ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖T, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖S, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// 貼圖參數, 放大時的內插, 用最近點
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// 貼圖參數, 縮小時的內插, 用最近點
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}

void display()
{


    ///projection--------------
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(80,1,1,10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.3, 3, ///eye
              0.0, 0.0, 0.0, ///center
              0, 1, 0);///up

    ///projection--------------------
//    glColor3f(0,0,0);
    glColor3f(1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float size=2;
    ///background-----
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, id1);
    //glutSolidTeapot(0.3);
    glBegin(GL_POLYGON);
        glTexCoord2f(0, 0); glVertex3f(-size, +size, -size);
        glTexCoord2f(0, 1); glVertex3f(-size, -size, -size);
        glTexCoord2f(1, 1); glVertex3f(+size, -size, -size);
        glTexCoord2f(1, 0); glVertex3f(+size, +size, -size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, id1);
    glBegin(GL_POLYGON);
        glTexCoord2f(0, 0); glVertex3f(-size, -size,+size/2);
        glTexCoord2f(0, 1); glVertex3f(-size, -size,-size);
        glTexCoord2f(1, 1); glVertex3f(+size, -size,-size);
        glTexCoord2f(1, 0); glVertex3f(+size, -size,+size/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    ///background-----


    glPushMatrix();
        glScalef(1.5,1.5,1.5);
        //down();
            //glTranslatef(body_pos[0],,body_z);
        glTranslatef(angle[54]/100.0,angle[55]/100.0,angle[56]/100.0);

        glTranslatef(0,-.9,0);


        /// robot--------------------------------------
        glPushMatrix();

            //glTranslatef(0,-.5,0);
                glRotatef(angle[51],1,0,0);
                glRotatef(angle[52],0,1,0);
                glRotatef(angle[53],0,0,1);
            glTranslatef(0,1,0);

            glScalef(.15,.15,.15);
            down();
        glPopMatrix();
        /// robot--------------------------------------



        /// location point-------------------------------

        glPushMatrix();

            glScalef(.01,.01,.01);
            glmDraw(pmodel1, GLM_SMOOTH | GLM_MATERIAL);
            glTranslatef(0,1,0);
        glPopMatrix();

        /// location point-------------------------------

    glPopMatrix();

    glutSwapBuffers();
}


int oldX;
void mouse(int button, int state, int x, int y)
{
    oldX = x;
}

float a=0;
void motion(int x, int y)
{
    int control = 3*select+axis-1;
    if (mode==1&&select>=0) angle[control] += (x-oldX);
    if (mode==2) {
        angle[50+axis]+=(x-oldX);
    }
    if (mode==3) {
        angle[53+axis]+=(x-oldX);
        angle[53+axis]+=(x-oldX);
    }
    oldX = x;
    //printf("control:%d\n",control);
    a++;
    display();
}

#include <math.h>
int fps=30;
void timer(int t)
{
    if (t%(fps*3)==0) {
        glMatrixMode(GL_TEXTURE);

            glRotatef(15,1,0,1);
        glMatrixMode(GL_MODELVIEW);
    }
    glutTimerFunc(33/2.0, timer, t+1);///每等33毫秒 就執行



    if(t%fps==0){ ///每frame 持續多久
        if(fin==NULL) fin=fopen("readActions.txt", "r");


        printf(" [%d] ", t/fps);
        if ((t/fps)==90) {
            glutDestroyWindow(1);
        }
        for(int i=0; i<100; i++){
            oldAngle[i] = newAngle[i];
            fscanf(fin, "%f", &newAngle[i]);

        }
        printf("beat");
        printf("\n");





    }



    float alpha= (t%fps)/(float)fps;
    for(int i=0; i<100; i++){
        angle[i] = alpha * newAngle[i] + (1-alpha) * oldAngle[i];
    }
    glutPostRedisplay();
    //printf("t:%d %f %f \n",t, newAngle,oldAngle);
}

void keyboard(unsigned char key, int x, int y)
{


    if (key=='1') axis=1;
    if (key=='2') axis=2;
    if (key=='3') axis=3;
    if (key=='d') {

            glutDestroyWindow(1);

    }
    printf("press:%d\n",key);
    printf("axis:%d\n",axis);
    if (key=='w') {
        if (fout==NULL) fout=fopen("motion.txt", "w+");
        for (int i=0; i<100; i++) {
            printf( "%.1f ", angle[i] );
            fprintf( fout, "%.1f ", angle[i]);

        }
        printf("record\n");
        fprintf(fout, "\n");

    }
    if(key=='r'){
        if(fin==NULL) fin = fopen("motion.txt", "rt");
        for(int i=0; i<100;i++){
            fscanf(fin, "%f", &angle[i]);
        }
    }
    if(key=='p'){
        glutTimerFunc(500, timer, 0);
        myMP3.Play();
        if(fin3==NULL) fin3=fopen("readActions.txt.txt", "rt");
        for(int i=0; i<100; i++){
            fscanf(fin, "%f", &newAngle[i]);
        }
    }
    if (key=='m') {
        myMP3.Play();
    }
    if (key=='t') {
        if(fin2==NULL) fin2 = fopen("t_pose.txt", "rt");
        for(int i=0; i<100;i++){
            fscanf(fin2, "%f", &angle[i]);
        }
    }
    glutPostRedisplay();
}

void processMenu(int option) {
    if (option<20) {
        select=option;
        mode=1;
        printf("select:%d\n", option);
    }
    else if (option<40) {
        mode = option-30;
        printf("mode:%d\n", mode);
    }
}
void createGLUTMenus() {

	int menu;
	int submenu;
	//glutAddMenuEntry("Sub 1",1);
	//glutAddMenuEntry("Sub 2",2);

	menu = glutCreateMenu(processMenu);
	glutAddMenuEntry("**select**", -1);
	glutAddMenuEntry(" 0:head",0);

    glutAddMenuEntry(" 1:center body",1);
    glutAddMenuEntry(" 3:center left joint",3);
    glutAddMenuEntry(" 7:center left limb",7);
    glutAddMenuEntry(" 5:center right joint",5);
    glutAddMenuEntry(" 9:center right limb",9);

    glutAddMenuEntry(" 2:down body",2);
    glutAddMenuEntry(" 4:down left joint",4);
    glutAddMenuEntry(" 8:down left limb",8);
    glutAddMenuEntry(" 6:down right joint",6);
    glutAddMenuEntry("10:down right limb",10);






    glutAddMenuEntry("**mode**", -2);
    glutAddMenuEntry("rotate",31);
    glutAddMenuEntry("move body rotate",32);
    glutAddMenuEntry("move body translate",33);


	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char ** argv)
{
    myMP3.Load("music.mp3");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(800,800);

    glutCreateWindow("alanhc CGfinal");

    glMatrixMode(GL_TEXTURE);

            glRotatef(180,1,0,0);
    glMatrixMode(GL_MODELVIEW);
    ///---texture
    id1 = myTexture("image/background.jpg");
    id2 = myTexture("image/happy.png");




    glClearColor(1,1,1,1);
    //glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
 //   glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    prepareModel();

    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    createGLUTMenus();///menu

    glutMainLoop();
}
