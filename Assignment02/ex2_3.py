
import numpy as np
import matplotlib.pyplot as plt
file = ['Data1.csv', 'Data2.csv', 'Data3.csv', 'Data4.csv']
i = 1
for f in file:
    np_array = np.loadtxt('provided_files/' + f, comments='#', skiprows=1)
    x = np_array[:,0]
    y = np_array[:, 1]
    mean = np.mean(np_array, axis=0)
    correlation = np.correlate(x, y)
    var = np.var(np_array, axis=0)
    print('correlation:', correlation)
    print('mean:', mean)
    print('var:', var)
    print(np_array)
    model = np.polyfit(x, y, 1)
    lin_reg = np.poly1d(model)
    x_lin_reg = np.linspace(np.amin(x), np.amax(x), 100)
    y_lin_reg = lin_reg(x_lin_reg)
    fig = plt.figure()
    plt.plot(x_lin_reg, y_lin_reg, c='r', label='linear regression')
    plt.scatter(x, y)
    ax = plt.axes()
    mean_x = mean[0]
    title = f + ': mean(x,y)= (' + '{:.2f}'.format(mean[0]) + '{:.2f}'.format(mean[1]) +')' \
            + ', var (x,y)=' + '{:.2f}'.format(var[0]) + '{:.2f}'.format(var[1]) +')' \
            + ', correlation=' + '{:.2f}'.format(correlation[0])
    ax.set(xlabel='x', ylabel='y',title=title)
    plt.legend()
    plt.show()

    fig.savefig('out_Data' + str(i) + '.png')
    i += 1

