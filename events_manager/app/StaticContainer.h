#ifndef __STATIC_CONTAINER_H__
#define __STATIC_CONTAINER_H__

template<typename T, size_t MAX_SIZE> 
class StaticContainer {
public:
  StaticContainer() : _count{0} {
    for (size_t ix = 0; ix < MAX_SIZE; ++ix) {
      _container[ix] = nullptr;
    }
  }

  bool Add(T *item) {
    if (_count >= MAX_SIZE || !item) {
      return false;
    }

    _container[_count++] = item;
    return true;
  }

  bool Remove(T *item) {
    // TODO FIXME
    return false;
  }

  T *operator[](size_t index) {
    return (index < _count) ? _container[index] : nullptr;
  }

  size_t Size() const { return _count; }

  T **begin() { return _container; }
  T **end() { return _container + _count; }

private:
  T *_container[MAX_SIZE];
  size_t _count{0};
};

#endif
