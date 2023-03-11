/* list.h */

typedef struct NODE {
    char* value;
    struct NODE *next;
} Node;

typedef Node** List;

List new_list();
List load_list(char* fileName);
List copy_list(List list);
List sublist(List list, int start, int end);

void clear(List list);
void push(List list, char* value);
void add(List list, char* value);
void print_list(List list);

char* pop(List list);
char* peek(List list);
char* rem(List list);
char* get_at(List list, int index);
char* remove_at(List list, int index);

int index_of(List list, char* value);
int index_of_alias(List list, char* value);
int contains(List list, char* value);
int contains_alias(List list, char* value);
int replace_at(List list, int index, char* value);
int insert_at(List list,int index, char* value);
int save_list(List list, char* fileName);
int is_empty(List list);
int size(List list);
