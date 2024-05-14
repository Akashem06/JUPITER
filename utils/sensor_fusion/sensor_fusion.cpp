#include "sensor_fusion.hpp"

void SensorFusion::reset(float p_init, float *const Q, float *const R) {
    this->Q[0] = Q[0];
    this->Q[1] = Q[1];

    this->R[0] = R[0];
    this->R[1] = R[1];
    this->R[2] = R[2];

    this->P[0] = p_init;
    this->P[1] = 0.0f;
    this->P[2] = 0.0f;
    this->P[3] = p_init;
}