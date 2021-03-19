#pragma once
#include <iostream>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <variant>
#include <vector>
 
namespace Svg {
 
struct Point {
  double x;
  double y;
};
 
struct Rgb {
  unsigned red;
  unsigned green;
  unsigned blue;
};
 
struct Rgba {
  unsigned red;
  unsigned green;
  unsigned blue;
  double alpha;
};
 
class Color {
 public:
  Color() = default;
  Color(const Rgb& rgb);
  Color(const Rgba& rgba);
  Color(const std::string& source);
  Color(const char* source);
 
 private:
  virtual std::ostream& write(std::ostream& stream) const;
  using ColorType = std::variant<Rgb, Rgba, std::string>;
  ColorType m_color = "none";
  friend std::ostream& operator<<(std::ostream& stream, Color color);
};
 
static const Color NoneColor;
 
class Figure {
 public:
  Figure() = default;
  Figure(const Figure&) = default;
  Figure(Figure&& other) = default;
  Figure& operator=(const Figure&) = default;
  Figure& operator=(Figure&&) = default;
  Figure& SetFillColor(Color);
  Figure& SetStrokeColor(Color);
  Figure& SetStrokeWidth(double);
  Figure& SetStrokeLineCap(std::string);
  Figure& SetStrokeLineJoin(std::string);
  using FigureHolder = std::unique_ptr<Figure>;
  virtual FigureHolder Clone() const = 0;
  virtual FigureHolder Move() = 0;
  virtual ~Figure(){};
 
 protected:
  virtual std::ostream& write(std::ostream& stream) const;
 
 private:
  Color m_fill_color = NoneColor;
  Color m_stroke_color = NoneColor;
  double m_width = 1.0;
  std::optional<std::string> m_line_cap;
  std::optional<std::string> m_line_join;
  friend std::ostream& operator<<(std::ostream& stream, const Figure& figure);
};
 
template <typename Derived>
class FigureAdapter : public Figure {
 public:
  Derived& SetFillColor(Color color) & {
    return static_cast<Derived&>(Figure::SetFillColor(color));
  };
  Derived& SetStrokeColor(Color color) & {
    return static_cast<Derived&>(Figure::SetStrokeColor(color));
  };
  Derived& SetStrokeWidth(double width) & {
    return static_cast<Derived&>(Figure::SetStrokeWidth(width));
  };
  Derived& SetStrokeLineCap(std::string source) & {
    return static_cast<Derived&>(Figure::SetStrokeLineCap(std::move(source)));
  };
  Derived& SetStrokeLineJoin(std::string source) & {
    return static_cast<Derived&>(Figure::SetStrokeLineJoin(std::move(source)));
  };
 
  Derived&& SetFillColor(Color color) && {
    return static_cast<Derived&&>(Figure::SetFillColor(color));
  };
  Derived&& SetStrokeColor(Color color) && {
    return static_cast<Derived&&>(Figure::SetStrokeColor(color));
  };
  Derived&& SetStrokeWidth(double width) && {
    return static_cast<Derived&&>(Figure::SetStrokeWidth(width));
  };
  Derived&& SetStrokeLineCap(std::string source) && {
    return static_cast<Derived&&>(Figure::SetStrokeLineCap(std::move(source)));
  };
  Derived&& SetStrokeLineJoin(std::string source) && {
    return static_cast<Derived&&>(Figure::SetStrokeLineJoin(std::move(source)));
  };
 
  FigureHolder Clone() const override {
    return std::make_unique<Derived>(static_cast<const Derived&>(*this));
  };
  FigureHolder Move() override {
    return std::make_unique<Derived>(std::move(static_cast<Derived&>(*this)));
  };
};
 
class Text : public FigureAdapter<Text> {
 public:
  Text& SetPoint(Point) &;
  Text&& SetPoint(Point) &&;
  Text& SetOffset(Point) &;
  Text&& SetOffset(Point) &&;
  Text& SetFontSize(uint32_t) &;
  Text&& SetFontSize(uint32_t) &&;
  Text& SetFontWeight(const std::string&) &;
  Text&& SetFontWeight(const std::string&) &&;
  Text& SetFontFamily(const std::string&) &;
  Text&& SetFontFamily(const std::string&) &&;
  Text& SetData(const std::string&) &;
  Text&& SetData(const std::string&) &&;
 
 private:
  virtual std::ostream& write(std::ostream&) const override;
  Point m_point;
  Point m_offset;
  uint32_t m_font_size;
  std::optional<std::string> m_font_family;
  std::optional<std::string> m_font_weight;
  std::string m_data;
};
 
class Circle : public FigureAdapter<Circle> {
 public:
  Circle& SetCenter(Point) &;
  Circle&& SetCenter(Point) &&;
  Circle& SetRadius(double) &;
  Circle&& SetRadius(double) &&;
 
 private:
  virtual std::ostream& write(std::ostream& stream) const override;
  Point m_center;
  double m_radius;
};
 
class Polyline : public FigureAdapter<Polyline> {
 public:
  Polyline& AddPoint(Point point) &;
  Polyline&& AddPoint(Point point) &&;
 
 private:
  virtual std::ostream& write(std::ostream& stream) const override;
  std::vector<Point> m_points;
};
 
class Document {
 public:
  void Add(Figure&& figure);
  void Add(const Figure& figure);
  static void PrintOpen(std::ostream& stream);
  static void PrintClose(std::ostream& stream);
  void PrintBody(std::ostream& stream) const;
  void Render(std::ostream& stream) const;
  void Clear();
 
 private:
  std::vector<Figure::FigureHolder> m_figures;
};
 
};  // namespace Svg