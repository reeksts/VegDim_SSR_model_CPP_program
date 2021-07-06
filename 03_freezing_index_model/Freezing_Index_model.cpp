#include "Freezing_Index_model.h"
#include <iostream>
#include <cmath>
#include <vector>

Freezing_Index_Model::Freezing_Index_Model(double &mean_temperature, double &target_freezing_index)
    : mean_temperature{mean_temperature}, target_freezing_index{target_freezing_index} {
    }

void Freezing_Index_Model::set_mean_temperature(const double &new_temperature) {
    mean_temperature = new_temperature;
}

void Freezing_Index_Model::set_freezing_index(const double &new_freezing_index) {
    target_freezing_index = new_freezing_index;
}

void Freezing_Index_Model::set_base_cos() {
    double cos_value {};
    double omega {};
    omega = 2*M_PI/365;
    for(size_t i {1}; i<=365; i++) {
        cos_value = cos(omega*i);
        base_cos.push_back(cos_value);
    }
}

void Freezing_Index_Model::populate_temperature_list() {
    temperature_list.clear();
    double temp_value {};
    for (auto x: base_cos) {
        temp_value = mean_temperature + amplitude*x;
        temperature_list.push_back(temp_value);
    }
}

void Freezing_Index_Model::calculate_current_freezing_index() {
    current_freezing_index = 0;
    for (auto x: temperature_list) {
        if (x<0) {
        current_freezing_index += x*24*-1;
        }
    }
}

// Here is the main fitting function:
void Freezing_Index_Model::fitting_freezing_index() {
    set_base_cos();
    while (std::abs(target_freezing_index - current_freezing_index) > 1) {
        // calculate freezing index
        populate_temperature_list();
        calculate_current_freezing_index();
        
        //std::cout << "amplitude: " << amplitude << std::endl;
        //std::cout << "target_freezing_index: " << target_freezing_index << std::endl;
        //std::cout << "current_freezing_index: " << current_freezing_index << std::endl;
        
        if (target_freezing_index > current_freezing_index) {
            if ((target_freezing_index - current_freezing_index) > 1000) {
                amplitude += 0.1;
            } else if ((target_freezing_index - current_freezing_index) > 100) {
                amplitude += 0.01;
            } else if ((target_freezing_index - current_freezing_index) > 10) {
                amplitude += 0.001;
            } else if ((target_freezing_index - current_freezing_index) > 1) {
                amplitude += 0.0001;
            }
        } else if (target_freezing_index < current_freezing_index) {
            if ((current_freezing_index - target_freezing_index) > 1000) {
                amplitude -= 0.1;
            } else if ((current_freezing_index - target_freezing_index) > 100) {
                amplitude -= 0.01;
            } else if ((current_freezing_index - target_freezing_index) > 10) {
                amplitude -= 0.001;
            } else if ((current_freezing_index - target_freezing_index) > 1) {
                amplitude -= 0.0001;
            }
        }
    }
    
    for (auto x: temperature_list) {
        if (x<0) {
            final_temperature_list.push_back(x);
        }
    }
}

void Freezing_Index_Model::return_temperature_values(std::vector<double> &temperature_vector) {
    for (auto x: final_temperature_list) {
        temperature_vector.push_back(x);
    }
}

