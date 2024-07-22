#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include "../../Display/include/observer.h"
#include <vector>

class Subject {
  public:
    void attach(Observer *observer);
    void detach(Observer *observer);
    void notifyObservers(Tile &t);

  private:
    std::vector<Observer *> observers;
};

#endif // __SUBJECT_H__
