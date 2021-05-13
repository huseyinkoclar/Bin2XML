#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct record
{
    char name[64];      //utf16
    char surname[32];   //utf8
    char gender;
    char email[32];
    char phone_number[16];
    char address[32];
    char level_of_education[8];
    unsigned int income_level;  // given little-endian
    unsigned int expenditure;   // given big-endian
    char currency_unit[16];
    char currentMood[32];
    float height;
    unsigned int weight;
};

struct header
{
    char name[64];      //utf16
    char surname[32];   //utf8
    char gender;
    char email[32];
    char phone_number[16];
    char address[32];
    char level_of_education[8];
    unsigned int income_level;  // given little-endian
    unsigned int expenditure;   // given big-endian
    char currency_unit[16];
    char currentMood[32];
    float height;
    unsigned int weight;
};

int num = 51;

int main();

struct record *readFile(char path[]);

int main(int argc, char const argv[]) {
    printf("hello assignment");

    FILE *fp = fopen("Bin2XML.xml", "w");
    struct record *records = readFile("./records.dat");
    fprintf(fp, "%s","<records>\n");
    for(int i = 1; i < 51; i++){
        fprintf(fp, "\trow id = %d\n", (i));
        fprintf(fp, "\t\t<%s>%s</%s>\n\t\t<%s>%s</%s>\n\t\t<%c>%c</%c>\n\t\t<%s>%s</%s>\n"
        "\t\t<%s>%d</%s>\n\t\t<%s>%s</%s>\n\t\t<%s>%s</%s>\n\t\t<%s>%d</%s>\n\t\t<%s>%d</%s>\n"
        "\t\t<%s>%s</%s>\n\t\t<%s>%s</%s>\n\t\t<%s>%d</%s>\n\t\t<%s>%d</%s>\n",
        records[0].name, records[i].name, records[0].name,
        records[0].surname, records[i].surname, records[0].surname,
        records[0].gender, records[i].gender, records[0].gender,
        records[0].email, records[i].email, records[0].email,
        records[0].phone_number, records[i].phone_number, records[0].phone_number,
        records[0].address, records[i].address, records[0].address,
        records[0].level_of_education, records[i].level_of_education, records[0].level_of_education,
        records[0].income_level, records[i].income_level, records[0].income_level,
        records[0].expenditure, records[i].expenditure, records[0].expenditure,
        records[0].currency_unit, records[i].currency_unit, records[0].currency_unit,
        records[0].currentMood, records[i].currentMood, records[0].currentMood,
        records[0].height, records[i].height, records[0].height,
        records[0].weight, records[i].weight, records[0].weight
        );
    }
    fprintf(fp, "%s", "records");
    printf("sasasa");
    return 0;    
}

struct record *readFile(char path[])
{
    struct record *recs = calloc(51, sizeof(struct record));
    FILE *binFile;
    binFile = fopen(path, "rb");
    if(binFile == NULL)
    {
        printf("File not found exceptioné Cannot find source file.");
        exit(1);
        return recs;
    }
    struct record rec;
    for(int i = 0; i < 51; i++){
        fread(&rec, sizeof(struct record), 1, binFile);
        recs[i] = rec;
    }
    fclose(binFile);
    return recs;
}