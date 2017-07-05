#include "ex_1layer.h"
#include "nnet_layer.h"

#include "data/mnist_layer1_biases_10x1.h"
#include "data/mnist_layer1_weights_784x10.h"

// AXI-Stream port type is compatible with pointer, reference, & array input / ouputs only
// See UG902 Vivado High Level Synthesis guide (2014.4) pg 157 Figure 1-49
void ex_1layer(
      hls::stream<input_t> &data,
      hls::stream<result_t> &res,
      unsigned short &const_size_in,
      unsigned short &const_size_out)
{
    // Remove ap ctrl ports (ap_start, ap_ready, ap_idle, etc) since we only use the AXI-Stream ports
    #pragma HLS INTERFACE ap_ctrl_none port=return

    // Connect size indicators
    #pragma HLS INTERFACE ap_none port=const_size_in
    #pragma HLS INTERFACE ap_none port=const_size_out
    const_size_in   = N_LAYER_IN;
    const_size_out  = N_LAYER_OUT;

    // ****************************************
    // NETWORK INSTATIATION
    // ****************************************

    // One fully connected layer
    nnet::compute_layer<input_t, result_t, coeff_t, bias_t, accum_t, N_LAYER_IN, N_LAYER_OUT>(data, res, weights, biases);
}
