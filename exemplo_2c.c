
// Para executar:
// gcc -c cg2d.c
// gcc exemplo_2c.c -o exemplo_2c cg2d.o -lm -lX11
// ./exemplo_2c

#include "cg2d.h"

int main(int argc, char ** argv) {
  
  palette * palheta;
  bufferdevice * monitor;
  window * janela;
  viewport * porta1, * porta2, * porta3, * porta4;
  object * poligono1, * poligono2, * poligono3, * poligono4;
  
  SetWorld(-20, -20, 10, 15); // Define o tamanho do mundo  
  monitor = CreateBuffer(640,480); // Cria um monitor virtual
  // monitor = CreateBuffer(1024,768); // conforme solicitado
  
  palheta = CreatePalette(5);  // Cria um colormap
  SetColor(0,0,0,palheta);
  SetColor(1,0,0,palheta);
  SetColor(0,1,0,palheta);
  SetColor(0,0,1,palheta);
  SetColor(1,1,1,palheta);
  
  poligono1 = CreateObject(7);
  poligono2 = CreateObject(3);
  
  SetObject(SetPoint(-6.0,-1.0,1,3), poligono1);
  SetObject(SetPoint(-11.0,-11.0,1,3), poligono1);
  SetObject(SetPoint(-9.0,-11.0,1,3), poligono1);
  SetObject(SetPoint(-8.0,-9.0,1,3), poligono1);
  SetObject(SetPoint(-4.0,-9.0,1,3), poligono1);
  SetObject(SetPoint(-3.0,-11.0,1,3), poligono1);
  SetObject(SetPoint(-1.0,-11.0,1,3), poligono1);
  
  SetObject(SetPoint(-6.0,-5.0,1,3), poligono2);
  SetObject(SetPoint(-8.0,-8.0,1,3), poligono2);
  SetObject(SetPoint(-4.0,-8.0,1,3), poligono2);
  
  janela = CreateWindow(-13.0, -13.0, 1.0, 1.0);

  porta1 = CreateViewPort(10, 10, 250, 110);
  DrawObject(poligono1,janela,porta1,monitor,4);
  DrawObject(poligono2,janela,porta1,monitor,4);

  porta2 = CreateViewPort(280, 100, 600, 250);
  poligono3 = TransObj(poligono1, SetSkwMatrix(0.1,0.0));
  poligono4 = TransObj(poligono2, SetSkwMatrix(0.1,0.0));
  DrawObject(poligono3,janela,porta2,monitor,2);
  DrawObject(poligono4,janela,porta2,monitor,2);

  porta3 = CreateViewPort(50, 270, 300, 450);
  poligono3 = TransObj(poligono1, SetSkwMatrix(0.15,0.0));
  poligono4 = TransObj(poligono2, SetSkwMatrix(0.15,0.0));
  DrawObject(poligono3,janela,porta3,monitor,1);
  DrawObject(poligono4,janela,porta3,monitor,1);

  porta4 = CreateViewPort(350, 310, 630, 470);
  poligono3 = TransObj(poligono1, SetSkwMatrix(0.2,0.0));
  poligono4 = TransObj(poligono2, SetSkwMatrix(0.2,0.0));
  DrawObject(poligono3,janela,porta4,monitor,3);
  DrawObject(poligono4,janela,porta4,monitor,3);
 
  Dump2X(monitor,palheta);

/*
Observações:
	a) repare que o valor para o parâmetro de cisalhamento deve ser baixo;
	b) está ocorrendo uma translação do objeto para a esquerda conforme aumenta o cisalhamento. Esse efeito não era para acontecer. Você saberia explicar o porquê desse fenômeno?
*/
 
  return 0;
  }

