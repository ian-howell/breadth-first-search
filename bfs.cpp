#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct Node
{
    int row;
    int col;
    Node* parent;
};

struct Grid
{
    char** grid;
    int rows;
    int cols;
    Node start;
    Node end;
};

Grid* create_grid(int rows, int cols);
void fill_grid(Grid* grid);
void print_grid(Grid* grid);
void free_grid(Grid* grid);
void breadth_first_search(Grid* grid);
vector<Node> get_neighbors(Node* node, const int max_row, const int max_col);

int main()
{
    Grid* my_grid = NULL;
    int rows, cols;
    cin >> rows >> cols;

    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    my_grid = create_grid(rows, cols);
    fill_grid(my_grid);

    print_grid(my_grid);
    breadth_first_search(my_grid);
    print_grid(my_grid);

    free_grid(my_grid);

    getch();
    endwin();
    return 0;
}

Grid* create_grid(int rows, int cols)
{
    Grid* grid = new Grid;
    grid->rows = rows;
    grid->cols = cols;

    grid->grid = new char*[rows];
    for (int i = 0; i < rows; i++)
        grid->grid[i] = new char[cols];

    return grid;
}

void fill_grid(Grid* grid)
{
    char new_line_garbage;
    for (int i = 0; i < grid->rows; i++)
    {
        cin.get(new_line_garbage);
        for (int j = 0; j < grid->cols; j++)
        {
            cin.get(grid->grid[i][j]);
            if (grid->grid[i][j] == 'S')
            {
                grid->start.row = i;
                grid->start.col = j;
            }
            else if (grid->grid[i][j] == 'E')
            {
                grid->end.row = i;
                grid->end.col = j;
            }
        }
    }
    return;
}

void print_grid(Grid* grid)
{
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    init_pair(3, COLOR_BLUE, COLOR_BLUE);
    init_pair(4, COLOR_RED, COLOR_RED);
    init_pair(5, COLOR_GREEN, COLOR_GREEN);

    for (int i = 0; i < grid->rows; i++)
    {
        for (int j = 0; j < grid->cols; j++)
        {
            if (grid->grid[i][j] == '#')
                attron(COLOR_PAIR(1));
            else if (grid->grid[i][j] == ' ')
                attron(COLOR_PAIR(2));
            else if (grid->grid[i][j] == '.')
                attron(COLOR_PAIR(5));
            else if (grid->grid[i][j] == 'S')
                attron(COLOR_PAIR(3));
            else
                attron(COLOR_PAIR(4));

            mvwprintw(stdscr, i + 1, j + 1, "%c", grid->grid[i][j]);

            attroff(COLOR_PAIR(1));
            attroff(COLOR_PAIR(2));
            attroff(COLOR_PAIR(3));
            attroff(COLOR_PAIR(4));
            attroff(COLOR_PAIR(5));
        }
    }
    refresh();

    return;
}

void free_grid(Grid* grid)
{
    for (int i = 0; i < grid->rows; i++)
    {
        delete [] grid->grid[i];
    }
    delete [] grid->grid;
    delete grid;

    return;
}

void breadth_first_search(Grid* grid)
{
    queue<Node*> frontier;
    queue<Node*> to_delete;
    // grid->grid[grid->start.row][grid->start.col] = '.';
    grid->start.parent = NULL;
    frontier.push(&grid->start);

    Node* u;
    while (!frontier.empty())
    {
        u = frontier.front(); frontier.pop();
        if (u->row == grid->end.row && u->col == grid->end.col)
        {
            for (Node* runner = u; runner; runner = runner->parent)
            {
                grid->grid[runner->row][runner->col] = '*';
                print_grid(grid);
                usleep(50000);
            }

            delete u;
            while(!frontier.empty())
            {
                u = frontier.front(); frontier.pop();
                delete u;
            }
            while (!to_delete.empty())
            {
                u = to_delete.front(); to_delete.pop();
                delete u;
            }
            return;
        }

        vector<Node> neighbors = get_neighbors(u, grid->rows, grid->cols);
        for (size_t i = 0; i < neighbors.size(); i++)
        {
            if (grid->grid[neighbors[i].row][neighbors[i].col] != '.' &&
                grid->grid[neighbors[i].row][neighbors[i].col] != '#' &&
                grid->grid[neighbors[i].row][neighbors[i].col] != 'S')
            {
                grid->grid[neighbors[i].row][neighbors[i].col] = '.';
                // system("clear");
                print_grid(grid);
                usleep(12000);
                neighbors[i].parent = u;
                Node* v = new Node;
                *v = neighbors[i];
                frontier.push(v);
            }
        }

        if (u->parent != NULL)
            to_delete.push(u);
    }

    return;
}

vector<Node> get_neighbors(Node* node, const int max_row, const int max_col)
{
    vector<Node> neighbors;
    Node new_node;
    int new_row;
    int new_col;

    for (int i = -1; i <= 1; i += 2)
    {
        new_row = node->row;
        new_col = node->col + i;
        if (new_row >= 0 && new_col >= 0 &&
            new_row < max_row && new_col < max_col)
        {
            new_node.row = new_row;
            new_node.col = new_col;
            new_node.parent = node;
            neighbors.push_back(new_node);
        }

        new_row = node->row + i;
        new_col = node->col;
        if (new_row >= 0 && new_col >= 0 &&
            new_row < max_row && new_col < max_col)
        {
            new_node.row = new_row;
            new_node.col = new_col;
            new_node.parent = node;
            neighbors.push_back(new_node);
        }
    }

    return neighbors;
}
