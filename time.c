#include "types.h"
#include "user.h"

void printTime(char *cname, int real_end, int sys_end, int user_end){
//Imprime o resultado calculando o tempo baseado nos ticks do processador;
printf(1, "\n\nComando %s:\nReal time: %d.%d%d.\nSystem time: %d.%d%d.\nUser time: %d.%d%d.\n\n",
              cname,
              real_end / 100,
              real_end % 100 / 10,
              real_end % 100 % 10,
              sys_end / 100,
              sys_end % 100 / 10,
              sys_end % 100 % 10,
              user_end / 100,
              user_end % 100 / 10,
              user_end % 100 % 10);  
}

int
call(char *argv[])
{ 
  int pid = fork();
  
  //Inicia a contagem do real_time
  int real_start = uptime(); 
  
  //Chama essa função pra poder zerar o valor acumulado no contador de tempo das chamadas de sistema.
  systime();
  
  
  if(pid == 0)
  {
    //Executa o comando recebido como parâmetro pela função time.    
    if(exec(argv[0], &argv[0]) < 0)
    {
      printf(2, "Erro\n");
    }    
  } else if(pid > 0)
  {
    wait();
  }
  else
  {
    printf(2, "Erro");
    exit();
  }
  
  //Número de ticks acumulados das chamadas de sistema.
  int sys_end = systime();
  //Número de ticks entre o começo real da chamada e o fim real da chamada.
  int real_end = uptime() - real_start;
  //Considerei o user time como o real_time - sys_time.
  int user_end = real_end - sys_end;
  
  printTime(argv[0], real_end, sys_end, user_end);
                                
  exit();
} 

int
main(int argc, char *argv[])
{
  if (argv[1] != 0)
    call(&argv[1]);
  else
    printf(1, "ran in 0.00 seconds.\n");
     
  exit();
}
