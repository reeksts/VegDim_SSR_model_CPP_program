#ifndef SSR_MODEL_H
#define SSR_MODEL_H

#include <string>
#include <vector>
#include <iostream>

class SSR_model {
private:
    // Input: constants
    const double ki {2.24};
    const double Tf {0};
    const double Lw {92500};
    const double rhow {1};

    //Filenames (TEMPORARY FOR DEVELOPMENT)
    std::string input_filename_1 {};    // input filename for layers file
    std::string input_filename_2 {};    // input filename for data file
    std::string input_filename_3 {};    // input filename for others file
    std::string input_filename_4 {};    // input filename for chaussee file
    std::string input_filename_5 {};    // input filename for site file
    std::string output_filename_1 {};   // output filename for main data output
    std::string output_filename_2 {};   // output filename for chaussee reults
    std::string output_filename_3 {};   // output filename for site results
    std::string output_filename_4 {};   // output filename for limits
    std::string output_filename_5 {};   // output filename for python model
    
    // Input: layer property lists (file 1)
    std::vector<double> rhod_list {};
    std::vector<double> rhos_list {};
    std::vector<double> porosity_list {};
    std::vector<double> w_grav_list {};
    std::vector<double> SP_list {};
    std::vector<double> a_list {};
    std::vector<double> ku_list {};
    std::vector<double> kf_list {};
    std::vector<double> Sr_list {};
    std::vector<double> Ls_list {};
    
    // Input: Climate data lists (file 2)
    std::vector<double> day_list {};
    std::vector<std::string> date_list {};
    std::vector<double> temps_list {};
    std::vector<double> S_vals_list {};
    
    // Input: other input (file 3) 
    double flag {};     // This shoudl maybe be disabled for now
    double xps {};      // This should maybe be disabled for now
    double Tma {};
    double lim {};      // This shoudl maybe be disabled for now
    double lim_upper {};
    double lim_lower {};
    double Cq_upper {};
    double Cq_lower {};
    
    // Input: Loading chaussee file - this part is just TEMPORARY (file 4)
    std::vector<double> chaussee_file_day_list {};
    std::vector<double> chaussee_file_dt_list {};
    std::vector<double> chaussee_file_temps_list {};
    std::vector<double> chaussee_file_chau_z_list {};
    std::vector<double> chaussee_file_chau_h_list {};
    
    // Input: Loading site file (file 5)
    std::vector<double> site_file_day_list {};
    std::vector<double> site_file_dt_list {};
    std::vector<double> site_file_temps_list {};
    std::vector<double> site_file_site_z_list {};
    std::vector<double> site_file_site_h_list {};
    
    // Pre-calculation lists
    std::vector<double> layer_thickness_list {};
    std::vector<double> layer_thickness_list_mod {};
    std::vector<double> interface_lim_list {};
    
    // Time step calculation: set proprties
    double ku_low {};
    double kf_low {};
    double a_low {};
    double SP_low {};
    double Sr_low {};
    double Ls_low {};
    double w_grav_low {};
    double rhod_low {};
    
    double ku_upp {};
    double kf_upp {};
    double a_upp {};
    double SP_upp {};
    double Sr_upp {};
    double Ls_upp {};
    double w_grav_upp {};
    double rhod_upp {};
    
    double gradT_p {};
    int idx {};
    double Ts {};
    double S {};
    double Rf {};
    double flux {};
    double Cq {};
    
    double imp_vs_exp {};
    
    double pos_flux {};
    double neg_flux {};
    double freeze_water_flux {};
    double segregation_flux {};
    
    double root_1 {};
    double root_2 {};
    
    // Time step calculation: step calculations
    double days_count {};
    int day_index {};
    int day {};
    double FI {};
    
    double total_test_time {};
    double current_hour_count {};
    
    double dz0_sum {};
    double dh0 {};
    double dhs {};
    double dh {};
    double z {};
    double dz {};
    double dh0_sum {};
    double dhs_sum {};
    double h {};
    double dz0_residual {};
    double solved_by {};
    double closest_interface {};
    double dz0_first {};
    double dz0_second {};
    
    // Output: Data containers
    std::vector<double> time_output {};
    std::vector<double> dt_output {};
    std::vector<double> hours_output {};
    std::vector<double> closest_interface_output {};
    std::vector<double> FI_output {};
    std::vector<double> Ts_output {};
    std::vector<double> ku_output {};
    std::vector<double> kf_output {};
    std::vector<double> SP_output {};
    std::vector<double> a_output {};
    std::vector<double> Ls_output {};
    std::vector<double> S_output {};
    std::vector<double> Sr_output {};
    std::vector<double> Rf_output {};
    std::vector<double> dz0_imp_output {};
    std::vector<double> imp_1_vs_exp_0_output {};
    std::vector<double> dz0_sum_output {};
    std::vector<double> dh0_output {};
    std::vector<double> dh0_sum_output {};
    std::vector<double> dhs_output {};
    std::vector<double> dhs_sum_output {};
    std::vector<double> dh_output {};
    std::vector<double> h_output {};
    std::vector<double> dz_output {};
    std::vector<double> z_output {};
    std::vector<double> idx_output {};
    std::vector<double> gradT_p_output {};
    std::vector<double> flux_output {};
    std::vector<double> Cq_output {};
    std::vector<double> root_1_output {};
    std::vector<double> root_2_output {};
    std::vector<double> pos_flux_output {};
    std::vector<double> neg_flux_output {};
    std::vector<double> freeze_water_flux_output {};
    std::vector<double> segregation_flux_output {};
    std::vector<double> xps_output {};
    
    std::vector<double> chaussee_FI_output {};
    std::vector<double> site_FI_output {};
    
    std::vector<std::string> headers_output_1 {"day", "dt", "hours", "closest_int", "FI",
                                               "Ts", "ku", "kf", "SP", "a",
                                               "Ls", "S", "Sr", "Rf", "dz0_imp", "imp_1_vs_exp_0",
                                               "dz0_sum", "dh0", "dh0_sum", "dhs", "dhs_sum",
                                               "dh", "h", "dz", "z", "idx",
                                               "gradT_p", "flux", "Cq", "root_1", "root_2",
                                               "pos_flux", "neg_flux", "wat_flux", "seg_flux", "xps"};
    std::vector<std::string> headers_output_2 {"day", "chau_z", "chau_h"};
    std::vector<std::string> headers_output_3 {"day", "site_z", "site_h"};
    std::vector<std::string> headers_output_5 {"day", "z", "h"};
    std::vector<std::vector<double>> dataframe_output_1;
    std::vector<std::vector<double>> dataframe_output_2;
    std::vector<std::vector<double>> dataframe_output_3;
    std::vector<std::vector<double>> dataframe_output_5;
       
    // Calculation initializer member methods (IS THIS FUNCTION NECESSARY??)
    void set_filenames (std::string &input_filename_1, std::string &input_filename_2, std::string &input_filename_3, std::string &input_filename_4, std::string &input_filename_5,
                        std::string &output_filename_1, std::string &output_filename_2, std::string &output_filename_3, std::string &output_filename_4, std::string &output_filename_5);
    
    // Load files methods
    void load_layers_file();
    void load_data_file();
    void load_other_file();
    void load_chaussee_file();
    void load_site_file();
    
    // Pre-calculation methods
    void interface_lim_creation();
    void set_total_test_time();
    void set_gradT_p();
    void set_Cq_lim_values();
    void add_zero_day_to_output_container();
    
    // Stepwise member methods
    double get_total_test_time();
    double get_current_hour_count();
    double set_full_step_dt();
    void increment_current_hour_count(const double &dt);
    void decrement_current_hour_count(const double &dt);
    void set_index();
    void set_index_alt();
    bool interface_check(const double &dz0_imp);
    double calculate_dz0_residual();
    double set_partial_time_step (const double &partial_time_step);
    void increment_partial_time_step(double &partial_time_step, const double &dt);
    void set_flux_func_based();
    void set_flux_gradT_based();
    void set_temp();
    void set_S();
    void set_layer_props();
    void set_layer_props_upp();
    void set_resistance();
    double calculate_dz0_imp(const double &dt);
    double calculate_dz0_exp(const double &dt);
    double calculate_dt(const double &dz0_resid);
    void calculate_FI(const double &dt);
    void calculate_step_increments(const double &dt, const double dz0_imp);
    void calculate_balance_flux(const double &dt, const double dz0_imp);
    void add_results_to_output_containers(const double &dt, const double &dz0_imp);
    
    // Updating parameter values (setter functions)
    double update_rhod_value(const int &layer_number, const double &rhos, const double &porosity);
    double update_rhos_value(const int &layer_number, const double &rhod, const double &porosity);
    double update_porosity_value(const int &layer_number, const double &rhod, const double &rhos);
    double update_degree_of_saturation (const int &layer_number, const double &w_grav, const double &rho_d, const double &porosity);
    double update_latent_heat(const int &layer_number, const double &w_grav, const double &rhod);
    
    // End of calculation member methods
    void chaussee_output_FI_list();
    void site_output_FI_list();
    void push_back_vectors();
    void write_to_file_output_1();  // outputs the main data file
    void write_to_file_output_2();  // outputs chaussee results
    void write_to_file_output_3();  // outputs site results 
    void write_to_file_output_4();  // outputs limits
    void write_to_file_output_5();  // outputs results for python model
    void print_output();

public:
    // Setter functions    
    void set_rhod_value (const int &layer_number, const double &rhod);
    void set_rhos_value (const int &layer_number, const double &rhos);
    void set_porosity_value (const int &layer_number, const double &porosity);
    void set_w_grav (const int &layer_number, const double &w_grav);
    void set_SP_value (const int &layer_number, const double &SP);
    void set_a_value (const int &layer_number, const double &a);
    void set_ku_value (const int &layer_number, const double &ku);
    void set_kf_value (const int &layer_number, const double &kf);
    void set_Sr_value (const int &layer_number, const double &Sr);
    void set_Ls_value (const int &layer_number, const double &Ls);
    
    // Getter functions
    double get_rhod_value (const int &layer_number);
    double get_rhos_value (const int &layer_number);
    double get_porosity_value (const int &layer_number);
    double get_w_grav (const int &layer_number);
    double get_SP_value (const int &layer_number);
    double get_a_value (const int &layer_number);
    double get_ku_value (const int &layer_number);
    double get_kf_value (const int &layer_number);
    double get_Sr_value (const int &layer_number);
    double get_Ls_value (const int &layer_number);
    
    // member methods for clearing input data lists
    void clear_material_properties_lists ();
    void clear_temperature_lists ();
    void clear_S_vals ();
    void clear_test_site_data();
    
    // member methods for populating input data lists
    void populate_layer_property_lists (std::vector<std::vector<double>> &input_values);
    void popoulate_temperature_lists (std::vector<double> &temperature_values);
    void populate_S_vals_list ();
    
    // member methods for 
    void run_single_calculation();
    void write_to_file_outputs();
    void load_all_files();
    void pre_calculation_operations();
    
    // post calculation getter methods
    void get_frost_depth_values(double &frost_depth_values);
    void get_frost_heave_values(double &frost_heave_values);
    void get_day_values();
    
    //Constructors
    SSR_model() {
    };
    SSR_model(std::string &input_filename_1, std::string &input_filename_2, std::string &input_filename_3, std::string &input_filename_4, std::string &input_filename_5,
              std::string &output_filename_1, std::string &output_filename_2, std::string &output_filename_3, std::string &output_filename_4, std::string &output_filename_5)
        : input_filename_1{input_filename_1}, input_filename_2{input_filename_2}, input_filename_3{input_filename_3}, input_filename_4{input_filename_4}, input_filename_5{input_filename_5},
        output_filename_1{output_filename_1}, output_filename_2{output_filename_2}, output_filename_3{output_filename_3}, output_filename_4{output_filename_4}, output_filename_5{output_filename_5} {
    };
    
    // Destructor
    ~SSR_model() {};
    
    
    
    
    
    // TEMPORARY functions during development
    void print_out_temperature_TEMP();
    void print_out_material_properties_TEMP();
    std::string select_temperature_file_TEMP();
    void load_layers_file_TEMP(const std::string &filename);
    void print_S_vals_list();
};

#endif // SSR_MODEL_H
