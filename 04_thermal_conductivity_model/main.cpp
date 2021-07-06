#include <Thermal_Conductivity_Model.h>
#include <iostream>
#include <string>

int main() {
    
    // These are values that should be taken from the main program.
    double porosity {0.4};
    double degree_of_saturation {0.4};
    
    // Initiate the model object
    Thermal_Conductivity_Model thermal_conductivity_model (porosity, degree_of_saturation);
    
    // STEP 1: Set thermal conductivity for particles.
    // This can be done either by selecting a rock type from the list or by selecting minerals form list and defining percentage.
    // If desired mineral is not in the list, there should aslo be an option to manually add mineral elemnts in the calculation. IN that way the user has to provide also the thermal conductivity of this additional mineral.
    // I did not implement this here, but when selecting minerals and their corresponding percentages, there should also be a check that the sum is equal to 100%.
    char selection {};    
    std::cout << "Set particle thermal conductivity" << std::endl;
    std::cout << "1. Based on rock" << std::endl;
    std::cout << "2. Based on minerals" << std::endl;
    
    std::cout << "Select option (type 1 or 2): ";
    std::cin >> selection;
    std::cin.sync();
        
    // Setting particle thermal conductivity based on rock type
    if (selection == '1') {
        std::string rock_choice {};
        std::cout << std::endl;
        thermal_conductivity_model.display_solid_type_names();
        std::cout << "\nSelect solid rock type (type only number): ";
        std::getline(std::cin, rock_choice);
        thermal_conductivity_model.set_thermal_conductivity_from_rock(rock_choice);
    
    // Setting particle thermal conductivity based on difefernt minerals. In this option
    // multiple minerals can be selected. There should also be an option to manually add values if desired mineral is not in the list.
    // Probably some functions have to be adjusted based on how the selection is made in GUI and how that selection is being found in that long vector with all the minerals.
    } else if (selection == '2') {
        char choice {};
        std::string mineral_selection {};
        std::string mineral_percentage {};
        std::string mineral_thermal {};
        while (true) {
            thermal_conductivity_model.display_mineral_type_names();
            std::cout << "\nSelect from the list (type '6.1.1.' or similar): ";
            std::getline(std::cin, mineral_selection);            
            std::cout << "Select percentage (from 0 to 1): ";
            std::getline(std::cin, mineral_percentage);
            
            thermal_conductivity_model.add_to_mineral_list_from_list_selection(mineral_selection, mineral_percentage);
            
            std::cout << "\nSelect another one? Y/N";
            std::cin >> choice;
            std::cin.ignore();
            if (choice == 'N' || choice == 'n') {
                break;
            }
        }
        // Additional minerals are added here. There is no need to save the mineral itself to a database or as it is in this code in a vector.
        // The user can just manually add thermal conductivity for that mineral and percentage.
        while (true) {
            std::cout << "\nAdd more minerals manually? (Y/N)";
            std::cin >> choice;
            std::cin.ignore();
            if (choice == 'N' || choice == 'n') {
                break;
            }
            std::cout << "\nAdd thermal conductivity of a mineral: ";
            std::getline(std::cin, mineral_thermal);
            std::cout << "\nAdd percentage (from 0 to 1): ";
            std::getline(std::cin, mineral_percentage);
            thermal_conductivity_model.add_to_mineral_list_from_manual_selection(mineral_thermal, mineral_percentage);
        }
        thermal_conductivity_model.calculate_thermal_conductivity_from_minerals();
    }
        
    // STEP 2. Selection of material type. This will set the correct kappa value for the model calculation.
    std::string material_selection {};
    std::cout << "\nMaterial type selection" << std::endl;
    thermal_conductivity_model.display_material_type_names();
    std::cout << "Select material from the list: ";
    std::getline(std::cin, material_selection);
    thermal_conductivity_model.set_material_type(material_selection);
    
    // STEP 3. Running the model
    // This step just do all the calculation with all the input parameters and choices selected from before.
    double unfrozen_thermal_conductivity {};
    double frozen_thermal_conductivity {};
    thermal_conductivity_model.calculate_thermal_conductivity(unfrozen_thermal_conductivity, frozen_thermal_conductivity);
    thermal_conductivity_model.display_all_parameters();
        
    return 0;
}