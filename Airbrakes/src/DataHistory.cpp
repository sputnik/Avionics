#include <stdio.h>
#include <iostream>
#include "DataHistory.h"
#include "Data.h"

//Constructor
DataHistory::DataHistory(int s){
  hist = new Data*[s];
  maxSize = s;
  size = 0;
  newest = s - 1;
  int i;
  //Uninitialized data points will be set to a default 0.
  for(i = 0; i < s; i++){
    hist[i] = new Data;
    *hist[i] = {
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0,
    };
  }
}

//Deconstructor
DataHistory::~DataHistory(){
  int i;
  for(i = 0; i < size; i++){
    delete hist[i];
  }
  delete hist;
}

//Overwrites the oldest data object with the given data object.
//Assumes the given data object is statically allocated; does not try to delete old data.
//This should be changed if data objects become dynamically allocated later in development.
void DataHistory::add(Data *data){
  newest = (newest + 1) % maxSize;

  hist[newest]->accX = data->accX;
  hist[newest]->accY = data->accY;
  hist[newest]->accZ = data->accZ;
  hist[newest]->velX = data->velX;
  hist[newest]->velY = data->velY;
  hist[newest]->velZ = data->velZ;
  hist[newest]->alt = data->alt;
  hist[newest]->pressure = data->pressure;
  hist[newest]->airbreaks = data->airbreaks;
  hist[newest]->time = data->time;

  if(size < maxSize){
    size++;
  }
}

//Returns the newest data point.
Data *DataHistory::getNewest(){
  return hist[newest];
}

//returns the ith oldest piece of data.
Data *DataHistory::get(int i){
  int pos = newest - i;
  if(pos < 0){
    pos = size + pos;
  }

  //if the data requested has already been overwritten, return the oldest data.
  if(i >= size){
    return get(size - 1);
  }
  return hist[pos];
}

//Returns the size of the data array.
int DataHistory::getSize(){
  return size;
}

int DataHistory::getMaxSize(){
  return maxSize;
}
