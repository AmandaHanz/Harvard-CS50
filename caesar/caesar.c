#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //check there is no command line arguement
    if (argc != 2)
    {
        printf("Usage: ./caesar  key\n");
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); i++) //checking input is a digit
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar  key\n");
            return 1;
        }
    }

    int k = atoi(argv[1]); //convert key to integer

    string plaintext = get_string("Plaintext: "); //get plaintext from user
    printf("Ciphertext: ");

    for (int j = 0; j < strlen(plaintext); j++) //obtain ciphertext
    {
        if (isupper(plaintext[j]))
        {
            printf("%C", (plaintext[j] - 65 + k) % 26 + 65);
        }

        else if (islower(plaintext[j]))
        {
            printf("%C", (plaintext[j] - 97 + k) % 26 + 97);
        }

        else
        {
            printf("%C", plaintext[j]);
        }
    }
    printf("\n");
}
