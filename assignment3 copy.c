#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Employee
{
    char Lname[20];
    char Fname[20];
    char ID[4];
    float salary;
};

int getEmployeeNum(FILE *input, FILE *output, int *grade)
{
    // Check if the first line is an integer
    if (fscanf(input, "%d\n", grade) != 1)
    {
        fprintf(output, "Error: input.txt has wrong format\n");
        return 1;
    }

    // Check if the grade is a valid number
    if (*grade < 1 || *grade > 5)
    {
        fprintf(output, "Error: option number should be an integer between 1 - 5\n");
        return 1;
    }

    // Check Employee info format and get num of Employees
    int numEmployee = 0;
    char Lname[20], Fname[20], ID[9];
    int mid, final;
    while (!feof(input))
    {

        if (fscanf(input, "%s %s %s %d %d\n", Lname, Fname, ID, &mid, &final) != 5)
        {
            if (Lname[0] == 'E')
            {
                break;
            }
            fprintf(output, "Error: input.txt has wrong format\n");
            return 0;
        }
        if (ID[0] != 'A')
        {
            fprintf(output, "Error: Employee number has wrong format\n");
            return 0;
        }
        if (mid > 100 || final > 100)
        {
            fprintf(output, "Error: %s %s's mid or final grade has wrong format\n", Lname, Fname);
            return 0;
        }
        numEmployee++;
    }
    return numEmployee;
}

void getEmployeeInfo(FILE *input, FILE *output, struct Employee *Employees, int numEmployee)
{
    rewind(input);
    int grade = 0;
    fscanf(input, "%d", &grade);

    if (Employees == NULL)
    {
        fprintf(output, "Error: Memory allocation failed\n");
        return;
    }

    // Give values for all particles
    for (int i = 0; i < numEmployee; i++)
    {
        struct Employee *p = Employees + i;
        fscanf(input, "%s %s %s %d %d", p->Lname, p->Fname, p->ID, &p->mid, &p->final);
    }
}

void printGrade(FILE *output, struct Employee *Employees, int numEmployee, int grade)
{
    for (int i = 0; i < numEmployee; i++)
    {
        struct Employee *p = Employees + i;
        printf("%s %s %s %d %d\n", p->Lname, p->Fname, p->ID, p->mid, p->final);
        // if (grade == 1 && (p->mid + p->final) >= 90)
        // {
        //     printf("%s %s %s %d %d\n", p->Lname, p->Fname, p->ID, p->mid, p->final);
        //     fprintf(output, "%s %s %s %d %d\n", p->Lname, p->Fname, p->ID, p->mid, p->final);
        // }
        // else if (grade == 2 && (p->mid + p->final) >= 80)
        // {
        //     fprintf(output, "%s %s %s %d %d\n", p->Lname, p->Fname, p->ID, p->mid, p->final);
        // }
        // else if (grade == 3 && (p->mid + p->final) >= 70)
        // {
        //     fprintf(output, "%s %s %s %d %d\n", p->Lname, p->Fname, p->ID, p->mid, p->final);
        // }
        // else if (grade == 4 && (p->mid + p->final) >= 60)
        // {
        //     fprintf(output, "%s %s %s %d %d\n", p->Lname, p->Fname, p->ID, p->mid, p->final);
        // }
        // else if (grade == 5 && (p->mid + p->final) < 60)
        // {
        //     fprintf(output, "%s %s %s %d %d\n", p->Lname, p->Fname, p->ID, p->mid, p->final);
        // }
    }
}

int main(int argc, char *argv[])
{
    // Initialize file pointer
    char *inputFileName = argv[1];
    char *outputFileName = argv[2];
    FILE *inputFile, *outputFile;
    inputFile = fopen(inputFileName, "r");
    outputFile = fopen(outputFileName, "w");

    // Check argument
    if (argc != 3)
    {
        fprintf(outputFile, "Error: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    // Check if files are opened successfully
    if (inputFile == NULL || outputFile == NULL)
    {
        fprintf(outputFile, "Error: cannot open the files.\n");
        // Quit
        return 1;
    }

    // Intialize some variables we gonna use
    int grade = 0;
    int numEmployee = getEmployeeNum(inputFile, outputFile, &grade);
    struct Employee *Employees = malloc(numEmployee * sizeof(struct Employee));
    getEmployeeInfo(inputFile, outputFile, Employees, numEmployee);
    printGrade(outputFile, Employees, numEmployee, grade);
    return 0;
}