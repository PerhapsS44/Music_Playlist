#ifndef __PLAYLIST__
#define __PLAYLIST__
#include <stdio.h>
/*
 functiile de baza din programul meu, care
 vor realiza cerintele temei
*/

void add_first(struct list *l, struct song *m, struct song **curs, FILE *output);
void add_last(struct list *l, struct song *m, struct song **curs, FILE *output);
void add_after(struct list *l, struct song *m, struct song **curs, FILE *output);

struct song *remove_first(struct list *l, struct song **curs, FILE *output);
struct song *remove_last(struct list *l, struct song **curs, FILE *output);
struct song *remove_curr(struct list *l, struct song **curs, FILE *output);
struct song *remove_song(struct list *l, struct song *m, struct song **curs, FILE *output);

void move_next(struct list *l, struct song **curs, FILE *output);
void move_prev(struct list *l, struct song **curs, FILE *output);

void show_playlist(struct list *l, FILE *output);
void show_first(struct list *l, FILE *output);
void show_last(struct list *l, FILE *output);
void show_curr(struct song **curs, FILE *output);
/*
 TODO:
 -- sa testez functiile
 -- sa rulez testele oficiale
*/

#endif