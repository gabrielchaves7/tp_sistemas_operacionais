#include "types.h"
#include "user.h"
#include "date.h"

int stdout = 1;
int stderr = 2;

int
main(int argc, char *argv[])
{
  struct rtcdate data;
  
  date(&data);
  printf(1, "%d/%d/%d %d:%d:%d\n",data.day, data.month, data.year, data.hour, data.minute, data.second);
  
  exit();
}
