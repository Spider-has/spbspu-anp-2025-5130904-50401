#include <iostream>

namespace khasnulin
{
  struct point_t
  {
    double x, y;
  };

  struct rectangle_t
  {
    double width, height;
    point_t pos;
  };

  class IShape
  {
  public:
    virtual ~IShape() = default;

    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(point_t to) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double k) = 0;
  };

  class Rectangle : public IShape
  {
  public:
    Rectangle(point_t pos, double w, double h);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t to) override;
    void move(double dx, double dy) override;
    void scale(double k) override;

  private:
    rectangle_t rect;
  };

  class Polygon : public IShape
  {
  public:
    Polygon(const point_t *points, size_t k);

    ~Polygon();

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t to) override;
    void move(double dx, double dy) override;
    void scale(double k) override;

  private:
    point_t *vertex;
    size_t size;
    point_t center;

    point_t calculateCenter();
  };

  class Xquare : public IShape
  {
  public:
    Xquare();

    ~Xquare();

    double getArea();
    rectangle_t getFrameRect();
    void move(point_t to);
    void move(double dx, double dy);
    void scale(double k);

  private:
    point_t center;
  };

  void printRectInfo(std::ostream &out, rectangle_t rect);
  rectangle_t getCommonRectangleFrame(rectangle_t r1, rectangle_t r2);
  void calculateAndPrintFiguresInfo(std::ostream &out, IShape **shapes, size_t size);
  rectangle_t calculateFiguresGeneralRectangleFrame(IShape **shapes, size_t size);

  void isotropicScaling(IShape &shape, point_t scale_pt, double scale);

  point_t getRightTop(rectangle_t frame);

  point_t operator-(point_t p_t1, point_t p_t2);
  point_t operator+(point_t p_t1, point_t p_t2);
  point_t operator*(point_t p_t1, double k);
  point_t operator/(point_t p_t1, double k);

  double triagleSignedArea(point_t v1, point_t v2);
  point_t getTriangleCenter(point_t v1, point_t v2);

  point_t *copy(const point_t *from, point_t *to, size_t k);
}

int main()
{
  using namespace khasnulin;
  IShape *shapes[3];
  size_t size = 0;
  size_t code = 0;
  try
  {

    shapes[size++] = new Rectangle({1, 1}, 5, 3);
    shapes[size++] = new Rectangle({0, 0}, 2, 2);

    double scale;
    point_t scale_pt;

    std::cin >> scale_pt.x >> scale_pt.y;
    std::cin >> scale;
    if (std::cin.fail())
    {
      throw std::runtime_error("incorrect input: fail to read arguments, must be 3 double");
    }
    if (scale <= 0)
    {
      throw std::runtime_error("incorrect input: scale coefficient must be more than zero");
    }

    std::cout << "before figures scaling: \n";
    calculateAndPrintFiguresInfo(std::cout, shapes, size);

    for (size_t i = 0; i < size; i++)
    {
      isotropicScaling(*shapes[i], scale_pt, scale);
    }
    std::cout << "\nafter figures scaling: \n";
    calculateAndPrintFiguresInfo(std::cout, shapes, size);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << "\n";
    code = 1;
  }
  catch (...)
  {
    std::cerr << "unknown error\n";
    code = 1;
  }

  for (size_t i = 0; i < size; i++)
  {
    delete shapes[i];
  }
  return code;
}

khasnulin::Rectangle::Rectangle(point_t pos, double w, double h):
    rect({w, h, pos})
{
  if (w <= 0.0 || h <= 0.0)
  {
    throw std::invalid_argument("incorrect rectangle creation: width and height must be positive");
  }
}

double khasnulin::Rectangle::getArea() const
{
  return rect.width * rect.height;
}

khasnulin::rectangle_t khasnulin::Rectangle::getFrameRect() const
{
  return rect;
}

void khasnulin::Rectangle::move(double dx, double dy)
{
  rect.pos.x += dx;
  rect.pos.y += dy;
}

void khasnulin::Rectangle::move(point_t to)
{
  rect.pos = to;
}

void khasnulin::Rectangle::scale(double k)
{
  if (k <= 0.0)
  {
    throw std::invalid_argument("incorrect rectangle scaling: scale coefficient must be positive");
  }
  rect.width *= k;
  rect.height *= k;
}

void khasnulin::printRectInfo(std::ostream &out, rectangle_t rect)
{
  out << "rectangle center x:" << rect.pos.x << ", y: " << rect.pos.y << ", width: " << rect.width
      << ", height: " << rect.height << "\n";
}

khasnulin::rectangle_t khasnulin::getCommonRectangleFrame(rectangle_t r1, rectangle_t r2)
{
  double left = std::min(r1.pos.x - r1.width / 2, r2.pos.x - r2.width / 2);
  double right = std::max(r1.pos.x + r1.width / 2, r2.pos.x + r2.width / 2);
  double bottom = std::min(r1.pos.y - r1.height / 2, r2.pos.y - r2.height / 2);
  double top = std::max(r1.pos.y + r1.height / 2, r2.pos.y + r2.height / 2);
  return rectangle_t{right - left, top - bottom, {(right + left) / 2, (top + bottom) / 2}};
}

void khasnulin::calculateAndPrintFiguresInfo(std::ostream &out, IShape **shapes, size_t size)
{
  double sum_area = 0;
  rectangle_t general_frame = calculateFiguresGeneralRectangleFrame(shapes, size);
  for (size_t i = 0; i < size; i++)
  {
    double area = shapes[i]->getArea();
    out << "figure " << i << " area: " << shapes[i]->getArea() << "\n";
    rectangle_t rect = shapes[i]->getFrameRect();
    out << "figure " << i << " frame ";
    printRectInfo(out, rect);

    sum_area += area;
  }
  out << "area sum: " << sum_area << "\n";
  out << "general figures frame ";
  printRectInfo(out, general_frame);
}

khasnulin::rectangle_t khasnulin::calculateFiguresGeneralRectangleFrame(IShape **shapes, size_t size)
{
  if (!size)
  {
    throw std::runtime_error("figures general frame: empty shapes array error");
  }
  rectangle_t general_frame = shapes[0]->getFrameRect();
  for (size_t i = 1; i < size; i++)
  {
    general_frame = getCommonRectangleFrame(general_frame, shapes[i]->getFrameRect());
  }
  return general_frame;
}

khasnulin::point_t khasnulin::operator-(point_t p_t1, point_t p_t2)
{
  return {p_t1.x - p_t2.x, p_t1.y - p_t2.y};
}

khasnulin::point_t khasnulin::operator+(point_t p_t1, point_t p_t2)
{
  return {p_t1.x + p_t2.x, p_t1.y + p_t2.y};
}

khasnulin::point_t khasnulin::operator*(point_t p_t1, double k)
{
  return {p_t1.x * k, p_t1.y * k};
}

khasnulin::point_t khasnulin::operator/(point_t p_t1, double k)
{
  return {p_t1.x / k, p_t1.y / k};
}

void khasnulin::isotropicScaling(IShape &shape, point_t scale_pt, double scale)
{
  rectangle_t base_frame = shape.getFrameRect();
  point_t old_right_top = getRightTop(base_frame);

  shape.move(scale_pt);

  rectangle_t new_frame = shape.getFrameRect();
  point_t new_right_top = getRightTop(new_frame);

  shape.scale(scale);

  point_t delta = (old_right_top - new_right_top) * scale;

  shape.move(delta.x, delta.y);
}

khasnulin::point_t khasnulin::getRightTop(rectangle_t frame)
{
  return frame.pos + point_t{frame.width / 2, frame.height / 2};
}

khasnulin::Polygon::Polygon(const point_t *points, size_t k):
    vertex(k > 2 ? new point_t[k] : nullptr),
    size(k)
{
  if (!points || k <= 2)
  {
    throw std::invalid_argument(
        "polygon creation error: points array must be not empty, count of vertexes must be more than 2");
  }
  copy(points, vertex, k);
  center = calculateCenter();
}

khasnulin::point_t *khasnulin::copy(const point_t *from, point_t *to, size_t k)
{
  for (size_t i = 0; i < k; i++)
  {
    to[i] = from[i];
  }
  return to + k;
}

khasnulin::Polygon::~Polygon()
{
  delete[] vertex;
}

// Дальнейшие комментарии написаны только из-за того, что центр и площадь полигона было тяжело понять!

// Площадь треугольника через модуль векторного произведения двух точек и точки(0,0)
// по альтернативной формуле через координаты вектора
double khasnulin::triagleSignedArea(point_t v1, point_t v2)
{
  return (v1.x * v2.y - v2.x * v1.y) / 2;
}

// считаем площадь невыпуклой фигуры по сумме знаковых площадей треугольников,
// построенных из двух точек, взятых при последовательном обходе вершин, и точки (0,0).
double khasnulin::Polygon::getArea() const
{
  double figure_area = 0;
  for (size_t i = 0; i < size - 1; i++)
  {
    figure_area += triagleSignedArea(vertex[i], vertex[i + 1]);
  }
  figure_area += triagleSignedArea(vertex[size - 1], vertex[0]);
}

// Берем центроид треугольника из двух точек полигона и точки (0,0), как среднее
// арифмитическое координат трех точек
khasnulin::point_t khasnulin::getTriangleCenter(point_t v1, point_t v2)
{
  return (v1 + v2) / 3;
}

// Получаем центроид фигуры: находя площадь каждого треугольника и его центр, можно посчитать
// вклад каждого треугольника в общую массу фигуры, как произведение координат центроида на площадь его треугольника.
// в конце делим сумму всех центроидов умноженных на их площади на общую площадь и получаем реальный центр масс
khasnulin::point_t khasnulin::Polygon::calculateCenter()
{
  double figure_area = triagleSignedArea(vertex[0], vertex[1]);
  point_t figure_center = getTriangleCenter(vertex[0], vertex[1]) * figure_area;
  for (size_t i = 1; i < size - 1; i++)
  {
    double current_area = triagleSignedArea(vertex[i], vertex[i + 1]);
    point_t current_center = getTriangleCenter(vertex[i], vertex[i + 1]);
    figure_center = figure_center + current_center * current_area;
    figure_area += current_area;
  }
  double last_area = triagleSignedArea(vertex[size - 1], vertex[0]);
  figure_center = figure_center + getTriangleCenter(vertex[size - 1], vertex[0]) * last_area;
  figure_area += last_area;
  return figure_area ? figure_center / figure_area : point_t{0, 0};
}

void khasnulin::Polygon::move(point_t to)
{
  point_t delta = to - center;
  for (size_t i = 0; i < size; i++)
  {
    vertex[i] = vertex[i] + delta;
  }
  center = to;
}

void khasnulin::Polygon::move(double dx, double dy)
{
  point_t newCenter = center + point_t{dx, dy};
  move(newCenter);
}

void khasnulin::Polygon::scale(double k)
{
  if (k <= 0.0)
  {
    throw std::invalid_argument("incorrect polygon scaling: scale coefficient must be positive");
  }
  for (size_t i = 0; i < size; i++)
  {
    point_t delta = vertex[i] - center;
    vertex[i] = vertex[i] + delta * k;
  }
}