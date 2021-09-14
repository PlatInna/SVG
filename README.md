Simplified library to output vector images in SVG format.

Implemented three types of objects:  
    - Circle  
    - Polyline  
    - Text  
The color can be set as a string or rgb-values.      
Method calls when creating Circle, Polyline, or Text objects can be chained. CRTP idiom is used. dir /Transport_F

#### Example
``` C++
Svg::Document svg;

svg.Add(
    Svg::Polyline{}
    .SetStrokeColor(Svg::Rgb{140, 198, 63})  // soft green
    .SetStrokeWidth(16)
    .SetStrokeLineCap("round")
    .AddPoint({50, 50})
    .AddPoint({250, 250})
);

for (const auto point : {Svg::Point{50, 50}, Svg::Point{250, 250}}) {
  svg.Add(
      Svg::Circle{}
      .SetFillColor("white")
      .SetRadius(6)
      .SetCenter(point)
  );
}

svg.Add(
    Svg::Text{}
    .SetPoint({50, 50})
    .SetOffset({10, -10})
    .SetFontSize(20)
    .SetFontFamily("Verdana")
    .SetFillColor("black")
    .SetData("C")
);
svg.Add(
    Svg::Text{}
    .SetPoint({250, 250})
    .SetOffset({10, -10})
    .SetFontSize(20)
    .SetFontFamily("Verdana")
    .SetFillColor("black")
    .SetData("C++")
);

svg.Render(std::cout);
```

#### Example output
``` xml
<?xml version="1.0" encoding="UTF-8" ?>
<svg xmlns="http://www.w3.org/2000/svg" version="1.1">
<polyline points="50,50 250,250 " fill="none" stroke="rgb(140,198,63)" stroke-width="16" stroke-linecap="round" />
<circle cx="50" cy="50" r="6" fill="white" stroke="none" stroke-width="1" />
<circle cx="250" cy="250" r="6" fill="white" stroke="none" stroke-width="1" />
<text x="50" y="50" dx="10" dy="-10" font-size="20" font-family="Verdana" fill="black" stroke="none" stroke-width="1" >C</text>
<text x="250" y="250" dx="10" dy="-10" font-size="20" font-family="Verdana" fill="black" stroke="none" stroke-width="1" >C++</text></svg>
```

![example](https://github.com/PlatInna/SVG/blob/master/Transport_F/example_out.jpg)
