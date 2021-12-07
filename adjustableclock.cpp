// Copyright 2021 Landon Kushimi lsk1801@bu.edu Homoon Jung brianhmj@bu.edu
// This program makes a window, and
// shows an analog and digital clock
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <chrono>
#include <cmath>

int main(int argc, char* argv[]) {
  // Declare variables
  int secAdjust;
  float second = 60;

  // Logic to check input, if no input adjust = 0
  if (argc < 2) {
    secAdjust = 0;
  } else {
    secAdjust = std::atoi(argv[1]);
  }

  // Configure the render window and sizes of clock hands
  sf::RenderWindow window(sf::VideoMode(200, 200),
                          "lsk1801@bu.edu/brianhmj@bu.edu");
  float hourHandLength = (10.0f / 16.0f) * 75;
  float minuteHandLength = (14.0f / 16.0f) * 75;
  float secondHandLength = (15.0f / 16.0f) * 75;
  float hourHandWidth = 3.0f;
  float minuteHandWidth = 3.0f;
  float secondHandWidth = 1.5f;
  float hourHandAngle = 0.0f;
  float minuteHandAngle = 0.0f;
  float secondHandAngle = 0.0f;

  sf::RectangleShape hourHand;
  hourHand.setPosition(100, 100 - hourHandWidth / 2);
  hourHand.setSize(sf::Vector2f(hourHandLength, hourHandWidth));
  hourHand.setFillColor(sf::Color::Blue);
  sf::RectangleShape minuteHand;
  minuteHand.setPosition(100, 100 - minuteHandWidth / 2);
  minuteHand.setSize(sf::Vector2f(minuteHandLength, minuteHandWidth));
  minuteHand.setFillColor(sf::Color::White);
  sf::RectangleShape secondHand;
  secondHand.setPosition(100, 100 - secondHandWidth / 2);
  secondHand.setSize(sf::Vector2f(secondHandLength, secondHandWidth));
  secondHand.setFillColor(sf::Color::Red);

  // Opening the window with clock
  while (window.isOpen()) {
    sf::Event Event;
    std::cout.precision(18);
    std::time_t time = std::time(NULL) + secAdjust;
    std::tm now = *std::localtime(&time);

    // Initialize and populate variables with different time formats
    struct tm * finalTime;
    finalTime = localtime(&time);
    std::string timeString = std::ctime(&time);
    char buffer[1];
    timeString = strftime(buffer, 50, "%X", finalTime);

    // Logic to set font with error check
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf")) {
      std::cout << "You don't have the font file." << std::endl;
      return 0;
    }
    sf::Text text(buffer, font, 10);

    float tempSecond = second;
    float year = 1900 + now.tm_year;
    float month = now.tm_mon;
    float day = now.tm_mday;
    float hour = now.tm_hour;
    float minute = now.tm_min;
    second = now.tm_sec;

    hourHandAngle = (hour / 12.0f) * 360.0f - 90.0f;
    minuteHandAngle = (minute / 60.0f) * 360.0f - 90.0f;
    secondHandAngle = (second / 60.0f) * 360.0f - 90.0f;
    hourHand.setRotation(hourHandAngle);
    minuteHand.setRotation(minuteHandAngle);
    secondHand.setRotation(secondHandAngle);

    // Printing the time in terminal
    if (tempSecond != second) {
      std::cout << asctime(localtime(&time)) << std::endl;
    }

    // If window is closed, close program
    while (window.pollEvent(Event)) {
      if (Event.type == sf::Event::Closed) {
        window.close();
        break;
      }
    }

    // Displaying everything
    window.clear(sf::Color::Black);
    window.draw(hourHand);
    window.draw(minuteHand);
    window.draw(secondHand);
    window.draw(text);
    window.display();
  }
}
