#include "svg.h"

namespace svg {

    using namespace std::literals;

    void Object::Render(const RenderContext& context) const {
        context.RenderIndent();

        // Делегируем вывод тега своим подклассам
        RenderObject(context);

        context.out << std::endl;
    }

    // ---------- Document ------------------

    void Document::AddPtr(std::unique_ptr<Object>&& obj)
    {
        objects_.emplace_back(std::move(obj));
    }

    void Document::Render(std::ostream& out) const
    {
        out << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"sv << std::endl;
        out << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">"sv << std::endl;
        for (const auto& obj : objects_) {
            obj.get()->Render({ out, 0 , 2 });
        }
        out << "</svg>"sv;
    }

    // ---------- Circle ------------------

    Circle& Circle::SetCenter(Point center) {
        center_ = center;
        return *this;
    }

    Circle& Circle::SetRadius(double radius) {
        radius_ = radius;
        return *this;
    }

    void Circle::RenderObject(const RenderContext& context) const {
        auto& out = context.out;
        out << "<circle ";
        out << "cx=\""sv << center_.x << "\" cy=\""sv << center_.y << "\" "sv;
        out << "r=\""sv << radius_ << "\""sv;
        RenderAttrs(out);
        out << "/>"sv;
    }

    // ---------- Polyline ------------------

    Polyline& Polyline::AddPoint(Point point)
    {
        points_.push_back(point);
        return *this;
    }

    void Polyline::RenderObject(const RenderContext& context) const {
        auto& out = context.out;
        out << "<polyline ";

        out << "points=\""sv;
        bool flag = true;
        for (const auto& point : points_) {
            if (!flag) {
                out << " "sv;
            }
            out << point.x << ","sv << point.y;
            flag = false;
        }
        out << "\""sv;
        RenderAttrs(out);
        out << "/>"sv;
    }

    // ---------- Text ------------------

    Text& Text::SetPosition(Point pos)
    {
        pos_ = pos;
        return *this;
    }

    Text& Text::SetOffset(Point offset)
    {
        offset_ = offset;
        return *this;
    }

    Text& Text::SetFontSize(uint32_t size)
    {
        font_size_ = size;
        return *this;
    }

    Text& Text::SetFontFamily(std::string font_family)
    {
        font_family_ = font_family;
        return *this;
    }

    Text& Text::SetFontWeight(std::string font_weight)
    {
        font_weight_ = font_weight;
        return *this;
    }

    Text& Text::SetData(std::string data)
    {
        data_ = data;
        return *this;
    }

    void Text::RenderObject(const RenderContext& context) const
    {
        // <text x="35" y="20" dx="0" dy="6" font-size="12" font-family="Verdana" font-weight="bold">Hello C++</text>
        auto& out = context.out;
        out << "<text ";
        out << "x=\""sv << pos_.x << "\" y=\""sv << pos_.y << "\" ";
        out << "dx = \""sv << offset_.x << "\" dy=\""sv << offset_.y << "\" ";
        out << "font-size=\""sv << font_size_ << "\" ";
        if (!font_family_.empty()) {
            out << "font-family=\""sv << font_family_ << "\" ";
        }
        if (!font_weight_.empty()) {
            out << "font-weight=\""sv << font_weight_ << "\" ";
        }
        RenderAttrs(out);
        out << ">"sv;
        for (const auto& letter : data_) {
            switch (letter) {
            case '\"':
                out << "&quot;";
                break;

            case '\'':
                out << "&apos;";
                break;

            case '<':
                out << "&lt;";
                break;

            case '>':
                out << "&gt;";
                break;

            case '&':
                out << "&amp;";
                break;

            default:
                out << letter;
            }
        }

        out << "</text>";
    }

    std::ostream& operator<<(std::ostream& out, const StrokeLineCap& line_cap)
    {
        {
            switch (line_cap) {
            case  StrokeLineCap::BUTT:
                out << "butt";
                break;

            case StrokeLineCap::ROUND:
                out << "round";
                break;

            case StrokeLineCap::SQUARE:
                out << "square";
                break;
            }
            return out;
        }
    }

    std::ostream& operator<<(std::ostream& out, const StrokeLineJoin& line_join)
    {
        {
            switch (line_join) {
            case  StrokeLineJoin::ARCS:
                out << "arcs";
                break;
            case StrokeLineJoin::BEVEL:
                out << "bevel";
                break;
            case StrokeLineJoin::MITER:
                out << "miter";
                break;
            case StrokeLineJoin::MITER_CLIP:
                out << "miter-clip";
                break;
            case StrokeLineJoin::ROUND:
                out << "round";
                break;
            }

            return out;
        }
    }

    std::ostream& operator<<(std::ostream& out, const Color& color)
    {
        std::visit(PrintColor{ out }, color);
        return out;
    }
}  // namespace svg