#include "cg2d.h"
#include <stdio.h>

void Center (float xmin, float ymin, float xmax, float ymax, window* win, float* shftVtr) {
    // Recebe as coordenadas de x e y máximos e mínimos da figura e da janela 
    // e retorna qual a distância necessária de shift para centralizar a figura
    float xtotal = fabsf(xmin + xmax);
    float ytotal = fabsf(ymin + ymax);
    // Calcula a distância necessária de cada borda para que a figura esteja no
    // centro da janela
    float xshft = -(-win->xmin - xtotal)/2;
    float yshft = -(-win->ymin - ytotal)/2;
    shftVtr[0] = xshft;
    shftVtr[1] = yshft;
    printf("%f %f\n",xtotal,ytotal);
    printf("%f %f\n",xshft,yshft);
}

int main() {
    palette *palheta;
    bufferdevice *dispositivo;
    viewport *vport;
    window *janela;

    SetWorld(-15, -10, 15, 10); // Define o tamanho do mundo  
    dispositivo = CreateBuffer(640,480); // cria um dispositivo
    janela = CreateWindow(-4.0, -4.0, 0.0, 0.0);
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
    /* Escalonando os objetos para que caibam nas coordenadas 
     * da janela de visualização. */
    spoli1 = TransObj(poli1, SetSclMatrix(0.30, 0.30));
    spoli2 = TransObj(poli2, SetSclMatrix(0.30, 0.30));
    
    float shftCenter[2];
    Center(spoli1->points[0].x, spoli1->points[0].y, spoli2->points[4].x, spoli2->points[3].y, janela, shftCenter);
    spoli1 = TransObj(spoli1, SetSftMatrix(shftCenter[0], shftCenter[1]));
    spoli2 = TransObj(spoli2, SetSftMatrix(shftCenter[0], shftCenter[1]));

    object *spoli3;
    spoli3 = TransObj(TransObj(spoli2, SetRotMatrix(45)), SetSftMatrix(-2.5,1.0));
    
    DrawObject(spoli1,janela,vport,dispositivo,3);
    DrawObject(spoli2,janela,vport,dispositivo,1);
    DrawObject(spoli3,janela,vport,dispositivo,2);

    Dump2X(dispositivo,palheta);

   return 0;
}
