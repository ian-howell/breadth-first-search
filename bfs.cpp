#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct Node
{
    int row;
    int col;
    bool visited;
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
vector<Node> get_neighbors(const Node& node, const int max_row, const int max_col);

int main()
{
    Grid* my_grid = NULL;
    int rows, cols;
    cin >> rows >> cols;

    my_grid = create_grid(rows, cols);
    fill_grid(my_grid);
    print_grid(my_grid);
    free_grid(my_grid);

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
    for (int i = 0; i < grid->rows; i++)
    {
        for (int j = 0; j < grid->cols; j++)
            cout << grid->grid[i][j];
        cout << endl;
    }

    cout << "Start at (" << grid->start.row << ", " << grid->start.col << ")" << endl;
    cout << "End at (" << grid->end.row << ", " << grid->end.col << ")" << endl;

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
    queue<Node> frontier;


    return;
}

vector<Node> get_neighbors(const Node& node, const int max_row, const int max_col)
{
    vector<Node> neighbors;
    Node new_node;
    int new_row;
    int new_col;

    for (int i = -1; i <= 1; i += 2)
    {
        new_row = node.row;
        new_col = node.col + i;
        if (new_row >= 0 && new_col >= 0 &&
            new_row < max_row && new_col < max_col)
        {
            new_node.row = new_row;
            new_node.col = new_col;
            new_node.visited = true;
            neighbors.push_back(new_node);
        }

        new_row = node.row + i;
        new_col = node.col;
        if (new_row >= 0 && new_col >= 0 &&
            new_row < max_row && new_col < max_col)
        {
            new_node.row = new_row;
            new_node.col = new_col;
            new_node.visited = true;
            neighbors.push_back(new_node);
        }
    }

    return neighbors;
}
