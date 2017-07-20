
#include "UATree/UADataFormat/interface/MyL1MenuRun2.h"

ClassImp(MyL1MenuRun2)

MyL1MenuRun2::MyL1MenuRun2(){
  this->Reset();
}

MyL1MenuRun2::~MyL1MenuRun2(){}

void MyL1MenuRun2::Reset()
{
  menu.clear();
}

void MyL1MenuRun2::Print()
{
  for (auto a: menu){
    std::cout << "MyL1MenuRun2, Run " << a.first << ":\n";
    a.second.Print();
  }
}

void MyL1TUtmTriggerMenu::Print(){
  MyL1TUtmTriggerMenu triggerMenu;
  std::cout << "L1TUtmTriggerMenu: " << std::endl;
  std::cout << " name: " << name << std::endl;
  std::cout << " version: " << version << std::endl;
  std::cout << " comment: " << comment << std::endl;
  std::cout << " date/time: " << datetime << std::endl;
  std::cout << " UUID: " << uuid_firmware << std::endl;
  std::cout << " Scales: " << scale_set_name << std::endl;
  std::cout << " modules: " << n_modules << std::endl;

  std::cout << " Algorithms[" << algorithm_map.size() << "]: " << std::endl;
  for( auto a : algorithm_map )
    std::cout << "  " << a.first      << " " <<
              a.second.name        << " " <<
              a.second.expression  << " " <<
              a.second.index       << " " <<
              a.second.module_id    << " " <<
              a.second.module_index << " " <<
              std::endl;

  std::cout << " Conditions[" << condition_map.size() << "]: " << std::endl;
  for( auto a : condition_map )
    std::cout << "  " << a.first << " " <<
              a.second.name << " " <<
              a.second.type << " " <<
              std::endl;

  std::cout << " ScaleMaps[" << scale_map.size() << "]: " << std::endl;
  for( auto a : scale_map )
    std::cout << "  " << a.first      << " " <<
              a.second.name       << " " <<
              a.second.object << " " <<
              a.second.type  << " " <<
              a.second.minimum    << " " <<
              a.second.maximum    << " " <<
              a.second.step       << " " <<
              a.second.n_bits      << " " << std::endl;

}
