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
int flag = 0;
Player player;

struct node
{
    int north;
    int west;
    int south;
    int east;
};
const int MAZE_ROWS = 8, MAZE_COLUMNS = 10;
vector<vector<node>> graph;
glm::vec3 cameraPos = glm::vec3(2 * MAZE_COLUMNS, 2 * MAZE_ROWS, 40.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
const float cameraSpeed = 0.1f;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw()
{
    // set camera view using lookAt() function, on the basis of current position, front, and up vectors
    Matrices.view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP; // MVP = Projection * View * Model

    // Scene render
    player.draw(VP);
}

void tick_input(GLFWwindow *window)
{
    int a = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int s = glfwGetKey(window, GLFW_KEY_S);
    if (w)
    {
        player.set_position(player.position.x, player.position.y + 1);
    }
    if (a)
    {
        player.set_position(player.position.x - 1, player.position.y);
    }
    if (s)
    {
        player.set_position(player.position.x, player.position.y - 1);
    }
    if (d)
    {
        player.set_position(player.position.x+1, player.position.y);
    }
}

void tick_elements()
{
    ;
}

void make_maze()
{
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
    vector<int> temp;
    for (int x = MAZE_ROWS - 1; x >= 0; x--)
    {
        temp.clear();
        for (int y = 0; y < MAZE_COLUMNS; y++)
        {
            if (x == MAZE_ROWS - 1 && y != MAZE_COLUMNS - 1)
            {
                graph[x][y].east = 0;
                graph[x][y + 1].west = 0;
                continue;
            }
            else if (x == MAZE_ROWS - 1 && y == MAZE_COLUMNS - 1)
                continue;
            if (temp.size() == 0)
                temp.push_back(y);
            int check = int(rand() % 2);
            if (y == MAZE_COLUMNS - 1)
                check = 1;
            if (check == 0)
            {
                temp.push_back(y + 1);
                graph[x][y].east = 0;
                graph[x][y + 1].west = 0;
            }
            else
            {
                int randval = int(rand() % (temp.size()));
                graph[x][temp[randval]].north = 0;
                graph[x + 1][temp[randval]].south = 0;
                temp.clear();
            }
        }
    }
    int cnt = (MAZE_ROWS + MAZE_COLUMNS) / 2;
    while (cnt > 0)
    {
        int xval = int(rand() % MAZE_ROWS);
        int yval = int(rand() % MAZE_COLUMNS);
        int dir = int(rand() % 4);
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

void print_maze()
{
    // clear the color and depth in the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram(programID);
    vector<GLfloat> vertex_temp;
    for (int x = 0; x < MAZE_ROWS; x++)
    {
        for (int y = 0; y < MAZE_COLUMNS; y++)
        {
            if (graph[x][y].north == 1)
            {
                vertex_temp.insert(vertex_temp.end(), {4 * y - 2.0f, 4 * x + 2.0f, 0.0f, 4 * y + 2.0f, 4 * x + 2.0f, 0.0f});
            }
            if (graph[x][y].east == 1)
            {
                vertex_temp.insert(vertex_temp.end(), {4 * y + 2.0f, 4 * x + 2.0f, 0.0f, 4 * y + 2.0f, 4 * x - 2.0f, 0.0f});
            }
            if (graph[x][y].south == 1)
            {
                vertex_temp.insert(vertex_temp.end(), {4 * y - 2.0f, 4 * x - 2.0f, 0.0f, 4 * y + 2.0f, 4 * x - 2.0f, 0.0f});
            }
            if (graph[x][y].west == 1)
            {
                vertex_temp.insert(vertex_temp.end(), {4 * y - 2.0f, 4 * x + 2.0f, 0.0f, 4 * y - 2.0f, 4 * x - 2.0f, 0.0f});
            }
        }
    }
    GLfloat vertex_buffer_data[vertex_temp.size()], colour_buffer_data[vertex_temp.size()];
    copy(vertex_temp.begin(), vertex_temp.end(), vertex_buffer_data);
    // for (int i = 0; i < vertex_temp.size(); i += q)
    // {
    //     if (flag == 0)
    //         cout << vertex_buffer_data[i] << ' ' << vertex_buffer_data[i + 1] << ' ' << vertex_buffer_data[i + 2] << '\n';
    // }
    // flag = 1;
    VAO *maze;
    maze = create3DObject(GL_LINES, vertex_temp.size() / 3, vertex_buffer_data, COLOR_GREEN, GL_FILL);
    draw3DObject(maze);
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height)
{
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    player = Player(0, 0, COLOR_RED);
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

int main(int argc, char **argv)
{
    srand(time(0));
    make_maze();
    int width = 1200;
    int height = 1200;

    window = initGLFW(width, height);

    initGL(window, width, height);
    player.set_position(2 * MAZE_COLUMNS, 2 * MAZE_ROWS);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window))
    {
        // Process timers

        if (t60.processTick())
        {
            print_maze();
            tick_input(window);
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            tick_elements();
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

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