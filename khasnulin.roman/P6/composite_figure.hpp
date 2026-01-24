#ifndef COMPOSITE_FIGURE_HPP
#define COMPOSITE_FIGURE_HPP

#include <ishape.hpp>

namespace khasnulin
{
  class CompositeFigure
  {
  public:
    CompositeFigure();
    CompositeFigure(const CompositeFigure &cf);
    CompositeFigure(CompositeFigure &&cf);

    ~CompositeFigure();

    CompositeFigure &operator=(const CompositeFigure &cf);
    CompositeFigure &operator=(const CompositeFigure &&cf);

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
    IShape **figures;
    size_t size;
    size_t capacity;

    void ensureCapacity();
  };
}

#endif