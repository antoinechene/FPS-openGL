// Rendu d'une th�i�re
// et d'un plan qui est un miroir
// et qui porte l'ombre de la th�i�re
//
//(c) Eric BITTAR - 14 Avril 2004
// http://www.univ-reims.fr/leri/membre/bittar
//
// Version avec plan de clipping pour le calcul de l'�quation du plan
//
// la souris permet de faire tourner toute la sc�ne
//           ou uniquement le miroir (touche 'w')
// les fl�ches permettent le d�placement de la th�i�re
//           ou de la lumi�re (avec SHIFT)
// Barre d'espace pour changer le type de la lumi�re (directionnelle|positionnelle)
// Echap pour quitter l'application
// Bonus : PAGE_UP|PAGE_DOWN pour la rotation de la th�i�re

#include <stdlib.h>
#include <GL/glut.h>


GLfloat spin = 0.0, spin_x=-45.0, spin_y=0.0;//Rotation du miroir
GLfloat spinG_x=0.0, spinG_y=0.0; //Rotation globale de la sc�ne
GLint G_rot = 1; // 1=>On effectue la rotation sur toute la sc�ne, 0=>seulement sur le plan

int mouse_x, mouse_y, incr=0;
double tX = 0.6, tY=0, tZ=0;
GLfloat lum[4]; //Les coordonn�es de la lumi�re
int list=0;

//Pour l'�clairage
GLfloat white[] = { 1.0, 1.0, 1.0, 0.0 };

void init_lights(void) 
{
  //Initialisation de la lumi�re
  lum[0]=3; lum[1]=0; lum[2]=0; lum[3]=0;
  
  glLightfv(GL_LIGHT0, GL_AMBIENT, white);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0); 
  
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}


//Affiche la sc�ne pour elle-m�me, ou pour son ombre...
void scene(int ombre)
{ 
  //Affiche la lampe
  if (!ombre){ //On n'affiche PAS l'ombre de la lampe !
    glPushMatrix();
    {
      glLightfv(GL_LIGHT0, GL_POSITION, lum);
      glDisable(GL_LIGHTING);
      glColor4f(0.9, 0.2, 0.2, 1.0);
      glTranslatef(lum[0], lum[1], lum[2]);
      glutSolidSphere(.1, 10, 10);
      glEnable(GL_LIGHTING);
    }
    glPopMatrix();
  }
  //Affiche les objets de la sc�ne (ici la th�i�re)
  glPushMatrix();
  {
    glTranslatef(tX,tY,tZ);   
    glRotatef(spin, 0, 1, 0);
    
    if (ombre){
      glDisable(GL_DEPTH_TEST);
      glColor4f(0, 0, 0, 0.85);
      glutSolidTeapot(1.0);
      glEnable(GL_DEPTH_TEST);
    }
    else {
      glColor3f(0.2, 0.8, 0.2);
      glutSolidTeapot(1.0);
    }
  }
  glPopMatrix();
} //scene()


void ombre(GLfloat t){
  //Ombre sur le miroir (plan 1.x + 0.y + 1.z + 0 = 0)
  GLdouble eq[4]={1, 0, 0, 0};
  
  glEnable(GL_CLIP_PLANE1);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  {
    glLoadIdentity();
    //On applique la transformation Mmiroir :
    // Ici deux rotations et une translation
    //On contr�le � la souris la rotation du miroir
    glRotatef(spin_y, 1, 0, 0); 
    glRotatef(spin_x, 0, 1, 0); 
    glTranslatef(-t, 0, 0);  //Centr� en -t, 0, 0
    
    glClipPlane(GL_CLIP_PLANE1, eq); //On place le plan de clipping
    glGetClipPlane(GL_CLIP_PLANE1, eq); //Et on r�cup�re son �quation transform�e !!
  }
  glPopMatrix();
  glDisable(GL_CLIP_PLANE1);
 
  GLfloat ps = 0;
  for (int i=0 ; i<4 ; i++)
    ps += lum[i]*eq[i];
  GLfloat projMat[16];
    
  //Colonne 1
  projMat[0]  = - lum[0] * eq[0] + ps;
  projMat[4]  = - lum[0] * eq[1];
  projMat[8]  = - lum[0] * eq[2];
  projMat[12] = - lum[0] * eq[3];

  //Colonne 2
  projMat[1]  = - lum[1] * eq[0];
  projMat[5]  = - lum[1] * eq[1] + ps;
  projMat[9]  = - lum[1] * eq[2];
  projMat[13] = - lum[1] * eq[3];

  //Colonne 3
  projMat[2]  = - lum[2] * eq[0];
  projMat[6]  = - lum[2] * eq[1];
  projMat[10] = - lum[2] * eq[2] + ps;
  projMat[14] = - lum[2] * eq[3];

  //Colonne 4
  projMat[3]  = - lum[3] * eq[0];
  projMat[7]  = - lum[3] * eq[1];
  projMat[11] = - lum[3] * eq[2];
  projMat[15] = - lum[3] * eq[3] + ps;

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  {
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    
    //Projection � l'aide de la matrice d'ombre
    glMultMatrixf(projMat);

    scene(true);
  }
  glPopMatrix();
}

//Dessine la face du miroir
void une_face (GLfloat t, GLenum mode){
  GLfloat u=2*t;
  glPolygonMode(GL_FRONT, mode);
  glBegin(GL_QUADS);		// C'est un carr� d'ar�te 2u
  glVertex3f( 0,  u,  u);
  glVertex3f( 0, -u,  u);
  glVertex3f( 0, -u, -u);
  glVertex3f( 0,  u, -u);
  glEnd();
  glPolygonMode(GL_FRONT, GL_FILL);
}

//Dessine le miroir avec ses d�corations
// la face est bleut�e
// l'encadrement est rouge
// et l'arri�re est jaune.
void miroir (GLfloat t, int back)
{
  glPushMatrix();
  {
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    
    glColor4f(0.2, 0.2, 0.8, 0.6); //Le miroir est bleut�
    
    //On applique la transformation Mmiroir :
    // Ici deux rotations et une translation
    //On contr�le � la souris la rotation du miroir
    glRotatef(spin_y, 1, 0, 0); 
    glRotatef(spin_x, 0, 1, 0); 
    glTranslatef(-t, 0, 0);  //Centr� en -t, 0, 0
    
    une_face(t, GL_FILL);
    
    if (back) { //On dessine l'arri�re du miroir
      glPushMatrix();
      {
	glRotatef(180.0, 0, 1, 0); //On fait un demi-tour pour dessiner l'envers... � l'endroit
	glColor3f(1, 0, 0);
	une_face(t, GL_LINE);		// On dessine les ar�tes en rouge
	
	glColor4f(1.0, 1.0, 0.0, 1.0);
	une_face(t, GL_FILL);		// On dessine l'arri�re en jaune
      }
      glPopMatrix();
    }
    glDisable(GL_CULL_FACE);
  }
  glPopMatrix();
}//miroir()


//Pour redimensionner la fen�tre
void myReshapeFunc(int w,int h)
{
  glViewport(0,0,(GLint) w,(GLint) h);
  
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho(-7,5,-7,7,-20,20);
  
  glMatrixMode( GL_MODELVIEW );
  
}//myReshapeFunc()
 

//Fonction d'affichage
void myDisplayFunc()
{
  GLfloat t = 1.5; //Taille et d�calage du miroir

  glPushMatrix();
  {
    //On contr�le � la souris la rotation globale de la sc�ne
    glRotatef(spinG_y, 1, 0, 0);
    glRotatef(spinG_x, 0, 1, 0);

    // Nettoyage du "Stencil Buffer" et du "Z buffer" 
    glClear (GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //============== On remplit le stencil buffer ==============
    
    //On active le test du stencil
    glEnable(GL_STENCIL_TEST) ;
    
    //Le test est param�tr� par deux fonctions :

    //   void glStencilFunc(GLenum func, GLint ref, GLuint mask)
    //     qui sert � indiquer le test � effectuer pour accepter le fragment. Les param�tres sont :
    //     "func" : GL_NEVER, GL_LESS, GL_LEQUAL, GL_GREATER, GL_GEQUAL, GL_EQUAL, GL_NOTEQUAL, ou GL_ALWAYS
    //     "ref"  : valeur de r�f�rence du test
    //     "mask" : masque binaire � appliquer � la valeur du stencil et � ref pour le test
    //    GL_NEVER	    Always fails.
    //    GL_LESS	    Passes if ( ref & mask ) < ( stencil & mask ).
    //    GL_LEQUAL	    Passes if ( ref & mask ) <= ( stencil & mask ).
    //    GL_GREATER	Passes if ( ref & mask ) > ( stencil & mask ).
    //    GL_GEQUAL	    Passes if ( ref & mask ) >= ( stencil & mask ).
    //    GL_EQUAL	    Passes if ( ref & mask ) = ( stencil & mask ).
    //    GL_NOTEQUAL	Passes if ( ref & mask ) != ( stencil & mask ).
    //    GL_ALWAYS	    Always passes.
    glStencilFunc(GL_ALWAYS, 1, 1);

    //   void glStencilOp( GLenum fail, GLenum zfail, GLenum zpass )
    //     qui sert � indiquer la nouvelle valeur du stencil suivant le r�sultat du test du stencil et du depth :
    //     "fail" : op�ration � effectuer sur la valeur dans le stencil lorsque le stencil test a �chou� 
    //             -> GL_KEEP, GL_ZERO, GL_REPLACE, GL_INCR, GL_DECR, ou GL_INVERT.
    //     "zfail": op�ration � effectuer si le stencil est pass� mais pas le depth.
    //             -> GL_KEEP, GL_ZERO, GL_REPLACE, GL_INCR, GL_DECR, ou GL_INVERT.
    //     "zpass": op�ration � effectuer si le stencil et le depth sont valid�s.
    //             -> GL_KEEP, GL_ZERO, GL_REPLACE, GL_INCR, GL_DECR, ou GL_INVERT.
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

    //On limite les reflets � la surface du miroir
    //le miroir est un rectangle plein 
    //On le dessine dans le stencil buffer
    miroir(t, false); //On le dessine SANS la face arri�re

    //============== On dessine toute la scene ==============
    // Nettoyage du "frame buffer" et du "Z buffer" 
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //On ne modifie plus les valeurs du stencil buffer
    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
 
    //On dessine le reflet des objets en accord avec le stencil buffer
    //ET seulement s'ils sont derri�re le miroir, avec le plan de clipping
    glEnable(GL_CLIP_PLANE0);
    GLdouble eqn[4];
    eqn[0] = -1.0; eqn[1] = 0.0; eqn[2] = 0.0; eqn[3] = 0.0;
    glPushMatrix();
    {
      //On applique la transformation Mmiroir :
      // Ici deux rotations et une translation
      //On contr�le � la souris la rotation du miroir
      glRotatef(spin_y, 1, 0, 0); 
      glRotatef(spin_x, 0, 1, 0); 
      glTranslatef(-t, 0, 0);  //Centr� en -t, 0, 0

      glClipPlane(GL_CLIP_PLANE0, eqn); //On place le plan de clipping
      glScalef(-1, 1, 1);        //on applique la sym�trie
      
      //On applique la transformation Mmiroir_inverse
      //On applique les transformations inverses dans l'ordre inverse
      // D'abord la translation inverse
      glTranslatef(t, 0, 0); 
      //Puis les deux rotations inverses, dans l'ordre inverse
      glRotatef(-spin_x, 0, 1, 0); 
      glRotatef(-spin_y, 1, 0, 0); 
      
      //Et on peut dessiner le reflet.
      scene(false);
      //ombre(t); //!
    }
    glPopMatrix();
    glDisable(GL_CLIP_PLANE0);
        
    //On dessine l'ombre AVEC le test stencil : uniquement dans le miroir
    ombre(t);

    //On d�sactive le test de stencil, on veut maintenant dessiner la sc�ne normale
    glDisable(GL_STENCIL_TEST);


    //On dessine le miroir, en g�rant la transparence pour att�nuer le reflet
    glEnable(GL_BLEND); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);    
    miroir(t, true); //On le dessine AVEC la face arri�re
    glDisable(GL_BLEND);
  
    //On dessine les objets
    scene(false);
  }
  glPopMatrix();

  // Permute les "back buffer" et "front buffer" (double-buffering).
  glutSwapBuffers();
  
}//myDisplayFunc()

//============== Function pour faire bouger la scene !!!!! ==============
void specialKeysFunction(int k, int x, int y)
{
  if ((glutGetModifiers()) & GLUT_ACTIVE_SHIFT)
    switch (k)
      {
      case GLUT_KEY_UP:    lum[1]+=.1;break;
      case GLUT_KEY_DOWN:  lum[1]-=.1;break;
      case GLUT_KEY_RIGHT: lum[0]+=.1;break;
      case GLUT_KEY_LEFT:  lum[0]-=.1;break;
      case GLUT_KEY_PAGE_UP:     lum[2]+=.1;break;
      case GLUT_KEY_PAGE_DOWN:   lum[2]-=.1;break;
      }
  else
    switch (k)
      {
      case GLUT_KEY_UP:    tY=tY+.1;break;
      case GLUT_KEY_DOWN:  tY=tY-.1;break;
      case GLUT_KEY_RIGHT: tX=tX+.1;break;
      case GLUT_KEY_LEFT:  tX=tX-.1;break;
      case GLUT_KEY_PAGE_UP:     incr++;break;
      case GLUT_KEY_PAGE_DOWN:   incr--;break;
      }

  // Force l'appel de la fonction d'affichage.
  glutPostRedisplay();

} //specialKeysFunction()
 
void myKeyboardFunc(unsigned char k,int x,int y)  
{ 
  switch(k)  
    { 
    case 'w' : G_rot = 1 - G_rot;break;
    case ' ' : lum[3] = 1 - lum[3];break;
    case 27 : exit(0);break;
    default: break; 
    }  
  // actualisation de l'affichage  
  glutPostRedisplay(); 

}//myKeyboardFunc()

//myMouseFunc
void myMouseFunc(int button, int state, int x, int y) 
{
  if ((button == GLUT_LEFT_BUTTON)
      && (state == GLUT_DOWN)){
    mouse_x = x;
    mouse_y = y;
  }
}//myMouseFunc

void myMotionFunc(int x, int y){
  if (G_rot) { //Rotation globale
    spinG_x += (mouse_x - x);
    if (spinG_x > 360.0) spinG_x -= 360.0;
    if (spinG_x < -360.0) spinG_x += 360.0;

    spinG_y += (mouse_y - y);
    if (spinG_y > 360.0) spinG_y -= 360.0;
    if (spinG_y < -360.0) spinG_y += 360.0;
  }
  else {
    spin_x += (mouse_x - x);
    if (spin_x > 360.0) spin_x -= 360.0;
    if (spin_x < -360.0) spin_x += 360.0;

    spin_y += (mouse_y - y);
    if (spin_y > 360.0) spin_y -= 360.0;
    if (spin_y < -360.0) spin_y += 360.0;
  }


  mouse_x = x;
  mouse_y = y;
}//myMotionFunc()

void spinFunc(void)
{
  spin = spin + incr;
  if (spin > 360.0)
    spin -= 360.0;
  glutPostRedisplay();
   
}//spinFunc()

void initializeGlut(int argc,char** argv)
{ 
  glutInit(&argc,argv);
  // Param�tres du contexte de rendu.
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL );
  // Dimensions de la fen�tre.
  glutInitWindowSize(500, 500);
  // Position du coin haut-gauche de la fen�tre.
  glutInitWindowPosition(50,50);
  // Creation de la fen�tre (titre en param�tre).
  glutCreateWindow("Reflets");
  // Association des fonctions utilisateurs et des 
  // callbacks glut (appel�es lors d'un �v�nement).
  glutReshapeFunc(myReshapeFunc);
  glutDisplayFunc(myDisplayFunc);
  glutKeyboardFunc(myKeyboardFunc); 
  glutSpecialFunc(specialKeysFunction);
  glutMouseFunc(myMouseFunc);
  glutMotionFunc(myMotionFunc);
  glutIdleFunc(spinFunc);

  // Couleur du fond
  glClearColor(1, 1, 1, 1);

  // Activation du test de profondeur
  glEnable(GL_DEPTH_TEST);
	
  //On �paissit les lignes
  glLineWidth(2.0);
	
}//initializeGlut()

int main(int argc,char **argv)
{
  initializeGlut(argc,argv);
  init_lights();
  glutMainLoop();
  return 0;

}//main()

