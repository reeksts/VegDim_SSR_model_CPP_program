import pandas as pd

filenames = pd.read_csv("filenames.csv", header=None)

postfix1 = "_layers.csv"
postfix2 = "_data.csv"
postfix3 = "_other.csv"
postfix4 = "_chaussee.csv"
postfix5 = "_site.csv"

for i in filenames[0]:
    file1 = pd.read_excel(i + ".xlsx", sheet_name = "layers", index_col=0)
    file1.to_csv(i + postfix1)
    file2 = pd.read_excel(i + ".xlsx", sheet_name = "data", index_col=0)
    file2.to_csv(i + postfix2)
    file2 = pd.read_excel(i + ".xlsx", sheet_name = "other", index_col=0)
    file2.to_csv(i + postfix3)
    file2 = pd.read_excel(i + ".xlsx", sheet_name = "chaussee", index_col=0)
    file2.to_csv(i + postfix4)
    file2 = pd.read_excel(i + ".xlsx", sheet_name = "site", index_col=0)
    file2.to_csv(i + postfix5)

print("DONE")
