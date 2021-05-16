#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//struct for record
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

//struct for tag all string
struct tags
{
    char name[32];      //utf16
    char surname[32];   //utf8
    char gender[32];
    char email[32];
    char phone_number[32];
    char address[32];
    char level_of_education[32];
    char income_level[32];  // given little-endian
    char expenditure[32];   // given big-endian
    char currency_unit[32];
    char currentMood[32];
    char height[32];
    char weight[32];
};

//function that converts little endian and big endian
unsigned int reverseEndian(unsigned int val)
{
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return((unsigned int) val << 16) | ((unsigned int) val >> 16);
}

int num = 50;

int main();

struct record *readFile(char path[]);

struct tags *readFile1(char path[]);

int main(int argc, char* argv[]) {
    printf("succesfull");

    //create xml file
    FILE *fp = fopen(argv[2], "w");
    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    struct record *records = readFile(argv[1]);
    struct tags *tag = readFile1(argv[1]);
    fprintf(fp, "\t%s","<records>\n");
    for(int i = 1; i < 51; i++){
        unsigned int reversedIncomeLevel = (unsigned int) reverseEndian(records[i].income_level);
        unsigned int reversedExpenditure = (unsigned int) reverseEndian(records[i].expenditure);
        fprintf(fp, "\t\t<row id = %c%d%c>\n", 34,(i),34);
        fprintf(fp, "\t\t\t<%s>%s</%s>\n\t\t\t<%s>%s</%s>\n\t\t\t<%s>%c</%s>\n\t\t\t<%s>%s</%s>\n"
        "\t\t\t<%s>%s</%s>\n\t\t\t<%s>%s</%s>\n\t\t\t<%s>%s</%s>\n\t\t\t<%s%s%c%u%c>%u</%s>\n\t\t\t<%s%s%c%u%c>%u</%s>\n"
        "\t\t\t<%s>%s</%s>\n\t\t\t<%s>%s</%s>\n\t\t\t<%s>%f</%s>\n\t\t\t<%s>%u</%s>\n",
        tag->name, records[i].name, tag->name,
        tag->surname, records[i].surname, tag->surname,
        tag->gender, records[i].gender, tag->gender,
        tag->email, records[i].email, tag->email,
        tag->phone_number, records[i].phone_number, tag->phone_number,
        tag->address, records[i].address, tag->address,
        tag->level_of_education, records[i].level_of_education, tag->level_of_education,
        tag->income_level, " bigEnd=", 34, reversedIncomeLevel, 34, records[i].income_level, tag->income_level,
        tag->expenditure, " bigEnd=", 34,records[i].expenditure, 34,reversedExpenditure, tag->expenditure,
        tag->currency_unit, records[i].currency_unit, tag->currency_unit,
        tag->currentMood, records[i].currentMood, tag->currentMood,
        tag->height, records[i].height, tag->height,
        tag->weight, records[i].weight, tag->weight
        );
        fprintf(fp, "\t\t</row>\n");
    }
    fprintf(fp, "\t%s", "</records>");
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
        if(i != 0){
        recs[i] = rec;
        }
    }
    fclose(binFile);
    return recs;
}

struct tags *readFile1(char path[])
{
    struct tags *tag = calloc(101, sizeof(struct tags));   
    FILE *binFile;
    binFile = fopen(path, "rb");
    if(binFile == NULL)
    {
        printf("File not found exceptioné Cannot find source file.");
        exit(1);
        return tag;
    }
    fread(tag, sizeof(struct tags), 1, binFile);
    fclose(binFile);
    strcpy(tag->gender, "gender");
    strcpy(tag->email, "email");
    strcpy(tag->surname, "surname");
    strcpy(tag->phone_number, "phone_number");
    strcpy(tag->address, "address");
    strcpy(tag->level_of_education, "level_of_education");
    strcpy(tag->income_level, "income_level");
    strcpy(tag->expenditure, "expenditure");
    strcpy(tag->currency_unit, "currency_unit");
    strcpy(tag->currentMood, "currentMood");
    strcpy(tag->height, "height");
    strcpy(tag->weight, "weight");

    return tag;
}
