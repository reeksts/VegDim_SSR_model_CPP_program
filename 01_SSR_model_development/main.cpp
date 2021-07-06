#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>

#include "SSR_model.h"

//TESTING 444

void load_all_data_sets(std::vector<std::vector<std::string>> &full_testsite_filename_vector) {
    std::string file_location_1 {"01_SAAR_original_data_set\\"};                     // add files here
    std::string file_location_2 {"02_QUEB_with_default_parameters\\"};               // Add files here
    std::string file_location_3 {"03_QUEB_with_given_parameters\\"};                 // Add files here
    std::string file_location_4 {"04_QUEB_with_backcalculated_values\\"};            // Add files here
    std::string file_location_5 {"05_ROROS_data_set\\"};                             // Add files here
    
    std::vector<std::string> file_location_vector {};
    file_location_vector.push_back(file_location_1);                            // Push back files here
    file_location_vector.push_back(file_location_2);                            // Push back files here
    file_location_vector.push_back(file_location_3);                            // Push back files here
    file_location_vector.push_back(file_location_4);                            // Push back files here
    file_location_vector.push_back(file_location_5);                            // Push back files here
    
    std::string filenames_file {"filenames.csv"};
    std::string input_prefix {"data_input\\"};
    std::string output_prefix {"data_output\\"};
    std::string output_prefix_2 {"C:\\Users\\User\\OneDrive - NTNU\\2_PostDoc_NTNU\\1_SSR_Model_development\\13_refactored_second_attempt\\data_input\\"};
    
    std::string input_postfix_1 {"_layers.csv"};
    std::string input_postfix_2 {"_data.csv"};
    std::string input_postfix_3 {"_other.csv"};
    std::string input_postfix_4 {"_chaussee.csv"};
    std::string input_postfix_5 {"_site.csv"};
    std::string output_postfix_1 {"_output_1.csv"};
    std::string output_postfix_2 {"_output_2.csv"};
    std::string output_postfix_3 {"_output_3.csv"};
    std::string output_postfix_4 {"_output_4.csv"};
    std::string output_postfix_5 {"_cpp_model_results.csv"};
    
    for (auto x: file_location_vector) {
        std::string filenames {input_prefix + x + filenames_file};
        
        std::ifstream file (filenames);
        std::string line {};
        
        if (!file.is_open()) {
            std::cout << "Failed to open: " << filenames << std::endl;
        } else {
            while (std::getline(file, line)) {
                std::vector<std::string> output_filename_vector {};
                output_filename_vector.push_back(input_prefix + x + line + input_postfix_1);       // input filename for layers file
                output_filename_vector.push_back(input_prefix + x + line + input_postfix_2);       // input filename for data file
                output_filename_vector.push_back(input_prefix + x + line + input_postfix_3);       // input filename for others file
                output_filename_vector.push_back(input_prefix + x + line + input_postfix_4);       // input filename for chaussee file
                output_filename_vector.push_back(input_prefix + x + line + input_postfix_5);       // input filename for site file
                output_filename_vector.push_back(output_prefix + x + line + output_postfix_1);     // output filename for main data output
                output_filename_vector.push_back(output_prefix + x + line + output_postfix_2);     // output filename for chaussee reults
                output_filename_vector.push_back(output_prefix + x + line + output_postfix_3);     // output filename for site results
                output_filename_vector.push_back(output_prefix + x + line + output_postfix_4);     // output filename for limits
                output_filename_vector.push_back(output_prefix_2 + x + line + output_postfix_5);   // output filename for python model
                    
                full_testsite_filename_vector.push_back(output_filename_vector);
            }
        }
    }
}

// Function that runs the program only for one test site. This is for testing purposes.
void SSR_calculate_single_test_case() {
    std::string folder {"05_ROROS_data_set\\"};
    std::string filename {"07_Roros_Rw1_winter_2016_2017_year1"};
    std::vector<std::string> filename_vector {};
    std::vector<std::vector<std::string>> main_vector {};
    
    std::string prefix_1 {"data_input\\"};
    std::string prefix_2 {"data_output\\"};
    
    std::string input_postfix_1 {"_layers.csv"};
    std::string input_postfix_2 {"_data.csv"};
    std::string input_postfix_3 {"_other.csv"};
    std::string input_postfix_4 {"_chaussee.csv"};
    std::string input_postfix_5 {"_site.csv"};
    
    std::string output_postfix_1 {"_output_1.csv"};
    std::string output_postfix_2 {"_output_2.csv"};
    std::string output_postfix_3 {"_output_3.csv"};
    std::string output_postfix_4 {"_output_4.csv"};
    std::string output_postfix_5 {"_cpp_model_results.csv"};
    
    filename_vector.push_back(prefix_1 + folder + filename + input_postfix_1);
    filename_vector.push_back(prefix_1 + folder + filename + input_postfix_2);
    filename_vector.push_back(prefix_1 + folder + filename + input_postfix_3);
    filename_vector.push_back(prefix_1 + folder + filename + input_postfix_4);
    filename_vector.push_back(prefix_1 + folder + filename + input_postfix_5);
    filename_vector.push_back(prefix_2 + folder + filename + output_postfix_1);
    filename_vector.push_back(prefix_2 + folder + filename + output_postfix_2);
    filename_vector.push_back(prefix_2 + folder + filename + output_postfix_3);
    filename_vector.push_back(prefix_2 + folder + filename + output_postfix_4);
    filename_vector.push_back(prefix_2 + folder + filename + output_postfix_5);
    
    main_vector.push_back(filename_vector);
    
    for (auto x: main_vector) {
        std::cout << "STARTING FOR " << x[0] << std::endl;
        double dt {};
        double dz0_imp {};
        double partial_time_step {};
        
        std::string input_filename_1 {x[0]};
        std::string input_filename_2 {x[1]};
        std::string input_filename_3 {x[2]};
        std::string input_filename_4 {x[3]};
        std::string input_filename_5 {x[4]};
        std::string output_filename_1 {x[5]};
        std::string output_filename_2 {x[6]};
        std::string output_filename_3 {x[7]};
        std::string output_filename_4 {x[8]};
        std::string output_filename_5 {x[9]};
        
        SSR_model test_site (input_filename_1, input_filename_2, input_filename_3, input_filename_4, input_filename_5,
                             output_filename_1, output_filename_2, output_filename_3, output_filename_4, output_filename_5);
        test_site.load_layers_file();
        test_site.load_data_file();
        test_site.load_other_file();
        test_site.load_chaussee_file();
        test_site.load_site_file();
        test_site.interface_lim_creation();
        test_site.set_total_test_time();
        test_site.set_gradT_p();
        test_site.set_Cq_lim_values();
        test_site.add_zero_day_to_output_container();
        
        while (test_site.get_current_hour_count() < test_site.get_total_test_time()) {
            if (partial_time_step != 0) {
                dt = test_site.set_partial_time_step(partial_time_step);
            } else {
                dt = test_site.set_full_step_dt();
            }
            test_site.set_index_alt();
            test_site.set_temp();
            test_site.set_S();
            test_site.set_layer_props();
            test_site.set_resistance();
            
            dz0_imp = test_site.calculate_dz0_imp(dt);
            
            if (test_site.interface_check(dz0_imp)) {
                test_site.decrement_current_hour_count(dt);
                dz0_imp = test_site.calculate_dz0_residual();
                dt = test_site.calculate_dt(dz0_imp);
                test_site.increment_current_hour_count(dt);
                test_site.increment_partial_time_step(partial_time_step, dt);
            } else {
                partial_time_step = 0;
            }
            test_site.calculate_FI(dt);
            test_site.calculate_step_increments(dt, dz0_imp);
            test_site.calculate_balance_flux(dt, dz0_imp);
            test_site.add_results_to_output_containers(dt, dz0_imp);
        }
        test_site.chaussee_output_FI_list();
        test_site.site_output_FI_list();
        test_site.push_back_vectors();
        test_site.write_to_file_output_1();
        test_site.write_to_file_output_2();
        test_site.write_to_file_output_3();
        test_site.write_to_file_output_4();
        test_site.write_to_file_output_5();
        
        std::cout << "FINISHED FOR " << x[0] << std::endl;
    }
}

// Function that runs throug all data sets.
void SSR_calculate_full_data_set() {
    std::vector<std::vector<std::string>> full_testsite_filename_vector {};
    load_all_data_sets(full_testsite_filename_vector);
    
    for (auto x: full_testsite_filename_vector) {
        std::cout << "STARTING FOR " << x[0] << std::endl;
        double dt {};
        double dz0_imp {};
        double partial_time_step {};
        
        std::string input_filename_1 {x[0]};
        std::string input_filename_2 {x[1]};
        std::string input_filename_3 {x[2]};
        std::string input_filename_4 {x[3]};
        std::string input_filename_5 {x[4]};
        std::string output_filename_1 {x[5]};
        std::string output_filename_2 {x[6]};
        std::string output_filename_3 {x[7]};
        std::string output_filename_4 {x[8]};
        std::string output_filename_5 {x[9]};
        
        SSR_model test_site (input_filename_1, input_filename_2, input_filename_3, input_filename_4, input_filename_5,
                             output_filename_1, output_filename_2, output_filename_3, output_filename_4, output_filename_5);
        test_site.load_layers_file();
        test_site.load_data_file();
        test_site.load_other_file();
        test_site.load_chaussee_file();
        test_site.load_site_file();
        test_site.interface_lim_creation();
        test_site.set_total_test_time();
        test_site.set_gradT_p();
        test_site.set_Cq_lim_values();
        test_site.add_zero_day_to_output_container();
        
        while (test_site.get_current_hour_count() < test_site.get_total_test_time()) {
            if (partial_time_step != 0) {
                dt = test_site.set_partial_time_step(partial_time_step);
            } else {
                dt = test_site.set_full_step_dt();
            }
            test_site.set_index_alt();
            test_site.set_temp();
            test_site.set_S();
            test_site.set_layer_props();
            test_site.set_resistance();
            
            dz0_imp = test_site.calculate_dz0_imp(dt);
            
            if (test_site.interface_check(dz0_imp)) {
                test_site.decrement_current_hour_count(dt);
                dz0_imp = test_site.calculate_dz0_residual();
                dt = test_site.calculate_dt(dz0_imp);
                test_site.increment_current_hour_count(dt);
                test_site.increment_partial_time_step(partial_time_step, dt);
            } else {
                partial_time_step = 0;
            }
            test_site.calculate_FI(dt);
            test_site.calculate_step_increments(dt, dz0_imp);
            test_site.calculate_balance_flux(dt, dz0_imp);
            test_site.add_results_to_output_containers(dt, dz0_imp);
        }
        test_site.chaussee_output_FI_list();
        test_site.site_output_FI_list();
        test_site.push_back_vectors();
        test_site.write_to_file_output_1();
        test_site.write_to_file_output_2();
        test_site.write_to_file_output_3();
        test_site.write_to_file_output_4();
        test_site.write_to_file_output_5();
        
        std::cout << "FINISHED FOR " << x[0] << std::endl;
    }
}

// Slightly modified function taht runs one test site and should work if data input files are stored in teh same folder as the main function.
void SSR_running_example_for_VTI() {
    std::vector<std::vector<std::string>> main_vector {};
    std::vector<std::string> filename_vector {};
    
    std::string prefix_1 {"test_input\\"};
    std::string prefix_2 {"test_output\\"};
    
    std::string input_postfix_1 {"_layers.csv"};
    std::string input_postfix_2 {"_data.csv"};
    std::string input_postfix_3 {"_other.csv"};
    std::string input_postfix_4 {"_chaussee.csv"};
    std::string input_postfix_5 {"_site.csv"};
    
    std::string output_postfix_1 {"_output_1.csv"};
    std::string output_postfix_2 {"_output_2.csv"};
    std::string output_postfix_3 {"_output_3.csv"};
    std::string output_postfix_4 {"_output_4.csv"};
    std::string output_postfix_5 {"_cpp_model_results.csv"};
    
    std::string filename {"01_test_file"};
    
    filename_vector.push_back(prefix_1 + filename + input_postfix_1);
    filename_vector.push_back(prefix_1 + filename + input_postfix_2);
    filename_vector.push_back(prefix_1 + filename + input_postfix_3);
    filename_vector.push_back(prefix_1 + filename + input_postfix_4);
    filename_vector.push_back(prefix_1 + filename + input_postfix_5);
    filename_vector.push_back(prefix_2 + filename + output_postfix_1);
    filename_vector.push_back(prefix_2 + filename + output_postfix_2);
    filename_vector.push_back(prefix_2 + filename + output_postfix_3);
    filename_vector.push_back(prefix_2 + filename + output_postfix_4);
    filename_vector.push_back(prefix_2 + filename + output_postfix_5);
    
    main_vector.push_back(filename_vector);
    
    for (auto x: main_vector) {
        std::cout << "STARTING FOR " << x[0] << std::endl;
        double dt {};
        double dz0_imp {};
        double partial_time_step {};
        
        std::string input_filename_1 {x[0]};
        std::string input_filename_2 {x[1]};
        std::string input_filename_3 {x[2]};
        std::string input_filename_4 {x[3]};
        std::string input_filename_5 {x[4]};
        std::string output_filename_1 {x[5]};
        std::string output_filename_2 {x[6]};
        std::string output_filename_3 {x[7]};
        std::string output_filename_4 {x[8]};
        std::string output_filename_5 {x[9]};
        
        
        SSR_model ssr_model (input_filename_1, input_filename_2, input_filename_3, input_filename_4, input_filename_5,
                             output_filename_1, output_filename_2, output_filename_3, output_filename_4, output_filename_5);
        
        ssr_model.load_all_files();
        ssr_model.pre_calculation_operations();
        ssr_model.run_single_calculation();
        ssr_model.write_to_file_outputs();
        
        std::cout << "FINISHED FOR " << x[0] << std::endl;
    }
}

void testing_function() {
    //SSR_model ssr_model;
    
    
    //std::string prefix {"data_input\\01_SAAR_original_data_set\\"};
    //std::string filename {};
    //std::string filepath {};
    //filename = test_instance.select_temperature_file_TEMP();
    //filepath = prefix + filename;
    //test_instance.load_layers_file_TEMP(filepath);
    //test_instance.print_out_material_properties_TEMP();
    
    //test_instance.populate_S_vals_list();
    //test_instance.print_S_vals_list();
}


int main() {
    // SSR_calculate_full_data_set();
    // SSR_calculate_single_test_case();
    SSR_running_example_for_VTI();
    
    testing_function();
    
    return 0;
}