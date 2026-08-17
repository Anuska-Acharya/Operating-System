#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    int opt;
    char line[100];

    printf("\n1. List Files");
    printf("\n2. Present Working Directory");
    printf("\n3. Display ch.c");
    printf("\n4. Exit");

    printf("\n\nEnter your choice: ");
    scanf("%d", &opt);

    switch (opt)
    {
    case 1:
        printf("\nList Command\n");
        printf("************\n");

        fp = popen("ls", "r");
        if (fp == NULL)
        {
            printf("Pipeline Error\n");
            return 1;
        }

        while (fgets(line, sizeof(line), fp) != NULL)
        {
            printf("%s", line);
        }

        pclose(fp);
        break;

    case 2:
        printf("\nPWD Command\n");
        printf("***********\n");

        fp = popen("pwd", "r");
        if (fp == NULL)
        {
            printf("Pipeline Error\n");
            return 1;
        }

        while (fgets(line, sizeof(line), fp) != NULL)
        {
            printf("%s", line);
        }

        pclose(fp);
        break;

    case 3:
        printf("\nCAT Command\n");
        printf("***********\n");

        fp = popen("cat ch.c", "r");

        if (fp == NULL)
        {
            printf("Unable to open ch.c\n");
            return 1;
        }

        while (fgets(line, sizeof(line), fp) != NULL)
        {
            printf("%s", line);
        }

        pclose(fp);
        break;

    case 4:
        printf("Exit\n");
        exit(0);

    default:
        printf("Invalid Choice\n");
    }

    return 0;
}