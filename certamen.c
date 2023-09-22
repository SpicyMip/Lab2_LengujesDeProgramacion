#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "certamen.h"

void usuario(void* pregunta, int tipo, tCertamen* certamen, int n_pregunta){
    tPregunta* preguntaCertamen;
    switch (tipo){
        case 0: ;
            tEnunciadoAlternativa* preguntaAlternativaS=(tEnunciadoAlternativa*)pregunta;
            int alternativa_correctaS = preguntaAlternativaS->alternativa_correcta;
            preguntaCertamen=crearPregunta(certamen,"AlternativaSimple\n", &alternativa_correctaS, revisarAlternativaSimple);
            int respuestaAlternativaS;
            printf("Ingrese su respuesta: ");
            scanf("%d", &respuestaAlternativaS);
            printf("\n");
            preguntaCertamen->respuesta=&respuestaAlternativaS;
            asignarPregunta(certamen, n_pregunta , preguntaCertamen);
            break;
        case 1: ;
            tEnunciadoAlternativaMultiple* preguntaAlternativaM=(tEnunciadoAlternativaMultiple*)pregunta;
            int* alternativa_correctaM = preguntaAlternativaM->alternativa_correcta;
            char* alternativa_correctaMc=malloc(2*(preguntaAlternativaM->n_alternativas)*sizeof(char));
            for (int i=0;i < 2*(preguntaAlternativaM->n_alternativas)-1; i=i+2){
                alternativa_correctaMc[i]=alternativa_correctaM[i/2];
                alternativa_correctaMc[i+1]=' ';
            }
            preguntaCertamen=crearPregunta(certamen,"AlternativaMultiple\n", &alternativa_correctaM, revisarAlternativaMultiple);
            char* respuestaAlternativaM;
            int n_alternativas;
            printf("Ingrese cantidad de alternativas: ");
            scanf("%d", &n_alternativas);
            respuestaAlternativaM=malloc(2*n_alternativas*sizeof(char));
            printf("Ingrese sus respuestas de menor a mayor\n");
            for (int i=0; i < 2*(n_alternativas); i=i+2){
                printf("Ingrese su respuesta: ");
                scanf("%s", &respuestaAlternativaM[i]);
                respuestaAlternativaM[i+1]=' ';
            }
            printf("\n");
            preguntaCertamen->respuesta=&respuestaAlternativaM;
            asignarPregunta(certamen, n_pregunta , preguntaCertamen);
            break;
        case 2: ;
            tEnunciadoVerdaderoFalso* preguntaAlternativaVF=(tEnunciadoVerdaderoFalso*)pregunta;
            bool respuesta = preguntaAlternativaVF->respuesta;
            preguntaCertamen=crearPregunta(certamen,"VerdaderoFalso\n", &respuesta, revisarVerdaderoFalso);
            bool respuestaUsuario;
            char temp;
            printf("Ingrese V o F: ");
            scanf("%s", &temp);
            printf("\n");
            if(temp == 'V'){
                respuestaUsuario = true;
            }else if(temp=='F'){
                respuestaUsuario=false;
            }
            preguntaCertamen->respuesta=&respuestaUsuario;
            asignarPregunta(certamen, n_pregunta , preguntaCertamen);
            break;
        case 3: ;
            /* code */
            break;
    };
}

void procesar(char* tipo, FILE* fp, tCertamen* certamen, int n_pregunta){
    printf("%d", n_pregunta+1);
    printf(") ");
    if(strcmp(tipo, "AlternativaSimple\n")==0){
        tEnunciadoAlternativa pregunta;
        fgets(pregunta.enunciado, 128, fp);
        printf("%s\n", pregunta.enunciado);
        char alternativa[5];
        fgets(alternativa, 5, fp);
        pregunta.n_alternativas=atoi(alternativa);
        pregunta.alternativas=malloc(pregunta.n_alternativas*sizeof(char*));
        for(int j=0;j<pregunta.n_alternativas;j++){
            char x[64];
            fgets(x, 64, fp);
            pregunta.alternativas[j]=x;
            printf("%d", j+1);
            printf(") %s", pregunta.alternativas[j]);
        }
        char correcta[5];
        fgets(correcta, 5, fp);
        pregunta.alternativa_correcta=atoi(correcta);
        usuario(&pregunta, 0, certamen, n_pregunta);
    }else if (strcmp(tipo, "AlternativaMultiple\n")==0){
        tEnunciadoAlternativaMultiple pregunta;
        fgets(pregunta.enunciado, 128, fp);
        printf("%s\n", pregunta.enunciado);
        char n_alternativa[5];
        fgets(n_alternativa, 5, fp);
        pregunta.n_alternativas=atoi(n_alternativa);
        pregunta.alternativas=malloc(pregunta.n_alternativas*sizeof(char*));
        for(int j=0;j<pregunta.n_alternativas;j++){
            char x[64];
            fgets(x, 64, fp);
            pregunta.alternativas[j]=x;
            printf("%d", j+1);
            printf(") %s", pregunta.alternativas[j]);

        }
        printf("\n");
        char n_correcta[5];
        fgets(n_correcta, 5, fp);
        pregunta.n_correctas=atoi(n_correcta);
        pregunta.alternativa_correcta=malloc(pregunta.n_correctas*sizeof(int));
        for(int j=0;j<pregunta.n_correctas;j++){
            char x[5];
            fgets(x, 5, fp);
            pregunta.alternativa_correcta[j]=atoi(x);
        }
        usuario(&pregunta, 1, certamen, n_pregunta);
    }else if (strcmp(tipo, "VerdaderoFalso\n")==0){
        tEnunciadoVerdaderoFalso pregunta;
        fgets(pregunta.enunciado, 128, fp);
        printf("%s", pregunta.enunciado);
        char respuesta[5];
        fgets(respuesta, 5, fp);
        if (strcmp(respuesta, "V\n")==0){
            pregunta.respuesta=true;
        }else{
            pregunta.respuesta=false;
        }
        usuario(&pregunta, 2, certamen, n_pregunta);   
    }else if (strcmp(tipo, "Completar\n")==0){
        tEnunciadoCompletar pregunta;
        char n_textos[5];
        fgets(n_textos, 5, fp);
        pregunta.n_textos=atoi(n_textos);
        pregunta.textos=malloc(pregunta.n_textos*sizeof(char*));
        for (int j=0; j < pregunta.n_textos; j++){
            char text[64];
            fgets(text, 64, fp);
            printf("%s", text);
            printf("\n");
            pregunta.textos[j]=text;
        }
        pregunta.textos=malloc((pregunta.n_textos-1)*sizeof(char*));
        for (int j=0; j < (pregunta.n_textos-1); j++){
            char text[64];
            fgets(text, 64, fp);
            pregunta.respuestas[j]=text;
        }
        usuario(&pregunta, 3, certamen, n_pregunta);
    }
};

bool revisarAlternativaSimple(void* enunciado, void* respuesta){
    int* respuestaCorrecta=(int*)enunciado;
    int* respuestaUsuario=(int*)respuesta;
    int respuestaC=(int)*respuestaCorrecta;
    int respuestaU=(int)*respuestaUsuario;
    if(*respuestaUsuario==*respuestaCorrecta){
        return true;
    }else{
        return false;
    }
};

bool revisarAlternativaMultiple(void* enunciado, void* respuesta){
    char* respuestaCorrecta;
    char* respuestaUsuario;
    respuestaCorrecta=(char*)enunciado;
    respuestaUsuario=(char*)respuesta;
    if(strcmp(respuestaCorrecta, respuestaUsuario) == 0){
        return true;
    }else{
        return false;
    }
};

bool revisarVerdaderoFalso(void* enunciado, void* respuesta){
    bool* respuestaCorrecta;
    bool* respuestaUsuario;
    respuestaCorrecta=(bool*)enunciado;
    respuestaUsuario=(bool*)respuesta;
    if(respuestaCorrecta==respuestaUsuario){
        return true;
    }else{
        return false;
    }
};

bool revisarCompletar(void* enunciado, void* respuesta){
    if(strcmp(enunciado,respuesta) == 0){
        return true;
    }else{
        return false;
    }
};

tCertamen* crearCertamen(int n_preguntas){
    tCertamen* certamen=malloc(sizeof(tCertamen));
    certamen->n_preguntas=n_preguntas;
    tPregunta* preguntas=malloc(n_preguntas*sizeof(tPregunta));
    certamen->preguntas=preguntas;
    return certamen;
};

tPregunta* crearPregunta(tCertamen* certamen, char* tipo, void* enunciado, bool revisar(void*, void*)){
    tPregunta* pregunta=malloc(sizeof(tPregunta));
    strcpy(pregunta->tipo, tipo);
    pregunta->enunciado=enunciado;
    pregunta->revisar=revisar;
    return pregunta;
};


void asignarPregunta(tCertamen* certamen, int n_pregunta, tPregunta* pregunta){
    certamen->preguntas[n_pregunta]=*pregunta;
};

tPregunta leerPregunta(tCertamen* certamen, int n_pregunta){
    return certamen->preguntas[n_pregunta];
};

int largoCertamen(tCertamen certamen){
    return certamen.n_preguntas;
};

int nCorrectasCertamen(tCertamen* certamen){
    int count=0;
    for(int i=0;i<certamen->n_preguntas;i++){
        tPregunta pregunta=leerPregunta(certamen, i);
        if(pregunta.revisar(pregunta.enunciado,pregunta.respuesta)){
            count++;
        }
    }
    return count;
};
