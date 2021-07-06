#include "SSR_model.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>

// Calculation initializer member methods
void SSR_model::set_filenames(std::string &input_filename_1, std::string &input_filename_2, std::string &input_filename_3, std::string &input_filename_4, std::string &input_filename_5,
                              std::string &output_filename_1, std::string &output_filename_2, std::string &output_filename_3, std::string &output_filename_4, std::string &output_filename_5) {
    this->input_filename_1 = input_filename_1;      // filename for layers file
    this->input_filename_2 = input_filename_2;      // filename for data file
    this->input_filename_3 = input_filename_3;      // filename for others file
    this->input_filename_4 = input_filename_4;      // filename for chaussee file
    this->input_filename_5 = input_filename_5;      // filename for site file
    this->output_filename_1 = output_filename_1;    // filename for main data output
    this->output_filename_2 = output_filename_2;    // filename for chaussee reults
    this->output_filename_3 = output_filename_3;    // filename for limits
    this->output_filename_4 = output_filename_5;    // filename for python model
}
void SSR_model::load_layers_file() {
    std::ifstream file(input_filename_1);
    std::string line {};
    std::string val_holder {};
    
    if (!file.is_open()) {
        std::cout << "Failed to open: " << input_filename_1 << std::endl;
    } else {
        getline(file, line);
        while(getline(file, line)) {
            std::stringstream string_stream(line);
            getline(string_stream, val_holder, ',');
            getline(string_stream, val_holder, ',');
            if (val_holder == "") {
                (this->layer_thickness_list).push_back(10);
            } else {
                (this->layer_thickness_list).push_back(stof(val_holder));
            }
            getline(string_stream, val_holder, ',');
            (this->ku_list).push_back(std::stof(val_holder));
            getline(string_stream, val_holder, ',');
            (this->kf_list).push_back(std::stof(val_holder));
            getline(string_stream, val_holder, ',');
            (this->SP_list).push_back(std::stof(val_holder));
            getline(string_stream, val_holder, ',');
            (this->a_list).push_back(std::stof(val_holder));
            getline(string_stream, val_holder, ',');
            (this->Sr_list).push_back(std::stof(val_holder));
            getline(string_stream, val_holder, ',');
            (this->Ls_list).push_back(std::stof(val_holder));
            getline(string_stream, val_holder, ',');
            (this->w_grav_list).push_back(std::stof(val_holder));
            getline(string_stream, val_holder, ',');
            (this->rhod_list).push_back(std::stof(val_holder));
        }
    }
    for (auto x: layer_thickness_list) {
        layer_thickness_list_mod.push_back(x);
    }
}
void SSR_model::load_data_file() {
    std::ifstream file (input_filename_2);
    std::string line {};
    std::string val_holder {};
    
    if (!file.is_open()) {
        std::cout << "Failed to open: " << input_filename_2 << std::endl;
    } else {
        std::getline(file, line);
        while(getline(file, line)) {
            std::stringstream string_stream(line);
            std::getline(string_stream, val_holder, ',');
            (this->day_list).push_back(std::stof(val_holder));
            std::getline(string_stream, val_holder, ',');
            (this->date_list).push_back(val_holder);
            std::getline(string_stream, val_holder, ',');
            (this->temps_list).push_back(std::stof(val_holder));
            std::getline(string_stream, val_holder, ',');
            (this->S_vals_list).push_back(std::stof(val_holder));
        }
    }
}
void SSR_model::load_other_file() {
    std::ifstream file (input_filename_3);
    std::string line {};
    std::string val_holder {};
    
    if  (!file.is_open()) {
        std::cout << "failed to open: " << input_filename_3 << std::endl;
    } else {
        std::getline(file, line);
        
        std::getline(file, line);
        std::stringstream ss1 (line);
        std::getline(ss1, val_holder, ',');
        std::getline(ss1, val_holder, ',');
        flag = std::stof(val_holder);
        
        std::getline(file, line);
        std::stringstream ss2 (line);
        std::getline(ss2, val_holder, ',');
        std::getline(ss2, val_holder, ',');
        xps = std::stof(val_holder);
        
        std::getline(file, line);
        std::stringstream ss3 (line);
        std::getline(ss3, val_holder, ',');
        std::getline(ss3, val_holder, ',');
        Tma = std::stof(val_holder);
        
        std::getline(file, line);
        std::stringstream ss4 (line);
        std::getline(ss4, val_holder, ',');
        std::getline(ss4, val_holder, ',');
        lim = std::stof(val_holder);
    }
}
void SSR_model::load_chaussee_file() {
    std::ifstream file (input_filename_4);
    std::string line {};
    std::string val_holder {};
    
    if (!file.is_open()) {
        std::cout << "Failed to open: " << input_filename_4 << std::endl;
    } else {
        std::getline(file, line);
        while(getline(file, line)) {
            std::stringstream string_stream(line);
            std::getline(string_stream, val_holder, ',');
            (this->chaussee_file_day_list).push_back(std::stof(val_holder));
            std::getline(string_stream, val_holder, ',');
            if (val_holder == "") {
                (this->chaussee_file_dt_list).push_back(std::numeric_limits<double>::quiet_NaN());
            } else {
                (this->chaussee_file_dt_list).push_back(std::stof(val_holder));
            }
            std::getline(string_stream, val_holder, ',');
            if (val_holder == "") {
                (this->chaussee_file_temps_list).push_back(std::numeric_limits<double>::quiet_NaN());
            } else {
                (this->chaussee_file_temps_list).push_back(std::stof(val_holder));
            }
            std::getline(string_stream, val_holder, ',');
            if (val_holder == "") {
                (this->chaussee_file_chau_z_list).push_back(std::numeric_limits<double>::quiet_NaN());
            } else {
                (this->chaussee_file_chau_z_list).push_back(std::stof(val_holder));
            }
            std::getline(string_stream, val_holder, ',');
            if (val_holder == "") {
                (this->chaussee_file_chau_h_list).push_back(std::numeric_limits<double>::quiet_NaN());
            } else {
                (this->chaussee_file_chau_h_list).push_back(std::stof(val_holder));
            }
        }
    }
}
void SSR_model::load_site_file() {
    std::ifstream file (input_filename_5);
    std::string line {};
    std::string val_holder {};
    
    if (!file.is_open()) {
        std::cout << "Failed to open: " << input_filename_5 << std::endl;
    } else {
        std::getline(file, line);
        while(getline(file, line)) {
            std::stringstream string_stream(line);
            std::getline(string_stream, val_holder, ',');
            (this->site_file_day_list).push_back(std::stof(val_holder));
            std::getline(string_stream, val_holder, ',');
            (this->site_file_dt_list).push_back(std::stof(val_holder));
            std::getline(string_stream, val_holder, ',');
            (this->site_file_temps_list).push_back(std::stof(val_holder));
            std::getline(string_stream, val_holder, ',');
            if (val_holder == "") {
                (this->site_file_site_z_list).push_back(std::numeric_limits<double>::quiet_NaN());
            } else {
                (this->site_file_site_z_list).push_back(std::stof(val_holder));
            }
            std::getline(string_stream, val_holder, ',');
            if (val_holder == "") {
                (this->site_file_site_h_list).push_back(std::numeric_limits<double>::quiet_NaN());
            } else {
                (this->site_file_site_h_list).push_back(std::stof(val_holder));
            }
        }
    }
}
void SSR_model::interface_lim_creation() {
	for (size_t i {0}; i < layer_thickness_list.size(); i++) {
        double control_sum {};
        for (size_t j {0}; j<=i; j++) {
            control_sum += layer_thickness_list[j];
        }
        interface_lim_list.push_back(control_sum);
	}
}
void SSR_model::set_total_test_time() {
    total_test_time = (day_list.size())*24;
}
void SSR_model::set_gradT_p() {
    gradT_p = (0.43*Tma+1)/0.82;
}
void SSR_model::set_Cq_lim_values(){
    lim_upper = lim - xps;
    lim_lower = lim;
    Cq_upper = std::pow(10,(-4.5*std::pow(xps, 0.8)));
    Cq_lower = 1.0;
}
void SSR_model::add_zero_day_to_output_container() {
    time_output.push_back(0);
    dt_output.push_back(std::numeric_limits<double>::quiet_NaN());
    hours_output.push_back(0);
    closest_interface_output.push_back(std::numeric_limits<double>::quiet_NaN());
    FI_output.push_back(0);
    Ts_output.push_back(std::numeric_limits<double>::quiet_NaN());
    ku_output.push_back(std::numeric_limits<double>::quiet_NaN());
    kf_output.push_back(std::numeric_limits<double>::quiet_NaN());
    SP_output.push_back(std::numeric_limits<double>::quiet_NaN());
    a_output.push_back(std::numeric_limits<double>::quiet_NaN());
    Ls_output.push_back(std::numeric_limits<double>::quiet_NaN());
    S_output.push_back(std::numeric_limits<double>::quiet_NaN());
    Sr_output.push_back(std::numeric_limits<double>::quiet_NaN());
    Rf_output.push_back(std::numeric_limits<double>::quiet_NaN());
    dz0_imp_output.push_back(std::numeric_limits<double>::quiet_NaN());
    imp_1_vs_exp_0_output.push_back(std::numeric_limits<double>::quiet_NaN());
    dz0_sum_output.push_back(0);
    dh0_output.push_back(0);
    dh0_sum_output.push_back(0);
    dhs_output.push_back(0);
    dhs_sum_output.push_back(0);
    dh_output.push_back(0);
    h_output.push_back(0);
    dz_output.push_back(0);
    z_output.push_back(0);
    idx_output.push_back(std::numeric_limits<double>::quiet_NaN());
    gradT_p_output.push_back(std::numeric_limits<double>::quiet_NaN());
    flux_output.push_back(std::numeric_limits<double>::quiet_NaN());
    Cq_output.push_back(std::numeric_limits<double>::quiet_NaN());
    root_1_output.push_back(std::numeric_limits<double>::quiet_NaN());
    root_2_output.push_back(std::numeric_limits<double>::quiet_NaN());
    pos_flux_output.push_back(std::numeric_limits<double>::quiet_NaN());
    neg_flux_output.push_back(std::numeric_limits<double>::quiet_NaN());
    freeze_water_flux_output.push_back(std::numeric_limits<double>::quiet_NaN());
    segregation_flux_output.push_back(std::numeric_limits<double>::quiet_NaN());
    xps_output.push_back(std::numeric_limits<double>::quiet_NaN());
}

// Stepwise member methods
double SSR_model::get_total_test_time() {
    return total_test_time;
}
double SSR_model::get_current_hour_count() {
    return current_hour_count;
}
double SSR_model::set_full_step_dt() {
    double dt {24};
    current_hour_count += 24;
    day_index = ceil(current_hour_count / 24) - 1;
    day = ceil(current_hour_count / 24);
    return dt;
}
void SSR_model::increment_current_hour_count(const double &dt) {
    current_hour_count += dt;
}
void SSR_model::decrement_current_hour_count(const double &dt) {
    current_hour_count -= dt;
}
void SSR_model::set_index() {
    std::vector<double> temp_vec {};
    int local {};
    for (auto x: interface_lim_list) {
        temp_vec.push_back(std::abs(x - dz0_sum));
    }
    local = std::min_element(temp_vec.begin(), temp_vec.end()) - temp_vec.begin();
    if (dz0_sum < interface_lim_list[local]) {
        idx = local;
    } else {
        idx = local +1;
    }
}
void SSR_model::set_index_alt() {
    for (size_t i {}; i<interface_lim_list.size(); i++)
        if (dz0_sum < interface_lim_list[i]) {
            idx = i;
            break;
        }
}
bool SSR_model::interface_check (const double &dz0_imp) {
    closest_interface = interface_lim_list[idx];
    return (dz0_sum + dz0_imp > closest_interface);    
}
double SSR_model::calculate_dz0_residual() {
    // double closest_interface {interface_lim_list[idx]};
    double dz0_resid {closest_interface - dz0_sum};
    return dz0_resid;
}
double SSR_model::set_partial_time_step(const double &partial_time_step) {
    double dt {};
    dt = 24 - partial_time_step;
    current_hour_count += dt;
    double fractpart {};
    double intpart {};
    fractpart = std::modf(current_hour_count, &intpart);
    if (current_hour_count > intpart) {
        current_hour_count = intpart;
    }
    day_index = ceil(current_hour_count / 24) - 1;
    day = ceil(current_hour_count / 24);
    return dt;
}
void SSR_model::increment_partial_time_step(double &partial_time_step, const double &dt) {
    partial_time_step += dt;
}
void SSR_model::set_flux_func_based () {
    if (dz0_sum <= lim_upper) {
        Cq = Cq_upper;
    } else if (lim_upper < dz0_sum && dz0_sum < lim_lower) {
        Cq = (dz0_sum-lim_upper)/(lim_lower-lim_upper)*(Cq_lower-Cq_upper)+Cq_upper;
    } else {
        Cq = Cq_lower;
    }
    flux = (((250-day)*(9.62+1.44*std::log(Tma))) / (250+(5.78-1.62*std::log(Tma))*day) + 1.2)*Cq;
}
void SSR_model::set_flux_gradT_based() {
    flux = S*gradT_p*ku_low;
}
void SSR_model::set_temp() {
    Ts = temps_list[day_index];
}
void SSR_model::set_S() {
    S = S_vals_list[day_index];
}
void SSR_model::set_layer_props () {
    ku_low = ku_list[idx];
    kf_low = kf_list[idx];
    a_low = a_list[idx];
    SP_low = SP_list[idx]*std::exp(-a_low*0.02*z);
    Sr_low = Sr_list[idx];
    Ls_low = Ls_list[idx];
    w_grav_low = w_grav_list[idx];
    rhod_low = rhod_list[idx];
}
void SSR_model::set_resistance () {
    double res1 {};
    double res2 {};
    double res3 {};
    for (int i {0}; i<idx; i++) {
        res1 += layer_thickness_list_mod[i] / kf_list[i];
    }
    double sum {};
    for (int i {0}; i<=idx; i++) {
        sum += layer_thickness_list[i];
    }
    res2 = (layer_thickness_list_mod[idx] - (sum - dz0_sum)) / kf_low;
    res3 = dhs_sum / ki;
    Rf = res1 + res2 + res3;
}
double SSR_model::calculate_dz0_imp (const double &dt) {
    if (flag == 0) {
        set_flux_gradT_based();
    } else {
        set_flux_func_based();
    }
        
    double a {};
    double b {};
    double c {};
    double x1 {};
    double x2 {};
    double real_part {};
    double imaginary_part {};
    double discriminant {};
    
    a = 0.5*Ls_low;
    b = 0.5*flux*dt+Ls_low*kf_low*Rf;
    c = flux*dt*kf_low*Rf+Lw*SP_low/1000000*(Tf-Ts)*dt-kf_low*(Tf-Ts)*dt;
    
    discriminant = b*b - 4*a*c;
    
    if (discriminant > 0) {
        x1 = (-b + sqrt(discriminant)) / (2*a);
        x2 = (-b - sqrt(discriminant)) / (2*a);
        root_1 = x1;
        root_2 = x2;
        imp_vs_exp = 1;
        return x1;
    } else if (discriminant == 0) {
        x1 = (-b + sqrt(discriminant)) / (2*a);
        root_1 = x1;
        root_2 = x1;
        imp_vs_exp = 1;
        return x1;
    } else {
        x1 = calculate_dz0_exp(dt);
        x2 = std::numeric_limits<double>::quiet_NaN();
        root_1 = x1;
        root_2 = x2;
        imp_vs_exp = 0;
        real_part = -b/(2*a);
        imaginary_part =sqrt(-discriminant)/(2*a);
        return x1;
    }
}
double SSR_model::calculate_dz0_exp (const double &dt) {
    if (flag == 0) {
        set_flux_gradT_based();
    } else {
        set_flux_func_based();
    }
    
    double dz0_exp {};
    dz0_exp = (Tf-Ts)*dt*(1-(SP_low/1000000)*Lw/kf_low)/(Ls_low*Rf)-flux*dt/Ls_low;
    return dz0_exp;
}
double SSR_model::calculate_dt (const double &dz0_resid) {
    double dt {};
    double upper_part {};
    double lower_part {};
    upper_part = (-0.5*Ls_low*std::pow(dz0_resid, 2)-Ls_low*kf_low*Rf*dz0_resid);
    lower_part = (0.5*flux*dz0_resid+flux*kf_low*Rf+Lw*(SP_low/1000000)*(Tf-Ts)-kf_low*(Tf-Ts));
    dt = upper_part/lower_part;
    return dt;
}
void SSR_model::calculate_step_increments(const double &dt, const double dz0_imp) {
    if (dz0_imp<=0) {
        dh0 = 0;
        dhs = 0;
        dh = dh0 + dhs;
        h += dh;
        dz = dz0_imp + dh;
        z += dz;
        dz0_sum += dz0_imp;
        dh0_sum += dh0;
        dhs_sum += dhs;
        if (dz0_sum <= 0.01) {
            dz0_sum = 0.01;
            z = 0;
        }
    } else {
        if (Sr_list[idx] <= 85) {
            dh0 = 0;
        } else {
            dh0 = (dz0_imp*0.09*w_grav_low/100*rhod_low/rhow)*(Sr_low-85)/15;
        }
        layer_thickness_list_mod[idx] += dh0;
        dhs = (1.09*SP_low/1000000*(Tf-Ts)*dt)/(kf_low*Rf+0.5*dz0_imp);
        dh = dh0 + dhs;
        h += dh;
        
        dz = dz0_imp + dh;
        z += dz;
        dz0_sum += dz0_imp;
        dh0_sum += dh0;
        dhs_sum += dhs;
    }
}
void SSR_model::calculate_FI(const double &dt) {
    if (Ts < 0) {
        FI += dt*Ts*-1;
    } else {
        FI = FI;
    }
}
void SSR_model::calculate_balance_flux(const double &dt, const double dz0_imp) {
    neg_flux = kf_low*(Tf-Ts)/(kf_low*Rf+0.5*dz0_imp);
    pos_flux = flux;
    freeze_water_flux = Ls_low*dz0_imp / dt;
    segregation_flux = Lw*(SP_low/1000000)*(Tf-Ts) / (kf_low*Rf+0.5*dz0_imp);
}
void SSR_model::add_results_to_output_containers(const double &dt, const double &dz0_imp) {
    time_output.push_back(current_hour_count/24);
    dt_output.push_back(dt);
    hours_output.push_back(current_hour_count);
    closest_interface_output.push_back(closest_interface);
    FI_output.push_back(FI);
    Ts_output.push_back(Ts);
    ku_output.push_back(ku_low);
    kf_output.push_back(kf_low);
    SP_output.push_back(SP_low);
    a_output.push_back(a_low);
    Ls_output.push_back(Ls_low);
    S_output.push_back(S);
    Sr_output.push_back(Sr_low);
    Rf_output.push_back(Rf);
    dz0_imp_output.push_back(dz0_imp);
    imp_1_vs_exp_0_output.push_back(imp_vs_exp);
    dz0_sum_output.push_back(dz0_sum);
    dh0_output.push_back(dh0);
    dh0_sum_output.push_back(dh0_sum);
    dhs_output.push_back(dhs);
    dhs_sum_output.push_back(dhs_sum);
    dh_output.push_back(dh);
    h_output.push_back(h);
    dz_output.push_back(dz);
    z_output.push_back(z);
    idx_output.push_back(idx);
    gradT_p_output.push_back(gradT_p);
    flux_output.push_back(flux);
    Cq_output.push_back(Cq);
    root_1_output.push_back(root_1);
    root_2_output.push_back(root_2);
    pos_flux_output.push_back(pos_flux);
    neg_flux_output.push_back(neg_flux);
    freeze_water_flux_output.push_back(freeze_water_flux);
    segregation_flux_output.push_back(segregation_flux);
    xps_output.push_back(xps);
}

// Setter functions
void SSR_model::set_rhod_value (const int &layer_number, const double &rhod) {
    rhod_list[layer_number] = rhod;
}
void SSR_model::set_rhos_value (const int &layer_number, const double &rhos) {
    rhos_list[layer_number] = rhos;
}
void SSR_model::set_porosity_value (const int &layer_number, const double &porosity) {
    porosity_list[layer_number] = porosity;
}
void SSR_model::set_w_grav (const int &layer_number, const double &w_grav) {
    w_grav_list[layer_number] = w_grav;
}
void SSR_model::set_SP_value (const int &layer_number, const double &SP) {
    SP_list[layer_number] = SP;
}
void SSR_model::set_a_value (const int &layer_number, const double &a) {
    a_list[layer_number] = a;
}
void SSR_model::set_ku_value (const int &layer_number, const double &ku) {
    ku_list[layer_number] = ku;
}
void SSR_model::set_kf_value (const int &layer_number, const double &kf) {
    kf_list[layer_number] = kf;
}
void SSR_model::set_Sr_value (const int &layer_number, const double &Sr) {
    Sr_list[layer_number] = Sr;
}
void SSR_model::set_Ls_value (const int &layer_number, const double &Ls) {
    Ls_list[layer_number] = Ls;
}

// Getter functions
double SSR_model::get_rhod_value (const int &layer_number) {
    return rhod_list[layer_number];
}
double SSR_model::get_rhos_value (const int &layer_number) {
    return rhos_list[layer_number];
}
double SSR_model::get_porosity_value (const int &layer_number) {
    return porosity_list[layer_number];
}
double SSR_model::get_w_grav (const int &layer_number) {
    return w_grav_list[layer_number];
}
double SSR_model::get_SP_value (const int &layer_number) {
    return SP_list[layer_number];
}
double SSR_model::get_a_value (const int &layer_number) {
    return a_list[layer_number];
}
double SSR_model::get_ku_value (const int &layer_number) {
    return ku_list[layer_number];
}
double SSR_model::get_kf_value (const int &layer_number) {
    return kf_list[layer_number];
}
double SSR_model::get_Sr_value (const int &layer_number) {
    return Sr_list[layer_number];
}
double SSR_model::get_Ls_value (const int &layer_number) {
    return Ls_list[layer_number];
}


// Updating parameter values
/* 
 * The updates should be implemented as follows:
 * - changing rhod -> changes porosity, Sr and Ls
 * - changing rhos -> changes porosity, Sr and Ls
 * - changing porosity -> changes rhod, Sr and Ls
 */
double SSR_model::update_rhod_value(const int &layer_number, const double &rhos, const double &porosity) {
    double rhod {};
    rhod = rhos * (1 - porosity);
    return rhod;
}
double SSR_model::update_rhos_value(const int &layer_number, const double &rhod, const double &porosity) {
    double rhos {};
    rhos = rhod / (1 - porosity);
    return rhos;
}
double SSR_model::update_porosity_value(const int &layer_number, const double &rhod, const double &rhos) {
    double porosity {};
    porosity = 1 - (rhod - rhos);
    return porosity;
}
double SSR_model::update_degree_of_saturation (const int &layer_number, const double &w_grav, const double &rho_d, const double &porosity) {
    double Sr {};
    // Sr = (w_grav*rho_d)/porosity;
    // return Sr;
}
double SSR_model::update_latent_heat(const int &layer_number, const double &w_grav, const double &rhod) {
    double Ls {};
    Ls = (w_grav/100) * rhod * Lw;
    return Ls;
}

// End of calculation member methods
void SSR_model::chaussee_output_FI_list() {
    for (size_t i {}; i<chaussee_file_day_list.size(); i++) {
        double counting_sum {};
        for (size_t j {}; j<=i; j++){
            counting_sum += (chaussee_file_temps_list[j]*chaussee_file_dt_list[j]*-1);
        }
        chaussee_FI_output.push_back(counting_sum);
    }
}
void SSR_model::site_output_FI_list() {
    for (size_t i {}; i<site_file_day_list.size(); i++) {
        double counting_sum {};
        for (size_t j {}; j<=i; j++){
            counting_sum += (site_file_temps_list[j]*site_file_dt_list[j]*-1);
        }
        site_FI_output.push_back(counting_sum);
    }
}
void SSR_model::push_back_vectors() {
    dataframe_output_1.push_back(time_output);
    dataframe_output_1.push_back(dt_output);
    dataframe_output_1.push_back(hours_output);
    dataframe_output_1.push_back(closest_interface_output);
    dataframe_output_1.push_back(FI_output);
    dataframe_output_1.push_back(Ts_output);
    dataframe_output_1.push_back(ku_output);
    dataframe_output_1.push_back(kf_output);
    dataframe_output_1.push_back(SP_output);
    dataframe_output_1.push_back(a_output);
    dataframe_output_1.push_back(Ls_output);
    dataframe_output_1.push_back(S_output);
    dataframe_output_1.push_back(Sr_output);
    dataframe_output_1.push_back(Rf_output);
    dataframe_output_1.push_back(dz0_imp_output);
    dataframe_output_1.push_back(imp_1_vs_exp_0_output);
    dataframe_output_1.push_back(dz0_sum_output);
    dataframe_output_1.push_back(dh0_output);
    dataframe_output_1.push_back(dh0_sum_output);
    dataframe_output_1.push_back(dhs_output);
    dataframe_output_1.push_back(dhs_sum_output);
    dataframe_output_1.push_back(dh_output);
    dataframe_output_1.push_back(h_output);
    dataframe_output_1.push_back(dz_output);
    dataframe_output_1.push_back(z_output);
    dataframe_output_1.push_back(idx_output);
    dataframe_output_1.push_back(gradT_p_output);
    dataframe_output_1.push_back(flux_output);
    dataframe_output_1.push_back(Cq_output);
    dataframe_output_1.push_back(root_1_output);
    dataframe_output_1.push_back(root_2_output);
    dataframe_output_1.push_back(pos_flux_output);
    dataframe_output_1.push_back(neg_flux_output);
    dataframe_output_1.push_back(freeze_water_flux_output);
    dataframe_output_1.push_back(segregation_flux_output);
    dataframe_output_1.push_back(xps_output);
    
    dataframe_output_2.push_back(chaussee_file_day_list);
    //dataframe_output_2.push_back(chaussee_FI_output);
    dataframe_output_2.push_back(chaussee_file_chau_z_list);
    dataframe_output_2.push_back(chaussee_file_chau_h_list);
    
    dataframe_output_3.push_back(site_file_day_list);
    //dataframe_output_3.push_back(site_FI_output);
    dataframe_output_3.push_back(site_file_site_z_list);
    dataframe_output_3.push_back(site_file_site_h_list);
    
    dataframe_output_5.push_back(time_output);
    dataframe_output_5.push_back(z_output);
    dataframe_output_5.push_back(h_output);
}
void SSR_model::write_to_file_output_1() {      // outputs the main data file
    std::ofstream file;
    file.open(output_filename_1);
    for (size_t i {0}; i<headers_output_1.size()-1; i++) {
        file << headers_output_1[i] << ",";
    }
    file << headers_output_1[headers_output_1.size()-1] << std::endl;
    for (size_t i {0}; i<time_output.size(); i++) {
        for (size_t j {}; j<dataframe_output_1.size()-1; j++) {
            file << dataframe_output_1[j][i] << ",";
        }
        file << dataframe_output_1[dataframe_output_1.size()-1][i] << std::endl;
    }
}
void SSR_model::write_to_file_output_2() {      // outputs chaussee results
    std::ofstream file;
    file.open(output_filename_2);
    
    // adding headers
    for (size_t i {0}; i<headers_output_2.size()-1; i++) {
        file << headers_output_2[i] << ",";
    }
    file << headers_output_2[headers_output_2.size()-1] << std::endl;
    
    // adding zeros
    for (size_t i {0}; i<headers_output_2.size()-1; i++) {
        file << 0 << ",";
    }
    file << 0 << std::endl;
    
    // adding data
    for (size_t i {0}; i<chaussee_file_day_list.size(); i++) {
        for (size_t j {}; j<dataframe_output_2.size()-1; j++) {
            file << dataframe_output_2[j][i] << ",";
        }
        file << dataframe_output_2[dataframe_output_2.size()-1][i] << std::endl;
    }
}
void SSR_model::write_to_file_output_3() {      // outputs site results
    std::ofstream file;
    file.open(output_filename_3);
    
    // adding headers
    for (size_t i {0}; i<headers_output_3.size()-1; i++) {
        file << headers_output_3[i] << ",";
    }
    file << headers_output_3[headers_output_3.size()-1] << std::endl;
    
    // adding zeros
    for (size_t i {0}; i<headers_output_3.size()-1; i++) {
        file << 0 << ",";
    }
    file << 0 << std::endl;
    
    // adding data
    for (size_t i {0}; i<site_file_day_list.size(); i++) {
        for (size_t j {}; j<dataframe_output_3.size()-1; j++) {
            file << dataframe_output_3[j][i] << ",";
        }
        file << dataframe_output_3[dataframe_output_3.size()-1][i] << std::endl;
    }
}
void SSR_model::write_to_file_output_4() {      // outputs limits
    std::ofstream file;
    file.open(output_filename_4);
    file << "limits" << std::endl;
    for (auto x: interface_lim_list) {
        file << x << std::endl;
    }
}
void SSR_model::write_to_file_output_5() {      // outputs results for python model
    std::ofstream file;
    file.open(output_filename_5);
    for (size_t i {0}; i<headers_output_3.size()-1; i++) {
        file << headers_output_5[i] << ",";
    }
    file << headers_output_5[headers_output_5.size()-1] << std::endl;
    for (size_t i {0}; i<time_output.size(); i++) {
        for (size_t j {}; j<dataframe_output_5.size()-1; j++) {
            file << dataframe_output_5[j][i] << ",";
        }
        file << dataframe_output_5[dataframe_output_5.size()-1][i] << std::endl;
    }
}

// another function for clearing all vectors..
// how many data vectors I actually have??

// member methods for clearing input data lists
void SSR_model::clear_material_properties_lists () {
    ku_list.clear();
    kf_list.clear();
    SP_list.clear();
    a_list.clear();
    Sr_list.clear();
    Ls_list.clear();
    w_grav_list.clear();
    rhod_list.clear();
    rhos_list.clear();
    porosity_list.clear();
}
void SSR_model::clear_temperature_lists () {
    day_list.clear();
    date_list.clear();
    temps_list.clear();
    S_vals_list.clear(); // these S vals should actually be here. This is not an input but rather calculated within the program.
}
void SSR_model::clear_S_vals() {
    
}
void SSR_model::clear_test_site_data() {
    
}


// member methods for populating input data lists
void SSR_model::populate_layer_property_lists (std::vector<std::vector<double>> &input_values) {
    for (auto value: input_values[0]) {
        rhod_list.push_back(value);
    }
    for (auto value: input_values[1]) {
        rhos_list.push_back(value);
    }
    for (auto value: input_values[2]) {
        porosity_list.push_back(value);
    }
    for (auto value: input_values[3]) {
        w_grav_list.push_back(value);
    }
    for (auto value: input_values[4]) {
        SP_list.push_back(value);
    }
    for (auto value: input_values[5]) {
        a_list.push_back(value);
    }
    for (auto value: input_values[6]) {
        ku_list.push_back(value);
    }
    for (auto value: input_values[7]) {
        kf_list.push_back(value);
    }
    for (auto value: input_values[8]) {
        Ls_list.push_back(value);
    }
    for (auto value: input_values[8]) {
        Ls_list.push_back(value);
    }
}
void SSR_model::popoulate_temperature_lists (std::vector<double> &temperature_values) {
    for (auto teperature: temperature_values) {
        temps_list.push_back(teperature);
    }
    
    int length {};
    length = temperature_values.size();
    for (size_t i {}; i <= length; i++) {
        day_list.push_back(i);
    }
    
}
void SSR_model::populate_S_vals_list () {
    // first thing i sto check if the dates list is empty or not
    // if that lits is not empty, tehn the S vals have to be set according to teh dates
    // else link them to months
    if (true) {
        double base_S {0.875};
        int first_half {107};
        int second_half {105};
        
        for (size_t i {0}; i <= second_half; i++) {
            if (i <= 16) {
                base_S += 0.025/16.0;
                S_vals_list.push_back(base_S);
            } else if (i <= 46) {
                base_S += 0.05/31.0;
                S_vals_list.push_back(base_S);
            } else if (i <= 76) {
                base_S += 0.05/30.0;
                S_vals_list.push_back(base_S);
            } else if (i <= 107) {
                S_vals_list.push_back(1.0);
            } else if (i <= 137) {
                S_vals_list.push_back(1.0);
            }
        }
        
        std::reverse(S_vals_list.begin(), S_vals_list.end());
        
        base_S = 0.875;
        for (size_t i {0}; i <= second_half; i++) {
            if (i <= 16) {
                base_S -= 0.025/16.0;
                S_vals_list.push_back(base_S);
            } else if (i <= 44) {
                base_S -= 0.05/28.0;
                S_vals_list.push_back(base_S);
            } else if (i <= 75) {
                base_S -= 0.05/31.0;
                S_vals_list.push_back(base_S);
            } else if (i <= 105) {
                base_S -= 0.05/30.0;
                S_vals_list.push_back(base_S);
            } else if (i <= 136) {
                base_S += 0.05/31.0;
                S_vals_list.push_back(base_S);
            }
        }
    }
}


// member methods for running calculation
void SSR_model::run_single_calculation() {
    double dt {};
    double dz0_imp {};
    double partial_time_step {};
    
    interface_lim_creation();
    set_total_test_time();
    set_gradT_p();
    set_Cq_lim_values();
    add_zero_day_to_output_container();
    
    while (get_current_hour_count() < get_total_test_time()) {
            if (partial_time_step != 0) {
                dt = set_partial_time_step(partial_time_step);
            } else {
                dt = set_full_step_dt();
            }
            set_index_alt();
            set_temp();
            set_S();
            set_layer_props();
            set_resistance();
            
            dz0_imp = calculate_dz0_imp(dt);
            
            if (interface_check(dz0_imp)) {
                decrement_current_hour_count(dt);
                dz0_imp = calculate_dz0_residual();
                dt = calculate_dt(dz0_imp);
                increment_current_hour_count(dt);
                increment_partial_time_step(partial_time_step, dt);
            } else {
                partial_time_step = 0;
            }
            calculate_FI(dt);
            calculate_step_increments(dt, dz0_imp);
            calculate_balance_flux(dt, dz0_imp);
            add_results_to_output_containers(dt, dz0_imp);
        }
        chaussee_output_FI_list();
        site_output_FI_list();
        push_back_vectors();
}
void SSR_model::write_to_file_outputs() {
    write_to_file_output_1();
    write_to_file_output_2();
    write_to_file_output_3();
    write_to_file_output_4();
    write_to_file_output_5();
}
void SSR_model::load_all_files() {
    load_layers_file();
    load_data_file();
    load_other_file();
    load_chaussee_file();
    load_site_file();
}
void SSR_model::pre_calculation_operations() {
    interface_lim_creation();
    set_total_test_time();
    set_gradT_p();
    set_Cq_lim_values();
    add_zero_day_to_output_container();
}

// temporary functions during development
void SSR_model::print_out_temperature_TEMP() {
    std::cout << "Printing out temperature list";
    for (auto x: temps_list) {
        std::cout << x << std::endl;
    }
}
void SSR_model::print_out_material_properties_TEMP() {
    std::cout << "Printing out ku list:" << std::endl;
    for (auto x: ku_list) {
        std::cout << x << std::endl;
    }
}
std::string SSR_model::select_temperature_file_TEMP() {
    std::string filename {};
    std::cout << "Pleasi insert filename: ";
    std::getline(std::cin, filename);
    std::cout << "Filename: " << filename << std::endl;
    return filename;
}
void SSR_model::load_layers_file_TEMP(const std::string &filename) {
    std::ifstream file(filename);
    std::string line {};
    std::string val_holder {};
    
    if (!file.is_open()) {
        std::cout << "Failed to open: " << filename << std::endl;
    } else {
        getline(file, line);
        while(getline(file, line)) {
            std::stringstream string_stream(line);
            getline(string_stream, val_holder, ',');
            getline(string_stream, val_holder, ',');
            if (val_holder == "") {
                (this->layer_thickness_list).push_back(10);
            } else {
                (this->layer_thickness_list).push_back(stof(val_holder));
            }
            getline(string_stream, val_holder, ',');
            (this->ku_list).push_back(std::stof(val_holder));
            getline(string_stream, val_holder, ',');
            (this->kf_list).push_back(std::stof(val_holder));
            getline(string_stream, val_holder, ',');
            (this->SP_list).push_back(std::stof(val_holder));
            getline(string_stream, val_holder, ',');
            (this->a_list).push_back(std::stof(val_holder));
            getline(string_stream, val_holder, ',');
            (this->Sr_list).push_back(std::stof(val_holder));
            getline(string_stream, val_holder, ',');
            (this->Ls_list).push_back(std::stof(val_holder));
            getline(string_stream, val_holder, ',');
            (this->w_grav_list).push_back(std::stof(val_holder));
            getline(string_stream, val_holder, ',');
            (this->rhod_list).push_back(std::stof(val_holder));
        }
    }
    for (auto x: layer_thickness_list) {
        layer_thickness_list_mod.push_back(x);
    }
}
void SSR_model::print_S_vals_list() {
    for (auto x: S_vals_list) {
        std::cout << x << std::endl;
    }
}