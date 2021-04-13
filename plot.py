import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

n = [2097152, 3145728, 4194304, 5242880, 6291456, 7340032, 8388608]
tsimd = np.array([0.1005797, 0.1512374, 0.2016846, 0.2524397, 0.3013446, 0.3520538, 0.4016309])
std = np.array([0.0503455, 0.07546566, 0.1007527, 0.1258644, 0.153692, 0.1763379, 0.2018683])
avx = np.array([0.0201362, 0.03012634, 0.04039097, 0.05019722, 0.06014804, 0.07003797, 0.08019224])

################# TIMES ####################

fig, ax1 = plt.subplots()
ax1.set_xlabel('Elements')
ax1.set_ylabel('Time [s]')
ax1.set_title('Execution Time History - tan(sin(x)) and tan(cos(x))')

ax1.plot(n, tsimd, 'b^-', label='TSIMD')
ax1.plot(n, std, 'rv-', label='STD')
ax1.plot(n, avx, 'ko-', label='AVX')
ax1.legend(loc='upper left')

plt.show()

################# SPEEDUP ####################

fig, ax1 = plt.subplots()
ax1.set_xlabel('Elements')
ax1.set_ylabel('Speedup')
ax1.set_title('Speedup History')

ax1.plot(n, tsimd/std, 'b^-', label='TSIMD/STD')
ax1.plot(n, tsimd/avx, 'rv-', label='TSIMD/AVX')
ax1.plot(n, std/avx, 'ko-', label='STD/AVX')
ax1.legend(loc='upper left')
ax1.set_ylim([1.8,6])

plt.show()

################# SCALABILITY ####################

tsimd_sca = []
std_sca = []
avx_sca = []
n_sca = []

for i in range(1,len(n)):
    tsimd_sca.append((tsimd[i] - tsimd[i-1])/ (n[i] - n[i-1]))
    std_sca.append((std[i] - std[i-1])/ (n[i] - n[i-1]))
    avx_sca.append((avx[i] - avx[i-1])/(n[i] - n[i-1]))
    n_sca.append(n[i])

fig, ax1 = plt.subplots()
ax1.set_xlabel('Elements')
ax1.set_ylabel('Scalability Rate')
ax1.set_title('Scalability Rate History')

ax1.plot(n_sca, tsimd_sca, 'b^-', label='TSIMD')
ax1.plot(n_sca, std_sca, 'rv-', label='STD')
ax1.plot(n_sca, avx_sca, 'ko-', label='AVX')
ax1.legend(loc='upper left')
#ax1.set_ylim([1.8,6])

plt.show()