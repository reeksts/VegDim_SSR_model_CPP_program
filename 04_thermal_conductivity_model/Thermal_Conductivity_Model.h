#ifndef THERMAL_CONDUCTIVITY_MODEL_H
#define THERMAL_CONDUCTIVITY_MODEL_H

#include <vector>
#include <string>

class Thermal_Conductivity_Model {
private:
    double degree_of_saturation {};
    double porosity {};
    std::vector<std::string> solid_type_names {"1. Anorthodide", "2. Basalt", "3. Diabase", "4. Dolostone", "5. Gabbro",
                                                "6. Gneiss", "7. Granite", "8. Limestone", "9. Marble", "10. Quartzite",
                                                "11. Sandstone", "12. Schist", "13. Shale", "14. Syenite", "15. Trap rock",
                                                "16. Coal", "17. Peat", "18. Silt"};
    std::vector<std::vector<double>> solid_type_values {{2.73, 1.80}, {2.90, 1.70}, {2.98, 2.30}, {2.90, 3.80}, {3.03, 2.20},
                                                         {2.75, 2.60}, {2.75, 2.50}, {2.70, 2.50}, {2.80, 3.20}, {2.63, 5.50},
                                                         {2.80, 3.00}, {2.65, 1.50}, {2.65, 2.00}, {2.80, 2.00}, {2.90, 2.00},
                                                         {2.73, 1.80}, {2.90, 1.70}, {2.98, 2.00}};
    std::vector<std::string> mineral_type_class_names {"1. Nesosilicates (single tetrahedron)",
                                                       "2. Sorosilicates (double tetrahedron)",
                                                       "3. Cyclosilicates (rings of tetrahedrons)",
                                                       "4. Inosilicates (chains of tetrahedrons)",
                                                       "5. Phyllosilicates (sheets)",
                                                       "6. Tectosilicates (framework)",
                                                       "7. Carbonates",
                                                       "8. Oxides",
                                                       "9. Hydroxides",
                                                       "10. Sulphates",
                                                       "11. Halides",
                                                       "12. Sulphides",
                                                       "13. Phosphates"};
    std::vector<std::vector<std::vector<std::string>>> mineral_type_values {{{"1.1. Olivine", "", ""},
                                                                          {"1.1.1. Chrysolite", "3.47", "4.81"},
                                                                          {"1.1.2. Fayalite", "4.36", "3.16"},
                                                                          {"1.1.3. Forsterite", "3.28", "5.03"},
                                                                          {"1.1.4. Hyalosiderite", "3.77", "3.45"},
                                                                          {"1.2. Garnet", "", ""},
                                                                          {"1.2.1. Almandine", "3.93", "3.31"},
                                                                          {"1.2.2. Andradite", "3.75", "3.09"},
                                                                          {"1.2.3. Grossularite", "3.49", "5.48"},
                                                                          {"1.2.4. Pyrope", "3.75", "3.18"},
                                                                          {"1.2.5. Spessartite", "3.99", "3.40"}},
                                                                         {{"2.1. Epidote", "", ""},
                                                                          {"2.1.1. Clinozoisite", "3.36", "2.40"},
                                                                          {"2.1.2. Epidote", "2.19", "2.83"},
                                                                          {"2.1.3. Zoisite", "3.27", "2.15"},
                                                                          {"2.2. Idocrase", "3.34", "2.41"}},
                                                                         {{"3.1. Beryl", "2.70", "3.99"},
                                                                          {"3.2. Cordierite", "2.59", "2.72"},
                                                                          {"3.3. Tourmaline", "3.13", "5.28"}},
                                                                         {{"4.1. Amphibole (double chains)", "", ""},
                                                                          {"4.1.1. Actinolite", "3.06", "3.48"},
                                                                          {"4.1.2. Grunerite", "3.40", "3.32"},
                                                                          {"4.1.3. Hornblende", "3.18", "2.81"},
                                                                          {"4.1.4. Tremolite", "2.99", "4.78"},
                                                                          {"4.2. Pyroxene (single chains)", "", ""},
                                                                          {"4.2.1. Acmite", "3.54", "3.49"},
                                                                          {"4.2.2. Augite", "3.27", "3.82"},
                                                                          {"4.2.3. Bronzite", "3.36", "4.16"},
                                                                          {"4.2.4. Diopside", "3.33", "4.93"},
                                                                          {"4.2.5. Enstatite", "3.27", "4.47"},
                                                                          {"4.2.6. Spodumene", "3.16", "5.65"}},
                                                                         {{"5.1. Chlorite", "2.75", "5.15"},
                                                                          {"5.2. Mica", "", ""},
                                                                          {"5.2.1. Biotite", "2.98", "2.02"},
                                                                          {"5.2.2. Glauconite", "2.85", "1.63"},
                                                                          {"5.2.3. Lepidomelane", "2.86", "1.57"},
                                                                          {"5.2.4. Muscovite", "2.85", "3.48"},
                                                                          {"5.2.5. Phlogopite", "2.85", "2.13"},
                                                                          {"5.3. Pyrophyllite", "2.83", "8.14"},
                                                                          {"5.4. Serpentine", "", ""},
                                                                          {"5.4.1. Antigorite", "2.66", "2.95"},
                                                                          {"5.4.2. Chrysotile", "2.60", "5.30"},
                                                                          {"5.4.3. Lizardite", "2.60", "2.34"},
                                                                          {"5.5. Talc", "2.81", "6.10"}},
                                                                         {{"6.1. Feldspar", "", ""},
                                                                          {"6.1.1. Celsian", "3.09", "1.44"},
                                                                          {"6.1.2. Microline", "2.56", "2.49"},
                                                                          {"6.1.3. Orthoclase", "2.58", "2.32"},
                                                                          {"6.1.4. Sanidinev", "2.57", "1.65"},
                                                                          {"6.2. Feldspathoid", "", ""},
                                                                          {"6.2.1. Nepheline", "2.62", "1.73"},
                                                                          {"6.2.2. Sodalite", "2.33", "2.51"},
                                                                          {"6.3. Plagioclase", "", ""},
                                                                          {"6.3.1. Albite", "2.63", "1.96"},
                                                                          {"6.3.2. Anorthite", "2.77", "1.68"},
                                                                          {"6.3.3. Bytownite", "2.72", "1.56"},
                                                                          {"6.3.4. Labradorite", "2.70", "1.53"},
                                                                          {"6.3.5. Oligoclase", "2.64", "1.98"},
                                                                          {"6.4. Silica", "", ""},
                                                                          {"6.4.1. Hyalite", "2.08", "1.21"},
                                                                          {"6.4.2. Novaculite", "2.66", "7.21"},
                                                                          {"6.4.3. Quartz", "2.65", "7.69"},
                                                                          {"6.4.4. Vitreous silica", "2.21", "1.35"}},
                                                                         {{"7.1. Calcite", "2.71", "3.59"},
                                                                          {"7.2. Dolomite", "2.90", "5.51"},
                                                                          {"7.3. Siderite", "3.81", "3.01"}},
                                                                         {{"8.1. Hematite", "5.14", "11.28"},
                                                                          {"8.2. Ilmenite", "4.55", "2.38"},
                                                                          {"8.3. Magnetite", "5.15", "5.10"},
                                                                          {"8.4. Magnesiochromite", "4.23", "2.54"}},
                                                                         {{"9.1. Brucite", "2.39", "8.44"},
                                                                          {"9.2. Gibbsite", "1.88", "2.60"}},
                                                                         {{"10.1. Anhydrite", "2.98", "4.76"},
                                                                          {"10.2. Barite", "4.41", "1.34"},
                                                                          {"10.3. Gypse", "2.30", "1.26"},
                                                                          {"10.4 .Selenite", "2.32", "1.26"}},
                                                                         {{"11.1. Fluorite", "3.10", "9.51"},
                                                                          {"11.2. Halite", "2.10", "6.11"}},
                                                                         {{"12.1. Chalcopyrite", "4.09", "8.20"},
                                                                          {"12.2. Pyrite", "5.10", "19.21"},
                                                                          {"12.3. Pyrrhotite", "4.60", "1.89"},
                                                                          {"12.4. Sphalerite", "4.00", "12.73"}},
                                                                         {{"13.1. Amblygonite", "3.03", "4.99"},
                                                                          {"13.2. Chlorapatite", "3.15", "1.39"},
                                                                          {"13.3. Fluorapatite", "3.22", "1.37"}}};
    std::vector<std::vector<std::string>> material_type_names {{"1. Gravel and coarse sands", "4.60", "1.70"},
                                                               {"2. Medium and fine sands", "3.55", "0.95"},
                                                               {"3. Silty and clayey soils", "1.90", "0.85"},
                                                               {"4. Organic fibrous soils (peat)", "0.60", "0.25"}};
    
    double particle_thermal_conductivity {};    
        
    std::vector<std::string> mineral_list_selection {};
    std::vector<std::string> mineral_thermal_conductivity_list {};
    std::vector<std::string> mineral_percentage_list {};
    
    double kappa_unfrozen {};
    double kappa_frozen {};
    double saturated_thermal_conductivity_unfrozen {};
    double saturated_thermal_conductivity_frozen {};
    double dry_thermal_conductivity {};
    double normalized_thermal_conductivity_unfrozen {};
    double normalized_thermal_conductivity_frozen {};
    double thermal_conductivity_water {0.6};
    double thermal_conductivity_ice {2.24};
    double thermal_conductivity_air {0.024};
    
    double unfrozen_th {1.0};
    double frozen_th {2.0};
    
    void calculate_saturated_thermal_conductivity();
    void calculate_dry_thermal_conductivity();
    void calculate_normalized_thermal_conductivity();
    
public:
    void display_solid_type_names();
    void display_mineral_type_names();
    void set_thermal_conductivity_from_rock(const std::string &rock_choice);
    void add_to_mineral_list_from_list_selection(const std::string &mineral_choice, const std::string &mineral_percentage);
    void add_to_mineral_list_from_manual_selection(const std::string &mineral_thermal, const std::string &mineral_percentage);
    void calculate_thermal_conductivity_from_minerals();
    void display_material_type_names();
    void set_material_type(const std::string &material_choice);
    void display_all_parameters();
    void calculate_thermal_conductivity(double &unfrozen_thermal_conductivity, double &frozen_thermal_conductivity);
    
    // Constructor
    Thermal_Conductivity_Model() {};
    Thermal_Conductivity_Model(double &porosity, double &degree_of_saturation);
    
    // Destructor
    ~Thermal_Conductivity_Model();

};

#endif // THERMAL_CONDUCTIVITY_MODEL_H
