#ifndef DATAHISTORY_H
#define DATAHISTORY_H
#include "Data.h"

class DataHistory {
private:
  int maxSize;
  int size;
  int newest;
  Data **hist;

public:
  DataHistory(int s);
  ~DataHistory(void);
  void add(Data *data);
  Data *getNewest(void);
  Data *get(int i);
  Data *operator[](int i);
  int getSize();
  int getMaxSize();
};

inline Data *DataHistory::getNewest() { return hist[newest]; }
inline int DataHistory::getSize() { return size; }
inline int DataHistory::getMaxSize() { return maxSize; }

#endif
