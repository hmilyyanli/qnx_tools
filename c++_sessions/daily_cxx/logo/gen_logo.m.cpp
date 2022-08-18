#include <cairo/cairo.h>
#include <cairo/cairo-svg.h>

#include <pango/pangocairo.h>
// #include <fontconfig/fontconfig.h> // for a different font familiy

#include <gsl/gsl> // util

#include <eigen3/Eigen/Eigen>

#include <iostream>
#include <cmath> // cos, sin
#include <string> // string
#include <vector> // vector

template<class T>
constexpr T pi = static_cast<T>(3.1415926535897932385L);

constexpr auto round_to_int(double n) -> int {
    return static_cast<int>(n + .5);
}

constexpr auto img_height{ 1032 };

constexpr auto char_size{ img_height * 0.3 };

const ::std::string text{ "DAILY C++" };
const auto img_width{ ::gsl::narrow<int>(text.size()) * ::round_to_int(char_size) };

class Degree {
    static constexpr auto _value_max{ 360 };
    static constexpr auto _value_min{ 0 };

    double _value; // >= 0, < 360

public:
    explicit constexpr Degree(double value) :_value{ value } {
        if (!((this->_value >= 0) && (this->_value < 360)))
            throw ::std::logic_error{ "0 <= alpha < 360" };
    }

    constexpr auto& operator+=(Degree rhs)& {
        *this = ::Degree{ this->_value + rhs._value };
        return *this;
    }

    constexpr auto value() const { return this->_value; }
};

constexpr auto operator+(Degree x, Degree y) {
    return x += y;
}

struct DegreeUtil {
    static constexpr auto to_radian(Degree alpha)
        //    2pi * alpha / 360
    {
        constexpr auto full_arc{ 2. * ::pi<double> };
        return full_arc * alpha.value() / 360.;
    }
};

auto get_pentagon_edges(double x_center, double y_center, double radius) {
    ::std::vector<::Eigen::Vector2d> result{};
    constexpr auto pentagon_size{ 5 };
    constexpr auto full_circle{ 2. * ::pi<double> };
    for (auto i{ 0 }; i != pentagon_size; ++i) {
        const auto arg{ full_circle * i / pentagon_size - full_circle * .25 };
        result.push_back(::Eigen::Vector2d{ ::std::cos(arg) * radius + x_center, ::std::sin(arg) * radius + y_center
            });
    }
    return result;
}

void draw_logo_circle(::cairo_t* cr)
//    Draw circle for the first letter.
{
    constexpr auto r{ img_height * .5 };
    constexpr auto x{ r };
    constexpr auto y{ r };
    ::cairo_move_to(cr, x, y);
    constexpr ::Degree deg_begin{ 45. + 90. };
    constexpr auto arc_begin{ ::DegreeUtil::to_radian(deg_begin) };
    constexpr auto arc_end{ ::DegreeUtil::to_radian(deg_begin + ::Degree{180}) };
    //::cairo_arc(cr, x, y, r, arc_begin, arc_end);
    //::cairo_close_path(cr);
    //::cairo_set_source_rgba(cr, 0.651, 0.3686, 0.1804, 1); // orange brown
    //::cairo_fill(cr);

    //::cairo_arc_negative(cr, x, y, r, arc_begin, arc_end);
    //::cairo_close_path(cr);
    //::cairo_set_source_rgba(cr, 0.2627, 0.149, 0.1843, 1); // Bordeaux Red
    //::cairo_fill(cr);
    const auto pentagon_edges{ ::get_pentagon_edges(x, y, r) };
    const auto last_idx = ::gsl::narrow<int>(pentagon_edges.size()) - 1;
    for (auto i{ 0 }; i <= last_idx; ++i) {
        const auto lower_idx{ i == 0 ? last_idx : i - 1 }; // bug is hidding for i == 0
        const auto upper_idx{ i == last_idx ? 0 : i + 1 };
        const auto& prev_pt{ pentagon_edges.at(lower_idx) };
        const auto& pt{ pentagon_edges.at(i) };
        const auto& next_pt{ pentagon_edges.at(upper_idx) };
        constexpr auto partial_dist{ 0.05 };
        const ::Eigen::Vector2d a{ pt + (pt - prev_pt) * partial_dist };
        const ::Eigen::Vector2d b{ pt + (next_pt - pt) * partial_dist };
        const ::Eigen::Vector2d c{ pt + (next_pt - pt) * (1. - partial_dist) };
        if (i == 0)
            ::cairo_move_to(cr, a.x(), a.y());
        ::cairo_curve_to(cr, pt.x(), pt.y(), pt.x(), pt.y(), b.x(), b.y());
        ::cairo_line_to(cr, c.x(), c.y());
    }
    auto linpat = cairo_pattern_create_linear(0., 0., 2. * r, 2. * r);
    cairo_pattern_add_color_stop_rgba(linpat, 0.00, 21. / 255, 153. / 255, 87. / 255, 1.);
    cairo_pattern_add_color_stop_rgba(linpat, 1., 21. / 255, 87. / 255, 153. / 255, 1.);
    // ::cairo_set_source_rgba(cr, .651, .3686, 0.1804, 1); // ??
    ::cairo_set_source(cr, linpat);
    ::cairo_fill(cr);

    cairo_set_font_size(cr, ::char_size * 1.5);
    cairo_set_source_rgb(cr, 1., 1., 1.);
    cairo_move_to(cr, r - char_size, r + char_size * .5);
    cairo_show_text(cr, "DC");
}

void add_color_background(cairo_t* cr) {
    auto linpat = cairo_pattern_create_linear(0., 0., img_width, 0.);
    ::cairo_pattern_add_color_stop_rgba(linpat, 0., 21. / 255, 87. / 255, 153. / 255, 1.);
    ::cairo_pattern_add_color_stop_rgba(linpat, 1.00, 21. / 255, 153. / 255, 87. / 255, 1.);
    ::cairo_rectangle(cr, 0, 0, ::gsl::narrow<int>(img_width), img_height);
    ::cairo_set_source(cr, linpat);
    ::cairo_fill(cr);
}

int main() {
    //std::string yourFontFilePath = "/home/testUser/bla.ttf";
    //const FcChar8* file = (const FcChar8*)yourFontFilePath.c_str();
    //FcBool fontAddStatus = FcConfigAppFontAddFile(FcConfigGetCurrent(), file);

    //cairo_surface_t* surface =
    //    cairo_image_surface_create(CAIRO_FORMAT_ARGB32, img_width, img_height);
    CAIRO_HAS_SVG_SURFACE;
    cairo_surface_t* surface =
        cairo_svg_surface_create("logo.svg",
            img_width,
            img_height);

    cairo_t* cr = cairo_create(surface);

    add_color_background(cr);

    //::cairo_rectangle(cr, 0, 0, ::gsl::narrow<int>(img_width), img_height);
    //::cairo_set_source_rgba(cr, 1., 1., 1., 1.);
    //::cairo_fill(cr);

    //auto font_description = pango_font_description_new();
    //pango_font_description_set_family(font_description, "sans");
    //pango_font_description_set_weight(font_description, PANGO_WEIGHT_BOLD);


    cairo_select_font_face(cr, "sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);

    draw_logo_circle(cr);

    cairo_set_font_size(cr, ::char_size);
    cairo_set_source_rgb(cr, 1., 1., 1.);
    //const ::Eigen::Vector3d b{ 21. / 255, 153. / 255, 87. / 255 };
    //const ::Eigen::Vector3d c{ 21. / 255, 87. / 255, 153. / 255 };
    //const ::Eigen::Vector3d m{ (b + c) * .45 };
    //::cairo_set_source_rgb(cr, m.x(), m.y(), m.z());
    cairo_move_to(cr, 3.5 * char_size, img_height * .6);
    cairo_show_text(cr, text.c_str());

    //auto layout = pango_cairo_create_layout(cr);
    //pango_layout_set_font_description(layout, font_description);

    // pango_font_description_set_absolute_size(font_description, char_size * PANGO_SCALE);

    //constexpr auto zero_terminated{ -1 };
    //pango_layout_set_text(layout, "D", zero_terminated);
    //cairo_set_source_rgb(cr, 0.0, 1.0, 1.0);
    //cairo_move_to(cr, char_size, 0);
    //pango_cairo_show_layout(cr, layout);
    //cairo_font_extents_t ex{};
    //cairo_font_extents(cr, &ex);

    //pango_layout_set_text(layout, "aily C++", zero_terminated);
    //cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);
    //::cairo_rel_move_to(cr, 15., 0);
    //pango_cairo_show_layout(cr, layout);



    // g_object_unref(layout);
    // pango_font_description_free(font_description);

    cairo_destroy(cr);
    cairo_surface_write_to_png(surface, "hello.png");

    cairo_surface_destroy(surface);
}
