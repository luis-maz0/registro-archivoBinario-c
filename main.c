#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include<time.h>

//****************************************************************MAZO GOMEZ LUIS JAVIER**********************************************************************************//
/*
IMPORTANTE -> EL PROGRAMA CUENTA CON VALIDACIONES EN LA ENTRADA DE DATOS PERO ALGUNAS HAY QUE MEJORARLAS.
COSAS A CORREGIR: AGREGAR VALIDACIONES Y FECHA AL ARCHIVO BINARIO DE LOS COMPETIDORES DADOS DE BAJA FISICA.

*/

struct fecha{
    int dia;
    int mes;
    int anio;
};

struct corredor
{
  int orden;
  int corredor;
  int dia;
  char mes[3];
  int anio;
  int edad;
  char pais[3];
  float tiempo;
  int activo;
};

//------------FUNCIONES--------------//

//1. CREAR MENU DE OPCIONES: Crea el menú principal de la aplicación. Retornará la opción seleccinada.
int crearMenuPrincipal(){
    int opcion;
    do{
    printf("\n\n****************** OPCIONES *******************\n\n");
    printf("1) Listar datos del archivo csv\n");
    printf("2) Crear un archivo binario .data\n");
    printf("3) Migrar datos csv al archivo .data\n");
    printf("4) Listar datos del archivo binario .data.\n");
    printf("5) Agregar nuevo corredor\n");
    printf("6) Buscar corredor\n");
    printf("7) Modificar corredor existente\n");
    printf("8) Baja logica\n");
    printf("9) Baja fisica\n");
    printf("11) Salir\n\n");
    printf("**********************************************\n\n");
    scanf("%i",&opcion);
    fflush(stdin);
     if((opcion<1)||(opcion>11)){
        crearMensajeError(1);
     }
    }while((opcion<1)||(opcion>11));

    return opcion;
}

//2. CREAR MENSAJE DE ERROR: Crea un mensaje al usuario de un valor ingresado NO válido.
void crearMensajeError(int num){
    switch(num){
        case 1: printf("\n \t\t ---- ERROR, INGRESE UN VALOR V%cLIDO POR FAVOR. ---- \n\n",181);
                break;
        case 2: printf("\n \t\t ---- ERROR EN LA APERTURA DEL ARCHIVO. ---- \n\n");
                break;
        case 3: printf("\n \t\t ---- ERROR AL CREAR ARCHIVO BINARIO. ---- \n\n");
                break;
        case 4: printf("\n \t\t ---- ERROR EN LA ESCRITURA DEL ARCHIVO BINARIO. ---- \n\n");
                break;
        case 5: printf("\n \t\t ---- ERROR EN LA LECTURA DEL ARCHIVO BINARIO. ---- \n\n");
                break;
        case 6: printf("\n \t\t ---- ERROR EN LOS TIEMPOS INGRESADOS. COMPRUEBE QUE EL TIEMPO M%cNIMO SEA MENOR AL TIEMPO M%cXIMO---- \n\n",214,181);
                break;
    }
}

//3. LEER ARCHIVO CSV CORREDORES: Lee el archivo csv y carga el array de strucs corredor definido al inicio del programa.
void leerArchivoCsv(FILE*pArchivo,char*nombreArchivo, struct corredor corredores[]){
    //Variables para cargar el struct.
    int orden,
        corredor,
        fechaDia,
        fechaAnio,
        edad,
        activo,
        i = 0;
    char pais[5],
         fechaMes[5],
         texto[200]; //Se usará para la función fgets();
    float tiempo;

    //Se abre el archivo y se lee. Es necesario que el archivo exista.
    pArchivo = fopen(nombreArchivo,"r");

    //Verificamos si el archivo de texto tiene datos.
    if(pArchivo != NULL){
        //Función fgets() lee una cadena de caracteres de un archivo y la almacena en la variable texto.
        fgets(texto,200,pArchivo);
        while(!feof(pArchivo)){
            //Extraemos los datos del archivo y se lo asignamos a las variables previamente definidas.
            extraerDatosCsv(texto,&orden,&corredor,&fechaDia,fechaMes,&fechaAnio,&edad,pais,&tiempo);
            corredores[i].orden = orden;
            corredores[i].corredor= corredor;
            corredores[i].dia=fechaDia;
            strcpy(corredores[i].mes,fechaMes);
            corredores[i].anio = fechaAnio;
            corredores[i].edad = edad;
            strcpy(corredores[i].pais, pais);
            corredores[i].tiempo = tiempo;
            corredores[i].activo = 1;
            i++;
            fgets(texto,200,pArchivo);
        }
        fclose(pArchivo);
    }else{
        crearMensajeError(2);
    }

}

//4. CONTAR CORREDORES CSV: Cuenta la cantidad de corredores o lineas del archivo csv y lo retorna.
int contarCorredoresCsv(FILE*archivo,char*nombreArchivo){
    int cantCorredores=0;
    char lineaTexto[200];
    archivo = fopen(nombreArchivo,"r");
    if(archivo != NULL){
    fgets(lineaTexto,200,archivo);
     while(!feof(archivo)){
        cantCorredores++;
        fgets(lineaTexto,200,archivo);
     }
     fclose(archivo);
   }else{
     crearMensajeError(2);
   }
    return cantCorredores;
}

//5. EXTRAER DATOS DEL ARCHIVO CSV: Extrae los datos del csv utilizando tokens y carga el array del struct de la función 3.
void extraerDatosCsv(char*texto,int*orden,int*corredor,int*fechaDia,char*fechaMes,int*fechaAnio,int*edad,char*pais,float*tiempo){

    char *cadOrden,
         *cadCorredor,
         *cadFechaDia,
         *cadFechaMes,
         *cadFechaAnio,
         *cadEdad,
         *cadPais,
         *cadTiempo;

    //Con la función strtok vamos a extraer los valores delimitados por caracteres especiales.
    cadOrden = strtok(texto,";");
    *orden = atoi(cadOrden);

    //El resto de las llamadas de utilza NULL en el primer parámetro. En cada llamada se retorna el siguiente texto delimitado.
    cadCorredor = strtok(NULL,";");
    *corredor = atoi(cadCorredor);//Atoi convierte el texto en entero.

    cadFechaDia = strtok(NULL,";");
    *fechaDia = atoi(cadFechaDia);

    cadFechaMes = strtok(NULL,";");
    strcpy(fechaMes,cadFechaMes); //strcpy copia el texto de la variable del segundo argumento y se lo asigna al primero.

    cadFechaAnio = strtok(NULL,";");
    *fechaAnio = atoi(cadFechaAnio);

    cadEdad = strtok(NULL,";");
    *edad = atoi(cadEdad);

    cadPais = strtok(NULL,";");
    strcpy(pais,cadPais);

    cadTiempo = strtok(NULL,";");
    *tiempo = atof(cadTiempo); //Atof convierte el texto en float.

}

//6. MOSTRAR DATOS CSV: Muestra los datos de los corredores (migrados del archivo csv al array de struc corredor).
void mostrarCorredoresCsv(struct corredor corredores[],int cantCorredores){
    int i;
    printf("\t\tORDEN\tCORREDOR\tDIA\tMES\tA%cO\tEDAD\tPAIS\tTIEMPO\n\n",165);
    for(i=0; i<cantCorredores;i++){
        printf("\t\t%d\t%d\t\t%d\t%s\t%d\t%d\t%s\t%.6f \n\n",corredores[i].orden,corredores[i].corredor,corredores[i].dia,corredores[i].mes,corredores[i].anio,corredores[i].edad,corredores[i].pais,corredores[i].tiempo);
    }
}

//7. CREAR ARCHIVO BINARIO: Crea un nuevo archivo binario, si ya existe uno, borrará el contenido.
void crearArchivoBinario(FILE*pArchivo, char*nombreArchivoBin){
    pArchivo = fopen(nombreArchivoBin,"wb");
    if(pArchivo!= NULL){
        printf("ARCHIVO \"%s\" CREADO",nombreArchivoBin);
    }else{
        crearMensajeError(3);
    }
    fclose(pArchivo);
}

//8. MIGRAR DATOS AL ARCHIVO BINARIO: A partir del struct(previamente cargado por el archivo Csv)se migra al archivo binario creado.
void migrarDatosArchivoBinario(FILE*pArchivo,char*nombreArchivoBinario,struct corredor corredores[],int cantCorredores){

    pArchivo = fopen(nombreArchivoBinario,"wb");

    //Con fwrite se escribe el archivo binario.
    //Primer argumento:dirección de memoria del array de struct.(datos que se desea escribir).
    //Segundo argumento: Definimos el tamaño para representar los datos a escribir.
    //Tercer argumento: indica la cantidad de elementos que se escribirán en el archivo binario.
    //Cuarto argumento: Direccion de memoria del archivo que se desea escribir.

    int total = fwrite(corredores, sizeof(struct corredor), cantCorredores, pArchivo);
     //La función fwrite retorna la cantidad de elementos escritos. Si es diferente a la cantidad de corredores, algo salió mal.
    if(total != cantCorredores){
        crearMensajeError(4);
    }else{
        printf("MIGRACI%cN EXITOSA AL ARCHIVO %s",224,nombreArchivoBinario);
    }
    fclose(pArchivo);

}

//9. MOSTRAR DATOS DEL ARCHIVO BINARIO
void mostrarDatosArchivoBinario(FILE*pArchivo,char*nombreArchivoBinario){

    //CORREGIR -> A PARTIR DE LA LECTURA DEL ARCHIVO, PUEDO SACAR LA CANTIDAD DE CORREDORES!CON EL MISMO PUEDO PONERLO DENTRO
    //DEL STRUCT.
    char opcion,*puntOpcion;
    puntOpcion = &opcion;
    struct corredor corredoresAux;
    int cantCorredores,i;
    pArchivo = fopen(nombreArchivoBinario,"rb");
    cantCorredores = contarCorredoresArchivoBinario(pArchivo,nombreArchivoBinario);


    do{
        crearSubMenuDatosArchivoBinario(puntOpcion);

        switch(opcion){
            case 'a':
                crearEncabezaTablaCorredores(1);
                i=0;
                while( i < cantCorredores ){
                    fseek(pArchivo,i*sizeof(struct corredor),SEEK_SET);
                    fread(&corredoresAux,sizeof(struct corredor),1,pArchivo);
                    listarCorredores(corredoresAux);
                    i++;
                }
                break;
            case 'b':
                crearEncabezaTablaCorredores(2);
                i=0;
                while( i < cantCorredores ){
                    fseek(pArchivo,i*sizeof(struct corredor),SEEK_SET);
                    fread(&corredoresAux,sizeof(struct corredor),1,pArchivo);
                    if( corredoresAux.activo == 1 ){
                       listarCorredores(corredoresAux);
                    }
                    i++;
                }
                break;
            case 'c':
                buscarPaisCorredores(pArchivo,corredoresAux,cantCorredores);
                break;

            case 'd':
                //CREAR FUNCION INGRESAR RANGO TIEMPO CON VALIDACIONES.
                ingresarRangoTiempo(pArchivo,corredoresAux, cantCorredores);
                break;

        }

    }while(tolower(opcion)!= 'x');

    fclose(pArchivo);
}

//10. CREAR SUBMENU: Crea un submenú para listar los datos de los archivos binarios.Toma como argumento un puntero.
void crearSubMenuDatosArchivoBinario(char *puntOpcion){
    char opcion;
    do{
        printf("\n\nSELECCIONAR OPCION:\n");
        printf("a) MOSTRAR TODOS LOS CORREDORES.\n");
        printf("b) MOSTRAR TODOS LOS CORREDORES ACTIVOS.\n");
        printf("c) MOSTRAR CORREDORES POR PAIS.\n");
        printf("d) MOSTRAR CORREDORES POR RANGO DE TIEMPO.\n\n");
        printf("x) VOLVER AL MENU PRINCIPAL.\n ");
        scanf("%c",&opcion);
        fflush(stdin);
        opcion = tolower(opcion);
        if( !((opcion == 'a')|| (opcion == 'b')||(opcion == 'c')||(opcion == 'd')||(opcion == 'x'))){
            crearMensajeError(1);
        }
    }while(!((opcion == 'a')|| (opcion == 'b')||(opcion == 'c')||(opcion == 'd')||(opcion == 'x')));

    //Se le asigna el valor ingresado, a la variable opción de la función 9.
   (*puntOpcion) = opcion;
}

//11. LISTAR CORREDORES: Utiliza la funcion printf()para mostrar los corredores. Toma como argumento un entero que representa el numero de corredor.
void listarCorredores(struct corredor corredoresAux){
    printf("\t%d\t%d\t\t%d\t%s\t%d\t%d\t%s\t%.6f\t%d\n",corredoresAux.orden,
                                                      corredoresAux.corredor,
                                                      corredoresAux.dia,
                                                      corredoresAux.mes,
                                                      corredoresAux.anio,
                                                      corredoresAux.edad,
                                                      corredoresAux.pais,
                                                      corredoresAux.tiempo,
                                                      corredoresAux.activo);
}

//12.CREAR ENCABEZADO DE TABLAS:Utiliza la función printf() para mostrar los encabezados de las tablas con los datos de los corredores de la función 9.
void crearEncabezaTablaCorredores(int num){
    switch(num){
        case 1: printf("\n\n\t\t----------- TABLA - TODOS LOS CORREDORES -------------\n\n");
                printf("\tORDEN\tCORREDOR\tDIA\tMES\tA%cO\tEDAD\tPAIS\tTIEMPO\t\tACTIVO\n",165);
                break;
        case 2: printf("\n\n\t----------- TABLA - CORREDORES ACTIVOS -------------\n\n");
                printf("\tORDEN\tCORREDOR\tDIA\tMES\tA%cO\tEDAD\tPAIS\tTIEMPO\t\tACTIVO\n",165);
                break;
        case 3: printf("\n\n\t\t----------- TABLA - CORREDORES POR PAIS: -------------\n\n");
                printf("\tORDEN\tCORREDOR\tDIA\tMES\tA%cO\tEDAD\tPAIS\tTIEMPO\t\tACTIVO\n",165);
                break;
        case 4: printf("\n\n\t\t----------- TABLA - CORREDORES POR RANGO DE TIEMPO: --------------\n\n");
                printf("\tORDEN\tCORREDOR\tDIA\tMES\tA%cO\tEDAD\tPAIS\tTIEMPO\t\tACTIVO\n",165);
                break;
    }
}

//13. BUSCAR PAIS: Se ingresa el dato del pais para la función 9 con sus respectivas validaciones.
void buscarPaisCorredores(FILE*pArchivo, struct corredor corredoresAux,int cantCorredores){
    char pais[4];
    printf("\n\t INGRESE PAIS: \t");
    fgets(pais,4,stdin);
    fflush(stdin);
    convertirStrMayuscula(pais);
    int encontrado = 0, i=0;
    crearEncabezaTablaCorredores(3);
     while( i < cantCorredores ){
        fseek(pArchivo,i*sizeof(struct corredor),SEEK_SET);
        fread(&corredoresAux,sizeof(struct corredor),1,pArchivo);
        if( strcmp( pais, corredoresAux.pais) == 0 ){
            listarCorredores(corredoresAux);
            encontrado = 1;
        }
        i++;
    }
    if( encontrado == 0){
        crearMensajeError(1);
    }
}

//14. INGRESAR RANGO TIEMPO: Se ingresa un rango de tiempo para la función 9 con sus respectivas validaciones.
void ingresarRangoTiempo(FILE*pArchivo, struct corredor corredoresAux,int cantCorredores){
     float tiempoMax,tiempoMin;
     int i;
     do{
        printf("INGRESE UN RANGO DE TIEMPO\n\n");
        printf("TIEMPO M%cNIMO:\t",214);
        scanf("%f",&tiempoMin);
        fflush(stdin);
        printf("TIEMPO M%XIMO:\t",181);
        scanf("%f",&tiempoMax);
        fflush(stdin);

        if(tiempoMin>tiempoMax){
            crearMensajeError(6);
        }
    }while(tiempoMin>tiempoMax);

    crearEncabezaTablaCorredores(4);
    i=0;
    while( i < cantCorredores ){
       fseek(pArchivo,i*sizeof(struct corredor),SEEK_SET);
       fread(&corredoresAux,sizeof(struct corredor),1,pArchivo);
       if( corredoresAux.tiempo>=tiempoMin && corredoresAux.tiempo<=tiempoMax ){
          listarCorredores(corredoresAux);
        }
       i++;
    }

}

//15. CARGAR NUEVOS CORREDORES AL ARCHIVO BINARIO: Permite escribir el archivo binario, agregando un corredor nuevo por el usuario.
void cargarNuevoCorredor(FILE*pArchivo,char*nombreArchivoBinario,struct fecha fechaActual){
    struct corredor nuevoCorredor;
    struct corredor * pNuevoCorredor;
    pNuevoCorredor = &nuevoCorredor;

    int cantCorredores;

    pArchivo = fopen(nombreArchivoBinario,"r+b");

    cantCorredores = contarCorredoresArchivoBinario(pArchivo,nombreArchivoBinario);
    printf("\nCANTIDAD ACTUAL DE CORREDORES %d\n",cantCorredores);

    for( int i=1; i<10;i++){
      validarDatosNuevoCorredor(i,pNuevoCorredor,cantCorredores, fechaActual,pArchivo, nombreArchivoBinario);
    }



    //Corroborar datos ingresados.

    printf("\n\nDATOS INGRESADOS:\n");
    printf("\t\tORDEN\tCORREDOR\tDIA\tMES\tA%cO\tEDAD\tPAIS\tTIEMPO\n\n",165);
    printf("\t%d\t%d\t%d\t%s\t%d\t%d\t%s\t%.6f\t%d\n",nuevoCorredor.orden,nuevoCorredor.corredor,nuevoCorredor.dia,nuevoCorredor.mes,nuevoCorredor.anio,nuevoCorredor.edad,nuevoCorredor.pais,nuevoCorredor.tiempo,nuevoCorredor.activo);

        //Muevo cursor del principio a la posicion de orden ingresado
        fseek(pArchivo,(nuevoCorredor.orden-1)*sizeof(struct corredor),SEEK_SET);
        fwrite(&nuevoCorredor, sizeof(struct corredor),1,pArchivo);
        rewind(pArchivo);

    cantCorredores = contarCorredoresArchivoBinario(pArchivo,nombreArchivoBinario);
    printf("\nCANTIDAD ACTUALIZADO DE CORREDORES %d\n",cantCorredores);
    fclose(pArchivo);


}

//16. CONTAR CANTIDAD DE CORREDORES ARCHIVO BINARIO:
int contarCorredoresArchivoBinario(FILE*pArchivo,char*nombreArchivoBinario){
    int cantCorredores;
    fseek(pArchivo,0,SEEK_END);
    cantCorredores = ftell(pArchivo)/sizeof(struct corredor);
    rewind(pArchivo);
    return cantCorredores;
}

//17. VALIDAR ENTRADA DE DATOS DE LA FUNCIÓN 15.
//*****AGREGAR MENSAJES DE ERROR******//
void validarDatosNuevoCorredor(int num, struct corredor * pNuevoCorredor,int cantCorredores,struct fecha fechaActual,FILE*pArchivo,char*nombreArchivoBinario){
    int dia = fechaActual.dia,
        mes = fechaActual.mes,
        anio = fechaActual.anio,
        encontrado = 0,
        ordenIngresado;
    struct corredor corredorLeido;

    char meses[][12] = {"ENE","FEB","MAR","ABR","MAY","JUN","JUL","AGO","SEP","OCT","NOV","DIC"};
    char paises[][4] = {"ARG","PER","MEX","BRA"}; //Se pueden agregar más paises de otro archivo.
    switch(num){
        //Validar orden
        case 1:
            do{
                printf("INGRESAR ORDEN:\n");
                scanf("%d",&ordenIngresado);
                fflush(stdin);
                //Con el cursor vamos a la posición de orden ingresada.
                if(fseek(pArchivo,((ordenIngresado)- 1)*sizeof(struct corredor),SEEK_SET) == 0){
                   //Leemos esa linea.
                   fread(&corredorLeido, sizeof(struct corredor),1,pArchivo);
                    if( corredorLeido.orden == 0 || corredorLeido.orden != ordenIngresado){
                        pNuevoCorredor->orden = ordenIngresado;
                    }else{
                        crearMensajeError(1);
                    }
                };


            }while(!(corredorLeido.orden == 0 || corredorLeido.orden != ordenIngresado));
            break;
        //Validad corredor
        case 2:
            do{
               printf("INGRESAR CORREDOR:\n");
               scanf("%d",&pNuevoCorredor->corredor);
               fflush(stdin);
            }while( pNuevoCorredor->corredor<0 );
            break;
        case 3:
        //Validar año
            do{
               printf("INGRESAR A%cO:\n",165);
               scanf("%d",&pNuevoCorredor->anio);
               fflush(stdin);
            }while(((pNuevoCorredor->anio) <= 1900)||((pNuevoCorredor->anio)>anio));
            break;
        case 4:
        //Validar mes
            do{
                printf("INGRESAR MES (ejemplo: abril o abr):\n");
                fgets(&pNuevoCorredor->mes,4,stdin);
                fflush(stdin);
                convertirStrMayuscula(&pNuevoCorredor->mes);
                for(int i=0; i<12;i++){
                    if( strcmp(pNuevoCorredor->mes, meses[i]) == 0){
                        encontrado = 1;
                    }
                }
            }while(encontrado!=1);
            break;
        //Validar dia.
        case 5:
                //- Año natural = 365 días, con meses de 30 o 31 días y febrero con 28 días.
                //- Año bisiesto = 366 días, con meses de 30 o 31 días  y febrero con 29 días.

                //Año bisiesto con febrero con 29 dias.
                if(esAnioBisiesto(pNuevoCorredor->anio) && (strcmp(pNuevoCorredor->mes,meses[3])==0)){
                    do{
                        printf("INGRESAR DIA:\n");
                        scanf("%d",&pNuevoCorredor->dia);
                        fflush(stdin);
                    }while((pNuevoCorredor->dia>30)|| (pNuevoCorredor->dia<0));
                //Año bisiesto con meses de 30 dias.
                }else if((esAnioBisiesto(pNuevoCorredor->anio) && (strcmp(pNuevoCorredor->mes,meses[3])==0)||
                                                                  (strcmp(pNuevoCorredor->mes,meses[5])==0)||
                                                                  (strcmp(pNuevoCorredor->mes,meses[8])==0)||
                                                                  (strcmp(pNuevoCorredor->mes,meses[3])==0))){
                    do{
                        printf("INGRESAR DIA:\n");
                        scanf("%d",&pNuevoCorredor->dia);
                        fflush(stdin);
                    }while((pNuevoCorredor->dia>31)||(pNuevoCorredor->dia<0));
                //Año bisiesto con meses de 31 dias.
                }else if((esAnioBisiesto(pNuevoCorredor->anio) && (strcmp(pNuevoCorredor->mes,meses[0])==0)||
                                                                  (strcmp(pNuevoCorredor->mes,meses[2])==0)||
                                                                  (strcmp(pNuevoCorredor->mes,meses[4])==0)||
                                                                  (strcmp(pNuevoCorredor->mes,meses[6])==0)||
                                                                  (strcmp(pNuevoCorredor->mes,meses[7])==0)||
                                                                  (strcmp(pNuevoCorredor->mes,meses[9])==0)||
                                                                  (strcmp(pNuevoCorredor->mes,meses[10])==0) )){
                    do{
                        printf("INGRESAR DIA:\n");
                        scanf("%d",&pNuevoCorredor->dia);
                        fflush(stdin);
                    }while((pNuevoCorredor->dia>32)||(pNuevoCorredor->dia<0));
                    //Año normal con febrero de 28 dias.
                 }else if( (strcmp(pNuevoCorredor->mes,meses[3])==0) ){
                     do{
                         printf("INGRESAR DIA:\n");
                         scanf("%d",&pNuevoCorredor->dia);
                         fflush(stdin);
                     }while((pNuevoCorredor->dia>29)||(pNuevoCorredor->dia<0));
                    //Año normal con 30 dias
                 }else if( (strcmp(pNuevoCorredor->mes,meses[3])==0)||
                           (strcmp(pNuevoCorredor->mes,meses[5])==0)||
                           (strcmp(pNuevoCorredor->mes,meses[8])==0)||
                           (strcmp(pNuevoCorredor->mes,meses[3])==0)){
                     do{
                        printf("INGRESAR DIA:\n");
                        scanf("%d",&pNuevoCorredor->dia);
                        fflush(stdin);
                     }while((pNuevoCorredor->dia>31)||(pNuevoCorredor->dia<0));
                   //Año normal con 31 dias.
                 }else{
                     do{
                        printf("INGRESAR DIA:\n");
                        scanf("%d",&pNuevoCorredor->dia);
                        fflush(stdin);
                     }while((pNuevoCorredor->dia>32)||(pNuevoCorredor->dia<0));

                 }
            break;
        //Validar pais
        case 6:
             do{
                printf("INGRESAR PAIS:\n");
                printf("Por este momento puede elegir entre ARG, PER, BRA, MEX\n");
                fgets(&pNuevoCorredor->pais,4,stdin);
                fflush(stdin);
                //Recorro array de paises
                convertirStrMayuscula(&pNuevoCorredor->pais);
                encontrado = 0;
                for(int i=0; i<4;i++){
                    if( strcmp(pNuevoCorredor->pais, paises[i]) == 0){
                        encontrado = 1;
                    }
                }
             }while(encontrado != 1);
             break;
        //Validar edad
        case 7:
            do{
                printf("INGRESAR EDAD:\n");
                scanf("%d",&pNuevoCorredor->edad);
                fflush(stdin);

            }while(pNuevoCorredor->edad<17 || pNuevoCorredor->edad>105);
            break;

        //Validar tiempo.
        case 8:
            do{
                printf("INGRESAR TIEMPO:\n");
                scanf("%f",&pNuevoCorredor->tiempo);
                fflush(stdin);
            }while(pNuevoCorredor->tiempo < 0);
            break;

        //AGREGAR ACTIVO POR DEFECTO.
        case 9:
            pNuevoCorredor->activo = 1;
            break;

    }}

//18. OBTENER HORA ACTUAL: Carga el struc de fecha con los datos del dia actual.
void obtenerFechaActual(struct fecha * pFecha){
    time_t segHoy = time(NULL); //Retorna los segundos desde 1970 (medianoche) hasta el dia de hoy.

    struct tm*hoy = localtime(&segHoy); //Función localtime() retorna un struct con los valores que nos interesan.

    pFecha->dia = (hoy->tm_mday);
    pFecha->mes = hoy->tm_mon+1;
    pFecha->anio = hoy->tm_year+1900;


}

//19. CONVERTIR STRINGS EN MAYUCULAS. Recorre los caracteres del string y los pasa a mayucula.
void convertirStrMayuscula(char*string){
    for (int indice = 0; string[indice] != '\0'; ++string){
		string[indice] = toupper(string[indice]);
	}
}

//20. DETERMINAR AÑO BISIESTO: Retorna 1 si el año es bisiesto, de lo contrario 0.
int esAnioBisiesto(int anio){
    //Son bisiestos todos los años múltiplos de 4, excepto aquellos que son múltiplos de 100 pero no de 400.
    if( (anio%4==0 && anio%100!=0) || (anio%400==0) ){
        return 1;
    }
    return 0;

}

//21. BUSCAR COMPETIDOR POR NUMERO DE ORDEN O  POR NUMERO DE CORREDOR.
//Buscar datos por competidor
void buscarDatosCompetidores(FILE*pArchivo,char*nombreArchivoBinario){
    char opcion;
     pArchivo = fopen(nombreArchivoBinario, "rb");
    do{
        printf("\n\nIngrese una opcion de busqueda:\n\n");
        printf("e)Buscar por numero de orden.\n");
        printf("f)Buscar por numero de corredor.\n");
        printf("x)volver \n");
        scanf("%c",&opcion);
        fflush(stdin);
        opcion = tolower(opcion);
        if(!(opcion =='e'|| opcion == 'f'|| opcion == 'x')){
            crearMensajeError(1);
        }else{
            buscarPorOrden_Corredor(pArchivo,nombreArchivoBinario,opcion);
        }

    }while(!(opcion=='x'));

    fclose(pArchivo);

}

//22. BUSQUEDA DE COMPETIDORES PARA FUNCIÓN 21.
void buscarPorOrden_Corredor(FILE*pArchivo, char*nombreArchivoBinario,char opcion){
    int cantCorredores,i;
    struct corredor corredores;
    int numOrden,numCorredor,encontrado=0;
    //Abro archivo binario.
    switch(opcion){
        case 'e':
            //FUNCIONA PERO AL INGRESAR UN CARACTER NO LANZA EL MENSAJE DE ERROR.
                  do{
                   printf("Ingrese numero de orden o (-1 para volver):\n");
                   scanf("%d",&numOrden);
                   fflush(stdin);
                   cantCorredores = contarCorredoresArchivoBinario(pArchivo,nombreArchivoBinario);
                    i=0;
                    while( i < cantCorredores ){
                        fseek(pArchivo,i*sizeof(struct corredor),SEEK_SET);
                        fread(&corredores,sizeof(struct corredor),1,pArchivo);
                        if( corredores.orden == numOrden){
                           listarCorredores(corredores);
                           encontrado++;
                        }
                        i++;
                    }
                    if((encontrado == 0) && (!isdigit(numOrden))){
                        crearMensajeError(1);
                    }
                }while(numOrden != -1 );
                break;



        case 'f':
            //FUNCIONA PERO AL INGRESAR UN CARACTER NO LANZA EL MENSAJE DE ERROR E IMPRIME EL VALOR ANTERIOR.
                do{
                   printf("Ingrese numero de corredor o (-1 para volver):\n");
                   scanf("%d",&numCorredor);
                   fflush(stdin);
                   cantCorredores = contarCorredoresArchivoBinario(pArchivo,nombreArchivoBinario);
                    i=0;
                    while( i < cantCorredores ){
                        fseek(pArchivo,i*sizeof(struct corredor),SEEK_SET);
                        fread(&corredores,sizeof(struct corredor),1,pArchivo);
                        if( corredores.corredor == numCorredor ){
                           listarCorredores(corredores);
                           encontrado++;
                        }
                        i++;
                    }
                    if(encontrado == 0){
                        crearMensajeError(1);
                    }
                }while(numCorredor != -1);
                break;
    }
}

//23. MODIFICAR DATOS DEL COMPETIDOR.
void modificarDatosCorredor(FILE*pArchivo,char*nombreArchivoBinario){
    struct corredor corredores;
    char opcion;
    float tiempo;
    int edad,nroOrden,encontrado;

    pArchivo = fopen(nombreArchivoBinario,"r+b");
    do{
        printf("\nSeleccionar dato que desea modificar:\n\n");
        printf("g) Modificar edad:\n");
        printf("h) Modificar tiempo:\n");
        printf("x) volver.\n");
        scanf("%c",&opcion);
        opcion = tolower(opcion);
        fflush(stdin);
        if( !(opcion == 'g' || opcion == 'h' || opcion == 'x') ){
            crearMensajeError(1);
        }
    }while(!(opcion == 'g' || opcion == 'h' || opcion == 'x') );


    switch(opcion){
        case 'g':
                 //VALIDAR NUMERO DE ORDEN CON FSEEK.
                 printf("Ingrese el numero de orden del corredor:\n");
                 scanf("%d",&nroOrden);
                 fflush(stdin);
                 encontrado = 0;
                 while(!feof(pArchivo)){
                    if(fread(&corredores, sizeof( struct corredor), 1, pArchivo) == 1){
                        if(corredores.orden == nroOrden){
                            printf("CORREDOR ENCONTRADO\n");
                            listarCorredores(corredores);
                            encontrado++;
                            do{
                                printf("\n%cEst%c seguro que desea modificar los datos(s/n)?\n",168,160);
                                scanf("%c",&opcion);
                                fflush(stdin);
                                opcion = tolower(opcion);
                                if( !(opcion =='s' || opcion =='n') ){
                                    crearMensajeError(1);
                                }
                            }while(!(opcion =='s' || opcion =='n'));
                            //VALIDAR EDAD
                            if(opcion == 's'){
                                printf("INGRESE EDAD\n");
                                scanf("%d",&edad);
                                fflush(stdin);
                                corredores.edad = edad;
                                fseek(pArchivo,-sizeof(struct corredor),SEEK_CUR);
                                fwrite(&corredores, sizeof(struct corredor),1,pArchivo);
                                fflush(pArchivo);
                                printf("CAMBIO DE EDAD EXITOSO\n");
                                listarCorredores(corredores);
                            }
                        }
                    }

                 }
                 if(encontrado == 0){
                    printf("\nCORREDOR NO ENCONTRADO\n");
                 }
                 break;

        case 'h':
                //VALIDAR NRO DE CORREDOR.
                 printf("Ingrese el numero de orden del corredor:\n");
                 scanf("%d",&nroOrden);
                 fflush(stdin);
                 encontrado = 0;
                 while(!feof(pArchivo)){
                    if(fread(&corredores, sizeof( struct corredor), 1, pArchivo) == 1){
                        if(corredores.orden == nroOrden){
                            printf("CORREDOR ENCONTRADO\n");
                            listarCorredores(corredores);
                            encontrado++;
                            do{
                                printf("\n%cEst%c seguro que desea modificar los datos(s/n)?\n",168,160);
                                scanf("%c",&opcion);
                                fflush(stdin);
                                opcion = tolower(opcion);
                                if( !(opcion =='s' || opcion =='n') ){
                                    crearMensajeError(1);
                                }
                            }while(!(opcion =='s' || opcion =='n'));

                            if(opcion == 's'){
                            printf("INGRESE TIEMPO\n");
                            scanf("%f",&tiempo);
                            fflush(stdin);
                            corredores.tiempo = tiempo;
                            fseek(pArchivo,-sizeof(struct corredor),SEEK_CUR);
                            fwrite(&corredores, sizeof(struct corredor),1,pArchivo);
                            fflush(pArchivo);
                            printf("CAMBIO DE EDAD EXITOSO\n");
                            listarCorredores(corredores);
                            }
                        }
                    }

                 }
                 if(encontrado == 0){
                    printf("\nCORREDOR NO ENCONTRADO\n\n");
                 }
                 break;
    }
    fclose(pArchivo);
}

//24. BAJA LOGICA DE UN CORREDOR EN ESPECIFICO - ACTIVO PASA A SER 0.
void bajaLogicaDelCorredor(FILE*pArchivo,char*nombreArchivoBinario){

    struct corredor corredores;
    int nroOrden;
    char opcion;
    pArchivo = fopen(nombreArchivoBinario,"r+b");
    //VALIDAR ORDEN.
    printf("Ingrese numero de orden\n");
    scanf("%d",&nroOrden);
    fflush(stdin);
    //Nos colocamos al incicio del archivo.
    fseek(pArchivo,0,SEEK_SET);
    //Vamos al lugar del corredor que nos interesa.
    fseek(pArchivo,(nroOrden-1)*sizeof(struct corredor),SEEK_SET);
    //Como hice un fread el cursor fue una posición adelante.
    fread(&corredores, sizeof(struct corredor),1,pArchivo);
    printf("USTED DAR%c DE BAJA AL SIGUENTE CORREDOR:\n\n",181);
    listarCorredores(corredores);

    do{
        printf("\n%cEst%c seguro que desea realizar esta operacion(s/n)?\n",168,160);
        scanf("%c",&opcion);
        fflush(stdin);
        opcion = tolower(opcion);
        if( !(opcion =='s' || opcion =='n') ){
            crearMensajeError(1);
        }
    }while(!(opcion =='s' || opcion =='n'));

    if( opcion == 's'){
        //Vuelvo a la posción del corredor que me interesa.
        fseek(pArchivo, -sizeof(struct corredor), SEEK_CUR);
        corredores.activo = 0;
        fwrite(&corredores, sizeof(struct corredor), 1, pArchivo);
        printf("BAJA EXITOSA.");
    }
    fclose(pArchivo);

}

//25. BAJA FISICA - ELIMANAMOS AL CORREDOR.
void bajaFisicaDelCorredor(FILE*pArchivo,char*nombreArchivoBinario){

    struct corredor corredores;
    FILE * pArchivo2;
    FILE * pArchivoTemp;
    char nombreArchivoBin2[50] = "competidores_baja.data",opcion;


    pArchivo = fopen(nombreArchivoBinario,"rb");
    pArchivo2 = fopen(nombreArchivoBin2,"w+b");
    pArchivoTemp = fopen("archivoTemporal.data","w+b");

    do{
         printf("\n%cEst%c seguro que desea realizar la baja fisica (s/n)?\n",168,160);
         scanf("%c",&opcion);
         fflush(stdin);
         opcion = tolower(opcion);
         if( !(opcion =='s' || opcion =='n') ){
              crearMensajeError(1);
        }
    }while(!(opcion =='s' || opcion =='n'));

    if(opcion == 's'){
        while( fread(&corredores, sizeof(struct corredor),1, pArchivo) == 1){
            //Escribo todos los corredores inactivos al archivo binario nuevo.
            if(corredores.activo == 0 && corredores.orden!=0){
                 fwrite(&corredores,sizeof(struct corredor),1,pArchivo2);
            }
            //Escribo todos los corredores activos al archivo temporal.
            if( corredores.activo == 1){
                fwrite(&corredores,sizeof(struct corredor),1,pArchivoTemp);
            }
          }
        fclose(pArchivo);
        fclose(pArchivo2);
        fclose(pArchivoTemp);
        //Borro archivo binario viejo(original)
        remove(nombreArchivoBinario);
        //Renombro el archivo temporal con los corredores activos con el nombre
        //del archivo original.
        rename("archivoTemporal.data",nombreArchivoBinario);
        //Borro archivo binario temporal.
        remove("archivoTemporal.data");

        printf("\nBAJA FISICA EXITOSA\n\n");
        mostrarBajasFisicas(nombreArchivoBin2);

    }else{
        fclose(pArchivo);
        fclose(pArchivo2);
        fclose(pArchivoTemp);
    }


}

//26. MOSTRAR BAJAS FISICA.
void mostrarBajasFisicas(char*nombreArchivoBin2){

    //FALTO COLOCAR FECHA AL ARCHIVO BINARIO DE CORRESDESBAJA.
    struct corredor corredores;
    int cantCorredores,i = 0;
    FILE*pArchivo2;

    pArchivo2 = fopen(nombreArchivoBin2,"rb");
    cantCorredores = contarCorredoresArchivoBinario(pArchivo2,nombreArchivoBin2);

    while( i < cantCorredores ){
       fseek(pArchivo2,i*sizeof(struct corredor),SEEK_SET);
       fread(&corredores,sizeof(struct corredor),1,pArchivo2);
       listarCorredores(corredores);
       i++;
    }
    fclose(pArchivo2);

}
int main()
{
    FILE*pArchivo;
    char nombreArchivo[30] = "corredores_v1.csv",
         nombreArchivoBinario[30] = "corredores.data";
    int opcion,
        cantCorredores;
    struct fecha fechaActual;
    struct fecha * pFecha;
    pFecha = &fechaActual;

    //Cargamos el struct con la fecha actual, es importante mandar un puntero del struct para modificar los campos.
    obtenerFechaActual(pFecha);


    /*De la función contarCorredoresCsv() se va obtener la cantidad de corredores
    del archivo csv y se creara un array con esa dimension.*/
    cantCorredores = contarCorredoresCsv(pArchivo,nombreArchivo);
    struct corredor corredores[cantCorredores];

    do{
        opcion = crearMenuPrincipal();
        switch(opcion){
            case 1:
                leerArchivoCsv(pArchivo, nombreArchivo, corredores);
                mostrarCorredoresCsv(corredores, cantCorredores);
                break;
            case 2:
                leerArchivoCsv(pArchivo, nombreArchivo, corredores);
                crearArchivoBinario(pArchivo, nombreArchivoBinario);
                break;
            case 3:
                migrarDatosArchivoBinario(pArchivo, nombreArchivoBinario, corredores,cantCorredores);
                break;
            case 4:
                mostrarDatosArchivoBinario(pArchivo,nombreArchivoBinario);
                break;
            case 5:
                cargarNuevoCorredor(pArchivo,nombreArchivoBinario,fechaActual);
                break;
            case 6:
                buscarDatosCompetidores(pArchivo,nombreArchivoBinario);
                break;
            case 7:
                modificarDatosCorredor(pArchivo,nombreArchivoBinario);
                break;
            case 8:
                bajaLogicaDelCorredor(pArchivo, nombreArchivoBinario);
                break;
            case 9:
                bajaFisicaDelCorredor(pArchivo,nombreArchivoBinario);
                break;
        }
    }while(opcion!=11);
    return 0;
}
