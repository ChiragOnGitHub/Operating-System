#include <stdio.h>
#include <fcntl.h>  // to use integer constant in open()
#include <stdlib.h> // to use exit() function

int main()
{

    char sourceFileName[50], destinationFileName[50];
    int fdSourceFile, fdDestinationFile;
    char bufferChar;

    printf("Enter path of the source file : ");
    scanf("%s", &sourceFileName);

    printf("Enter path of the destination file : ");
    scanf("%s", &destinationFileName);

    fdSourceFile = open(sourceFileName, O_RDONLY);
    fdDestinationFile = open(destinationFileName, O_CREAT | O_WRONLY | O_TRUNC);

    if (fdSourceFile < 0 || fdDestinationFile < 0)
    {
        printf("Error while opening file ");
        exit(-1);
    }

    // Enter content from source file to destination file character by character
    //  until EOF reached as at that time read() return 0
    while (read(fdSourceFile, &bufferChar, sizeof(char)) > 0)
    {
        write(fdDestinationFile, &bufferChar, sizeof(char));
    }

    printf("\nContent of file  '%s' is successfully copied in the file '%s' ", sourceFileName, destinationFileName);

    close(fdSourceFile);
    close(fdDestinationFile);
    return 0;
}