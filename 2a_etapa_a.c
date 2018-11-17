#include "cg2d.h"

int main() {
    palette *palheta;
    bufferdevice *dispositivo;
    viewport *vport;
    window *janela;

    SetWorld(-15, -10, 15, 10); // Define o tamanho do mundo  
    dispositivo = CreateBuffer(640,480); // cria um dispositivo
    janela = CreateWindow(-6.0, -5.0, 0.0, 0.0);
    vport = CreateViewPort((dispositivo->MaxX - 300)/2, (dispositivo->MaxY - 200)/2, (dispositivo->MaxX + 300)/2, (dispositivo->MaxY + 200)/2);
    
    palheta = CreatePalette(5);  
    
    SetColor(0,0,0,palheta);
    SetColor(1,0,0,palheta);
    SetColor(0,1,0,palheta);
    SetColor(0,0,1,palheta);
    SetColor(1,1,1,palheta);

    object *poli1, *poli2;
    poli1 = CreateObject(4);
    poli2 = CreateObject(5);

    SetObject(SetPoint(-1.0,-2.0,1,3), poli1);
    SetObject(SetPoint(-1.0,-6.0,1,3), poli1);
    SetObject(SetPoint(-6.0,-6.0,1,3), poli1);
    SetObject(SetPoint(-6.0,-2.0,1,3), poli1);

    SetObject(SetPoint(-7.0,-3.0,1,1), poli2);
    SetObject(SetPoint(-4.0,-4.0,1,1), poli2);
    SetObject(SetPoint(-3.0,-6.0,1,1), poli2);
    SetObject(SetPoint(-6.0,-9.0,1,1), poli2);
    SetObject(SetPoint(-9.0,-8.0,1,1), poli2);

    object *spoli1, *spoli2;
    /* Escalando os objetos para que caibam nas coordenadas 
     * da janela de visualização. */
    spoli1 = TransObj(poli1, SetSclMatrix(0.5, 0.5));
    spoli2 = TransObj(poli2, SetSclMatrix(0.5, 0.5));
    
    object *spoli3;
    /* Aparentemente a operação de rotação rotaciona a figura em torno da origem,
     * não em torno do centro da própria figura, tornando necessário transpor a
     * figura original de volta para onde ela deveria estar. */
    spoli3 = TransObj(TransObj(spoli1, SetRotMatrix(75)), SetSftMatrix(-3,0));

    DrawObject(spoli1,janela,vport,dispositivo,3);
    DrawObject(spoli2,janela,vport,dispositivo,1);
    DrawObject(spoli3,janela,vport,dispositivo,2);

    Dump2X(dispositivo,palheta);

   return 0;
}
