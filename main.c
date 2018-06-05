#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


struct lego {
    int no_nodes;
    int init;
    int *adj_matrix;
};

struct piece{
    int info;
    struct piece *next;
};

void set_adj_matrix_value(struct lego *graph, int row_index, int column_index, int element_value){
    int position;

    assert(row_index < graph->no_nodes);
    assert(column_index < graph->no_nodes);
    position = row_index * graph->no_nodes + column_index;
    *(graph->adj_matrix + position) = element_value;
}

int get_adj_matrix_value(struct lego *graph, int row_index, int column_index) {
    int position;

    assert(row_index < graph->no_nodes);
    assert(column_index < graph->no_nodes);
    if (graph->init == 1){
        position = row_index * graph->no_nodes + column_index;
        return *(graph->adj_matrix + position);
    }
    else{
        printf("Please read the graph first");
        return -1;
    }
}

void read_graph(struct lego *graph){
    int column_index;
    int row_index;
    int aux;

    graph->no_nodes = 1000;
    graph->init = 1;
    graph->adj_matrix = calloc(graph->no_nodes * graph->no_nodes,sizeof(int));

    assert((graph->no_nodes * graph->no_nodes) > 0);
    for (row_index = 0; row_index < graph->no_nodes; row_index++ ){
        for (column_index = row_index + 1; column_index < graph->no_nodes; column_index++ ){
            aux = rand() % 2;
            set_adj_matrix_value(graph, row_index, column_index, aux);
        }
    }
}

void delete_graph(struct lego *graph){
    free(graph->adj_matrix);
    free(graph);
}

void push_begining_list(struct piece *head, int new_value){
    struct piece *next_piece;
    struct piece *new_piece;

    next_piece = head->next;
    new_piece = malloc(sizeof(struct piece));
    new_piece->info = new_value;
    new_piece->next = head->next;
    head->next = new_piece;
}

int pop_begining_list(struct piece *head){
    struct piece *removed_piece;
    int aux;

    if (head->next != NULL) {
        removed_piece = head->next;
        aux = removed_piece->info;
        head->next = removed_piece->next;
        free(removed_piece);
        return aux;
    }
    else{
        printf("\n The list is empty");
        return -1;
    }
}

int pop_end_list(struct piece *head) {
    struct piece *removed_piece;
    struct piece *iterator;
    int aux;

    if (head->next != NULL) {
        for (iterator = head; iterator->next->next != NULL; iterator = iterator->next);
        removed_piece = iterator->next;
        aux = removed_piece->info;
        iterator->next = removed_piece->next;
        free(removed_piece);
        return aux;
    }
    else {
        printf("\n The list is empty");
        return -1;
    }
}

void instruction_1(struct lego *graph, int start_node){
    struct piece *head_queue;
    int present_instruction;
    int column_iterator;
    int *visited;
    int aux;

    head_queue = calloc(1, sizeof(struct piece));
    head_queue->next = NULL;
    head_queue->info = 0;
    visited = calloc((graph->no_nodes), sizeof(int));
    push_begining_list(head_queue, start_node);
    visited[start_node] = 1;

    printf("\n Ordinea pieselor 1: ");
    while (head_queue->next != NULL){
        present_instruction = pop_end_list(head_queue);
        printf("%d, ",present_instruction + 1);
        for(column_iterator = 0; column_iterator < graph->no_nodes; column_iterator++){
            aux = get_adj_matrix_value(graph, present_instruction, column_iterator);
            if ( (aux != 0) && ( (visited[column_iterator]) == 0 )){
                push_begining_list(head_queue, column_iterator);
                visited[column_iterator] = 1;
            }
        }
    }

    free(head_queue);
    free(visited);
}

void instruction_2(struct lego *graph, int start_node){
    struct piece *head_stack;
    int presesnt_instruction;
    int column_iterator;
    int *visited;
    int aux;


    head_stack = calloc(1, sizeof(struct piece));
    head_stack->next = NULL;
    head_stack->info = 0;
    visited = calloc((graph->no_nodes), sizeof(int));
    push_begining_list(head_stack, start_node);
    visited[start_node] = 1;

    printf("\n Ordinea pieselor 2: ");
    while (head_stack->next != NULL){
        presesnt_instruction = pop_begining_list(head_stack);
        printf("%d, ",presesnt_instruction + 1);
        for(column_iterator = 0; column_iterator < graph->no_nodes; column_iterator++){
            aux = get_adj_matrix_value(graph, presesnt_instruction, column_iterator);
            if ( (aux != 0) && ( (visited[column_iterator]) == 0 )){
                push_begining_list(head_stack, column_iterator);
                visited[column_iterator] = 1;
            }
        }
    }

    free(head_stack);
    free(visited);

}

int main(){
    struct lego *graph;
    graph = calloc(1, sizeof(struct lego));
    read_graph(graph);
    instruction_1(graph,0);
    instruction_2(graph,0);

    delete_graph(graph);

    return 0;
}
