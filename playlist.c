#include "./structuri.h"
#include "./playlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void add_first(struct list *l, struct song *m, struct song **curs, FILE *output)
{
    struct song *del;
    if (l->head == NULL)
    {
        /* l->size==0 */
        l->head = m;
        l->tail = m;
        l->head->next = NULL;
        l->tail->next = NULL;
        l->head->prev = NULL;
        l->tail->prev = NULL;
        l->size++;
        (*curs) = m;
        return;
    }
    if (find_song(l, m->metadata.data))
    {
        /* este in lista, deci clar size>0 */
        del = remove_song(l, m, curs, output);
        free_song(del);
    }
    m->next = l->head;
    l->head->prev = m;
    l->head = m;
    m->prev = NULL;
    l->size++;
    return;
}

void add_last(struct list *l, struct song *m, struct song **curs, FILE *output)
{
    struct song *del;
    if (l->head == NULL)
    {
        /* l->size==0 */
        l->head = m;
        l->tail = m;
        l->head->next = NULL;
        l->tail->next = NULL;
        l->head->prev = NULL;
        l->tail->prev = NULL;
        l->size++;
        (*curs) = m;
        return;
    }
    if (find_song(l, m->metadata.data))
    {
        /* este in lista, deci clar size>0 */
        del = remove_song(l, m, curs, output);
        free_song(del);
    }
    m->prev = l->tail;
    l->tail->next = m;
    l->tail = m;
    m->next = NULL;
    l->size++;
    return;
}
void add_after(struct list *l, struct song *m, struct song **curs, FILE *output)
{
    struct song *s, *del;
    if ((*curs) == NULL)
    {
        free_song(m);
        return;
    }
    s = find_song(l, m->metadata.data);
    if (s)
    {
        /* este in lista, deci clar size>0 */
        if (*curs == s)
        {
            free_song(m);
            return;
        }
        del = remove_song(l, m, curs, output);
        free_song(del);
    }
    if (l->tail == (*curs))
    {
        add_last(l, m, curs, output);
        return;
    }
    m->next = (*curs)->next;
    m->prev = (*curs);
    (*curs)->next->prev = m;
    (*curs)->next = m;
    l->size++;
    return;
}

struct song *remove_first(struct list *l, struct song **curs, FILE *output)
{
    struct song *current;
    if (l->head == NULL)
    {
        fprintf(output, "Error: delete from empty playlist\n");
        return NULL;
    }
    current = l->head;
    if (l->head == l->tail)
    {
        l->head = NULL;
        l->tail = NULL;
        l->size--;
        (*curs) = NULL;
        return current;
    }
    if ((*curs) == l->head)
        (*curs) = l->head->next;
    l->head = l->head->next;
    l->head->prev = NULL;
    l->size--;
    return current;
}

struct song *remove_last(struct list *l, struct song **curs, FILE *output)
{
    struct song *current;
    if (l->tail == NULL)
    {
        fprintf(output, "Error: delete from empty playlist\n");
        return NULL;
    }
    current = l->tail;
    if (l->tail == l->head)
    {
        l->tail = NULL;
        l->head = NULL;
        l->size--;
        (*curs) = NULL;
        return current;
    }
    if ((*curs) == l->tail)
        (*curs) = l->tail->prev;
    l->tail = l->tail->prev;
    l->tail->next = NULL;
    l->size--;
    return current;
}

struct song *remove_curr(struct list *l, struct song **curs, FILE *output)
{
    struct song *c;
    if ((*curs) == NULL)
    {
        fprintf(output, "Error: no track playing\n");
        return NULL;
    }
    c = (*curs);
    if (c == l->head)
    {
        remove_first(l, curs, output);
    }
    else if (c == l->tail)
    {
        remove_last(l, curs, output);
    }
    else
    {
        c->prev->next = c->next;
        c->next->prev = c->prev;
        l->size--;
        (*curs) = c->next;
        if ((*curs) == NULL)
            (*curs) = c->prev;
    }
    return c;
}

struct song *remove_song(struct list *l, struct song *m, struct song **curs, FILE *output)
{
    struct song *c;
    if (m == NULL)
    {
        fprintf(output, "Error: no song found to delete\n");
        return NULL;
    }
    if (l->size == 0)
    {
        fprintf(output, "Error: delete from empty playlist\n");
        return NULL;
    }
    c = find_song(l, m->metadata.data);

    if (c == l->head)
    {
        remove_first(l, curs, output);
    }
    else if (c == l->tail)
    {
        remove_last(l, curs, output);
    }
    else
    {
        c->prev->next = c->next;
        c->next->prev = c->prev;
        l->size--;
    }
    if ((*curs) == c)
    {
        (*curs) = c->next;
        if ((*curs) == NULL)
            (*curs) = c->prev;
    }
    return c;
}

void move_next(struct list *l, struct song **curs, FILE *output)
{
    if ((*curs) == NULL)
    {
        fprintf(output, "Error: no track playing\n");
    }
    if ((*curs) != l->tail)
        (*curs) = (*curs)->next;
    return;
}
void move_prev(struct list *l, struct song **curs, FILE *output)
{
    if ((*curs) == NULL)
    {
        fprintf(output, "Error: no track playing\n");
    }
    if ((*curs) != l->head)
        (*curs) = (*curs)->prev;
    return;
}

void show_first(struct list *l, FILE *output)
{
    struct song *s;
    s = l->head;
    if (s == NULL)
    {
        fprintf(output, "Error: show empty playlist\n");
        return;
    }

    fprintf(output, "Title: %.*s\n", 30, s->metadata.id3.titlu);
    fprintf(output, "Artist: %.*s\n", 30, s->metadata.id3.artist);
    fprintf(output, "Album: %.*s\n", 30, s->metadata.id3.album);
    fprintf(output, "Year: %.*s\n", 4, s->metadata.id3.an);
    return;
}

void show_last(struct list *l, FILE *output)
{
    struct song *s;
    s = l->tail;
    if (s == NULL)
    {
        fprintf(output, "Error: show empty playlist\n");
        return;
    }

    fprintf(output, "Title: %.*s\n", 30, s->metadata.id3.titlu);
    fprintf(output, "Artist: %.*s\n", 30, s->metadata.id3.artist);
    fprintf(output, "Album: %.*s\n", 30, s->metadata.id3.album);
    fprintf(output, "Year: %.*s\n", 4, s->metadata.id3.an);
    return;
}
void show_curr(struct song **curs, FILE *output)
{
    struct song *s;
    s = (*curs);
    if (s == NULL)
    {
        fprintf(output, "Error: show empty playlist\n");
        return;
    }

    fprintf(output, "Title: %.*s\n", 30, s->metadata.id3.titlu);
    fprintf(output, "Artist: %.*s\n", 30, s->metadata.id3.artist);
    fprintf(output, "Album: %.*s\n", 30, s->metadata.id3.album);
    fprintf(output, "Year: %.*s\n", 4, s->metadata.id3.an);
    return;
}

void show_playlist(struct list *l, FILE *output)
{
    struct song *c;
    int i;
    if (l->size == 0)
    {
        fprintf(output, "[]\n");
        return;
    }
    c = l->head;
    fprintf(output, "[%.*s", 30, c->metadata.id3.titlu);
    c = c->next;
    for (i = 1; i < l->size; i++)
    {

        fprintf(output, "; %.*s", 30, c->metadata.id3.titlu);
        c = c->next;
    }
    fprintf(output, "]\n");
    return;
}