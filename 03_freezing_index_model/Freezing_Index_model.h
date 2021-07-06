#ifndef FREEZING_INDEX_MODEL_H
#define FREEZING_INDEX_MODEL_H

#include <vector>


class Freezing_Index_Model {
private:
    double mean_temperature {};
    double target_freezing_index {};
    double amplitude {10.0};
    double current_freezing_index {};
    std::vector<double> temperature_list {};
    std::vector<double> base_cos {};
    std::vector<double> final_temperature_list {};
    void set_base_cos();
    void populate_temperature_list();
    void calculate_current_freezing_index();
    
public:
    void set_mean_temperature(const double &new_temperature);
    void set_freezing_index(const double &new_temperature);
    void fitting_freezing_index();
    void return_temperature_values(std::vector<double> &temperature_vector);
    
    // Constructor
    Freezing_Index_Model() {};

    Freezing_Index_Model(double &mean_temperature, double &target_freezing_index);

    // Destructor
    ~Freezing_Index_Model() {};
};

#endif // FREEZING_INDEX_MODEL_H
