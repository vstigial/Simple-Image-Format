#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <Windows.h>

int isolateR(std::string str) {
    //std::cout << str.find(",") << std::endl;
    std::string red = str.substr(0, str.find(","));
    //std::cout << r << std::endl;
    return static_cast<uint16_t>(std::stoi(red));
}

int isolateG(std::string str) {
    std::string green = str.substr(str.find(",")+1, str.find(",")+1);
    //std::cout << green << std::endl;
    return static_cast<uint16_t>(std::stoi(green));
}

int isolateB(std::string str) { 
    std::string blue = str.substr(str.find(",", str.find(",")+1)+1, std::string::npos);
    //std::cout << blue << std::endl;
    return static_cast<uint16_t>(std::stoi(blue));
}

int main(int argc, char* argv[]) {
    if (!argv[1]) {
        std::cerr << "You must provide a file to open!\n    program.exe <file>" << std::endl;
        return 1;
    }
    HDC hdc = GetDC(0);
    std::ifstream File(argv[1]);
    if (!File) {
        std::cerr << "Provide a valid file path!" << std::endl;
        return 1;
    }
    std::string text;
    std::vector<std::string> position_lines;
    std::vector<std::string> color_lines;
    std::vector<uint16_t> r, g, b;
    std::vector<size_t> x, y;

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
        size_t x_pix = std::stoi(line.substr(0, line.find(" ")));
        x.push_back(x_pix);
        size_t y_pix = std::stoi(line.substr(line.find(" ")+1, std::string::npos));
        y.push_back(y_pix);
    }

    for (std::string line : color_lines) {
       line = line.substr(1, std::string::npos);
       line = line.substr(0, line.size()-1);
       //std::cout << line << std::endl;
       r.push_back(isolateR(line));
       g.push_back(isolateG(line));
       b.push_back(isolateB(line));
    }


    // draw directly on screen for now
    while (true) {
        for (size_t i = 0; i < r.size(); ++i) {
            SetPixel(hdc, x[i], y[i], RGB(r[i], g[i], b[i]));
            //Sleep(5);    
        }
    } 
    return 0;
}
