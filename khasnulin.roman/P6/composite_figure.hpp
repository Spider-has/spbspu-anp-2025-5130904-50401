#ifndef COMPOSITE_FIGURE_HPP
#define COMPOSITE_FIGURE_HPP

#include <ishape.hpp>

namespace khasnulin
{
  class CompositeFigure
  {
  public:
    CompositeFigure() noexcept = default;
    CompositeFigure(const CompositeFigure &cf) = default;
    CompositeFigure(CompositeFigure &&cf) noexcept = default;

    ~CompositeFigure() = default;

    CompositeFigure &operator=(const CompositeFigure &cf) = default;
    CompositeFigure &operator=(CompositeFigure &&cf) = default;

    void preappend(IShape figure);
    void append(IShape figure);
    void add(IShape figure, size_t pos);

    IShape &last();
    IShape &first();
    const IShape &last() const;
    const IShape &first() const;

    IShape &at(size_t index);
    IShape &get(size_t index);
    const IShape &at(size_t index) const;
    const IShape &get(size_t index) const;

    void remove(size_t index);

    void dropFirst(size_t index);
    void dropLast(size_t index);

    void clear();

    size_t size() const;

    bool empty() const;

    void reserve(size_t newCapacity);
    void shrink();
    size_t capacity() const;

  private:
    class ShapeVector
    {
    public:
      ShapeVector() noexcept;
      ShapeVector(const ShapeVector &sv);
      ShapeVector(ShapeVector &&sv) noexcept;

      ShapeVector &operator=(const ShapeVector &sv);
      ShapeVector &operator=(ShapeVector &&sv) noexcept;
      IShape *operator[](size_t index) const;

      ~ShapeVector();

      void append(IShape *figure);
      void preappend(IShape *figure);
      size_t size() const noexcept;

    private:
      IShape **figures_;
      size_t size_;
      size_t capacity_;

      void ensureCapacity(size_t newSize);
    };

    ShapeVector figures;
  };
}

#endif