#include "svg.h"

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
