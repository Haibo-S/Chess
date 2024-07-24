#ifndef __OBSERVER_H__
#define __OBSERVER_H__

class Tile; // fwd decl

class Observer {
  public:
    virtual ~Observer() = default;
    virtual void notify(Tile &t) = 0;
};
#endif
