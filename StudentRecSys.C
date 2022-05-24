#include <stdio.h>
#include <cstring>
#include <unistd.h>

struct StudentData
{
    char id[30];
    char name[30];
    float cgpa;
};

    StudentData *dataListPointer[100];
    StudentData dataListArr[100];
    

void writeInFile()
{
    FILE *fpointer = fopen("studentPointerFile.data", "wb");
    fwrite(dataListPointer, sizeof(StudentData), sizeof(dataListPointer), fpointer);
    fclose(fpointer);

    FILE *fpointer2 = fopen("studentDataFile.data", "wb");
    fwrite(dataListArr, sizeof(StudentData), sizeof(dataListArr), fpointer2);
    fclose(fpointer2);
}

void readFromFile()
{
    FILE *fpointer = fopen("studentPointerFile.data", "rb");
    fread(dataListPointer, sizeof(StudentData), sizeof(dataListPointer), fpointer);
    fclose(fpointer);

    FILE *fpointer2 = fopen("studentDataFile.data", "rb");
    fread(dataListArr, sizeof(StudentData), sizeof(dataListArr), fpointer2);
    fclose(fpointer2);
}

void showAllStudent()
{
    bool flag = false;
    printf("\n_____All Students_____\n");
    for(int i=0; i<100; i++)
    {
        if(dataListPointer[i] != NULL)
        {
            printf("\nId: %s" , dataListArr[i].id);
            printf(" Name: %s" , dataListArr[i].name);
            printf(" CGPA: %f\n" , dataListArr[i].cgpa);
            flag = true;
        }
    }
    if (!flag)
    {
        printf("\nStudent list empty!\n");
    }
    
}

bool addStudent()
{
    bool flag = false;
    for(int i=0; i<100; i++)
    {
        if(dataListPointer[i] == NULL)
        {
            printf("\nEnter ID:");
            scanf("%s", dataListArr[i].id);
            printf("\nEnter Name:");
            scanf("%s", dataListArr[i].name);
            printf("\nEnter CGPA:");
            scanf("%f", &dataListArr[i].cgpa);
            dataListPointer[i] = &dataListArr[i];
            flag = true;
            break;
        }
    }
    return flag;
}

bool remStudent()
{
    bool flag = false;
    char checkId[30];
    printf("\nEnter ID:");
    scanf("%s", checkId);
    for(int i=0; i<100; i++)
    {
        if(dataListPointer[i] != NULL)
        {
            if(strcmp(dataListArr[i].id, checkId) == 0)
            {
                dataListPointer[i] = NULL;
                flag = true;
                break;
            }
        }
    }
    return flag;
}

int main()
{
    printf("\n*****Student Record System*****\n");

    int choice = 0;
    bool run = true;

    if( access( "studentPointerFile.data", F_OK ) != -1)
    {
        readFromFile();
    }
    else
    {
        for(int i=0; i<100; i++)
        {
            dataListPointer[i] = NULL;
        }
        writeInFile();
    }

    while(run)
    {
        printf("\n-------------Menu---------------\n");
        printf("\n1.All Students\n");
        printf("2.New Student\n");
        printf("3.Remove Student\n");
        printf("4.Exit Program\n");
        printf("Choice:");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            showAllStudent();
            break;

        case 2:
            if(addStudent())
            {
                printf("\nStudent added!\n");
            }
            else
            {
                printf("\nError while adding student!\n");
            }
            break;

        case 3:
            if(remStudent())
            {
                printf("\nStudent removed!\n");
            }
            else
            {
                printf("\nStudent id not found!\n");
            }
            break;

        case 4:
            run = false;
            writeInFile();
            printf("Exitting...\n");
            break;
        
        default:
            printf("\nWrong Choice!\n");
            break;
        }
    }
    
    return 0;
}