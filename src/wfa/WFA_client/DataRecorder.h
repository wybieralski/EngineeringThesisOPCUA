//
// Created by lw on 20.03.19.
//

#ifndef FREEOPCUA_DATARECORDER_H
#define FREEOPCUA_DATARECORDER_H

#include <fstream>
#include <iostream>
#include <opc/ua/node.h>
#include <opc/ua/protocol/variant.h>
#include <string>

class DataRecorder {
public:
  static void write_to_row(std::ofstream &csv_file,
                           const OpcUa::Node &node,const OpcUa::DataValue &value );
  static void init_columns(std::ofstream &csv_file);
};

#endif // FREEOPCUA_DATARECORDER_H
