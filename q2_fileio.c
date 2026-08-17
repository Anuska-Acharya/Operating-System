#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    int i = 0;
    int f1, f2;
    char c, strin[100];

    f1 = open("data", O_RDWR | O_CREAT | O_TRUNC, 0644);

    printf("Enter a string: ");

    while ((c = getchar()) != '\n')
    {
        strin[i++] = c;
    }

    strin[i] = '\0';

    write(f1, strin, i);
    close(f1);

    f2 = open("data", O_RDONLY);

    read(f2, strin, i);
    strin[i] = '\0';

    printf("\nContents of file: %s\n", strin);

    close(f2);

    return 0;
}