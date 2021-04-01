#include "main.h"
#include "timer.h"
#include "object.h"

using namespace std;

GLMatrices Matrices;
GLuint programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

// Initialize display and environment varaibles
int flag = 0;
Player player;
Imposter imposter;
Pow_imp pow_imp;
Pow_obspow pow_obspow;
Exitgame exitgame;

struct node
{
    int north;
    int west;
    int south;
    int east;
};

const int MAZE_ROWS = 10, MAZE_COLUMNS = 10, NUM_PICKUPS = 6;
char HUD_text[1000];
int gamescore = 0, gametime = 20000, gamestate = 0; // gamestates :- 0 is running, 1 is successful exit, 2 is timed out, 3 is caught
vector<vector<node>> graph;

// define camera states
glm::vec3 cameraPos = glm::vec3(2 * MAZE_COLUMNS, 2 * MAZE_ROWS, 45.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
const float cameraSpeed = 0.1f, playerSpeed = 0.1f, imposterSpeed = 0.11f;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Pickups pickups[NUM_PICKUPS];

Timer t60(1.0 / 60);

void tick_input(GLFWwindow *window)
{
    // capture all key inputs and do the necessary actions
    int a = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int s = glfwGetKey(window, GLFW_KEY_S);
    if (w)
    {
        // get current player position
        float up = player.position.y + 1.0f, left = player.position.x - 0.8f, right = player.position.x + 0.5f, down = player.position.y - 1.3f;
        // check if player is contained in one cell
        if (int(left / 4.0) == int(right / 4.0) && up + 0.1f < 4 * MAZE_ROWS)
        {
            // check if boundary is not a wall
            if (graph[int(up / 4.0)][int(left / 4.0)].north == 0)
            {
                player.set_position(player.position.x, player.position.y + playerSpeed);
                cameraPos += cameraSpeed * cameraUp;
            }
            // check if boundary is a wall but player is not touching it
            else if (graph[int(up / 4.0)][int(left / 4.0)].north == 1 && (up + 0.1f < 4 * int(up / 4.0 + 1)))
            {
                player.set_position(player.position.x, player.position.y + playerSpeed);
                cameraPos += cameraSpeed * cameraUp;
            }
        }
        // check if player is in 2 cells
        else if (int(left / 4.0) != int(right / 4.0) && up + 0.1f < 4 * MAZE_ROWS)
        {
            // check if boundary of both cells is not a wall, and adjacent perpendicular wall is absent
            if (graph[int(up / 4.0)][int(left / 4.0)].north == 0 && graph[int(up / 4.0)][int(right / 4.0)].north == 0 && graph[int(up / 4.0) + 1][int(left / 4.0)].east == 0)
            {
                player.set_position(player.position.x, player.position.y + playerSpeed);
                cameraPos += cameraSpeed * cameraUp;
            }
            // check if player is not touching wall
            else if ((up + 0.1f < 4 * int(up / 4.0 + 1)))
            {
                player.set_position(player.position.x, player.position.y + playerSpeed);
                cameraPos += cameraSpeed * cameraUp;
            }
        }
    }
    if (a)
    {
        // get current player position
        float up = player.position.y + 1.0f, left = player.position.x - 0.8f, right = player.position.x + 0.5f, down = player.position.y - 1.3f;
        // check if player is contained in one cell
        if (int(up / 4.0) == int(down / 4.0) && left - 0.1f > 0)
        {
            // check if boundary is not a wall
            if (graph[int(up / 4.0)][int(left / 4.0)].west == 0)
            {
                player.set_position(player.position.x - playerSpeed, player.position.y);
                cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            }
            // check if boundary is a wall but player is not touching it
            else if (graph[int(up / 4.0)][int(left / 4.0)].west == 1 && (left - 0.1f > 4 * int(left / 4.0)))
            {
                player.set_position(player.position.x - playerSpeed, player.position.y);
                cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            }
        }
        // check if player is in 2 cells
        if (int(up / 4.0) != int(down / 4.0) && left - 0.1f > 0)
        {
            // check if boundary of both cells is not a wall, and adjacent perpendicular wall is absent
            if (graph[int(up / 4.0)][int(left / 4.0)].west == 0 && graph[int(down / 4.0)][int(left / 4.0)].west == 0 && graph[int(down / 4.0)][int(left / 4.0) - 1].north == 0)
            {
                player.set_position(player.position.x - playerSpeed, player.position.y);
                cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            }
            // check if player is not touching wall
            else if ((left - 0.1f > 4 * int(left / 4.0)))
            {
                player.set_position(player.position.x - playerSpeed, player.position.y);
                cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            }
        }
    }
    if (s)
    {
        // get current player position
        float up = player.position.y + 1.0f, left = player.position.x - 0.8f, right = player.position.x + 0.5f, down = player.position.y - 1.3f;
        // check if player is contained in one cell
        if (int(left / 4.0) == int(right / 4.0) && down - 0.1f > 0)
        {
            // check if boundary is not a wall
            if (graph[int(down / 4.0)][int(left / 4.0)].south == 0)
            {
                player.set_position(player.position.x, player.position.y - playerSpeed);
                cameraPos -= cameraSpeed * cameraUp;
            }
            // check if boundary is a wall but player is not touching it
            else if (graph[int(down / 4.0)][int(left / 4.0)].south == 1 && (down - 0.1f > 4 * int(down / 4.0)))
            {
                player.set_position(player.position.x, player.position.y - playerSpeed);
                cameraPos -= cameraSpeed * cameraUp;
            }
        }
        // check if player is in 2 cells
        if (int(left / 4.0) != int(right / 4.0) && down - 0.1f > 0)
        {
            // check if boundary of both cells is not a wall, and adjacent perpendicular wall is absent
            if (graph[int(down / 4.0)][int(left / 4.0)].south == 0 && graph[int(down / 4.0)][int(right / 4.0)].south == 0 && graph[int(down / 4.0) - 1][int(left / 4.0)].east == 0)
            {
                player.set_position(player.position.x, player.position.y - playerSpeed);
                cameraPos -= cameraSpeed * cameraUp;
            }
            // check if player is not touching wall
            else if ((down - 0.1f > 4 * int(down / 4.0)))
            {
                player.set_position(player.position.x, player.position.y - playerSpeed);
                cameraPos -= cameraSpeed * cameraUp;
            }
        }
    }
    if (d)
    {
        // get current player position
        float up = player.position.y + 1.0f, left = player.position.x - 0.8f, right = player.position.x + 0.5f, down = player.position.y - 1.3f;
        // check if player is contained in one cell
        if (int(up / 4.0) == int(down / 4.0) && right + 0.1f < 4 * MAZE_COLUMNS)
        {
            if (graph[int(up / 4.0)][int(right / 4.0)].east == 0)
            {
                player.set_position(player.position.x + playerSpeed, player.position.y);
                cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            }
            // check if boundary is a wall but player is not touching it
            else if (graph[int(up / 4.0)][int(right / 4.0)].east == 1 && (right + 0.1f < 4 * int(right / 4.0 + 1)))
            {
                player.set_position(player.position.x + playerSpeed, player.position.y);
                cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            }
        }
        // check if player is in 2 cells
        else if (int(up / 4.0) != int(down / 4.0) && right + 0.1f < 4 * MAZE_COLUMNS)
        {
            // check if boundary of both cells is not a wall, and adjacent perpendicular wall is absent
            if (graph[int(up / 4.0)][int(right / 4.0)].east == 0 && graph[int(down / 4.0)][int(right / 4.0)].east == 0 && graph[int(down / 4.0)][int(right / 4.0) + 1].north == 0)
            {
                player.set_position(player.position.x + playerSpeed, player.position.y);
                cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            }
            // check if player is not touching wall
            else if ((right + 0.1f < 4 * int(right / 4.0 + 1)))
            {
                player.set_position(player.position.x + playerSpeed, player.position.y);
                cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            }
        }
    }
}

// function that calculates shortest path for imposter to reach the player, using breadth first search (BFS)
void move_imposter()
{
    // initialize destination, source, and visited, parent, and output arrays and assign values
    pair<int, int> src, dest;
    src.first = int(imposter.position.y / 4.0), src.second = int(imposter.position.x / 4.0);
    dest.first = int(player.position.y / 4.0), dest.second = int(player.position.x / 4.0);
    vector<vector<int>> vis;
    vector<vector<pair<int, int>>> parent;
    vector<pair<int, int>> outpath;
    for (int x = 0; x < MAZE_ROWS; x++)
    {
        vector<int> vistemp;
        vector<pair<int, int>> partemp;
        for (int y = 0; y < MAZE_COLUMNS; y++)
        {
            vistemp.push_back(0);
            partemp.push_back({-1, -1});
        }
        vis.push_back(vistemp);
        parent.push_back(partemp);
        vistemp.clear();
        partemp.clear();
    }
    // create queue to be used in BFS and push source to it
    queue<pair<int, int>> q;
    q.push(src);
    while (q.size() > 0)
    {
        pair<int, int> cur;
        cur = q.front();
        q.pop();
        int x = cur.first, y = cur.second;
        // check if current node in queue is destination
        if (cur == dest)
        {
            // code to output path from destination to source as per parent vector
            outpath.push_back(cur);
            while (parent[x][y].first != -1)
            {
                int tx = parent[x][y].first, ty = parent[x][y].second;
                outpath.push_back({tx, ty});
                x = tx, y = ty;
            }
            break;
        }
        if (vis[x][y] == 0)
        {
            vis[x][y] = 1;
            // push neighbouring nodes to queue, if valid, and assign parent values
            if (x < MAZE_ROWS - 1)
            {
                if (graph[x][y].north == 0 && vis[x + 1][y] == 0)
                {
                    q.push({x + 1, y});
                    parent[x + 1][y] = {x, y};
                }
            }
            if (x > 0)
            {
                if (graph[x][y].south == 0 && vis[x - 1][y] == 0)
                {
                    q.push({x - 1, y});
                    parent[x - 1][y] = {x, y};
                }
            }
            if (y < MAZE_COLUMNS - 1)
            {
                if (graph[x][y].east == 0 && vis[x][y + 1] == 0)
                {
                    q.push({x, y + 1});
                    parent[x][y + 1] = {x, y};
                }
            }
            if (y > 0)
            {
                if (graph[x][y].west == 0 && vis[x][y - 1] == 0)
                {
                    q.push({x, y - 1});
                    parent[x][y - 1] = {x, y};
                }
            }
        }
    }
    // if imposter is present in same square as player, move towards player
    if (outpath.size() == 1)
    {
        if (imposter.position.y < player.position.y)
            imposter.set_position(imposter.position.x, imposter.position.y + imposterSpeed);
        if (imposter.position.y > player.position.y)
            imposter.set_position(imposter.position.x, imposter.position.y - imposterSpeed);
        if (imposter.position.x < player.position.x)
            imposter.set_position(imposter.position.x + imposterSpeed, imposter.position.y);
        if (imposter.position.x > player.position.x)
            imposter.set_position(imposter.position.x - imposterSpeed, imposter.position.y);
    }
    else
    {
        // check if imposter is present in center of the cell. If not present in center of cell and if perpendicular to desired motion, move to center first
        dest = outpath[outpath.size() - 2];
        int cflag = 0;
        if (imposter.position.y < 4 * src.first + 1.9 && src.first == dest.first)
        {
            imposter.set_position(imposter.position.x, imposter.position.y + imposterSpeed);
            cflag = 1;
        }
        if (imposter.position.y > 4 * src.first + 2.1 && src.first == dest.first)
        {
            imposter.set_position(imposter.position.x, imposter.position.y - imposterSpeed);
            cflag = 1;
        }
        if (imposter.position.x > 4 * src.second + 2.1 && src.second == dest.second)
        {
            imposter.set_position(imposter.position.x - imposterSpeed, imposter.position.y);
            cflag = 1;
        }
        if (imposter.position.x < 4 * src.second + 1.9 && src.second == dest.second)
        {
            imposter.set_position(imposter.position.x + imposterSpeed, imposter.position.y);
            cflag = 1;
        }
        // move towards desired cell, if present towards center of current cell
        if (cflag == 0)
        {
            if (src.first < dest.first)
                imposter.set_position(imposter.position.x, imposter.position.y + imposterSpeed);
            else if (src.first > dest.first)
                imposter.set_position(imposter.position.x, imposter.position.y - imposterSpeed);
            else if (src.second < dest.second)
                imposter.set_position(imposter.position.x + imposterSpeed, imposter.position.y);
            else if (src.second > dest.second)
                imposter.set_position(imposter.position.x - imposterSpeed, imposter.position.y);
        }
    }
}

// function to update game details, collisions, states, score, and other semantics
void tick_elements()
{
    // update time and check if it has reached 0
    gametime--;
    if (gametime <= 0)
    {
        gamestate = 2;
        return;
    }
    if (gametime % 100 == 0)
    {
        gamescore += 5;
    }
    // check for collision with imposter task and update imposter flag 
    float up = player.position.y + 1.0f, left = player.position.x - 0.8f, right = player.position.x + 0.5f, down = player.position.y - 1.3f;
    if (pow_imp.position.x >= left && pow_imp.position.x <= right && pow_imp.position.y >= down && pow_imp.position.y <= up)
    {
        if (pow_imp.flag == 0)
            gamescore += 100;
        pow_imp.flag = 1;
        imposter.flag = 1;
    }
    // check for collision with powerups task and update flag
    if (pow_obspow.position.x >= left && pow_obspow.position.x <= right && pow_obspow.position.y >= down && pow_obspow.position.y <= up)
    {
        if (pow_obspow.flag == 0)
            gamescore += 75;
        pow_obspow.flag = 1;
    }
    // check for collision with imposter and update game state
    if (imposter.position.x + 0.4f >= left && imposter.position.x - 0.7f <= right && imposter.position.y + 1.3f >= down && imposter.position.y - 1.3f <= up && imposter.flag == 0)
    {
        gamestate = 3;
    }
    // check for collision with exit and update game state
    if (exitgame.position.x + 1.4f >= left && exitgame.position.x - 1.4f <= right && exitgame.position.y + 1.4f >= down && exitgame.position.y - 1.4f <= up)
    {
        if (pow_imp.flag == 1 && pow_obspow.flag == 1)
        {
            exitgame.flag = 1;
            gamestate = 1;
        }
    }
    // check for collision with obstacle/powerup
    if (pow_obspow.flag == 1)
    {
        for (int i = 0; i < NUM_PICKUPS; i++)
        {
            if (pickups[i].flag == 1)
                pickups[i].flag = 0;
            if (pickups[i].position.x >= left && pickups[i].position.x <= right && pickups[i].position.y >= down && pickups[i].position.y <= up && pickups[i].flag == 0)
            {
                if (pickups[i].type == 0)
                    gamescore -= 50;
                else
                    gamescore += 50;
                pickups[i].flag = 2;
            }
        }
    }
    // update imposter movement if valid
    if (imposter.flag == 0)
    {
        move_imposter();
    }
}

// function that generates a maze using the sidewinder algorithm. Maze is stored in vector of vector, graph
void make_maze()
{
    // initialize graph
    for (int x = 0; x < MAZE_ROWS; x++)
    {
        vector<node> row;
        for (int y = 0; y < MAZE_COLUMNS; y++)
        {
            row.push_back({1, 1, 1, 1});
        }
        graph.push_back(row);
        row.clear();
    }
    // temp stores list of currently selected set of nodes
    vector<int> temp;
    for (int x = MAZE_ROWS - 1; x >= 0; x--)
    {
        temp.clear();
        for (int y = 0; y < MAZE_COLUMNS; y++)
        {
            // the first row has each cell carved east out of necessity
            if (x == MAZE_ROWS - 1 && y != MAZE_COLUMNS - 1)
            {
                graph[x][y].east = 0;
                graph[x][y + 1].west = 0;
                continue;
            }
            else if (x == MAZE_ROWS - 1 && y == MAZE_COLUMNS - 1)
                continue;
            // om case the temp set is empty, we select current node
            if (temp.size() == 0)
                temp.push_back(y);
            int check = int(rand() % 2);
            // if we are at the last column of any row, we must randomly carve north out of the selected set
            if (y == MAZE_COLUMNS - 1)
                check = 1;
            // if check is 0, we carve east and add the next node to the current set
            if (check == 0)
            {
                temp.push_back(y + 1);
                graph[x][y].east = 0;
                graph[x][y + 1].west = 0;
            }
            // if check is 1, we carve north for a random node from set, and clear the set
            else
            {
                int randval = int(rand() % (temp.size()));
                graph[x][temp[randval]].north = 0;
                graph[x + 1][temp[randval]].south = 0;
                temp.clear();
            }
        }
    }
    // get number of nodes to be randomly removed, so as to remove perfect nature of the maze and have a certain number of cycles
    int cnt = (MAZE_ROWS + MAZE_COLUMNS) / 2;
    while (cnt > 0)
    {
        int xval = int(rand() % MAZE_ROWS);
        int yval = int(rand() % MAZE_COLUMNS);
        int dir = int(rand() % 4);
        // check if generated values are valid removals of edges
        if ((xval == 0 && dir == 2) || (xval == MAZE_ROWS - 1 && dir == 0) || (yval == 0 && dir == 3) || (yval == MAZE_COLUMNS - 1 && dir == 1))
            continue;
        if (dir == 0 && graph[xval][yval].north != 0)
        {
            graph[xval][yval].north = 0;
            graph[xval + 1][yval].south = 0;
            cnt--;
        }
        else if (dir == 1 && graph[xval][yval].east != 0)
        {
            graph[xval][yval].east = 0;
            graph[xval][yval + 1].west = 0;
            cnt--;
        }
        else if (dir == 2 && graph[xval][yval].south != 0)
        {
            graph[xval][yval].south = 0;
            graph[xval - 1][yval].north = 0;
            cnt--;
        }
        else if (dir == 3 && graph[xval][yval].west != 0)
        {
            graph[xval][yval].west = 0;
            graph[xval][yval - 1].east = 0;
            cnt--;
        }
    }
}

// function that prints the maze background using GL_LINES primitive
void print_maze(glm::mat4 VP)
{
    // clear the color and depth in the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    glUseProgram(programID);
    // create and give values of vertices from graph to vector
    vector<GLfloat> vertex_temp;
    for (int x = 0; x < MAZE_ROWS; x++)
    {
        for (int y = 0; y < MAZE_COLUMNS; y++)
        {
            if (graph[x][y].north == 1)
            {
                vertex_temp.insert(vertex_temp.end(), {4 * float(y), 4 * x + 4.0f, 0.0f, 4 * y + 4.0f, 4 * x + 4.0f, 0.0f});
            }
            if (graph[x][y].east == 1)
            {
                vertex_temp.insert(vertex_temp.end(), {4 * y + 4.0f, 4 * x + 4.0f, 0.0f, 4 * y + 4.0f, 4 * float(x), 0.0f});
            }
            if (graph[x][y].south == 1)
            {
                vertex_temp.insert(vertex_temp.end(), {4 * float(y), 4 * float(x), 0.0f, 4 * y + 4.0f, 4 * float(x), 0.0f});
            }
            if (graph[x][y].west == 1)
            {
                vertex_temp.insert(vertex_temp.end(), {4 * float(y), 4 * x + 4.0f, 0.0f, 4 * float(y), 4 * float(x), 0.0f});
            }
        }
    }
    // convert vector to const float
    GLfloat vertex_buffer_data[vertex_temp.size()];
    copy(vertex_temp.begin(), vertex_temp.end(), vertex_buffer_data);
    
    // define VAO, create, transform, and draw object
    VAO *maze;
    maze = create3DObject(GL_LINES, vertex_temp.size() / 3, vertex_buffer_data, COLOR_GREEN_MAZE, GL_FILL);
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(maze);
}

// Initialize the OpenGL rendering properties
void initGL(GLFWwindow *window, int width, int height)
{
    // Create all the game models
    player = Player(0, 0, COLOR_RED);
    imposter = Imposter(0, 0, COLOR_RED);
    pow_imp = Pow_imp(0, 0, COLOR_BLACK);
    pow_obspow = Pow_obspow(0, 0, COLOR_BLACK);
    exitgame = Exitgame(0, 0, COLOR_EXIT);
    for (int i = 0; i < NUM_PICKUPS; i++)
    {
        int typerand = int(rand() % 2);
        if (typerand == 0)
            pickups[i] = Pickups(0, 0, typerand, COLOR_RED);
        else
            pickups[i] = Pickups(0, 0, typerand, COLOR_GREEN);
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../source/shaders/shader.vert", "../source/shaders/shader.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow(window, width, height);

    // Background color of the scene
    glClearColor(COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

// end screen, displayed when the gamestate changes
void end_screen(int gamestate)
{
    //alter camera position, reset background colour and player position
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);
    cameraPos = glm::vec3(0.0f, 0.0f, 20.0f);
    Matrices.view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 MVP; // MVP = Projection * View * Model

    if (gamestate == 1)
    {
        glClearColor(COLOR_BACKGROUND_WIN.r / 256.0, COLOR_BACKGROUND_WIN.g / 256.0, COLOR_BACKGROUND_WIN.b / 256.0, 0.0f); // R, G, B, A
        glClearDepth(1.0f);
        player.set_position(0.0f, -2.0f);
        player.draw(VP);
    }
    else
    {
        glClearColor(COLOR_BACKGROUND_LOSS.r / 256.0, COLOR_BACKGROUND_LOSS.g / 256.0, COLOR_BACKGROUND_LOSS.b / 256.0, 0.0f); // R, G, B, A
        glClearDepth(1.0f);
        imposter.set_position(0.0f, -2.0f);
        imposter.draw(VP);
    }

    // Creating text for output of the screen, and rendering it appropriately
    GLTtext *scoretext = gltCreateText();
    GLTtext *titletext = gltCreateText();
    GLTtext *subtitletext = gltCreateText();
    sprintf(HUD_text, "Your final score was: %d", gamescore);
    gltSetText(scoretext, HUD_text);
    if (gamestate == 1)
    {
        gltSetText(titletext, "VICTORY!");
        gltSetText(subtitletext, "You have successfully exited the maze!");
    }
    else if (gamestate == 2)
    {
        gltSetText(titletext, "DEFEAT!");
        gltSetText(subtitletext, "You ran out of time!");
    }
    else if (gamestate == 3)
    {
        gltSetText(titletext, "DEFEAT!");
        gltSetText(subtitletext, "You were caught by the imposter!");
    }
    // Begin text drawing
    gltBeginDraw();

    if (gamestate == 1)
        gltColor(0.1f, 1.0f, 0.1f, 1.0f);
    else
        gltColor(1.0f, 0.1f, 0.1f, 1.0f);
    gltDrawText2DAligned(titletext, 550.0f, 100.0f, 10.0f, GLT_CENTER, GLT_TOP);
    gltColor(1.0f, 1.0f, 1.0f, 1.0f);
    gltDrawText2DAligned(subtitletext, 550.0f, 275.0f, 3.3f, GLT_CENTER, GLT_TOP);
    gltDrawText2DAligned(scoretext, 550.0f, 375.0f, 2.5f, GLT_CENTER, GLT_TOP);
    
    // Finish drawing text
    gltEndDraw();

    gltDeleteText(scoretext);
    gltDeleteText(titletext);
    gltDeleteText(subtitletext);
}

// Render the scene with openGL
void draw()
{
    // set camera view using lookAt() function, on the basis of current position, front, and up vectors
    Matrices.view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    glm::mat4 MVP; // MVP = Projection * View * Model

    // Scene render
    print_maze(VP);
    pow_imp.draw(VP);
    pow_obspow.draw(VP);
    exitgame.draw(VP);
    for (int i = 0; i < NUM_PICKUPS; i++)
        pickups[i].draw(VP);
    player.draw(VP);
    imposter.draw(VP);

    // Creating text for HUD display
    GLTtext *text = gltCreateText();
    sprintf(HUD_text, "Score: %d\nTasks: %d/2\nTime: %d", gamescore, pow_imp.flag + pow_obspow.flag, gametime / 100);
    gltSetText(text, HUD_text);

    // Begin text drawing 
    gltBeginDraw();

    gltColor(0.2f, 1.0f, 0.2f, 1.0f);
    gltDrawText2D(text, 15.0f, 15.0f, 1.5f);

    // Finish drawing text
    gltEndDraw();
    gltDeleteText(text);
}

int main(int argc, char **argv)
{
    // initialize maze and openGL background window and functions
    srand(time(0));
    make_maze();
    int width = 1080;
    int height = 1080;
    window = initGLFW(width, height);
    initGL(window, width, height);
    gltInit();
    // randomize starting position of imposter, tasks, pickups, and exit
    player.set_position(2 * MAZE_COLUMNS + 2.0, 2 * MAZE_ROWS + 2.0);
    int xval = int(rand() % MAZE_COLUMNS), yval = int(rand() % MAZE_ROWS);
    imposter.set_position(4 * xval + 2.0, 4 * yval + 2.0);
    xval = int(rand() % MAZE_COLUMNS), yval = int(rand() % MAZE_ROWS);
    pow_imp.set_position(4 * xval + 2.0, 4 * yval + 2.0);
    xval = int(rand() % MAZE_COLUMNS), yval = int(rand() % MAZE_ROWS);
    exitgame.set_position(4 * xval + 2.0, 4 * yval + 2.0);
    xval = int(rand() % MAZE_COLUMNS), yval = int(rand() % MAZE_ROWS);
    pow_obspow.set_position(4 * xval + 2.0, 4 * yval + 2.0);
    for (int i = 0; i < NUM_PICKUPS; i++)
    {
        xval = int(rand() % MAZE_COLUMNS), yval = int(rand() % MAZE_ROWS);
        pickups[i].set_position(4 * xval + 2.0, 4 * yval + 2.0);
    }

    // Draw in loop
    while (!glfwWindowShouldClose(window))
    {
        // Process timers
        if (t60.processTick())
        {
            // draw game if state is valud
            if (gamestate == 0)
            {
                tick_input(window);
                
                // OpenGL Draw commands
                draw();
                tick_elements();
            }
            // if gamestate changes, display appropriate end screen
            else
                end_screen(gamestate);
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
        }
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }
    gltTerminate();
    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b)
{
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen()
{
    float top = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left = screen_center_x - 4 / screen_zoom;
    float right = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
}
