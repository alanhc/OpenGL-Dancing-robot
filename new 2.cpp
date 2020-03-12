
#include <math.h>
int fps=30;
void timer(int t)
{

    glutTimerFunc(33/2.0, timer, t+1);///每等33毫秒 就執行




    if(t%fps==0){ ///每frame 持續多久
        if(fin==NULL) fin=fopen("motion.txt", "r");
        fscanf(fin, "%d", &dur);

        printf(" [%d] ", t/fps);
        for(int i=0; i<100; i++){
            oldAngle[i] = newAngle[i];
            fscanf(fin, "%f", &newAngle[i]);
            printf("%f ",newAngle[i]);
        }
        printf("\n");
    }



    float alpha= (t%fps)/(float)fps;
    for(int i=0; i<100; i++){
        angle[i] = alpha * newAngle[i] + (1-alpha) * oldAngle[i];
    }
    glutPostRedisplay();
    //printf("t:%d %f %f \n",t, newAngle,oldAngle);
}