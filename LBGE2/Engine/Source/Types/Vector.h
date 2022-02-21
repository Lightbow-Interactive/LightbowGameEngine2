#ifndef LBGE2_VECTOR_H
#define LBGE2_VECTOR_H

template<typename T>
struct Vector2
{
  T x;
  T y;

  Vector2(){}
  Vector2(T _x, T _y) { x = _x; y = _y; }
  explicit operator sf::Vector2<T>() const { return sf::Vector2<T>(x, y); }
};

#endif //LBGE2_VECTOR_H
