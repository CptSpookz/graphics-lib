#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>

#define EventMask (KeyPressMask | ExposureMask)
#define PI 3.1415926535

/* Exemplo de estruturas de dados para a 
   biblioteca de funções gráficas em C, considerando 
   o plano como referência para o mundo */

float XWMax, XWMin, YWMax, YWMin;

struct Window {
  float xmin,
        xmax,
        ymin,
        ymax;
};
      
typedef struct Window window;

struct ViewPort {
  int xmin,
      xmax,
      ymin,
      ymax;
};
      
typedef struct ViewPort viewport;

struct Point2D {
  float x,
        y;
  int   color;
};
      
typedef struct Point2D point;

struct Object2D {
  int numbers_of_points;
  point * points;
};
  
typedef struct Object2D object; 

struct Color {
  float red,
        green,
        blue;
};
      
typedef struct Color ColorValues;    
  
struct Palette {
  int numbers_of_colors;
  ColorValues * colors;
};

typedef struct Palette palette;

struct Buffer {
  int MaxX,
      MaxY;
  int * buffer;
};

typedef struct Buffer bufferdevice;

struct HPoint2D {
  float x,
        y,
        w;
  int   color;
};

typedef struct HPoint2D hpoint;

struct HObject2D {
  int numbers_of_points;
  hpoint * points;
};

typedef struct HObject2D hobject;

struct HMatrix2D {
  float a11, a12, a13,
        a21, a22, a23,
        a31, a32, a33;
};

typedef struct HMatrix2D hmatrix;

/* estabelece os limites do mundo */
void SetWorld(float, float, float, float);

/* cria pontos e objetos no mundo */
point * SetPoint(float, float, int);
object * CreateObject(int);
int SetObject(point *, object *);

/* cria pontos e objetos homogeneos no mundo */
hpoint* SetHPoint(float, float, float, int);
hobject* CreateHObject(int);
int SetHObject(hpoint*, hobject*);
int DestroyHObject(hobject*);

/* sistemas de referências */
window * CreateWindow(float, float, float, float);
bufferdevice * CreateBuffer(int, int);
viewport* CreateViewPort(int, int, int, int);
hpoint* Sru2Srn(hpoint*, window*);
hpoint* Srn2Srd(hpoint*, viewport*);
//point * Srn2Srd(point *, bufferdevice *);

/* funções para criar e gerenciar uma paleta de cores */
palette * CreatePalette(int);
int SetColor(float, float, float, palette *);
ColorValues * GetColor(int, palette *);
object * ChangeColor(object *, int);

/* funções para conversão matricial e preenchimento de objetos */
int DrawLine(hpoint*, hpoint*, window*, viewport*, bufferdevice*, int); 
int DrawObject(hobject*, window*, viewport*, bufferdevice*);
int Fill(hobject*, window*, viewport*, bufferdevice*, int);

/* operações com objetos no mundo */
hobject* Rotate(hobject *, float);
hobject* Translate(hobject *, float, float);
hobject* Scale(hobject *, float, float);
hobject* Shear(hobject*, float, float); // operacao de cisalhamento
hpoint*  LinearTransf(hmatrix *, hpoint *);
hmatrix* ComposeMatrix(hmatrix *, hmatrix *);
hmatrix* SetRotMatrix(float);
hmatrix* SetSclMatrix(float, float);
hmatrix* SetSftMatrix(float, float);
hmatrix* SetShrMatrix(float, float); // matriz de cisalhamento

/* visualiza o buffer (SRD) no monitor virtual */
int Dump2X(bufferdevice *, palette *);
