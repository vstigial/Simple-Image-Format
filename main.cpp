#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

uint8_t isolateR(std::string str) {
    //std::cout << str.find(",") << std::endl;
    std::string red = str.substr(0, str.find_first_of(","));
    // remove whitespace. commented out because it is not needed
    //red.erase(remove_if(red.begin(), red.end(), isspace), red.end());
    //std::cout << "r: " << red << std::endl;
    return static_cast<uint8_t>(std::stoi(red));
}

uint8_t isolateG(std::string str) {
    std::string green = str.substr(str.find_first_of(",")+1, str.find_last_of(",")-str.find_first_of(",")-1);
    //green.erase(remove_if(green.begin(), green.end(), isspace), green.end());
    //std::cout << "g: " << green << std::endl;
    return static_cast<uint8_t>(std::stoi(green));
}

uint8_t isolateB(std::string str) { 
    std::string blue = str.substr(str.find_last_of(",")+1, std::string::npos);
    //blue.erase(remove_if(blue.begin(), blue.end(), isspace), blue.end());
    //std::cout << "b: " << blue << std::endl;
    return static_cast<uint8_t>(std::stoi(blue));
}

int main(int argc, char* argv[]) {
    if (!argv[1]) {
        std::cerr << "You must provide a file to open!\n    program.exe <file>" << std::endl;
        return 1;
    }
    //HDC hdc = GetDC(0);
    std::ifstream File(argv[1]);
    if (!File) {
        std::cerr << "Provide a valid file path!" << std::endl;
        return 1;
    }
    std::string text;
    std::vector<std::string> position_lines;
    std::vector<std::string> color_lines;
    std::vector<uint8_t> r, g, b;
    std::vector<std::vector<size_t>> x, y;
    //std::vector<size_t> x, y;

    while (getline(File, text)) {
        std::string position = text.substr(0, text.find("(")-1);
        //std::cout << position << std::endl;
        position_lines.push_back(position);
        std::string color = text.substr(text.find("("), std::string::npos);
        //std::cout << color << std::endl;
        color_lines.push_back(color);
        
        //std::cout << text << std::endl;
    }
    File.close();

    for (std::string line : position_lines) {
        std::vector<size_t> x_line = {}, y_line = {};

        std::string x_data = line.substr(0, line.find(" "));
        size_t x_pix_start = std::stoi(x_data.substr(0, x_data.find("-")))+1;
        size_t x_pix_end = std::stoi(x_data.substr(x_data.find("-")+1, std::string::npos));
        while (x_pix_start <= x_pix_end) {
            x_line.push_back(x_pix_start);
            ++x_pix_start;
        }
        std::string y_data = line.substr(line.find(" ")+1, std::string::npos);
        size_t y_pix_start = std::stoi(y_data.substr(0, y_data.find("-")))+1;
        size_t y_pix_end = std::stoi(y_data.substr(y_data.find("-")+1, std::string::npos));
        while (y_pix_start <= y_pix_end) {
            y_line.push_back(y_pix_start);
            ++y_pix_start;        
        }
        x.push_back(x_line);
        y.push_back(y_line);
    }

    for (std::string line : color_lines) {
       line = line.substr(1, std::string::npos);
       line = line.substr(0, line.size()-1);
       //std::cout << line << std::endl;
       r.push_back(isolateR(line));
       g.push_back(isolateG(line));
       b.push_back(isolateB(line));
    }

    GLuint vertex_shader, fragment_shader, program;
    if (!glfwInit()) return 1;
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Image", NULL, NULL);
    if (!window) return 1;
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(2);
    glViewport(0, 0, 1920, 1080);

    // draw to a window pixel by pixel
    while (!glfwWindowShouldClose(window)) {
        glLoadIdentity();
        glOrtho(0.0f, 1920, 1080, 0.0f, 0.0f, 1.0f);
        glBegin(GL_POINTS);
        for (size_t i = 0; i < r.size(); ++i) {
            //SetPixel(hdc, x[i], y[i], RGB(r[i], g[i], b[i]));
            //Sleep(5);

            glColor3ub(r[i], g[i], b[i]);
            for (size_t x_coord : x[i]) {
                for (size_t y_coord : y[i]) {
                    glVertex2i(x_coord, y_coord);
                }
            }
        }
        glEnd();
        Sleep(50); // limit cpu usage. constant image, framerate doesn't matter
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
