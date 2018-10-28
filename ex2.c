#include "cg2d.h"

int main() {
    palette* palheta;
    bufferdevice* dispositivo;
    viewport* vport;
    window* janela;
    hobject *aInner, *aOuter, *bOuter, *bInner;
  
    SetWorld(-20, -20, 10, 15); // Define o tamanho do mundo  
    dispositivo = CreateBuffer(1024,768); // cria um dispositivo
    vport = CreateViewPort(dispositivo->MaxX/2,(dispositivo->MaxX/2)+250,dispositivo->MaxY/2,(dispositivo->MaxY/2)+250); // cria um viewport centralizado no SRD (250x250)
    janela = CreateWindow(-20.0,0.0,-20.0,0.0);  
    palheta = CreatePalette(6);  
    
    SetColor(0,0,0,palheta);
    SetColor(1,0,0,palheta);
    SetColor(0,1,0,palheta);
    SetColor(0,0,1,palheta);
    SetColor(1,1,1,palheta);

    aInner = CreateHObject(3);
    aOuter = CreateHObject(7);
    bOuter = CreateHObject(7);
    bInner = CreateHObject(4);

    /* 
     * Este objeto apresenta certa distorção, talvez por haverem 
     * poucos pontos na janela/poligono e a linha estar na diagonal
     */
    SetHObject(SetHPoint(-6.0,-5.0,0,3), aInner);
    SetHObject(SetHPoint(-4.0,-8.0,0,3), aInner);
    SetHObject(SetHPoint(-8.0,-8.0,0,3), aInner);
    SetHObject(SetHPoint(-6.0,-1.0,0,3), aOuter);
    SetHObject(SetHPoint(-1.0,-12.0,0,3), aOuter);
    SetHObject(SetHPoint(-3.0,-12.0,0,3), aOuter);
    SetHObject(SetHPoint(-4.0,-10.0,0,3), aOuter);
    SetHObject(SetHPoint(-8.0,-10.0,0,3), aOuter);
    SetHObject(SetHPoint(-9.0,-12.0,0,3), aOuter);
    SetHObject(SetHPoint(-11.0,-12.0,0,3), aOuter);

    SetHObject(SetHPoint(-6.0,-3.0,0,3), bInner);
    SetHObject(SetHPoint(-10.0,-3.0,0,3), bInner);
    SetHObject(SetHPoint(-10.0,-7.0,0,3), bInner);
    SetHObject(SetHPoint(-6.0,-7.0,0,3), bInner);
    SetHObject(SetHPoint(-4.0,-2.0,0,3), bOuter);
    SetHObject(SetHPoint(-4.0,-6.0,0,3), bOuter);
    SetHObject(SetHPoint(-5.0,-7.0,0,3), bOuter);
    SetHObject(SetHPoint(-4.0,-8.0,0,3), bOuter);
    SetHObject(SetHPoint(-4.0,-14.0,0,3), bOuter);
    SetHObject(SetHPoint(-12.0,-14.0,0,3), bOuter);
    SetHObject(SetHPoint(-12.0,-2.0,0,3), bOuter);

//    DrawObject(aInner,janela,vport,dispositivo); // desenha a parte de dentro do A dentro da janela no buffer
//    DrawObject(aOuter,janela,vport,dispositivo); // desenha a parte de fora do A dentro da janela no buffer
    DrawObject(Shear(aInner,0.45,0),janela,vport,dispositivo); // desenha a parte de dentro do A (itálico) dentro da janela no buffer do dispositivo 
    DrawObject(Shear(aOuter,0.45,0),janela,vport,dispositivo); // desenha a parte de fora do A (itálico) da janela no buffer do dispositivo

//    DrawObject(bInner,janela,vport,dispositivo); // desenha a primeira parte de dentro do B da janela no buffer do dispositivo
//    DrawObject(Translate(bInner,0,-5),janela,vport,dispositivo); // desenha a segunda parte de dentro do B da janela no buffer do dispositivo
//    DrawObject(bOuter,janela,vport,dispositivo);  // desenha a parte de dentro do B da janela no buffer do dispositivo
//    DrawObject(Shear(bInner,0.45,0),janela,vport,dispositivo); // desenha a primeira parte de dentro do B (itálico) da janela no buffer do dispositivo
//    DrawObject(Shear(Translate(bInner,0,-5),0.45,0),janela,vport,dispositivo); // desenha a segunda parte de dentro do B (itálico) da janela no buffer do dispositivo
//    DrawObject(Shear(bOuter,0.45,0),janela,vport,dispositivo);  // desenha a parte de dentro do B (itálico) da janela no buffer do dispositivo

    Dump2X(dispositivo,palheta);
    
    DestroyHObject(aInner);
    DestroyHObject(aOuter);
    DestroyHObject(bInner);
    DestroyHObject(bOuter);

    free(palheta);
    free(dispositivo);
    free(vport);
    free(janela);
    return 0;
}
