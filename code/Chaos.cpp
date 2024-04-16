// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

void createTextObject(Text& text, Font& font, string content);


int main() {
    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game", Style::Default);
    srand(time(NULL));

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    const int POINTS_NUMBER = 10;

    // Text content
    Text askVertextInput;
    Text askPointInput;

    Font font;
    font.loadFromFile("fonts/arial.ttf");
    createTextObject(askVertextInput, font, "Click on any three point to create a triangle");
    createTextObject(askPointInput, font, "Click on any point inside the triangle to run the algorithm");


    while (window.isOpen()) {
        /*
        ****************************************
        Handle the players input
        ****************************************
        */
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                // Quit the game when the window is closed
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if (vertices.size() < 3) {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0) {
                        ///fourth click
                        ///push back to points vector
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        /*
        ****************************************
        Update
        ****************************************
        */

        if (points.size() > 0) {
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.
            while (points.size() <= POINTS_NUMBER) {
                int vertexIndex = rand() % 3;
                cout << "Current vertex index: " << vertexIndex << endl;
                Vector2f currentVertex = vertices[vertexIndex];
                Vector2f lastPoint = points[points.size() - 1];
                float midX = (currentVertex.x + lastPoint.x) / 2.0f;
                float midY = (currentVertex.y + lastPoint.y) / 2.0f;
                cout << "Midpoint X: " << midX << " Y: " << midY << endl;
                points.push_back(Vector2f(midX, midY));
            }
        }

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();

        if (vertices.size() < 3) {
            window.draw(askVertextInput);
        }

        if (vertices.size() == 3 && points.size() == 0) {
            window.draw(askPointInput);
        }

        for (int i = 0; i < vertices.size(); i++) {
            RectangleShape rect(Vector2f(10, 10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }

        for (int i = 0; i < points.size(); i++) {
            CircleShape circle(1);
            circle.setPosition(Vector2f(points[i].x, points[i].y));
            circle.setFillColor(Color::White);
            window.draw(circle);
        }
        window.display();
    }
}

void createTextObject(Text& text, Font& font, string content) {
    text.setFont(font);
    text.setString(content);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left +
        textRect.width / 2.0f,
        textRect.top +
        textRect.height / 2.0f);
    text.setPosition(1920 / 2.0f, 60);
}
