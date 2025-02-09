#include <stdio.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>

int statistics(FILE *input_file, FILE *output_file);
int sentence_end(char character);
int word_end(char character);

int main(void)
{
    char input_file[32];
    char output_file[32];

    printf("Enter the name of the input file (must be the same as created): \n");
    if (scanf("%31s", input_file) != 1 || input_file[0] == '\0')
    {
        printf("Error loading!\n");
        return 1;
    }

    printf("Enter the name of the output file: \n");
    if (scanf("%31s", output_file) != 1 || output_file[0] == '\0')
    {
        printf("Error loading!\n");
        return 1;
    }

    FILE *fr = fopen(input_file, "r");
    if (fr == NULL)
    {
        perror("Error opening file for reading\n");
        return 1;
    }
    else
    {
        printf("File %s was opened for reading\n", input_file);
    }

    FILE *fw = fopen(output_file, "w");
    if (fw == NULL)
    {
        perror("Error opening output file for writing.\n");
        fclose(fr);
        return 1;
    }

    statistics(fr, fw);

    fclose(fr);
    fclose(fw);

    return 0;
}

int sentence_end(char character)
{
    return character == '?' || character == '!' || character == '.';
}

int word_end(char character)
{
    return sentence_end(character) || character == ' ' || character == '\n' || character == ',' || character == ';';
}

int statistics(FILE *input_file, FILE *output_file)
{
    int line_counter = 0;
    int word_counter = 0;
    int sentence_counter = 0;
    int word_index = 0;
    int line_ended = 0;
    char character;
    char *word;
    size_t word_size = 16;

    if ((word = (char*) malloc(word_size * sizeof(char))) == NULL)
    {
        printf("Not enough memory!\n");
        return 1;
    }
    while ((character = getc(input_file)) != EOF)
    {

        if (isalnum(character))
        {
            if(word_index >= word_size - 1)
            {
                word_size *= 2;
                char* new_word = (char*) realloc(word, word_size * sizeof(char));
                if (new_word == NULL)
                {
                    free(word);
                    printf("Reallocation failed!\n");
                    return 1;
                }
                word = new_word;
            }
            word[word_index++] = character;
            continue;
        }
        if (word_end(character) && word_index > 0)
        {
            word_counter++;

            if (sentence_end(character))
            {
                sentence_counter++;
            }
            word[word_index] = '\0';

            printf("Word %d: %s\n", word_counter, word);

            word_index = 0;
        }

        if (character == '\n' )
        {
            line_counter++;
            line_ended = 1;
        }
        else
        {
            line_ended = 0;
        }
    }
    if (word_index > 0 || line_ended == 0)
    {
        line_counter++;
    }

    fprintf(output_file, "Number of lines: %d\n", line_counter);
    fprintf(output_file, "Number of words: %d\n", word_counter);
    fprintf(output_file, "Number of sentences: %d\n", sentence_counter);

    free((void*)word);
    word = NULL;

    return 0;
}
