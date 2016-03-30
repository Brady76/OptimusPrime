/*
 *  Textures and Lighting
 *
 *  Demonstrates using lighting and textures.
 *
 *  Key bindings:
 *  l          Toggle lighting on/off
 *  t          Change textures
 *  m          Toggles texture mode modulate/replace
 *  a/A        decrease/increase ambient light
 *  d/D        decrease/increase diffuse light
 *  s/S        decrease/increase specular light
 *  e/E        decrease/increase emitted light
 *  n/N        Decrease/increase shininess
 *  []         Lower/rise light
 *  x          Toggle axes
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx229.h"
int mode=0;       //  Texture mode
int ntex=0;       //  Cube faces
int axes=0;       //  Display axes
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int light=1;      //  Lighting
int rep=1;        //  Repitition
int perspective = 0;
double asp=1;     //  Aspect ratio
double dim=50.0;   //  Size of world
// Light values
int dusk = 1;
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%) 
int ambientnight = 10;
int diffusenight = 0;
int specularnight = 0; 
int shininess =   0;  // Shininess (power of two)
float shinyvec[1];    // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light
double ArmAngles[2] = {0.0,0.0};
double LegAngles[2] = {0.0,0.0};
double TransformAngle = 0.0;
double HeadTransformAngle = 0.0;
double TireAngle = 0.0;
unsigned int texture[18]; // Texture names
typedef int bool;
#define true 1
#define false 0
static bool leftarm = true;
static bool rightarm = false;
static bool leftleg = false;
static bool rightleg = true;
static bool cartransformbit = false;
static bool humantransformbit = true;
static bool midtransformbit = false;
static bool transformpeak = false;
static bool transformcomplete = false;
static bool firstperson = false;
static bool day = true;
double OptimusX = 0;
double OptimusY = 0;
double OptimusZ = 0;
double OptimusAngle = 0;
double CameraAngle = 180;
double CameraX = 0;
double CameraZ = 0;
double ExtraLength = 0;
double ExtraWidth = 0;
static void Torso(double x, double y, double z,double dx,double dy,double dz,double th){
   //TORSO
   //Front
   glPushMatrix();
   glTranslated(x,y,z);   
   glRotated(th,0,1,0);
   glRotated(TransformAngle,1,0,0);
   glScaled(dx,dy,dz);
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glColor3f(1,1,1);
   //Front
   glTexCoord2f(0,0); glVertex3f(-1,-2 - ExtraWidth,+0.5 + ExtraLength);
   glTexCoord2f(1,0); glVertex3f(+1,-2 - ExtraWidth,+0.5 + ExtraLength);
   glTexCoord2f(1,0.55); glVertex3f(+1,0,+0.5 + ExtraLength);
   glTexCoord2f(0,0.55); glVertex3f(-1,0,+0.5 + ExtraLength);
   glEnd();
   glBegin(GL_QUADS);
   glTexCoord2f(0,0.55); glVertex3f(-1,0,+0.5);
   glTexCoord2f(1,0.55); glVertex3f(+1,0,+0.5);
   glTexCoord2f(1,1); glVertex3f(+1,+2,+0.5);
   glTexCoord2f(0,1); glVertex3f(-1,+2,+0.5);
   glEnd();
   //Back
   glBindTexture(GL_TEXTURE_2D,texture[4]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3f(-1,-2,-0.5 - ExtraLength);
   glTexCoord2f(1,0); glVertex3f(+1,-2,-0.5 - ExtraLength);
   glTexCoord2f(1,1); glVertex3f(+1,+2,-0.5 - ExtraLength);
   glTexCoord2f(0,1); glVertex3f(-1,+2,-0.5- ExtraLength);
   glEnd();
   //Left
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3f(-1,-2 - ExtraWidth,-0.5 - ExtraLength);
   glTexCoord2f(1,0); glVertex3f(-1,-2 - ExtraWidth,+0.5 + ExtraLength);
   glTexCoord2f(1,0.55); glVertex3f(-1,0,+0.5 + ExtraLength);
   glTexCoord2f(0,0.55); glVertex3f(-1,0,-0.5-ExtraLength);
   glEnd();
   glBegin(GL_QUADS);
   glTexCoord2f(0,0.55); glVertex3f(-1, 0,-0.5 - ExtraLength);
   glTexCoord2f(1,0.55); glVertex3f(-1, 0, +0.5);
   glTexCoord2f(1,1); glVertex3f(-1,+2,+0.5);
   glTexCoord2f(0,1); glVertex3f(-1,+2,-0.5 - ExtraLength);
   glEnd();
   //Right
   glBegin(GL_QUADS);
   glNormal3f(+1,0,0);
   glTexCoord2f(0,0); glVertex3f(+1,-2 - ExtraWidth,-0.5 - ExtraLength);
   glTexCoord2f(1,0); glVertex3f(+1,-2 - ExtraWidth,+0.5 + ExtraLength);
   glTexCoord2f(1,0.55); glVertex3f(+1,0,+0.5 + ExtraLength);
   glTexCoord2f(0,0.55); glVertex3f(+1,0,-0.5 - ExtraLength);
   glEnd();
   glBegin(GL_QUADS);
   glTexCoord2f(0,0.55); glVertex3f(+1, 0,-0.5 - ExtraLength);
   glTexCoord2f(1,0.55); glVertex3f(+1, 0, +0.5);
   glTexCoord2f(1,1); glVertex3f(+1,+2,+0.5);
   glTexCoord2f(0,1); glVertex3f(+1,+2,-0.5 - ExtraLength);
   glEnd();
   //Top
   glBindTexture(GL_TEXTURE_2D,texture[4]);
   glBegin(GL_QUADS);
   glNormal3f(0,+1,0);
   glTexCoord2f(0,0); glVertex3f(-1, +2, +0.5);
   glTexCoord2f(1,0); glVertex3f(+1, +2, +0.5);
   glTexCoord2f(1,1); glVertex3f(+1, +2, -0.5 - ExtraLength);
   glTexCoord2f(0,1); glVertex3f(-1, +2, -0.5 - ExtraLength);
   glEnd();
   glBegin(GL_QUADS);
   glTexCoord2f(0,0); glVertex3f(-1, +0, +0.5 + ExtraLength);
   glTexCoord2f(1,0); glVertex3f(+1, +0, +0.5 + ExtraLength);
   glTexCoord2f(1,1); glVertex3f(+1, +0, -0.5 - ExtraLength);
   glTexCoord2f(0,1); glVertex3f(-1, +0, -0.5 - ExtraLength);
   glEnd();
   //Bottom
   glBegin(GL_QUADS);
   glNormal3f(0,-1,0);
   glTexCoord2f(0,0); glVertex3f(-1, -2 - ExtraWidth, +0.5 + ExtraLength);
   glTexCoord2f(1,0); glVertex3f(+1, -2 - ExtraWidth, +0.5 + ExtraLength);
   glTexCoord2f(1,1); glVertex3f(+1, -2 - ExtraWidth, -0.5 - ExtraLength);
   glTexCoord2f(0,1); glVertex3f(-1, -2 - ExtraWidth, -0.5- ExtraLength); 
   glEnd();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}
//HEAD
static void Head(double x, double y, double z, double dx, double dy, double dz, double th){
   glPushMatrix();
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glRotated(TransformAngle,1,0,0);
   //glPushMatrix();
   glRotated(HeadTransformAngle,0,1,0);
   //glPopMatrix();
   glScaled(dx,dy,dz);
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   glColor3f(1,1,1);
   //Front
   if(humantransformbit){
	   glBindTexture(GL_TEXTURE_2D,texture[0]);
   }
   else{
	   glBindTexture(GL_TEXTURE_2D,texture[1]);
   }
   glBegin(GL_QUADS);
   glNormal3f(0,0,+1);
   glTexCoord2f(0,0); glVertex3f(-0.5 - 1.6*ExtraWidth,+2,+0.45);
   glTexCoord2f(1,0); glVertex3f(+0.5 + 1.6*ExtraWidth,+2,+0.45);
   glTexCoord2f(1,1); glVertex3f(+0.5 + 1.6*ExtraWidth,+3.0,+0.45);
   glTexCoord2f(0,1); glVertex3f(-0.5 - 1.6*ExtraWidth,+3.0,+0.45);
   glEnd();
   //Back
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3f(-0.5 - 1.6* ExtraWidth,+2,-0.45);
   glTexCoord2f(1,0); glVertex3f(+0.5 + 1.6* ExtraWidth,+2,-0.45);
   glTexCoord2f(1,1); glVertex3f(+0.5 + 1.6* ExtraWidth,+3.0,-0.45);
   glTexCoord2f(0,1); glVertex3f(-0.5 - 1.6*ExtraWidth,+3.0,-0.45);
   glEnd();
   //Left
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3f(-0.5 - 1.6*ExtraWidth,+2,-0.45);
   glTexCoord2f(1,0); glVertex3f(-0.5 - 1.6*ExtraWidth,+2,+0.45);
   glTexCoord2f(1,1); glVertex3f(-0.5 - 1.6*ExtraWidth,+3.0,+0.45);
   glTexCoord2f(0,1); glVertex3f(-0.5 - 1.6*ExtraWidth,+3.0,-0.45);
   glEnd();
   //Right
   glBegin(GL_QUADS);
   glNormal3f(+1,0,0);
   glTexCoord2f(0,0); glVertex3f(+0.5 + 1.6*ExtraWidth,+2,-0.45);
   glTexCoord2f(1,0); glVertex3f(+0.5 + 1.6*ExtraWidth,+2,+0.45);
   glTexCoord2f(1,1); glVertex3f(+0.5 + 1.6*ExtraWidth,+3.0,+0.45);
   glTexCoord2f(0,1); glVertex3f(+0.5 + 1.6*ExtraWidth,+3.0,-0.45);
   glEnd();
   //Top 
   glBindTexture(GL_TEXTURE_2D,texture[10]);
   glNormal3f(0,+1,0);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0); glVertex3f(-0.5 - 1.6*ExtraWidth,+3.0,+0.45);
   glTexCoord2f(1,0); glVertex3f(+0.5 + 1.6*ExtraWidth,+3.0,+0.45);
   glTexCoord2f(1,1); glVertex3f(+0.5 + 1.6*ExtraWidth,+3.0,-0.45);
   glTexCoord2f(0,1); glVertex3f(-0.5 - 1.6*ExtraWidth,+3.0,-0.45);
   glEnd();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}
static void LeftArm(double x, double y, double z, double dx, double dy, double dz,double th){
   //LEFT ARM
   glPushMatrix();
   glTranslated(x,1,z);
   glRotated(th,0,1,0);
   glRotated(ArmAngles[0],1,0,0);
   glRotated(th,0,-1,0);
   glTranslated(-x,-1,-z);
   glTranslated(x,y,z);   
   glRotated(th,0,1,0);
   glRotated(TransformAngle,1,0,0);
   glScaled(dx,dy,dz);
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   glColor3f(1,1,1);
   //Front
   glNormal3f(0,0,+1);
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0); glVertex3f(-1.5, -2.5, +0.5);
   glTexCoord2f(1,0); glVertex3f(-1,-2.5,+0.5);
   glTexCoord2f(1,1); glVertex3f(-1,+2,+0.5);
   glTexCoord2f(0,1); glVertex3f(-1.5,+2,+0.5);
   glEnd();
   //Back
   glBindTexture(GL_TEXTURE_2D,texture[7]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3f(-1.5, -2.5, -0.5);
   glTexCoord2f(1,0); glVertex3f(-1,-2.5,-0.5);
   glTexCoord2f(1,1); glVertex3f(-1,+2,-0.5);
   glTexCoord2f(0,1); glVertex3f(-1.5,+2,-0.5);
   glEnd();
   //Left
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3f(-1.5,-2.5,-0.5);
   glTexCoord2f(1,0); glVertex3f(-1.5,-2.5,+0.5);
   glTexCoord2f(1,1); glVertex3f(-1.5,+2,+0.5);
   glTexCoord2f(0,1); glVertex3f(-1.5,+2,-0.5);
   glEnd();
   //Right
   glBindTexture(GL_TEXTURE_2D,texture[7]);
   glBegin(GL_QUADS);
   glNormal3f(+1,0,0);
   glTexCoord2f(0,0); glVertex3f(-1,-2.5,-0.5);
   glTexCoord2f(1,0); glVertex3f(-1,-2.5,+0.5);
   glTexCoord2f(1,1); glVertex3f(-1,+2,+0.5);
   glTexCoord2f(0,1); glVertex3f(-1,+2,-0.5);
   glEnd();
   //Top
   glBegin(GL_QUADS);
   glNormal3f(0,+1,0);
   glTexCoord2f(0,0); glVertex3f(-1.5,+2,+0.5);
   glTexCoord2f(1,0); glVertex3f(-1,+2,+0.5);
   glTexCoord2f(1,1); glVertex3f(-1,+2,-0.5);
   glTexCoord2f(0,1); glVertex3f(-1.5,+2,-0.5);
   glEnd();
   //Bottom
   glBegin(GL_QUADS);
   glNormal3f(0,-1,0);
   glTexCoord2f(0,0); glVertex3f(-1.5,-2.5,+0.5);
   glTexCoord2f(1,0); glVertex3f(-1,-2.5,+0.5);
   glTexCoord2f(1,1); glVertex3f(-1,-2.5,-0.5);
   glTexCoord2f(0,1); glVertex3f(-1.5,-2.5,-0.5);
   glEnd();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}
   //RIGHT ARM
static void RightArm(double x, double y, double z, double dx, double dy, double dz, double th){
   //Front
   glPushMatrix();
   glTranslated(x,1,z);
   glRotated(th,0,1,0);
   glRotated(ArmAngles[1], 1, 0, 0);
   glRotated(th,0,-1,0);
   glTranslated(-x,-1,-z);
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glRotated(TransformAngle,1,0,0);
   glScaled(dx,dy,dz);   
   glColor3f(1,1,1);
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   //FRONT
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,+1);
   glTexCoord2f(0,0); glVertex3f(+1.5, -2.5, +0.5);
   glTexCoord2f(1,0); glVertex3f(+1,-2.5,+0.5);
   glTexCoord2f(1,1); glVertex3f(+1,+2,+0.5);
   glTexCoord2f(0,1); glVertex3f(+1.5,+2,+0.5);
   glEnd();
   //Back
   glBindTexture(GL_TEXTURE_2D,texture[7]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3f(+1.5, -2.5, -0.5);
   glTexCoord2f(1,0); glVertex3f(+1,-2.5,-0.5);
   glTexCoord2f(1,1); glVertex3f(+1,+2,-0.5);
   glTexCoord2f(0,1); glVertex3f(+1.5,+2,-0.5);
   glEnd();
   //Right
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_QUADS);
   glNormal3f(+1,0,0);
   glTexCoord2f(0,0); glVertex3f(+1.5,-2.5,-0.5);
   glTexCoord2f(1,0); glVertex3f(+1.5,-2.5,+0.5);
   glTexCoord2f(1,1); glVertex3f(+1.5,+2,+0.5);
   glTexCoord2f(0,1); glVertex3f(+1.5,+2,-0.5);
   glEnd();
   //Left
   glBindTexture(GL_TEXTURE_2D,texture[7]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3f(+1,-2.5,-0.5);
   glTexCoord2f(1,0); glVertex3f(+1,-2.5,+0.5);
   glTexCoord2f(1,1); glVertex3f(+1,+2,+0.5);
   glTexCoord2f(0,1); glVertex3f(+1,+2,-0.5);
   glEnd();
   //Top
   glBegin(GL_QUADS);
   glNormal3f(0,+1,0);
   glTexCoord2f(0,0); glVertex3f(+1.5,+2,+0.5);
   glTexCoord2f(1,0); glVertex3f(+1,+2,+0.5);
   glTexCoord2f(1,1); glVertex3f(+1,+2,-0.5);
   glTexCoord2f(0,1); glVertex3f(+1.5,+2,-0.5);
   glEnd();
   //Bottom
   glBegin(GL_QUADS);
   glNormal3f(0,-1,0);
   glTexCoord2f(0,0); glVertex3f(+1.5,-2.5,+0.5);
   glTexCoord2f(1,0); glVertex3f(+1,-2.5,+0.5);
   glTexCoord2f(1,1); glVertex3f(+1,-2.5,-0.5);
   glTexCoord2f(0,1); glVertex3f(+1.5,-2.5,-0.5);   
   glEnd();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}
static void Wheels(){
   glPushMatrix();
   glColor3f(0,0,0);
   glRotated(90,0,1,0);
   glRotated(TireAngle,0,0,1);
   GLUquadricObj *quadObj = gluNewQuadric();
   glEnable(GL_TEXTURE_2D);
   gluCylinder(quadObj, 1.0, 1.0, 0.5, 16, 16);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   gluQuadricNormals(quadObj, GLU_SMOOTH);
   gluQuadricTexture(quadObj, true);
   glBindTexture(GL_TEXTURE_2D,texture[17]);
   glColor3f(1,1,1);
   GLUquadricObj *quadObj2 = gluNewQuadric();
   gluQuadricOrientation(quadObj2, GLU_INSIDE);
   gluQuadricNormals(quadObj2, GLU_SMOOTH);
   gluQuadricTexture(quadObj2, true);
   gluDisk(quadObj2, 0, 1.0, 16, 16);
   glPushMatrix();
   glTranslated(0,0,0.5);
   gluDisk(quadObj, 0, 1.0, 16, 16);
   glPopMatrix();
   glPopMatrix();
  // glDisable(GL_TEXTURE_2D);
}

static void LeftLeg(double x, double y, double z, double dx, double dy, double dz, double th){
   glPushMatrix();
   glTranslated(x,y-2,z);
   glRotated(th,0,1,0);
   glRotated(LegAngles[0], 1, 0, 0);
   glRotated(th,0,-1,0);
   glTranslated(-x,-y+2,-z);
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glRotated(TransformAngle,1,0,0);
   glScaled(dx,dy,dz);
   glColor3f(1,1,1);
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   //LEFT LEG
   //Front
   glBindTexture(GL_TEXTURE_2D,texture[8]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,+1);
   glTexCoord2f(0,0); glVertex3f(-1 - ExtraWidth,-5.5 - ExtraLength,+0.5);
   glTexCoord2f(1,0); glVertex3f(0,-5.5 - ExtraLength,+0.5);
   glTexCoord2f(1,1); glVertex3f(0,-2,+0.5);
   glTexCoord2f(0,1); glVertex3f(-1,-2,+0.5);
   glEnd();
   //Back
   glBindTexture(GL_TEXTURE_2D,texture[9]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3f(-1 - ExtraWidth,-5.5 - ExtraLength,-0.5);
   glTexCoord2f(1,0); glVertex3f(0,-5.5 - ExtraLength,-0.5);
   glTexCoord2f(1,1); glVertex3f(0,-2,-0.5);
   glTexCoord2f(0,1); glVertex3f(-1 - ExtraWidth,-2,-0.5);
   glEnd();
   //Left
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3f(-1 - ExtraWidth,-5.5-ExtraLength,-0.5);
   glTexCoord2f(1,0); glVertex3f(-1 - ExtraWidth,-5.5-ExtraLength,+0.5);
   glTexCoord2f(1,1); glVertex3f(-1 - ExtraWidth,-2,+0.5);
   glTexCoord2f(0,1); glVertex3f(-1 - ExtraWidth,-2,-0.5);
   glEnd();
   //Right
   glBegin(GL_QUADS);
   glNormal3f(+1,0,0);
   glTexCoord2f(0,0); glVertex3f(0,-5.5-ExtraLength,-0.5);
   glTexCoord2f(1,0); glVertex3f(0,-5.5-ExtraLength,+0.5);
   glTexCoord2f(1,1); glVertex3f(0,-2,+0.5);
   glTexCoord2f(0,1); glVertex3f(0,-2,-0.5);
   glEnd();
   //Top
   glBindTexture(GL_TEXTURE_2D,texture[10]);
   glBegin(GL_QUADS);
   glNormal3f(0,+1,0);
   glTexCoord2f(0,0); glVertex3f(-1 - ExtraWidth,-2,+0.5);
   glTexCoord2f(1,0); glVertex3f(0,-2,+0.5);
   glTexCoord2f(1,1); glVertex3f(0,-2,-0.5);
   glTexCoord2f(0,1); glVertex3f(-1 - ExtraWidth,-2,-0.5);
   glEnd();
   //Bottom
   glBegin(GL_QUADS);
   glNormal3f(0,-1,0);
   glTexCoord2f(0,0); glVertex3f(-1 - ExtraWidth,-5.5-ExtraLength,+0.5);
   glTexCoord2f(1,0); glVertex3f(0,-5.5-ExtraLength,+0.5);
   glTexCoord2f(1,1); glVertex3f(0,-5.5-ExtraLength,-0.5);
   glTexCoord2f(0,1); glVertex3f(-1 - ExtraWidth,-5.5-ExtraLength,-0.5);
   glEnd();
   glPushMatrix();
   glTranslated(-1.5-ExtraWidth,-3,0);
   Wheels();
   glPopMatrix();
   glPushMatrix();
   glTranslated(-1.5-ExtraWidth,-5 - ExtraLength,0);
   Wheels();
   glPopMatrix();;
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}   

static void RightLeg(double x, double y, double z, double dx, double dy, double dz, double th){
   glPushMatrix();
   glTranslated(x,y-2,z);
   glRotated(th,0,1,0);
   glRotated(LegAngles[1], 1, 0, 0);
   glRotated(th,0,-1,0);
   glTranslated(-x,-y+2,-z);
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glRotated(TransformAngle,1,0,0);
   glScaled(dx,dy,dz);
   glColor3f(1,1,1);
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   //RIGHT LEG
   //Front
   glBindTexture(GL_TEXTURE_2D,texture[8]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,+1);
   glTexCoord2f(0,0); glVertex3f(0,-5.5-ExtraLength,+0.5);
   glTexCoord2f(1,0); glVertex3f(+1 + ExtraWidth,-5.5-ExtraLength,+0.5);
   glTexCoord2f(1,1); glVertex3f(+1 + ExtraWidth,-2,+0.5);
   glTexCoord2f(0,1);glVertex3f(0,-2,+0.5);
   glEnd();
   //Back
   glBindTexture(GL_TEXTURE_2D,texture[9]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3f(0,-5.5-ExtraLength,-0.5);
   glTexCoord2f(1,0); glVertex3f(+1 + ExtraWidth,-5.5-ExtraLength,-0.5);
   glTexCoord2f(1,1); glVertex3f(+1 + ExtraWidth,-2,-0.5);
   glTexCoord2f(0,1); glVertex3f(0,-2,-0.5);
   glEnd();
   //Left
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3f(0,-5.5-ExtraLength,+0.5);
   glTexCoord2f(1,0); glVertex3f(0,-5.5-ExtraLength,-0.5);
   glTexCoord2f(1,1); glVertex3f(0,-2,-0.5);
   glTexCoord2f(0,1); glVertex3f(0,-2,+0.5);
   glEnd();
   //Right
   glBegin(GL_QUADS);
   glNormal3f(+1,0,0);
   glTexCoord2f(0,0); glVertex3f(+1 + ExtraWidth,-5.5-ExtraLength,+0.5);
   glTexCoord2f(1,0); glVertex3f(+1 + ExtraWidth,-5.5-ExtraLength,-0.5);
   glTexCoord2f(1,1); glVertex3f(+1 + ExtraWidth,-2,-0.5);
   glTexCoord2f(0,1); glVertex3f(+1 + ExtraWidth,-2,+0.5);
   glEnd();
   //Top
   glBindTexture(GL_TEXTURE_2D,texture[10]);
   glBegin(GL_QUADS);
   glNormal3f(0,+1,0);
   glTexCoord2f(0,0); glVertex3f(0,-2,+0.5);
   glTexCoord2f(1,0); glVertex3f(+1 + ExtraWidth,-2,+0.5);
   glTexCoord2f(1,1); glVertex3f(+1 + ExtraWidth,-2,-0.5);
   glTexCoord2f(0,1); glVertex3f(0,-2,-0.5);
   glEnd();
   //Bottom
   glBegin(GL_QUADS);
   glNormal3f(0,-1,0);
   glTexCoord2f(0,0); glVertex3f(0,-5.5-ExtraLength,+0.5);
   glTexCoord2f(1,0); glVertex3f(+1 + ExtraWidth,-5.5-ExtraLength,+0.5);
   glTexCoord2f(1,1); glVertex3f(+1+ ExtraWidth,-5.5-ExtraLength,-0.5);
   glTexCoord2f(0,1); glVertex3f(0,-5.5-ExtraLength,-0.5);
   glEnd();
   glPushMatrix();
   glTranslated(+1+ExtraWidth,-3,0);
   Wheels();
   glPopMatrix();
   glPushMatrix();
   glTranslated(+1+ExtraWidth,-5 - ExtraLength,0);
   Wheels();
   glPopMatrix();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void OptimusPrime(double x, double y, double z, double dx, double dy, double dz, double th){
   //Beginning code taken from
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
   Head(x,y,z,dx,dy,dz,th);
   Torso(x,y,z,dx,dy,dz,th);
   LeftArm(x,y,z,dx,dy,dz,th);
   RightArm(x,y,z,dx,dy,dz,th);
   RightLeg(x,y,z,dx,dy,dz,th);
   LeftLeg(x,y,z,dx,dy,dz,th);   
   //  Enable textures
   //glEnable(GL_TEXTURE_2D);
   //glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   //glColor3f(1,0,0);
   //glBindTexture(GL_TEXTURE_2D,texture[0]);
   //glPopMatrix();
}
/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius r
 */
static void ball(double x,double y,double z,double r)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glutSolidSphere(1.0,16,16);
   //  Undo transofrmations
   glPopMatrix();
}

static void Sky(double D)
{
   glColor3f(1,1,1);
   glEnable(GL_TEXTURE_2D);

   //  Sides
   //Back
   glBindTexture(GL_TEXTURE_2D,texture[11]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,1);
   glTexCoord2f(0,0); glVertex3f(-D,-60,-D);
   glTexCoord2f(1,0); glVertex3f(+D,-60,-D);
   glTexCoord2f(1,1); glVertex3f(+D,+D,-D);
   glTexCoord2f(0,1); glVertex3f(-D,+D,-D);
   glEnd();
   //Right
   glBindTexture(GL_TEXTURE_2D,texture[15]);
   glBegin(GL_QUADS);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,0); glVertex3f(+D,-60,-D);
   glTexCoord2f(1,0); glVertex3f(+D,-60,+D);
   glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
   glTexCoord2f(0,1); glVertex3f(+D,+D,-D);
   glEnd();
   //Front
   glBindTexture(GL_TEXTURE_2D,texture[12]);
   glBegin(GL_QUADS);
   glNormal3f(0,0,-1);
   glTexCoord2f(0,0); glVertex3f(+D,-60,+D);
   glTexCoord2f(1,0); glVertex3f(-D,-60,+D);
   glTexCoord2f(1,1); glVertex3f(-D,+D,+D);
   glTexCoord2f(0,1); glVertex3f(+D,+D,+D);
   glEnd();
   //Left
   glBindTexture(GL_TEXTURE_2D,texture[14]);
   glBegin(GL_QUADS);
   glNormal3f(1,0,0);
   glTexCoord2f(0,0); glVertex3f(-D,-60,+D);
   glTexCoord2f(1,0); glVertex3f(-D,-60,-D);
   glTexCoord2f(1,1); glVertex3f(-D,+D,-D);
   glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
   glEnd();

   //  Top and bottom
   glBindTexture(GL_TEXTURE_2D,texture[13]);
   glBegin(GL_QUADS);
   //Top
   glNormal3f(0,-1,0);
   glTexCoord2f(0,0); glVertex3f(+D,+D,-D);
   glTexCoord2f(1,0); glVertex3f(+D,+D,+D);
   glTexCoord2f(1,1); glVertex3f(-D,+D,+D);
   glTexCoord2f(0,1); glVertex3f(-D,+D,-D);
   glEnd();
   //Bottom
   glBindTexture(GL_TEXTURE_2D,texture[16]);
   glBegin(GL_QUADS);
   glNormal3f(0,1,0);
   glTexCoord2f(0,0); glVertex3f(-D,-5.5,+D);
   glTexCoord2f(1,0); glVertex3f(+D,-5.5,+D);
   glTexCoord2f(1,1); glVertex3f(+D,-5.5,-D);
   glTexCoord2f(0,1); glVertex3f(-D,-5.5,-D);
   glEnd();

   glDisable(GL_TEXTURE_2D);
}
/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Length of axes
   const double len=2.0;
   //  Eye position
   double Ex = -2*dim*Sin(th)*Cos(ph);
   double Ey = +2*dim        *Sin(ph);
   double Ez = +2*dim*Cos(th)*Cos(ph);
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Set perspective
   glLoadIdentity();
   if(perspective == 0){
      gluLookAt(OptimusX+ -2*10*Sin(CameraAngle)*Cos(ph),Ey + OptimusY,2*10*Cos(CameraAngle)*Cos(ph) + OptimusZ, OptimusX,OptimusY,OptimusZ , 0,Cos(ph),0);
   }
   else if(perspective == 1){
	   gluLookAt(OptimusX + -Sin(CameraAngle)*Cos(ph) + 5 * sin(fmodf(OptimusAngle,360.0) * M_PI/180),OptimusY,Cos(CameraAngle)*Cos(ph) + OptimusZ + 5 * cos(fmodf(OptimusAngle,360.0) * M_PI/180), 
	   OptimusX + 10 * sin(fmodf(OptimusAngle,360.0) * M_PI/180),OptimusY,OptimusZ + 10 * cos(fmodf(OptimusAngle,360.0) * M_PI/180) ,
	   0,1,0);
   }
   else if(perspective == 2){
	  gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //OptimusX += 0.1 * sin(fmodf(OptimusAngle,360.0) * M_PI/180);
   //OptimusZ += 0.1 * cos(fmodf(OptimusAngle,360.0) * M_PI/180); 
	   
  
	   
   //  Light switch
   if (light)
   {
      //  Translate intensity to color vectors
      float Ambient[]   = {0.01*ambient/dusk,0.01*ambient/dusk,0.01*ambient/dusk ,1.0};
      float Diffuse[]   = {0.01*diffuse/dusk ,0.01*diffuse/dusk ,0.01*diffuse/dusk ,1.0};
      float Specular[]  = {0.01*specular/dusk,0.01*specular/dusk,0.01*specular/dusk,1.0};
      
      float AmbientNight[]   = {0.01*ambientnight ,0.01*ambientnight ,0.01*ambientnight ,1.0};
      float DiffuseNight[]   = {0.01*diffusenight,0.01*diffusenight,0.01*diffusenight ,1.0};
      float SpecularNight[]  = {0.01*specularnight,0.01*specularnight,0.01*specularnight,1.0};
		  
      //  Light direction
      float Position[]  = {110*Cos(zh),100*Sin(zh),0,1};
      float NightPosition[] = {-110*Cos(zh), -100*Sin(zh), 0,1};
      //  Draw light position as ball (still no lighting here)
      glColor3f(1,1,1);
      ball(Position[0],Position[1],Position[2] , 5);
      ball(NightPosition[0],NightPosition[1],NightPosition[2], 5);
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      //  Set ambient, diffuse, specular components and position of light 0
      if(day){
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);
      }
      else{
	  glLightfv(GL_LIGHT0,GL_AMBIENT ,AmbientNight);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,DiffuseNight);
      glLightfv(GL_LIGHT0,GL_SPECULAR,SpecularNight);
      glLightfv(GL_LIGHT0,GL_POSITION,NightPosition);
	  }
  }
   else
      glDisable(GL_LIGHTING);
   //  Draw scene
   OptimusPrime(OptimusX,OptimusY,OptimusZ , 1,1,1 , OptimusAngle);
   Sky(2*50);
   //  Draw axes - no lighting from here on
   glDisable(GL_LIGHTING);
   glColor3f(1,1,1);
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/100000.0;
   zh = fmod(45*t,360.0);
	   if(zh >= 0 && zh <= 180 ){
		   day = true;
	   }
       else if(zh >= 180 && zh <= 360)
       {
		   day = false;
	   }
	   if(zh <= 30){
		   dusk = 2;
	   }
	   else if(zh >= 31){
		   dusk = 1;
	   }
	   if(zh >= 150 && zh <= 180){
		   dusk = 2;
	   }
	   else if(zh >= 181){
		   dusk = 1;
	   } 
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 1;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(45,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == 'p'){
	   perspective = (perspective+1)%3;
   }
   else if (ch == 'h'){
	  if(midtransformbit == false && cartransformbit == false){
	  OptimusAngle += 5;
	  CameraAngle -= 5;
      if(leftarm){
	      ArmAngles[0] += 2;
      }
      else{
	      ArmAngles[0] -= 2;
      }
      if(ArmAngles[0] >= 30.0){
	      leftarm = false;
      }
      if(ArmAngles[0] <= -30.0){
	      leftarm = true;
      }
      //RIGHT ARM
      if(rightarm){
	      ArmAngles[1] += 2;
      }
      else{
	      ArmAngles[1] -= 2;
      }
      if(ArmAngles[1] >= 30.0){
	      rightarm = false;
      }
      if(ArmAngles[1] <= -30.0){
	      rightarm = true;
      }
      //LEFT LEG
      if(leftleg){
	      LegAngles[0] += 2;
      }
      else{
	      LegAngles[0] -= 2;
      }
      if(LegAngles[0] >= 30.0){
	      leftleg = false;
      }
      if(LegAngles[0] <= -30.0){
	      leftleg = true;
      }
      //RIGHT LEG
      if(rightleg){
	      LegAngles[1] += 2;
      }
      else{
	      LegAngles[1] -= 2;
      }
      if(LegAngles[1] >= 30.0){
	      rightleg = false;
      }
      if(LegAngles[1] <= -30.0){
	      rightleg = true;
      }
    }
    if(cartransformbit){
	  OptimusAngle += 5;
	  CameraAngle -= 5;
	  OptimusX += 1 * sin(fmodf(OptimusAngle,360.0) * M_PI/180);
	  OptimusZ += 1 * cos(fmodf(OptimusAngle,360.0) * M_PI/180);
	  TireAngle += 20;
   }
}
   else if (ch == 'u'){
	  if(midtransformbit == false && cartransformbit == false){
	  CameraX += 0.1 * sin(fmodf(OptimusAngle,360.0) * M_PI/180); 
	  CameraZ += 0.1 * cos(fmodf(OptimusAngle,360.0) * M_PI/180);
      OptimusX += 0.1 * sin(fmodf(OptimusAngle,360.0) * M_PI/180);
      OptimusZ += 0.1 * cos(fmodf(OptimusAngle,360.0) * M_PI/180); 
      //ANIMATION
      //LEFT ARM
      if(leftarm){
	      ArmAngles[0] += 2;
      }
      else{
	      ArmAngles[0] -= 2;
      }
      if(ArmAngles[0] >= 30.0){
	      leftarm = false;
      }
      if(ArmAngles[0] <= -30.0){
	      leftarm = true;
      }
      //RIGHT ARM
      if(rightarm){
	      ArmAngles[1] += 2;
      }
      else{
	      ArmAngles[1] -= 2;
      }
      if(ArmAngles[1] >= 30.0){
	      rightarm = false;
      }
      if(ArmAngles[1] <= -30.0){
	      rightarm = true;
      }
      //LEFT LEG
      if(leftleg){
	      LegAngles[0] += 2;
      }
      else{
	      LegAngles[0] -= 2;
      }
      if(LegAngles[0] >= 30.0){
	      leftleg = false;
      }
      if(LegAngles[0] <= -30.0){
	      leftleg = true;
      }
      //RIGHT LEG
      if(rightleg){
	      LegAngles[1] += 2;
      }
      else{
	      LegAngles[1] -= 2;
      }
      if(LegAngles[1] >= 30.0){
	      rightleg = false;
      }
      if(LegAngles[1] <= -30.0){
	      rightleg = true;
      }
   }
      if(cartransformbit){
		 OptimusX += 1 * sin(fmodf(OptimusAngle,360.0) * M_PI/180);
	     OptimusZ += 1 * cos(fmodf(OptimusAngle,360.0) * M_PI/180); 
	     CameraX += 1 * sin(fmodf(OptimusAngle,360.0) * M_PI/180); 
	     CameraZ += 1 * cos(fmodf(OptimusAngle,360.0) * M_PI/180);
	     TireAngle += 20;
	 }
   }
   else if (ch == 'j'){
	  if(midtransformbit == false && cartransformbit == false){
	  CameraX += 0.1 * sin(fmodf(OptimusAngle,360.0) * M_PI/180); 
	  CameraZ += 0.1 * cos(fmodf(OptimusAngle,360.0) * M_PI/180);
      OptimusX -= 0.1 * sin(fmodf(OptimusAngle,360.0) * M_PI/180);
      OptimusZ -= 0.1 * cos(fmodf(OptimusAngle,360.0) * M_PI/180);
      if(leftarm){
	      ArmAngles[0] += 2;
      }
      else{
	      ArmAngles[0] -= 2;
      }
      if(ArmAngles[0] >= 30.0){
	      leftarm = false;
      }
      if(ArmAngles[0] <= -30.0){
	      leftarm = true;
      }
      //RIGHT ARM
      if(rightarm){
	      ArmAngles[1] += 2;
      }
      else{
	      ArmAngles[1] -= 2;
      }
      if(ArmAngles[1] >= 30.0){
	      rightarm = false;
      }
      if(ArmAngles[1] <= -30.0){
	      rightarm = true;
      }
      //LEFT LEG
      if(leftleg){
	      LegAngles[0] += 2;
      }
      else{
	      LegAngles[0] -= 2;
      }
      if(LegAngles[0] >= 30.0){
	      leftleg = false;
      }
      if(LegAngles[0] <= -30.0){
	      leftleg = true;
      }
      //RIGHT LEG
      if(rightleg){
	      LegAngles[1] += 2;
      }
      else{
	      LegAngles[1] -= 2;
      }
      if(LegAngles[1] >= 30.0){
	      rightleg = false;
      }
      if(LegAngles[1] <= -30.0){
	      rightleg = true;
      }
   }
      if(cartransformbit){
		 OptimusX -= 0.5 * sin(fmodf(OptimusAngle,360.0) * M_PI/180);
	     OptimusZ -= 0.5 * cos(fmodf(OptimusAngle,360.0) * M_PI/180);
	     CameraX -= 0.5 * sin(fmodf(OptimusAngle,360.0) * M_PI/180); 
	     CameraZ -= 0.5 * cos(fmodf(OptimusAngle,360.0) * M_PI/180);
	     TireAngle += 20;
	 }
   }
   else if (ch == 'k'){
	  if(midtransformbit == false && cartransformbit == false){
	  OptimusAngle -= 5;
	  CameraAngle += 5;
      if(leftarm){
	      ArmAngles[0] += 2;
      }
      else{
	      ArmAngles[0] -= 2;
      }
      if(ArmAngles[0] >= 30.0){
	      leftarm = false;
      }
      if(ArmAngles[0] <= -30.0){
	      leftarm = true;
      }
      //RIGHT ARM
      if(rightarm){
	      ArmAngles[1] += 2;
      }
      else{
	      ArmAngles[1] -= 2;
      }
      if(ArmAngles[1] >= 30.0){
	      rightarm = false;
      }
      if(ArmAngles[1] <= -30.0){
	      rightarm = true;
      }
      //LEFT LEG
      if(leftleg){
	      LegAngles[0] += 2;
      }
      else{
	      LegAngles[0] -= 2;
      }
      if(LegAngles[0] >= 30.0){
	      leftleg = false;
      }
      if(LegAngles[0] <= -30.0){
	      leftleg = true;
      }
      //RIGHT LEG
      if(rightleg){
	      LegAngles[1] += 2;
      }
      else{
	      LegAngles[1] -= 2;
      }
      if(LegAngles[1] >= 30.0){
	      rightleg = false;
      }
      if(LegAngles[1] <= -30.0){
	      rightleg = true;
      }
    }
      if(cartransformbit){
	     OptimusAngle -= 5;
	     CameraAngle += 5;
	     OptimusX += 1 * sin(fmodf(OptimusAngle,360.0) * M_PI/180);
	     OptimusZ += 1 * cos(fmodf(OptimusAngle,360.0) * M_PI/180);
	     TireAngle += 20;
	 }
   }
   //TRANSFOOOOOORRMMMM
   else if(ch == 32){
		     if(cartransformbit == true){
				 midtransformbit = true;
				 if(perspective == 1){
				    perspective = 0;
				    firstperson = true;
			     }
	         //Left Arm
	         if(ArmAngles[0] >= 1){
		         ArmAngles[0] -= 2;
	         }
	         else if(ArmAngles[0] <= -1){
		         ArmAngles[0] += 2;
	         }
	         //Right Arm
	         if(ArmAngles[1] >= 1){
		         ArmAngles[1] -= 2;
	         }
	         else if(ArmAngles[1] <= -1){
		         ArmAngles[1] += 2;
	         }
	         //Left Leg
	         if(LegAngles[0] >= 1){
		         LegAngles[0] -= 2;
	         }
	         else if(LegAngles[0] <= -1){
		         LegAngles[0] += 2;
	         }
             //Right Leg
	         if(LegAngles[1] >= 1){
		         LegAngles[1] -= 2;
	         }
	         else if(LegAngles[1] <= -1){
		         LegAngles[1] += 2;
	         }
	         if(OptimusY < 10.1){
			     OptimusY += 0.5;
		     }
		     if(OptimusY >= 10){
				 transformpeak = true;
			 }
			 if(transformpeak && OptimusY > 0){
				 OptimusY -= 0.8;
			 }
			 if(transformpeak && OptimusY <= 0){
				 transformcomplete = true;
			 }
			 if(TransformAngle < 360){
				 TransformAngle += 8;
			 }
			 if(HeadTransformAngle > 0){
				 HeadTransformAngle -= 7;
			 }
			 ExtraLength -= 0.05;
			 ExtraWidth -= 0.01;
			  
		     if(ArmAngles[0] >= -1 && ArmAngles[0] <= 1 && ArmAngles[1] >= -1 && ArmAngles[1] <= 1 && LegAngles[0] >= -1 && LegAngles[0] <= 1 && LegAngles[1] >= -1 && LegAngles[1] <= 1
		        && transformcomplete == true){
		        midtransformbit = false;
		        cartransformbit = false;
		        transformpeak = false;
		        transformcomplete = false;
		        humantransformbit = true;
		        TransformAngle = 0;
		        if(firstperson){
					perspective = 1;
				}
	     }
	 }
  }
	  else if (ch == 'b'){
		     if(humantransformbit){
			 midtransformbit = true;
			 if(perspective == 1){
				    perspective = 0;
				    firstperson = true;
			     }
	         //Left Arm
	         if(ArmAngles[0] >= 1){
		         ArmAngles[0] -= 2;
	         }
	         else if(ArmAngles[0] <= -1){
		         ArmAngles[0] += 2;
	         }
	         //Right Arm
	         if(ArmAngles[1] >= 1){
		         ArmAngles[1] -= 2;
	         }
	         else if(ArmAngles[1] <= -1){
		         ArmAngles[1] += 2;
	         }
	         //Left Leg
	         if(LegAngles[0] <= 89){
		         LegAngles[0] += 2;
	         }
             //Right Leg
	         if(LegAngles[1] <= 89){
		         LegAngles[1] += 2;
	         }
	         //>-2.5 at 0.06 rate is final
	         if(OptimusY < 10.1){
			     OptimusY += 0.5;
		     }
		     if(OptimusY >= 10){
				 transformpeak = true;
			 }
			 if(transformpeak && OptimusY > -2.5){
				 OptimusY -= 0.8;
			 }
			 if(transformpeak && OptimusY <= -2.5){
				 transformcomplete = true;
			 }
			 if(TransformAngle < 360){
				 TransformAngle += 8;
			 }
			 if(HeadTransformAngle < 180){
				 HeadTransformAngle += 7;
			 }
			 
			 ExtraLength += 0.05;
			 ExtraWidth  += 0.01;
			 if(ArmAngles[0] >= -1 && ArmAngles[0] <= 1 && ArmAngles[1] >= -1 && ArmAngles[1] <= 1 && LegAngles[0] >= 89 && LegAngles[1] >= 89 && transformcomplete == true){
		        midtransformbit = false;
		        cartransformbit = true;
		        transformcomplete = false;
		        transformpeak = false;
		        humantransformbit = false;
		        TransformAngle = 0;
		        if(firstperson){
					perspective = 1;
				}
			}
	     }
      }
   //  Translate shininess power to value (-1 => 0)
   shinyvec[0] = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project(45,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project(45,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(600,600);
   glutCreateWindow("Final Project: Brady Auen");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //  Load textures
   texture[0] = LoadTexBMP("Optimus.bmp");
   texture[1] = LoadTexBMP("FaceSide.bmp");
   texture[2] = LoadTexBMP("TorsoFront.bmp");
   texture[3] = LoadTexBMP("ArmFront.bmp");
   texture[4] = LoadTexBMP("TorsoBack.bmp");
   texture[5] = LoadTexBMP("ArmFront.bmp");
   texture[6] = LoadTexBMP("ArmOutside.bmp");
   texture[7] = LoadTexBMP("ArmBackandSide.bmp");
   texture[8] = LoadTexBMP("LegsFront.bmp");
   texture[9] = LoadTexBMP("LegsOther.bmp");
   texture[10] = LoadTexBMP("FaceTop.bmp");
   texture[11] = LoadTexBMP("skyback.bmp");
   texture[12] = LoadTexBMP("skyfront.bmp");
   texture[13] = LoadTexBMP("skysky.bmp");
   texture[14] = LoadTexBMP("skyleft.bmp");
   texture[15] = LoadTexBMP("skyright.bmp");
   texture[16] = LoadTexBMP("skyfloor.bmp");
   texture[17] = LoadTexBMP("tire.bmp");
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
