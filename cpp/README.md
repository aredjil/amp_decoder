# Approximate Message-Passing Decoder (`C++`)

This repo contains a `C++` implementation of the naive approimate message-decoder (AMP) on sparse superposition codes. It is baed on on these two papers [Replica Analysis and Approximate Message Passing Decoder for Superposition Codes](https://arxiv.org/abs/1403.8024) and [Approximate message-passing decoder and capacity-achieving sparse superposition codes](https://arxiv.org/abs/1503.08040). 

`run.sh` script performs amp decoding on sparse codes with section size of `8192` for five values of communication rate `1.3 1.4 1.45 1.5 1.6`. The section error rate results are stored in `./root/data` directory. The data is used to produce the section error rate plot saved in `figures`. The line to generate mean square error rate is commented. 
 