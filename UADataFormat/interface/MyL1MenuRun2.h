#ifndef __MyL1MenuRun2_H__
#define __MyL1MenuRun2_H__

#include "TObject.h"
#include <iostream>
#include <map>

struct MyL1TUtmCutValue {
  double value;               /**< cut value */
  unsigned int index;         /**< HW index for the cut value */
};
struct MyL1TUtmCut{
  std::string name;          /**< name of cut */
  int object_type;           /**< target object type */
  int cut_type;              /**< type of cut */
  MyL1TUtmCutValue minimum;        /**< minimum value of cut range */
  MyL1TUtmCutValue maximum;        /**< maximum value of cut range */
  std::string data;          /**< data for charge/quality/isolation/charge correlation */
  std::string key;           /**< key for accessing a scale */
};
struct MyL1TUtmObject{
  std::string name;                          /**< name of object */
  int type;                                  /**< type of object */
  int comparison_operator;                   /**< comparison operator for threshold cut */
  int bx_offset;                             /**< bunch crossing  offset of object */
  double threshold;                          /**< threshold in GeV */
  std::string ext_signal_name;               /**< name of extenal signal, only valid when esObjectType == EXT */
  unsigned int ext_channel_id;               /**< channel id of external signal, only valid when esObjectType == EXT */
  std::vector<MyL1TUtmCut> cuts;             /**< list of cuts applied on object */ // They are all the same?
};
struct MyL1TUtmBin{
  unsigned int hw_index;   /**< HW index of bin */
  double minimum;          /**< minimum value of bin */
  double maximum;          /**< maximum value of bin */
};
struct MyL1TUtmScale{
  std::string name;        /**< name of scale */
  int object;              /**< type of object */
  int type;                /**< type of scale */
  double minimum;          /**< minimum value of scale */
  double maximum;          /**< maximum value of scale */
  double step;             /**< step size of linear scale */
  unsigned int n_bits;     /**< number of bits for scale */
  std::vector<MyL1TUtmBin> bins; /**< array of L1TUtmBin */
};
struct MyL1TUtmCondition{
  std::string name;                /**< name of condition */
  int type;                        /**< type of condition */
  std::vector<MyL1TUtmObject> objects;   /**< list of objects used in condition */ //TODO
  std::vector<MyL1TUtmCut> cuts;         /**< list of cuts applied on condition */ //TODO
};
  
struct MyL1TUtmAlgorithm {
  std::string name;                    /**< name of algorithm */
  std::string expression;              /**< algorithm expression in grammar */
  std::string expression_in_condition; /**< algorithm expression in condition */
  unsigned int index;                  /**< index of algorithm (global) */
  unsigned int module_id;              /**< module id */
  unsigned int module_index;           /**< index of algorithm in module (local to module id) */
  std::vector<std::string> rpn_vector; /**< reverse polish notation of algorithm expression in condition */
};
  
struct MyL1TUtmTriggerMenu {
  std::map<std::string, MyL1TUtmAlgorithm> algorithm_map;      /**< map of algorithm <algorithm name, L1TUtmAlgorithm> */
  std::map<std::string, MyL1TUtmCondition> condition_map;      /**< map of condition <condition name, L1TUtmCondition> */
  std::map<std::string, MyL1TUtmScale> scale_map;              /**< map of scale <scale name, L1TUtmScale*> */
  std::string name;                                      /**< name of the menu */
  std::string version;                                   /**< menu grammar version */
  std::string comment;                                   /**< comment on the menu */
  std::string datetime;                                  /**< datetime of the menu */
  std::string uuid_firmware;                             /**< uuid of firmware */
  std::string scale_set_name;                            /**< scale set name */
  unsigned int n_modules;                                /**< number of uGT boards for the menu */
  void Print();
};

class MyL1MenuRun2 {

public :
  MyL1MenuRun2();
  virtual ~MyL1MenuRun2();

  void Reset();
  void Print();

  std::map<unsigned int, MyL1TUtmTriggerMenu> menu;

private:

  ClassDef (MyL1MenuRun2,1)
};

#endif
