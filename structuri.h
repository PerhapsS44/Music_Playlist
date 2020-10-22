#ifndef __STRUCTURI__
#define __STRUCTURI__
#define ID3_SIZE 97
union record {
    char data[ID3_SIZE];
    struct ID3
    {
        char antet[3];
        char titlu[30];
        char artist[30];
        char album[30];
        char an[4];
    } id3;
};

struct song
{
    char *nume;
    union record metadata;
    struct song *next;
    struct song *prev;
};

struct list
{
    struct song *head;
    struct song *tail;
    int size;
};

void clean_name(char *string);
struct list *define_list();
union record get_meta();
struct song *create_song(union record meta, char *nume);

struct song *find_song(struct list *l, char data[ID3_SIZE]);
/*
    TODO:
*/

void free_song(struct song *m);
void free_list(struct list *l);
#endif