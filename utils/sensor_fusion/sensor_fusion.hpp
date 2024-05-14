#ifndef SENSOR_FUSION_HPP
#define SENSOR_FUSION_HPP

#include "clock.hpp"

class SensorFusion {
    private:
    // Roll
    float phi_rad;
    // Pitch
    float theta_rad;
    
    // Error Covariance Matrix
    float P[4];
    // Process Noise Matrix
    float Q[2];
    // Measurement Noise Matrix
    float R[3];

    HAL::JupiterClock &clock;

    public:
        SensorFusion(float p_init, float *const Q, float *const R, HAL::JupiterClock &clock)
        :   phi_rad(0.0f), theta_rad(0.0f), clock(clock) {
            this->Q[0] = Q[0]; this->Q[1] = Q[1];

            this->R[0] = R[0]; this->R[1] = R[1]; this->R[2] = R[2];
            
            this->P[0] = p_init; this->P[1] = 0.0f; this->P[2] = 0.0f; this->P[3] = p_init;
        };

        /**
        * @brief Resets the Sensor fusion matrices and rads
         */
        void reset(float p_init, float *const Q, float *const R);

        /**
        * @brief Predict
         */
        void predict(float *const gyro, float T);

        /**
        * @brief Update
         */
        void update(float *const acc);
        
};

#endif