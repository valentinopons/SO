#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 

//ejercicio 2

int KEY_READY;
int KE_RUNNING;
int KE_BLOCKED;
int KE_NEW;
int PC;
int R0;
/*
·=·; // asignación entre registros y memoria
int ke_current_user_time(); // devuelve el valor del cronómetro
void ke_reset_current_user_time(); // resetea el cronómetro
void ret(); // desapila el tope de la pila y reemplaza el PC
void set_current_process(int pid) // asigna al proceso con el pid como el siguiente
a ejecutarse

*/

typedef struct  {
    int STAT; // valores posibles KE_RUNNING, KE_READY, KE_BLOCKED, KE_NEW
    int P_ID; // process ID
    int PC; // valor del PC del proceso al ser desalojado
    int RO; // valor del registro R0 al ser desalojado
    // ....
    int R15; // valor del registro R15 al ser desalojado
    int CPU_TIME // tiempo de ejecución del proceso
    } PCB;

    
    void Ke_context_switch(PCB* pcb_0, PCB* pcb_1){
        pcb_0->STAT = KEY_READY;
        pcb_0->PC = PC;
        for (int i = 0; i <= 15; i++)
        {
            pcb_0->RO = R0; //  CON 0 = i;
        }
        pcb_0->CPU_TIME = ke_current_user_time();

        pcb_1->STAT = KE_RUNNING;
        PC = pcb_1->PC;
        for (int i = 0; i <= 15; i++){
            R0 = pcb_1->RO; // con 0 = i
        }
        pcb_1->CPU_TIME = 0;
        ke_reset_current_user_time();
        set_current_process(pcb_1->P_ID);
        ret();
    }
    
    
    
    