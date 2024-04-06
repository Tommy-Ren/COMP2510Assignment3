#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

typedef struct {
    int id;
    char *firstName;
    char *lastName;
    float salary;
} Person;

// Global variable
FILE *inputfile;
FILE *outputfile;

// Check valid id
int checkId(Person *arr, int size, int id, int pos) {
    for (int i = 0; i < size; i++) {
        if (i != pos){
            if (arr[i].id == id || id < 0 || !isdigit(id)){
                return 0;
            }
        }
    }
    return 1;
}

// Check valid salary
int checkSalary(float salary) {
    if (salary < 0){
        return 0;
    };
    return 1;
}

// Check valid name
int checkName(char *name) {
    for (int i = 0; i < strlen(name); i++) {
        if (!((name[i] >= 'a' && name[i] <= 'z') 
            || (name[i] >= 'A' && name[i] <= 'Z') 
            || name[i] == '-')) {
            return 0;
        }
    }
    return 1;
}

// Compare
int comparePerson(Person *a, Person *b) {
    int firstNameCompare = strcmp(a->firstName, b->firstName);
    if (firstNameCompare != 0) {
        return firstNameCompare;
    }

    int lastNameCompare = strcmp(a->lastName, b->lastName);
    if (lastNameCompare != 0) {
        return lastNameCompare;
    } 

    return a->id - b->id;
}

// Sorts an array of people based of criteria.
void sortArray(Person *arr, int size) {
    for (int i = 0; i < size; i++) {
        Person *smallest = &arr[i];
        int s = 0;
        for (int j = i; j < size; j++) {
            if (comparePerson(smallest, &arr[j]) >= 0) {
                smallest = &arr[j];
                s = j;
            }
        }
        Person temp = arr[s];
        arr[s] = arr[i];
        arr[i] = temp;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3){
        // Quit
        return 1;
    }

    // Initialize input and output
    char *inputFileName = argv[1];
    char *outputFileName = argv[2];

    // Open the input file
    inputfile = fopen(inputFileName, "r");
    if (inputfile == NULL) {
        // Quit
        return 1;
    }

    // Open the output file
    outputfile = fopen(outputFileName, "w");
    if (outputfile == NULL) {
        // Quit
        return 1;
    }

    // Find how many line in the input
    int size = 0;
    int foundE = 0;
    char inputchar;
    while ((inputchar = fgetc(inputfile)) != EOF) {
        char nextchar;
        if (inputchar == 'E' && (nextchar = fgetc(inputfile)) == '\n') {
            foundE++;
            break;
        } else {
            if (inputchar == '\n') {
                size++;
            }
        }  
    }
    fclose(inputfile);
    
    // Error case
    // No E end
    if (foundE != 1) {
        fprintf(outputfile, "Error");
        // Quit
        return 1;
    }

    // Array to store person info
    Person *arr = malloc(sizeof(Person) * size);
    // Empty record
    if (size == 0 || arr == NULL){
        fprintf(outputfile, "Error");
        // Quit
        return 1;
    }

    // Re-open the input file to reset the pointer
    inputfile = fopen(inputFileName, "r");

    // Put persons in array
    for (int i = 0; i < size; i++) {

        // Initialize lastName, firstName and studentNumber
        arr[i].firstName = malloc(50 * sizeof(char));
        arr[i].lastName = malloc(50 * sizeof(char));
        if (arr[i].firstName == NULL || arr[i].lastName == NULL){
            fprintf(outputfile, "Error");
            // Quit
            return 1;
        }
        
        // Scan students in input file
        fscanf(inputfile, "%d,%[^ ] %[^,],%f", 
               &arr[i].id,
               arr[i].firstName, 
               arr[i].lastName, 
               &arr[i].salary 
               );

        // Non-valid id
        if (!checkId(arr, size, arr[i].id, i)) {
            fprintf(outputfile, "Error");
            // Quit
            return 1;
        }

        // Non-valid salary
        if (!checkSalary(arr[i].salary)) {
            fprintf(outputfile, "Error");
            // Quit
            return 1;
        }
    }

    sortArray(arr, size);

    // Print the output
    for (int i = 0; i < size; i++) {
        fprintf(outputfile, "%d,%s %s,%.2f\n",
                arr[i].id, arr[i].firstName, arr[i].lastName, arr[i].salary);
    }

    // Free the array
    for (int i = 0; i < size; i++) {
        free(arr[i].firstName);
        free(arr[i].lastName);
    }
    free(arr);

    fclose(inputfile);
    fclose(outputfile);

    return 0;
}
