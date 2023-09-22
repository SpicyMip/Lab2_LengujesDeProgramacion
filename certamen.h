#ifndef A_H
#define A_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char enunciado[128];
    int n_alternativas;
    char** alternativas;
    int alternativa_correcta;
} tEnunciadoAlternativa;

typedef struct {
    char enunciado[128];
    int n_alternativas;
    char** alternativas;
    int n_correctas;
    int* alternativa_correcta;
} tEnunciadoAlternativaMultiple;

typedef struct {
    char enunciado[128];
    bool respuesta;
} tEnunciadoVerdaderoFalso;

typedef struct {
    int n_textos;
    char** textos;
    char** respuestas;
} tEnunciadoCompletar;

typedef struct {
    char tipo[64];
    void* enunciado;
    void* respuesta;
    bool (*revisar)(void*, void*);
} tPregunta;

typedef struct {
    int n_preguntas;
    tPregunta* preguntas;
} tCertamen;

/*
Revisa si la respuesta a la pregunta es correcta
    Parametros:
        enunciado (void*): Respuesta correcta de la pregunta
        respuesta (void*): Respuesta que da el usuario
    Retorno:
        (bool): true o false si las respuestas estan correctas o incorrectas

*/
bool revisarAlternativaSimple(void* enunciado, void* respuesta);
bool revisarAlternativaMultiple(void* enunciado, void* respuesta);
bool revisarVerdaderoFalso(void* enunciado, void* respuesta);
bool revisarCompletar(void* enunciado, void* respuesta);

/*
Crea un nuevo certamen vacio
    Parametros:
        n_preguntas(int): cantidad de preguntas del certamen
    Retorno:
        certamen(tCertamen*): el certamen vacio sin preguntas

*/
tCertamen* crearCertamen(int n_preguntas);
/*
Crea una pregunta con el enunciado y funcion de revision dados
    Parametros:
        certamen(tCertamen*):
        tipo(char*): tipo de pregunta
        enunciado(void*): respuesta correcta de la pregunta
        revisar(void*,void*)(bool): puntero a funcion dependiendo del tipo de pregunta
    Retorno:
        pregunta(tPregunta*): pregunta sin la respuesta del usuario

*/
tPregunta* crearPregunta(tCertamen* certamen, char* tipo, void* enunciado, bool revisar(void*, void*));
/*
Asigna la pregunta a la posicion n_pregunta del certamen
    Parametros:
        certamen(tCertamen*): certamen para asignar la pregunta
        n_pregunta(int): posicion donde se asignara la pregunta
        pregunta(tPregunta*): pregunta a ser asignada
    Retorno:
        No retorna
*/
void asignarPregunta(tCertamen* certamen, int n_pregunta, tPregunta* pregunta);
/*
Retorna la pregunta en la posicion n_pregunta del certamen
    Parametros:
        certamen(tCertamen*): certamen con la pregunta
        n_pregunta(int): posicion que se quiere obtener
    Retorno:
        pregunta(tPregunta): pregunta del certamen
*/
tPregunta leerPregunta(tCertamen* certamen, int n_pregunta);
/*
Retorna el numero de preguntas en un certamen
    Parametros:
        certamen(tCertamen): certamen con preguntas
    Retorno:
        certamen.n_preguntas(int): largo del certamen
*/
int largoCertamen(tCertamen certamen);
/*
Retorna el numero de respuestas correctas que tiene el certamen
    Parametros:
        certamen(tCertamen*): certamen a evaluar
    Retorno:
        count(int): cantidad de preguntas correctas
*/
int nCorrectasCertamen(tCertamen* certamen);
/*
La funcion lee el archivo y recolectan las preguntas en sus strucs respectivos
    Parametros:
        tipo(char*): tipo de pregunta
        fp(FILE*): archivo a leer
        certamen(tCertamen*): certamen
        n_pregunta(int): numero de pregunta que va (contador)
    Retorno:
        No retorna
*/
void procesar(char* tipo, FILE* fp, tCertamen* certamen, int n_pregunta);
/*
traspasa la informacion de los strucs al genertico tPregunta y pide la info al usuario
    Parametros:
        pregunta(void*): pregunta en formato void*
        tipo(int): tipo de pregunta
        certamen(tCertamen*): certamen
        n_pregunta(int): numero de pregunta que va (contador)
    Retorno:
        No retorna
*/
void usuario(void* pregunta, int tipo, tCertamen* certamen, int n_pregunta);

#endif