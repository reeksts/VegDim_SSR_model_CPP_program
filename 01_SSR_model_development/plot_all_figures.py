import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import math

full_testsite_filename_vector = []

file_location_1 = "01_SAAR_original_data_set\\"
file_location_2 = "02_QUEB_with_default_parameters\\"
file_location_3 = "03_QUEB_with_given_parameters\\"
file_location_4 = "04_QUEB_with_backcalculated_values\\"
file_location_5 = "05_ROROS_data_set\\"

file_location_vector = []
file_location_vector.append(file_location_1)
file_location_vector.append(file_location_2)
file_location_vector.append(file_location_3)
file_location_vector.append(file_location_4)
file_location_vector.append(file_location_5)

filenames_file = "filenames.csv"
output_prefix = "data_output\\"

postfix_1 = "_output_1.csv"
postfix_2 = "_output_2.csv"
postfix_3 = "_output_3.csv"
postfix_4 = "_output_4.csv"
postfix_5 = '_frost_penetration'
postfix_6 = '_frost_heave'

for i in file_location_vector:
    filenames = output_prefix + i + filenames_file
    import_filenames = pd.read_csv(filenames, header=None)
    for j in import_filenames[0]:
        output_filename_vector = []
        output_filename_vector.append(output_prefix + i + j + postfix_1)    #file location
        output_filename_vector.append(output_prefix + i + j + postfix_2)    #file location
        output_filename_vector.append(output_prefix + i + j + postfix_3)    #file location
        output_filename_vector.append(output_prefix + i + j + postfix_4)    #file location
        output_filename_vector.append(output_prefix + i + j + postfix_5)    #figure location
        output_filename_vector.append(output_prefix + i + j + postfix_6)    #figure location
        output_filename_vector.append(j + postfix_5)
        output_filename_vector.append(j + postfix_6)
        full_testsite_filename_vector.append(output_filename_vector)
        
min_z = -0.1
max_z = 2.1
min_h = -0.01
max_h = 0.21

def find_x_lim(x):
    x_lim = int(math.ceil(x / 10.0)) * 10
    if x==x_lim:
        return x_lim +10
    else:
        return x_lim

def find_y_lim_frost(y):
    y_lim = int(math.ceil(y / 0.5)) * 0.5
    if y==y_lim:
        return y_lim + 0.5
    else:
        return y_lim
    
def fig_1_frost_penetration(df1, df2, df3, df4, fig1_loc, fig1_name):
    fig = plt.figure(figsize=(8,6), dpi=100)
    ax = fig.add_axes([0.1, 0.1, 0.8, 0.8])
    ax.plot(df1['day'], df1['z'], label='my result', color='#948B3d', lw=2)
    ax.plot(df2['day'], df2['chau_z'], label='from Chau')
    ax.plot(df2['day'], df3['site_z'], label='from Saarelainen', marker='x')
    ax.legend(loc="upper right")
    x_lim = find_x_lim(df1['day'].max())
    for i in range(df4['limits'].count() - 1):
        ax.plot([-5, x_lim], [df4['limits'][i], df4['limits'][i]], color='black', lw=1, ls='dashed')
    ax.set_xlim([-5, x_lim])
    y_lim = find_y_lim_frost(df1['z'].max())
    ax.set_ylim(-0.1, y_lim)
    ax.set_xticks(range(0,x_lim+10,10))
    ax.set_yticks([x / 10.0 for x in range(0, int(y_lim*10)+5, 5)])
    ax.set_xlabel('Days', size=12)
    ax.set_ylabel('Frost depth, m', size=12)
    ax.set_title(fig1_name, size=14)
    for i in ['top', 'bottom', 'left', 'right']:
        ax.spines[i].set_linewidth(1.5)
    ax.tick_params(axis='both', direction='in', width=1.5, right=True, top=True)
    ax.invert_yaxis()
    fig.savefig(fig1_loc, dpi=200)
    plt.close()

def fig_2_frost_heave(df1, df2, df3, df4, fig2_loc, fig2_name):
    fig = plt.figure(figsize=(8,6), dpi=100)
    ax = fig.add_axes([0.1, 0.1, 0.8, 0.8])
    ax.plot(df1['day'], df1['h'], label='my result', color='#948B3d', lw=2)
    ax.plot(df2['day'], df2['chau_h'], label='from Chau')
    ax.plot(df2['day'], df3['site_h'], label='from Saarelainen', marker='x')
    ax.legend(loc="upper right")
    x_lim = find_x_lim(df2['day'].max())
    ax.set_xlim([-5, x_lim])
    ax.set_ylim(min_h, max_h)
    ax.set_xticks(range(0,x_lim+10,10))
    ax.set_yticks([0, 0.05, 0.1, 0.15, 0.2])
    ax.set_xlabel('Days', size=12)
    ax.set_ylabel('Frost heave, cm', size=12)
    ax.set_title(fig2_name, size=14)
    for i in ['top', 'bottom', 'left', 'right']:
        ax.spines[i].set_linewidth(1.5)
    ax.tick_params(axis='both', direction='in', width=1.5, right=True, top=True)
    print("DONE {}".format(fig2_name))
    fig.savefig(fig2_loc, dpi=200)
    plt.close()

def print_figures():
    for i in full_testsite_filename_vector:
        df1 = pd.read_csv(i[0])     # the main data set
        df2 = pd.read_csv(i[1])     # chaussee results
        df3 = pd.read_csv(i[2])     # site results
        df4 = pd.read_csv(i[3])     # limits
        fig1_loc = i[4]
        fig2_loc = i[5]
        fig1_name = i[6]
        fig2_name = i[7]
        fig_1_frost_penetration(df1, df2, df3, df4, fig1_loc, fig1_name)
        fig_2_frost_heave(df1, df2, df3, df4, fig2_loc, fig2_name)


print_figures()
