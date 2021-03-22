// Transport.cpp : https://www.coursera.org/ C++ Development Fundamentals: Black Belt, Week 1.
// Task: Transport Guide, Part F. Implement SVG library.


//#include "svg.h"

#include <iostream>
#include <string>
#include <optional>
#include <vector>
#include <memory>
#include <variant>

namespace Svg {

    struct Point {
        double x;
        double y;
    };

    struct Rgb {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    };

    struct Color {
    //private:
        //std::variant<Rgb, std::string> color = "none";
        std::string color = "none";
    public:
        Color() = default;
        Color(const std::string& str) { color = str; }
        //Color(const Rgb& rgb) { color = rgb; }
        Color(const char* c) { color = c; }
         
    };


    class Figure {
    private:
        const std::string my_type;
        //Color fill_color;
        std::string fill_color;
        Color stroke_color;
        double stroke_width;
        std::optional<std::string> stroke_linecap;
        std::optional<std::string> stroke_linejoin;
    public:
        //Figure(std::string f_type) : my_type(f_type) {}
        Figure() = default;

        virtual void SetFillColor(const Color& c) { //задаёт значение свойства fill — цвет заливки.Значение по умолчанию — NoneColor.
            fill_color = c.color;
        }
        virtual void SetStrokeColor(const Color& c) { //задаёт значение свойства stroke — цвет линии.Значение по умолчанию — NoneColor.
            stroke_color.color = c.color;
        }
        virtual void SetStrokeWidth(double w) { //задаёт значение свойства stroke - width — толщину линии.Значение по умолчанию — 1.0.
            stroke_width = w;
        }
        virtual void SetStrokeLineCap(const std::string& l_c) { //задаёт значение свойства stroke - linecap — тип формы конца линии.По умолчанию свойство не выводится.
            stroke_linecap = l_c;
        }
        virtual void SetStrokeLineJoin(const std::string& l_j) { //задаёт значение свойства stroke - linejoin — тип формы соединения линий.По умолчанию свойство не выводится.
            stroke_linejoin = l_j;
        }
        std::string GetFillColor() const { return fill_color; }
    };

    class Circle : public Figure {
    private:
        double cx = 0.0, cy = 0.0;
        double cr = 1.0;
    public:
        Circle() = default;
        void SetFillColor(const Color& c) override { Figure::SetFillColor(c); }
        void SetCenter(Point p) { // задаёт значения свойств cx и cy — координаты центра круга.Значения по умолчанию — 0.0.
            cx = p.x; cy = p.y;
        }
        void SetRadius(double r) { // задаёт значение свойства r — радиус круга.Значение по умолчанию — 1.0.
            cr = r;
        }
        double GetCenterX() const { return cx; }
        double GetCenterY() const { return cy; }
        double GetRadius() const { return cr; }
    };

    class Polyline : public Figure {
    private:
        std::vector<Point> vertices{};
    public:
        void AddPoint(Point p) { //добавляет вершину ломаной — элемент свойства points, записываемый в виде x, y и отделяемый пробелами от соседних элементов(см.примеры).Значение свойства по умолчанию — пустая строка.
            vertices.push_back(p);
        }
    };

    class Text : public Figure {
    private:
        Point onset{ 0.0, 0.0 }, offset{ 0.0, 0.0 };
        uint32_t font_size = 1;
        std::optional<std::string> font_name;
        std::string text = "";
    public:
        void SetPoint(Point p) { //задаёт значения свойств x и y — координаты текста.Значения по умолчанию — 0.0.
            onset.x = p.x; onset.y = p.y;
        }
        void SetOffset(Point p) { //задаёт значения свойств dx и dy — величины отступа текста от координаты.Значения по умолчанию — 0.0.
            offset.x = p.x; offset.y = p.y;
        }
        void SetFontSize(uint32_t f_s) { //задаёт значение свойства font - size — размер шрифта.Значение по умолчанию — 1.
            font_size = f_s;
        }
        void SetFontFamily(const std::string& f_n) { //задаёт значение свойства font - family — название шрифта.По умолчанию свойство не выводится.
            font_name = f_n;
        }
        void SetData(const std::string& t) { //задаёт содержимое тега <text> — непосредственно выводимый текст.По умолчанию текст пуст.
            text = t;
        }
    };

    class Document {
    private:
        std::vector<std::shared_ptr<Figure>> v_ptr_figures;
        std::vector<Figure> v_figures;
    public:
        //std::vector<Figure> figures;
        void Add(const Figure& f) {
            auto current_figure_ptr = std::make_shared<Figure>(f);
            v_ptr_figures.push_back(current_figure_ptr);
            v_figures.push_back(f);
        }

        std::vector<Figure> GetVector() {
            return v_figures;
        }

        std::vector<std::shared_ptr<Figure>> GetVectorPtr() {
            return v_ptr_figures;
        }

    };
}

int main() {
    Svg::Document doc;

    Svg::Point point{ 50, 50 };
    Svg::Circle c;
    c.SetFillColor("white");
    c.SetRadius(6);
    c.SetCenter(point);

    doc.Add(c);
    auto v = doc.GetVectorPtr();
    auto fig = *v[0];
    //std::cout <<  << '\t' << figures[0].GetCenterY() << '\t' << doc[0].GetRadius() << '\t' << doc[0].GetFillColor();
    return 0;
}
