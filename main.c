#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "certamen.h"

int main(){
    FILE *fp=fopen("certamen.txt", "r");
    if(fp==NULL){
        return 1;
    }
    char str[5];
    int n_preguntas;
    fgets(str, 10, fp);
    n_preguntas=atoi(str);
    tCertamen* certamen=crearCertamen(n_preguntas);

    for(int i=0; i < n_preguntas; i++){
        char tipo[64];
        fgets(tipo, 64, fp);
        printf("%s", tipo);
        procesar(tipo, fp, certamen, i);
    }
    int correctas=nCorrectasCertamen(certamen);
    printf("Su nota es: ");
    printf("%d", 100*correctas/n_preguntas);
    printf("\n");
    free(certamen);
    fclose(fp);
    return 0;
};