#include <iostream>
#include <stdio.h>
#include <math.h>
#include <chrono> //Libreria que permite medir el tiempo
#include <pthread.h> //Librería que permite la creación de hilos
#include <thread>
#include "string" //Para usar strings
using namespace std; //Permite no poner std:: antes de cada comando std
long double arr[100000000]; /*Me permite crear el array de 10000000 datos,
es un long double para que pueda llegar a números altos sin producir errores y se cambió a 10000000
para notar un cambio en el tiempo de ejecución*/ 
void single_thread();//Función de un hilo
void threader();//Función que entrelaza varios hilos

int main(void)//Función principal
{
    char h;
    cout << "Digite la cantidad de hilos (1 o 4)" << endl;//Dos opciones según la cantidad de hilos que se quieran.
    cin >> h;

    switch(h)
    {
        case '1': //Para el caso de un hilo
            single_thread(); //Haga el caso de un hilo
            break;
        case '4': //Para el caso de 4 hilos haga la función threader.
            threader();
            break;
        default:
            main();//Si puso otra cosa que no tiene sentido, que comience de nuevo.
    }
}

void thread_four(int j)//Cuatro hilos, recibe donde comienza a contar el hilo actual, no retorna nada.
{
    chrono::steady_clock sc; //Crea una variable de reloj
    auto start = sc.now();//Comienza el cronómetro (toma el tiempo)
    for (long int i = j; i<(j+25000000); i++) // Crea los arrays según la variable c, me permite haber usado solo un for.
    {
        arr[i]=pow(i,2);
    }
    auto end = sc.now();//Termina el cronómetro
    auto time_span = static_cast<chrono::duration<double>>(end - start); //Resta el tiempo final menos el inicial para obtener el tiempo que duró en ejecutarse un hilo
    cout<<"Para cuatro hilos tomó "<<time_span.count()<<" segundos en el hilo " << j << endl; //Dice cuanto duró el cronómetro y el hilo que se ejecutó.
}

void threader() // Crea los hilos, no crea ni retorna nada
{
    chrono::steady_clock sc;
    auto start = sc.now();//Guarda la hora de comienzo.
    thread t1(thread_four,0); // Crea los hilos, mandandolo a la función de cuatro hilos, el número a la derecha de la coma corresponde a la entrada de la función
    thread t2(thread_four,25000000);
    thread t3(thread_four,50000000);
    thread t4(thread_four,75000000);
    t1.join();//Espera que termine T1 para continuar
    t2.join();
    t3.join();
    t4.join(); // Ya terminaron sus operaciones todos los hilos
    auto end = sc.now();// Guarda el tiempo una vez se ejecutan todos los hilos.
    auto time_span = static_cast<chrono::duration<double>>(end - start); // Dice el tiempo transcurrido para todos los hilos
    cout<<"Para cuatro hilos tomó "<<time_span.count()<<" segundos en total" << endl;
}
void single_thread() // Un solo hilo, operación muy simple, no retorna ni recibe nada.
{
    chrono::steady_clock sc;
    auto start = sc.now(); // Guarda la hora de comienzo

    for (long int i = 0; i<100000000;i++)//Hace el array en un solo hilo y de manera secuencial.
    {
        arr[i]=pow(i,2);
    }
    auto end = sc.now(); // Guarda la hora en la que termina la operación
    auto time_span = static_cast<chrono::duration<double>>(end - start); // Dice el tiempo transcurrido en total para la ejecución de un solo hilo.
    cout<<"Para un solo hilo tomó "<<time_span.count()<<" segundos" << endl;

}