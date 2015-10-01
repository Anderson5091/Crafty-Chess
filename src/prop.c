#include <stdio.h>
#include <stdlib.h>
main()
{
  float pitch, rpm, speed;
  char buff[16];
  printf("Prop performance analyzer\n");
  printf("engine:  Mercury XR6 150hp  1.78:1 final drive ratio\n");
  printf("assumes SS cupped propeller with a 10% slip factor\n\n");
  while (1) {
    printf("enter prop pitch (in inches): ");
    gets(buff);
    pitch=atof(buff);
    printf("enter engine RPM: ");
    gets(buff);
    rpm=atof(buff);
    printf("enter boat speed (mph): ");
    gets(buff);
    speed=atof(buff);
    if (pitch + rpm + speed == 0) exit(0);
    if (pitch == 0) pitch = ((speed*1.78*12.0*5280.0)/(60.0*rpm)-1.0)/.9;
    else if (rpm == 0) rpm = (12.0*5280.0*speed*1.78)/(60.0*(pitch+1.0)*.9);
    else speed = ((60.0*rpm*(pitch+1.0)/1.78)/(12.0*5280.0))*.9;
    printf("   pitch        rpm          speed\n");
    printf("     %2d        %4d           %4.1f\n",
           (int) (pitch+.5), (int) rpm, speed);
  }
}
