#include "Data.h"
#include "DataHistory.h"
#include <iostream>
#include <stdio.h>

// Constructor
DataHistory::DataHistory(int s) {
  hist = new Data *[s];
  maxSize = s;
  size = 0;
  newest = 0;
  int i;
  // Uninitialized data points will be set to a default 0.
  for (i = 0; i < s; i++) {
    hist[i] = new Data;
  }
}

// Deconstructor
DataHistory::~DataHistory() {
  for (int i = 0; i < size; i++) {
    delete hist[i];
  }
  delete hist;
}

// Overwrites the oldest data object with the given data object.
// Assumes the given data object is statically allocated; does not try to delete
// old data.
// This should be changed if data objects become dynamically allocated later in
// development.
void DataHistory::add(Data *data) {
  newest--;
  if (newest < 0)
  {
    newest = maxSize - 1;
  }
  hist[newest]->clone(data);
  if (size < maxSize) {
    size++;
  }
}

// returns the ith oldest piece of data.
// assumes i < maxSize
Data *DataHistory::get(int i) {
  int pos = (newest + i) % maxSize;
  return hist[pos];
}
Data *DataHistory::operator[](int i)
{
  int pos = (newest + i) % maxSize;
  return hist[pos];
}
