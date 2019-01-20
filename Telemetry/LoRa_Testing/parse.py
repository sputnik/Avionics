filenames = ["LoRa_Test_Fiberglass", "LoRa_Test"]
for filename in filenames:
    fi = filename + ".txt"
    fo = filename + "_out.dat"
    file = open(fi, "r")
    f_w = open(fo,"w")
    for line in file:
        lines = line.split()
        if lines[0][0] != 'T' and lines[1][0] != 'L':
            lat = lines[1]
            lon = lines[2]
            alt = lines[3].split(",")[0]
            l = lon + "," + lat + "," + alt + "\n"
            f_w.write(l)
        #end if
    #end for
    f_w.close()
    file.close()
#end for
