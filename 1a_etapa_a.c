#include "cg2d.h"

typedef struct {
    object *outer;
    object *inner1, *inner2;
} letraB;

int main() {
    palette *palheta;
    bufferdevice *dispositivo;
    viewport *vport1, *vport2;
    window *janela;
    letraB regular, italico;

    SetWorld(-20, -20, 10, 15); // Define o tamanho do mundo  
    dispositivo = CreateBuffer(640,480); // cria um dispositivo
    palheta = CreatePalette(5);  
    
    SetColor(0,0,0,palheta);
    SetColor(1,0,0,palheta);
    SetColor(0,1,0,palheta);
    SetColor(0,0,1,palheta);
    SetColor(1,1,1,palheta);

    regular.outer = CreateObject(7);
    regular.inner1 = CreateObject(4);
    regular.inner2 = CreateObject(4);

    /* 
     * Este objeto apresenta certa distorção, talvez por haverem 
     * poucos pontos na janela/poligono e a linha estar na diagonal
     */
    SetObject(SetPoint(-6.0,-3.0,1,3), regular.inner1);
    SetObject(SetPoint(-10.0,-3.0,1,3), regular.inner1);
    SetObject(SetPoint(-10.0,-7.0,1,3), regular.inner1);
    SetObject(SetPoint(-6.0,-7.0,1,3), regular.inner1);
    
    SetObject(SetPoint(-6.0,-8.0,1,3), regular.inner2);
    SetObject(SetPoint(-10.0,-8.0,1,3), regular.inner2);
    SetObject(SetPoint(-10.0,-12.0,1,3), regular.inner2);
    SetObject(SetPoint(-6.0,-12.0,1,3), regular.inner2);

    SetObject(SetPoint(-4.0,-2.0,1,3), regular.outer);
    SetObject(SetPoint(-4.0,-6.0,1,3), regular.outer);
    SetObject(SetPoint(-5.0,-7.0,1,3), regular.outer);
    SetObject(SetPoint(-4.0,-8.0,1,3), regular.outer);
    SetObject(SetPoint(-4.0,-14.0,1,3), regular.outer);
    SetObject(SetPoint(-12.0,-14.0,1,3), regular.outer);
    SetObject(SetPoint(-12.0,-2.0,1,3), regular.outer);

    janela = CreateWindow(-18.0,-18.0,1.0,1.0);  
 
    vport1 = CreateViewPort(150, 150, 300, 300);
    DrawObject(regular.inner1,janela,vport1,dispositivo,3); // desenha a primeira parte de dentro do B da janela no buffer do dispositivo
    DrawObject(regular.inner2,janela,vport1,dispositivo,3); // desenha a segunda parte de dentro do B da janela no buffer do dispositivo
    DrawObject(regular.outer,janela,vport1,dispositivo,3);  // desenha a parte de dentro do B da janela no buffer do dispositivo

    vport2 = CreateViewPort(310, 150, 460, 300);
    italico.inner1 = TransObj(regular.inner1, SetSkwMatrix(0.45,0.0));
    italico.inner2 = TransObj(regular.inner2, SetSkwMatrix(0.45,0.0));
    italico.outer = TransObj(regular.outer, SetSkwMatrix(0.45,0.0));
    DrawObject(italico.inner1,janela,vport2,dispositivo,3); // desenha a primeira parte de dentro do B (itálico) da janela no buffer do dispositivo
    DrawObject(italico.inner2,janela,vport2,dispositivo,3); // desenha a segunda parte de dentro do B (itálico) da janela no buffer do dispositivo
    DrawObject(italico.outer,janela,vport2,dispositivo,3);  // desenha a parte de dentro do B (itálico) da janela no buffer do dispositivo

    Dump2X(dispositivo,palheta);

   return 0;
}
