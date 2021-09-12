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
        unsigned red;
        unsigned green;
        unsigned blue;
        std::optional<double> alpha;
    };

    struct Color {
        std::variant<Rgb, std::string> m_color = "none";
        Color() = default;
        Color(const std::string& str) { m_color = str; }
        Color(const char* c) { m_color = c; }
        Color(const Rgb& rgb) { m_color = rgb; }
        friend std::ostream& operator<<(std::ostream& stream, Color& color);
    };

    static Color NoneColor = "none";

    class Figure {
    private:
        std::string my_type;
        Color m_fill_color = NoneColor;
        Color m_stroke_color = NoneColor;
        double m_stroke_width = 1.0;
        std::optional<std::string> m_linecap;
        std::optional<std::string> m_linejoin;
    public:
        void SetMyType(std::string m_t) { my_type = m_t; }
        Figure& SetFillColor(const Color& c);
        Figure& SetStrokeColor(const Color& c);
        Figure& SetStrokeWidth(double w) { m_stroke_width = w; return *this; }
        Figure& SetStrokeLineCap(const std::string& l_c) { m_linecap = l_c; return *this; }
        Figure& SetStrokeLineJoin(const std::string& l_j) { m_linejoin = l_j; return *this; }
        std::ostream& GetBaseStream(std::ostream& stream);
        virtual std::shared_ptr<Figure> GetObjPtr() const = 0;
        virtual std::ostream& GetChildStream(std::ostream& stream) = 0;
        virtual ~Figure() {};
    };

    template<typename Derived>
    class Figure_CRTP : public Figure {
    public:
        Derived& SetFillColor(const Color& c) { return static_cast<Derived&>(Figure::SetFillColor(c)); }
        Derived& SetStrokeColor(const Color& c) { return static_cast<Derived&>(Figure::SetStrokeColor(c)); }
        Derived& SetStrokeWidth(double w) { return static_cast<Derived&>(Figure::SetStrokeWidth(w)); }
        Derived& SetStrokeLineCap(const std::string& l_c) { return static_cast<Derived&>(Figure::SetStrokeLineCap(l_c)); }
        Derived& SetStrokeLineJoin(const std::string& l_j) { return static_cast<Derived&>(Figure::SetStrokeLineJoin(l_j)); }
        std::shared_ptr<Figure> GetObjPtr() const override { return std::make_shared<Derived>(static_cast<const Derived&>(*this)); }
    };

    class Circle : public Figure_CRTP<Circle> {
    private:
        double cx = 0.0, cy = 0.0; // x,y Circle center
        double cr = 1.0; // Circle radius
    public:
        Circle() { Figure::SetMyType("circle"); }
        Circle& SetCenter(Point p) { cx = p.x; cy = p.y; return *this; }
        Circle& SetRadius(double r) { cr = r; return *this; }
        std::ostream& GetChildStream(std::ostream& stream) override;
    };

    class Polyline : public Figure_CRTP<Polyline> {
    private:
        std::vector<Point> m_vertices{};
    public:
        Polyline() { Figure::SetMyType("polyline"); }
        Polyline& AddPoint(Point p) { m_vertices.push_back(p); return *this; }
        std::ostream& GetChildStream(std::ostream& stream) override;
    };

    class Text : public Figure_CRTP<Text> {
    private:
        Point m_onset{ 0.0, 0.0 }, m_offset{ 0.0, 0.0 };
        uint32_t m_font_size = 1;
        std::optional<std::string> m_font_name;
        std::string m_text = "";
    public:
        Text() { Figure::SetMyType("text"); }
        Text& SetPoint(Point p) { m_onset = p; return *this; }
        Text& SetOffset(Point p) { m_offset = p; return *this; }
        Text& SetFontSize(uint32_t f_s) { m_font_size = f_s; return *this; }
        Text& SetFontFamily(const std::string& f_n) { m_font_name = f_n; return *this; }
        Text& SetData(const std::string& t) { m_text = t; return *this; }
        std::ostream& GetChildStream(std::ostream& stream) override;
    };

    class Document {
    private:
        std::vector<std::shared_ptr<Figure>> m_ptrs;
    public:
        void Add(const Figure& f) { m_ptrs.push_back(f.GetObjPtr()); }
        void Render(std::ostream& os);
    };
} // namespace Svg


using namespace std;

namespace Svg {

    std::ostream& operator<<(std::ostream& stream, Color& color) {
        if (color.m_color.index() == 0) {
            stream << "rgb("
                << std::get<Rgb>(color.m_color).red << ','
                << std::get<Rgb>(color.m_color).green << ','
                << std::get<Rgb>(color.m_color).blue;
            if (std::get<Rgb>(color.m_color).alpha) {
                stream << ',' << std::get<Rgb>(color.m_color).alpha.value();
            }
            stream << ')';
        }
        else { stream << std::get<std::string>(color.m_color); }
        return stream;
    }

    Figure& Figure::SetFillColor(const Color& c) {
        if (c.m_color.index() == 0) { m_fill_color = std::get<Rgb>(c.m_color); }
        else { m_fill_color = std::get<std::string>(c.m_color); }
        return *this;
    }

    Figure& Figure::SetStrokeColor(const Color& c) {
        if (c.m_color.index() == 0) { m_stroke_color = std::get<Rgb>(c.m_color); }
        else { m_stroke_color = std::get<std::string>(c.m_color); }
        return *this;
    }

    std::ostream& Figure::GetBaseStream(std::ostream& stream) {
        stream << "<" << my_type
            << " fill=\"" << m_fill_color << "\""
            << " stroke=\"" << m_stroke_color << "\""
            << " stroke-width=\"" << m_stroke_width << "\"";
        if (m_linecap) { stream << " stroke-linecap=\"" << m_linecap.value() << "\""; }
        if (m_linejoin) { stream << " stroke-linejoin=\"" << m_linejoin.value() << "\""; }
        stream << " ";
        return stream;
    }

    std::ostream& Circle::GetChildStream(std::ostream& stream) {
        return stream << "cx=\"" << cx << "\" cy=\"" << cy << "\" r=\"" << cr << "\" />\n";
    }

    std::ostream& Polyline::GetChildStream(std::ostream& stream) {
        stream << "points=\"";
        for (auto& vertice : m_vertices) {
            stream << vertice.x << ',' << vertice.y << ' ';
        }
        stream << "\" />\n";
        return stream;
    }

    std::ostream& Text::GetChildStream(std::ostream& stream) {
        stream << "x=\"" << m_onset.x << "\" y=\"" << m_onset.y
            << "\" dx=\"" << m_offset.x << "\" dy=\"" << m_offset.y;
        if (m_font_name) { stream << "\" font-family=\"" << m_font_name.value(); }
        stream << "\" font-size=\"" << m_font_size << "\" >"
            << m_text << "</text>\n";
        return stream;
    }

    std::ostream& GetHeaderStream(std::ostream& stream) {
        return stream << R"(<?xml version="1.0" encoding="UTF-8" ?>)" << '\n'
            << R"(<svg xmlns="http://www.w3.org/2000/svg" version="1.1">)" << '\n';
    }

    std::ostream& GetFooterStream(std::ostream& stream) {
        return stream << "</svg>";
    }

    void Document::Render(std::ostream& os) {
        GetHeaderStream(os);
        for (auto ptr : m_ptrs) {
            ptr->GetBaseStream(os);
            ptr->GetChildStream(os);

        }
        GetFooterStream(os);
    };
}
