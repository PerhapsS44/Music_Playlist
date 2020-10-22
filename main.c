/*
Copyright 2020 Stefan Saraev 312CA
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./structuri.h"
#include "./playlist.h"

void process(char *comm, char *song, struct list *l,
             struct song **curs, FILE *output)
{
    struct song *new, *del;
    union record meta;
    if (strcmp(comm, "ADD_FIRST") == 0)
    {
        meta = get_meta(song);
        new = create_song(meta, song);
        add_first(l, new, curs, output);
    }
    if (strcmp(comm, "ADD_LAST") == 0)
    {
        meta = get_meta(song);
        new = create_song(meta, song);
        add_last(l, new, curs, output);
    }
    if (strcmp(comm, "ADD_AFTER") == 0)
    {
        meta = get_meta(song);
        new = create_song(meta, song);
        add_after(l, new, curs, output);
    }
    if (strcmp(comm, "DEL_FIRST") == 0)
    {
        del = remove_first(l, curs, output);
        free_song(del);
    }
    if (strcmp(comm, "DEL_LAST") == 0)
    {
        del = remove_last(l, curs, output);
        free_song(del);
    }
    if (strcmp(comm, "DEL_CURR") == 0)
    {
        del = remove_curr(l, curs, output);
        free_song(del);
    }
    if (strcmp(comm, "DEL_SONG") == 0)
    {
        struct song *m;
        meta = get_meta(song);
        m = find_song(l, meta.data);
        del = remove_song(l, m, curs, output);
        free_song(del);
    }
    if (strcmp(comm, "MOVE_NEXT") == 0)
    {
        move_next(l, curs, output);
    }
    if (strcmp(comm, "MOVE_PREV") == 0)
    {
        move_prev(l, curs, output);
    }
    if (strcmp(comm, "SHOW_FIRST") == 0)
    {
        show_first(l, output);
    }
    if (strcmp(comm, "SHOW_LAST") == 0)
    {
        show_last(l, output);
    }
    if (strcmp(comm, "SHOW_CURR") == 0)
    {
        show_curr(curs, output);
    }
    if (strcmp(comm, "SHOW_PLAYLIST") == 0)
    {
        show_playlist(l, output);
    }
}

int main(int argc, char *argv[])
{
    struct list *playlist;
    struct song *cursor;
    FILE *input, *output;
    char command[20], song_name[100], song[120];
    int no_commands, i;
    playlist = define_list();
    cursor = NULL;
    if (argc != 3)
    {
        printf("Nu sunt date ca parametrii fisierele de in/out!\n");
        return -1;
    }
    input = fopen(argv[1], "rt");
    output = fopen(argv[2], "wt");
    fscanf(input, " %d ", &no_commands);
    for (i = 0; i < no_commands; i++)
    {
        fscanf(input, "%s ", command);
        if (command[0] == 'A' || strcmp(command, "DEL_SONG") == 0)
        {
            fgets(song_name, 100, input);
            clean_name(song_name);
            snprintf(song, sizeof(song), "./songs/%s", song_name);
        }
        process(command, song, playlist, &cursor, output);
    }
    free_list(playlist);
    fclose(output);
    fclose(input);
    return 0;
}
