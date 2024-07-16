//
// Created by ASUS on 28/08/2023.
//

#include "FaceRecognizer.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>


vector<double> FaceRecognizer::distances_from_point(const vector<pair<int, int>>& matrix, int index = 0) {
  vector<pair<int, int>> points = matrix;
  vector<double> distances;

  pair<int, int> base_point = points[index];

  for (const auto& point : points) {
    double distance = sqrt(pow(point.first - base_point.first, 2) + pow(point.second - base_point.second, 2));
    distances.push_back(distance);
  }

  return distances;
}

vector<double> FaceRecognizer::get_distance_faces(const vector<pair<int, int>>& points, const vector<pair<int, int>>& target_points) {
  vector<pair<int, int>> points_stretched = stretch_and_align_points(points);
  vector<pair<int, int>> target_points_stretched = stretch_and_align_points(target_points);

  vector<double> dists_live = distances_from_point(points_stretched);
  vector<double> dists_target = distances_from_point(target_points_stretched);

  vector<double> dists;
  for (size_t i = 0; i < dists_live.size(); ++i) {
    dists.push_back(abs(dists_live[i] - dists_target[i]));
  }
  return dists;
}

string FaceRecognizer::identify(const vector<string>& ids, const vector<vector<pair<int, int>>>&  target_points, const vector<pair<int, int>>& face) {
//  Serial.print("face: ");
//  Serial.println(face.size());
//  Serial.print("target_points: ");
//  Serial.println(target_points.size());
  double min_tot_dist = 800;
  int min_tot_id = -1;

  for (size_t id = 0; id < target_points.size(); ++id) {
//    Serial.print(target_points[id][0].first);Serial.print(" ");Serial.println(target_points[id][0].second);
    vector<double> dists = get_distance_faces(face, target_points[id]);
    double dist_tot = 0;
    for(auto i = 0;i<dists.size();++i)
    {
      dist_tot+=dists[i];
    }
//    Serial.print(ids[id].c_str());
//    Serial.print(" dist: ");
//    Serial.println(dist_tot);
    if (min_tot_dist > dist_tot) {
      min_tot_dist = dist_tot;
      min_tot_id = static_cast<int>(id);
    }
  }

  if (min_tot_id == -1) {
    return "-";
    //        cout << ".";
  } else {
    cout << "\n" << ids[min_tot_id]<<min_tot_dist << endl;
    return ids[min_tot_id];
    //        
  }
}

vector<pair<int, int>> FaceRecognizer::stretch_and_align_points(const vector<pair<int, int>> &points)
{
  int new_max_x = size.first;
  int new_min_x = 0;
  int new_max_y = size.second;
  int new_min_y = 0;

  vector<int> x_values, y_values;
  for (const auto& point : points) {
    x_values.push_back(point.first);
    y_values.push_back(point.second);
  }

  int min_x = *min_element(x_values.begin(), x_values.end());
  int max_x = *max_element(x_values.begin(), x_values.end());
  int min_y = *min_element(y_values.begin(), y_values.end());
  int max_y = *max_element(y_values.begin(), y_values.end());

  vector<pair<int, int>> stretched_points;
  for (const auto& point : points) {
    int new_x = static_cast<int>(((point.first - min_x) / static_cast<double>(max_x - min_x)) * (new_max_x - new_min_x) + new_min_x);
    int new_y = static_cast<int>(((point.second - min_y) / static_cast<double>(max_y - min_y)) * (new_max_y - new_min_y) + new_min_y);
    stretched_points.emplace_back(new_x, new_y);
  }
  return stretched_points;
}
