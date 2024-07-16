#include "HardwareSerial.h"
#include "LandmarkConverter.h"
LandmarkConverter::LandmarkConverter()
{
}
bool LandmarkConverter::is_ready() {
  return done;
}

bool LandmarkConverter::process_str(const string &message) {
  //  Serial.print(message.c_str());
  if (message.compare("end") == 0) {
    this->convert_str_to_arr();
    //    this->print_landmarks();
    this->done = true;
  } else if (message.compare("start") == 0) {
    this->done = false;
    this->points_str = "";
    this->points.clear();
  } else {
    this->done = false;
    this->points_str = this->points_str + message;
  }
  return true;
}


void LandmarkConverter::convert_str_to_arr() {
  const string &input = this->points_str;
  char delimiter = '.';
  //  std::vector<std::pair<string, string>> result;
  size_t start = 0;
  size_t endi = input.find(delimiter);

  while (endi != string::npos) {
    string token = input.substr(start, endi - start);
    size_t dotPos = token.find(',');

    if (dotPos != string::npos) {
      string first = token.substr(0, dotPos);
      string second = token.substr(dotPos + 1);
      this->points.emplace_back(atoi(first.c_str()), atoi(second.c_str()));
    }

    start = endi + 1;
    endi = input.find(delimiter, start);
  }

  // Process the last token (or the only token if there are no delimiters)
  string lastToken = input.substr(start);
  size_t dotPos = lastToken.find(',');

  if (dotPos != string::npos) {
    string first = lastToken.substr(0, dotPos);
    string second = lastToken.substr(dotPos + 1);
    this->points.emplace_back(atoi(first.c_str()), atoi(second.c_str()));
  }
}

void LandmarkConverter::convert_str_targets_to_arr(const char* input_chars) {
  const string &input = string(input_chars);
//  Serial.print("in LandmarkConverter::convert_str_targets_to_arr");
//  Serial.println(input.c_str());
  char delimiter = ';';
  vector<pair<int, int>> result;
  size_t start = 0;
  size_t endi = input.find(delimiter);
  while (endi != string::npos) {
    string token = input.substr(start, endi - start);
//    Serial.println(token.c_str());
    size_t dotPos = token.find(':');

    if (dotPos != string::npos) {
      string name_str = token.substr(0, dotPos);
      this->targets_names.push_back(name_str);
      this->points_str = token.substr(dotPos + 1);
//      Serial.println("B:");
//      Serial.println(this->points_str.c_str());
      this->convert_str_to_arr();
      this->targets_points.push_back(this->points);
      this->points.clear();
    }
    start = endi + 1;
    endi = input.find(delimiter, start);
  }
  this->points.clear();
  this->done = false;
  Serial.println("in convert_str_targets_to_arr:");
//  print_targets_landmarks();
}

vector<pair<int, int>> &LandmarkConverter::get_points() {
  return this->points;
}
vector<vector<pair<int, int>>> &LandmarkConverter::get_targets_points() {
//  Serial.println();
//  Serial.print("in LandmarkConverter get_targets_points:");
//  Serial.println(this->targets_points.size());
  return this->targets_points;
}

vector<string> &LandmarkConverter::get_targets_names() {
//  Serial.println();
//  Serial.print("in LandmarkConverter: get_targets_names");
//  Serial.println(this->targets_names.size());
  return this->targets_names;
}

void LandmarkConverter::print_landmarks()
{
  Serial.println();
  Serial.print("print landmarks = ");
  for (auto i = 0; i < this->points.size(); ++i)
  {
    Serial.print(this->points[i].first);
    Serial.print(",");
    Serial.print(this->points[i].second);
    Serial.print(" ");

  }
  auto len = this->points.size();
  Serial.print("len landmarks = "); Serial.println(len);
}

void LandmarkConverter::print_targets_landmarks()
{
  for (auto i = 0; i < this->targets_points.size(); i++)
  {
    for (auto j = 0; j < this->targets_points[0].size(); j++)
    {
      Serial.print(this->targets_points[i][j].first);
      Serial.print(",");
      Serial.print(this->targets_points[i][j].second);
      Serial.print(" ");
    }
    Serial.println();
    Serial.println("----------------");
  }
}
