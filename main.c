/* Header files. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO_OF_EMPLOYEE 0

#define MAX_NO_OF_EMPLOYEE 20

#define CONFIRM_EXIT 4


/* Structure definitions. */
typedef struct{
    unsigned empID;
    char empName[40];
} Employee;


/* Declaring functions */
void loadData(Employee *, unsigned int *, unsigned int);
void addEmployee(Employee *, unsigned int *);
void displayEmployee(Employee *, unsigned int);
void update(Employee *, unsigned int);
void saveData(Employee *, unsigned int);

int bufferNotEmpty();

int main(void) {
    Employee employee[MAX_NO_OF_EMPLOYEE];
    unsigned int noOfEmployee;
    int option = 0;
    
    loadData(employee, &noOfEmployee, MAX_NO_OF_EMPLOYEE);
    
    do{
        printf("MENU:\n");
        printf("1.Add a Record\n");
        printf("2.Display the File\n");
        printf("3.Update the Record\n");
        printf("4.Exit\n");
        printf("Enter your Choice: ");
        
        do{
            scanf("%d", &option);
            if (bufferNotEmpty()) {
                option = 0;
            }
            if (option < 1 || option > 4) {
                printf("You need to enter [1-4] : ");
            }
            /* Error validation */
        } while (option < 1 || option > 4);
        
        switch(option) {
            case 1:
                addEmployee(employee, &noOfEmployee);
                break;
            case 2:
                displayEmployee(employee, noOfEmployee);
                break;
            case 3:
                displayEmployee(employee, noOfEmployee);
                update(employee, noOfEmployee);
                break;
            case 4:
                saveData(employee, noOfEmployee);
                break;
        }
    } while (option != CONFIRM_EXIT);
    return EXIT_SUCCESS;
}

void loadData(Employee *employee, unsigned int *noOfEmployee, unsigned int maxNoOfEmployee){
    FILE *file;
    int i = 0;
    /* Loading file and create if it the file does not exist */
    if ((file = fopen("employee.dat", "ab+")) == NULL) {
        exit(EXIT_FAILURE);
    }
    /* Reading file and making sure it gets 2 variables (employeeID and employeeName) up to maxNoOfEmployees */
    while (fscanf(file, " %u,%[^\n]", &employee[i].empID, employee[i].empName) == 2) {
        if (++i >= maxNoOfEmployee) {
            break;
        }
    }
    
    *noOfEmployee = i;
    printf("Loaded %d employees.\n", i);
    
    /* Closing file handle */
    fclose(file);
}

void addEmployee(Employee *employee, unsigned int *noOfEmployee){
    int i, employeeID;
    
    do {
        printf("\nEnter Employee ID: ");
        scanf("%d", &employeeID);
        /* Ensure proper ID is keyed in and must be > 0 */
    } while (bufferNotEmpty() || employeeID <= 0);
    
    /* Check if employee exists */
    for (i = 0; i < *noOfEmployee; i++) {
        if (employee[i].empID == employeeID) {
            printf("\nEmployee already exists.\n\n");
            return;
        }
    }
    
    /* Assigns the employee ID as the employee with the ID does not exist */
    employee[*noOfEmployee].empID = employeeID;
    printf("Enter Employee Name: ");
    scanf(" %[^\n]s", employee[*noOfEmployee].empName);
    printf("\n");
    
    *noOfEmployee = *noOfEmployee + 1;
    
    /* Saves the employee data */
    saveData(employee, *noOfEmployee);
    
}

void displayEmployee(Employee *employee, unsigned int noOfEmployee){
    printf("\n");
    int i;
    
    /* Loops through all the employees and prints */
    for(i = 0; i < noOfEmployee; i++) {
        printf("%d", employee[i].empID);
        printf(" %s\n", employee[i].empName);
    }
    printf("\n");
    
}

void update(Employee *employee, unsigned int noOfEmployee) {
    int id;
    int i;
    
    do {
        printf("\nEnter Employee ID to update: ");
        scanf("%d", &id);
        
        /* Error validation */
    } while (bufferNotEmpty());
    
    for (i = 0; i < noOfEmployee; i++) {
        /* Enters if employee exists, and saves the file */
        if(id == employee[i].empID) {
            printf("Enter Employee Name for Update: ");
            scanf(" %[^\n]s", employee[i].empName);
            printf("\nRecord updated.\n\n");
            saveData(employee, noOfEmployee);
            return;
        }
    }
    printf("Employee with that ID does not exist.\n\n");
}

void saveData(Employee *employee, unsigned int noOfEmployee) {
    int i;
    FILE *fp;
    /* Open file with write mode */
    if ((fp = fopen("employee.dat", "w")) == NULL) {
        printf("\nERROR: File cannot be opened to write/save.\n");
        return;
    }
    /* Loops through all the employees and saves them line by line */
    for (i = 0; i < noOfEmployee; i++) {
        fprintf(fp, "%u,%s\n", employee[i].empID, employee[i].empName);
    }
    fclose(fp);
}

int bufferNotEmpty() {
    int count = 0;
    char clear;
    /* Ensuring that there's nothing left in the keyboard buffer */
    while ((clear = getchar()) != '\n' && clear != EOF) {
        count++;
    }
    return count;
}