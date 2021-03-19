// Transport.cpp : https://www.coursera.org/ C++ Development Fundamentals: Black Belt, Week 1.
// Task: Transport Guide, Part F. Implement SVG library.


#include "svg.h"

#include <iostream>
#include <string>

struct Point {
    double x;
    double y;
};

struct Rgb {
    uint16_t red;
    uint16_t green;
    uint16_t blue;
};

struct Color {

};


class Figure {
private:
    Color fill;
    Color stroke_color;
    double stroke_width;
    std::string stroke_linecap, stroke_linejoin;
public:
    void SetFillColor(const Color&) { //задаёт значение свойства fill — цвет заливки.Значение по умолчанию — NoneColor.

    }
    void SetStrokeColor(const Color&) { //задаёт значение свойства stroke — цвет линии.Значение по умолчанию — NoneColor.

    }
    void SetStrokeWidth(double) { //задаёт значение свойства stroke - width — толщину линии.Значение по умолчанию — 1.0.

    }
    void SetStrokeLineCap(const std::string&) { //задаёт значение свойства stroke - linecap — тип формы конца линии.По умолчанию свойство не выводится.

    }
    void SetStrokeLineJoin(const std::string&) { //задаёт значение свойства stroke - linejoin — тип формы соединения линий.По умолчанию свойство не выводится.

    }
};

class Circle : public Figure {
private:
    double cx, cy;
    double r;
public:
    void SetCenter(Point) // задаёт значения свойств cx и cy — координаты центра круга.Значения по умолчанию — 0.0.
    {}
    void SetRadius(double) // задаёт значение свойства r — радиус круга.Значение по умолчанию — 1.0.
    {}

};

class Polyline : public Figure {
    void AddPoint(Point)  //добавляет вершину ломаной — элемент свойства points, записываемый в виде x, y и отделяемый пробелами от соседних элементов(см.примеры).Значение свойства по умолчанию — пустая строка.
    {}
};

class Text : public Figure {
    void SetPoint(Point) //задаёт значения свойств x и y — координаты текста.Значения по умолчанию — 0.0.
    {}
    void SetOffset(Point) //задаёт значения свойств dx и dy — величины отступа текста от координаты.Значения по умолчанию — 0.0.
    {}
    void SetFontSize(uint32_t) //задаёт значение свойства font - size — размер шрифта.Значение по умолчанию — 1.
    {}
    void SetFontFamily(const std::string&) //задаёт значение свойства font - family — название шрифта.По умолчанию свойство не выводится.
    {}
    void SetData(const std::string&) //задаёт содержимое тега <text> — непосредственно выводимый текст.По умолчанию текст пуст.
    {}
};

class Document {

    void Add() {
    
    }

    void Render() {

    }

};

int main() {
    

    return 0;
}
