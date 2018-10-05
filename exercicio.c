#include "cg2d.h"

int main() {
  palette* palheta;
  bufferdevice* dispositivo;
  viewport* vport;
  window* janela;
  hobject *poligono1, *poligono2;
  
  SetWorld(-20, 10, -20, 15); // Define o tamanho do mundo  
  dispositivo = CreateBuffer(640,480); // cria um dispositivo
  vport = CreateViewPort(0,640,0,480); // cria um viewport

  palheta = CreatePalette(6);  
  SetColor(0,0,0,palheta);
  SetColor(1,0,0,palheta);
  SetColor(0,1,0,palheta);
  SetColor(0,0,1,palheta);
  SetColor(1,1,1,palheta);
  
  poligono1 = CreateHObject(5);
  poligono2 = CreateHObject(4);
  
  SetHObject(SetHPoint(-9.0,-8.0,0,1), poligono1);
  SetHObject(SetHPoint(-7.0,-3.0,0,1), poligono1);
  SetHObject(SetHPoint(-4.0,-4.0,0,1), poligono1);
  SetHObject(SetHPoint(-3.0,-6.0,0,1), poligono1);
  SetHObject(SetHPoint(-6.0,-9.0,0,1), poligono1);
  
  SetHObject(SetHPoint(-6.0,-2.0,0,3), poligono2);
  SetHObject(SetHPoint(-1.0,-2.0,0,3), poligono2);
  SetHObject(SetHPoint(-1.0,-6.0,0,3), poligono2);
  SetHObject(SetHPoint(-6.0,-6.0,0,3), poligono2);
  
  janela = CreateWindow(-8.0,5.0,-7.0,5.0); // define uma janela de visualização
  // janela = CreateWindow(-10.0,0.0,-10.0,0.0);  
  
  DrawObject(poligono1,janela,vport,dispositivo); // desenha o poligono 1 dentro da janela no buffer do dispositivo 
  DrawObject(poligono2,janela,vport,dispositivo); // desenha o poligono 2 dentro da janela no buffer do dispositivo
  
  /* 
   * Dispositivo gráfico matricial.
   * A janela de visualização considerada não está adequada para visualizar completamente os dois objetos.
   * Poderiamos considerar a janela definida pelos pontos (-10,-10) e (0,0)
   */
  
  Dump2X(dispositivo,palheta);

  DestroyHObject(poligono1);
  DestroyHObject(poligono2);
  free(palheta);
  free(dispositivo);
  free(vport);
  free(janela);
  return 0;
}
