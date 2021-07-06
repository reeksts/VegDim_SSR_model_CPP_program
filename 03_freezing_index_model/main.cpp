#include <vector>
#include "Freezing_index_model.h"

int main() {
    double mean_temperature {0.1};
    double target_freezing_index {20000.0};
    
    std::vector<double> final_values {};
    
    Freezing_Index_Model freezing_index_model (mean_temperature, target_freezing_index);
    
    //freezing_index_model.set_mean_temperature(new_temperature);
    //freezing_index_model.set_freezing_index(new_freezing_index);
    freezing_index_model.fitting_freezing_index();
    freezing_index_model.return_temperature_values(final_values);
        
    return 0;
}
