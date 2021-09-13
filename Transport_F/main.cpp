// Transport.cpp : https://www.coursera.org/ C++ Development Fundamentals: Black Belt, Week 1.
// Task: Implement simplify SVG library. (CRTP method is used) 

#include "svg.h"

int main() {
    Svg::Document svg;

    svg.Add(
        Svg::Polyline{}
        .SetStrokeColor(Svg::Rgb{ 140, 198, 63 })  
        .SetStrokeWidth(16)
        .SetStrokeLineCap("round")
        .AddPoint({ 50, 50 })
        .AddPoint({ 250, 250 })
    );

    for (const auto& point : { Svg::Point{50, 50}, Svg::Point{250, 250} }) {
        svg.Add(
            Svg::Circle{}
            .SetFillColor("white")
            .SetRadius(6)
            .SetCenter(point)
        );
    }

    svg.Add(
        Svg::Text{}
        .SetPoint({ 50, 50 })
        .SetOffset({ 10, -10 })
        .SetFontSize(20)
        .SetFontFamily("Verdana")
        .SetFillColor("black")
        .SetData("C")
    );

    svg.Add(
        Svg::Text{}
        .SetPoint({ 250, 250 })
        .SetOffset({ 10, -10 })
        .SetFontSize(20)
        .SetFontFamily("Verdana")
        .SetFillColor("black")
        .SetData("C++")
    );

    svg.Add(
        Svg::Text{}
        .SetPoint({ 2.000000, 30.000000 })
        .SetOffset({ 1.000000, 2.000000 })
        .SetFontSize(30)
        .SetFillColor(Svg::Rgb{ 5, 155, 37 })
        .SetStrokeColor(Svg::Rgb{ 145, 135, 200, 0.75 }) 
        .SetStrokeWidth(5.500000)
        .SetData("txt")
    );
       
    svg.Render(std::cout);

    return 0;
}
