#include "./structuri.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clean_name(char *string)
{
    int i, l;
    l = strlen(string);
    for (i = 0; i < l; i++)
    {
        if (string[i] == '\n' || string[i] == '\r' || string[i] == '\t')
        {
            string[i] = '\0';
        }
    }
}

struct list *define_list()
{
    struct list *l;
    l = (struct list *)malloc(sizeof(struct list));
    l->size = 0;
    l->head = NULL;
    l->tail = NULL;
    return l;
}

struct song *create_song(union record meta, char *nume)
{
    struct song *m;
    m = (struct song *)malloc(sizeof(struct song));
    m->metadata = meta;
    m->nume = nume;
    m->next = NULL;
    m->prev = NULL;
    return m;
}

union record get_meta(char *filename)
{
    FILE *f;
    union record meta;
    f = fopen(filename, "rb");
    fseek(f, -ID3_SIZE, SEEK_END);
    fread(meta.data, ID3_SIZE, 1, f);
    fclose(f);
    return meta;
}

struct song *find_song(struct list *l, char data[ID3_SIZE])
{
    /*
        functia intoarce pointer la melodia gasita
        sau NULL, care va fi folosit ca sa se afiseze mesaje/steagra elementele
    */
    struct song *c;
    int i;
    if (l->size == 0)
    {
        return NULL;
    }
    c = l->head;
    for (i = 0; i < l->size; i++)
    {
        if (strncmp(data, c->metadata.data, ID3_SIZE - 1) == 0)
        {
            return c;
        }
        c = c->next;
    }
    return NULL;
}

void free_song(struct song *m)
{
    free(m);
    return;
}
void free_list(struct list *l)
{
    struct song *c, *d;
    int i;
    if (l->size == 0)
    {
        free(l);
        return;
    }
    c = l->head;
    for (i = 0; i < l->size; i++)
    {
        d = c;
        c = c->next;
        free_song(d);
    }
    free(l);
    return;
}