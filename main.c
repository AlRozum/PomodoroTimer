#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>
#define ENTER_BUTTON 13

typedef enum
{
    WORKTIMER,
    RESTTIMER
} PROCESS_t;

time_t worktime = 0;
time_t resttime = 0;
uint32_t setnum = 0;



void Header(void);
bool Timer_Set(void);
void Timer(time_t input, PROCESS_t process);
void Default_Config(void);
bool Custom_Config(void);

int main()
{
    Header();
    bool isready = false;
    while ((isready = Timer_Set()))
    {
        printf("Sets = %d, Worktime = %ld min, Rest = %ld min\n", setnum, worktime / 60, resttime / 60);
        for (uint32_t i = 0; i < setnum; i++)
        {
            printf("SET %d\n", i + 1);
            Timer(worktime, WORKTIMER);
            Timer(resttime, RESTTIMER);
            printf("SET!\n\n");
        }
    }
    return 0;
}

void Header()
{
    printf(" __________________________________________________________________ \n");
    printf("|                                                                  |\n");
    printf("| 000     000    0       0    000    000      000    000     000   |\n");
    printf("| 0  0   0   0   00     00   0   0   0  0    0   0   0  0   0   0  |\n");
    printf("| 0  0  0     0  0 0   0 0  0     0  0   0  0     0  0  0  0     0 |\n");
    printf("| 000   0     0  0  0 0  0  0     0  0   0  0     0  000   0     0 |\n");
    printf("| 0     0     0  0   0   0  0     0  0   0  0     0  0 0   0     0 |\n");
    printf("| 0      0   0   0       0   0   0   0  0    0   0   0  0   0   0  |\n");
    printf("| 0       000    0       0    000    000      000    0   0   000   |\n");
    printf("|__________________________________________________________________|\n");
    printf("|               0000000  0  0       0  0000000  000                |\n");
    printf("|                  0        00     00  0        0  0               |\n");
    printf("|                  0     0  0 0   0 0  0        0  0               |\n");
    printf("|                  0     0  0  0 0  0  0000     000                |\n");
    printf("|                  0     0  0   0   0  0        0 0                |\n");
    printf("|                  0     0  0       0  0        0  0               |\n");
    printf("|                  0     0  0       0  0000000  0   0              |\n");
    printf("|__________________________________________________________________|\n");

}

bool Timer_Set()
{
    printf("\n\n");
    fflush(stdin);
    worktime = 0;
    resttime = 0;
    setnum = 0;
    uint32_t result = 0;
    printf("Press Enter for default setup (2 sets, 25 min worktime, 5 min rest) or press any key to configure: ");
    result = _getch();
    if ((char)result == ENTER_BUTTON)
    {
        Default_Config();
        return true;
    }
    else
    {
        return Custom_Config();
    }

}

void Timer(time_t input, PROCESS_t process)
{
    static char* messages[] = { "Work timer in progress...\n", "Rest timer in progress...\n" };
    printf("%s", messages[process]);
    time_t starttime = time(NULL);
    time_t currtime = time(NULL);
    while ((time_t)difftime((currtime = time(NULL)), starttime) < input)
    {
        //do nothing
    }
    printf("\a");
}

void Default_Config()
{
    setnum = 2;
    worktime = 1500;
    resttime = 300;
    printf("\n\nDefault configuration\n");
}

bool Custom_Config()
{
    uint32_t result = 0;
    printf("\nEnter Number of sets,  Work and Rest timers in minutes (enter any letter for quit): ");
    result = scanf("%lu %lu %lu", &setnum, &worktime, &resttime);
    if ((result != 3) || ((setnum * worktime * resttime) <= 0))
    {
        return false;
    }
    else
    {
        worktime *= 60;
        resttime *= 60;
        printf("\nCustom configuration\n");
        return true;
    }
}
