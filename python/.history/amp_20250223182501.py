#!/usr/bin/python3
import numpy as np
class amp:
  def __init__(self, 
               L,   # Number of sections 
               B,   # Section size  
               snr, # Signal to nosie ratio 
               R,   # Communication rate 
               c    # Power allocation 
               ):
    """
    FIXME: Fix the class :)  
    1. Pass all the parameters to the class 
    2. make sure that arrays are copies of the original ones (ground truth signal and codeword)
    """
    np.random.seed(0)
    self.L = L     #
    self.B = B     # Section size 
    self.N = L * B # Size of the code message 
    self.snr = snr # Signal to noise ratio
    self.R = R # Communication rate 
    self.c = c 
    self.std = 1 / np.sqrt(snr)
    self.M = int((self.N * np.log2(self.B)) / (self.R * self.B))
    self.x = self.gen_ss() # Ground truth message 
    

  def awgn_ch(self):
    snr = self.snr 
    M = self.M 
    R = self.R
    N = self.N 
    std = self.std 

    x_gt = self.x.reshape(self.N)
    F = np.random.normal(0, 1/np.sqrt(self.L), (self.M, self.N))
    self.F = F
    noise = std * np.random.randn(self.M)
    y = (F @ x_gt) + noise
    return y

  def gen_ss(self):
    x = np.zeros((self.L, self.B))
    for arr in x:
      randy = np.random.randint(0, self.B)
      arr[randy] = 1
    return x

  def g(self, z, y, V, snr):

    var = 1 / snr
    B = (y - z) / (V + var)
    return B

  def dg(self, V, snr):

    var = 1 / snr
    A = 1 / (V + var)
    return A

  def denoising_a(self, x_hat, v, sigma, r, L, B, c=1):
    """
    Denoising the estimate of the message and it's variance 
    """
    N = int(L * B)
    new_sigma = sigma.copy().reshape(L, B)
    new_r = r.copy().reshape(L, B)
    x_hat = x_hat.reshape(L, B)
    v = v.reshape(L, B)
    for l in range(L):
        x_hat[l, :] = c* np.exp((-c * (c-2*new_r[l, :]))/(2*new_sigma[l, :]**2)) / np.sum(np.exp((-c * (c-2*new_r[l, :]))/(2*new_sigma[l, :]**2)))
        v[l,:] = x_hat[l,:] * (1-x_hat[l, :])
    x_hat  = x_hat.reshape(N)
    v = v.reshape(N)
    return x_hat, v

  def amplify(self, arr, c=1):

    row_idx = np.arange(self.L)
    col_idx = self.get_argmax(arr)
    arr = arr.reshape(self.L, self.B)
    arr_new = np.zeros((self.L, self.B))
    arr_new[row_idx, col_idx] = c
    return arr_new

  def section_error_rate(self, x_gt, x_hat, c=1):

    x_hat = self.amplify(x_hat, c=1)
    x_gt = x_gt.reshape(self.L, self.B)
    count = 0
    for row1, row2 in zip(x_hat, x_gt):
        if all(row1 == row2):
            count += 0
        else:
            count += 1
    ser = count / self.L
    return ser
  def get_argmax(self, arr):

    arr = arr.reshape(self.L, self.B)
    idx = np.argmax(arr, axis=1)
    return idx

  def decode(self, snr, t_max=25, ep=10**-8):
    c = self.c 
    n = self.N
    R = self.R
    y = self.awgn_ch()
    # Initialization
    delta = 1 + ep
    t = 0
    # AMP estimate of the signal
    x_hat = np.zeros(self.N)
    # AMP estimate of the variances per component
    v = np.ones(self.N)/(snr * self.B)
    #v = np.zeros(N)
    # Variances of the estimation of messages before taking the prior into account
    V = np.zeros(self.M)
    z = y.copy()
    ser = []
    ser.append(1)
    while t < t_max and delta > ep:
        # Here I just created a copy of he intilized arrays to use them as old instances (i.e values at t-1 when calculatin values at time step t)
        V_old = V.copy()
        z_old = z.copy()
        x_hat_old =x_hat.copy()

        # AMP starts here
        V = self.F **2 @ v
        z = (self.F @ x_hat) - V * self.g(z_old, y, V_old, snr)

        sigma = 1 / np.sqrt(self.dg(V, snr) @ self.F**2)

        # Estimation of messages before taking the prior into account
        r = x_hat_old + sigma ** 2 * (self.g(z, y, V, snr) @ self.F)
        # Creating copies of sigma and r arrays and reshaping them in order to use them in the denoisin function and update the estimates
        x_hat, v = self.denoising_a(x_hat, v, sigma, r, self.L , self.B, c)
        delta = (1/n)* np.sum(np.square(x_hat-x_hat_old))
        temp_err = self.section_error_rate(self.x, x_hat)
        ser.append(temp_err)
        #ber.append(bit_error)
        t = t + 1
        if t > 2 * t_max:
            return ser
            break
    return ser
  
if __name__ == "__main__":
   print("AMP class")