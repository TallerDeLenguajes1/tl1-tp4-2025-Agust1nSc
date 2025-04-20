#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char *TiposProductos[] = {"Galletas", "Snack", "Cigarrillos", "Caramelos", "Bebidas"};

struct Tarea
{
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} typedef Tarea;

struct Nodo
{

    Tarea T;
    struct Nodo *Siguiente;

} typedef Nodo;

struct Producto
{
    int ProductoID;       // Numerado en ciclo iterativo
    int Cantidad;         // entre 1 y 10
    char *TipoProducto;   // Algún valor del arreglo TiposProductos
    float PrecioUnitario; // entre 10 - 100
} typedef Producto;

struct Cliente
{
    int ClienteID;               // Numerado en el ciclo iterativo
    char *NombreCliente;         // Ingresado por usuario
    int CantidadProductosAPedir; // (aleatorio entre 1 y 5)
    Producto *Productos;         // El tamaño de este arreglo depende de la variable
    // “CantidadProductosAPedir”
} typedef Clientes;

float CostoTotalDeUnProducto();
Nodo *CrearListaVacia();
void *CrearTarea(Nodo **lista, int *idActual);
void MostrarLista(Nodo *lista);
void TransferirTarea(Nodo **pendientes, Nodo **realizadas);
void MarcarTareaComoRealizada(Nodo **pendientes, Nodo **realizadas, int id);
void ConsultarTarea(Nodo *pendientes, Nodo *realizadas);
void LiberarMemoria(Nodo *lista);

int main()
{

    int cantClientes;
    float totalGalletas = 0;
    float totalSnack = 0;
    float totalCigarrillos = 0;
    float totalCaramelos = 0;
    float totalBebidas = 0;
    int idActual = 1000;
    int opcion;

    srand(time(NULL));

    Nodo *pendientes = CrearListaVacia();
    Nodo *realizadas = CrearListaVacia();

    do
    {
        printf("\nMenu:\n");
        printf("1. Agregar tarea\n");
        printf("2. Ver tareas pendientes\n");
        printf("3. Ver tareas realizadas\n");
        printf("4. Marcar tarea como realizada\n");
        printf("5. Consultar tarea por ID o palabra clave\n");
        printf("0. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        fflush(stdin); // Limpiar el buffer de entrada

        switch (opcion)
        {
        case 1:
            CrearTarea(&pendientes, &idActual);
            break;
        case 2:
            printf("Tareas pendientes:\n");
            MostrarLista(pendientes);
            break;
        case 3:
            printf("Tareas realizadas:\n");
            MostrarLista(realizadas);
            break;
        case 4:
            TransferirTarea(&pendientes, &realizadas);
            break;
        case 5:
            ConsultarTarea(pendientes, realizadas);
            break;
        case 0:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opción no válida.\n");
            break;
        }
    } while (opcion != 0);

    // printf("Ingrese la cantidad de clientes\n");
    // scanf("%d", &cantClientes);

    // Clientes *cliente = (Clientes *)malloc(cantClientes * sizeof(Clientes));

    // for (int i = 0; i < cantClientes; i++)
    // {
    //     float totalPorCliente = 0;
    //     cliente[i].ClienteID = i + 1;
    //     cliente[i].NombreCliente = (char *)malloc(50 * sizeof(char));
    //     printf("Ingrese el nombre del cliente %d\n", i + 1);
    //     fflush(stdin);
    //     gets(cliente[i].NombreCliente);
    //     fflush(stdin);
    //     cliente[i].CantidadProductosAPedir = (rand() % 5) + 1;

    //     cliente[i].Productos = (Producto *)malloc(cliente[i].CantidadProductosAPedir * sizeof(Producto));

    //     for (int j = 0; j < cliente[i].CantidadProductosAPedir; j++)
    //     {
    //         int ProductoRandom = (rand() % 5);
    //         cliente[i].Productos[j].ProductoID = j + 1;
    //         cliente[i].Productos[j].Cantidad = (rand() % 10) + 1;
    //         cliente[i].Productos[j].TipoProducto = TiposProductos[ProductoRandom];
    //         cliente[i].Productos[j].PrecioUnitario = 10 + rand() % (100 - 10 + 1);

    //         Producto p = cliente[i].Productos[j];
    //         float costoTotal = CostoTotalDeUnProducto(p);

    //         if (strcmp(p.TipoProducto, "Galletas") == 0)
    //             totalGalletas += costoTotal;
    //         else if (strcmp(p.TipoProducto, "Snack") == 0)
    //             totalSnack += costoTotal;
    //         else if (strcmp(p.TipoProducto, "Cigarrillos") == 0)
    //             totalCigarrillos += costoTotal;
    //         else if (strcmp(p.TipoProducto, "Caramelos") == 0)
    //             totalCaramelos += costoTotal;
    //         else if (strcmp(p.TipoProducto, "Bebidas") == 0)
    //             totalBebidas += costoTotal;

    //         printf("El cliente %s con ID %d, compro el producto %s, tiene una cantidad de %d a un precio de %.2f \n", cliente[i].NombreCliente, cliente[i].ClienteID, cliente[i].Productos[j].TipoProducto, cliente[i].Productos[j].Cantidad, cliente[i].Productos[j].PrecioUnitario);

    //         totalPorCliente += costoTotal;
    //     }
    //     printf("El total del cliente %d es de %.2f\n", i + 1, totalPorCliente);
    // }
    // printf("Total por galletas: %.2f\n Total por Snack: %.2f\n Total por Cigarrillos: %.2f\n Total por Caramelos: %.2f\n Total por Bebidas: %.2f\n", totalGalletas, totalSnack, totalCigarrillos, totalCaramelos, totalBebidas);

    // for (int i = 0; i < cantClientes; i++)
    // {
    //     free(cliente[i].NombreCliente);
    //     free(cliente[i].Productos);
    // }

    // free(cliente);

    LiberarMemoria(pendientes);
    LiberarMemoria(realizadas);

    return 0;
}

Nodo *CrearListaVacia()
{

    return NULL;
}

void *CrearTarea(Nodo **lista, int *idActual)
{

    Nodo *NuevoNodo = (Nodo *)malloc(sizeof(Nodo));

    NuevoNodo->T.Descripcion = (char *)malloc(sizeof(char) * 50);
    printf("Ingrese la descripcion de la nueva tarea \n");
    fflush(stdin);
    gets(NuevoNodo->T.Descripcion);

    NuevoNodo->T.TareaID = (*idActual)++;
    NuevoNodo->T.Duracion = 10 + rand() % 91;

    NuevoNodo->Siguiente = *lista;
    *lista = NuevoNodo;
}

void MostrarLista(Nodo *lista)
{

    while (lista)
    {
        printf("Id de tarea: %d, duracion: %d, descripcion: %s\n", lista->T.TareaID, lista->T.Duracion, lista->T.Descripcion);
        lista = lista->Siguiente;
    }
}

void MarcarTareaComoRealizada(Nodo **pendientes, Nodo **realizadas, int id)
{

    Nodo *actual = *pendientes, *anterior = NULL;

    while (actual != NULL && actual->T.TareaID != id)
    {
        anterior = actual;
        actual = actual->Siguiente;
    }
    if (actual == NULL)
    {
        printf("Tarea no encontrada.\n");
        return;
    }

    if (anterior == NULL)
    {
        *pendientes = actual->Siguiente;
    }
    else
    {
        anterior->Siguiente = actual->Siguiente;
    }

    actual->Siguiente = *realizadas;
    *realizadas = actual;

    printf("Tarea %d realizada con exito\n", id);
}

void TransferirTarea(Nodo **pendientes, Nodo **realizadas)
{

    int id;
    printf("Ingrese la id de la tarea para marcarla como realizada\n");
    scanf("%d", &id);
    MarcarTareaComoRealizada(pendientes, realizadas, id);
}

void ConsultarTarea(Nodo *pendientes, Nodo *realizadas)
{
    char busqueda[50];
    printf("Ingrese el ID o palabra de busqueda\n");
    fflush(stdin);
    gets(busqueda);

    int idEncontrado = atoi(busqueda);
    int encontrada = 0;
    Nodo *aux = pendientes;

    while (aux != NULL)
    {
        if (aux->T.TareaID == idEncontrado || strstr(aux->T.Descripcion, busqueda) != NULL)
        {
            printf("Tarea encontrada en pendientes.\n");
            printf("Tarea de ID: %d, Duracion: %d, y descripcion: %s\n", aux->T.TareaID, aux->T.Duracion, aux->T.Descripcion);
            encontrada = 1;
        }
        aux = aux->Siguiente;
    }
    aux = realizadas;

    while (aux != NULL)
    {
        if (aux->T.TareaID == idEncontrado || strstr(aux->T.Descripcion, busqueda) != NULL)
        {
            printf("Tarea encontrada en realizadas.\n");
            printf("Tarea de ID: %d, Duracion: %d, y descripcion: %s\n", aux->T.TareaID, aux->T.Duracion, aux->T.Descripcion);
            encontrada = 1;
        }
        aux = aux->Siguiente;
    }

    if (!encontrada)
    {
        printf("No se encontro ninguna tarea con ese ID o palabra clave.\n");
    }
}

void LiberarMemoria(Nodo *lista){
    while (lista != NULL)
    {
        Nodo *aux = lista;
        lista = lista->Siguiente;
        free(aux->T.Descripcion);
        free(aux);
    }
    
}

float CostoTotalDeUnProducto(Producto p)
{
    return p.Cantidad * p.PrecioUnitario;
}
