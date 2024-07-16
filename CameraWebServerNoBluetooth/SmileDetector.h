
#ifndef FACERECOGNIZER_H_SMILEDETECTOR_H
#define FACERECOGNIZER_H_SMILEDETECTOR_H

#include <iostream>
#include <vector>
#include <cmath>

class SmileDetector {
private:
    std::vector<int> corners_distances;
    std::vector<int> lips_distances;
    int counter;
    int save_smile_counter=0;
    const int MAX_FRAMES = 6;
    const int LEFT_CORNER = 1;
    const int RIGHT_CORNER = 2;
    const int TOP_LIP = 3;
    const int BOTTOM_LIP = 4;
    const int TOP_NORM = 0;
    const int BOTTOM_NORM = 5;

public:
    SmileDetector();

    void no_face();

    void face_detected(std::vector<std::pair<int,int>> face);

    bool is_smile();

private:
    double distance(std::pair<int,int> point1, std::pair<int,int> point2);

    double mean(std::vector<int>::iterator begin, std::vector<int>::iterator end);
};

#endif //FACERECOGNIZER_H_SMILEDETECTOR_H
