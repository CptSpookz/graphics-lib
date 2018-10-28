#include "cg2d.h"

void SetWorld(float xmin, float xmax, float ymin, float ymax) {
 XWMax = xmax;
 XWMin = xmin;
 YWMax = ymax;
 YWMin = ymin;
}

point * SetPoint(float x, float y, int color) {
  point * pnt;
  
  pnt = (point *) malloc(sizeof(point)); 
  pnt->x = x;
  pnt->y = y;
  pnt->color = color;
  
  return pnt;
}

object * CreateObject(int numbers_of_points) {
  object * ob;
 
  ob = (object *) malloc(sizeof(object));
  ob->numbers_of_points = 0;
  ob->points = (point *) malloc(numbers_of_points*sizeof(point));
 
  return ob;
}

int SetObject(point * pnt, object * ob) {
  ob->points[ob->numbers_of_points] = *pnt;
  ob->numbers_of_points = ob->numbers_of_points + 1;

  return 0;
}

hpoint* SetHPoint(float x, float y, float w, int color) {
    hpoint* pnt;
    
    pnt = (hpoint*) malloc(sizeof(hpoint)); 
    pnt->x = x;
    pnt->y = y;
    pnt->w = w;
    pnt->color = color;
    
    return pnt;
}

hobject* CreateHObject(int numbers_of_points) {
  hobject* ob;
 
  ob = (hobject*) malloc(sizeof(hobject));
  ob->numbers_of_points = 0;
  ob->points = (hpoint*) malloc(numbers_of_points*sizeof(hpoint));
 
  return ob;
}

int SetHObject(hpoint* pnt, hobject* ob) {
  ob->points[ob->numbers_of_points] = *pnt;
  ob->numbers_of_points = ob->numbers_of_points + 1;

  return 0;
}

int DestroyHObject(hobject* ob) {
    free(ob->points);
    free(ob);

    return 0;
}

object * ChangeColor(object * ob, int color) {
  object * oob;
  int i;
  
  oob = CreateObject(ob->numbers_of_points); 
  for(i=0;i<ob->numbers_of_points;i++) {
    SetObject(SetPoint(ob->points[i].x,ob->points[i].y,color),oob);    
    }
    
  return oob;  
}

palette * CreatePalette(int numbers_of_colors) {
  palette * pal;

  pal = (palette *) malloc(sizeof(palette));
  pal->numbers_of_colors = 0;
  pal->colors = (ColorValues *) malloc(numbers_of_colors*sizeof(ColorValues));
  
  return pal;
}

int SetColor(float red, float green, float blue, palette * pal) {
  pal->colors[pal->numbers_of_colors].red = red;
  pal->colors[pal->numbers_of_colors].green = green;
  pal->colors[pal->numbers_of_colors].blue = blue;
  pal->numbers_of_colors = pal->numbers_of_colors + 1;

  return 0;
}
  
ColorValues * GetColor(int value, palette * pal) {
 ColorValues * color;
 
 color = (ColorValues *) malloc(sizeof(ColorValues)); 
 color->red = pal->colors[value].red;
 color->green = pal->colors[value].green;
 color->blue = pal->colors[value].blue; 
 
 return color;
}

bufferdevice * CreateBuffer(int maxx, int maxy) {
  bufferdevice * dev;
  
  dev = (bufferdevice *) malloc(sizeof(bufferdevice));
  dev->MaxX = maxx;
  dev->MaxY = maxy;
  dev->buffer = (int *) malloc(maxx*maxy*sizeof(int));
    
  return dev;
}
  
window * CreateWindow(float xmin, float xmax, float ymin, float ymax) {
  window * win;

  win = (window *) malloc(sizeof(window));
  win->xmin = xmin;
  win->xmax = xmax;
  win->ymin = ymin;
  win->ymax = ymax;
  
  return win;
}

/*point * Srn2Srd(point * ponto, bufferdevice * dev) {
  point * dpt;

  dpt = (point *) malloc(sizeof(point));
  dpt->x = round((ponto->x)*(dev->MaxX - 1));
  dpt->y = round((ponto->y)*(dev->MaxY - 1));
  dpt->color = ponto->color;
 
  return dpt;
}*/

viewport* CreateViewPort(int xmin, int xmax, int ymin, int ymax) {
    viewport* vpt;
    
    vpt = (viewport*) malloc(sizeof(viewport));
    vpt->xmin = xmin;
    vpt->xmax = xmax;
    vpt->ymin = ymin;
    vpt->ymax = ymax;

    return vpt;
}

hpoint* Sru2Srn(hpoint* ponto, window* janela) {
  hpoint* np;

  np = (hpoint*) malloc(sizeof(hpoint));
  np->x = (ponto->x - janela->xmin)/(janela->xmax - janela->xmin);
  np->y = (ponto->y - janela->ymin)/(janela->ymax - janela->ymin);
  np->w = ponto->w;
  np->color = ponto->color;
  
  return np;  
}

hpoint* Srn2Srd(hpoint* ponto, viewport* vpt) {
  hpoint* dpt;

  dpt = (hpoint*) malloc(sizeof(hpoint));
  dpt->x = round((ponto->x)*(vpt->xmax - 1));
  dpt->y = round((ponto->y)*(vpt->ymax - 1));
  dpt->w = ponto->w;
  dpt->color = ponto->color;
 
  return dpt;
}

int InWin(hpoint* pt, window* win) {
  if ((pt->x >= win->xmin)&&(pt->x <= win->xmax)&&(pt->y >= win->ymin)&&(pt->y <= win->ymax)) return 1;
  else return 0;
}

hpoint* InterX(hpoint* p1, hpoint* p2, float x, float w) {
 float a, b, aux;
 
 if (p2->x - p1->x) {
   a = (p2->y - p1->y)/(p2->x - p1->x);
   b = p1->y - a*p1->x;
   aux = a*x+b;
   }
 else aux = 1000000.0;  
 
 return SetHPoint(x,aux,w,p1->color);
}

hpoint* InterY(hpoint* p1, hpoint* p2, float y, float w) {
 float a, b, aux;

 if (p2->x - p1->x) {
   a = (p2->y - p1->y)/(p2->x - p1->x);
   b = p1->y - a*p1->x;
   if (a) aux = (y-b)/a;
   else aux = 1000000.0;
 }
 else aux = p2->x;
 
 return SetHPoint(aux,y,w,p1->color);
}

int DrawLine(hpoint* p1, hpoint* p2, window* win, viewport* vpt, bufferdevice* dev, int color) {
  float a, b;
  int i, j, aux;
  hpoint *pn1, *pd1, *pn2, *pd2;
  
  pn1 = Sru2Srn(p1,win);
  pd1 = Srn2Srd(pn1,vpt);
  pn2 = Sru2Srn(p2,win);
  pd2 = Srn2Srd(pn2,vpt);
  
  if (pd1->x > pd2->x) {
      aux = pd1->x;
      pd1->x = pd2->x;
      pd2->x = aux;
      aux = pd1->y;
      pd1->y = pd2->y;
      pd2->y = aux;
      aux = pd1->w;
      pd1->w = pd2->w;
      pd2->w = aux;
  }

   i = pd1->x;
   j = pd1->y;
   
   if (pd1->x == pd2->x) {
     while (j < pd2->y) {
       dev->buffer[(dev->MaxY - j - 1) * dev->MaxX + i] = color;
       j++;
     }
   }
   else {
     a = (pd2->y - pd1->y)/(pd2->x - pd1->x);
     b = pd1->y - a*pd1->x;
     while (i < pd2->x) {
       dev->buffer[(dev->MaxY - j - 1) * dev->MaxX + i] = color;
       aux = j;
       j = round(a*(++i) + b);
       
       if (j > aux) {
           while (aux < j) {
               dev->buffer[(dev->MaxY - aux - 1) * dev->MaxX + i] = color; 
               aux++;
           }
       }
       if (j < aux) {
           while (aux > j) { 
               dev->buffer[(dev->MaxY - aux - 1) * dev->MaxX + i] = color;
               aux--;
           }
       }
     }
   }

  free(pn1);
  free(pd1);
  free(pn2);
  free(pd2);
  return 0;
}

int DrawObject(hobject* ob, window* win, viewport* vpt, bufferdevice* dev) {
  int i;
  float aux, w = 0;
  hpoint *p1, *p2, *paux;
  
  for(i=0;i<ob->numbers_of_points;i++) {
    p1 = SetHPoint(ob->points[i].x,ob->points[i].y,ob->points[i].w,ob->points[i].color);
    p2 = SetHPoint(ob->points[(i+1)%ob->numbers_of_points].x,ob->points[(i+1)%ob->numbers_of_points].y,
            ob->points[(i+1)%ob->numbers_of_points].w,ob->points[(i+1)%ob->numbers_of_points].color);
    
    if (p1->y > p2->y) {
      aux = p1->y;
      p1->y = p2->y;
      p2->y = aux;
      aux = p1->x;
      p1->x = p2->x;
      p2->x = aux;
      aux = p1->w;
      p1->w = p2->w;
      p2->w = aux;
    }
    if ((p1->y < win->ymax)&&(p2->y > win->ymax)) {
      paux = InterY(p1,p2,win->ymax, w);
      if (InWin(paux,win)) {
        p2 = paux;
      } 
    }
    if ((p1->y < win->ymin)&&(p2->y > win->ymin)) {
      paux = InterY(p1,p2,win->ymin, w);
      if (InWin(paux,win)) {
        p1 = paux;
      } 
    }
    if (p1->x > p2->x) {
      aux = p1->y;
      p1->y = p2->y;
      p2->y = aux;
      aux = p1->x;
      p1->x = p2->x;
      p2->x = aux;
      aux = p1->w;
      p1->w = p2->w;
      p2->w = aux;
    }
    if ((p1->x < win->xmax)&&(p2->x > win->xmax)) {
      paux = InterX(p1,p2,win->xmax, w);
      if (InWin(paux,win)) {
        p2 = paux;
      } 
    }
    if ((p1->x < win->xmin)&&(p2->x > win->xmin)) {
      paux = InterX(p1,p2,win->xmin, w);
      if (InWin(paux,win)) {
        p1 = paux;
      } 
    }

    if ((InWin(p1,win))&&(InWin(p2,win))) DrawLine(p1,p2,win,vpt,dev,p1->color);
  }

  return 0;
}

int Fill(hobject* obj, window* win, viewport* vpt, bufferdevice* dev, int color) {
  return 0;
}

hobject* Rotate(hobject * ob, float theta) {
  hobject* oob;
  hmatrix* rotmatrix;
  int i;
  
  oob = CreateHObject(ob->numbers_of_points);
  rotmatrix = SetRotMatrix(theta);
  for(i = 0; i < ob->numbers_of_points; i++) {
    SetHObject(LinearTransf(rotmatrix,&ob->points[i]),oob);
  }

  return oob;
}
  
hobject* Translate(hobject* ob, float x, float y) {
  hobject* oob;
  int i;
  
  oob = CreateHObject(ob->numbers_of_points); 
  for(i = 0; i < ob->numbers_of_points; i++) {
    SetHObject(SetHPoint(ob->points[i].x + x,ob->points[i].y + y,ob->points[i].w,ob->points[i].color),oob); 
  }
    
  return oob;
}

hobject* Scale(hobject* ob, float sx, float sy) {
  hobject* oob;
  hmatrix* sclmatrix;
  int i;
  
  oob = CreateHObject(ob->numbers_of_points); 
  sclmatrix = SetSclMatrix(sx,sy);
  for(i = 0; i < ob->numbers_of_points; i++) {
    SetHObject(LinearTransf(sclmatrix,&ob->points[i]),oob);
  }
  
  return oob;  
}

hobject* Shear(hobject* ob, float sx, float sy) {
   hobject* oob;
   hmatrix* shrmatrix;
   int i;

   oob = CreateHObject(ob->numbers_of_points);
   shrmatrix = SetShrMatrix(sx, sy);
   for(i = 0; i < ob->numbers_of_points; i++) {
       SetHObject(LinearTransf(shrmatrix,&ob->points[i]),oob);
   }

   return oob;
}

hpoint * LinearTransf(hmatrix * m, hpoint * p) {
  hpoint * pt;
  
  pt = (hpoint *) malloc(sizeof(hpoint));
  
  pt->x = m->a11*p->x + m->a12*p->y + m->a13*p->w;
  pt->y = m->a21*p->x + m->a22*p->y + m->a23*p->w;
  pt->w = m->a31*p->x + m->a32*p->y + m->a33*p->w;
  pt->color = p->color;

  return pt;
}

hmatrix * ComposeMatrix(hmatrix * m1, hmatrix * m2) {
  hmatrix * m;

  m = (hmatrix *) malloc(sizeof(hmatrix));
  
  m->a11 = m1->a11*m2->a11 + m1->a12*m2->a21 + m1->a13*m2->a31;
  m->a12 = m1->a11*m2->a12 + m1->a12*m2->a22 + m1->a13*m2->a32;
  m->a13 = m1->a11*m2->a13 + m1->a12*m2->a23 + m1->a13*m2->a33;
  
  m->a21 = m1->a21*m2->a11 + m1->a22*m2->a21 + m1->a23*m2->a31;
  m->a22 = m1->a21*m2->a12 + m1->a22*m2->a22 + m1->a23*m2->a32;
  m->a23 = m1->a21*m2->a13 + m1->a22*m2->a23 + m1->a23*m2->a33;
  
  m->a31 = m1->a31*m2->a11 + m1->a32*m2->a21 + m1->a33*m2->a31;
  m->a32 = m1->a31*m2->a12 + m1->a32*m2->a22 + m1->a33*m2->a32;
  m->a33 = m1->a31*m2->a13 + m1->a32*m2->a23 + m1->a33*m2->a33;
  
  return m;
}

hmatrix * SetRotMatrix(float th) {
  hmatrix * m;

  m = (hmatrix *) malloc(sizeof(hmatrix));
  
  m->a11 = cos((th*PI)/180.0); m->a12 = (-1.0)*sin((th*PI)/180.0); m->a13 = 0.0;
  m->a21 = sin((th*PI)/180.0); m->a22 = cos((th*PI)/180.0);        m->a23 = 0.0;
  m->a31 = 0.0;                m->a32 = 0.0;                       m->a33 = 1.0;
  
  return m;
  }

hmatrix * SetSclMatrix(float sx, float sy) {
  hmatrix * m;

  m = (hmatrix *) malloc(sizeof(hmatrix));
  
  m->a11 = sx;  m->a12 = 0.0;  m->a13 = 0.0;
  m->a21 = 0.0; m->a22 = sy;   m->a23 = 0.0;
  m->a31 = 0.0; m->a32 = 0.0;  m->a33 = 1.0;
  
  return m;
  }

hmatrix * SetSftMatrix(float dx, float dy) {
  hmatrix * m;

  m = (hmatrix *) malloc(sizeof(hmatrix));
  
  m->a11 = 1.0;  m->a12 = 0.0;  m->a13 = dx;
  m->a21 = 0.0;  m->a22 = 1.0;  m->a23 = dy;
  m->a31 = 0.0;  m->a32 = 0.0;  m->a33 = 1.0;
  
  return m;  
}

hmatrix* SetShrMatrix(float sx, float sy) {
  hmatrix * m;

  m = (hmatrix *) malloc(sizeof(hmatrix));
  
  m->a11 = 1.0;  m->a12 = sx;   m->a13 = 0.0;
  m->a21 = sy;   m->a22 = 1.0;  m->a23 = 0.0;
  m->a31 = 0.0;  m->a32 = 0.0;  m->a33 = 1.0;
  
  return m;  
}

ColorValues * RGB2HSV(ColorValues * rgb) {
  float r, g, b, h, s, v, max, min;
  ColorValues * hsv;
  
  r = rgb->red;
  g = rgb->green;
  b = rgb->blue;
  
  if ((r>=g)&&(r>=b)) max = r;
  if ((g>=r)&&(g>=b)) max = g;
  if ((b>=g)&&(b>=r)) max = b;
  
  if ((r<=g)&&(r<=b)) min = r;
  if ((g<=r)&&(g<=b)) min = g;
  if ((b<=g)&&(b<=r)) min = b;
  
  v = max;
  
  s = (max-min)/max;
  
  if ((max==r)&&(g>=b)) h = 60.0 * (g-b)/(max-min);
  if ((max==r)&&(g<b)) h = 60.0 * (g-b)/(max-min) + 360;
  if (max==g) h = 60.0 * (b-r)/(max-min) + 120;
  if (max==b) h = 60.0 * (r-g)/(max-min) + 240; 
  
  hsv = (ColorValues *) malloc(sizeof(ColorValues));
  
  hsv->red = h;
  hsv->green = s;
  hsv->blue = v;
  
  return hsv;
}

ColorValues * HSV2RGB(ColorValues * hsv) {
  float r, g, b, h, s, v, f, p, q, t;
  ColorValues * rgb;
  int hi;
  
  h = hsv->red;
  s = hsv->green;
  v = hsv->blue; 
  
  rgb = (ColorValues *) malloc(sizeof(ColorValues));
  
  if (s==0) {
    rgb->red = v;
    rgb->green = v;
    rgb->blue = v;
    }
  else {
    hi = ((int)floor(h/60.0)) % 6;
    f = h/60.0 - hi;
    p = v*(1.0-s);
    q = v*(1.0-f*s);
    t = v*(1.0-(1.0-f)*s);
    if (hi==0) {
      rgb->red = v;
      rgb->green = t;
      rgb->blue = p;
      }
    if (hi==1) {
      rgb->red = q;
      rgb->green = v;
      rgb->blue = p;
      }
    if (hi==2) {
      rgb->red = p;
      rgb->green = v;
      rgb->blue = t;
      }
    if (hi==3) {
      rgb->red = p;
      rgb->green = q;
      rgb->blue = v;
      }
    if (hi==4) {
      rgb->red = t;
      rgb->green = p;
      rgb->blue = v;
      }
    if (hi==5) {
      rgb->red = v;
      rgb->green = p;
      rgb->blue = q;
      }       
    }
  
  return rgb;
}

int Dump2X(bufferdevice * dev, palette * pal) {
  Display               * display;
  XImage                * ximage;
  Window                window;
  XEvent                an_event;
  GC                    gc;
  Visual                * visual;
  XGCValues             values;
  int                   m, n, screen, dplanes;
  int                   width, height, ret = 1;
  ColorValues           * cor;
  
  width = dev->MaxX;
  height = dev->MaxY; 

  if ((display = XOpenDisplay(NULL)) == NULL) ret = 0;
  else {  
    screen = DefaultScreen(display);
    dplanes = DisplayPlanes(display,screen);   
    visual = XDefaultVisual(display,screen);
  
    if (!(window=XCreateSimpleWindow(display,RootWindow(display,screen),0,0,width,height,1,BlackPixel(display,screen),WhitePixel(display,screen)))) ret = 0;
    else {
      XSelectInput(display, window, EventMask);
      XStoreName(display, window, "Monitor Virtual");
      gc = XCreateGC(display, window, 0, &values);
  
      XMapWindow(display,window);
      XSync(display,False);
  
      ximage = XCreateImage(display,visual,dplanes,ZPixmap,0,malloc(width*height*sizeof(int)),width,height,8,0);

      for(m=0;m<height;m++) {
        for(n=0;n<width;n++) {
          cor = GetColor(dev->buffer[m*width+n],pal);
          ximage -> data[(m*4)*width+n*4] = (char) round((cor->blue)*255);
          ximage -> data[(m*4)*width+n*4+1] = (char) round((cor->green)*255);
          ximage -> data[(m*4)*width+n*4+2] = (char) round((cor->red)*255);
          ximage -> data[(m*4)*width+n*4+3] = (char) 0;
          }
        }

      XPutImage(display,window,gc,ximage,0,0,0,0,width,height);

      /* Trata os eventos */
      while(1) {
      XNextEvent(display, &an_event);
      switch(an_event.type) {
	case Expose:
             	XPutImage(display,window,gc,ximage,0,0,0,0,width,height);
                break;
	/* outros eventos ... */
           }
        }

      }
    }
 
  return ret;
}
