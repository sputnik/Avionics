#ifndef DATAHISTORY_H
# define DATAHISTORY_H
# include <iostream>
# include "Data.h"


class DataHistory {
private:
  int size;
  int newest;
  Data **hist;
public:
  DataHistory(int s);
  ~DataHistory(void);
  void add(Data *data);
  Data *getNewest(void);
  Data *get(int i);
  int getSize();
};

#endif
