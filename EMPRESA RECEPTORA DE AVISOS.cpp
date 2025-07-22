/* Una empresa receptora de avisos clasificados tiene oficinas en 5 localidades y opera con 3 rubros. 
El c�digo de los rubros como sus precios se conoce.

Cada vez que una agencia vende la publicaci�n de UN AVISO se registran los siguientes datos: 

� Nro. de recepci�n del aviso 
� Nro. de la agencia (nro correlativo de 1 a 5) 
� C�digo del rubro (nro. de 3 cifras) 
� Cantidad de l�neas publicadas 

La carga de datos finaliza con N�MERO DE RECEPCION IGUAL A CERO. 

Se sabe que si el aviso excede las 5 l�neas se aplica un recargo del 2% sobre el importe del aviso. 
Una vez al mes se procesan los datos y se pide informar: 

1. Cantidad total de avisos publicados por cada agencia . 
2. Para cada agencia el c�digo del rubro que tuvo la mayor recaudaci�n . 
3. Porcentaje que le corresponde a cada agencia sobre el total de avisos publicados 
4. Recaudaci�n de la agencia 1 para cada rubro.
*/

#include <stdio.h>

void CARGAR_OFI(int[], int);
void CARGAR_RUBROS(int[], float[], int);
int VALIDAR(int, int);
int BUSQUEDA(int[], int, int);

int main() {
    int oficinas[5], rubros[3];
    float precios[3];
    int nro_rep, agencia, rubro, POS, pos_rubro, cant_lineas;
    float importe;

    int cant_avisos[5] = {0};         // Cantidad de avisos por agencia
    float recaudacion[5][3] = {0};    // Recaudaci�n por agencia y rubro

    printf("\n---------------- Cargar n�meros de agencias ----------------");
    CARGAR_OFI(oficinas, 5);

    printf("\n---------------- Cargar c�digos de rubros y precios ----------------");
    CARGAR_RUBROS(rubros, precios, 3);

    printf("\n\nIngrese n�mero de recepci�n del aviso (0 para terminar): ");
    scanf("%d", &nro_rep);

    while (nro_rep != 0) {
        printf("\nN�mero de recepci�n: %d", nro_rep);

        printf("\nIngrese n�mero de agencia (1 a 5): ");
        agencia = VALIDAR(1, 5);
        POS = BUSQUEDA(oficinas, agencia, 5);

        if (POS >= 0) {
            printf("\nIngrese c�digo del rubro (3 cifras): ");
            rubro = VALIDAR(100, 999);
            pos_rubro = BUSQUEDA(rubros, rubro, 3);

            if (pos_rubro >= 0) {
                printf("\nIngrese cantidad de l�neas publicadas: ");
                scanf("%d", &cant_lineas);

                importe = precios[pos_rubro] * cant_lineas;

                if (cant_lineas > 5) {
                    importe *= 1.02; // recargo del 2%
                }

                cant_avisos[POS]++;
                recaudacion[POS][pos_rubro] += importe;
            } else {
                printf("\n?? Rubro no encontrado.\n");
            }
        } else {
            printf("\n?? Agencia no encontrada.\n");
        }

        printf("\n\nIngrese n�mero de recepci�n del aviso (0 para terminar): ");
        scanf("%d", &nro_rep);
    }

    // -----------------------------------------------
    // INFORMES
    // -----------------------------------------------
    int i, j, total_avisos = 0, max_rubro;
    float max_recaudacion;

    printf("\n\n********* INFORMES *********\n");

    // 1. Cantidad total de avisos por agencia
    printf("\n1. Cantidad total de avisos por agencia:");
    for (i = 0; i < 5; i++) {
        printf("\nAgencia %d: %d avisos", oficinas[i], cant_avisos[i]);
        total_avisos += cant_avisos[i];
    }

    // 2. C�digo del rubro con mayor recaudaci�n por agencia
    printf("\n\n2. C�digo del rubro con mayor recaudaci�n por agencia:");
    for (i = 0; i < 5; i++) {
        max_recaudacion = recaudacion[i][0];
        max_rubro = rubros[0];
        for (j = 1; j < 3; j++) {
            if (recaudacion[i][j] > max_recaudacion) {
                max_recaudacion = recaudacion[i][j];
                max_rubro = rubros[j];
            }
        }
        printf("\nAgencia %d: Rubro %d", oficinas[i], max_rubro);
    }

    // 3. Porcentaje de avisos por agencia
    printf("\n\n3. Porcentaje de avisos por agencia:");
    for (i = 0; i < 5; i++) {
        if (total_avisos > 0) {
            float porcentaje = (cant_avisos[i] * 100.0) / total_avisos;
            printf("\nAgencia %d: %.2f%%", oficinas[i], porcentaje);
        } else {
            printf("\nAgencia %d: 0.00%%", oficinas[i]);
        }
    }

    // 4. Recaudaci�n de la agencia 1 por cada rubro
    printf("\n\n4. Recaudaci�n de la agencia 1 por cada rubro:");
    int pos_ag1 = BUSQUEDA(oficinas, 1, 5);
    if (pos_ag1 >= 0) {
        for (j = 0; j < 3; j++) {
            printf("\nRubro %d: $%.2f", rubros[j], recaudacion[pos_ag1][j]);
        }
    } else {
        printf("\nLa agencia 1 no fue cargada.");
    }

    return 0;
}

// -----------------------------------------------
// Carga de agencias (n�meros entre 1 y 5)
// -----------------------------------------------
void CARGAR_OFI(int agencias[], int cantidad) {
    int i;
    for (i = 0; i < cantidad; i++) {
        printf("\nAgencia N�%d: ", i + 1);
        agencias[i] = VALIDAR(1, 5);
    }
}

// -----------------------------------------------
// Carga de rubros y precios
// -----------------------------------------------
void CARGAR_RUBROS(int rubros[], float precios[], int cantidad) {
    int i;
    for (i = 0; i < cantidad; i++) {
        printf("\nRubro N�%d (c�digo de 3 cifras): ", i + 1);
        rubros[i] = VALIDAR(100, 999);
        printf("Precio por l�nea: ");
        scanf("%f", &precios[i]);
    }
}

// -----------------------------------------------
// Validar n�mero dentro de un rango
// -----------------------------------------------
int VALIDAR(int desde, int hasta) {
    int dato;
    do {
        scanf("%d", &dato);
        if (dato < desde || dato > hasta) {
            printf("Error. Ingrese un n�mero entre %d y %d: ", desde, hasta);
        }
    } while (dato < desde || dato > hasta);
    return dato;
}

// -----------------------------------------------
// Buscar un valor en un vector y devolver su posici�n
// -----------------------------------------------
int BUSQUEDA(int vec[], int clave, int cantidad) {
    int i = 0, pos = -1;
    while (i < cantidad && pos == -1) {
        if (vec[i] == clave) {
            pos = i;
        }
        i++;
    }
    return pos;
}
