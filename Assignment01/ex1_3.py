
fdata_txt = 'data'
xList = []
yList = []
zList = []
with open(fdata_txt, 'r') as f:
    # skip first two line
    next(f)
    next(f)
    for line in f:
        list = line.split(' ')
        xList.append(list[5])
        yList.append(list[9])
        zList.append(list[12])
        print(list[5])
        print(list[9])
        print(list[12])