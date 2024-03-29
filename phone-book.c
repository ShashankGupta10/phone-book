#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_COMMAND_SIZE 1000
#define file_name "phone_book.txt"

void help()
{
    printf("Usage: pb [TYPE] [FLAG]... [DATA]...\n");
    printf("Use the phone book to add, update, delete, or find records.\n\n");
    printf("NOTE:\n- E-mail IDs are unique, so duplicate e-mail IDs are not allowed.\n- Commands are whitespace-sensitive, so data should not contain whitespaces.\n\n");
    printf("Actions:\n\
    - Display all records: pb display\n\
    - Add a record: pb add <first_name> <last_name> <unique_email> <phone_number>\n\
    - Find a record using an e-mail: pb find -e <email_of_record_to_find>\n\
    - (To do) Update a record: pb update <first_name> <last_name> <email_of_record_to_update> <phone_number>\n\
    - (To do) Delete a record: pb delete <email_of_record_to_delete>\n\
    - (To do) Find record(s) using a first name: pb find -n <first_name_of_records_to_find>\n\
    - Exit phone book: pb exit\n\
    - Display command help: pb help\n");
}

void display()
{
    printf("\n");
    FILE *file = fopen(file_name, "r");
    char line[MAX_COMMAND_SIZE];
    int num = 0;
    bool printed = false;
    while (fgets(line, sizeof(line), file))
    {
        if (line[0] != '\n' && num % 4 == 0)
        {
            char *first_name = strtok(line, "\n");
            printf("First Name: %s\n", first_name);
            printed = false;
        }
        else if (line[0] != '\n' && num % 4 == 1)
        {
            char *last_name = strtok(line, "\n");
            printf("Last Name: %s\n", last_name);
            printed = false;
        }
        else if (line[0] != '\n' && num % 4 == 2)
        {
            char *email = strtok(line, "\n");
            printf("Email: %s\n", email);
            printed = false;
        }
        else if (line[0] != '\n' && num % 4 == 3)
        {
            char *phone_number = strtok(line, "\n");
            printf("Mobile No.%s\n", phone_number);
            printed = false;
        }
        else if (!printed)
        {
            printf("\n--------------------\n\n");
            printed = true;
        }
        num++;
    }
    fclose(file);
}

void add_record(char *command)
{
    printf("Adding a record...\n");
    char *substr = malloc(sizeof(char) * MAX_COMMAND_SIZE);
    int i = 7;
    while (command[i] != '\0')
    {
        substr[i - 7] = command[i];
        i++;
    }
    printf("%s\n", substr);
    char *first_name = strtok(substr, " ");
    char *last_name = strtok(NULL, " ");
    char *email = strtok(NULL, " ");
    char *phone_number = strtok(NULL, " ");
    printf("%s %s %s %s\n", first_name, last_name, email, phone_number);
    if (first_name == NULL || last_name == NULL || email == NULL || phone_number == NULL)
    {
        printf("Insufficient number of parameters passed. Expected 4 parameter(s). Use 'pb help' for usage.The phone record could not be added to the phone book.\n");
        return;
    }
    else
    {
        FILE *file = fopen(file_name, "a");
        printf("%s %s %s %s\n", first_name, last_name, email, phone_number);
        fprintf(file, "\n\n\n\n%s\n%s\n%s\n%s\n", first_name, last_name, email, phone_number);
        fclose(file);
        printf("Record added successfully\n");
    }
}

void find_record_from_email(char *command)
{
    char *substr = malloc(sizeof(char) * (strlen(command) - 10 + 1));
    int i = 11;
    int j = 0;
    while (command[i] != '\0')
    {
        substr[j++] = command[i++];
    }
    substr[j] = '\0';
    printf("%s\n", substr);
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        free(substr);
        return;
    }

    char line[MAX_COMMAND_SIZE];
    int num = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (line[0] != '\n' && num % 4 == 2)
        {
            char *email = strtok(line, "\n");
            printf("%s\n", email);
            if (strcmp(email, substr) == 0)
            {
                printf("%s\n", email);
                break;
            }
        }
        num++;
    }
    printf("%d\n", num);
    int num1 = 0;
    rewind(file);
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (line[0] != '\n' && num1 == num - 2)
        {
            char *first_name = strtok(line, "\n");
            printf("First Name: %s\n", first_name);
        }
        else if (line[0] != '\n' && num1 == num - 1)
        {
            char *last_name = strtok(line, "\n");
            printf("Last Name: %s\n", last_name);
        }
        else if (line[0] != '\n' && num1 == num)
        {
            char *email = strtok(line, "\n");
            printf("Email: %s\n", email);
        }
        else if (line[0] != '\n' && num1 == num + 1)
        {
            char *phone_number = strtok(line, "\n");
            printf("Phone number: %s\n", phone_number);
        }
        num1++;
    }

    free(substr);
    fclose(file);
}

void update_records(char *command)
{
    char *substr = malloc(sizeof(char) * (strlen(command) - 10 + 1));
    int i = 10;
    int j = 0;
    while (command[i] != '\0')
    {
        substr[j++] = command[i++];
    }
    substr[j] = '\0';
    printf("%s\n", substr);
    int spaces = 0, k = 0, m = 0;
    char first_name[MAX_COMMAND_SIZE];
    char last_name[MAX_COMMAND_SIZE];
    char email[MAX_COMMAND_SIZE];
    char phone_number[MAX_COMMAND_SIZE];

    while (substr[k] != ' ' && spaces == 0)
    {
        first_name[m++] = substr[k++];
    }
    first_name[m] = '\0';
    spaces++;
    m = 0;
    k++;
    while (substr[k] != ' ' && spaces == 1)
    {
        last_name[m++] = substr[k++];
    }
    last_name[m] = '\0';
    spaces++;
    m = 0;
    k++;
    while (substr[k] != ' ' && spaces == 2)
    {
        email[m++] = substr[k++];
    }
    email[m] = '\0';
    spaces++;
    m = 0;
    k++;
    while (substr[k] != ' ' && spaces == 3)
    {
        phone_number[m++] = substr[k++];
    }
    phone_number[m] = '\0';
    spaces++;
    m = 0;
    k++;
    printf("%s\n %s\n %s\n %s\n", first_name, last_name, email, phone_number);
    m = 0;
    printf("%s\n", email);
    printf("%d\n", strlen(email));
    printf("Extracted Email: %s\n", email);
    printf("Searching for record with email: %s\n", email);
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        free(substr);
        return;
    }

    char line[MAX_COMMAND_SIZE];
    int num = 0;
    int record_found = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s\n", line);
        if (line[0] != '\n')
        {
            char *new_email = strtok(line, "\n");
            if (strcmp(email, new_email) == 0)
            {
                printf("Record found:\n");
                printf("Email: %s\n", new_email);
                record_found = 1;
                break;
            }
        }
        num++;
    }

    if (!record_found)
    {
        printf("Record with email '%s' not found.\n", email);
        free(substr);
        fclose(file);
        return;
    }
    rewind(file);
    FILE *temp_file = fopen("temp_phone_book.txt", "w");

    int current_record = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (line[0] != '\n' && current_record == num - 2)
        {
            fprintf(temp_file, "%s\n", first_name);
        }
        else if (line[0] != '\n' && current_record == num - 1)
        {
            fprintf(temp_file, "%s\n", last_name);
        }
        else if (line[0] != '\n' && current_record == num)
        {
            fprintf(temp_file, "%s\n", email);
        }
        else if (line[0] != '\n' && current_record == num + 1)
        {
            fprintf(temp_file, "%s\n", phone_number);
        }
        else
        {
            fprintf(temp_file, "%s", line);
        }
        current_record++;
    }

    fclose(file);
    fclose(temp_file);

    remove(file_name);
    rename("temp_phone_book.txt", file_name);

    free(substr);
    printf("Record updated successfully.\n");
}

void delete_record(char *command)
{
    char *substr = malloc(sizeof(char) * (strlen(command) - 11 + 1));
    int i = 10;
    int j = 0;
    while (command[i] != '\0')
    {
        substr[j++] = command[i++];
    }
    substr[j] = '\0';

    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        free(substr);
        return;
    }

    FILE *temp_file = fopen("temp_file.txt", "w");
    if (temp_file == NULL)
    {
        perror("Error creating temporary file");
        fclose(file);
        free(substr);
        return;
    }

    char line[MAX_COMMAND_SIZE];
    int num = 0;
    int found = 0;
    printf("%s\n", substr);
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (line[0] != '\n' && num % 4 == 2)
        {
            char *email = strtok(line, "\n");
            if (strcmp(email, substr) == 0)
            {
                found = 1;
                break;
            }
        }
        num++;
    }

    if (!found)
    {
        printf("Record not found for deletion.\n");
        fclose(file);
        fclose(temp_file);
        free(substr);
        remove("temp_file.txt");
        return;
    }

    rewind(file);
    printf("%d\n", num);
    int n = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (line[0] != '\n' && !(n >= num - 2 && n <= num + 1))
        {
            fputs(line, temp_file);
        }
        n++;
    }

    fclose(file);
    fclose(temp_file);

    remove(file_name);
    rename("temp_file.txt", file_name);

    printf("Record deleted successfully.\n");

    free(substr);
}

void find_record_from_first_name(char *command)
{
    ;
}

int main()
{
    char command[MAX_COMMAND_SIZE];

    printf("Phone Book\n");
    printf("Use 'pb help' for usage\n");

    if (fgets(command, MAX_COMMAND_SIZE, stdin) != NULL)
    {
        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n')
        {
            command[len - 1] = '\0';
            if (command[0] == 'p' && command[1] == 'b')
            {
                if (strcmp(command, "pb help") == 0)
                    help();
                else if (strcmp(command, "pb display") == 0)
                    display();
                else if (command[3] == 'a' && command[4] == 'd' && command[5] == 'd')
                    add_record(command);
                else if (command[3] == 'f' && command[4] == 'i' && command[5] == 'n' && command[6] == 'd' && command[7] == ' ' && command[8] == '-' && command[9] == 'e')
                    find_record_from_email(command);
                else if (command[3] == 'u' && command[4] == 'p' && command[5] == 'd' && command[6] == 'a' && command[7] == 't' && command[8] == 'e')
                    update_records(command);
                else if (command[3] == 'd' && command[4] == 'e' && command[5] == 'l' && command[6] == 'e' && command[7] == 't' && command[8] == 'e')
                    delete_record(command);
                else if (strcmp(command, "pb find -n") == 0)
                    find_record_from_first_name(command);
                else if (strcmp(command, "pb exit") == 0)
                    return 0;
                else
                {
                    printf("Invalid Command\n");
                    return 0;
                }
            }
            else
            {
                printf("Invalid Command\n");
                return 0;
            }
        }
    }
    return 0;
}
