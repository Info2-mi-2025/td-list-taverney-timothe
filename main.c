#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ne pas modifier
void init_file()
{
    // data.txt
    FILE* f = fopen("data.txt", "w");
    if (f)
    {
        fprintf(f, "5\n12\n8\n1\n19\n");
        fclose(f);
    }

    // data2.txt
    f = fopen("data2.txt", "w");
    if (f)
    {
        fprintf(f, "10\n20\n30\n");
        fclose(f);
    }

    // data3.txt
    f = fopen("data3.txt", "w");
    if (f)
    {
        fprintf(f, "1\n2\n3\n4\n5\n");
        fclose(f);
    }

    // data_vide.txt
    f = fopen("data_vide.txt", "w");
    if (f)
    {
        fclose(f);  // fichier vide
    }
}



typedef struct Node
{
    int value;
    struct Node* next;
} Node;

typedef struct
{
    Node* head;
    Node* tail;
} List;

// Fonctions de base
void append(List* list, int value)
{
    if(list == NULL) exit(3);

    Node* n = malloc(sizeof(Node));
    if(n == NULL) exit(3);

    n->value = value;
    n->next = NULL;

    if(list->head == NULL){
        list->head = n;
        list->tail = n;
    }
    else{
        n->next = list->head;
        list->head = n;
    }
}

void free_list(List* list)
{
    if(list->head == NULL) return;

    Node* n_tmp = list->head;
    while(list->head != list->tail){
        list->head = list->head->next;
        free(n_tmp);
        n_tmp = list->head;
    }
    free(list->head);
    list->head = NULL;
    list->tail = NULL;
}

void print_list(const List* list)
{
    if(list->head == NULL) return;

    printf("Liste :");
    Node* current = list->head;
    do{
        printf(" %d ->", current->value);
        current = current->next;
    }while(current != list->tail);
    printf(" %d\n", current->value);
}

void reverse_list(List* list)
{
    printf("Reverse list\n");

}

int sum_list(const List* list)
{
    printf("Sum list\n");
    return 0;
}

int min_list(const List* list)
{
    printf("Min list\n");
    return 0;
}

int max_list(const List* list)
{
    printf("max list\n");
    return 0;
}

void filter_list(List* list, int threshold)
{
    printf("Filter list %d\n", threshold);
}

void version()
{
    printf("version 1.0\n");
}

void help()
{
    printf("Utilisation : ./app <fichier> [options]\n\n");
    printf("Options disponibles :\n");
    printf("  --reverse         Inverse l'ordre des éléments\n");
    printf("  --sum             Affiche la somme des éléments\n");
    printf("  --filter <val>    Filtre les éléments >= val\n");
    printf("  --add <val>       Ajoute une valeur à la fin du fichier\n");
    printf("  --help            Affiche ce message d'aide\n");
    printf("  --version, -v     Affiche la version du programme\n");
    printf("  --min             Affiche la valeur minimale de la liste\n");
    printf("  --max             Affiche la valeur maximale de la liste\n");
}

// Lecture fichier
bool read_file(const char* filename, List* list)
{
    FILE* f = fopen(filename, "r");
    if (!f) return false;
    int value;
    
    while (fscanf(f, "%d", &value) == 1) append(list, value);
    
    fclose(f);
    return true;
}

bool add_to_file(const char* filename, int value)
{
    FILE* f = fopen(filename, "a");
    if (!f) return false;
    fprintf(f, "%d\n", value);
    fclose(f);
    return true;
}

void handle_options(int argc,char* argv[], List* list)
{
    int value = 0;

    for(int i = 2; i < argc; i++)
    {
        if(strcmp(argv[i], "--help") == 0)
        {
            help();
        }
        else if(strcmp(argv[i],"--version") == 0 || strcmp(argv[i],"-v") == 0)
        {
            version();
        }
        else if(strcmp(argv[i],"--reverse") == 0)
        {
            reverse_list(list);
        }
        else if(strcmp(argv[i],"--sum") == 0)
        {
            sum_list(list);
        }
        else if(strcmp(argv[i],"--min") == 0)
        {
            min_list(list);
        }
        else if(strcmp(argv[i],"--max") == 0)
        {
            max_list(list);
        }
        else if(sscanf(argv[i],"--filter%d", &value))
        {
            filter_list(list, value);
        }
        else if(sscanf(argv[i],"--add%d", &value))
        {
            add_to_file(argv[1], value);
        }
        else exit(1);
    }
}

int main(int argc, char* argv[])
{
    // Ne pas modifier
    init_file();
    // ---------------
    
    if(argc < 2) return 1;
    FILE* f = fopen(argv[1], "r");
    if(f == NULL) exit(2);
    fclose(f);

    List list = {0};
    read_file(argv[1], &list);

    if(argc == 2){
        print_list(&list);
    }
    else{
        handle_options(argc, argv, &list);
    }
    
    return 0;
}