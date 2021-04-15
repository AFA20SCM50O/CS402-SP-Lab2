

#include <stdio.h>
#include <string.h>
#include "readfile.h"
#define MAXNAME 64

extern FILE *file; 
struct employee  
{
    char firstName[MAXNAME];
    char lastName[MAXNAME];
    int empID;
    int salary;
};
struct employee db[1000]; 
int empcounter = 0; 
char term; 

//used to print out the DB         
void PrintDB (struct employee x[], int x_size)
{
    int i;

    printf("\nName\t\t\t\tSALARY\t   ID\n");
    printf("----------------------------------------------\n");
    for (i = 0; i < x_size; i++)
    {
        printf("%-15s\t%-15s\t%d\t%d\n", x[i].firstName,x[i].lastName,x[i].salary, x[i].empID);
    }
    printf("----------------------------------------------\n");
    printf(" Number of Employees (%d)\n", x_size);
}

// search employee by ID

int searchID (struct employee arr[], int m, int key)
{
    int i;
    for (i = 0; i < m; i++)
    {
        if (arr[i].empID == key)
        {
            return i;
        }
    }
    return -1;
}



//last name search
int searchLName (struct employee arr[], int m, char* name)
{
    int i;
    for (i = 0; i < m; i++)
    {
        if (strcmp(arr[i].lastName, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

//add employee
int addEmp(struct employee arr[])
{
    char newFirst[MAXNAME];
    char newLast[MAXNAME];
    int newSalary;
    int confirm;

    printf("\nEnter first name: ");
    scanf("%s", newFirst);
    if (strlen(newFirst) > 64)
    {
        printf("Too Long. Try again.\n");
        return 0;
    }
    printf("Enter last name: ");
    scanf("%s", newLast);
    if (strlen(newFirst) > 64)
    {
        printf("Too Long. Try again.\n");
        return 0;
    }
    printf("Enter employee's salary (30000 to 150000): ");
    scanf("%d", &newSalary);
    if (newSalary < 30000 || newSalary > 150000)
    {
        printf("Error, out of range.\n");
        return 0;
    }
    printf("\nAre you sure you want to add the employee?\n");
    printf("\t%s %s, \tSalary: %d\n", newFirst, newLast, newSalary);
    printf("\nEnter 1 for yes, 0 for no: ");
    scanf("%d", &confirm);

    if (confirm == 1)
    {
        strcpy(db[empcounter].firstName, newFirst);
        strcpy(db[empcounter].lastName, newLast);
        db[empcounter].salary = newSalary;
        db[empcounter].empID = db[empcounter -1].empID + 1;
        empcounter++;
        printf("employee add complete\n");
    }
    return 1;
}

//create db
void populateDB(char* datafile)
{
    if (open_file(datafile) == 0)
    {
        char buffer[135];
        int ret;
        while (fgets(buffer, sizeof(buffer), file)) 
        {
            ret = read_int(buffer, 1, &db[empcounter].empID);
            ret = read_int(buffer, 2, &db[empcounter].salary);
            ret = read_string(buffer, 1, &db[empcounter].firstName);
            ret = read_string(buffer, 2, &db[empcounter].lastName);
            empcounter++; 
        }

        if (feof(file)) // end of file
        {
            close_file(file);
        } 
    }
}

int updateEmployee(int employeeDbIndexToUpdate)
{
    char newFirst[MAXNAME];
    char newLast[MAXNAME];
    int newSalary;
    int confirm;

    printf("\nEnter first name (input 0 to skip): ");
    scanf("%s", newFirst);
    if (strlen(newFirst) > 64)
    {
        printf("Too Long. Try again.\n");
        return 0;
    }
    
    printf("Enter last name (input 0 to skip): ");
    scanf("%s", newLast);
    if (strlen(newFirst) > 64)
    {
        printf("Too Long. Try again.\n");
        return 0;
    }
    printf("Enter employee's salary (30000 to 150000) (input 0 to skip): ");
    scanf("%d", &newSalary);
    if (newSalary < 30000 || newSalary > 150000)
    {
        if (newSalary != 0) {
            printf("Error, out of range.\n");
            return 0;
        }
    }
    printf("\nAre you sure you want to add the employee?\n");
    printf("\t%s %s, \tSalary: %d\n", newFirst, newLast, newSalary);
    printf("\nEnter 1 for yes, 0 for no: ");
    scanf("%d", &confirm);

    if (confirm != 1)
    {
        return 1;
    }

    if (strncmp(newFirst, "0", 1) != 0) {
        strcpy(db[employeeDbIndexToUpdate].firstName, newFirst);
        printf("Updated first name\n");
    } else {
        printf("Skipping update to first name\n");
    }

    if (strncmp(newLast, "0", 1) != 0) {
        strcpy(db[employeeDbIndexToUpdate].lastName, newLast);
        printf("Updated last name\n");
    } else {
        printf("Skipping update to last name\n");
    }
    
    if (newSalary != 0) {
        db[employeeDbIndexToUpdate].salary = newSalary;
        printf("Updated new salary\n");
    } else {
        printf("Skipping update to salary\n");
    }
    
    printf("employee update complete\n");
    
    return 1;
}

void Swap(struct employee* xp, struct employee* yp) 
{ 
    struct employee temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
//sort
void sort(struct employee arr[], int n) 
{ 
    int i, j, min; 
  
     
    for (i = 0; i < n - 1; i++) { 
  
        
        min = i; 
        for (j = i + 1; j < n; j++) 
            if (arr[j].empID < arr[min].empID) 
                min = j; 
  
        
        Swap(&arr[min], &arr[i]); 
    } 
}

//sort
void sortSalary(struct employee arr[], int n) 
{ 
    int i, j, min; 
  
     
    for (i = 0; i < n - 1; i++) { 
  
        
        min = i; 
        for (j = i + 1; j < n; j++) 
            if (arr[j].salary > arr[min].salary) 
                min = j; 
  
        
        Swap(&arr[min], &arr[i]); 
    } 
}

void removeEmployee(int employeeToRemoveIndex) {
    int lastEmployeeIndex = empcounter - 1;
    Swap(&db[employeeToRemoveIndex], &db[lastEmployeeIndex]);
    empcounter = empcounter - 1;
    sort(db, empcounter);
}

void outputTopSalaries(int numberOfSalaries) {
    struct employee dbTemp[1000];
    memcpy(&dbTemp, &db, sizeof(dbTemp));
    sortSalary(dbTemp, empcounter);
    PrintDB(dbTemp, numberOfSalaries);
}

void findAllByLastName(struct employee arr[], int m, char* name) {
    struct employee dbTemp[1000];
    int found = 0;
    for (int i = 0; i < m; i++)
    {
        if (strcasecmp(arr[i].lastName, name) == 0)
        {
            strcpy(dbTemp[found].firstName, arr[i].firstName);
            strcpy(dbTemp[found].lastName, arr[i].lastName);
            dbTemp[found].salary = arr[i].salary;
            dbTemp[found].empID = arr[i].empID;
            found++;
        }
    }
    PrintDB(dbTemp, found);
}

int main(int argc, char *argv[])
{
    if ( argc != 2 ) 
    {
        
        printf( "usage: %s filename\n", argv[0] );
    }
    else
    {   
        populateDB(argv[1]);        
        sort(db, empcounter); 

        int choice; 
        int x = 0; 
        
        while (1) {
            printf("\nEmployee DB Menu:\n");
            printf("----------------------------------\n");
            printf("\t(1) Print the Database\n");
            printf("\t(2) Lookup by ID\n");
            printf("\t(3) Lookup by Last Name\n");
            printf("\t(4) Add an Employee\n");
            printf("\t(5) Quit\n");
            printf("\t(6) Remove an Employee\n");
            printf("\t(7) Update an employee's information\n");
            printf("\t(8) Print the M employees with the highest salaries\n");
            printf("\t(9) Find all employees with matching last name\n");
            printf("----------------------------------\n");
            printf("Enter your choice: ");

            scanf("%d", &choice); //scan user choice

            //switch case
            switch (choice) {
                case 1:
                    PrintDB(db, empcounter);
                    break;
                case 2:;
                    int lookforID; 
                    printf("\nPlease enter an employee ID: ");
                    scanf("%d", &lookforID);
                    x = searchID(db, empcounter, lookforID);
                    if (x == -1)
                    {
                        printf("\nUser with employee ID '%d' not found\n",lookforID);
                    }
                    else
                    {
                        printf("\nName\t\t\t\tSALARY\t   ID\n");
                        printf("----------------------------------------------\n");
                        printf("%-15s\t%-15s\t%d\t%d\n", db[x].firstName,db[x].lastName,db[x].salary, db[x].empID);
                        printf("----------------------------------------------\n");
                    }
                    
                    break;
                case 3:;
                    char target_name[MAXNAME]; //target name to search                 
                    printf("\nPlease enter an employee's last name: ");
                    scanf("%s", target_name); 
                    x = searchLName(db, empcounter, target_name);
                    if (x == -1)
                    {
                        printf("\nUser with last name '%s' not found\n", target_name);
                    }
                    else
                    {
                        printf("\nName\t\t\t\tSALARY\t   ID\n");
                        printf("----------------------------------------------\n");
                        printf("%-15s\t%-15s\t%d\t%d\n", db[x].firstName,db[x].lastName,db[x].salary, db[x].empID);
                        printf("----------------------------------------------\n");
                    }                    
                    break;
                case 4:;
                    addEmp(db);
                    break;
                case 5:; 
                    printf("\n You have chosen to exit... Goodbye \n");      
                    return 0;
                    break;
                case 6:; // remove an employee
                    int employeeIdToDelete; 
                    printf("\nPlease enter an employee ID: ");
                    scanf("%d", &employeeIdToDelete);
                    int employeeDbIndexToDelete = searchID(db, empcounter, employeeIdToDelete);
                    if (employeeDbIndexToDelete == -1)
                    {
                        printf("\nUser with employee ID '%d' not found\n", employeeIdToDelete);
                    }
                    else
                    {
                        removeEmployee(employeeDbIndexToDelete);
                    }
                    break;
                case 7:; // Update an employee's information
                    int employeeIdToUpdate; 
                    printf("\nPlease enter an employee ID: ");
                    scanf("%d", &employeeIdToUpdate);
                    int employeeDbIndexToUpdate = searchID(db, empcounter, employeeIdToUpdate);
                    updateEmployee(employeeDbIndexToUpdate);
                    break;
                case 8:; // print the M employees with the highest salaries
                    int numberOfSalaries; 
                    printf("\nTop number of salaries to print?: ");
                    scanf("%d", &numberOfSalaries);
                    outputTopSalaries(numberOfSalaries);
                    break;
                case 9:; // find all employees with matching last name
                    char lastNameToSearch[MAXNAME]; //target name to search                 
                    printf("\nPlease enter an employee's last name: ");
                    scanf("%s", lastNameToSearch); 
                    findAllByLastName(db, empcounter, lastNameToSearch);
                    break;
                default:;            
                    printf( "\n Error, please try again.\n" );
                    break;
            }
        }
    }
}