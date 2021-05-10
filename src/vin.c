#include <IL/il.h>
#include <GL/glut.h>


#define DEFAULT_WIDTH  640
#define DEFAULT_HEIGHT 480

static int width  = DEFAULT_WIDTH;
static int height = DEFAULT_HEIGHT;

void Display() 
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  glMatrixMode(GL_MODELVIEW);
  
  glBegin(GL_QUADS);
    glTexCoord2i(0, 0); glVertex2i(0,   0);
    glTexCoord2i(0, 1); glVertex2i(0,   height);
    glTexCoord2i(1, 1); glVertex2i(width, height);
    glTexCoord2i(1, 0); glVertex2i(width, 0);
  glEnd();

  glutSwapBuffers();
} 

void Reshape(GLsizei newwidth, GLsizei newheight) 
{  
  glViewport(0, 0, width=newwidth, height=newheight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, width, height, 0.0, 0.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  
  glutPostRedisplay();
}

  
void Init(int w, int h) 
{
  glViewport(0, 0, w, h);
  glEnable(GL_TEXTURE_2D);
 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, w, h, 0.0, 0.0, 100.0);

  glMatrixMode(GL_MODELVIEW);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
  glClearDepth(0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int LoadImage(char* filename)
{
  ILuint image; 

  ilGenImages(1, &image);
  ilBindImage(image);
  ILboolean success = ilLoadImage(filename);
     
  if (success)
    {
      success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE); 
      if (!success) return -1;
    }
  else return -1;
  return image;
}

int main(int argc, char** argv) 
{

  GLuint texid;
  int    image;

  if (argc < 1) return -1;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE);
  glutInitWindowSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
  char* title = { argv[1] };
  glutCreateWindow(title);
  glutDisplayFunc(Display);
  glutReshapeFunc(Reshape);
  Init(DEFAULT_WIDTH, DEFAULT_HEIGHT);

  if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
    {
      printf("DevIL version not supported\n");
      return -1;
    }
  ilInit();

  image = LoadImage(argv[1]);
  if (image == -1)
    {
      printf("Failed to load picture file %s\n", argv[1]);
      return -1;
    }

  glGenTextures(1, &texid);
  glBindTexture(GL_TEXTURE_2D, texid);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
	       0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
 

  glutMainLoop();
    
  ilDeleteImages(1, &image);
  glDeleteTextures(1, &texid);

  return 0;
} 
