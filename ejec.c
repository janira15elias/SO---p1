#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void alarma()
{
    signal(SIGALRM,SIG_IGN);
    printf("¡Alarma!\n");
}

int main()
{
    int i,e,aux1=0,aux2=0;
    int pid_arb,pid_A,pid_B,pid_X,pid_Y,pid_Z;

    for(int j=0;j<2;j++)
    {
        if(fork()==0)
        { 
            if(aux1==0)
            {
                pid_arb=getppid();
                pid_A=getpid();
                printf ("Soy el proceso ejec: mi pid es %d\n",pid_arb);
                printf("Soy el proceso A: mi pid es %d. Mi padre es %d\n",pid_A,getppid());
                aux1++;
            }
            else
            {
                pid_B=getpid();
                printf("Soy el proceso B: mi pid es %d. Mi padre es %d. Mi abuelo es %d\n",pid_B,getppid(),pid_arb);

                //Three grandsons:
                for(i = 0;i < 3;i++)
                {
                    if(fork() == 0)
                    {
                        if(aux2==0)
                        {
                            pid_X=getpid();
                            printf("Soy el proceso X: mi pid es %d. Mi padre es %d. Mi abuelo es %d. Mi bisabuelo es %d\n",pid_X,getppid(),pid_A,pid_arb);
                            break;
                        }
                        else if(aux2==1)
                        {
                            pid_Y=getpid();
                            printf("Soy el proceso Y: mi pid es %d. Mi padre es %d. Mi abuelo es %d. Mi bisabuelo es %d\n",pid_Y,getppid(),pid_A,pid_arb);
                            break;
                        }
                        else
                        {
                            pid_Z=getpid();
                            printf("Soy el proceso Z: mi pid es %d. Mi padre es %d. Mi abuelo es %d. Mi bisabuelo es %d\n",pid_Z,getppid(),pid_A,pid_arb);
                            
                            //alarm(15);
                            
                            //Kill one by one:
                            printf("Soy Z (%d) y muero\n",pid_Z);
                            kill(pid_Z,SIGKILL);
                            sleep(3);
                            printf("Soy Y (%d) y muero\n",pid_Y);
                            kill(pid_Y,SIGKILL);
                            sleep(3);
                            printf("Soy X (%d) y muero\n",pid_X);
                            kill(pid_X,SIGKILL);
                            sleep(3);
                            printf("Soy B (%d) y muero\n",pid_B);
                            kill(pid_B,SIGKILL);
                            sleep(3);
                            printf("Soy A (%d) y muero\n",pid_A);
                            kill(pid_A,SIGKILL);
                            sleep(3);
                            printf("Soy ejec (%d) y muero\n",pid_arb);
                            kill(pid_arb,SIGKILL);
                            sleep(3);
                            break;

                        }
                    }
                    sleep(4);
                    aux2++;
                }
            }
        }
        else       
        {
            wait(&e);
            exit(0);        
        }    
        sleep(4);
    }
}