#include "Thermal_Conductivity_Model.h"
#include <iostream>
#include <cmath>



Thermal_Conductivity_Model::Thermal_Conductivity_Model(double &porosity, double &degree_of_saturation)
    : porosity{porosity}, degree_of_saturation{degree_of_saturation} {
        std::cout << "Porosity initialized to: " << porosity << std::endl;
        std::cout << "Degree of saturation initialized to: " << degree_of_saturation << std::endl;
    }

Thermal_Conductivity_Model::~Thermal_Conductivity_Model(){
}

void Thermal_Conductivity_Model::display_solid_type_names() {
    for (auto x: solid_type_names) {
        std::cout << x << std::endl;
    }
}

void Thermal_Conductivity_Model::display_mineral_type_names() {
    std::cout << std::endl;
    int counter {0};
    for (auto x: mineral_type_class_names) {
        std::cout << x << std::endl;
        for (auto mineral: mineral_type_values.at(counter)) {
            for (auto content: mineral) {
                std::cout << content << " ";
            }
            std::cout << std::endl;
        }
        counter += 1;
    }
}

void Thermal_Conductivity_Model::set_thermal_conductivity_from_rock(const std::string &rock_choice) {
    int rock_index {std::stoi(rock_choice)};
    particle_thermal_conductivity = solid_type_values.at(rock_index-1).at(0);
}

void Thermal_Conductivity_Model::add_to_mineral_list_from_list_selection(const std::string &mineral_choice, const std::string &mineral_percentage) {
    for (auto mineral_class: mineral_type_values) {
        for (auto mineral: mineral_class) {
            size_t position = mineral.at(0).find(mineral_choice);
            if (position != std::string::npos) {
                mineral_thermal_conductivity_list.push_back(mineral.at(2));
            }
        } 
    }
    mineral_percentage_list.push_back(mineral_percentage);
} 

void Thermal_Conductivity_Model::add_to_mineral_list_from_manual_selection(const std::string &mineral_thermal, const std::string &mineral_percentage) {
    mineral_thermal_conductivity_list.push_back(mineral_thermal);
    mineral_percentage_list.push_back(mineral_percentage);
}

void Thermal_Conductivity_Model::calculate_thermal_conductivity_from_minerals() {
    int counter {0};
    particle_thermal_conductivity = 1;
    for (auto x: mineral_thermal_conductivity_list) {
        particle_thermal_conductivity *= std::pow(std::stod(x), std::stod(mineral_percentage_list.at(counter)));
        counter += 1;
    }    
}

void Thermal_Conductivity_Model::display_material_type_names() {
    for (auto x: material_type_names) {
        std::cout << x.at(0) << std::endl;
    }
}

void Thermal_Conductivity_Model::set_material_type(const std::string &material_choice) {
    kappa_unfrozen = std::stod(material_type_names.at(std::stoi(material_choice)-1).at(1));
    kappa_frozen = std::stod(material_type_names.at(std::stoi(material_choice)-1).at(2));
}

void Thermal_Conductivity_Model::display_all_parameters() {
    std::cout << "\nINPUT PARAMETERS FOR THE MODEL:" << std::endl;
    std::cout << "Particle thermal conductivity: " << particle_thermal_conductivity << std::endl;
    std::cout << "Kappa value unfrozen: " << kappa_unfrozen << std::endl;
    std::cout << "Kappa value frozen: " << kappa_frozen << std::endl;
    std::cout << "Porosity: " << porosity << std::endl;
    std::cout << "Degree of saturation: " << degree_of_saturation << std::endl;
    
    std::cout << "\nINTERMEDIATE CALCULATION VALUES:" << std::endl;
    std::cout << "Unfrozen saturated thermal conductivity: " << saturated_thermal_conductivity_unfrozen << std::endl;
    std::cout << "Frozen saturated thermal conductivity: " << saturated_thermal_conductivity_frozen << std::endl;
    std::cout << "Dry thermal conductivity: " << dry_thermal_conductivity << std::endl;
    std::cout << "Unfrozen normalized thermal conductivity: " << normalized_thermal_conductivity_unfrozen << std::endl;
    std::cout << "Frozen normalized thermal conductivity: " << normalized_thermal_conductivity_frozen << std::endl;
    
    std::cout << "\nFINAL MODEL RESULT:" << std::endl;
    std::cout << "Unfrozen thermal conductivity: " << unfrozen_th << std::endl;
    std::cout << "Frozen thermal conductivity: " << frozen_th << std::endl;
}

void Thermal_Conductivity_Model::calculate_saturated_thermal_conductivity() {
    saturated_thermal_conductivity_unfrozen = std::pow(particle_thermal_conductivity, 1-porosity)*std::pow(thermal_conductivity_water, porosity); 
    saturated_thermal_conductivity_frozen = std::pow(particle_thermal_conductivity, 1-porosity)*std::pow(thermal_conductivity_ice, porosity);
}

void Thermal_Conductivity_Model::calculate_dry_thermal_conductivity() {
    dry_thermal_conductivity = std::pow(particle_thermal_conductivity, std::pow(1-porosity, 0.59))*std::pow(thermal_conductivity_air, std::pow(porosity, 0.73));
}

void Thermal_Conductivity_Model::calculate_normalized_thermal_conductivity() {
    normalized_thermal_conductivity_unfrozen = (kappa_unfrozen*degree_of_saturation)/(1+(kappa_unfrozen-1)*degree_of_saturation);
    normalized_thermal_conductivity_frozen = (kappa_frozen*degree_of_saturation)/(1+(kappa_frozen-1)*degree_of_saturation);
}

void Thermal_Conductivity_Model::calculate_thermal_conductivity(double &unfrozen_thermal_conductivity, double &frozen_thermal_conductivity) {
    calculate_saturated_thermal_conductivity();
    calculate_dry_thermal_conductivity();
    calculate_normalized_thermal_conductivity();
    unfrozen_th = (saturated_thermal_conductivity_unfrozen - dry_thermal_conductivity) * normalized_thermal_conductivity_unfrozen + dry_thermal_conductivity;
    frozen_th = (saturated_thermal_conductivity_frozen - dry_thermal_conductivity) * normalized_thermal_conductivity_frozen + dry_thermal_conductivity;
    unfrozen_thermal_conductivity = unfrozen_th;
    frozen_thermal_conductivity = frozen_th;
    
}

