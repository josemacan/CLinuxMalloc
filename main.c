#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


#define BLOCK_SIZE 20       // tamano del bloque de metadata 20 dec = 14 h
#define align4(x) (((((x)-1)>>2)<<2)+4)
#define MAXSHELL 100

// RECETAS
/*
 * 1) Crear un nodo - LISTO
 * 2) Funcion alocar memoria - LISTO
 * 3) Buscar en una lista - LISTO
 * 4) Eliminar de una lista - LISTO
 * 5) Funcion para validar una direccion introducida
 * 6) Free
 * 7) Fusion entre bloques
 * 8) Dividir un bloque
 * 9) Manejo de input
 *
 * */

// VARIABLES

struct node *first = NULL;  /* variable que siempre apunta al primer nodo de la lista*/
struct node *ultim = NULL;

struct node {
    int value;  /* datos se guardan en el nodo*/
    int value_alin;
    int free;
    struct node *next; /*puntero al siguiente nodo*/
    struct node *prev; /*puntero al anterior nodo*/
    void *direccion;
};

// FUNCIONES

void nuevonodo(int );   // @desc: lanza creacion de nodo
// @param: int - cant de espacio a reservar sin alinear
// @return:

void *mallocar(int );   // @desc: aloca memoria
// @param: int - cant de espacio a reservar sin alinear
// @return: direccion de memoria a la que
// apunta la estructura creada

int sum_alinear (int ); // @desc: alinear a multiplos de 4
// @param: int - cant espacio sin alinear
// @return: int - cant espacio alineada

void displayList();     // @desc: muestra lista de todos los bloques reservados
// @param:
// @return:

struct node *buscar (struct node *, long int , int);
// @desc: busca en la lista de todos los bloques reservados actualmente
// @param: struct node - puntero a nodo inicial de la lista
//         int - busca mediante "first search" el valor
//         int - 1 -> direccion - 0 -> valor entero
// @return: struct node - direccion a nodo encontrado / NULL caso contrario

struct node *borrar (struct node *, size_t );
// @desc: busca en la lista el bloque con valor clave para borrarlo
// @param: struct node - puntero a nodo inicial de la lista
//         int - busca mediante "first search" el valor
// @return: struct node - direccion a nodo encontrado / NULL caso contrario

struct node *extender_heap(struct node *, size_t , size_t);
// @desc: alinea, extiende el heap y crea nuevo nodo
// @param: struct node - puntero a nodo inicial de la lista
//         int - busca mediante "first search" el valor
// @return: struct node - direccion a nodo encontrado / NULL caso contrario

void mensaje_inicio ();
// @desc: despliega mensaje de ayuda para inicio
// @param:
// @return:

int valid_addr (void *);
// @desc: la direccion se encuentra entre la base y el heap
// @param: direccion del bloque de memoria que busco
// @return: 0 -> No, 1 -> Si

void eliminarCaracterNuevaLinea (const char* );
// @desc: elimino "\n" y reemplazo por caracter de fin de char
// @param:  arreglo de caracteres
// @return: -

char *strremove(char *str, const char *sub);
// @desc: quito una parte de la cadena
// @param: *str - cadena completa, *sub - parte a eliminar
// @return:

int prefix(const char *, const char *);
// @desc: comprueba si un arreglo de caracteres posee una determinada palabra al inicio
// @param: 1) prefijo 2) arreglo completo
// @return: 1 = true, 0 = false

int liberar (struct node *);
// @desc: libera un bloque reservado -> Coloco free
// @param: direccion del bloque a liberar
// @return:

struct node *fusion (struct node* );
// @desc: fusiono un bloque vacío con el siguiente o el anterior (en caso de ser posible)
// @param: bloque origen que quiero fusionar
// @return: puntero del bloque expandido

struct node *separar(struct node* , size_t);
// @desc: crea un bloque nuevo dentro del espacio reservado para un bloque mas grande
// @param: struct node* - direccion del bloque que quiero dividir - size_t - tamano deseado del nuevo bloque
// @return: direccion del nuevo bloque

int launcher_malloc(char *input);
void launcher_buscar_d( char *input);
void launcher_buscar_v( char *input);
int launcher_separar( char *input);
void launcher_liberar( char *input);
void launcher_borrar( char *input);
void launcher_tests();



void imprimirDirecciones(); //////// BORRAR

void grupoTest();
int testAlocarMemoria(); // Prueba de correcta allocacion de memoria
int testAlocarMemoriaERROR();   // Pruebo valor erroneo de memoria
int testLiberarMemoria();   // Pruebo flag de libre
int testLiberarMemoriaERROR();  // Pruebo liberar un espacio no existente
int testBuscarDireccion();  // Pruebo encontrar chunk de memoria por su direccion
int testBuscarDireccionERROR(); // Pruebo error de chunk no existente
int testBuscarValor();  // Pruebo encontrar chunk de memoria por valor (FIRST SEARCH)
int testBuscarValorERROR(); // Pruebo error de chunk no existe
int testSeparar();  // Pruebo
int testSepararERROR(); // Pruebo valor mas grande que espacio del bloque a separar
int testdesplegarLista();   // Pruebo cantidad de bloques alocados desplegados igual a existentes


int main() {

    while(1) {

        printf("\nInput: ");
        char input[MAXSHELL];
        fgets(input, MAXSHELL, stdin);
        eliminarCaracterNuevaLinea(input);
        if (prefix("q",input)) {                //  "q" -> salir
            return 0;
        }
        else if (prefix("m", input)) {               //  "m" -> malloc
            if(launcher_malloc(input) != 1){
                printf("\nERROR - Ingrese un valor de memoria mayor a 0");
            }
        }
        else if (prefix("d", input)) {               // "d" -> despliega lista de
            displayList();
        }
        else if (prefix("h", input)) {               // "h" -> despliega mensaje de ayuda
            mensaje_inicio();
        }
        else if (prefix("sd", input)) {               // "sd" -> despliega para buscar por direccion
            launcher_buscar_d(input);
        }
        else if (prefix("sv", input)) {               // "sv" -> despliega para buscar por valor
            launcher_buscar_v(input);
        }

        else if (prefix("s", input)) {               // "s" -> despliega para separar un bloque
            if(launcher_separar(input) == 0){
                printf("\nERROR AL SEPARAR BLOQUE");
            }
        }

        else if (prefix("f", input)) {               // "f" -> funcion liberar
            launcher_liberar(input);
        }

        else if (prefix("d", input)) {               // "d" -> funcion borrar
            launcher_borrar(input);
        }

        else if (prefix("t", input)) {               // "t" -> funcion desplegar tests
            launcher_tests(input);
        }


        else{
            printf("\nComando incorrecto");
            mensaje_inicio();
        }
    }

    return 0;
}

int launcher_malloc(char *input){
    int b = 0;
    char* cad = strremove(input, "m ");     // quito clave
    b = atoi(cad);                              // convierto  char en entero

    if(b <= 0){
        return 0;
    }
    else{
        mallocar(b);
        return 1;
    }
}

void launcher_buscar_d(char *input){
    long int valorinthexa = 0;

    char* cad = strremove(input, "sd ");
    valorinthexa = strtoul(cad, NULL, 0);     //convierto string de numero hexa en entero
    printf("\nDIRE: %s, VALOR ENTERO: %ld", input, valorinthexa);
    struct node *retorno = buscar(first,valorinthexa,1);         // busco dando clave direccion
    if(retorno == NULL){
        printf("-- NO ENCONTRADO --");
    }
    else{
        printf("- BUSQUEDA POR DIRECCION- ENCONTRADO -- Tam: %d  - Direccion: %p \n", retorno -> value, (void*) retorno);
    }
}

void launcher_buscar_v(char *input){
    int b = 0;

    char* cad = strremove(input, "sv ");
    b = atoi(cad);                            // convierto en char en entero

    struct node *retorno = buscar(first,b,0);                   // busco y muestro el primer bloque que coincida con el valor b

    if(retorno == NULL){
        printf("-- NO ENCONTRADO --");
    }
    else{
        printf("- BUSQUEDA POR TAMANIO - ENCONTRADO -- Tam: %d  - Direccion: %p \n", retorno -> value, (void*) retorno);
    }

}

int launcher_separar(char *input){
    long int valorinthexa;

    char* cad = strremove(input, "s ");
    valorinthexa = strtoul(cad, NULL, 0);     //convierto string de numero hexa en entero
    void *puntero = (void *)valorinthexa;                  // convierto de entero a hexa

    if(valid_addr(puntero)){                               // chequeo si la direccion esta entre la base y el heap actual
        printf("\nIngrese tamano del nuevo bloque: ");
        char inp [MAXSHELL];
        fgets(inp, MAXSHELL, stdin);
        eliminarCaracterNuevaLinea(inp);
        size_t tam_s = atoi(inp);
        printf("\nTamano ingresado: %ld", tam_s);

        separar(puntero,tam_s);

        return 1;
    }
    else{
        printf("\nNO SE PUEDE ENCONTRAR EL BLOQUE A SEPARAR\n");
        return 0;
    }
}



void launcher_liberar(char *input){
    long int valorinthexa = 0;

    char* cad = strremove(input, "f ");
    valorinthexa = strtoul(cad, NULL, 0);     //convierto string de numero hexa en entero
    void *puntero = (void *)valorinthexa;                   // convierto entero en puntero

    if(liberar(puntero) == 0){
        fprintf(stderr, "\n **LIBERAR ---- FALLO EN LIBRERAR MEMORIA!!!");
    }
}

void launcher_borrar(char *input){
    long int valorinthexa = 0;

    char* cad = strremove(input, "dd ");
    valorinthexa = strtoul(cad, NULL, 0);     //convierto string de numero hexa en entero

    borrar(first,valorinthexa);
}

void launcher_tests(char *input){
    grupoTest();
}

void grupoTest(){
    int passed = 0;
    int error = 0;
    // -- 1)
    if(testAlocarMemoria() == 1){
        printf("\n1) Alocar memoria: CORRECTO");
        passed++;
    }else{
        printf("\n1) Alocar memoria: -- FALLO --");
        error++;
    }

    // -- 2)
    if(testAlocarMemoriaERROR() == 0){
        printf("\n2) Fallo al alocar memoria: CORRECTO");
        passed++;
    }else{
        printf("\n2) Fallo al alocar memoria: -- FALLO --");
        error++;
    }

    // -- 3)
    if(testLiberarMemoria() == 1){
        printf("\n3) Liberar memoria: CORRECTO");
        passed++;
    }else{
        printf("\n3) Liberar memoria: -- FALLO --");
        error++;
    }

    // -- 4)
    if(testLiberarMemoriaERROR() == 1){
        printf("\n4) Fallo al liberar memoria: CORRECTO");
        passed++;
    }else{
        printf("\n4) Fallo al liberar memoria: -- FALLO --");
        error++;
    }

    // -- 5)
    if(testBuscarDireccion() == 1){
        printf("\n5) Buscar por direccion: CORRECTO");
        passed++;
    }else{
        printf("\n5) Buscar por direccion: -- FALLO --");
        error++;
    }

    // -- 6)
    if(testBuscarDireccionERROR() == 1){
        printf("\n6) Fallo al buscar por direccion: CORRECTO");
        passed++;
    }else{
        printf("\n6) Fallo al buscar por direccion: -- FALLO --");
        error++;
    }

    // -- 7)
    if(testBuscarValor() == 1){
        printf("\n7) Buscar por valor: CORRECTO");
        passed++;
    }else{
        printf("\n7) Buscar por valor: -- FALLO --");
        error++;
    }

    // -- 8)
    if(testBuscarValorERROR() == 1){
        printf("\n8) Fallo al buscar por valor: CORRECTO");
        passed++;
    }else{
        printf("\n8) Fallo al buscar por valor: -- FALLO --");
        error++;
    }
    /*
    // -- 9)
    if(testSeparar() == 1){
        printf("\n9) Separar bloque: CORRECTO");
        passed++;
    }else{
        printf("\n9) Separar bloque: -- FALLO --");
        error++;
    }

    // -- 10)
    if(testSepararERROR() == 1){
        printf("\n10) Fallo al separar bloque: CORRECTO");
        passed++;
    }else{
        printf("\n10) Fallo al separar bloque: -- FALLO --");
        error++;
    }

    // -- 11)
    if(testdesplegarLista() == 1){
        printf("\n11) Cantidad de bloques desplegados: CORRECTO");
        passed++;
    }else{
        printf("\n11)  Cantidad de bloques desplegados: -- FALLO --");
        error++;
    }
     */

}

int testAlocarMemoria(){
    char input[MAXSHELL] = "m 10";
    int retorno = launcher_malloc(input);
    return retorno;
}

int testAlocarMemoriaERROR(){
    char input[MAXSHELL] = "m 0";
    return launcher_malloc(input);
}

int testLiberarMemoria(){
    struct node * dire = 0;
    dire = mallocar(20);
    liberar((void*)dire);
    if(dire -> free == 1){
        return 1;
    }
    else{
        return 0;
    }


}

int testLiberarMemoriaERROR(){
    long int valorinthexa = strtoul("0x558000000000", NULL, 0);     //convierto string de numero hexa en entero
    void *puntero = (void *)valorinthexa;                   // convierto entero en puntero

    if(liberar(puntero) == 0){
        return 1;
    }
    else{
        return 0;
    }
}

int testBuscarDireccion(){
    struct node * dire = 0;
    dire = mallocar(40);
    void *direccion = (void*) dire;
    long int direint = (long int) direccion;
    printf("\ndire: %ld", direint);
    struct node *retorno = buscar(first, direint ,1);         // busco dando clave direccion
    if(retorno != NULL){
        liberar(retorno);
        return 1;
    }
    else{
        liberar(retorno);
        return 0;
    }
}

int testBuscarDireccionERROR(){
    long int valorinthexa = strtoul("0x558000000000", NULL, 0);     //convierto string de numero hexa en entero
    struct node *retorno = buscar(first,valorinthexa,1);         // busco dando clave direccion
    if(retorno == NULL){
        liberar(retorno);
        return 1;
    }
    else{
        liberar(retorno);
        return 0;
    }
}

int testBuscarValor(){
    //struct node * dire = 0;
    //dire = mallocar(40);
    int valor = 40;
    struct node *retorno = buscar(first,valor,0);         // busco dando clave direccion
    if(retorno != NULL){
        liberar(retorno);
        return 1;
    }
    else{
        liberar(retorno);
        return 0;
    }
}

int testBuscarValorERROR(){
    int valor = 491238;
    struct node *retorno = buscar(first,valor,0);         // busco dando clave direccion
    if(retorno == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

int testSeparar(){
    struct node * dire = 0;
    dire = mallocar(80);
    struct node * nuevo = separar(dire,10);
    if(  nuevo != NULL){
        liberar(dire);
        liberar(nuevo);
        return 1;
    }
    else{
        liberar(dire);
        liberar(nuevo);
        return 0;
    }
}

int testSepararERROR(){
    struct node * dire = 0;
    dire = mallocar(80);
    struct node * nuevo = separar(dire,300);
    if( nuevo == NULL){
        liberar(dire);
        liberar(nuevo);
        return 1;
    }
    else{
        liberar(dire);
        liberar(nuevo);
        return 0;
    }
}



void mensaje_inicio (){
    printf("\nIngrese: ");
    printf("\n - m [TAMANO]     para alocar memoria");
    printf("\n - f [DIRECCION]  para liberar memoria");
    printf("\n - sd [DIRECCION]  para buscar un bloque mediante su direccion");
    printf("\n - sv [TAMANO]  para buscar un bloque mediante su tamano - METODO FIRST SEARCH");
    printf("\n - s [DIRECCION]  para separar un bloque");
    printf("\n - d           para desplegar lista de bloques alocados");
    printf("\n - t           para iniciar unit tests\n");


    printf("\n - q           para salir del programa\n");
}

void * mallocar(int tam){

    struct node * dire = 0;
    int tamanio = 0;

    tamanio = sum_alinear(tam);

    if(first == NULL){          // LISTA VACIA - SE QUIERE ASIGNAR EL PRIMER BLOQUE
        dire = extender_heap(NULL, tamanio, tam);   // ultimo = NULL, entrego tamano para obtener nuevo bloque
        if(!dire){
            fprintf(stderr, "FALLO EN EXTENDER HEAP - MALLOCAR...\n");
            exit(-1);
        }
        first = dire;           // defino como primer nodo al bloque que asigne recien (solo cuando es el primero)
        ultim = dire;           // defino como ultimo nodo al bloque recien asignado
    }
    else{                       // NO ES EL PRIMER BLOQUE QUE ASIGNO
        if(ultim == first){     // Si solo hay un unico elemento en la lista
            dire = extender_heap(ultim, tamanio, tam);  // paso ultimo elemento de la lista (en este caso, es igual al primero)
            if(!dire){
                fprintf(stderr, "FALLO EN EXTENDER HEAP - MALLOCAR...\n");
                exit(-1);
            }
        }
        else{                   // Hay mas de un elemento en la lista
            dire = extender_heap(ultim,tamanio,tam); // paso ultimo elemento de la lista para asignar bloque continuo
            if(!dire){
                fprintf(stderr, "FALLO EN EXTENDER HEAP - MALLOCAR...\n");
                exit(-1);
            }
        }
        ultim -> next = dire;   // el ex-ultimo de la lista (ahora penultimo) tiene como siguiente al bloque que le sigue
        ultim = dire;           // el ultimo ahora es el nuevo bloque

    }

    return dire;                // devuelvo puntero al nuevo bloque

}

int sum_alinear (int tam){
    int tama = 0;
    tama = align4(tam);
    tama = tama + BLOCK_SIZE;
    tama = align4(tama);

    return tama;
}


struct node *extender_heap(struct node *ultimo, size_t tamano, size_t tam){

    struct node *dirheap = 0;          // puntero a la direccion actual del heap - direccion donde va a estar el nuevo
    // bloque
    dirheap = sbrk(0);             // dir. actual del heap
    void *direccion = sbrk(0);

    long int rtado_sbrk = 0;
    rtado_sbrk = (long int) sbrk(tamano);   // muevo el heap tanto espacio como necesito


    if(rtado_sbrk < 0){
        fprintf(stderr, "No se puede mover el heap - MALLOCAR...\n");
        exit(-1);
    }

    if(first == NULL){                      //  Si la lista esta vacia. Estoy asignando el primer bloque. Sin anteriores
        dirheap -> prev = NULL;
    }
    else                                    // La lista contiene uno o mas bloques
    {
        if (first != NULL && ultimo == first){  // La lista tiene 1 elemento (first). Estoy asignando el segundo bloque de la lista
            first -> next = dirheap;            // el primer elemento de la lista se anida con el segundo
        }
        dirheap -> prev = ultimo;               // Lista tiene 1 o mas elementos. Anidar con el nuevo bloque con los de la lista
    }

    dirheap -> next = NULL; // no tiene siguiente (estoy asignando un nuevo bloque, por ende, es el ultimo de la lista
    dirheap -> value = tam; // valor
    dirheap -> value_alin = tamano; // valor alineado
    dirheap -> free = 0;    // bloque marcado como usado
    dirheap -> direccion = (void *) direccion;

    return dirheap;
}

int liberar (struct node *p){

    if(valid_addr( (void *) p )){   // si la direccion del bloque es valida

        struct node *bloque;
        bloque = buscar(first, (long int) p, 1); // asigno a bloque el bloque de la direccion - recibo direccion

        bloque -> free = 1; // set el flag de libre

        /* Fusion con anterior - si es posible */
        if(bloque -> prev && bloque -> prev -> free){ // si el anterior esta inicializado y tambien esta libre
            bloque = fusion (bloque -> prev);         // fusiono el anterior con el actual
        }
        /* Fusion con el siguiente  */
        if(bloque -> next != NULL){                     // si el siguiente esta definido
            fusion (bloque);           // fusiono actual con el siguiente
        }
        else{                                   // SI NO TIENE SIGUIENTE -> tope del heap
            if(bloque -> prev){                 // defino como siguiente del anterior a vacio
                bloque -> prev -> next = NULL;
            }
            else{
                first = NULL;                   // defino el break en la direccion del inicio del chunk b
            }
            brk(bloque);
        }
        return 1;
    }
    else
    {
        return 0;
    }
}



struct node *fusion (struct node* b){

    if(b -> next != NULL && b -> next -> free){     // Si no es el primero y ademas el siguiente esta libre
        b -> value_alin = b -> value_alin + b -> next -> value_alin;    // incremento valor alineado
        b -> value = b -> value + b -> next -> value;
        b -> next = b -> next -> next;                                  // modifico anidacion
        if( b -> next ){                    // si tiene anterior
            b -> next -> prev = b;          // modifico siguiente
        }

    }
    return  b;

}

struct node *separar(struct node *bloque_original, size_t tam){
    /* Bloque original = Bloque original + Nuevo*/  // Nuevo bloque va al final del actual

    struct node *nuevo;                         // valor
    int tam_alineado = sum_alinear((int)tam );     // alineo tamanio ingresado
    printf("\nTamano ingresado: %zu - Alineado: %d", tam, tam_alineado);

    if(bloque_original -> value_alin <= tam_alineado){   // chequeo que el bloque nuevo cabe dentro del actual
        fprintf(stderr, "\nFALLO EN SEPARAR - Quiere separar un bloque mas chico al necesario...\n");
        return NULL;
    }

    nuevo = (struct node *) (bloque_original + (bloque_original -> value_alin - tam_alineado));    // direccion de nuevo bloque
    nuevo -> value_alin = tam_alineado;    // valor alineado del nuevo bloque
    nuevo -> value = tam ;              // valor del nuevo bloque
    nuevo -> next = bloque_original -> next;                             // modificacion de anidacion
    nuevo -> prev = bloque_original;
    nuevo -> free = 1;                                          // creo un bloque free
    nuevo -> direccion = (void *) nuevo;
    bloque_original ->value_alin = bloque_original -> value_alin - tam_alineado;
    bloque_original ->value = bloque_original -> value - tam;
    bloque_original -> next = nuevo;
    if( nuevo -> next){
        nuevo -> next -> prev = nuevo;
    }
    printf("\nBloque restante ---- Valineado: %d - Val: %d ",bloque_original -> value_alin, bloque_original -> value);
    printf("\nBloque creado al final del espacio ---- Valineado: %d - Val: %d ",nuevo -> value_alin, nuevo -> value);

    return nuevo;
}



int valid_addr (void *p)        // devuelvo si una direccion es valida para liberar (Si esta dentro del heap o no)
{
    if ( (void *)first != NULL)                   // si base esta inicializada
    {
        if ( p >= (void *) first && p < sbrk (0))     // si la direccion esta dentro del heap y la direccion esta dentro del heap total
        {
            void *a = buscar(first, (long int) p, 1);   // obtengo la direccion dentro de la lista

            return (p == a );   // devuelvo true si la direccion esta en la lista
        }
    }
    return (0);     // no direccion valida
}

void *obtener_bloque (void *p){     // Obtengo el bloque dada una direccion
    void *tmp;
    tmp = p;
    //tmp -= BLOCK_SIZE; // VER VER VER
    p = tmp;

    if(p == tmp){
        printf("\nIGUALES");
    }

    return p;
}

struct node *borrar(struct node *lista, size_t tam){
    struct node * resultado = 0;
    resultado = buscar(lista,tam, 1);       // compruebo si la direccion esta dentro de la lista
    if(resultado == NULL){
        fprintf(stderr, "FALLO AL BORRAR - NO SE ENCUENTRA - BORRAR...\n");
        exit(-1);
    }
    (resultado -> prev) -> next  = resultado -> next;           // modifico next y prev de nodos anterior y posterior
    (resultado -> next) -> prev = resultado -> prev;

    return resultado;
}



struct node *buscar (struct node *list, long int n, int flag)
{   // flag = 1 -> direccion // flag = 0 -> valor
    printf("\nBUSCANDO: %ld", n);
    struct node *p;

    for (p = list; p != NULL; p = p -> next){           // Recorro toda la lista
        if(flag == 0) {                                 // busco por valor
            if (p->value == n) {
                //printf("- BUSQUEDA POR TAMANIO- ENCONTRADO: %d \n", p->value, p->direccion);
                return p;
            }
        }
        else{                                           // busco por direccion
            if ((long int) p == n) {
                //printf("- BUSQUEDA POR DIRECCION - ENCONTRADO: %d \n", p->value, p->direccion);
                return p;
            }
        }
    }

    return NULL;            // si no encontre en la lista
}

void displayList()
{
    printf(" \n");
    printf(" \n-- DISPLAY LIST \n");
    struct node *p;
    if(first == NULL){
        printf("**LISTA VACÍA**\n");
    }
    for (p = first; p != NULL; p = p -> next){      // recorro lista anidada e imprimo
        printf("Dir: %p - Valor: %d - Valor alin: %d - Dire: %p - Free: %d - Prev: %p - Next: %p\n", (void *) p,
                p -> value, p -> value_alin, p -> direccion, p -> free, (void *) p -> prev , (void *) p -> next);
    }

    //imprimirDirecciones();
}

void imprimirDirecciones()
{
    printf(" \n");
    printf(" \n-- DISPLAY LIST \n");
    struct node *p;
    if(first == NULL){
        printf("**LISTA VACÍA**\n");
    }
    for (p = first; p != NULL; p = p -> next){      // recorro lista anidada e imprimo
        printf("Dir: %p - Dire: %p \n", (void *) p, p -> direccion);
    }
}

int prefix(const char *pre, const char *str){
    return strncmp(pre, str, strlen(pre)) == 0;
}

void eliminarCaracterNuevaLinea (const char* string){
    char *pos;
    if ((pos=strchr(string, '\n')) != NULL)
        *pos = '\0';
}

char *strremove(char *str, const char *sub) {
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}
