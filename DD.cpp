#include <iostream>
#include <iomanip>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h> 

using namespace std;

float accelerationOfGravity = 9.8;
float realPoint = 0;
float deltaZ = 0;
float targetPoint = 0.25;
int X = 5;
int SpeedX = 17;

float VerticalDirection(int speed, float angle) {
    float k = 0.47 * 1.169 * 0.017 * 0.017 * M_PI * 1000 / 3.2;
    float TimeX = (exp(k * X) - 1) / (k * speed * cos(angle));
    realPoint = speed * TimeX * sin(angle) - (accelerationOfGravity * TimeX * TimeX / 2);
    cout << "The realPoint is " << fixed << setprecision(7) << realPoint;
    deltaZ = realPoint - targetPoint;
    cout << "  The deltaZ is " << fixed << setprecision(7) << deltaZ;
    return deltaZ;
}

void findSolution(vector<float>& solutions,int cofficient) {
    float currentAngle = M_PI_4;
    float tempPoint = targetPoint;
    float tolerance = 1e-3;

    while (true) {
        tempPoint += VerticalDirection(SpeedX, currentAngle) * cofficient;
        currentAngle = atan(tempPoint / X);
        cout << "  The new angle is " << fixed << setprecision(7) << currentAngle << "\n";
        if (fabs(deltaZ) < tolerance) {
            solutions.push_back(currentAngle);
            break;
        currentAngle += atan(tempPoint/X);
        }
    }
}


int main() {
    vector<float>solutions;
    cout << "第一个可能结果的迭代过程如下" << "\n";
    findSolution(solutions,  1);
    cout << "第二个可能结果的迭代过程如下" << "\n";
    findSolution(solutions, -1);
    cout << "总共有 " << solutions.size() << "个结果" << endl;
    for (size_t i = 0; i < solutions.size(); ++i) {
        cout << "结果 " << i + 1 << ": " << solutions[i] * 180 / M_PI << " degrees" << endl;
    }
    return 0;
}
