#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double balance = initial;
  int currentAge = startAge;
  int currentPhase = 0;
  while (currentPhase < 2) {
    retire_info phase;
    if (currentPhase == 0) {
      phase = working;
    }
    else if (currentPhase == 1) {
      phase = retired;
    }
    else {
      break;
    }
    for (int thisMonth = 0; thisMonth < phase.months; thisMonth++) {
      printf("Age %3d month %2d you have $%.2f\n",
             currentAge / 12,
             currentAge % 12,
             balance);
      balance = balance + balance * phase.rate_of_return;
      balance = balance + phase.contribution;
      currentAge++;
    }
    currentPhase++;
  }
}

int main() {
  retire_info myWorkPlan;
  myWorkPlan.months = 489;
  myWorkPlan.contribution = 1000;
  myWorkPlan.rate_of_return = .045 / 12.0;
  retire_info myRetiredPlan;
  myRetiredPlan.months = 384;
  myRetiredPlan.contribution = -4000;
  myRetiredPlan.rate_of_return = .01 / 12.0;
  int myAge = 327;
  double mySavings = 21345.0;
  retirement(myAge, mySavings, myWorkPlan, myRetiredPlan);
  return 0;
}
